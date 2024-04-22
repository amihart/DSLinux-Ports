/*
 *  units, a program for units conversion
 *  Copyright (C) 1996, 1997, 1999, 2000, 2001 Free Software Foundation, Inc
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

#include <math.h>
#include <errno.h>

/* Apparently popen and pclose require leading _ under windows */
#if defined(_MSC_VER) || defined(__MINGW32__)
#  define popen(c,m) _popen(c,m)
#  define pclose(p) _pclose(p)
#endif

#ifdef STRINGS_H
#  include <strings.h>
#else
#  include <string.h>
#endif 

#ifndef NO_STDLIB_H
#  include <stdlib.h>
#else
   char *malloc(),  *realloc(),  *getenv();
#endif

#ifndef strchr
#  ifdef NO_STRCHR
#    define strchr(a,b) index((a),(b))
#  else
     char *strchr();
#  endif
#endif /* !strchr */

#ifndef strerror
#   define smarterror 0
#else
#   define smarterror 1
#endif

char *strtok(); 
double strtod();

#ifndef __STDC__
#  define void int
#endif

#define NOPOINT 0
#define POINT 1

#define E_NORMAL 0
#define E_PARSE 1
#define E_PRODOVERFLOW 2
#define E_REDUCE 3
#define E_BADSUM 4
#define E_NOTANUMBER 5
#define E_NOTROOT 6
#define E_UNKNOWNUNIT 7
#define E_FUNC 8         /* If errno is set after calling a function */
#define E_BADFUNCTYPE 9
#define E_BADFUNCARG 10
#define E_NOTINDOMAIN 11
#define E_BADTABLE 12
#define E_NOINVERSE 13
#define E_PARSEMEM 14
#define E_FUNARGDEF 15
#define E_FILE 16
#define E_BADFILE 17
#define E_MEMORY 18

#define WHITE " \t\n"

extern char *errormsg[];

/* 
   Data type used to store a single unit being operated on. 

   The numerator and denominator arrays contain lists of units
   (strings) which are terminated by a null pointer.  The special
   string NULLUNIT is used to mark blank units that occur in the
   middle of the list.  
*/

extern char *NULLUNIT;

#define MAXSUBUNITS 100		/* Size of internal unit reduction buffer */

struct unittype {
   char *numerator[MAXSUBUNITS];
   char *denominator[MAXSUBUNITS];
   double factor;
};


struct functype {
  char *param;
  char *def;
  char *dimen;
};

struct pair {
  double location, value;
};

struct func {
  char *name;
  struct functype forward;
  struct functype inverse;
  struct pair *table;
  int tablelen;
  char *tableunit;
  struct func *next;
  int linenumber;
  char *file;                  /* file where defined */ 
};

extern struct unittype *parameter_value;
extern char *function_parameter;
extern int minusminus;

void *mymalloc(int bytes,char *mesg);
void initializeunit(struct unittype *theunit);
void freeunit(struct unittype *theunit);
void unitcopy(struct unittype *dest, struct unittype *src);
int divunit(struct unittype *left, struct unittype *right);
void invertunit(struct unittype *theunit);
int multunit(struct unittype *left, struct unittype *right);
int expunit(struct unittype *theunit, int  power);
int addunit(struct unittype *unita, struct unittype *unitb);
int rootunit(struct unittype *inunit,int n);
int unitpower(struct unittype *base, struct unittype *exponent);
char *dupstr(char *str);
int unit2num(struct unittype *input);
struct func *fnlookup(const char *str, int length);
int evalfunc(struct unittype *theunit, struct func *infunc, int inverse);

int parseunit(struct unittype *output, char *input,char **errstr,int *errloc);

