#define VERSION "1.86"

/*
 *  units, a program for units conversion
 *  Copyright (C) 1996, 1997, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006
 *  Free Software Foundation, Inc
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 *  Boston, MA 02110-1301 USA
 *     
 *  This program was written by Adrian Mariano (adrian@cam.cornell.edu)
 */

#include<stdio.h>
#include<signal.h>

#ifdef READLINE
#  include <readline/readline.h>
#  define RVERSTR "with readline"
#else
#  define RVERSTR "without readline"
#endif

#include "getopt.h"
#include "units.h"

#ifndef UNITSFILE
#  define UNITSFILE "units.dat"
#endif

#ifndef EOFCHAR
#  define EOFCHAR "D"
#endif

#define PRIMITIVECHAR '!'	/* Character that marks irreducible units */
#define COMMENTCHAR '#'         /* Comments marked by this character */
#define COMMANDCHAR '!'         /* Unit database commands marked with this */
#define HELPCOMMAND "help"      /* Command to request help at prompt */
#define UNITMATCH "?"           /* Command to request conformable units */
#define DEFAULTPAGER "more"     /* Default pager program */
#define DEFAULTLOCALE "en_US"   /* Default locale */
#define MAXINCLUDE 5            /* Max depth of include files */
#define MAXFILES 25             /* Max number of units files on command line */
#define NODIM "!dimensionless"  /* Marks dimensionless primitive units, such */
				/* as the radian, which are ignored when */
                                /* doing unit comparisons. */

char *pager;                    /* Actual pager (from PAGER environment var) */
char *mylocale;                 /* Locale in effect (from LOCALE env var) */
char *numformat = "%.8g";	/* printf format for numeric output */
char *powerstring = "^";	/* Exponent character used in output */
int quiet = 0;                  /* Flag for supressing prompting (-q option) */
int unitcheck = 0;              /* Flag for unit checking, set to 1 for 
                                   regular check, set to 2 for verbose check */
int verbose = 1;                /* Flag for output verbosity */
int strictconvert = 0;          /* Strict conversion (disables reciprocals) */
int minusminus = 1;             /* Should '-' character give subtraction */
int oneline = 0;                /* Suppresses the second line of output */
char *unitsfiles[MAXFILES+1];   /* Null terminated list of units file names */
char *progname="units";         /* Used in error messages */
char *queryhave = "You have: "; /* Prompt text for units to convert from */
char *querywant = "You want: "; /* Prompt text for units to convert to */
char *deftext="\tDefinition: "; /* Output text when printing definition */

#define  HASHSIZE 101           /* Straight from K&R */
#define  HASHNUMBER 31

#define  PREFIXTABSIZE 128
#define  prefixhash(str) (*(str) & 127)    /* "hash" value for prefixes */

char *errormsg[]={"Successful completion", 
                  "Parse error",           
                  "Product overflow",      
                  "Unit reduction error (bad unit definition)",
                  "Illegal sum or difference of non-conformable units",
                  "Unit not dimensionless",
		  "Unit not a root",
		  "Unknown unit",
		  "Bad argument",
		  "Weird nonlinear unit type (bug in program)",
		  "Function argument has wrong dimension",
		  "Argument of table outside domain",
		  "Nonlinear unit definition has unit error",
		  "No inverse defined",
		  "Parser memory overflow (recursive function definition?)",
		  "Argument wrong dimension or bad nonlinear unit definition",
                  "Unable to open units file",
		  "Units file contains errors",
		  "Memory allocation error"
                  };

char *irreducible=0;            /* Name of last irreducible unit */


/* Hash table for unit definitions. */

struct unitlist {
   char *name;			/* unit name */
   char *value;			/* unit value */
   int linenumber;              /* line in units data file where defined */
   char *file;                  /* file where defined */ 
   struct unitlist *next;	/* next item in list */
} *utab[HASHSIZE];


/* Table for prefix definitions. */

struct prefixlist {
   int len;			/* length of name string */
   char *name;			/* prefix name */
   char *value;			/* prefix value */
   int linenumber;              /* line in units data file where defined */
   char *file;                  /* file where defined */ 
   struct prefixlist *last;	/* last item in list--only set in first item */
   struct prefixlist *next;   	/* next item in list */
} *ptab[PREFIXTABSIZE];


/* Functions are stored in a linked list */

struct func *firstfunc = 0;    /* Base of linked list of functions */
struct func *lastfunc = 0;     /* Last entry in linked list of functions */

/* 
   Used for passing parameters to the parser when we are in the process
   of parsing a unit function.  If function_parameter is non-nil, then 
   whenever the text in function_parameter appears in a unit expression
   it is replaced by the unit value stored in parameter_value.
*/

char *function_parameter = 0; 
struct unittype *parameter_value = 0;

char *NULLUNIT = "";  /* Used for units that are canceled during reduction */

/* Increases the buffer by BUFGROW bytes and leaves the new pointer in buf
   and the new buffer size in bufsize. */

#define BUFGROW 10

void
growbuffer(char **buf, int *bufsize)
{
  int usemalloc;

  usemalloc = !*buf || !*bufsize;
  *bufsize += BUFGROW;
  if (usemalloc)
    *buf = malloc(*bufsize);
  else
    *buf = realloc(*buf,*bufsize);
  if (!*buf){
    fprintf(stderr, "%s: memory allocation error (growbuffer)\n",progname);  
    exit(3); 
  }
}

/* 
   Fetch a line of data with backslash for continuation.  The
   parameter count is incremented to report the number of newlines
   that are read so that line numbers can be accurately reported. 
*/

char *
fgetscont(char *buf, int size, FILE *file, int *count)
{
  if (!fgets(buf,size,file))
    return 0;
  (*count)++;
  while(strlen(buf)>=2 && 0==strcmp(buf+strlen(buf)-2,"\\\n")){
    (*count)++;
    buf[strlen(buf)-2] = 0; /* delete trailing \n and \ char */
    if (strlen(buf)>=size-1) /* return if the buffer is full */
      return buf;
    if (!fgets(buf+strlen(buf), size - strlen(buf), file))
      return buf;  /* already read some data so return success */
  }
  if (buf[strlen(buf)-1] == '\\') {   /* If last char of buffer is \ then   */
    ungetc('\\', file);               /* we don't know if it is followed by */
    buf[strlen(buf)-1] = 0;           /* a \n, so put it back and try again */
  }
  return buf;
}


/* 
   Gets arbitrarily long input data into a buffer using growbuffer().
   Returns 0 if no data is read.  Increments count by the number of
   newlines read unless it points to NULL. 
*/

char *
fgetslong(char **buf, int *bufsize, FILE *file, int *count)
{
  int dummy;
  if (!count)
    count = &dummy;
  if (!*bufsize) growbuffer(buf,bufsize);
  if (!fgetscont(*buf, *bufsize, file, count))
    return 0;
  while ((*buf)[strlen(*buf)-1] != '\n' && !feof(file)){
    growbuffer(buf, bufsize);
    fgetscont(*buf+strlen(*buf), *bufsize-strlen(*buf), file, count);
    (*count)--;
  }  
  return *buf;
}

/* Allocates memory and aborts if malloc fails. */

void *
mymalloc(int bytes,char *mesg)
{
   void *pointer;

   pointer = malloc(bytes);
   if (!pointer){
     fprintf(stderr, "%s: memory allocation error %s\n", progname,mesg);
     exit(3);
   }
   return pointer;
}


/* Duplicates a string */

char *
dupstr(char *str)
{
   char *ret;

   ret = mymalloc(strlen(str) + 1,"(dupstr)");
   strcpy(ret, str);
   return (ret);
}


/* hashing algorithm for units */

unsigned
uhash(const char *str)
{
   unsigned hashval;

   for (hashval = 0; *str; str++)
      hashval = *str + HASHNUMBER * hashval;
   return (hashval % HASHSIZE);
}


/* Lookup a unit in the units table.  Returns the definition, or NULL
   if the unit isn't found in the table. */

struct unitlist *
ulookup(const char *str)
{
   struct unitlist *uptr;

   for (uptr = utab[uhash(str)]; uptr; uptr = uptr->next)
      if (strcmp(str, uptr->name) == 0)
	 return uptr;
   return NULL;
}

/* Lookup a prefix in the prefix table.  Finds the first prefix that
   matches the beginning of the input string.  Returns NULL if no
   prefixes match. */

struct prefixlist *
plookup(const char *str)
{
   struct prefixlist *prefix;

   for (prefix = ptab[prefixhash(str)]; prefix; prefix = prefix->next) {
      if (!strncmp(str, prefix->name, prefix->len))
	 return prefix;
   }
   return NULL;
}

/* Look up function in the function linked list */

struct func *
fnlookup(const char *str, int length)
{ 
  struct func *funcptr;

  for(funcptr=firstfunc;funcptr;funcptr = funcptr->next)
    if (length==strlen(funcptr->name) && 
	0==strncmp(funcptr->name,str,length))
      return funcptr;
  return 0;
}

/* Insert a new function into the linked list of functions */

void
addfunction(struct func *newfunc)
{
  if (!lastfunc){
    firstfunc = newfunc;
    lastfunc = firstfunc;
  } else {
    lastfunc->next = newfunc;
    lastfunc = newfunc;
  }
  newfunc->next = 0;
}

/* Remove leading and trailing white space from the input */

char *
removepadding(char *in)
{
  char *endptr;

  in += strspn(in,WHITE);
  for(endptr = in + strlen(in) - 1;*in && strchr(WHITE,*endptr);endptr--)
    *endptr=0;
  return in;
}


/* 
   Checks whether the input string is a function name, possibly
   surrounded by white space.  Returns the function structure if one
   is found, or null otherwise.
*/

