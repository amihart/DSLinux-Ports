/*-------------------------------------------------------------------------
  SDCCpeeph.c - The peep hole optimizer: for interpreting the
                peep hole rules

             Written By -  Sandeep Dutta . sandeep.dutta@usa.net (1999)

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   In other words, you are welcome to use, share and improve this program.
   You are forbidden to forbid anyone else to use, share and improve
   what you give them.   Help stamp out software-hoarding!
-------------------------------------------------------------------------*/

#include "common.h"

static peepRule *rootRules = NULL;
static peepRule *currRule = NULL;

#define HTAB_SIZE 53
typedef struct
  {
    char name[SDCC_NAME_MAX + 1];
    int refCount;
  }
labelHashEntry;

static hTab *labelHash = NULL;

static struct
{
  allocTrace values;
  allocTrace labels;
} _G;

static int hashSymbolName (const char *name);
static void buildLabelRefCountHash (lineNode * head);

static bool matchLine (char *, char *, hTab **);
bool isLabelDefinition (const char *line, const char **start, int *len);

#define FBYNAME(x) int x (hTab *vars, lineNode *currPl, lineNode *endPl, \
	lineNode *head, const char *cmdLine)

#if !OPT_DISABLE_PIC
void peepRules2pCode(peepRule *);
#endif

#if !OPT_DISABLE_PIC16
void pic16_peepRules2pCode(peepRule *);
#endif

/*-----------------------------------------------------------------*/
/* pcDistance - afinds a label back ward or forward                */
/*-----------------------------------------------------------------*/
int
mcs51_instruction_size(const char *inst)
{
	char *op, op1[256], op2[256];
	int opsize;
	const char *p;

	while (*inst && isspace(*inst)) inst++;

	#define ISINST(s) (strncmp(inst, (s), sizeof(s)-1) == 0)

	/* Based on the current (2003-08-22) code generation for the
	   small library, the top instruction probability is:
	   
	     57% mov/movx/movc
	      6% push
	      6% pop
	      4% inc
	      4% lcall
	      4% add
	      3% clr
	      2% subb
	*/
	/* mov, push, & pop are the 69% of the cases. Check them first! */
	if (ISINST("mov"))
	  {
	    if (*(inst+3)=='x') return 1; /* movx */
	    if (*(inst+3)=='c') return 1; /* movc */
	    goto checkoperands;           /* mov  */
	  }
	if (ISINST("push")) return 2;
	if (ISINST("pop")) return 2;

	if (ISINST("lcall")) return 3;
	if (ISINST("ret")) return 1;
	if (ISINST("ljmp")) return 3;
	if (ISINST("sjmp")) return 2;
	if (ISINST("rlc")) return 1;
	if (ISINST("rrc")) return 1;
	if (ISINST("rl")) return 1;
	if (ISINST("rr")) return 1;
	if (ISINST("swap")) return 1;
	if (ISINST("jc")) return 2;
	if (ISINST("jnc")) return 2;
	if (ISINST("jb")) return 3;
	if (ISINST("jnb")) return 3;
	if (ISINST("jbc")) return 3;
	if (ISINST("jmp")) return 1;	// always jmp @a+dptr
	if (ISINST("jz")) return 2;
	if (ISINST("jnz")) return 2;
	if (ISINST("cjne")) return 3;
	if (ISINST("mul")) return 1;
	if (ISINST("div")) return 1;
	if (ISINST("da")) return 1;
	if (ISINST("xchd")) return 1;
	if (ISINST("reti")) return 1;
	if (ISINST("nop")) return 1;
	if (ISINST("acall")) return 1;
	if (ISINST("ajmp")) return 2;

checkoperands:
	p = inst;
	while (*p && isalnum(*p)) p++;
	for (op = op1, opsize=0; *p && *p != ',' && opsize < sizeof(op1); p++) {
		if (!isspace(*p)) *op++ = *p, opsize++;
	}
	*op = '\0';
	if (*p == ',') p++;
	for (op = op2, opsize=0; *p && *p != ',' && opsize < sizeof(op2); p++) {
		if (!isspace(*p)) *op++ = *p, opsize++;
	}
	*op = '\0';

	#define IS_A(s) (*(s) == 'a' && *(s+1) == '\0')
	#define IS_C(s) (*(s) == 'c' && *(s+1) == '\0')
	#define IS_Rn(s) (*(s) == 'r' && *(s+1) >= '0' && *(s+1) <= '7')
	#define IS_atRi(s) (*(s) == '@' && *(s+1) == 'r')

	if (ISINST("mov")) {
		if (IS_C(op1) || IS_C(op2)) return 2;
		if (IS_A(op1)) {
			if (IS_Rn(op2) || IS_atRi(op2)) return 1;
			return 2;
		}
		if (IS_Rn(op1) || IS_atRi(op1)) {
			if (IS_A(op2)) return 1;
			return 2;
		}
		if (strcmp(op1, "dptr") == 0) return 3;
		if (IS_A(op2) || IS_Rn(op2) || IS_atRi(op2)) return 2;
		return 3;
	}
	if (ISINST("add") || ISINST("addc") || ISINST("subb") || ISINST("xch")) {
		if (IS_Rn(op2) || IS_atRi(op2)) return 1;
		return 2;
	}
	if (ISINST("inc") || ISINST("dec")) {
		if (IS_A(op1) || IS_Rn(op1) || IS_atRi(op1)) return 1;
		if (strcmp(op1, "dptr") == 0) return 1;
		return 2;
	}
	if (ISINST("anl") || ISINST("orl") || ISINST("xrl")) {
		if (IS_C(op1)) return 2;
		if (IS_A(op1)) {
			if (IS_Rn(op2) || IS_atRi(op2)) return 1;
			return 2;
		} else {
			if (IS_A(op2)) return 2;
			return 3;
		}
	}
	if (ISINST("clr") || ISINST("setb") || ISINST("cpl")) {
		if (IS_A(op1) || IS_C(op1)) return 1;
		return 2;
	}
	if (ISINST("djnz")) {
		if (IS_Rn(op1)) return 2;
		return 3;
	}

	if (*inst == 'a' && *(inst+1) == 'r' && *(inst+2) >= '0' && *(inst+2) <= '7' && op1[0] == '=') {
		/* ignore ar0 = 0x00 type definitions */
		return 0;
	}

	fprintf(stderr, "Warning, peephole unrecognized instruction: %s\n", inst);
	return 3;
}

int 
pcDistance (lineNode * cpos, char *lbl, bool back)
{
  lineNode *pl = cpos;
  char buff[MAX_PATTERN_LEN];
  int dist = 0;

  SNPRINTF (buff, sizeof(buff), "%s:", lbl);
  while (pl)
    {

      if (pl->line &&
	  *pl->line != ';' &&
	  pl->line[strlen (pl->line) - 1] != ':' &&
	  !pl->isDebug) {
	        if (TARGET_IS_MCS51) {
			dist += mcs51_instruction_size(pl->line);
		} else {
			dist += 3;
		}
	}

      if (strncmp (pl->line, buff, strlen (buff)) == 0)
	return dist;

      if (back)
	pl = pl->prev;
      else
	pl = pl->next;

    }
  return 0;
}

