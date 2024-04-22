/* A tiny BASIC interpreter */

// heavily modified from:
// https://gist.github.com/pmachapman/661f0fff9814231fde48
//
// Now it works with doubles instead of ints. Also fixed some bugs.

#include <string.h>
#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define NUM_LAB 100
#define LAB_LEN 10
#define FOR_NEST 25
#define SUB_NEST 25
#define PROG_SIZE 10000

#define DELIMITER  1
#define VARIABLE  2
#define NUMBER    3
#define COMMAND   4
#define STRING	  5
#define QUOTE	  6

#define PRINT 1
#define INPUT 2
#define IF    3
#define THEN  4
#define FOR   5
#define NEXT  6
#define TO    7
#define GOTO  8
#define EOL   9
#define FINISHED  10
#define GOSUB 11
#define RETURN 12
#define END 13

char *prog;  /* holds expression to be analyzed */
jmp_buf e_buf; /* hold environment for longjmp() */

double variables[26]= {    /* 26 user variables,  A-Z */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0
};

struct commands { /* keyword lookup table */
  char command[20];
  char tok;
} table[] = { /* Commands must be entered lowercase */
  {"print", PRINT}, /* in this table. */
  {"input", INPUT},
  {"if", IF},
  {"then", THEN},
  {"goto", GOTO},
  {"for", FOR},
  {"next", NEXT},
  {"to", TO},
  {"gosub", GOSUB},
  {"return", RETURN},
  {"end", END},
  {"", END}  /* mark end of table */
};

char token[80];

struct label {
  char name[LAB_LEN];
  char *p;  /* points to place to go in source file*/
};
struct label label_table[NUM_LAB];

char *find_label(), *gpop();

struct for_stack {
  int var; /* counter variable */
  double target;  /* target value */
  char *loc;
} fstack[FOR_NEST]; /* stack for FOR/NEXT loop */
struct for_stack fpop();

char *gstack[SUB_NEST];	/* stack for gosub */

int ftos;  /* index to top of FOR stack */
int gtos;  /* index to top of GOSUB stack */

void assignment();
void print(), scan_labels(), find_eol(), exec_goto();
void exec_if(), exec_for(), next(), fpush(), input();
void gosub(), greturn(), gpush(), label_init();
void serror(), get_exp(), putback();
void level2(), level3(), level4(), level5(), level6(), primitive();
void unary(), arith();
int load_program(char *p, char *fname), look_up(char *s);
int get_next_label(char *s), iswhite(char c), isdelim(char c);
double find_var(char *s);
void get_token(char *token_type, char *tok);

int main(int argc, char *argv[])
{
  char *p_buf;
  char token_type = 0;
  char tok = 0;
  
  if(argc!=2) {
    printf("usage: tinybasic <filename>\n");
    exit(1);
  }

  /* allocate memory for the program */
  if(!(p_buf=(char *) malloc(PROG_SIZE))) {
    printf("allocation failure");
    exit(1);
  }
  
  /* load the program to execute */
  if(!load_program(p_buf,argv[1])) exit(1);
  
  if(setjmp(e_buf)) exit(1); /* initialize the long jump buffer */
  
  prog = p_buf;
  scan_labels(); /* find the labels in the program */
  
  ftos = 0; /* initialize the FOR stack index */
  gtos = 0; /* initialize the GOSUB stack index */
  do {
    
    get_token(&token_type, &tok);
    /* check for assignment statement */
    if(token_type == VARIABLE) {
      putback(); /* return the var to the input stream */
      assignment(); /* must be assignment statement */
    }
    else /* is command */
      switch(tok) {
        case PRINT:
	        print();
  	      break;
        case GOTO:
          exec_goto();
          break;
        case IF:
          exec_if();
          break;
        case FOR:
          exec_for();
          break;
        case NEXT:
          next();
          break;
        case INPUT:
          input();
          break;
        case GOSUB:
          gosub();
          break;
        case RETURN:
          greturn();
          break;
        case END:
          exit(0);
      }
  } while (tok != FINISHED);
}

