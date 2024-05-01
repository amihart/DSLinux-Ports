/*
 *  parse.y: the parser for GNU units, a program for units conversion
 *  Copyright (C) 1999, 2000, 2001, 2002 Free Software Foundation, Inc
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
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *     
 *  This program was written by Adrian Mariano (adrian@cam.cornell.edu)
 */


%{

#define YYPARSE_PARAM comm
#define YYLEX_PARAM comm

#define COMM ((struct commtype *)comm)

#include "units.h"


static int err;  /* value used by parser to store return values */

#define CHECK if (err) { COMM->errorcode=err; YYABORT; }


#define MEMSIZE 100
struct unittype *memtable[MEMSIZE];
int nextunit=0;
int maxunit=0;

struct commtype {
   int location;
   char *data;
   struct unittype *result;
   int errorcode;
   char *paramname;
   struct unittype *paramvalue;
};

struct function { 
   char *name; 
   double (*func)(double); 
   int type;
}; 

#define DIMENSIONLESS 0
#define ANGLEIN 1
#define ANGLEOUT 2

struct unittype *
getnewunit()
{
  if (nextunit>=MEMSIZE) 
    return 0;
  memtable[nextunit] = (struct unittype *) 
    mymalloc(sizeof(struct unittype),"(getnewunit)");
  if (!memtable[nextunit])
    return 0;
  initializeunit(memtable[nextunit]);
  return memtable[nextunit++];
}
 

struct unittype *
makenumunit(double num,int *myerr)
{
  struct unittype *ret;
  ret=getnewunit();
  if (!ret){
    *myerr = E_PARSEMEM;
    return 0;  
  }
  ret->factor = num;
  *myerr = 0;
  return ret;
}


double 
logb2(double x)
{
  return log(x)/log(2.0);
}


int
funcunit(struct unittype *theunit, struct function *fun)
{
  struct unittype angleunit;

  if (fun->type==ANGLEIN){
    err=unit2num(theunit);
    if (err==E_NOTANUMBER){
      initializeunit(&angleunit);
      angleunit.denominator[0] = dupstr("radian");
      angleunit.denominator[1] = 0;
      err = multunit(theunit, &angleunit);
      freeunit(&angleunit);
      if (!err)
	err = unit2num(theunit);
    }
    if (err)
      return err;
  } else if (fun->type==ANGLEOUT || fun->type == DIMENSIONLESS) {
    if (err=unit2num(theunit))
      return err;
    
  } else 
     return E_BADFUNCTYPE;
  errno = 0;
  theunit->factor = (*(fun->func))(theunit->factor);
  if (errno)
    return E_FUNC;
  if (fun->type==ANGLEOUT) {
    theunit->numerator[0] = dupstr("radian");
    theunit->numerator[1] = 0;
  }
  return 0;
}


%}

%pure_parser
%name-prefix="units"

%union {
  double number;
  int integer;
  struct unittype *utype;
  struct function *dfunc;
  struct func *ufunc;
}


%token <number> REAL
%token <utype> UNIT
%token <dfunc> RFUNC
%token <ufunc> UFUNC
%token <integer> EXPONENT
%token <integer> MULTIPLY
%token <integer> DIVIDE
%token <integer> NUMDIV
%token <integer> SQRT
%token <integer> CUBEROOT
%token <integer> MULTMINUS
%token <integer> EOL
%token <integer> FUNCINV
%token <integer> SCANERROR

%type <number> numexpr
%type <utype> expr
%type <utype> list
%type <utype> pexpr
%type <utype> unitexpr


%left ADD MINUS
%left UNARY
%left DIVIDE 
%left MULTIPLY MULTMINUS
%nonassoc '(' SQRT CUBEROOT RFUNC UNIT REAL UFUNC FUNCINV SCANERROR
%right EXPONENT
%left NUMDIV