/*-----------------------------------------------------------------*/
/* flat24bitModeAndPortDS390 - 					   */
/*-----------------------------------------------------------------*/
FBYNAME (flat24bitModeAndPortDS390)
{
    return (((strcmp(port->target,"ds390") == 0) ||
	     (strcmp(port->target,"ds400") == 0)) && 
	    (options.model == MODEL_FLAT24));
}

/*-----------------------------------------------------------------*/
/* portIsDS390 - return true if port is DS390  			   */
/*-----------------------------------------------------------------*/
FBYNAME (portIsDS390)
{
    return ((strcmp(port->target,"ds390") == 0) ||
	    (strcmp(port->target,"ds400") == 0));
}

/*-----------------------------------------------------------------*/
/* flat24bitMode - will check to see if we are in flat24 mode      */
/*-----------------------------------------------------------------*/
FBYNAME (flat24bitMode)
{
  return (options.model == MODEL_FLAT24);
}

/*-----------------------------------------------------------------*/
/* xramMovcOption - check if using movc to read xram               */
/*-----------------------------------------------------------------*/
FBYNAME (xramMovcOption)
{
  return (options.xram_movc && (strcmp(port->target,"mcs51") == 0));
}






/*-----------------------------------------------------------------*/
/* labelInRange - will check to see if label %5 is within range    */
/*-----------------------------------------------------------------*/
FBYNAME (labelInRange)
{
  /* assumes that %5 pattern variable has the label name */
  char *lbl = hTabItemWithKey (vars, 5);
  int dist = 0;

  if (!lbl)
    return FALSE;

  /* Don't optimize jumps in a jump table; a more generic test */
  if (currPl->ic && currPl->ic->op == JUMPTABLE)
    return FALSE;
    
  /* if the previous two instructions are "ljmp"s then don't
     do it since it can be part of a jump table */
  if (currPl->prev && currPl->prev->prev &&
      strstr (currPl->prev->line, "ljmp") &&
      strstr (currPl->prev->prev->line, "ljmp"))
    return FALSE;

  /* calculate the label distance : the jump for reladdr can be
     +/- 127 bytes, here Iam assuming that an average 8051
     instruction is 2 bytes long, so if the label is more than
     63 intructions away, the label is considered out of range
     for a relative jump. we could get more precise this will
     suffice for now since it catches > 90% cases */
  dist = (pcDistance (currPl, lbl, TRUE) +
	  pcDistance (currPl, lbl, FALSE));

/*    changed to 127, now that pcDistance return actual number of bytes */
  if (!dist || dist > 127)
    return FALSE;

  return TRUE;
}

/*-----------------------------------------------------------------*/
/* labelIsReturnOnly - Check if label %5 is followed by RET        */
/*-----------------------------------------------------------------*/
FBYNAME (labelIsReturnOnly)
{
  /* assumes that %5 pattern variable has the label name */
  const char *label, *p;
  const lineNode *pl;
  int len;

  label = hTabItemWithKey (vars, 5);
  if (!label) return FALSE;
  len = strlen(label);

  for(pl = currPl; pl; pl = pl->next) {
	if (pl->line && !pl->isDebug &&
	  pl->line[strlen(pl->line)-1] == ':') {
		if (strncmp(pl->line, label, len) == 0) break; /* Found Label */
		if (strlen(pl->line) != 7 || !isdigit(*(pl->line)) ||
		  !isdigit(*(pl->line+1)) || !isdigit(*(pl->line+2)) ||
		  !isdigit(*(pl->line+3)) || !isdigit(*(pl->line+4)) ||
		  *(pl->line+5) != '$') {
			return FALSE; /* non-local label encountered */
		}
	}
  }
  if (!pl) return FALSE; /* did not find the label */
  pl = pl->next;
  if (!pl || !pl->line || pl->isDebug) return FALSE; /* next line not valid */
  p = pl->line;
  for (p = pl->line; *p && isspace(*p); p++)
	  ;
  if (strcmp(p, "ret") == 0) return TRUE;
  return FALSE;
}


/*-----------------------------------------------------------------*/
/* okToRemoveSLOC - Check if label %1 is a SLOC and not other      */
/* usage of it in the code depends on a value from this section    */
/*-----------------------------------------------------------------*/
FBYNAME (okToRemoveSLOC)
{
  const lineNode *pl;
  const char *sloc, *p;
  int dummy1, dummy2, dummy3;

  /* assumes that %1 as the SLOC name */
  sloc = hTabItemWithKey (vars, 1);
  if (sloc == NULL) return FALSE;
  p = strstr(sloc, "sloc");
  if (p == NULL) return FALSE;
  p += 4;
  if (sscanf(p, "%d_%d_%d", &dummy1, &dummy2, &dummy3) != 3) return FALSE;
  /*TODO: ultra-paranoid: get funtion name from "head" and check that */
  /* the sloc name begins with that.  Probably not really necessary */

  /* Look for any occurance of this SLOC before the peephole match */
  for (pl = currPl->prev; pl; pl = pl->prev) {
	if (pl->line && !pl->isDebug && !pl->isComment
	  && *pl->line != ';' && strstr(pl->line, sloc))
		return FALSE;
  }
  /* Look for any occurance of this SLOC after the peephole match */
  for (pl = endPl->next; pl; pl = pl->next) {
	if (pl->line && !pl->isDebug && !pl->isComment
	  && *pl->line != ';' && strstr(pl->line, sloc))
		return FALSE;
  }
  return TRUE; /* safe for a peephole to remove it :) */
}


/*-----------------------------------------------------------------*/
/* operandsNotSame - check if %1 & %2 are the same                 */
/*-----------------------------------------------------------------*/
FBYNAME (operandsNotSame)
{
  char *op1 = hTabItemWithKey (vars, 1);
  char *op2 = hTabItemWithKey (vars, 2);

  if (strcmp (op1, op2) == 0)
    return FALSE;
  else
    return TRUE;
}

/*-----------------------------------------------------------------*/
/* operandsNotSame3- check if any pair of %1,%2,%3 are the same    */
/*-----------------------------------------------------------------*/
FBYNAME (operandsNotSame3)
{
  char *op1 = hTabItemWithKey (vars, 1);
  char *op2 = hTabItemWithKey (vars, 2);
  char *op3 = hTabItemWithKey (vars, 3);

  if ( (strcmp (op1, op2) == 0) ||
       (strcmp (op1, op3) == 0) ||
       (strcmp (op2, op3) == 0) )
    return FALSE;
  else
    return TRUE;
}

/*-----------------------------------------------------------------*/
/* operandsNotSame4- check if any pair of %1,%2,%3,.. are the same */
/*-----------------------------------------------------------------*/
FBYNAME (operandsNotSame4)
{
  char *op1 = hTabItemWithKey (vars, 1);
  char *op2 = hTabItemWithKey (vars, 2);
  char *op3 = hTabItemWithKey (vars, 3);
  char *op4 = hTabItemWithKey (vars, 4);

  if ( (strcmp (op1, op2) == 0) ||
       (strcmp (op1, op3) == 0) ||
       (strcmp (op1, op4) == 0) ||
       (strcmp (op2, op3) == 0) ||
       (strcmp (op2, op4) == 0) ||
       (strcmp (op3, op4) == 0) )
    return FALSE;
  else
    return TRUE;
}