/* Load a program. */
int load_program(char *p, char *fname)
{
  FILE *fp;
  int i = 0;

  if(!(fp = fopen(fname, "rb"))) return 0;

  i = 0;
  do {
    *p = getc(fp);
    p++; i++;
  } while(!feof(fp) && i<PROG_SIZE);
  *(p-2) = '\0'; /* null terminate the program */
  fclose(fp);
  return 1;
}

/* Assign a variable a value. */
void assignment()
{
  int var;
  double value;
  char token_type = 0;
  char tok = 0;
  
  /* get the variable name */
  get_token(&token_type, &tok);
  if(!isalpha(*token)) {
    serror(4);
  }

  var = toupper(*token)-'A';
 
  /* get the equals sign */
  get_token(&token_type, &tok);
  if(*token!='=') {
    serror(3);
  }
  
  /* get the value to assign to var */
  get_exp(&value);
  /* assign the value */
  variables[var] = value;
}

/* Execute a simple version of the BASIC PRINT statement */
void print()
{
  double answer;
  int len=0, spaces;
  char last_delim;
  char token_type = 0;
  char tok = 0;

  do {
    get_token(&token_type, &tok); /* get next list item */
    if(tok==EOL || tok==FINISHED) break;
    if(token_type==QUOTE) { /* is string */
      printf("%s",token);
      len += strlen(token);
      get_token(&token_type, &tok);
    }
    else { /* is expression */
      putback();
      get_exp(&answer);
      get_token(&token_type, &tok);
      if ( (long)floor(answer * 1000.0) % 1000 < 10 )
      	len += printf("%.0f", answer);
      else
      	len += printf("%.4f", answer);
    }
    
    last_delim = *token;
    
    if(*token==';') {
      /* compute number of spaces to move to next tab */
      spaces = 8 - (len % 8);
      len += spaces; /* add in the tabbing position */
      while(spaces) {
	      printf(" ");
        spaces--;
      }
    }
    else if(*token == ',') /* do nothing */;
    else if(tok != EOL && tok != FINISHED) serror(0);
  } while (*token != '\r' || *token == ';' || *token == ',');

  if(tok==EOL || tok==FINISHED) {
    if(last_delim != ';' && last_delim != ',') printf("\n");
  }
  //else serror(0); /* error is not , or ; */

}

/* Find all labels. */
void scan_labels()
{
  int addr;
  char *temp;
  char token_type = 0;
  char tok = 0;
  
  label_init();  /* zero all labels */
  temp = prog;   /* save pointer to top of program */
  
  /* if the first token in the file is a label */
  get_token(&token_type, &tok);
  
  if(token_type==NUMBER) {
    strcpy(label_table[0].name,token);
    label_table[0].p=prog;
  }
  
  find_eol();
  do {
    get_token(&token_type, &tok);
    if(token_type==NUMBER) {
      addr = get_next_label(token);
      if(addr==-1 || addr==-2) {
          (addr==-1) ?serror(5):serror(6);
      }
      
      strcpy(label_table[addr].name, token);
      label_table[addr].p = prog;  /* current point in program */
    }
    /* if not on a blank line, find next line */
    if(tok!=EOL) find_eol();
  } while(tok!=FINISHED);
  
  prog = temp;  /* restore to original */
}

/* Find the start of the next line. */
void find_eol()
{
  while(*prog != '\n' && *prog != '\0') {
    prog++;
  }
  //if(*prog) prog++;
}

/* Return index of next free position in label array.
   A -1 is returned if the array is full.
   A -2 is returned when duplicate label is found.
*/
int get_next_label(char *s)
{
  register int t;

  for(t=0;t<NUM_LAB;++t) {
    if(label_table[t].name[0]==0) return t;
    if(!strcmp(label_table[t].name,s)) return -2; /* dup */
  }

  return -1;
}

/* Find location of given label.  A null is returned if
   label is not found; otherwise a pointer to the position
   of the label is returned.
*/
char *find_label(s)
char *s;
{
  register int t;

  for(t=0; t<NUM_LAB; ++t)
    if(!strcmp(label_table[t].name,s)) return label_table[t].p;
  return '\0'; /* error condition */
}