struct func *
isfunction(char *str)
{
  str = removepadding(str);
  return fnlookup(str,strlen(str));
}

/* Print out error message encountered while reading the units file. */

void
readerror(FILE *errfile, int linenum, const char *filename)
{
  if (errfile)
    fprintf(errfile, "%s: error in units file '%s' line %d\n",
	    progname, filename, linenum);
}


/* 
   Read in units data.  

   file - Filename to load
   errfile - File to receive messages about errors in the units database.  
             Set it to 0 to suppress errors. 
   unitcount, prefixcount, funccount - Return statistics to the caller.  
                                       Must initialize to zero before calling.
   depth - Used to prevent recursive includes.  Call with it set to zero.


   The global variable progname is used in error messages.  
*/

int
readunits(char *file, FILE *errfile, 
          int *unitcount, int *prefixcount, int *funccount, int depth)
{
   struct prefixlist *pfxptr;
   struct unitlist *uptr;
   FILE *unitfile;
   char *line, *lineptr, *unitdef, *unitname, *permfile;
   int len, linenum, linebufsize, goterr;
   unsigned hashval, pval;
   int locunitcount, locprefixcount, locfunccount;
   struct func *funcentry;
   int wronglocale = 0;   /* If set then we are currently reading data */
   int inlocale = 0;      /* for the wrong locale so we should skip it */
   locunitcount = 0;
   locprefixcount = 0;
   locfunccount  = 0;
   linenum = 0;
   linebufsize = 0;
   goterr = 0;

   growbuffer(&line,&linebufsize);

   permfile = dupstr(file);                 /* This is a permanent copy to 
                                               reference in the database.
                                               It is never freed. */
   unitfile = fopen(file, "rt");
   if (!unitfile) 
     return E_FILE;
   while (!feof(unitfile)) {
      if (!fgetslong(&line, &linebufsize, unitfile, &linenum)) 
        break;
      if (*line == COMMANDCHAR) {         /* Process units.dat commands    */
        unitname = strtok(line+1, WHITE);
	if (!strcmp(unitname,"locale")){ 
	  unitname = strtok(0, WHITE); 
	  if (!*unitname) {
	    if (errfile)
	      fprintf(errfile, 
		      "%s: no locale specified on line %d of '%s'\n",
		      progname, linenum, file);
	    goterr=1;
	  } else if (inlocale){
	    if (errfile)
	      fprintf(errfile,
		      "%s: nested locales not allowed, line %d of '%s'\n",
		      progname, linenum, file);
	    goterr=1;
	  } else {
	    inlocale = 1;
	    if (strcmp(unitname,mylocale))  /* locales don't match           */
	      wronglocale = 1;
	  }
	  continue;
	} 
	else if (!strcmp(unitname, "endlocale")){
	  if (!inlocale){
	    if (errfile)
	      fprintf(errfile, 
		      "%s: unmatched !endlocale on line %d of '%s'\n",
		      progname, linenum, file);
	    goterr=1;
	  }
	  wronglocale = 0;
	  inlocale = 0;
	  continue;
	}
	if (wronglocale)
	  continue;
        if (!strcmp(unitname, "include")){
          if (depth>MAXINCLUDE){
	    if (errfile)
	      fprintf(errfile, 
		      "%s: max include depth of %d exceeded in file '%s' line %d\n",
		      progname, MAXINCLUDE, file, linenum);
	    goterr=1;
	  } else {
	    int readerr;
	    char *includefile;
	    unitname = strtok(0, WHITE); 
	    includefile = mymalloc(strlen(file)+strlen(unitname)+1, "(readunits)");
            if (strchr(unitname, '/') || strchr(unitname, '\\'))
	      strcpy(includefile,unitname);
	    else {
              char *pathend;
	      strcpy(includefile, file);
	      pathend = includefile + strlen(includefile) - 1;
	      while(pathend != includefile && !strchr("/\\", *pathend))
		pathend--;
	      if (strchr("/\\", *pathend))
		pathend++;
	      strcpy(pathend, unitname);
	    }
	    readerr = readunits(includefile, errfile, unitcount, prefixcount, 
				funccount, depth+1);
	    if (readerr == E_MEMORY) 
	      return readerr;
	    if (readerr == E_FILE) {
	      if (errfile)
		fprintf(errfile, "%s: unable to open included file '%s' at line %d of file '%s\n", progname, includefile, linenum, file);
	    }
	    
	    if (readerr)
	      goterr = 1;
	    free(includefile);
	  }
	} else {                             /* not a valid command */
	  readerror(errfile,linenum,file);
	  goterr=1;
	}
	continue;
      }	
      if (wronglocale)
	continue;
      if (lineptr = strchr(line,COMMENTCHAR))
         *lineptr = 0;
      unitname = strtok(line, WHITE);
      if (!unitname || !*unitname) 
	continue;
      unitdef = strtok(NULL, "\n");
      if (!unitdef){
        readerror(errfile,linenum,file);
	goterr=1;
        continue;
      }
      unitdef = removepadding(unitdef);
      if (!*unitdef){ 
        readerror(errfile,linenum,file);
	goterr=1;
        continue;
      }
      
      len = strlen(unitname);      

      if (unitname[len - 1] == '-') {	/* it's a prefix definition */
         unitname[len - 1] = 0;
	 if (strchr("0123456789.", unitname[0])){
	   if (errfile)
	     fprintf(errfile,
	     "%s: unit '%s' on line %d of '%s' ignored.  It starts with a digit\n", 
	     progname, unitname, linenum, file);
  	     goterr=1;
	     continue;
	 }
	 if (pfxptr = plookup(unitname)) {  /* already there: redefinition */
 	    goterr=1;
            if (errfile)
	      if (!strcmp(pfxptr->name, unitname))
		fprintf(errfile,
   	        "%s: redefinition of prefix '%s-' on line %d of '%s' ignored.\n",
		       progname, unitname, linenum, file);
	      else
	         fprintf(errfile, "%s: prefix '%s-' on line %d of '%s' is hidden by earlier definition of '%s-'.\n",
		       progname, unitname, linenum, file, pfxptr->name);
	    continue;
	 } 

         /* Make new prefix table entry */
         
         pfxptr = (struct prefixlist *) mymalloc(sizeof(*pfxptr),"(readunits)");
	 pfxptr->name = dupstr(unitname);
	 pfxptr->len = len - 1;
	 pfxptr->value = dupstr(unitdef);
         pfxptr->linenumber = linenum;
	 pfxptr->file = permfile;
	 /*
	    Install prefix name/len/value in list
	    Order is FIFO, so a prefix that is a substring of another
	    prefix must follow the longer prefix in the units file
	    (e.g, 'k' must come after 'kilo') or it will not be found
	    by plookup().
	  */

	 pfxptr->next = NULL;
	 pval = prefixhash(pfxptr->name);
	 if (ptab[pval] == NULL)
	    ptab[pval] = pfxptr;
	 else
	    ptab[pval]->last->next = pfxptr;
	 ptab[pval]->last = pfxptr;
	 locprefixcount++;
      } else if (strchr(unitname,'[')){ /* table definition  */
	char *start, *end;
	int tablealloc, tabpt;
        struct pair *tab;
	int tableerr;

	tableerr=0;
	start  = strchr(unitname,'[');
	end = strchr(unitname,']');
	*start++=0;
	if (strchr("0123456789.", unitname[0])){
	  if (errfile)
	    fprintf(errfile,
            "%s: unit '%s' on line %d ignored.  It starts with a digit\n", 
		     progname, unitname, linenum);
	  goterr=1;
	  continue;
	}
	if (!end || strlen(end)>1){
	  if (errfile)
 	    fprintf(errfile,"%s: missing ']' in units file '%s' line %d\n",
		    progname,file,linenum);
	  goterr=1;
	  continue;
	} 
        if (fnlookup(unitname,strlen(unitname))){
	  if (errfile)
	    fprintf(errfile,
		  "%s: redefinition of unit '%s' on line %d of file '%s' ignored\n",
		  progname, unitname, linenum, file);
	  goterr=1;
	  continue;
	}
	*end=0;
	funcentry = (struct func *)mymalloc(sizeof(struct func),"(readunits)");
	funcentry->name = dupstr(unitname);
	funcentry->tableunit = dupstr(start);
        tab = (struct pair *)mymalloc(sizeof(struct pair)*20, "(readunits)");
        tablealloc=20;
        tabpt = 0;
	start = unitdef;
	while (1) {
	  if (tabpt>=tablealloc){
	    tablealloc+=20;
	    tab = (struct pair *)realloc(tab,sizeof(struct pair)*tablealloc);
	    if (!tab){
	      if (errfile)
	        fprintf(errfile, "%s: memory allocation error (readunits)\n",
		        progname);  
	      return E_MEMORY;
	    }
	  }
	  tab[tabpt].location = strtod(start,&end);
	  if (start==end)
	    break;
	  if (tabpt>0 && tab[tabpt].location<=tab[tabpt-1].location){
	    if (errfile)
  	      fprintf(errfile,"%s: points don't increase (%.8g to %.8g) in units file '%s' line %d\n",
		    progname, tab[tabpt-1].location, tab[tabpt].location,
		    file, linenum);
	    tableerr=1;
	    break;
	  }
	  start=end+strspn(end," \t");
	  tab[tabpt].value = strtod(start,&end);
	  if (start==end){
	    if (errfile)
	      fprintf(errfile,"%s: missing value after %.8g in units file '%s' line %d\n",
		    progname, tab[tabpt].location, file, linenum);
	    tableerr=1;
	    break;
	  }
	  tabpt++;
	  start=end+strspn(end," \t,");
	}
	if (tableerr){
	  free(tab);
	  free(funcentry->name);
	  free(funcentry->tableunit);
	  free(funcentry);
	  goterr=1;
	} else {
	  funcentry->tablelen = tabpt;
	  funcentry->table = tab;
          funcentry->linenumber = linenum;
	  funcentry->file = permfile;
	  locfunccount++;
	  addfunction(funcentry);
	}
      } else if (strchr(unitname,'(')){ /* function definition */
         char *start, *end, *inv;

         start = strchr(unitname,'(');
         end = strchr(unitname,')');
         *start++ = 0;

	 if (strchr("0123456789.", unitname[0])){
	   if (errfile)
	     fprintf(errfile,
	     "%s: unit '%s' on line %d of '%s' ignored.  It starts with a digit\n", 
		   progname, unitname, linenum, file);
	   goterr=1;
	   continue;
	 }

         if (!end || strlen(end)>1){
	   if (errfile)
	     fprintf(errfile,
		   "%s: bad function definition of '%s' in '%s' line %d\n",
		   progname,unitname,file,linenum);
	   goterr=1;
	   continue;
	 }
	 if (fnlookup(unitname,strlen(unitname))){
	   if (errfile)
	     fprintf(errfile,
		   "%s: redefinition of unit '%s' on line %d of '%s' ignored\n",
		   progname, unitname, linenum, file);
	   goterr=1;
	   continue;
	 }
 	 funcentry = (struct func*)mymalloc(sizeof(struct func),"(readunits)");
         *end=0;
	 funcentry->forward.dimen = 0;
	 funcentry->inverse.dimen = 0;
         if (*unitdef=='['){  /* found dimension spec [input;inverse input] */
           unitdef++;
	   inv = strchr(unitdef,';');
	   end = strchr(unitdef,']');
           if (inv)
	     *inv++=0;
	   if (!end || (inv && (end-inv<0))){
	     free(funcentry);
	     if (errfile)
	       fprintf(errfile,
   	         "%s: expecting ']' in definition of '%s' in '%s' line %d\n",
		 progname, unitname, file, linenum);
	     goterr=1;
	     continue;
	   }
	   *end=0;
	   unitdef = removepadding(unitdef);
	   funcentry->forward.dimen=dupstr(unitdef);
	   if (inv){
	     inv = removepadding(inv);
	     funcentry->inverse.dimen = dupstr(inv);
	   }
	   unitdef = end+1;
	 }
         inv = strchr(unitdef,';');
         if (inv)
           *inv++ = 0;
         funcentry->name = dupstr(unitname);
         funcentry->forward.param = dupstr(start);
         funcentry->table = 0;
         funcentry->forward.def = dupstr(removepadding(unitdef));
	 if (inv){
	   funcentry->inverse.def = dupstr(removepadding(inv));
	   funcentry->inverse.param = dupstr(unitname);
         } 
	 else 
	   funcentry->inverse.def = 0;
         locfunccount++;
	 funcentry->linenumber = linenum;
	 funcentry->file = permfile;
	 addfunction(funcentry);
      } else {	/* it is a unit definition */

  	 /* Units that end in [2-9] can never be accessed */

 	 if (strchr("23456789", unitname[strlen(unitname)-1])){
	   if (errfile)
	     fprintf(errfile,
             "%s: unit '%s' on line %d of '%s' ignored.  It ends with a nonzero digit\n",
             progname, unitname, linenum, file);
   	   goterr=1;
	   continue;
	 }

	 if (strchr("0123456789.", unitname[0])){
	   if (errfile)
	     fprintf(errfile,
		     "%s: unit '%s' on line %d of '%s' ignored.  It starts with a digit\n", 
		     progname, unitname, linenum, file);
	   goterr=1;
	   continue;
	 }

         /* Is it a redefinition? */

	 if (ulookup(unitname)) {
	   if (errfile)
	     fprintf(errfile,
		    "%s: redefinition of unit '%s' on line %d of '%s' ignored\n",
		    progname, unitname, linenum, file);
	   goterr=1;
	   continue;
	 }

         /* make new units table entry */

         uptr = (struct unitlist *) mymalloc(sizeof(*uptr),"(readunits)");
	 uptr->name = dupstr(unitname);
	 uptr->value = dupstr(unitdef);
         uptr->linenumber = linenum;
	 uptr->file = permfile;

	 /* install unit name/value pair in list */

	 hashval = uhash(uptr->name);
	 uptr->next = utab[hashval];
	 utab[hashval] = uptr;
	 locunitcount++;
      }
   }
   fclose(unitfile);
   free(line);
   if (unitcount)
     *unitcount+=locunitcount;
   if (prefixcount)
     *prefixcount+=locprefixcount;
   if (funccount)
     *funccount+=locfunccount;
   if (goterr)
     return E_BADFILE;
   else return 0;
}