/*-----------------------------------------------------------------*/
/* operandsNotSame5- check if any pair of %1,%2,%3,.. are the same */
/*-----------------------------------------------------------------*/
FBYNAME (operandsNotSame5)
{
  char *op1 = hTabItemWithKey (vars, 1);
  char *op2 = hTabItemWithKey (vars, 2);
  char *op3 = hTabItemWithKey (vars, 3);
  char *op4 = hTabItemWithKey (vars, 4);
  char *op5 = hTabItemWithKey (vars, 5);

  if ( (strcmp (op1, op2) == 0) ||
       (strcmp (op1, op3) == 0) ||
       (strcmp (op1, op4) == 0) ||
       (strcmp (op1, op5) == 0) ||
       (strcmp (op2, op3) == 0) ||
       (strcmp (op2, op4) == 0) ||
       (strcmp (op2, op5) == 0) ||
       (strcmp (op3, op4) == 0) ||
       (strcmp (op3, op5) == 0) ||
       (strcmp (op4, op5) == 0) )
    return FALSE;
  else
    return TRUE;
}

/*-----------------------------------------------------------------*/
/* operandsNotSame6- check if any pair of %1,%2,%3,.. are the same */
/*-----------------------------------------------------------------*/
FBYNAME (operandsNotSame6)
{
  char *op1 = hTabItemWithKey (vars, 1);
  char *op2 = hTabItemWithKey (vars, 2);
  char *op3 = hTabItemWithKey (vars, 3);
  char *op4 = hTabItemWithKey (vars, 4);
  char *op5 = hTabItemWithKey (vars, 5);
  char *op6 = hTabItemWithKey (vars, 6);

  if ( (strcmp (op1, op2) == 0) ||
       (strcmp (op1, op3) == 0) ||
       (strcmp (op1, op4) == 0) ||
       (strcmp (op1, op5) == 0) ||
       (strcmp (op1, op6) == 0) ||
       (strcmp (op2, op3) == 0) ||
       (strcmp (op2, op4) == 0) ||
       (strcmp (op2, op5) == 0) ||
       (strcmp (op2, op6) == 0) ||
       (strcmp (op3, op4) == 0) ||
       (strcmp (op3, op5) == 0) ||
       (strcmp (op3, op6) == 0) ||
       (strcmp (op4, op5) == 0) ||
       (strcmp (op4, op6) == 0) ||
       (strcmp (op5, op6) == 0) )
    return FALSE;
  else
    return TRUE;
}


/*-----------------------------------------------------------------*/
/* operandsNotSame7- check if any pair of %1,%2,%3,.. are the same */
/*-----------------------------------------------------------------*/
FBYNAME (operandsNotSame7)
{
  char *op1 = hTabItemWithKey (vars, 1);
  char *op2 = hTabItemWithKey (vars, 2);
  char *op3 = hTabItemWithKey (vars, 3);
  char *op4 = hTabItemWithKey (vars, 4);
  char *op5 = hTabItemWithKey (vars, 5);
  char *op6 = hTabItemWithKey (vars, 6);
  char *op7 = hTabItemWithKey (vars, 7);

  if ( (strcmp (op1, op2) == 0) ||
       (strcmp (op1, op3) == 0) ||
       (strcmp (op1, op4) == 0) ||
       (strcmp (op1, op5) == 0) ||
       (strcmp (op1, op6) == 0) ||
       (strcmp (op1, op7) == 0) ||
       (strcmp (op2, op3) == 0) ||
       (strcmp (op2, op4) == 0) ||
       (strcmp (op2, op5) == 0) ||
       (strcmp (op2, op6) == 0) ||
       (strcmp (op2, op7) == 0) ||
       (strcmp (op3, op4) == 0) ||
       (strcmp (op3, op5) == 0) ||
       (strcmp (op3, op6) == 0) ||
       (strcmp (op3, op7) == 0) ||
       (strcmp (op4, op5) == 0) ||
       (strcmp (op4, op6) == 0) ||
       (strcmp (op4, op7) == 0) ||
       (strcmp (op5, op6) == 0) ||
       (strcmp (op5, op7) == 0) ||
       (strcmp (op6, op7) == 0) )
    return FALSE;
  else
    return TRUE;
}

/*-----------------------------------------------------------------*/
/* operandsNotSame8- check if any pair of %1,%2,%3,.. are the same */
/*-----------------------------------------------------------------*/
FBYNAME (operandsNotSame8)
{
  char *op1 = hTabItemWithKey (vars, 1);
  char *op2 = hTabItemWithKey (vars, 2);
  char *op3 = hTabItemWithKey (vars, 3);
  char *op4 = hTabItemWithKey (vars, 4);
  char *op5 = hTabItemWithKey (vars, 5);
  char *op6 = hTabItemWithKey (vars, 6);
  char *op7 = hTabItemWithKey (vars, 7);
  char *op8 = hTabItemWithKey (vars, 8);

  if ( (strcmp (op1, op2) == 0) ||
       (strcmp (op1, op3) == 0) ||
       (strcmp (op1, op4) == 0) ||
       (strcmp (op1, op5) == 0) ||
       (strcmp (op1, op6) == 0) ||
       (strcmp (op1, op7) == 0) ||
       (strcmp (op1, op8) == 0) ||
       (strcmp (op2, op3) == 0) ||
       (strcmp (op2, op4) == 0) ||
       (strcmp (op2, op5) == 0) ||
       (strcmp (op2, op6) == 0) ||
       (strcmp (op2, op7) == 0) ||
       (strcmp (op2, op8) == 0) ||
       (strcmp (op3, op4) == 0) ||
       (strcmp (op3, op5) == 0) ||
       (strcmp (op3, op6) == 0) ||
       (strcmp (op3, op7) == 0) ||
       (strcmp (op3, op8) == 0) ||
       (strcmp (op4, op5) == 0) ||
       (strcmp (op4, op6) == 0) ||
       (strcmp (op4, op7) == 0) ||
       (strcmp (op4, op8) == 0) ||
       (strcmp (op5, op6) == 0) ||
       (strcmp (op5, op7) == 0) ||
       (strcmp (op5, op8) == 0) ||
       (strcmp (op6, op7) == 0) ||
       (strcmp (op6, op8) == 0) ||
       (strcmp (op7, op8) == 0) )
    return FALSE;
  else
    return TRUE;
}


/* labelRefCount:

 * takes two parameters: a variable (bound to a label name)
 * and an expected reference count.
 *
 * Returns TRUE if that label is defined and referenced exactly
 * the given number of times.
 */