/* Execute a GOTO statement. */
void exec_goto()
{
  char *loc;
  char token_type = 0;
  char tok = 0;

  get_token(&token_type, &tok); /* get label to go to */
  /* find the location of the label */
  loc = find_label(token);
  if(*loc=='\0')
    serror(7); /* label not defined */

  else prog=loc;  /* start program running at that loc */
}

/* Initialize the array that holds the labels.
   By convention, a null label name indicates that
   array position is unused.
*/
void label_init()
{
  register int t;

  for(t=0; t<NUM_LAB; ++t) label_table[t].name[0]='\0';
}

/* Execute an IF statement. */
void exec_if()
{
  double x, y;
  int cond;
  char op[3] = "";
  char token_type = 0;
  char tok = 0;

  get_exp(&x); /* get left expression */
  get_token(&token_type, &tok); /* get the operator */
  if(strcmp("<>", token) != 0 && !strchr("=<>", *token)) {
    serror(0); /* not a legal operator */
    return;
  }
  
  strcpy(op, token);
  
  get_exp(&y); /* get right expression */
  /* determine the outcome */
  cond = 0;

  if(strcmp("<>", op) == 0) {
    if(x != y) cond = 1;
  } else if(strchr("<", *op)) {
    if(x < y) cond = 1;
  } else if(strchr(">", *op)) {
    if(x > y) cond = 1;
  } else if(strchr("=", *op)) {
    if(x == y) cond = 1;
  }
  if(cond) { /* is true so process target of IF */
    get_token(&token_type, &tok);
    if(tok != THEN) {
      serror(8);
      return;
    }/* else program execution starts on next line */
    exec_goto(); //<-- added line!
  }
  else {
    find_eol(); /* find start of next line */
  }
}

/* Execute a FOR loop. */
void exec_for()
{
  struct for_stack i;
  double value;
  char token_type = 0;
  char tok = 0;

  get_token(&token_type, &tok); /* read the control variable */
  if(!isalpha(*token)) {
    serror(4);
    return;
  }

  i.var=toupper(*token)-'A'; /* save its index */

  get_token(&token_type, &tok); /* read the equals sign */
  if(*token!='=') {
    serror(3);
    return;
  }

  get_exp(&value); /* get initial value */

  variables[i.var] = value;

  get_token(&token_type, &tok);
  if(tok != TO) serror(9); /* read and discard the TO */

  get_exp(&i.target); /* get target value */

  /* if loop can execute at least once, push info on stack */
  if(value >= variables[i.var]) {
    i.loc = prog;
    fpush(i);
  }
  else  /* otherwise, skip loop code altogether */
    while(tok != NEXT) get_token(&token_type, &tok);
}

/* Execute a NEXT statement. */
void next()
{
  struct for_stack i;

  i = fpop(); /* read the loop info */

  variables[i.var]++; /* increment control variable */
  if(variables[i.var] > i.target) return;  /* all done */
  fpush(i);  /* otherwise, restore the info */
  prog = i.loc;  /* loop */
}

/* Push function for the FOR stack. */
void fpush(i)
struct for_stack i;
{
   if(ftos > FOR_NEST)
    serror(10);

  fstack[ftos] = i;
  ftos++;
}

struct for_stack fpop()
{
  ftos--;
  if(ftos < 0) serror(11);
  return(fstack[ftos]);
}

/* Execute a simple form of the BASIC INPUT command */
void input()
{
  char var;
  int i;
  char token_type = 0;
  char tok = 0;

  get_token(&token_type, &tok); /* see if prompt string is present */
  if(token_type==QUOTE) {
    printf("%s",token); /* if so, print it and check for comma */
    get_token(&token_type, &tok);
    if(*token!=',') serror(1);
    get_token(&token_type, &tok);
  }
  else printf("? "); /* otherwise, prompt with / */
  var = toupper(*token)-'A'; /* get the input var */

  scanf("%d", &i); /* read input */

  variables[(int)var] = i; /* store it */
}