/* Initialize a unit to be equal to 1. */

void
initializeunit(struct unittype *theunit)
{
   theunit->factor = 1.0;
   theunit->numerator[0] = theunit->denominator[0] = NULL;
}


/* Free a unit: frees all the strings used in the unit structure.
   Does not free the unit structure itself.  */

void
freeunit(struct unittype *theunit)
{
   char **ptr;

   for(ptr = theunit->numerator; *ptr; ptr++)
     if (*ptr != NULLUNIT) free(*ptr);
   for(ptr = theunit->denominator; *ptr; ptr++)
     if (*ptr != NULLUNIT) free(*ptr);

   /* protect against repeated calls to freeunit() */

   theunit->numerator[0] = 0;  
   theunit->denominator[0] = 0;
}



/* Print out a unit  */

void
showunit(struct unittype *theunit)
{
   char **ptr;
   int printedslash;
   int counter = 1;

   printf(numformat, theunit->factor);

   for (ptr = theunit->numerator; *ptr; ptr++) {
      if (ptr > theunit->numerator && **ptr &&
	  !strcmp(*ptr, *(ptr - 1)))
	 counter++;
      else {
	 if (counter > 1)
	    printf("%s%d", powerstring, counter);
	 if (**ptr)
	    printf(" %s", *ptr);
	 counter = 1;
      }
   }
   if (counter > 1)
      printf("%s%d", powerstring, counter);
   counter = 1;
   printedslash = 0;
   for (ptr = theunit->denominator; *ptr; ptr++) {
      if (ptr > theunit->denominator && **ptr &&
	  !strcmp(*ptr, *(ptr - 1)))
	 counter++;
      else {
	 if (counter > 1)
	    printf("%s%d", powerstring, counter);
	 if (**ptr) {
	    if (!printedslash)
	       printf(" /");
	    printedslash = 1;
	    printf(" %s", *ptr);
	 }
	 counter = 1;
      }
   }
   if (counter > 1)
      printf("%s%d", powerstring, counter);
}


/* qsort comparison function */

int
compare(const void *item1, const void *item2)
{
   return strcmp(*(char **) item1, *(char **) item2);
}

/* Sort numerator and denominator of a unit so we can compare different
   units */

void
sortunit(struct unittype *theunit)
{
   char **ptr;
   int count;

   for (count = 0, ptr = theunit->numerator; *ptr; ptr++, count++);
   qsort(theunit->numerator, count, sizeof(char *), compare);
   for (count = 0, ptr = theunit->denominator; *ptr; ptr++, count++);
   qsort(theunit->denominator, count, sizeof(char *), compare);
}


/* Cancels duplicate units that appear in the numerator and
   denominator.  The input unit must be sorted. */

void
cancelunit(struct unittype *theunit)
{
   char **den, **num;
   int comp;

   den = theunit->denominator;
   num = theunit->numerator;

   while (*num && *den) { 
      comp = strcmp(*den, *num);
      if (!comp) { /* units match, so cancel them */
         if (*den!=NULLUNIT) free(*den);
         if (*num!=NULLUNIT) free(*num);  
	 *den++ = NULLUNIT;
	 *num++ = NULLUNIT;
      } else if (comp < 0) /* Move up whichever pointer is alphabetically */
	 den++;            /* behind to look for future matches */
      else
	 num++;
   }
}


/*
   Looks up the definition for the specified unit including prefix processing
   and plural removal.

   Returns a pointer to the definition or a null pointer
   if the specified unit does not appear in the units table.

   Sometimes the returned pointer will be a pointer to the special
   buffer created to hold the data.  This buffer grows as needed during 
   program execution.  

   Note that if you pass the output of lookupunit() back into the function
   again you will get correct results, but the data you passed in may get
   clobbered if it happened to be the internal buffer.  
*/

static int bufsize=0;
static char *buffer;  /* buffer for lookupunit answers with prefixes */


/* 
  Plural rules for english: add -s
  after x, sh, ch, ss   add -es
  -y becomes -ies except after a vowel when you just add -s as usual
*/
  