FBYNAME (labelRefCount)
{
  int varNumber, expectedRefCount;
  bool rc = FALSE;

  /* If we don't have the label hash table yet, build it. */
  if (!labelHash)
    {
      buildLabelRefCountHash (head);
    }

  if (sscanf (cmdLine, "%*[ \t%]%d %d", &varNumber, &expectedRefCount) == 2)
    {
      char *label = hTabItemWithKey (vars, varNumber);

      if (label)
	{
	  labelHashEntry *entry;

	  entry = hTabFirstItemWK (labelHash, hashSymbolName (label));

	  while (entry)
	    {
	      if (!strcmp (label, entry->name))
		{
		  break;
		}
	      entry = hTabNextItemWK (labelHash);
	    }
	  if (entry)
	    {
#if 0
	      /* debug spew. */
	      fprintf (stderr, "labelRefCount: %s has refCount %d, want %d\n",
		       label, entry->refCount, expectedRefCount);
#endif

	      rc = (expectedRefCount == entry->refCount);
	    }
	  else
	    {
	      fprintf (stderr, "*** internal error: no label has entry for"
		       " %s in labelRefCount peephole.\n",
		       label);
	    }
	}
      else
	{
	  fprintf (stderr, "*** internal error: var %d not bound"
		   " in peephole labelRefCount rule.\n",
		   varNumber);
	}

    }
  else
    {
      fprintf (stderr,
	       "*** internal error: labelRefCount peephole restriction"
	       " malformed: %s\n", cmdLine);
    }
  return rc;
}

/* Within the context of the lines currPl through endPl, determine
** if the variable var contains a symbol that is volatile. Returns
** TRUE only if it is certain that this was not volatile (the symbol
** was found and not volatile, or var was a constant or CPU register).
** Returns FALSE if the symbol was found and volatile, the symbol was
** not found, or var was a indirect/pointer addressing mode.
*/
static bool
notVolatileVariable(char *var, lineNode *currPl, lineNode *endPl)
{
  char symname[SDCC_NAME_MAX + 1];
  char *p = symname;
  char *vp = var;
  lineNode *cl;
  operand *op;
  iCode *last_ic;

  /* Can't tell if indirect accesses are volatile or not, so
  ** assume they are, just to be safe.
  */
  if (TARGET_IS_MCS51 || TARGET_IS_DS390 || TARGET_IS_DS400)
    {
      if (*var=='@')
        return FALSE;
    }
  if (TARGET_IS_Z80 || TARGET_IS_GBZ80)
    {
      if (strstr(var,"(bc)"))
        return FALSE;
      if (strstr(var,"(de)"))
        return FALSE;
      if (strstr(var,"(hl)"))
        return FALSE;
      if (strstr(var,"(ix"))
        return FALSE;
      if (strstr(var,"(iy"))
        return FALSE;
    }

  /* Extract a symbol name from the variable */
  while (*vp && (*vp!='_'))
    vp++;
  while (*vp && (isalnum(*vp) || *vp=='_'))
    *p++ = *vp++;
  *p='\0';

  if (!symname[0])
    {
      /* Nothing resembling a symbol name was found, so it can't
         be volatile
      */
      return TRUE;
    }

  last_ic = NULL;
  for (cl = currPl; cl!=endPl->next; cl = cl->next)
  {
    if (cl->ic && (cl->ic!=last_ic))
      {
        last_ic = cl->ic;
        switch (cl->ic->op)
          {
          case IFX:
            op = IC_COND (cl->ic);
            if (IS_SYMOP (op) && !strcmp(OP_SYMBOL (op)->rname,symname) )
              return !op->isvolatile;
          case JUMPTABLE:
            op = IC_JTCOND (cl->ic);
            if (IS_SYMOP (op) && !strcmp(OP_SYMBOL (op)->rname,symname) )
              return !op->isvolatile;
          default:
            op = IC_LEFT (cl->ic);
            if (IS_SYMOP (op) && !strcmp(OP_SYMBOL (op)->rname,symname) )
              return !op->isvolatile;
            op = IC_RIGHT (cl->ic);
            if (IS_SYMOP (op) && !strcmp(OP_SYMBOL (op)->rname,symname) )
              return !op->isvolatile;
            op = IC_RESULT (cl->ic);
            if (IS_SYMOP (op) && !strcmp(OP_SYMBOL (op)->rname,symname) )
              return !op->isvolatile;
          }
      }
  }
  
  /* Couldn't find the symbol for some reason. Assume volatile. */
  return FALSE;
}

/*  notVolatile:
 *
 *  This rule restriction has two different behaviours depending on
 *  the number of parameters given.
 *
 *    if notVolatile                 (no parameters given)
 *       The rule is applied only if none of the iCodes originating
 *       the matched pattern reference a volatile operand.
 *
 *    if notVolatile %1 ...          (one or more parameters given)
 *       The rule is applied if the parameters are not expressions
 *       containing volatile symbols and are not pointer accesses.
 *
 */
FBYNAME (notVolatile)
{
  int varNumber;
  char *var;
  bool notvol;
  char *digitend;
  lineNode *cl;
  operand *op;

  if (!cmdLine)
    {
      /* If no parameters given, just scan the iCodes for volatile operands */
      for (cl = currPl; cl!=endPl->next; cl = cl->next)
      {
        if (cl->ic)
          {
            switch (cl->ic->op)
              {
              case IFX:
                op = IC_COND (cl->ic);
                if (IS_SYMOP (op) && op->isvolatile)
                  return FALSE;
              case JUMPTABLE:
                op = IC_JTCOND (cl->ic);
                if (IS_SYMOP (op) && op->isvolatile)
                  return FALSE;
              default:
                op = IC_LEFT (cl->ic);
                if (IS_SYMOP (op) && op->isvolatile)
                  return FALSE;
                op = IC_RIGHT (cl->ic);
                if (IS_SYMOP (op) && op->isvolatile)
                  return FALSE;
                op = IC_RESULT (cl->ic);
                if (IS_SYMOP (op) && op->isvolatile)
                  return FALSE;
              }
          }
      }
      return TRUE;
    }

  /* There were parameters; check the volatility of each */
  while (*cmdLine && isspace(*cmdLine))
    cmdLine++;
  while (*cmdLine)
    {
      if (*cmdLine!='%')
        goto error;
      cmdLine++;
      if (!isdigit(*cmdLine))
        goto error;
      varNumber = strtol(cmdLine, &digitend, 10);
      cmdLine = digitend;
      while (*cmdLine && isspace(*cmdLine))
        cmdLine++;

      var = hTabItemWithKey (vars, varNumber);

      if (var)
        {
          notvol = notVolatileVariable (var, currPl, endPl);
          if (!notvol)
            return FALSE;
        }
      else
	{
	  fprintf (stderr, "*** internal error: var %d not bound"
		   " in peephole notVolatile rule.\n",
		   varNumber);
	  return FALSE;
	}
    }

  return TRUE;
    
    
error:
  fprintf (stderr,
           "*** internal error: notVolatile peephole restriction"
           " malformed: %s\n", cmdLine);
  return FALSE;
}
    