/* Execute a GOSUB command. */
void gosub()
{
  char *loc;
  char token_type = 0;
  char tok = 0;

  get_token(&token_type, &tok);
  /* find the label to call */
  loc = find_label(token);
  if(*loc=='\0')
    serror(7); /* label not defined */
  else {
    gpush(prog); /* save place to return to */
    prog = loc;  /* start program running at that loc */
  }
}

/* Return from GOSUB. */
void greturn()
{
   prog = gpop();
}

/* GOSUB stack push function. */
void gpush(s)
char *s;
{
  gtos++;

  if(gtos==SUB_NEST) {
    serror(12);
    return;
  }

  gstack[gtos]=s;

}

/* GOSUB stack pop function. */
char *gpop()
{
  if(gtos==0) {
    serror(13);
    return 0;
  }

  return(gstack[gtos--]);
}

/* Entry point into parser. */
void get_exp(result)
double *result;
{
  char token_type = 0;
  char tok = 0;
  get_token(&token_type, &tok);
  if(!*token) {
    serror(2);
    return;
  }
  level2(result, token_type, tok);
  putback(); /* return last token read to input stream */
}


/* display an error message */
void serror(error)
int error;
{
  static char *e[]= {
    "syntax error",
    "unbalanced parentheses",
    "no expression present",
    "equals sign expected",
    "not a variable",
    "Label table full",
    "duplicate label",
    "undefined label",
    "THEN expected",
    "TO expected",
    "too many nested FOR loops",
    "NEXT without FOR",
    "too many nested GOSUBs",
    "RETURN without GOSUB"
  };
  printf("%s\n", e[error]);
  longjmp(e_buf, 1); /* return to save point */
}

/* Get a token. */
void get_token(char *token_type, char *tok)
{

  register char *temp;

  temp=token;

  //printf(",%s",token);
  
  if(*prog=='\0') { /* end of file */
    *token=0;
    *tok = FINISHED;
    *token_type = DELIMITER;
    return;
  }

  while(iswhite(*prog)) ++prog;  /* skip over white space */
  
  
  if(*prog == '\r') { /* crlf */
    ++prog; ++prog;
    *tok = EOL; *token='\r';
    token[1]='\n'; token[2]=0;
    *token_type = DELIMITER;
    return;
  } 
  else if(*prog == '\n') {
    ++prog;
    *tok = EOL;
    *token = '\n';
    token[1] = 0;
    *token_type = DELIMITER;
    return;
  }
  
  // if clause delimiter x <> y
  if((*prog == '<') && (*(prog+1) == '>')) {
    *temp=*prog;
    prog++;
    temp++;
    *temp=*prog;
    prog++;
    temp++;
    *temp=0;
    *token_type=DELIMITER;
    return;
  }
  
  if(strchr("+-*^/%=;(),><", *prog)){ /* delimiter */
    *temp=*prog;
    prog++; /* advance to next position */
    temp++;
    *temp=0;
    *token_type=DELIMITER;
    return;
  }
  
  if(*prog=='"') { /* quoted string */
    prog++;
    while(*prog!='"'&& (*prog!='\r' || *prog!='\n')) *temp++=*prog++;
    if(*prog=='\r' || *prog=='\n') serror(1);
    prog++;*temp=0;
    *token_type=QUOTE;
    return;
  }
  
  if(isdigit(*prog)) { /* number */
    while(!isdelim(*prog)) {
      *temp++=*prog++;
    }
    *temp = '\0';    
    *token_type = NUMBER;
    return;
  }
  
  if(isalpha(*prog)) { /* var or command */
    while(!isdelim(*prog)) *temp++=*prog++;
    *token_type=STRING;
  }

  *temp = '\0';
  
  /* see if a string is a command or a variable */
  if(*token_type==STRING) {
    *tok = look_up(token); /* convert to internal rep */
    if(!*tok) *token_type = VARIABLE;
    else *token_type = COMMAND; /* is a command */
  }
}