char *
lookupunit(char *unit,int prefixok)
{
   char *copy;
   struct prefixlist *pfxptr;
   struct unitlist *uptr;

   if (uptr = ulookup(unit))
      return uptr->value;

   if (strlen(unit)>2 && unit[strlen(unit) - 1] == 's') {
      copy = dupstr(unit);
      copy[strlen(copy) - 1] = 0;
      if (lookupunit(copy,prefixok)){
         while(strlen(copy)+1 > bufsize) {
            growbuffer(&buffer, &bufsize);
         }
         strcpy(buffer, copy);  /* Note: returning looked up result seems   */
	 free(copy);		/*   better but it causes problems when it  */
         return buffer;		/*   contains PRIMITIVECHAR.                */
      }
      if (strlen(copy)>2 && copy[strlen(copy) - 1] == 'e') {
	 copy[strlen(copy) - 1] = 0;
	 if (lookupunit(copy,prefixok)){
	    while (strlen(copy)+1 > bufsize) {
	       growbuffer(&buffer,&bufsize);
	    }
            strcpy(buffer,copy);
	    free(copy);
            return buffer;
	 }
      }
      if (strlen(copy)>2 && copy[strlen(copy) - 1] == 'i') {
	 copy[strlen(copy) - 1] = 'y';
	 if (lookupunit(copy,prefixok)){
	    while (strlen(copy)+1 > bufsize) {
	       growbuffer(&buffer,&bufsize);
	    }
            strcpy(buffer,copy);
	    free(copy);
            return buffer;
	 }
      }
      free(copy);
   }
   if (prefixok && (pfxptr = plookup(unit))) {
      copy=unit;
      copy += pfxptr->len;
      if (!strlen(copy) || lookupunit(copy,0)) {
         char *tempbuf;
         while (strlen(pfxptr->value)+strlen(copy)+2 > bufsize){
            growbuffer(&buffer, &bufsize);
         }
         tempbuf = dupstr(copy);   /* copy might point into buffer */
	 strcpy(buffer, pfxptr->value);
	 strcat(buffer, " ");
	 strcat(buffer, tempbuf);
         free(tempbuf);
	 return buffer;
      }
   }
   return 0;
}

/* 
   Returns 1 if the input consists entirely of whitespace characters
   and returns 0 otherwise. 
*/

int
isblankstr(char *str)
{
  while(*str) if (!strchr(WHITE,*str++)) return 0;
  return 1;
}


/* Points entries of product[] to the strings stored in tomove[].  
   Leaves tomove pointing to a list of NULLUNITS.  */

int
moveproduct(char *product[], char *tomove[])
{
   char **dest, **src;

   dest=product;
   for(src = tomove; *src; src++){
     if (*src == NULLUNIT) continue;
     for(; *dest && *dest != NULLUNIT; dest++);
     if (dest - product >= MAXSUBUNITS - 1) {
       return E_PRODOVERFLOW;
     }
     if (!*dest)
        *(dest + 1) = 0;
     *dest = *src;
     *src=NULLUNIT;
   }
   return 0;
}

/* 
   Make a copy of a product list.  Note that no error checking is done
   for overflowing the product list because it is assumed that the
   source list doesn't overflow, so the destination list shouldn't
   overflow either.  (This assumption could be false if the
   destination is not actually at the start of a product buffer.) 
*/

void
copyproduct(char **dest, char **source)
{
   for(;*source;source++,dest++) {
     if (*source==NULLUNIT)
       *dest = NULLUNIT;
     else
       *dest=dupstr(*source);
   }
   *dest=0;
}

/* Make a copy of a unit */ 

void
unitcopy(struct unittype *dest, struct unittype *source)
{
  dest->factor = source->factor;
  copyproduct(dest->numerator, source->numerator);
  copyproduct(dest->denominator, source->denominator);
}


/* Multiply left by right.  In the process, all of the units are
   deleted from right (but it is not freed) */

int 
multunit(struct unittype *left, struct unittype *right)
{
  int myerr;
  left->factor *= right->factor;
  myerr = moveproduct(left->numerator, right->numerator);
  if (!myerr)
    myerr = moveproduct(left->denominator, right->denominator);
  return myerr;
}

int 
divunit(struct unittype *left, struct unittype *right)
{
  int myerr;
  left->factor /= right->factor;
  myerr = moveproduct(left->numerator, right->denominator);
  if (!myerr)
    myerr = moveproduct(left->denominator, right->numerator);
  return myerr;
}


/*
   reduces a product of symbolic units to primitive units.
   The three low bits are used to return flags:

   bit 0 set if reductions were performed without error.
   bit 1 set if no reductions are performed.
   bit 2 set if an unknown unit is discovered.

   Return values from multiple calls will be ORed together later.
 */

#define DIDREDUCTION (1<<0)
#define NOREDUCTION  (1<<1)
#define ERROR        (1<<2)

int
reduceproduct(struct unittype *theunit, int flip)
{

   char *toadd;
   char **product;
   int didsomething = NOREDUCTION;
   struct unittype newunit;
   int ret;

   if (flip)
      product = theunit->denominator;
   else
      product = theunit->numerator;

   for (; *product; product++) {
      for (;;) {
	 if (!strlen(*product))
	    break;
	 toadd = lookupunit(*product,1);
	 if (!toadd) {
            if (!irreducible)
	      irreducible = dupstr(*product);
	    return ERROR;
         }
	 if (strchr(toadd, PRIMITIVECHAR))
	    break;
	 didsomething = DIDREDUCTION;
	 if (*product != NULLUNIT) {
	    free(*product);
	    *product = NULLUNIT;
	 }
         if (parseunit(&newunit, toadd, 0, 0))
	    return ERROR;
         if (flip) ret=divunit(theunit,&newunit);
         else ret=multunit(theunit,&newunit);
         freeunit(&newunit);
         if (ret) 
            return ERROR;
      }
   }
   return didsomething;
}


/*
   Reduces numerator and denominator of the specified unit.
   Returns 0 on success, or 1 on unknown unit error.
 */

int
reduceunit(struct unittype *theunit)
{
   int ret;

   if (irreducible)
     free(irreducible);
   irreducible=0;
   ret = DIDREDUCTION;

   /* Keep calling reduceprodut until it doesn't do anything */

   while (ret & DIDREDUCTION) {
      ret = reduceproduct(theunit, 0);
      if (!(ret & ERROR))
	ret |= reduceproduct(theunit, 1);
      if (ret & ERROR){
         if (irreducible) 
	   return E_UNKNOWNUNIT;
         else
	   return E_REDUCE;
      }
   }
   return 0;
}

/* 
   Returns one if the argument unit is defined in the data file as a   
  dimensionless unit.  This is determined by comparing its definition to
  the string NODIM.  
*/

int
ignore_dimless(char *name)
{
  struct unitlist *ul;
  if (!name) 
    return 0;
  ul = ulookup(name);
  if (ul && !strcmp(ul->value, NODIM))
    return 1;
  return 0;
}

int 
ignore_nothing(char *name)
{
  return 0;
}


int
ignore_primitive(char *name)
{
  struct unitlist *ul;
  if (!name) 
    return 0;
  ul = ulookup(name);
  if (ul && strchr(ul->value, PRIMITIVECHAR))
    return 1;
  return 0;
}


/* 
   Compare two product lists, return zero if they match and one if
   they do not match.  They may contain embedded NULLUNITs which are
   ignored in the comparison. Units defined as NODIM are also ignored
   in the comparison.
*/

int
compareproducts(char **one, char **two, int (*isdimless)(char *name))
{
   int oneblank, twoblank;
   while (*one || *two) {
      oneblank = (*one==NULLUNIT) || isdimless(*one);    
      twoblank = (*two==NULLUNIT) || isdimless(*two);    
      if (!*one && !twoblank)
	 return 1;
      if (!*two && !oneblank)
	 return 1;
      if (oneblank)
	 one++;
      else if (twoblank)
	 two++;
      else if (strcmp(*one, *two))
	 return 1;
      else
	 one++, two++;
   }
   return 0;
}


/* Return zero if units are compatible, nonzero otherwise.  The units
   must be reduced, sorted and canceled for this to work.  */

int
compareunits(struct unittype *first, struct unittype *second, 
	     int (*isdimless)(char *name))
{
   return
      compareproducts(first->numerator, second->numerator, isdimless) ||
      compareproducts(first->denominator, second->denominator, isdimless);
}


/* Reduce a unit as much as possible */

int
completereduce(struct unittype *unit)
{
   int err;

   if (err=reduceunit(unit))
     return err;
   sortunit(unit);
   cancelunit(unit);
   return 0;
}


/* Raise theunit to the specified power.  This function does not fill
   in NULLUNIT gaps, which could be considred a deficiency. */

int
expunit(struct unittype *theunit, int  power)
{
  char **numptr, **denptr;
  double thefactor;
  int i, uind, denlen, numlen;

  if (power==0){
    freeunit(theunit);
    initializeunit(theunit);
    return 0;
  }
  numlen=0;
  for(numptr=theunit->numerator;*numptr;numptr++) numlen++;
  denlen=0;
  for(denptr=theunit->denominator;*denptr;denptr++) denlen++;
  thefactor=theunit->factor;
  for(i=1;i<power;i++){
    theunit->factor *= thefactor;
    for(uind=0;uind<numlen;uind++){
      if (theunit->numerator[uind]!=NULLUNIT){
	if (numptr-theunit->numerator>MAXSUBUNITS-1) {
           *numptr=*denptr=0;
           return E_PRODOVERFLOW;
	}
        *numptr++=dupstr(theunit->numerator[uind]);
      }
    }
    for(uind=0;uind<denlen;uind++){
      if (theunit->denominator[uind]!=NULLUNIT){
        *denptr++=dupstr(theunit->denominator[uind]);
        if (denptr-theunit->denominator>MAXSUBUNITS-1) {
          *numptr=*denptr=0;
          return E_PRODOVERFLOW;
	}
      }   
    }
  }
  *numptr=0;
  *denptr=0;
  return 0;
}


int
unit2num(struct unittype *input)
{
  struct unittype one;
  int err;

  initializeunit(&one);
  if (err=completereduce(input))
    return err;
  if (compareunits(input,&one,ignore_nothing))
    return E_NOTANUMBER;
  freeunit(input);
  return 0;
}