/*-----------------------------------------------------------------*/
/* callFuncByName - calls a function as defined in the table       */
/*-----------------------------------------------------------------*/
int 
callFuncByName (char *fname,
		hTab * vars,
		lineNode * currPl,
		lineNode * endPl,
		lineNode * head)
{
  struct ftab
  {
    char *fname;
    int (*func) (hTab *, lineNode *, lineNode *, lineNode *, const char *);
  }
  ftab[] =
  {
    {
      "labelInRange", labelInRange
    }
    ,
    {
      "operandsNotSame", operandsNotSame
    }
    ,
    {
      "operandsNotSame3", operandsNotSame3
    }
    ,
    {
      "operandsNotSame4", operandsNotSame4
    }
    ,
    {
      "operandsNotSame5", operandsNotSame5
    }
    ,
    {
      "operandsNotSame6", operandsNotSame6
    }
    ,
    {
      "operandsNotSame7", operandsNotSame7
    }
    ,
    {
      "operandsNotSame8", operandsNotSame8
    }
    ,	  
    {
      "24bitMode", flat24bitMode
    }
    ,
    {
      "xramMovcOption", xramMovcOption
    }
    ,
    {
      "labelRefCount", labelRefCount
    }
    ,
    {
      "portIsDS390", portIsDS390
    },
    {
      "labelIsReturnOnly", labelIsReturnOnly
    },
    {
      "okToRemoveSLOC", okToRemoveSLOC
    },
    {
      "24bitModeAndPortDS390", flat24bitModeAndPortDS390
    },
    {
      "notVolatile", notVolatile
    }
  };
  int 	i;
  char  *cmdCopy, *funcName, *funcArgs;
  int 	rc = -1;
    
  /* Isolate the function name part (we are passed the full condition 
   * string including arguments) 
   */
  cmdCopy = Safe_strdup(fname);
  funcName = strtok(cmdCopy, " \t");
  funcArgs = strtok(NULL, "");

    for (i = 0; i < ((sizeof (ftab)) / (sizeof (struct ftab))); i++)
    {
	if (strcmp (ftab[i].fname, funcName) == 0)
	{
	    rc = (*ftab[i].func) (vars, currPl, endPl, head,
				  funcArgs);
	}
    }
    
    if (rc == -1)
    {
	fprintf (stderr, 
		 "could not find named function \"%s\" in "
		 "peephole function table\n",
		 funcName);
        // If the function couldn't be found, let's assume it's
	// a bad rule and refuse it.
	rc = FALSE;
    }

    Safe_free(cmdCopy);
    
  return rc;
}

/*-----------------------------------------------------------------*/
/* printLine - prints a line chain into a given file               */
/*-----------------------------------------------------------------*/
void 
printLine (lineNode * head, FILE * of)
{
  iCode *last_ic = NULL;
  bool debug_iCode_tracking = (getenv("DEBUG_ICODE_TRACKING")!=NULL);
  
  if (!of)
    of = stdout;

  while (head)
    {
      if (head->ic!=last_ic)
        {
          last_ic = head->ic;
          if (debug_iCode_tracking)
            {
              if (head->ic)
                fprintf (of, "; block = %d, seq = %d\n",
                         head->ic->block, head->ic->seq);
              else
                fprintf (of, "; iCode lost\n");
            }
        }
        
      /* don't indent comments & labels */
      if (head->line &&
	  (*head->line == ';' ||
	   head->line[strlen (head->line) - 1] == ':')) {
	fprintf (of, "%s\n", head->line);
      } else {
	if (head->isInline && *head->line=='#') {
	  // comment out preprocessor directives in inline asm
	  fprintf (of, ";");
	}
	fprintf (of, "\t%s\n", head->line);
      }
      head = head->next;
    }
}

/*-----------------------------------------------------------------*/
/* newPeepRule - creates a new peeprule and attach it to the root  */
/*-----------------------------------------------------------------*/
peepRule *
newPeepRule (lineNode * match,
	     lineNode * replace,
	     char *cond,
	     int restart)
{
  peepRule *pr;

  pr = Safe_alloc ( sizeof (peepRule));
  pr->match = match;
  pr->replace = replace;
  pr->restart = restart;

  if (cond && *cond)
    {
      pr->cond = Safe_strdup (cond);
    }
  else
    pr->cond = NULL;

  pr->vars = newHashTable (100);

  /* if root is empty */
  if (!rootRules)
    rootRules = currRule = pr;
  else
    currRule = currRule->next = pr;

  return pr;
}

/*-----------------------------------------------------------------*/
/* newLineNode - creates a new peep line                           */
/*-----------------------------------------------------------------*/
lineNode *
newLineNode (char *line)
{
  lineNode *pl;

  pl = Safe_alloc ( sizeof (lineNode));
  pl->line = Safe_strdup (line);
  pl->ic = NULL;
  return pl;
}

/*-----------------------------------------------------------------*/
/* connectLine - connects two lines                                */
/*-----------------------------------------------------------------*/
lineNode *
connectLine (lineNode * pl1, lineNode * pl2)
{
  if (!pl1 || !pl2)
    {
      fprintf (stderr, "trying to connect null line\n");
      return NULL;
    }

  pl2->prev = pl1;
  pl1->next = pl2;

  return pl2;
}

#define SKIP_SPACE(x,y) { while (*x && (isspace(*x) || *x == '\n')) x++; \
                         if (!*x) { fprintf(stderr,y); return ; } }

#define EXPECT_STR(x,y,z) { while (*x && strncmp(x,y,strlen(y))) x++ ;   \
                           if (!*x) { fprintf(stderr,z); return ; } }
#define EXPECT_CHR(x,y,z) { while (*x && *x != y) x++ ;   \
                           if (!*x) { fprintf(stderr,z); return ; } }

/*-----------------------------------------------------------------*/
/* getPeepLine - parses the peep lines                             */
/*-----------------------------------------------------------------*/
static void 
getPeepLine (lineNode ** head, char **bpp)
{
  char lines[MAX_PATTERN_LEN];
  char *lp;

  lineNode *currL = NULL;
  char *bp = *bpp;
  while (1)
    {

      if (!*bp)
	{
	  fprintf (stderr, "unexpected end of match pattern\n");
	  return;
	}

      if (*bp == '\n')
	{
	  bp++;
	  while (isspace (*bp) ||
		 *bp == '\n')
	    bp++;
	}

      if (*bp == '}')
	{
	  bp++;
	  break;
	}

      /* read till end of line */
      lp = lines;
      while ((*bp != '\n' && *bp != '}') && *bp)
	*lp++ = *bp++;

      *lp = '\0';
      if (!currL)
	*head = currL = newLineNode (lines);
      else
	currL = connectLine (currL, newLineNode (lines));

      lp = lines;
      while (*lp && isspace(*lp))
        lp++;
      if (*lp==';')
        currL->isComment = 1;
    }

  *bpp = bp;
}