/* Return a token to input stream. */
void putback()
{
  char *t;
  t = token;
  for(; *t; t++) prog--;
}

/* Look up a a token's internal representation in the
   token table.
*/
int look_up(char *s)
{
  register int i;
  char *p;

  /* convert to lowercase */
  p = s;
  while(*p){ *p = tolower(*p); p++; }

  /* see if token is in table */
  for(i=0; *table[i].command; i++)
      if(!strcmp(table[i].command, s)) return table[i].tok;
  return 0; /* unknown command */
}

/* Return true if c is a delimiter. */
int isdelim(char c)
{
  if(strchr(" ;,+-<>/*%^=()", c) || c==9 || c=='\r' || c=='\n' || c==0)
    return 1;
  return 0;
}

/* Return 1 if c is space or tab. */
int iswhite(char c)
{
  if(c==' ' || c=='\t') return 1;
  else return 0;
}



/*  Add or subtract two terms. */
void level2(result, token_type, tok)
double *result;
char token_type;
char tok;
{
  register char op;
  double hold;

  level3(result, token_type, tok);
  while((op = *token) == '+' || op == '-') {
    get_token(&token_type, &tok);
    level3(&hold, token_type, tok);
    arith(op, result, &hold);
  }
}

/* Multiply or divide two factors. */
void level3(result, token_type, tok)
double *result;
char token_type;
char tok;
{
  register char  op;
  double hold;

  level4(result, token_type, tok);
  while((op = *token) == '*' || op == '/' || op == '%') {
    get_token(&token_type, &tok);
    level4(&hold, token_type, tok);
    arith(op, result, &hold);
  }
}

/* Process integer exponent. */
void level4(result, token_type, tok)
double *result;
char token_type;
char tok;
{
  double hold;

  level5(result, token_type, tok);
  if(*token== '^') {
    get_token(&token_type, &tok);
    level4(&hold, token_type, tok);
    arith('^', result, &hold);
  }
}

/* Is a unary + or -. */
void level5(result, token_type, tok)
double *result;
char token_type;
char tok;
{
  register char op;

  op = 0;
  if((token_type==DELIMITER) && (*token=='+' || *token=='-')) {
    op = *token;
    get_token(&token_type, &tok);
  }
  level6(result, token_type, tok);
  if(op)
    unary(op, result);
}

/* Process parenthesized expression. */
void level6(result, token_type, tok)
double *result;
char token_type;
char tok;
{
  if((*token == '(') && (token_type == DELIMITER)) {
    get_token(&token_type, &tok);
    level2(result, token_type, tok);
    if(*token != ')')
      serror(1);
    get_token(&token_type, &tok);
  }
  else
    primitive(result, token_type, tok);
}

/* Find value of number or variable. */
void primitive(result, token_type, tok)
double *result;
char token_type;
char tok;
{

  switch(token_type) {
  case VARIABLE:
    *result = find_var(token);
    get_token(&token_type, &tok);
    return;
  case NUMBER:
    *result = atof(token);
    get_token(&token_type, &tok);
    return;
  default:
    serror(0);
  }
}

/* Perform the specified arithmetic. */
void arith(o, r, h)
char o;
double *r, *h;
{
  register int t, ex;

  switch(o) {
    case '-':
      *r = *r - *h;
      break;
    case '+':
      *r = *r + *h;
      break;
    case '*':
      *r = *r * *h;
      break;
    case '/':
      *r = *r / *h;
      break;
    case '%':
      t = (*r) / (*h);
      *r = *r - (t*(*h));
      break;
    case '^':
      ex = *r;
      if(*h == 0) {
        *r = 1;
        break;
      }
      for(t = *h-1; t > 0; --t) *r = (*r) * ex;
      break;
  }
}

/* Reverse the sign. */
void unary(o, r)
char o;
double *r;
{
  if(o=='-') *r = -(*r);
}

/* Find the value of a variable. */
double find_var(char *s)
{
  if(!isalpha(*s)){
    serror(4); /* not a variable */
    return 0;
  }
  return variables[toupper(*token)-'A'];
}