/*
void showunitdetail(struct unittype *foo)
{
  char **ptr;

  printf("%.17g ", foo->factor);

  for(ptr=foo->numerator;*ptr;ptr++)
    if (*ptr==NULLUNIT) printf("NULL ");
    else printf("`%s' ", *ptr);
  printf(" / ");
  for(ptr=foo->denominator;*ptr;ptr++)
    if (*ptr==NULLUNIT) printf("NULL ");
    else printf("`%s' ", *ptr);
  putchar('\n');
}
*/


/* 
   The unitroot function takes the nth root of an input unit which has
   been completely reduced.  Returns 1 if the unit is not a power of n. 
   Input data can contain NULLUNITs.  
*/

int 
subunitroot(int n,char *in[], char *out[])
{
  char **ptr,**current;
  int count;

  for(current = in;*current && *current==NULLUNIT;current++);
  count = 0;
  for(ptr=in;*ptr;ptr++){
    if (*ptr==NULLUNIT) continue;
    if (count==n) {
      *(out++)=dupstr(*current);
      current = ptr;
      count=0;
    }
    if (!strcmp(*current,*ptr)) count++;
    else return E_NOTROOT;
  }
  if (count==n) *(out++)=dupstr(*current);
  else if (count!=0) return E_NOTROOT;
  *out = 0;
  return 0;
}

int 
rootunit(struct unittype *inunit,int n)
{
   struct unittype outunit;
   int err; 

   initializeunit(&outunit);
   if (err=completereduce(inunit))
     return err;
   if ((n & 1==0) && (inunit->factor<0)) return E_NOTROOT;
   outunit.factor = pow(inunit->factor,1.0/(double)n);
   if (err = subunitroot(n, inunit->numerator, outunit.numerator))
     return err;
   if (err = subunitroot(n, inunit->denominator, outunit.denominator))
     return err;
   freeunit(inunit);
   initializeunit(inunit);
   return multunit(inunit,&outunit);
}


/* Compute the inverse of a unit (1/theunit) */

void
invertunit(struct unittype *theunit)
{
  char **ptr, *swap;
  int numlen, length, ind;

  theunit->factor = 1.0/theunit->factor;  
  length=numlen=0;
  for(ptr=theunit->denominator;*ptr;ptr++,length++);
  for(ptr=theunit->numerator;*ptr;ptr++,numlen++);
  if (numlen>length)
    length=numlen;
  for(ind=0;ind<=length;ind++){
    swap = theunit->numerator[ind];
    theunit->numerator[ind] = theunit->denominator[ind];
    theunit->denominator[ind] = swap;
  }
}

/* Raise a unit to a power */

int
unitpower(struct unittype *base, struct unittype *exponent)
{
  double expnum;
  int errcode;
  errcode = unit2num(exponent);
  if (errcode) 
    return errcode;
  expnum = exponent->factor;
  if (floor(expnum)==expnum){ /* integer case */
    errcode = expunit(base,abs((int)expnum));
    if (errcode)
      return errcode;
    if (expnum<0)
      invertunit(base);
  } else if (floor(1.0/expnum)==1.0/expnum) { /* root */
     expnum = 1/expnum;
     errcode = rootunit(base,abs((int)expnum));
     if (errcode)
       return errcode;
     if (expnum<0) 
       invertunit(base);
  } else {  /* general case */
     errcode = unit2num(base);
     if (errcode) 
       return errcode;
     base->factor = pow(base->factor,expnum);
  }
  return 0;
}


/* Old units program would give message about what each operand
   reduced to, showing that they weren't conformable.  Can this
   be achieved here?  */

int
addunit(struct unittype *unita, struct unittype *unitb)
{
  int err;

  if (err=completereduce(unita))
    return err;
  if (err=completereduce(unitb))
    return err;
  if (compareunits(unita,unitb,ignore_nothing))
    return E_BADSUM;
  unita->factor += unitb->factor;
  freeunit(unitb);
  return 0;
}


double
linearinterp(double  a, double b, double aval, double bval, double c)
{
  double lambda;

  lambda = (b-c)/(b-a);
  return lambda*aval + (1-lambda)*bval;
}


/* evaluate a user function */

int
evalfunc(struct unittype *theunit, struct func *infunc, int inverse)
{
   struct unittype result;
   struct functype *thefunc;
   int err;
   double value;
   int foundit, count;
   struct unittype *save_value;
   char *save_function;

   if (infunc->table) {  /* Tables are short, so use dumb search algorithm */
     err = parseunit(&result, infunc->tableunit, 0, 0);
     if (err)
       return E_BADTABLE;
     if (inverse){
       err = divunit(theunit, &result);
       if (err)
	 return err;
       err = unit2num(theunit);
       if (err==E_NOTANUMBER)
	 return E_BADFUNCARG;
       if (err)
	 return err;
       value = theunit->factor;
       foundit=0;
       for(count=0;count<infunc->tablelen-1;count++)
         if ((infunc->table[count].value<=value &&
	      value<=infunc->table[count+1].value) ||
	     (infunc->table[count+1].value<=value &&
	      value<=infunc->table[count].value)){
	   foundit=1;
	   value  = linearinterp(infunc->table[count].value,
				 infunc->table[count+1].value,
				 infunc->table[count].location,
				 infunc->table[count+1].location,
				 value);
	   break;
	 }
       if (!foundit)
	 return E_NOTINDOMAIN;
       freeunit(&result);
       freeunit(theunit);
       theunit->factor = value;
       return 0;
     } else {
       err=unit2num(theunit);
       if (err)
	 return err;
       value=theunit->factor;
       foundit=0;
       for(count=0;count<infunc->tablelen-1;count++)
	 if (infunc->table[count].location<=value &&
	     value<=infunc->table[count+1].location){
           foundit=1;
	   value =  linearinterp(infunc->table[count].location,
			infunc->table[count+1].location,
			infunc->table[count].value,
			infunc->table[count+1].value,
			value);
	   break;
	 } 
       if (!foundit)
	 return E_NOTINDOMAIN;
       result.factor *= value;
     }
   } else {  /* it's a function */
     if (inverse){
       thefunc=&(infunc->inverse);
       if (!thefunc->def)
	 return E_NOINVERSE;
     }
     else
       thefunc=&(infunc->forward);
     err = completereduce(theunit);
     if (err)
       return err;
     if (thefunc->dimen){
       err = parseunit(&result, thefunc->dimen, 0, 0);
       if (err)
	 return E_BADTABLE;
       err = completereduce(&result);
       if (err)
	 return E_BADTABLE;
       if (compareunits(&result, theunit, ignore_nothing))
	 return E_BADFUNCARG;
     }
     save_value = parameter_value;
     save_function = function_parameter;
     parameter_value = theunit;
     function_parameter = thefunc->param;
     err = parseunit(&result, thefunc->def, 0,0);
     function_parameter = save_function;
     parameter_value = save_value;
     if (err==E_PARSEMEM) return err;
     if (err)
       return E_FUNARGDEF;
   }
   freeunit(theunit);
   initializeunit(theunit);
   multunit(theunit, &result);
   return 0;
}


/* 
   If the given character string has only one unit name in it, then print out
   the rule for that unit.  In any case, print out the reduced form for
   the unit.
*/

void
showdefinition(char *unitstr, struct unittype *theunit)
{
  unitstr = removepadding(unitstr);
  printf("%s",deftext);
  unitstr = lookupunit(unitstr,1);
  while(unitstr && strspn(unitstr,"0123456789.") != strlen(unitstr) && 
	!strchr(unitstr,PRIMITIVECHAR)) {
    printf("%s = ",unitstr);
    unitstr=lookupunit(unitstr,1);
  } 
  showunit(theunit);
  putchar('\n');
}

void
showfuncdefinition(struct func *fun)
{
  int i;

  if (fun->table){  /* It's a table */
    printf("%sinterpolated table with points\n",deftext);
    for(i=0;i<fun->tablelen;i++){
      if (verbose>0)
        printf("\t\t    ");
      printf("%s(", fun->name);
      printf(numformat, fun->table[i].location);
      printf(") = ");
      printf(numformat, fun->table[i].value);
      if (strchr("0123456789.",fun->tableunit[0]))
        printf(" *");
      printf(" %s\n",fun->tableunit);
    }
    return;
  }
  printf("%s%s(%s) = %s\n", deftext, fun->name, fun->forward.param,
	 fun->forward.def);
    
}


/* Show conversion to a function.  Input unit 'have' is completely reduced. */

int
showfunc(char *havestr, struct unittype *have, struct func *fun)
{
   int err;
   char *dimen;

   err = evalfunc(have, fun, 1);
   if (!err)
     err = completereduce(have);
   if (err) {
     if (err==E_BADFUNCARG){
       printf("conformability error");
       if (fun->table)
	 dimen = fun->tableunit;
       else if (fun->inverse.dimen)
	 dimen = fun->inverse.dimen;
       else 
	 dimen = 0;
       if (!dimen)
	 putchar('\n');
       else {
	 struct unittype want;
	 
	 if (*dimen==0)
	   dimen = "1";
	 printf(": conversion requires dimensions of '%s'\n",dimen);
	 if (verbose==2) printf("\t%s = ",havestr);
	 else if (verbose==1) putchar('\t');
	 showunit(have);
	 if (verbose==2) printf("\n\t%s = ",dimen);
	 else if (verbose==1) printf("\n\t");
	 else putchar('\n');
	 parseunit(&want, dimen, 0, 0);
	 completereduce(&want);
	 showunit(&want);
	 putchar('\n');
	 }
     } else if (err==E_NOTINDOMAIN)
       printf("Value '%s' is not in the table's range\n",havestr);
     else
       printf("Function evaluation error (bad function definition)\n");
     return 1;
   }
   if (verbose==2)
     printf("\t%s = %s(", havestr, fun->inverse.param);
   else if (verbose==1) 
     putchar('\t');
   showunit(have);
   if (verbose==2)
     putchar(')');
   putchar('\n');
   return 0;
}