/*-----------------------------------------------------------------*/
/* readRules - reads the rules from a string buffer                */
/*-----------------------------------------------------------------*/
static void 
readRules (char *bp)
{
  char restart = 0;
  char lines[MAX_PATTERN_LEN];
  char *lp;
  lineNode *match;
  lineNode *replace;
  lineNode *currL = NULL;

  if (!bp)
    return;
top:
  restart = 0;
  /* look for the token "replace" that is the
     start of a rule */
  while (*bp && strncmp (bp, "replace", 7))
    bp++;

  /* if not found */
  if (!*bp)
    return;

  /* then look for either "restart" or '{' */
  while (strncmp (bp, "restart", 7) &&
	 *bp != '{' && bp)
    bp++;

  /* not found */
  if (!*bp)
    {
      fprintf (stderr, "expected 'restart' or '{'\n");
      return;
    }

  /* if brace */
  if (*bp == '{')
    bp++;
  else
    {				/* must be restart */
      restart++;
      bp += strlen ("restart");
      /* look for '{' */
      EXPECT_CHR (bp, '{', "expected '{'\n");
      bp++;
    }

  /* skip thru all the blank space */
  SKIP_SPACE (bp, "unexpected end of rule\n");

  match = replace = currL = NULL;
  /* we are the start of a rule */
  getPeepLine (&match, &bp);

  /* now look for by */
  EXPECT_STR (bp, "by", "expected 'by'\n");

  /* then look for a '{' */
  EXPECT_CHR (bp, '{', "expected '{'\n");
  bp++;

  SKIP_SPACE (bp, "unexpected end of rule\n");
  getPeepLine (&replace, &bp);

  /* look for a 'if' */
  while ((isspace (*bp) || *bp == '\n') && *bp)
    bp++;

  if (strncmp (bp, "if", 2) == 0)
    {
      bp += 2;
      while ((isspace (*bp) || *bp == '\n') && *bp)
	bp++;
      if (!*bp)
	{
	  fprintf (stderr, "expected condition name\n");
	  return;
	}

      /* look for the condition */
      lp = lines;
      while (*bp && (*bp != '\n'))
	{
	  *lp++ = *bp++;
	}
      *lp = '\0';

      newPeepRule (match, replace, lines, restart);
    }
  else
    newPeepRule (match, replace, NULL, restart);
  goto top;

}

/*-----------------------------------------------------------------*/
/* keyForVar - returns the numeric key for a var                   */
/*-----------------------------------------------------------------*/
static int 
keyForVar (char *d)
{
  int i = 0;

  while (isdigit (*d))
    {
      i *= 10;
      i += (*d++ - '0');
    }

  return i;
}

/*-----------------------------------------------------------------*/
/* bindVar - binds a value to a variable in the given hashtable    */
/*-----------------------------------------------------------------*/
static void 
bindVar (int key, char **s, hTab ** vtab)
{
  char vval[MAX_PATTERN_LEN];
  char *vvx;
  char *vv = vval;

  /* first get the value of the variable */
  vvx = *s;
  /* the value is ended by a ',' or space or newline or null or ) */
  while (*vvx &&
	 *vvx != ',' &&
	 !isspace (*vvx) &&
	 *vvx != '\n' &&
	 *vvx != ':' &&
	 *vvx != ')')
    {
      char ubb = 0;
      /* if we find a '(' then we need to balance it */
      if (*vvx == '(')
	{
	  ubb++;
	  while (ubb)
	    {
	      *vv++ = *vvx++;
	      if (*vvx == '(')
		ubb++;
	      if (*vvx == ')')
		ubb--;
	    }
	  // include the trailing ')'
	  *vv++ = *vvx++;
	}
      else
	*vv++ = *vvx++;
    }
  *s = vvx;
  *vv = '\0';
  /* got value */
  vvx = traceAlloc (&_G.values, Safe_strdup(vval));

  hTabAddItem (vtab, key, vvx);
}

/*-----------------------------------------------------------------*/
/* matchLine - matches one line                                    */
/*-----------------------------------------------------------------*/
static bool 
matchLine (char *s, char *d, hTab ** vars)
{

  if (!s || !(*s))
    return FALSE;

  while (*s && *d)
    {

      /* skip white space in both */
      while (isspace (*s))
	s++;
      while (isspace (*d))
	d++;

      /* if the destination is a var */
      if (*d == '%' && isdigit (*(d + 1)) && vars)
	{
	  char *v = hTabItemWithKey (*vars, keyForVar (d + 1));
	  /* if the variable is already bound
	     then it MUST match with dest */
	  if (v)
	    {
	      while (*v)
		if (*v++ != *s++)
		  return FALSE;
	    }
	  else
	    /* variable not bound we need to
	       bind it */
	    bindVar (keyForVar (d + 1), &s, vars);

	  /* in either case go past the variable */
	  d++;
	  while (isdigit (*d))
	    d++;

	  while (isspace (*s))
	    s++;
	  while (isspace (*d))
	    d++;
	}

      /* they should be an exact match other wise */
      if (*s && *d)
	{
	  if (*s++ != *d++)
	    return FALSE;
	}

    }

  /* get rid of the trailing spaces
     in both source & destination */
  if (*s)
    while (isspace (*s))
      s++;

  if (*d)
    while (isspace (*d))
      d++;

  /* after all this if only one of them
     has something left over then no match */
  if (*s || *d)
    return FALSE;

  return TRUE;
}

/*-----------------------------------------------------------------*/
/* matchRule - matches a all the rule lines                        */
/*-----------------------------------------------------------------*/
static bool 
matchRule (lineNode * pl,
	   lineNode ** mtail,
	   peepRule * pr,
	   lineNode * head)
{
  lineNode *spl;		/* source pl */
  lineNode *rpl;		/* rule peep line */

/*     setToNull((void *) &pr->vars);    */
/*     pr->vars = newHashTable(100); */

  /* for all the lines defined in the rule */
  rpl = pr->match;
  spl = pl;
  while (spl && rpl)
    {

      /* if the source line starts with a ';' then
         comment line don't process or the source line
         contains == . debugger information skip it */
      if (spl->line &&
	  (*spl->line == ';' || spl->isDebug))
	{
	  spl = spl->next;
	  continue;
	}

      if (!matchLine (spl->line, rpl->line, &pr->vars))
	return FALSE;

      rpl = rpl->next;
      if (rpl)
	spl = spl->next;
    }

  /* if rules ended */
  if (!rpl)
    {
      /* if this rule has additional conditions */
      if (pr->cond)
	{
	  if (callFuncByName (pr->cond, pr->vars, pl, spl, head))
	    {
	      *mtail = spl;
	      return TRUE;
	    }
	  else
	    return FALSE;
	}
      else
	{
	  *mtail = spl;
	  return TRUE;
	}
    }
  else
    return FALSE;
}

static void
reassociate_ic_down (lineNode *shead, lineNode *stail,
                     lineNode *rhead, lineNode *rtail)
{
  lineNode *csl;	/* current source line */
  lineNode *crl;	/* current replacement line */

  csl = shead;
  crl = rhead;
  while (1)
    {
      /* skip over any comments */
      while (csl!=stail->next && csl->isComment)
        csl = csl->next;
      while (crl!=rtail->next && crl->isComment)
        crl = crl->next;

      /* quit if we reach the end */
      if ((csl==stail->next) || (crl==rtail->next) || crl->ic)
        break;

      if (matchLine(csl->line,crl->line,NULL))
        {
          crl->ic = csl->ic;
          csl = csl->next;
          crl = crl->next;
        }
      else
        break;
    }
}

static void
reassociate_ic_up (lineNode *shead, lineNode *stail,
                   lineNode *rhead, lineNode *rtail)
{
  lineNode *csl;	/* current source line */
  lineNode *crl;	/* current replacement line */

  csl = stail;
  crl = rtail;
  while (1)
    {
      /* skip over any comments */
      while (csl!=shead->prev && csl->isComment)
        csl = csl->prev;
      while (crl!=rhead->prev && crl->isComment)
        crl = crl->prev;

      /* quit if we reach the end */
      if ((csl==shead->prev) || (crl==rhead->prev) || crl->ic)
        break;

      if (matchLine(csl->line,crl->line,NULL))
        {
          crl->ic = csl->ic;
          csl = csl->prev;
          crl = crl->prev;
        }
      else
        break;
    }
}