%%
 input: EOL          { COMM->result = makenumunit(1,&err); CHECK; YYACCEPT; }
      | unitexpr EOL { COMM->result = $1; YYACCEPT; }
      | error        { YYABORT; }
      ;

 unitexpr:  expr                    {$$ = $1;}
         |  DIVIDE list             { invertunit($2); $$=$2;}
         ;

 expr: list                         { $$ = $1; }
     | MULTMINUS list %prec UNARY   { $$ = $2; $$->factor *= -1; }
     | MINUS list %prec UNARY       { $$ = $2; $$->factor *= -1; }
     | expr ADD expr                { err = addunit($1,$3); CHECK; $$=$1;}
     | expr MINUS expr              { $3->factor *= -1; err = addunit($1,$3); 
                                         CHECK; $$=$1;}
     | expr DIVIDE expr             { err = divunit($1, $3); CHECK; $$=$1;}
     | expr MULTIPLY expr           { err = multunit($1,$3); CHECK; $$=$1;}
     ; 

 numexpr:  REAL                     { $$ = $1;         }
         | numexpr NUMDIV numexpr   { $$ = $1 / $3;    }
     ;

 pexpr: '(' expr ')'                { $$ = $2;  }
       ;

 /* list is a list of units, possibly raised to powers, to be multiplied
    together. */

 list:  numexpr                    { $$ = makenumunit($1,&err); CHECK;}
      | UNIT                       { $$ = $1; }
      | list EXPONENT list         { err = unitpower($1,$3); CHECK; $$=$1;}
      | list MULTMINUS list        { err = multunit($1,$3); CHECK; $$=$1;}
      | list list %prec MULTIPLY   { err = multunit($1,$2); CHECK; $$=$1;}
      | pexpr                      { $$=$1; }
      | SQRT pexpr                 { err = rootunit($2,2); CHECK; $$=$2;}
      | CUBEROOT pexpr             { err = rootunit($2,3); CHECK; $$=$2;}
      | RFUNC pexpr                { err = funcunit($2,$1); CHECK; $$=$2;}
      | UFUNC pexpr                { err = evalfunc($2,$1,0); CHECK; $$=$2;}
      | FUNCINV UFUNC pexpr        { err = evalfunc($3,$2,1); CHECK; $$=$3;}
      | list EXPONENT MULTMINUS list %prec EXPONENT  
                                   { $4->factor *= -1;
				   err = unitpower($1,$4); CHECK; $$=$1;}
      | SCANERROR                  { err = E_PARSEMEM; CHECK; }        
   ;




%%

#ifndef strchr
#  ifdef NO_STRCHR
#    define strchr(a,b) index((a),(b))
#  else
     char *strchr();
#  endif
#endif /* !strchr */

double strtod();


struct function 
  realfunctions[] = { "sin", sin,    ANGLEIN,
                      "cos", cos,    ANGLEIN,
                      "tan", tan,    ANGLEIN,
                      "ln", log,     DIMENSIONLESS,
                      "log", log10,  DIMENSIONLESS,
                      "log2", logb2, DIMENSIONLESS,
                      "exp", exp,    DIMENSIONLESS,
                      "acos", acos,  ANGLEOUT,
                      "atan", atan,  ANGLEOUT,
                      "asin", asin,  ANGLEOUT,
                      0, 0, 0};

struct {
  char op;
  int value;
} optable[] = { '*', MULTIPLY,
            	'/', DIVIDE, 
            	'|', NUMDIV, 
            	'+', ADD, 
            	'(', '(', 
            	')', ')', 
            	'^', EXPONENT, 
                '~', FUNCINV,
            	0, 0 };

struct {
  char *name;
  int value;
} strtable[] = { "sqrt", SQRT, 
                 "cuberoot", CUBEROOT, 
                 "per" , DIVIDE, 
                 "**", EXPONENT, 
                 0, 0 };