/* Show the conversion factors or print the conformability error message */

int
showanswer(char *havestr,struct unittype *have,
           char *wantstr,struct unittype *want)
{
   struct unittype invhave;
   int doingrec;  /* reciprocal conversion? */
   char *sep, *right, *left;

   doingrec=0;
   havestr = removepadding(havestr);
   wantstr = removepadding(wantstr);
   if (compareunits(have, want, ignore_dimless)) {
        char **src,**dest;

        invhave.factor=1/have->factor;
        for(src=have->numerator,dest=invhave.denominator;*src;src++,dest++)
           *dest=*src;
        *dest=0;
        for(src=have->denominator,dest=invhave.numerator;*src;src++,dest++)
           *dest=*src;
        *dest=0;
        if (strictconvert || compareunits(&invhave, want, ignore_dimless)){
	  printf("conformability error\n");
	  if (verbose==2) 
	    printf("\t%s = ",havestr);
	  else if (verbose==1)
	    putchar('\t');
	  showunit(have);
	  if (verbose==2) 
	    printf("\n\t%s = ",wantstr);
	  else if (verbose==1)
	    printf("\n\t");
	  else
	    putchar('\n');
	  showunit(want);
	  putchar('\n');
	  return -1;
        }
	if (verbose>0)
	  putchar('\t');
        printf("reciprocal conversion\n");
        have=&invhave;
        doingrec=1;
   } 
   if (verbose==2) {
     if (strchr("0123456789.",wantstr[0]))
       sep=" *";
     else 
       sep="";
     if (!doingrec) 
       left=right="";
     else if (strchr(havestr,'/')) {
       left="1 / (";
       right=")";
     } else {
       left="1 / ";
       right="";
     }
   }   

   /* Print the first line of output. */

   if (verbose==2) 
     printf("\t%s%s%s = ",left,havestr,right);
   else if (verbose==1)
     printf("\t* ");
   printf(numformat, have->factor / want->factor);
   if (verbose==2) {
     printf("%s %s", sep, wantstr);
   }

   /* Print the second line of output. */

   if (!oneline){
     if (verbose==2) 
       printf("\n\t%s%s%s = (1 / ",left,havestr,right);
     else if (verbose==1)
       printf("\n\t/ ");
     else 
       putchar('\n');
     printf(numformat, want->factor / have->factor);
     if (verbose==2) printf(")%s %s",sep,wantstr);
   }
   putchar('\n');
   return 0;
}


/* Checks that the function definition has a valid inverse 
   Prints a message to stdout if function has bad definition or
   invalid inverse. 
*/

#define SIGN(x) ( (x) > 0.0 ?   1 :   \
                ( (x) < 0.0 ? (-1) :  \
                                0 ))

void
checkfunc(struct func *infunc, int verbose)
{
  struct unittype theunit, saveunit;
  int err, i;
  double direction;

  if (verbose)
    printf("doing function '%s'\n", infunc->name);
  if (infunc->table){         /* Check for monotonicity which is needed for */
    if (infunc->tablelen<=1){ /* unique inverses */
      printf("Table '%s' has only one data point\n", infunc->name);
      return;
    }
    direction = SIGN(infunc->table[1].value -  infunc->table[0].value);
    for(i=2;i<infunc->tablelen;i++)
      if (SIGN(infunc->table[i].value-infunc->table[i-1].value) != direction){
	printf("Table '%s' lacks unique inverse around entry %.8g\n",
	       infunc->name, infunc->table[i].location);
	return;
      }
    return;
  }
  if (infunc->forward.dimen){
    err = parseunit(&theunit, infunc->forward.dimen, 0, 0);
    if (err){
      printf("Function '%s' has invalid type '%s'\n", 
	     infunc->name, infunc->forward.dimen);
      return;
    }
  } else initializeunit(&theunit);
  theunit.factor *= 7;   /* Arbitrary choice where we evaluate inverse */
  unitcopy(&saveunit, &theunit);
  err = evalfunc(&theunit, infunc, 0);
  if (err) {
    printf("Error in definition %s(%s) as '%s'\n",
	   infunc->name, infunc->forward.param, infunc->forward.def);
    freeunit(&theunit);
    freeunit(&saveunit);
    return;
  }
  if (!(infunc->inverse.def)){
    printf("Warning: no inverse for function '%s'\n", infunc->name);
    freeunit(&theunit);
    freeunit(&saveunit);
    return;
  }
  err = evalfunc(&theunit, infunc, 1);
  if (err){
    printf("Error in inverse ~%s(%s) as '%s'\n",
	   infunc->name,infunc->inverse.param, infunc->inverse.def);
    freeunit(&theunit);
    freeunit(&saveunit);
    return;
  }
  divunit(&theunit, &saveunit);
  if (unit2num(&theunit) || fabs(theunit.factor-1)>1e-12)
    printf("Inverse is not the inverse for function '%s'\n", infunc->name);
  freeunit(&theunit);
}


/* 
   Check that all units and prefixes are reducible to primitive units and that
   function definitions are valid and have correct inverses.  A message is
   printed for every unit that does not reduce to primitive units.

*/


void 
checkunits(int verbosecheck)
{
  struct unittype have,second,one;
  struct unitlist *uptr;
  struct prefixlist *pptr;
  struct func *funcptr;
  int i;

  initializeunit(&one);

  /* Check all functions for valid definition and correct inverse */
  
  for(funcptr=firstfunc;funcptr;funcptr=funcptr->next)
    checkfunc(funcptr, verbosecheck);

  /* Now check all units for validity */

  for(i=0;i<HASHSIZE;i++)
    for (uptr = utab[i]; uptr; uptr = uptr->next){
      if (verbosecheck)
        printf("doing '%s'\n",uptr->name);
      if (parseunit(&have, uptr->name,0,0) 
	  || completereduce(&have) 
	  || compareunits(&have,&one, ignore_primitive)){
	if (isfunction(uptr->name)) 
	  printf("Unit '%s' hidden by function '%s'\n", uptr->name, uptr->name);
	else
	  printf("'%s' defined as '%s' irreducible\n",uptr->name, uptr->value);
      } else {
        minusminus = !minusminus;
        parseunit(&second, uptr->name, 0, 0);
        completereduce(&second);
        if (compareunits(&have, &second, ignore_nothing)){
	  printf("'%s': replace '-' with '+-' for subtraction or '*' to multiply\n", uptr->name);
	}
	freeunit(&second);
        minusminus=!minusminus;
      }

      freeunit(&have);
    }

  /* Check prefixes */ 

  for(i=0;i<PREFIXTABSIZE;i++)
    for(pptr = ptab[i]; pptr; pptr = pptr->next){
      if (verbosecheck)
        printf("doing '%s'\n",pptr->name);
      if (parseunit(&have, pptr->name,0,0) 
	  || completereduce(&have) || compareunits(&have,&one,ignore_primitive))
	printf("'%s-' defined as '%s' irreducible\n",pptr->name, pptr->value);
      else { 
	int plevel;    /* check for bad '/' character in prefix */
	char *ch;
	plevel = 0;
	for(ch=pptr->value;*ch;ch++){
	  if (*ch==')') plevel--;
	  else if (*ch=='(') plevel++;
	  else if (plevel==0 && *ch=='/'){
	    printf(
              "'%s-' defined as '%s' contains a bad '/'. (Add parentheses.)\n",
	      pptr->name, pptr->value);
	    break;
	  }
	}	    
      }  
      freeunit(&have);
    }
}


struct namedef { 
  char *name;
  char *def;
};
    
void addtolist(struct unittype *have, char *rname, char *name, char *def, 
	       struct namedef **list, int *listsize, int *maxnamelen, 
	       int *count)
{
  struct unittype want;
  int len;

  if (!name) 
    return;
  initializeunit(&want);
  parseunit(&want, name,0,0);
  completereduce(&want);
  if (!compareunits(have,&want,ignore_dimless)){
    if (*count==*listsize){
      *listsize += 100;
      *list = (struct namedef *) 
	realloc(*list,*listsize*sizeof(struct namedef));
      if (!*list){
	fprintf(stderr, "%s: memory allocation error (tryallunits)\n",
		progname);  
	exit(3);
      }
    }
    (*list)[*count].name = rname;
    if (strchr(def, PRIMITIVECHAR))
      (*list)[*count].def = "<primitive unit>";
    else
      (*list)[*count].def = def;
    (*count)++;
    len = strlen(name);
    if (len>*maxnamelen)
	  *maxnamelen = len;
  }
  freeunit(&want);
}


int 
compnd(const void *a, const void *b)
{
  return strcmp(((struct namedef *)a)->name, ((struct namedef *)b)->name);
}


/* Ideally this would return the actual screen height, but it's so 
   hard to code that portably... */

int 
screensize()
{
   return 20;
}


/* 
   Cycle through all units and print ones which are conformable with
   the argument.
*/