/*------------------------------------------------------------------*/
/* reassociate_ic - reassociate replacement lines with origin iCode */
/*------------------------------------------------------------------*/
static void
reassociate_ic (lineNode *shead, lineNode *stail,
                lineNode *rhead, lineNode *rtail)
{
  lineNode *csl;	/* current source line */
  lineNode *crl;	/* current replacement line */
  bool single_iCode;
  iCode *ic;
  
  /* Check to see if all the source lines (excluding comments) came
  ** for the same iCode
  */
  ic = NULL;
  for (csl=shead;csl!=stail->next;csl=csl->next)
    if (csl->ic && !csl->isComment)
      {
        ic = csl->ic;
        break;
      }
  single_iCode = (ic!=NULL);
  for (csl=shead;csl!=stail->next;csl=csl->next)
    if ((csl->ic != ic) && !csl->isComment)
      {
        /* More than one iCode was found. However, if it's just the
        ** last line with the different iCode and it was not changed
        ** in the replacement, everything else must be the first iCode.
        */
        if ((csl==stail) && matchLine (stail->line, rtail->line, NULL))
          {
            rtail->ic = stail->ic;
            for (crl=rhead;crl!=rtail;crl=crl->next)
              crl->ic = ic;
            return;
          }
            
        single_iCode = FALSE;
        break;
      }
  
  /* If all of the source lines came from the same iCode, then so have
  ** all of the replacement lines too.
  */
  if (single_iCode)
    {
      for (crl=rhead;crl!=rtail->next;crl=crl->next)
        crl->ic = ic;
      return;
    }
  
  /* The source lines span iCodes, so we may end up with replacement
  ** lines that we don't know which iCode(s) to associate with. Do the
  ** best we can by using the following strategies:
  **    1) Start at the top and scan down. As long as the source line
  **       matches the replacement line, they have the same iCode.
  **    2) Start at the bottom and scan up. As long as the source line
  **       matches the replacement line, they have the same iCode.
  **    3) For any label in the source, look for a matching label in
  **       the replacment. If found, they have the same iCode. From
  **       these matching labels, scan down for additional matching
  **       lines; if found, they also have the same iCode.
  */

  /* Strategy #1: Start at the top and scan down for matches
  */
  reassociate_ic_down(shead,stail,rhead,rtail);
  
  /* Strategy #2: Start at the bottom and scan up for matches
  */
  reassociate_ic_up(shead,stail,rhead,rtail);

  /* Strategy #3: Try to match labels
  */
  csl = shead;
  while (1)
    {
      const char *labelStart;
      int labelLength;
      
      /* skip over any comments */
      while (csl!=stail->next && csl->isComment)
        csl = csl->next;
      if (csl==stail->next)
        break;

      if (isLabelDefinition(csl->line, &labelStart, &labelLength))
        {
          /* found a source line label; look for it in the replacment lines */
          crl = rhead;
          while (1)
            {
              while (crl!=rtail->next && crl->isComment)
                crl = crl->next;
              if (crl==rtail->next)
                break;
              if (matchLine(csl->line, crl->line, NULL))
                {
                  reassociate_ic_down(csl,stail,crl,rtail);
                  break;
                }
              else
                crl = crl->next;
            }
        }
      csl = csl->next;
    }
  
  /* Try to assign a meaningful iCode to any comment that is missing
     one. Since they are comments, it's ok to make mistakes; we are just
     trying to improve continuity to simplify other tests.
  */
  ic = NULL;
  for (crl=rtail;crl!=rhead->prev;crl=crl->prev)
    {
      if (!crl->ic && ic && crl->isComment)
        crl->ic = ic;
      ic = crl->ic;
    }
}

                  
/*-----------------------------------------------------------------*/
/* replaceRule - does replacement of a matching pattern            */
/*-----------------------------------------------------------------*/
static void 
replaceRule (lineNode ** shead, lineNode * stail, peepRule * pr)
{
  lineNode *cl = NULL;
  lineNode *pl = NULL, *lhead = NULL;
  /* a long function name and long variable name can evaluate to
     4x max pattern length e.g. "mov dptr,((fie_var>>8)<<8)+fie_var" */
  char lb[MAX_PATTERN_LEN*4];
  char *lbp;
  lineNode *comment = NULL;

  /* collect all the comment lines in the source */
  for (cl = *shead; cl != stail; cl = cl->next)
    {
      if (cl->line && (*cl->line == ';' || cl->isDebug))
	{
	  pl = (pl ? connectLine (pl, newLineNode (cl->line)) :
		(comment = newLineNode (cl->line)));
	  pl->isDebug = cl->isDebug;
	  pl->isComment = cl->isComment || (*cl->line == ';');
	}
    }
  cl = NULL;

  /* for all the lines in the replacement pattern do */
  for (pl = pr->replace; pl; pl = pl->next)
    {
      char *v;
      char *l;
      lbp = lb;

      l = pl->line;

      while (*l)
	{
	  /* if the line contains a variable */
	  if (*l == '%' && isdigit (*(l + 1)))
	    {
	      v = hTabItemWithKey (pr->vars, keyForVar (l + 1));
	      if (!v)
		{
		  fprintf (stderr, "used unbound variable in replacement\n");
		  l++;
		  continue;
		}
	      while (*v) {
		*lbp++ = *v++;
	      }
	      l++;
	      while (isdigit (*l)) {
		l++;
	      }
	      continue;
	    }
	  *lbp++ = *l++;
	}

      *lbp = '\0';
      if (cl)
	cl = connectLine (cl, newLineNode (lb));
      else
	lhead = cl = newLineNode (lb);
      cl->isComment = pl->isComment;
    }

  /* add the comments if any to the head of list */
  if (comment)
    {
      lineNode *lc = comment;
      while (lc->next)
	lc = lc->next;
      lc->next = lhead;
      if (lhead)
	lhead->prev = lc;
      lhead = comment;
    }

  /* determine which iCodes the replacment lines relate to */
  reassociate_ic(*shead,stail,lhead,cl);

  /* now we need to connect / replace the original chain */
  /* if there is a prev then change it */
  if ((*shead)->prev)
    {
      (*shead)->prev->next = lhead;
      lhead->prev = (*shead)->prev;
    }
  *shead = lhead;
  /* now for the tail */
  if (stail && stail->next)
    {
      stail->next->prev = cl;
      if (cl)
	cl->next = stail->next;
    }
}

/* Returns TRUE if this line is a label definition.

 * If so, start will point to the start of the label name,
 * and len will be it's length.
 */
