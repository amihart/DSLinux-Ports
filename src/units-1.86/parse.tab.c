/* A Bison parser, made by GNU Bison 1.875a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse unitsparse
#define yylex   unitslex
#define yyerror unitserror
#define yylval  unitslval
#define yychar  unitschar
#define yydebug unitsdebug
#define yynerrs unitsnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     REAL = 258,
     UNIT = 259,
     RFUNC = 260,
     UFUNC = 261,
     EXPONENT = 262,
     MULTIPLY = 263,
     DIVIDE = 264,
     NUMDIV = 265,
     SQRT = 266,
     CUBEROOT = 267,
     MULTMINUS = 268,
     EOL = 269,
     FUNCINV = 270,
     SCANERROR = 271,
     MINUS = 272,
     ADD = 273,
     UNARY = 274
   };
#endif
#define REAL 258
#define UNIT 259
#define RFUNC 260
#define UFUNC 261
#define EXPONENT 262
#define MULTIPLY 263
#define DIVIDE 264
#define NUMDIV 265
#define SQRT 266
#define CUBEROOT 267
#define MULTMINUS 268
#define EOL 269
#define FUNCINV 270
#define SCANERROR 271
#define MINUS 272
#define ADD 273
#define UNARY 274




/* Copy the first part of user declarations.  */
#line 23 "parse.y"


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




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 139 "parse.y"
typedef union YYSTYPE {
  double number;
  int integer;
  struct unittype *utype;
  struct function *dfunc;
  struct func *ufunc;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 244 "parse.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 256 "parse.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   149

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  22
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  7
/* YYNRULES -- Number of rules. */
#define YYNRULES  29
/* YYNRULES -- Number of states. */
#define YYNSTATES  51

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      20,    21,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    15,    17,    20,
      23,    27,    31,    35,    39,    41,    45,    49,    51,    53,
      57,    61,    64,    66,    69,    72,    75,    78,    82,    87
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      23,     0,    -1,    14,    -1,    24,    14,    -1,     1,    -1,
      25,    -1,     9,    28,    -1,    28,    -1,    13,    28,    -1,
      17,    28,    -1,    25,    18,    25,    -1,    25,    17,    25,
      -1,    25,     9,    25,    -1,    25,     8,    25,    -1,     3,
      -1,    26,    10,    26,    -1,    20,    25,    21,    -1,    26,
      -1,     4,    -1,    28,     7,    28,    -1,    28,    13,    28,
      -1,    28,    28,    -1,    27,    -1,    11,    27,    -1,    12,
      27,    -1,     5,    27,    -1,     6,    27,    -1,    15,     6,
      27,    -1,    28,     7,    13,    28,    -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,   180,   180,   181,   182,   185,   186,   189,   190,   191,
     192,   193,   195,   196,   199,   200,   203,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   223
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "REAL", "UNIT", "RFUNC", "UFUNC", 
  "EXPONENT", "MULTIPLY", "DIVIDE", "NUMDIV", "SQRT", "CUBEROOT", 
  "MULTMINUS", "EOL", "FUNCINV", "SCANERROR", "MINUS", "ADD", "UNARY", 
  "'('", "')'", "$accept", "input", "unitexpr", "expr", "numexpr", 
  "pexpr", "list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    22,    23,    23,    23,    24,    24,    25,    25,    25,
      25,    25,    25,    25,    26,    26,    27,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    28,    28,    28,    28
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     2,     2,
       3,     3,     3,     3,     1,     3,     3,     1,     1,     3,
       3,     2,     1,     2,     2,     2,     2,     3,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     4,    14,    18,     0,     0,     0,     0,     0,     0,
       2,     0,    29,     0,     0,     0,     0,     5,    17,    22,
       7,    25,    26,     6,    23,    24,     8,     0,     9,     0,
       1,     3,     0,     0,     0,     0,     0,     0,     0,    21,
      27,    16,    13,    12,    11,    10,    15,     0,    19,    20,
      28
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,    15,    16,    17,    18,    19,    39
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -18
static const short yypact[] =
{
      39,   -18,   -18,   -18,   -17,   -17,   129,   -17,   -17,   129,
     -18,     6,   -18,   129,    57,     8,     3,    13,    19,   -18,
      75,   -18,   -18,    75,   -18,   -18,    75,   -17,    75,     2,
     -18,   -18,    57,    57,    57,    57,    15,    93,   129,   111,
     -18,   -18,   -18,    28,     7,     7,   -18,   129,    32,   111,
      32
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -18,   -18,   -18,    -7,     5,    -3,     0
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      20,    21,    22,    14,    24,    25,    23,    29,    30,    26,
      32,    33,    27,    28,    20,    32,    33,    31,     2,    34,
      35,    32,    33,    41,    40,    42,    43,    44,    45,    36,
      34,    35,    20,    20,    20,    20,    32,    48,    49,    37,
       1,    46,     2,     3,     4,     5,     0,    50,     6,     0,
       7,     8,     9,    10,    11,    12,    13,     0,     0,    14,
       2,     3,     4,     5,     0,     0,     0,     0,     7,     8,
       9,     0,    11,    12,    13,     0,     0,    14,     2,     3,
       4,     5,    37,     0,     0,     0,     7,     8,    38,     0,
      11,    12,     0,     0,     0,    14,     2,     3,     4,     5,
       0,     0,     0,     0,     7,     8,    47,     0,    11,    12,
       0,     0,     0,    14,     2,     3,     4,     5,    37,     0,
       0,     0,     7,     8,     0,     0,    11,    12,     0,     0,
       0,    14,     2,     3,     4,     5,     0,     0,     0,     0,
       7,     8,     0,     0,    11,    12,     0,     0,     0,    14
};

static const yysigned_char yycheck[] =
{
       0,     4,     5,    20,     7,     8,     6,    14,     0,     9,
       8,     9,     6,    13,    14,     8,     9,    14,     3,    17,
      18,     8,     9,    21,    27,    32,    33,    34,    35,    10,
      17,    18,    32,    33,    34,    35,     8,    37,    38,     7,
       1,    36,     3,     4,     5,     6,    -1,    47,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    11,    12,
      13,    -1,    15,    16,    17,    -1,    -1,    20,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    12,    13,    -1,
      15,    16,    -1,    -1,    -1,    20,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    11,    12,    13,    -1,    15,    16,
      -1,    -1,    -1,    20,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    15,    16,    -1,    -1,
      -1,    20,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      11,    12,    -1,    -1,    15,    16,    -1,    -1,    -1,    20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     3,     4,     5,     6,     9,    11,    12,    13,
      14,    15,    16,    17,    20,    23,    24,    25,    26,    27,
      28,    27,    27,    28,    27,    27,    28,     6,    28,    25,
       0,    14,     8,     9,    17,    18,    10,     7,    13,    28,
      27,    21,    25,    25,    25,    25,    26,    13,    28,    28,
      28
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 180 "parse.y"
    { COMM->result = makenumunit(1,&err); CHECK; YYACCEPT; ;}
    break;

  case 3:
#line 181 "parse.y"
    { COMM->result = yyvsp[-1].utype; YYACCEPT; ;}
    break;

  case 4:
#line 182 "parse.y"
    { YYABORT; ;}
    break;

  case 5:
#line 185 "parse.y"
    {yyval.utype = yyvsp[0].utype;;}
    break;

  case 6:
#line 186 "parse.y"
    { invertunit(yyvsp[0].utype); yyval.utype=yyvsp[0].utype;;}
    break;

  case 7:
#line 189 "parse.y"
    { yyval.utype = yyvsp[0].utype; ;}
    break;

  case 8:
#line 190 "parse.y"
    { yyval.utype = yyvsp[0].utype; yyval.utype->factor *= -1; ;}
    break;

  case 9:
#line 191 "parse.y"
    { yyval.utype = yyvsp[0].utype; yyval.utype->factor *= -1; ;}
    break;

  case 10:
#line 192 "parse.y"
    { err = addunit(yyvsp[-2].utype,yyvsp[0].utype); CHECK; yyval.utype=yyvsp[-2].utype;;}
    break;

  case 11:
#line 193 "parse.y"
    { yyvsp[0].utype->factor *= -1; err = addunit(yyvsp[-2].utype,yyvsp[0].utype); 
                                         CHECK; yyval.utype=yyvsp[-2].utype;;}
    break;

  case 12:
#line 195 "parse.y"
    { err = divunit(yyvsp[-2].utype, yyvsp[0].utype); CHECK; yyval.utype=yyvsp[-2].utype;;}
    break;

  case 13:
#line 196 "parse.y"
    { err = multunit(yyvsp[-2].utype,yyvsp[0].utype); CHECK; yyval.utype=yyvsp[-2].utype;;}
    break;

  case 14:
#line 199 "parse.y"
    { yyval.number = yyvsp[0].number;         ;}
    break;

  case 15:
#line 200 "parse.y"
    { yyval.number = yyvsp[-2].number / yyvsp[0].number;    ;}
    break;

  case 16:
#line 203 "parse.y"
    { yyval.utype = yyvsp[-1].utype;  ;}
    break;

  case 17:
#line 209 "parse.y"
    { yyval.utype = makenumunit(yyvsp[0].number,&err); CHECK;;}
    break;

  case 18:
#line 210 "parse.y"
    { yyval.utype = yyvsp[0].utype; ;}
    break;

  case 19:
#line 211 "parse.y"
    { err = unitpower(yyvsp[-2].utype,yyvsp[0].utype); CHECK; yyval.utype=yyvsp[-2].utype;;}
    break;

  case 20:
#line 212 "parse.y"
    { err = multunit(yyvsp[-2].utype,yyvsp[0].utype); CHECK; yyval.utype=yyvsp[-2].utype;;}
    break;

  case 21:
#line 213 "parse.y"
    { err = multunit(yyvsp[-1].utype,yyvsp[0].utype); CHECK; yyval.utype=yyvsp[-1].utype;;}
    break;

  case 22:
#line 214 "parse.y"
    { yyval.utype=yyvsp[0].utype; ;}
    break;

  case 23:
#line 215 "parse.y"
    { err = rootunit(yyvsp[0].utype,2); CHECK; yyval.utype=yyvsp[0].utype;;}
    break;

  case 24:
#line 216 "parse.y"
    { err = rootunit(yyvsp[0].utype,3); CHECK; yyval.utype=yyvsp[0].utype;;}
    break;

  case 25:
#line 217 "parse.y"
    { err = funcunit(yyvsp[0].utype,yyvsp[-1].dfunc); CHECK; yyval.utype=yyvsp[0].utype;;}
    break;

  case 26:
#line 218 "parse.y"
    { err = evalfunc(yyvsp[0].utype,yyvsp[-1].ufunc,0); CHECK; yyval.utype=yyvsp[0].utype;;}
    break;

  case 27:
#line 219 "parse.y"
    { err = evalfunc(yyvsp[0].utype,yyvsp[-1].ufunc,1); CHECK; yyval.utype=yyvsp[0].utype;;}
    break;

  case 28:
#line 221 "parse.y"
    { yyvsp[0].utype->factor *= -1;
				   err = unitpower(yyvsp[-3].utype,yyvsp[0].utype); CHECK; yyval.utype=yyvsp[-3].utype;;}
    break;

  case 29:
#line 223 "parse.y"
    { err = E_PARSEMEM; CHECK; ;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 1325 "parse.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 229 "parse.y"


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