void 
tryallunits(struct unittype *have)
{
  struct unitlist *uptr;
  struct namedef *list;
  int listsize, maxnamelen, count;
  struct func *funcptr;
  int i, j;
  FILE *outfile;

  list = (struct namedef *) mymalloc( 100 * sizeof(struct namedef), 
				       "(tryallunits)");
  listsize = 100;
  maxnamelen = 0;
  count = 0;

  for(i=0;i<HASHSIZE;i++)
    for (uptr = utab[i]; uptr; uptr = uptr->next)
      addtolist(have, uptr->name, uptr->name, uptr->value, &list, 
		&listsize, &maxnamelen, &count);
  for(funcptr=firstfunc;funcptr;funcptr=funcptr->next){
    if (funcptr->table) 
      addtolist(have, funcptr->name, funcptr->tableunit, "<piecewise linear>", 
		&list, &listsize, &maxnamelen, &count);
    else
      addtolist(have, funcptr->name, funcptr->inverse.dimen, "<nonlinear>", 
		&list, &listsize, &maxnamelen, &count);
  }
  qsort(list, count, sizeof(struct namedef), compnd);

  outfile = 0;
  if (count==0)
    printf("No matching units found.\n");
#ifdef SIGPIPE
  signal(SIGPIPE, SIG_IGN);
#endif
  if (count>screensize()){
    outfile = popen(pager, "w");
  }
  if (!outfile)
    outfile = stdout;
  for(i=0;i<count;i++){
    fputs(list[i].name,outfile);
    for(j=strlen(list[i].name);j<=maxnamelen;j++)
      putc(' ',outfile);
    fprintf(outfile, "%s\n",list[i].def);
  }
  if (outfile != stdout)
    pclose(outfile);
#ifdef SIGPIPE
  signal(SIGPIPE, SIG_DFL);
#endif
}


/* print usage message */

void 
usage()
{
   printf("Usage: %s [option] ['from-unit' 'to-unit']\n",progname);
   fputs("\
\n\
    -h, --help          print this help and exit\n\
    -c, --check         check that all units reduce to primitive units\n\
        --check-verbose like --check, but lists units as they are checked\n\
        --verbose-check   so you can find units that cause endless loops\n\
    -e, --exponential   exponential format output\n\
    -f, --file          specify a units data file (-f '' loads default file)\n\
    -m, --minus         make - into a subtraction operator (default)\n\
    -o, --output-format specify printf numeric output format\n\
    -p, --product       make - into a product operator\n\
    -q, --quiet         supress prompting\n\
        --silent        same as --quiet\n\
    -s, --strict        suppress reciprocal unit conversion (e.g. Hz<->s)\n\
    -v, --verbose       print slightly more verbose output\n\
        --compact       suppress printing of tab, '*', and '/' character\n\
    -1, --one-line      suppress the second line of output\n\
    -t, --terse         terse output (--strict --compact --quiet --one-line)\n\
    -V, --version       print version number and exit\n\n\
Report bugs to adrian@cam.cornell.edu.\n\n", stdout);
   exit(0);
}

/* Print message about how to get help */

void 
helpmsg()
{
  fprintf(stderr,"Try `%s --help' for more information.\n",progname);
  exit(3);
}

void
printversion()
{
  printf("GNU Units version %s\n%s, units database in %s\n\
Copyright (C) 2006 Free Software Foundation, Inc.\n\
GNU Units comes with ABSOLUTELY NO WARRANTY.\n\
You may redistribute copies of GNU Units\n\
under the terms of the GNU General Public License.\n\n", 
	 VERSION, RVERSTR,UNITSFILE);
}


/* If quiet is false then prompt user with the query.  

   Fetch one line of input and return it in *buffer.

   The bufsize argument is a dummy argument if we are using readline. 
   The readline version frees buffer if it is non-null.  The other
   version keeps the same buffer and grows it as needed.

   If no data is read, then this function exits the program. 
*/

#ifdef READLINE

void
getuser(char **buffer, int *bufsize, char *query)
{
  if (*buffer) free(*buffer);
  *buffer = readline(quiet?"":query);
  if (*buffer && **buffer) add_history(*buffer);
  if (!*buffer){
    if (!quiet)
       putchar('\n');
    exit(0);
  }
}

/* Note:  What should this do?  

   Complete either to the end of a prefix or complete to the 
   end of a unit.  Or if there is a full prefix plus part of a unit, 
   and if that prefix is longer than one character
   then complete that compound.  Don't complete a prefix fragment into
   prefix plus anything.  

   Seems to be working right now...but one problem.  Completing a blank
   entry always gets the cent sign.  Why is that?  My code seems to be
   working ok....

   One thing still needs to be done:  it won't complete a fragment into
   a whole prefix.  It should be possible to type "myr<tab>" and
   get "myria" for example.  
*/
   
char *
completeunits(char *text, int state)
{
  static struct prefixlist *curprefix;
  static struct unitlist *curunit;
  static int uhash;
  static int checkfunctions;
  static struct func *nextfunc;
  char *output,*thistry;
  
  if (!state){     /* state = 0 means this is the first call, so initialize */
    checkfunctions=1;
    nextfunc=firstfunc;
    uhash = 0;
    curprefix=0;
    curunit=utab[uhash];
  }
  output = 0;
  if (!nextfunc)
    checkfunctions = 0;
  while (!output){
    if (checkfunctions){
      if (nextfunc){
	if (strlen(text)<=strlen(nextfunc->name) &&
	    !strncmp(text,nextfunc->name,strlen(text))){
	  output = dupstr(nextfunc->name);
	}
	nextfunc = nextfunc->next;
	continue;
      } else checkfunctions = 0;
    }
    while (!curunit && uhash<HASHSIZE-1){
      uhash++;
      curunit = utab[uhash];
    }
    if (!curunit) return 0;
    thistry = text;
    if (curprefix)
       thistry+=curprefix->len;
    if (strlen(thistry)<=strlen(curunit->name) && 
           !strncmp(curunit->name,thistry,strlen(thistry))){
       output = (char *)mymalloc(1 + strlen(curunit->name)
                        + (curprefix ? curprefix->len:0),"(completeunits)");
       strcpy(output,curprefix?curprefix->name:"");
       strcat(output,curunit->name);
    }
    curunit = curunit->next;
    while (!curunit && uhash<HASHSIZE-1){
      uhash++;
      curunit = utab[uhash];
    }
    if (!curunit && !curprefix){
      if (curprefix = plookup(text)){
        if (strlen(curprefix->name)>1 && strlen(curprefix->name)<strlen(text)){
          uhash = 0;
          curunit = utab[uhash];
        } else curprefix=0;
      }
    }
  }    
  return output;
}

#else /* We aren't using READLINE */

void
getuser(char **buffer, int *bufsize, char *query)
{
  if (!quiet) fputs(query, stdout);
  if (!fgetslong(buffer, bufsize, stdin,0)){
    if (!quiet)
       putchar('\n');
    exit(0);
  }
}  


#endif /* READLINE */


char *
findunitsfile()
{
  FILE *testfile;
  char *file = UNITSFILE;
  testfile = fopen(file, "rt");
  if (!testfile) {
    char *direc, *env;
    char *filename;
    char separator[2];

    env = getenv("PATH");
    if (env) {
      filename = mymalloc(strlen(env)+strlen(UNITSFILE)+2,"(readunits)");

      if (strchr(env, ';'))	/* MS-DOS */
	strcpy(separator, ";");
      else		        /* UNIX */
	strcpy(separator, ":");
      direc = strtok(env, separator);
      while (direc) {
	strcpy(filename, "");
	strcat(filename, direc);
	strcat(filename, "/");
	strcat(filename, UNITSFILE);
	testfile = fopen(filename, "rt");
	if (testfile){
	  file = dupstr(filename);
	  break;
	}
	direc = strtok(NULL, separator);
      }
      free(filename);
    }
  }
  if (testfile)
    fclose(testfile);
  return file;
}
   

char *shortoptions = "Vvqechstf:o:mp1";

struct option longoptions[] = {
  {"version", no_argument, 0, 'V'},
  {"quiet", no_argument, &quiet, 1},
  {"silent", no_argument, &quiet, 1},
  {"exponential", no_argument, 0, 'e'},
  {"check", no_argument, &unitcheck, 1},
  {"check-verbose", no_argument, &unitcheck, 2},
  {"verbose-check", no_argument, &unitcheck, 2},
  {"verbose", no_argument, &verbose, 2},
  {"file", required_argument, 0, 'f'},
  {"output-format", required_argument, 0, 'o'},
  {"help",no_argument,0,'h'},
  {"strict",no_argument,&strictconvert, 1},
  {"terse",no_argument, 0, 't'},
  {"compact", no_argument, &verbose, 0},
  {"minus", no_argument, &minusminus, 1},
  {"product", no_argument, &minusminus, 0},
  {"one-line", no_argument, &oneline, 1},
  {0,0,0,0} };

/* Process the args.  Returns 1 if interactive mode is desired, and 0
   for command line operation.  If units appear on the command line
   they are returned in the from and to parameters. */

int
processargs(int argc, char **argv, char **from, char **to)
{
   extern char *optarg;
   extern int optind;
   int optchar, optindex;
   int ind;

   while ( -1 != 
      (optchar = 
         getopt_long(argc, argv,shortoptions,longoptions, &optindex ))) {
      switch (optchar) {
         case 'm':
	    minusminus = 1;
	    break;
         case 'p':
	    minusminus = 0;
	    break;
         case 't':
	    oneline = 1;
	    quiet = 1;
	    strictconvert = 1;
	    verbose = 0;
            break;
         case 'o':
            numformat = optarg;
            break;
         case 'c':
            unitcheck = 1;
            break;
	 case 'e':
	    numformat = "%6e";
	    break;
	 case 'f':
 	    for(ind=0;unitsfiles[ind];ind++); 
	    if (ind==MAXFILES){
	      fprintf(stderr, "At most %d -f specifications are allowed\n",
		      MAXFILES);
              exit(3);
	    }
            if (optarg && *optarg)
	      unitsfiles[ind] = optarg;
	    else 
	      unitsfiles[ind] = findunitsfile();
	    unitsfiles[ind+1] = 0;
	    break;
	 case 'q':
	    quiet = 1;
	    break; 
         case 's':
            strictconvert = 1;
            break;
         case 'v':
            verbose = 2;
            break;
         case '1':
          oneline = 1;
          break;
	 case 'V':
 	    printversion();
	    exit(3);
         case 0: break;  /* This is reached if a long option is 
                            processed with no return value set. */
         case '?':
	 case 'h':
	    usage();
	    break;
         default:
            helpmsg();
      } 
   }

   if (unitcheck) {
     if (optind != argc){
       fprintf(stderr, "Too many arguments (arguments are not allowed with -c).\n");
       helpmsg();
     }
   } else {
     if (optind == argc - 2) {
        quiet=1;
        *from = argv[optind];
        *to = argv[optind+1]; 
        return 0;
     }

     if (optind == argc - 1) {
        quiet=1;
        *from = argv[optind];
        *to=0;
        return 0;
     }
     if (optind < argc - 2) {
        fprintf(stderr,"Too many arguments (maybe you need quotes).\n");
        helpmsg();
     }
   }
   return 1;
}