yylex(YYSTYPE *lvalp, struct commtype *comm)
{
  int length, count;
  struct unittype *output;
  char *inptr;

  char *nonunitchars = "+-*/|\t\n^ ()";
  
  if (comm->location==-1) return 0;
  inptr = comm->data + comm->location;   /* Point to start of data */

  /* Skip white space */
  while( *inptr && strchr(WHITE,*inptr)) inptr++, comm->location++;

  if (*inptr==0) {
    comm->location = -1;
    return EOL;  /* Return failure if string has ended */
  }  

  /* Check for '-' character which gets special handling */
 
  if (*inptr=='-'){
    comm->location++;
    if (minusminus)
      return MINUS;
    return MULTMINUS;
  }      

  /* Look for single character ops */

  for(count=0; optable[count].op; count++){
    if (*inptr==optable[count].op) {
       comm->location++;
       return optable[count].value;
    }
  }

  /* Look for numbers */

  if (strchr(".0123456789",*inptr)){  /* prevent "nan" from being recognized */
    char *endloc;
    lvalp->number = strtod(inptr, &endloc);
    if (inptr != endloc) { 
      comm->location += (endloc-inptr);
      return REAL;
    }
  }

  /* Look for a word (function name or unit name) */

  length = strcspn(inptr,nonunitchars);   

  if (!length){  /* This shouldn't happen */
     return 0;
  }
  
  /* Look for string operators */

  for(count=0;strtable[count].name;count++){
     if (length==strlen(strtable[count].name) && 
	 0==strncmp(strtable[count].name,inptr,length)){
       comm->location += length;
       return strtable[count].value;
     }
  }

  /* Look for real function names */

  for(count=0;realfunctions[count].name;count++){
     if (length==strlen(realfunctions[count].name) && 
	 0==strncmp(realfunctions[count].name,inptr,length)){
       lvalp->dfunc = realfunctions+count;
       comm->location += length;
       return RFUNC;
     }
  }

  /* Look for function parameter */

  if (function_parameter && length==strlen(function_parameter) && 
      0==strncmp(function_parameter, inptr, length)){
      output = getnewunit();
      if (!output)
	return SCANERROR;
      unitcopy(output, parameter_value);
      lvalp->utype = output;
      comm->location += length;
      return UNIT;
  } 

  /* Look for user defined function */

  lvalp->ufunc = fnlookup(inptr,length);
  if (lvalp->ufunc){
    comm->location += length;
    return UFUNC;
  }

  /* Didn't find a special string, so treat it as unit name */

  comm->location+=length;
  if (strchr("23456789",inptr[length-1])) {  /* do exponent handling like m3 */
     count = inptr[length-1] - '0';
     length--;
  } else count=1;

  output = getnewunit();
  if (!output)
    return SCANERROR;
  output->numerator[count]=0;
  for(;count;count--){
    output->numerator[count-1] = mymalloc(length+1,"(yylex)");
    strncpy(output->numerator[count-1], inptr, length);
    output->numerator[count-1][length]=0;
  }
  lvalp->utype=output;
  return UNIT;
}


yyerror(char *s){}

void
freelist(int startunit)
{
  if (nextunit>maxunit) 
    maxunit = nextunit;
  while(nextunit>startunit){
    freeunit(memtable[--nextunit]);
    free(memtable[nextunit]);
  }
}


int
parseunit(struct unittype *output, char *input,char **errstr,int *errloc)
{
  struct commtype comm;
  int startunit;

  startunit = nextunit;
  initializeunit(output);
  comm.location = 0;
  comm.data = input;
  comm.errorcode = E_PARSE;    /* Assume parse error */
  if (yyparse(&comm)){
    if (comm.location==-1) 
      comm.location = strlen(input);
    if (errstr){
      if (smarterror && comm.errorcode==E_FUNC)
	*errstr = strerror(errno);
      else
        *errstr=errormsg[comm.errorcode];
    }
    if (errloc)
      *errloc = comm.location;
    freelist(startunit);
    return comm.errorcode;
  } else {
    if (errstr)
      *errstr = 0;
    multunit(output,comm.result);
    freeunit(comm.result);
    freelist(startunit);
    return 0;
  }
}