bool 
isLabelDefinition (const char *line, const char **start, int *len)
{
  const char *cp = line;

  /* This line is a label if if consists of:
   * [optional whitespace] followed by identifier chars
   * (alnum | $ | _ ) followed by a colon.
   */

  while (*cp && isspace (*cp))
    {
      cp++;
    }

  if (!*cp)
    {
      return FALSE;
    }

  *start = cp;

  while (isalnum (*cp) || (*cp == '$') || (*cp == '_'))
    {
      cp++;
    }

  if ((cp == *start) || (*cp != ':'))
    {
      return FALSE;
    }

  *len = (cp - (*start));
  return TRUE;
}

/* Quick & dirty string hash function. */
static int 
hashSymbolName (const char *name)
{
  int hash = 0;

  while (*name)
    {
      hash = (hash << 6) ^ *name;
      name++;
    }

  if (hash < 0)
    {
      hash = -hash;
    }

  return hash % HTAB_SIZE;
}

/* Build a hash of all labels in the passed set of lines
 * and how many times they are referenced.
 */
static void 
buildLabelRefCountHash (lineNode * head)
{
  lineNode *line;
  const char *label;
  int labelLen;
  int i;

  assert (labelHash == NULL);
  labelHash = newHashTable (HTAB_SIZE);

  /* First pass: locate all the labels. */
  line = head;

  while (line)
    {
      if (isLabelDefinition (line->line, &label, &labelLen)
	  && labelLen <= SDCC_NAME_MAX)
	{
	  labelHashEntry *entry;

	  entry = traceAlloc (&_G.labels, Safe_alloc(sizeof (labelHashEntry)));

	  memcpy (entry->name, label, labelLen);
	  entry->name[labelLen] = 0;
	  entry->refCount = -1;

	  hTabAddItem (&labelHash, hashSymbolName (entry->name), entry);
	}
      line = line->next;
    }


  /* Second pass: for each line, note all the referenced labels. */
  /* This is ugly, O(N^2) stuff. Optimizations welcome... */
  line = head;
  while (line)
    {
      for (i = 0; i < HTAB_SIZE; i++)
	{
	  labelHashEntry *thisEntry;

	  thisEntry = hTabFirstItemWK (labelHash, i);

	  while (thisEntry)
	    {
	      if (strstr (line->line, thisEntry->name))
		{
		  thisEntry->refCount++;
		}
	      thisEntry = hTabNextItemWK (labelHash);
	    }
	}
      line = line->next;
    }

#if 0
  /* Spew the contents of the table. Debugging fun only. */
  for (i = 0; i < HTAB_SIZE; i++)
    {
      labelHashEntry *thisEntry;

      thisEntry = hTabFirstItemWK (labelHash, i);

      while (thisEntry)
	{
	  fprintf (stderr, "label: %s ref %d\n",
		   thisEntry->name, thisEntry->refCount);
	  thisEntry = hTabNextItemWK (labelHash);
	}
    }
#endif
}

/* How does this work?
   peepHole
    For each rule,
     For each line,
      Try to match
      If it matches,
       replace and restart.

    matchRule
     matchLine

  Where is stuff allocated?
  
*/

/*-----------------------------------------------------------------*/
/* peepHole - matches & substitutes rules                          */
/*-----------------------------------------------------------------*/
void 
peepHole (lineNode ** pls)
{
  lineNode *spl;
  peepRule *pr;
  lineNode *mtail = NULL;
  bool restart;

#if !OPT_DISABLE_PIC || !OPT_DISABLE_PIC16
  /* The PIC port uses a different peep hole optimizer based on "pCode" */
  if (TARGET_IS_PIC || TARGET_IS_PIC16)
    return;
#endif

  assert(labelHash == NULL);

  do
    {
      restart = FALSE;

      /* for all rules */
      for (pr = rootRules; pr; pr = pr->next)
        {
          for (spl = *pls; spl; spl = spl->next)
            {
              /* if inline assembler then no peep hole */
              if (spl->isInline)
                continue;

              /* don't waste time starting a match on debug symbol
              ** or comment */
              if (spl->isDebug || spl->isComment || *(spl->line)==';')
                continue;
              
              mtail = NULL;

              /* Tidy up any data stored in the hTab */
              
              /* if it matches */
              if (matchRule (spl, &mtail, pr, *pls))
                {
                  
                  /* then replace */
                  if (spl == *pls)
                    replaceRule (pls, mtail, pr);
                  else
                    replaceRule (&spl, mtail, pr);
                  
                  /* if restart rule type then
                     start at the top again */
                  if (pr->restart)
                    {
                      restart = TRUE;
                    }
                }
              
              if (pr->vars)
                {
                  hTabDeleteAll (pr->vars);
                  Safe_free (pr->vars);
                  pr->vars = NULL;
                }
              
              freeTrace (&_G.values);
            }
        }
    } while (restart == TRUE);

  if (labelHash)
    {
      hTabDeleteAll (labelHash);
      freeTrace (&_G.labels);
    }
  labelHash = NULL;
}


/*-----------------------------------------------------------------*/
/* readFileIntoBuffer - reads a file into a string buffer          */
/*-----------------------------------------------------------------*/
static char *
readFileIntoBuffer (char *fname)
{
  FILE *f;
  char *rs = NULL;
  int nch = 0;
  int ch;
  char lb[MAX_PATTERN_LEN];

  if (!(f = fopen (fname, "r")))
    {
      fprintf (stderr, "cannot open peep rule file\n");
      return NULL;
    }

  while ((ch = fgetc (f)) != EOF)
    {
      lb[nch++] = ch;

      /* if we maxed out our local buffer */
      if (nch >= (MAX_PATTERN_LEN - 2))
	{
	  lb[nch] = '\0';
	  /* copy it into allocated buffer */
	  if (rs)
	    {
	      rs = Safe_realloc (rs, strlen (rs) + strlen (lb) + 1);
	      strncatz (rs, lb,  strlen (rs) + strlen (lb) + 1);
	    }
	  else
	    {
	      rs = Safe_strdup (lb);
	    }
	  nch = 0;
	}
    }

  /* if some charaters left over */
  if (nch)
    {
      lb[nch] = '\0';
      /* copy it into allocated buffer */
      if (rs)
	{
	  rs = Safe_realloc (rs, strlen (rs) + strlen (lb) + 1);
	  strncatz (rs, lb, strlen (rs) + strlen (lb) + 1);
	}
      else
	{
	  rs = Safe_strdup (lb);
	}
    }
  return rs;
}

/*-----------------------------------------------------------------*/
/* initPeepHole - initialises the peep hole optimizer stuff        */
/*-----------------------------------------------------------------*/
void 
initPeepHole ()
{
  char *s;

  /* read in the default rules */
  readRules (port->peep.default_rules);

  /* if we have any additional file read it too */
  if (options.peep_file)
    {
      readRules (s = readFileIntoBuffer (options.peep_file));
      setToNull ((void *) &s);
    }


#if !OPT_DISABLE_PIC
  /* Convert the peep rules into pcode.
     NOTE: this is only support in the PIC port (at the moment)
  */
	if (TARGET_IS_PIC)
		peepRules2pCode(rootRules);
#endif

#if !OPT_DISABLE_PIC16
  /* Convert the peep rules into pcode.
     NOTE: this is only support in the PIC port (at the moment)
       and the PIC16 port (VR 030601)
  */
	if (TARGET_IS_PIC16)
		pic16_peepRules2pCode(rootRules);

#endif

}