/* 
   Process the string 'unitstr' as a unit, placing the processed data
   in the unit structure 'theunit'.  Returns 0 on success and 1 on
   failure.  If an error occurs an error message is printed to stdout.
   If pointer is set to POINT then a pointer (^) is printed showing
   the character in 'unitstr' where the error was detected.  In order
   for this pointer to be placed correctly, the prompt string must be
   passed (in 'prompt') so that it's length can be measured to
   correctly offset the pointer.
*/


 
int 
processunit(struct unittype *theunit, char *unitstr, char *prompt, int pointer)
{
  char *errmsg;
  int errloc,err;

  if (err=parseunit(theunit, unitstr, &errmsg, &errloc)){
    if (pointer){
      if (err!=E_UNKNOWNUNIT || !irreducible){
	if (!quiet) {
          while(*prompt++) putchar(' ');
	}
	if (errloc>0)  
	  while(--errloc) putchar(' ');
	printf("^\n");
      }
    }
    else
      printf("Error in '%s': ", unitstr);
    printf("%s",errmsg);
    if (err==E_UNKNOWNUNIT && irreducible)
      printf(" '%s'", irreducible);
    putchar('\n');

    return 1;
  }
  if (err=completereduce(theunit)){
    printf("%s",errormsg[err]);
    if (err==E_UNKNOWNUNIT)
      printf(" '%s'", irreducible);
    putchar('\n');
    return 1;
  }
  return 0;
}


/* 
   Checks to see if the input string contains HELPCOMMAND possibly
   followed by a unit name on which help is sought.  If not, then
   return 0.  Otherwise invoke the pager on units.dat at the line
   where the specified unit is defined.  Then return 1.  */

int
ishelpquery(char *str, struct unittype *have)
{
  struct unitlist *unit;
  struct func *function;
  struct prefixlist *prefix;
  char commandbuf[1000];  /* Hopefully this is enough overkill as no bounds */
  int unitline;           /* checking is performed. */
  char *file;
  
  str=removepadding(str);
  if (have && !strcmp(str, UNITMATCH)){
    tryallunits(have);
    return 1;
  }
  if (!strncmp(HELPCOMMAND,str,strlen(HELPCOMMAND))){
    str+=strlen(HELPCOMMAND);
    if (!strchr(WHITE,*str))
      return 0;
    str = removepadding(str);
    if (strlen(str)==0){
      printf("\n\
Units converts between different measuring systems.  At the '%s' \n\
prompt type in the units you want to convert from.  At the '%s'\n\
prompt enter the units to convert to.  \n\
\n\
Examples:\n\
%s6 inches\t%stempF(75)\t%s2 btu + 450 ft lbf\n\
%scm\t\t%stempC\t\t%s(kg^2/s)/(day lb/m^2)\n\
\t* 15.24\t\t\t23.889\t\t\t* 1.0660684e+08\n\
\t/ 0.065\t\t\t\t\t\t/ 9.3802611e-09\n\
\n\
The first example shows that 6 inches is about 15 cm or (1/0.065) cm.\n\
The second example shows how to convert 75 degrees Fahrenheit to Celsius.\n\
\n\
To quit from units type ^%s.\n\
\n\
At the '%s' prompt press return to see the definition of the unit you\n\
entered above or '%s' to get a list of conformable units. \n\
\n\
At either prompt you can type 'help' to see this message or 'help myunit' to \n\
browse the units database and read the comments relating to myunit or see\n\
other units related to myunit. \n\n",
	     queryhave, 
             querywant, 
             queryhave, queryhave, queryhave,
             querywant, querywant, querywant,
             EOFCHAR,
             querywant,
             UNITMATCH);
      return 1;
    }
    if (function = isfunction(str)){
      file = function->file;
      unitline = function->linenumber;
    }
    else if (unit = ulookup(str)){
      unitline = unit->linenumber;
      file = unit->file;
    }
    else if ((prefix = plookup(str)) && strlen(str)==prefix->len){
      unitline = prefix->linenumber;
      file = prefix->file;
    }
    else {
      printf("Unknown unit '%s'\n",str);
      return 1;
    }
    sprintf(commandbuf,"%s +%d %s", pager, unitline, file);
    if (system(commandbuf))
      fprintf(stderr,"%s: unable to invoke pager '%s' to display help\n", 
	      progname, pager);
    return 1;
  }
  return 0;
}

 

int
main(int argc, char **argv)
{
   struct unittype have, want;
   char *havestr=0, *wantstr=0;
   struct func *funcval;
   int havestrsize=0;   /* Only used if READLINE is undefined */
   int wantstrsize=0;   /* Only used if READLINE is undefined */
   int interactive;
   int readerr;
   char **unitfileptr;
   int unitcount=0, prefixcount=0, funccount=0;   /* for counting units */

#ifdef READLINE
#  if RL_READLINE_VERSION >= 0x0402 
      rl_completion_entry_function = (rl_compentry_func_t *)completeunits;
#  else
      rl_completion_entry_function = (Function *)completeunits;
#  endif
   rl_basic_word_break_characters = " \t+-*/()|^";
#endif

   unitsfiles[0] = 0;

   interactive = processargs(argc, argv, &havestr, &wantstr);

   if (verbose==0)
     deftext = "";

   if (!unitsfiles[0]){
     unitsfiles[0] = getenv("UNITSFILE");
     if (!unitsfiles[0])
       unitsfiles[0] = findunitsfile();
     unitsfiles[1] = 0;
   }

   mylocale = getenv("LOCALE");
   if (!mylocale)
     mylocale = DEFAULTLOCALE;

   for(unitfileptr=unitsfiles;*unitfileptr;unitfileptr++){      
     readerr = readunits(*unitfileptr, stderr, &unitcount, &prefixcount, 
			 &funccount, 0);
     if (readerr==E_MEMORY) 
       exit(3);
     if (readerr==E_FILE){
       fprintf(stderr, "%s: unable to open units file '%s'.  ",
	       progname, *unitfileptr);
       perror(0);
       exit(1);
     }
   }

   if (!quiet)
     printf("%d units, %d prefixes, %d nonlinear units\n\n", unitcount, prefixcount,
     funccount);
   if (unitcheck) {
      checkunits(unitcheck==2 || verbose==2);
      exit(0);
   }

   if (!interactive) {
      if (funcval = isfunction(havestr)){
	showfuncdefinition(funcval);
  	exit(0);
      }
      if (processunit(&have, havestr,"",NOPOINT))
	 exit(1);
      if (!wantstr){
         showdefinition(havestr,&have);
         exit(0);
      }
      if (funcval = isfunction(wantstr)){
         if (showfunc(havestr, &have, funcval))
	   exit(1);
	 else
	   exit(0);
      }
      if (processunit(&want, wantstr, "", NOPOINT))
	 exit(1);
      if (showanswer(havestr,&have,wantstr,&want))
	 exit(1);
      else
	 exit(0);
   } else {
      pager = getenv("PAGER");
      if (!pager)
	pager = DEFAULTPAGER;
      for (;;) {
	 do {
            getuser(&havestr,&havestrsize,queryhave);
	 } while (isblankstr(havestr) || ishelpquery(havestr,0) ||
		  (isfunction(havestr)==0 
		  && processunit(&have, havestr, queryhave, POINT)));
         if (funcval = isfunction(havestr)){
	   showfuncdefinition(funcval);
	   continue;
	 }
	 do { 
	   int repeat; 
	   do {
	     repeat = 0;
	     getuser(&wantstr,&wantstrsize,querywant);
             if (ishelpquery(wantstr, &have)){
	       repeat = 1;
	       printf("%s%s\n",queryhave, havestr);
	     }
	   } while (repeat);
	 } while (isfunction(wantstr)==0
		  && processunit(&want, wantstr, querywant, POINT));
         if (isblankstr(wantstr))
           showdefinition(havestr,&have);
         else if (funcval = isfunction(wantstr))
           showfunc(havestr, &have, funcval);
	 else {
           showanswer(havestr,&have,wantstr, &want);
	   freeunit(&want);
	 }
         freeunit(&have);
      }
   }
   return (0);
}

/* NOTES:

mymalloc, growbuffer and tryallunits are the only places with print
statements that should (?) be removed to make a library.  How can
error reporting in these functions (memory allocation errors) be
handled cleanly for a library implementation?  

method of reporting the definition of a function or table:
  Is it ok as is?  Report inverses?

functions allocated in linked list: could be bad if lots of functions

completion that recognizes built in functions (?)

Way to report the reduced form of the two operands of a sum when
they are not conformable.

*/



