/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 24 "SDCC.y"

#include <stdio.h>
#include <stdarg.h> 
#include <string.h>
#include "SDCCglobl.h"
#include "SDCCsymt.h"
#include "SDCChasht.h"
#include "SDCCval.h"
#include "SDCCmem.h"
#include "SDCCast.h"
#include "port.h"
#include "newalloc.h"
#include "SDCCerr.h"
#include "SDCCutil.h"

extern int yyerror (char *);
extern FILE	*yyin;
int NestLevel = 0 ;     /* current NestLevel       */
int stackPtr  = 1 ;     /* stack pointer           */
int xstackPtr = 0 ;     /* xstack pointer          */
int reentrant = 0 ; 
int blockNo   = 0 ;     /* sequential block number  */
int currBlockno=0 ;
int inCritical= 0 ;
int seqPointNo= 1 ;	/* sequence point number */
int ignoreTypedefType=0;
extern int yylex();
int yyparse(void);
extern int noLineno ;
char lbuff[1024];      /* local buffer */

/* break & continue stacks */
STACK_DCL(continueStack  ,symbol *,MAX_NEST_LEVEL)
STACK_DCL(breakStack  ,symbol *,MAX_NEST_LEVEL)
STACK_DCL(forStack  ,symbol *,MAX_NEST_LEVEL)
STACK_DCL(swStk   ,ast   *,MAX_NEST_LEVEL)
STACK_DCL(blockNum,int,MAX_NEST_LEVEL*3)

value *cenum = NULL  ;  /* current enumeration  type chain*/
bool uselessDecl = TRUE;

#define YYDEBUG 1



/* Line 268 of yacc.c  */
#line 117 "SDCCy.c"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     TYPE_NAME = 259,
     CONSTANT = 260,
     STRING_LITERAL = 261,
     SIZEOF = 262,
     TYPEOF = 263,
     PTR_OP = 264,
     INC_OP = 265,
     DEC_OP = 266,
     LEFT_OP = 267,
     RIGHT_OP = 268,
     LE_OP = 269,
     GE_OP = 270,
     EQ_OP = 271,
     NE_OP = 272,
     AND_OP = 273,
     OR_OP = 274,
     MUL_ASSIGN = 275,
     DIV_ASSIGN = 276,
     MOD_ASSIGN = 277,
     ADD_ASSIGN = 278,
     SUB_ASSIGN = 279,
     LEFT_ASSIGN = 280,
     RIGHT_ASSIGN = 281,
     AND_ASSIGN = 282,
     XOR_ASSIGN = 283,
     OR_ASSIGN = 284,
     TYPEDEF = 285,
     EXTERN = 286,
     STATIC = 287,
     AUTO = 288,
     REGISTER = 289,
     CODE = 290,
     EEPROM = 291,
     INTERRUPT = 292,
     SFR = 293,
     AT = 294,
     SBIT = 295,
     REENTRANT = 296,
     USING = 297,
     XDATA = 298,
     DATA = 299,
     IDATA = 300,
     PDATA = 301,
     VAR_ARGS = 302,
     CRITICAL = 303,
     NONBANKED = 304,
     BANKED = 305,
     CHAR = 306,
     SHORT = 307,
     INT = 308,
     LONG = 309,
     SIGNED = 310,
     UNSIGNED = 311,
     FLOAT = 312,
     DOUBLE = 313,
     CONST = 314,
     VOLATILE = 315,
     VOID = 316,
     BIT = 317,
     STRUCT = 318,
     UNION = 319,
     ENUM = 320,
     ELIPSIS = 321,
     RANGE = 322,
     FAR = 323,
     CASE = 324,
     DEFAULT = 325,
     IF = 326,
     ELSE = 327,
     SWITCH = 328,
     WHILE = 329,
     DO = 330,
     FOR = 331,
     GOTO = 332,
     CONTINUE = 333,
     BREAK = 334,
     RETURN = 335,
     NAKED = 336,
     JAVANATIVE = 337,
     OVERLAY = 338,
     INLINEASM = 339,
     IFX = 340,
     ADDRESS_OF = 341,
     GET_VALUE_AT_ADDRESS = 342,
     SPIL = 343,
     UNSPIL = 344,
     GETHBIT = 345,
     BITWISEAND = 346,
     UNARYMINUS = 347,
     IPUSH = 348,
     IPOP = 349,
     PCALL = 350,
     ENDFUNCTION = 351,
     JUMPTABLE = 352,
     RRC = 353,
     RLC = 354,
     CAST = 355,
     CALL = 356,
     PARAM = 357,
     NULLOP = 358,
     BLOCK = 359,
     LABEL = 360,
     RECEIVE = 361,
     SEND = 362,
     ARRAYINIT = 363,
     DUMMY_READ_VOLATILE = 364,
     ENDCRITICAL = 365,
     SWAP = 366
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define TYPE_NAME 259
#define CONSTANT 260
#define STRING_LITERAL 261
#define SIZEOF 262
#define TYPEOF 263
#define PTR_OP 264
#define INC_OP 265
#define DEC_OP 266
#define LEFT_OP 267
#define RIGHT_OP 268
#define LE_OP 269
#define GE_OP 270
#define EQ_OP 271
#define NE_OP 272
#define AND_OP 273
#define OR_OP 274
#define MUL_ASSIGN 275
#define DIV_ASSIGN 276
#define MOD_ASSIGN 277
#define ADD_ASSIGN 278
#define SUB_ASSIGN 279
#define LEFT_ASSIGN 280
#define RIGHT_ASSIGN 281
#define AND_ASSIGN 282
#define XOR_ASSIGN 283
#define OR_ASSIGN 284
#define TYPEDEF 285
#define EXTERN 286
#define STATIC 287
#define AUTO 288
#define REGISTER 289
#define CODE 290
#define EEPROM 291
#define INTERRUPT 292
#define SFR 293
#define AT 294
#define SBIT 295
#define REENTRANT 296
#define USING 297
#define XDATA 298
#define DATA 299
#define IDATA 300
#define PDATA 301
#define VAR_ARGS 302
#define CRITICAL 303
#define NONBANKED 304
#define BANKED 305
#define CHAR 306
#define SHORT 307
#define INT 308
#define LONG 309
#define SIGNED 310
#define UNSIGNED 311
#define FLOAT 312
#define DOUBLE 313
#define CONST 314
#define VOLATILE 315
#define VOID 316
#define BIT 317
#define STRUCT 318
#define UNION 319
#define ENUM 320
#define ELIPSIS 321
#define RANGE 322
#define FAR 323
#define CASE 324
#define DEFAULT 325
#define IF 326
#define ELSE 327
#define SWITCH 328
#define WHILE 329
#define DO 330
#define FOR 331
#define GOTO 332
#define CONTINUE 333
#define BREAK 334
#define RETURN 335
#define NAKED 336
#define JAVANATIVE 337
#define OVERLAY 338
#define INLINEASM 339
#define IFX 340
#define ADDRESS_OF 341
#define GET_VALUE_AT_ADDRESS 342
#define SPIL 343
#define UNSPIL 344
#define GETHBIT 345
#define BITWISEAND 346
#define UNARYMINUS 347
#define IPUSH 348
#define IPOP 349
#define PCALL 350
#define ENDFUNCTION 351
#define JUMPTABLE 352
#define RRC 353
#define RLC 354
#define CAST 355
#define CALL 356
#define PARAM 357
#define NULLOP 358
#define BLOCK 359
#define LABEL 360
#define RECEIVE 361
#define SEND 362
#define ARRAYINIT 363
#define DUMMY_READ_VOLATILE 364
#define ENDCRITICAL 365
#define SWAP 366




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 70 "SDCC.y"

    symbol     *sym ;      /* symbol table pointer       */
    structdef  *sdef;      /* structure definition       */
    char       yychar[SDCC_NAME_MAX+1];
    sym_link   *lnk ;      /* declarator  or specifier   */
    int        yyint;      /* integer value returned     */
    value      *val ;      /* for integer constant       */
    initList   *ilist;     /* initial list               */
    const char *yyinline;  /* inlined assembler code     */
    ast        *asts;      /* expression tree            */



/* Line 293 of yacc.c  */
#line 389 "SDCCy.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 401 "SDCCy.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  60
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1589

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  136
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  102
/* YYNRULES -- Number of rules.  */
#define YYNRULES  272
/* YYNRULES -- Number of states.  */
#define YYNSTATES  414

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   366

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   123,     2,     2,     2,   125,   118,     2,
     112,   113,   119,   120,   117,   121,   116,   124,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   131,   133,
     126,   132,   127,   130,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   114,     2,   115,   128,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   134,   129,   135,   122,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    15,    19,    21,
      24,    27,    29,    31,    33,    35,    37,    39,    41,    43,
      45,    48,    50,    52,    54,    58,    60,    62,    67,    71,
      76,    80,    84,    87,    90,    92,    96,    98,   101,   104,
     107,   110,   115,   118,   120,   122,   124,   126,   128,   130,
     132,   137,   139,   143,   147,   151,   153,   157,   161,   163,
     167,   171,   173,   177,   181,   185,   189,   191,   195,   199,
     201,   205,   207,   211,   213,   217,   219,   220,   225,   227,
     228,   233,   235,   236,   243,   245,   249,   251,   253,   255,
     257,   259,   261,   263,   265,   267,   269,   271,   273,   274,
     279,   281,   284,   288,   290,   293,   295,   298,   300,   304,
     306,   310,   312,   314,   316,   318,   320,   322,   325,   327,
     331,   333,   335,   337,   339,   341,   343,   345,   347,   349,
     351,   353,   355,   357,   359,   361,   363,   365,   367,   369,
     371,   373,   375,   377,   379,   382,   383,   390,   393,   395,
     397,   399,   400,   402,   404,   407,   411,   413,   417,   419,
     422,   426,   431,   437,   440,   442,   445,   449,   452,   455,
     456,   458,   461,   463,   465,   467,   470,   472,   475,   477,
     481,   485,   490,   494,   495,   501,   506,   508,   511,   514,
     518,   520,   522,   525,   527,   531,   533,   537,   539,   543,
     545,   549,   552,   554,   556,   559,   561,   563,   566,   570,
     573,   577,   581,   586,   589,   593,   597,   598,   604,   606,
     610,   615,   617,   621,   623,   625,   627,   629,   631,   633,
     635,   638,   640,   643,   646,   651,   652,   657,   659,   661,
     664,   668,   669,   674,   675,   681,   684,   686,   689,   691,
     694,   696,   699,   702,   703,   704,   712,   713,   720,   722,
     724,   726,   727,   734,   742,   752,   753,   755,   759,   762,
     765,   768,   772
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     137,     0,    -1,   138,    -1,   137,   138,    -1,   139,    -1,
     169,    -1,   194,   142,    -1,   170,   194,   142,    -1,   141,
      -1,   141,   140,    -1,    42,     5,    -1,    41,    -1,    48,
      -1,    81,    -1,    82,    -1,    83,    -1,    49,    -1,    50,
      -1,   174,    -1,   220,    -1,   223,   220,    -1,   237,    -1,
       5,    -1,   144,    -1,   112,   166,   113,    -1,     6,    -1,
     143,    -1,   145,   114,   166,   115,    -1,   145,   112,   113,
      -1,   145,   112,   146,   113,    -1,   145,   116,   237,    -1,
     145,     9,   237,    -1,   145,    10,    -1,   145,    11,    -1,
     164,    -1,   164,   117,   146,    -1,   145,    -1,    10,   147,
      -1,    11,   147,    -1,   148,   149,    -1,     7,   147,    -1,
       7,   112,   207,   113,    -1,     8,   147,    -1,   118,    -1,
     119,    -1,   120,    -1,   121,    -1,   122,    -1,   123,    -1,
     147,    -1,   112,   207,   113,   149,    -1,   149,    -1,   150,
     119,   149,    -1,   150,   124,   149,    -1,   150,   125,   149,
      -1,   150,    -1,   151,   120,   150,    -1,   151,   121,   150,
      -1,   151,    -1,   152,    12,   151,    -1,   152,    13,   151,
      -1,   152,    -1,   153,   126,   152,    -1,   153,   127,   152,
      -1,   153,    14,   152,    -1,   153,    15,   152,    -1,   153,
      -1,   154,    16,   153,    -1,   154,    17,   153,    -1,   154,
      -1,   155,   118,   154,    -1,   155,    -1,   156,   128,   155,
      -1,   156,    -1,   157,   129,   156,    -1,   157,    -1,    -1,
     158,    18,   159,   157,    -1,   158,    -1,    -1,   160,    19,
     161,   158,    -1,   160,    -1,    -1,   160,   130,   163,   160,
     131,   162,    -1,   162,    -1,   147,   165,   164,    -1,   132,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,    29,
      -1,   164,    -1,    -1,   166,   117,   167,   164,    -1,   162,
      -1,   170,   133,    -1,   170,   171,   133,    -1,   173,    -1,
     173,   170,    -1,   175,    -1,   175,   170,    -1,   172,    -1,
     171,   117,   172,    -1,   192,    -1,   192,   132,   211,    -1,
      30,    -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,
      37,    -1,    37,     5,    -1,   176,    -1,   176,    39,   168,
      -1,    51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,
      -1,    56,    -1,    61,    -1,    59,    -1,    60,    -1,    57,
      -1,    43,    -1,    35,    -1,    36,    -1,    44,    -1,    45,
      -1,    46,    -1,    62,    -1,   179,    -1,   188,    -1,     4,
      -1,   177,    -1,    40,    -1,   178,    -1,    38,    -1,    38,
      50,    -1,    -1,   181,   182,   180,   134,   184,   135,    -1,
     181,   183,    -1,    63,    -1,    64,    -1,   183,    -1,    -1,
     237,    -1,   185,    -1,   184,   185,    -1,   201,   186,   133,
      -1,   187,    -1,   186,   117,   187,    -1,   192,    -1,   131,
     168,    -1,   192,   131,   168,    -1,    65,   134,   189,   135,
      -1,    65,   237,   134,   189,   135,    -1,    65,   237,    -1,
     190,    -1,   189,   117,    -1,   189,   117,   190,    -1,   237,
     191,    -1,   132,   168,    -1,    -1,   193,    -1,   199,   193,
      -1,   195,    -1,   196,    -1,   195,    -1,   199,   195,    -1,
     197,    -1,   197,   140,    -1,   237,    -1,   112,   192,   113,
      -1,   193,   114,   115,    -1,   193,   114,   168,   115,    -1,
     196,   112,   113,    -1,    -1,   196,   112,   198,   204,   113,
      -1,   196,   112,   202,   113,    -1,   200,    -1,   200,   201,
      -1,   200,   199,    -1,   200,   201,   199,    -1,   119,    -1,
     175,    -1,   201,   175,    -1,   203,    -1,   203,   117,    66,
      -1,   237,    -1,   203,   117,   237,    -1,   205,    -1,   205,
     117,    47,    -1,   206,    -1,   205,   117,   206,    -1,   201,
     192,    -1,   207,    -1,   201,    -1,   201,   208,    -1,   199,
      -1,   209,    -1,   199,   209,    -1,   112,   208,   113,    -1,
     114,   115,    -1,   114,   168,   115,    -1,   209,   114,   115,
      -1,   209,   114,   168,   115,    -1,   112,   113,    -1,   112,
     204,   113,    -1,   209,   112,   113,    -1,    -1,   209,   112,
     210,   204,   113,    -1,   164,    -1,   134,   212,   135,    -1,
     134,   212,   117,   135,    -1,   211,    -1,   212,   117,   211,
      -1,   216,    -1,   220,    -1,   225,    -1,   227,    -1,   233,
      -1,   236,    -1,   215,    -1,    84,   133,    -1,    48,    -1,
     214,   213,    -1,   237,   131,    -1,    69,   168,   131,   213,
      -1,    -1,    70,   217,   131,   213,    -1,   134,    -1,   135,
      -1,   218,   219,    -1,   218,   224,   219,    -1,    -1,   218,
     223,   221,   219,    -1,    -1,   218,   223,   222,   224,   219,
      -1,     1,   133,    -1,   169,    -1,   223,   169,    -1,   213,
      -1,   224,   213,    -1,   133,    -1,   166,   133,    -1,    72,
     213,    -1,    -1,    -1,    71,   112,   166,   113,   228,   213,
     226,    -1,    -1,    73,   112,   166,   113,   229,   213,    -1,
      74,    -1,    75,    -1,    76,    -1,    -1,   230,   112,   166,
     113,   234,   213,    -1,   231,   213,    74,   112,   166,   113,
     133,    -1,   232,   112,   235,   133,   235,   133,   235,   113,
     213,    -1,    -1,   166,    -1,    77,   237,   133,    -1,    78,
     133,    -1,    79,   133,    -1,    80,   133,    -1,    80,   166,
     133,    -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   135,   135,   136,   140,   143,   169,   174,   183,   184,
     188,   192,   195,   198,   201,   204,   207,   213,   222,   231,
     232,   240,   241,   242,   243,   247,   251,   252,   253,   255,
     259,   266,   272,   274,   279,   280,   284,   285,   286,   287,
     288,   289,   290,   294,   295,   296,   297,   298,   299,   303,
     304,   308,   309,   310,   311,   315,   316,   317,   321,   322,
     323,   327,   328,   333,   338,   343,   351,   352,   357,   365,
     366,   370,   371,   375,   376,   380,   381,   381,   386,   387,
     387,   392,   393,   393,   401,   402,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   472,   473,   473,
     477,   481,   488,   506,   507,   520,   521,   537,   538,   542,
     543,   548,   552,   556,   560,   564,   571,   572,   585,   586,
     596,   601,   606,   611,   616,   621,   626,   631,   635,   639,
     644,   648,   652,   656,   660,   664,   668,   677,   682,   688,
     697,   701,   707,   711,   719,   731,   730,   777,   796,   797,
     801,   802,   809,   820,   821,   834,   860,   861,   869,   870,
     882,   901,   906,   923,   937,   938,   940,   956,   970,   983,
     998,   999,  1007,  1008,  1012,  1013,  1021,  1022,  1054,  1055,
    1056,  1065,  1088,  1089,  1089,  1115,  1125,  1126,  1137,  1143,
    1181,  1189,  1191,  1207,  1208,  1212,  1213,  1221,  1222,  1226,
    1227,  1235,  1245,  1254,  1255,  1272,  1273,  1274,  1281,  1282,
    1287,  1293,  1299,  1307,  1308,  1309,  1321,  1321,  1340,  1341,
    1342,  1346,  1347,  1351,  1352,  1353,  1354,  1355,  1356,  1357,
    1358,  1369,  1378,  1388,  1389,  1396,  1396,  1405,  1413,  1417,
    1418,  1420,  1419,  1423,  1422,  1426,  1430,  1442,  1467,  1468,
    1472,  1473,  1477,  1478,  1483,  1483,  1489,  1489,  1514,  1528,
    1543,  1562,  1562,  1570,  1579,  1607,  1608,  1612,  1617,  1630,
    1640,  1649,  1661
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "TYPE_NAME", "CONSTANT",
  "STRING_LITERAL", "SIZEOF", "TYPEOF", "PTR_OP", "INC_OP", "DEC_OP",
  "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPEDEF", "EXTERN", "STATIC", "AUTO", "REGISTER", "CODE",
  "EEPROM", "INTERRUPT", "SFR", "AT", "SBIT", "REENTRANT", "USING",
  "XDATA", "DATA", "IDATA", "PDATA", "VAR_ARGS", "CRITICAL", "NONBANKED",
  "BANKED", "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT",
  "DOUBLE", "CONST", "VOLATILE", "VOID", "BIT", "STRUCT", "UNION", "ENUM",
  "ELIPSIS", "RANGE", "FAR", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH",
  "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "NAKED",
  "JAVANATIVE", "OVERLAY", "INLINEASM", "IFX", "ADDRESS_OF",
  "GET_VALUE_AT_ADDRESS", "SPIL", "UNSPIL", "GETHBIT", "BITWISEAND",
  "UNARYMINUS", "IPUSH", "IPOP", "PCALL", "ENDFUNCTION", "JUMPTABLE",
  "RRC", "RLC", "CAST", "CALL", "PARAM", "NULLOP", "BLOCK", "LABEL",
  "RECEIVE", "SEND", "ARRAYINIT", "DUMMY_READ_VOLATILE", "ENDCRITICAL",
  "SWAP", "'('", "')'", "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'",
  "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'",
  "':'", "'='", "';'", "'{'", "'}'", "$accept", "file",
  "external_definition", "function_definition", "function_attribute",
  "function_attributes", "function_body", "primary_expr", "string_literal",
  "postfix_expr", "argument_expr_list", "unary_expr", "unary_operator",
  "cast_expr", "multiplicative_expr", "additive_expr", "shift_expr",
  "relational_expr", "equality_expr", "and_expr", "exclusive_or_expr",
  "inclusive_or_expr", "logical_and_expr", "$@1", "logical_or_expr", "$@2",
  "conditional_expr", "$@3", "assignment_expr", "assignment_operator",
  "expr", "$@4", "constant_expr", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "Interrupt_storage", "type_specifier", "type_specifier2", "sfr_reg_bit",
  "sfr_attributes", "struct_or_union_specifier", "$@5", "struct_or_union",
  "opt_stag", "stag", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "enum_specifier",
  "enumerator_list", "enumerator", "opt_assign_expr", "declarator",
  "declarator3", "function_declarator", "declarator2_function_attributes",
  "declarator2", "function_declarator2", "$@6", "pointer",
  "unqualified_pointer", "type_specifier_list",
  "parameter_identifier_list", "identifier_list", "parameter_type_list",
  "parameter_list", "parameter_declaration", "type_name",
  "abstract_declarator", "abstract_declarator2", "$@7", "initializer",
  "initializer_list", "statement", "critical", "critical_statement",
  "labeled_statement", "@8", "start_block", "end_block",
  "compound_statement", "$@9", "$@10", "declaration_list",
  "statement_list", "expression_statement", "else_statement",
  "selection_statement", "$@11", "@12", "while", "do", "for",
  "iteration_statement", "$@13", "expr_opt", "jump_statement",
  "identifier", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,    40,    41,    91,    93,    46,    44,    38,    42,
      43,    45,   126,    33,    47,    37,    60,    62,    94,   124,
      63,    58,    61,    59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   142,
     142,   143,   143,   143,   143,   144,   145,   145,   145,   145,
     145,   145,   145,   145,   146,   146,   147,   147,   147,   147,
     147,   147,   147,   148,   148,   148,   148,   148,   148,   149,
     149,   150,   150,   150,   150,   151,   151,   151,   152,   152,
     152,   153,   153,   153,   153,   153,   154,   154,   154,   155,
     155,   156,   156,   157,   157,   158,   159,   158,   160,   161,
     160,   162,   163,   162,   164,   164,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   166,   167,   166,
     168,   169,   169,   170,   170,   170,   170,   171,   171,   172,
     172,   173,   173,   173,   173,   173,   174,   174,   175,   175,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   177,   177,   178,   178,   180,   179,   179,   181,   181,
     182,   182,   183,   184,   184,   185,   186,   186,   187,   187,
     187,   188,   188,   188,   189,   189,   189,   190,   191,   191,
     192,   192,   193,   193,   194,   194,   195,   195,   196,   196,
     196,   196,   197,   198,   197,   197,   199,   199,   199,   199,
     200,   201,   201,   202,   202,   203,   203,   204,   204,   205,
     205,   206,   206,   207,   207,   208,   208,   208,   209,   209,
     209,   209,   209,   209,   209,   209,   210,   209,   211,   211,
     211,   212,   212,   213,   213,   213,   213,   213,   213,   213,
     213,   214,   215,   216,   216,   217,   216,   218,   219,   220,
     220,   221,   220,   222,   220,   220,   223,   223,   224,   224,
     225,   225,   226,   226,   228,   227,   229,   227,   230,   231,
     232,   234,   233,   233,   233,   235,   235,   236,   236,   236,
     236,   236,   237
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     3,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     3,     1,     1,     4,     3,     4,
       3,     3,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     4,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     0,     4,     1,     0,
       4,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     2,     3,     1,     2,     1,     2,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     6,     2,     1,     1,
       1,     0,     1,     1,     2,     3,     1,     3,     1,     2,
       3,     4,     5,     2,     1,     2,     3,     2,     2,     0,
       1,     2,     1,     1,     1,     2,     1,     2,     1,     3,
       3,     4,     3,     0,     5,     4,     1,     2,     2,     3,
       1,     1,     2,     1,     3,     1,     3,     1,     3,     1,
       3,     2,     1,     1,     2,     1,     1,     2,     3,     2,
       3,     3,     4,     2,     3,     3,     0,     5,     1,     3,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     2,     4,     0,     4,     1,     1,     2,
       3,     0,     4,     0,     5,     2,     1,     2,     1,     2,
       1,     2,     2,     0,     0,     7,     0,     6,     1,     1,
       1,     0,     6,     7,     9,     0,     1,     3,     2,     2,
       2,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   272,   139,   111,   112,   113,   114,   115,   131,   132,
     143,   141,   130,   133,   134,   135,   120,   121,   122,   123,
     124,   125,   129,   127,   128,   126,   136,   148,   149,     0,
       0,   190,     0,     2,     4,     5,     0,   103,   105,   118,
     140,   142,   137,   151,   138,     0,     0,   174,   173,   176,
       0,   186,   178,   144,     0,   163,     0,   170,   172,     0,
       1,     3,   101,     0,   107,   109,     0,     0,   104,   106,
       0,   145,   147,   152,     0,     0,   237,     6,   246,     0,
       0,    19,     0,   183,   116,    11,     0,    12,    16,    17,
      13,    14,    15,   177,     8,    18,   175,   191,   188,   187,
       0,   164,   169,     0,   179,   171,     0,   102,     0,     7,
      22,    25,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,    26,    23,    36,    49,     0,    51,    55,
      58,    61,    66,    69,    71,    73,    75,    78,    81,   100,
     119,    21,     0,   180,     0,   245,   231,     0,   235,     0,
       0,   258,   259,   260,     0,     0,     0,     0,     0,   250,
     238,    49,    84,    97,     0,   248,     0,   229,   223,   239,
     224,   243,     0,   225,   226,     0,     0,     0,   227,   228,
      21,   247,    20,   182,     0,     0,   193,   195,   117,    10,
       9,   192,   189,   165,   161,     0,   167,     0,   108,     0,
     218,   110,     0,    40,     0,    42,    37,    38,     0,   203,
       0,     0,    32,    33,     0,     0,     0,    39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,    79,    82,     0,   181,     0,
       0,     0,     0,     0,   268,   269,   270,     0,   230,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    86,
       0,    98,   251,   232,     0,     0,   249,   240,     0,     0,
     265,   233,   203,     0,   197,   199,   202,   185,     0,   166,
     168,   162,   221,     0,     0,    24,     0,     0,   205,   204,
     206,     0,    31,    28,     0,    34,     0,    30,    52,    53,
      54,    56,    57,    59,    60,    64,    65,    62,    63,    67,
      68,    70,    72,    74,     0,     0,     0,     0,   153,     0,
       0,     0,     0,     0,   267,   271,    85,     0,   242,     0,
       0,     0,   266,     0,     0,   201,   205,   184,     0,   194,
     196,     0,   219,    41,   213,     0,     0,   209,     0,   207,
     216,     0,    50,    29,     0,    27,    77,    80,     0,   146,
     154,     0,     0,   156,   158,   234,   236,   254,   256,    99,
     244,   261,     0,   265,   198,   200,   220,   222,   214,   208,
     210,   215,     0,   211,     0,    35,     0,   159,     0,   155,
       0,     0,     0,     0,     0,     0,     0,   212,    83,   157,
     160,   253,   257,   262,     0,   265,   217,     0,   255,   263,
       0,   252,     0,   264
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    32,    33,    34,    93,    94,    77,   123,   124,   125,
     294,   161,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   314,   138,   315,   162,   316,   163,   260,
     164,   327,   140,    78,    79,    63,    64,    37,    95,    97,
      39,    40,    41,    42,   142,    43,    71,    72,   317,   318,
     362,   363,    44,   100,   101,   196,    65,    57,    46,    58,
      48,    49,   184,    59,    51,   272,   185,   186,   345,   274,
     275,   276,   289,   290,   382,   201,   283,   165,   166,   167,
     168,   240,    80,   169,   170,   264,   265,    82,   172,   173,
     408,   174,   391,   392,   175,   176,   177,   178,   393,   333,
     179,   141
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -357
static const yytype_int16 yypact[] =
{
    1194,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,
     -12,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,     3,
      30,  -357,  1156,  -357,  -357,  -357,    15,  1448,  1448,   -13,
    -357,  -357,  -357,    50,  -357,   -49,   601,    65,   -30,   181,
      44,  1402,  -357,  -357,    50,    11,    -3,   -49,  -357,    44,
    -357,  -357,  -357,   -45,  -357,    29,   601,    44,  -357,  -357,
    1015,  -357,    21,  -357,   837,    17,  -357,  -357,  -357,    15,
     415,  -357,   601,    18,   115,  -357,   158,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,   181,  -357,    65,  -357,  -357,  1402,
     -77,  -357,    49,    50,  -357,   -49,    30,  -357,   747,  -357,
    -357,  -357,  1043,  1061,  1061,  1061,   940,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,  -357,    90,  -357,  1015,  -357,    -2,
      23,   140,    31,   172,    72,    66,    56,   185,     9,  -357,
    -357,  -357,    71,  -357,    94,  -357,  -357,  1015,  -357,   103,
     105,  -357,  -357,  -357,    50,    86,    87,   764,    92,  -357,
    -357,   349,  -357,  -357,   -15,  -357,   667,  -357,  -357,  -357,
    -357,   772,   495,  -357,  -357,   114,   667,   116,  -357,  -357,
      96,  -357,  -357,  -357,  1524,   119,   121,  -357,  -357,  -357,
    -357,  -357,  -357,    50,  -357,  1015,  -357,   -69,  -357,   747,
    -357,  -357,   940,  -357,  1015,  -357,  -357,  -357,   -53,  1358,
     120,    50,  -357,  -357,   921,  1015,    50,  -357,  1015,  1015,
    1015,  1015,  1015,  1015,  1015,  1015,  1015,  1015,  1015,  1015,
    1015,  1015,  1015,  1015,  -357,  -357,  -357,  1524,  -357,   111,
     125,  1015,  1015,   117,  -357,  -357,  -357,    34,  -357,  -357,
    -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,
    1015,  -357,  -357,  -357,   118,   667,  -357,  -357,  1015,   177,
    1015,  -357,  1276,   139,   141,  -357,  -357,  -357,    20,  -357,
    -357,  -357,  -357,   -62,   144,  -357,  1320,   958,   -44,  -357,
     -22,  1015,  -357,  -357,   146,   153,   -20,  -357,  -357,  -357,
    -357,    -2,    -2,    23,    23,   140,   140,   140,   140,    31,
      31,   172,    72,    66,  1015,  1015,  1015,   645,  -357,   858,
     667,   667,   -26,    -1,  -357,  -357,  -357,  1015,  -357,   495,
      61,   149,   154,   143,  1238,  -357,    16,  -357,  1491,  -357,
    -357,   395,  -357,  -357,  -357,   160,   161,  -357,   164,   -22,
     167,  1003,  -357,  -357,  1015,  -357,    56,   185,    -6,  -357,
    -357,  1015,    58,  -357,   151,  -357,  -357,  -357,  -357,  -357,
    -357,  -357,  1015,  1015,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,  -357,  1524,  -357,   168,  -357,  1015,  -357,    28,  -357,
    1015,   667,   667,   667,    67,   156,   171,  -357,  -357,  -357,
    -357,   214,  -357,  -357,   159,  1015,  -357,   667,  -357,  -357,
     174,  -357,   667,  -357
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -357,  -357,   261,  -357,   200,  -357,   230,  -357,  -357,  -357,
     -57,   122,  -357,  -105,   -14,   -24,    19,   -17,    69,    70,
      68,   -11,    -9,  -357,    -8,  -357,   -63,  -357,   -73,  -357,
    -106,  -357,   -66,    12,   133,  -357,   198,  -357,  -357,    39,
    -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,   -10,
    -357,   -79,  -357,   207,   123,  -357,   -29,     2,   276,    57,
    -357,  -357,  -357,     5,  -357,   -42,  -357,  -357,  -181,  -357,
     -25,   -91,  -271,  -261,  -357,  -195,  -357,  -152,  -357,  -357,
    -357,  -357,  -357,  -156,    -4,  -357,  -357,   234,    53,  -357,
    -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -356,
    -357,     0
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -242
static const yytype_int16 yytable[] =
{
      52,    56,    45,   273,   282,    50,     1,   139,   144,    99,
     208,   139,    35,   235,   263,   346,   267,   395,     1,     1,
     266,     1,   217,     1,   269,   210,    70,   349,   235,    55,
      52,     1,    52,     1,    45,   200,    52,    50,    53,    38,
     193,    67,    81,    73,    35,   225,   226,     1,   193,   410,
      52,   247,    45,     1,   102,   341,    98,    47,   194,    52,
     285,   105,    81,   346,   261,    74,   281,    52,   286,   105,
     287,    38,   106,   342,   209,   349,    38,    38,   182,    52,
     180,   239,    83,   187,   139,    38,   339,   367,   107,    47,
     350,   261,   351,    47,   181,   355,   208,   261,   208,   211,
     212,   213,   261,   102,   192,    38,    52,    96,   328,   296,
     104,   284,   368,   298,   299,   300,   261,   218,   262,    38,
     188,    38,   219,   220,    96,   386,   200,    30,   334,   280,
     287,   183,   139,    36,    31,   322,   323,    54,   191,   236,
      30,   295,    30,   221,   222,   103,   377,    31,    62,    31,
     145,   261,   223,   224,   243,  -150,    30,   227,   228,   361,
     209,   108,   330,   189,   332,    36,   180,   325,   365,   366,
      68,    69,   180,   370,   371,   388,   180,   266,   261,  -172,
     404,   195,  -172,   181,   261,   233,   352,   326,   229,   230,
     231,   389,   126,   102,   232,   319,   126,  -172,  -172,   303,
     304,   396,   214,   234,   215,   237,   216,   301,   302,   238,
      38,   292,   309,   310,   288,   241,   297,   242,    84,   244,
     245,   348,    85,    86,   139,   248,   268,   271,   270,    87,
      88,    89,   277,   291,   203,   205,   206,   207,   278,   401,
     402,   403,   320,   335,   305,   306,   307,   308,   191,   126,
     324,   331,   337,   160,   369,   411,   321,   343,   338,   353,
     413,   372,    90,    91,    92,   180,   394,   332,   200,   126,
     354,   261,    52,   378,   379,   319,   373,   336,   340,   380,
     381,   295,   390,   397,   406,   384,   407,   412,   139,   405,
     364,   288,   409,    61,   190,   387,   109,   385,   139,   332,
     311,   313,   312,   356,   198,    56,   357,   360,   358,   399,
     197,   191,    66,   375,   171,     0,   279,   126,   329,    52,
     180,   180,     0,   398,   400,     0,     0,   139,     0,   180,
       0,     0,     0,     0,    52,     0,    52,     0,   105,   336,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,     0,     0,   191,   364,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    52,     0,
       0,   180,   180,   180,     0,     0,     0,     0,     1,     0,
     110,   111,   112,   113,     0,   114,   115,   180,     0,   126,
       0,     0,   180,   126,     0,     0,    75,     0,     1,     2,
     110,   111,   112,   113,     0,   114,   115,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   126,   126,   126,     0,
       0,     0,     0,     0,     0,     3,     4,     5,     6,     7,
       8,     9,     0,    10,     0,    11,     0,     0,    12,    13,
      14,    15,     0,   146,     0,     0,    16,    17,    18,    19,
      20,    21,    22,   126,    23,    24,    25,    26,    27,    28,
      29,   259,     0,   126,   147,   148,   149,     0,   150,   151,
     152,   153,   154,   155,   156,   157,    75,     0,     1,   158,
     110,   111,   112,   113,     0,   114,   115,   116,   126,     0,
       0,     0,   126,   117,   118,   119,   120,   121,   122,     0,
       0,     0,     0,     0,     0,     0,     0,   116,     0,   199,
     376,     0,     0,   117,   118,   119,   120,   121,   122,     0,
       0,     0,     0,   146,     0,     0,     0,     0,   159,    76,
     160,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   148,   149,     0,   150,   151,
     152,   153,   154,   155,   156,   157,     0,     0,     0,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     2,     0,   116,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,   122,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,    76,
     160,     3,     4,     5,     6,     7,     8,     9,     0,    10,
       0,    11,     0,     0,    12,    13,    14,    15,     0,     2,
       0,     0,    16,    17,    18,    19,    20,    21,    22,     0,
      23,    24,    25,    26,    27,    28,    29,     0,    75,     0,
       1,     0,   110,   111,   112,   113,     0,   114,   115,     0,
       8,     9,     0,    10,     0,    11,     0,     0,    12,    13,
      14,    15,     0,     0,     0,     0,    16,    17,    18,    19,
      20,    21,    22,     0,    23,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,   146,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,   147,   148,   149,     0,
     150,   151,   152,   153,   154,   155,   156,   157,     0,     0,
       1,   158,   110,   111,   112,   113,     0,   114,   115,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,   110,
     111,   112,   113,     0,   114,   115,     2,     0,     0,   116,
     359,     0,     0,     0,     0,   117,   118,   119,   120,   121,
     122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     159,    76,     3,     4,     5,     6,     7,     8,     9,     0,
      10,     0,    11,     0,     0,    12,    13,    14,    15,     0,
       0,     0,     0,    16,    17,    18,    19,    20,    21,    22,
       0,    23,    24,    25,    26,    27,    28,    29,     0,     0,
       1,     0,   110,   111,   112,   113,     0,   114,   115,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   116,
       0,     1,     2,     0,     0,   117,   118,   119,   120,   121,
     122,     0,     0,     0,     0,     0,   116,     0,     0,     0,
       0,   199,   117,   118,   119,   120,   121,   122,     0,     0,
       0,     0,     0,     8,     9,     0,    10,   246,    11,     0,
       0,    12,    13,    14,    15,     0,     0,  -241,     0,    16,
      17,    18,    19,    20,    21,    22,     0,    23,    24,    25,
      26,    27,    28,    29,     1,     0,   110,   111,   112,   113,
       0,   114,   115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,   110,   111,   112,   113,   116,
     114,   115,   143,     0,     0,   117,   118,   119,   120,   121,
     122,     1,     0,   110,   111,   112,   113,     0,   114,   115,
      30,     0,     0,     0,     0,     8,     9,    31,    10,     0,
      11,     0,     0,    12,    13,    14,    15,     0,     0,   361,
       0,    16,    17,    18,    19,    20,    21,    22,     0,    23,
      24,    25,    26,    27,    28,    29,     1,     0,   110,   111,
     112,   113,     0,   114,   115,     0,     0,     0,     1,     0,
     110,   111,   112,   113,     0,   114,   115,     0,     0,     0,
       0,     0,     0,   116,   293,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,     0,     1,     0,   110,   111,
     112,   113,   116,   114,   115,     0,     0,     0,   117,   118,
     119,   120,   121,   122,     1,     0,   110,   111,   112,   113,
     116,   114,   115,   347,     0,     0,   117,   118,   119,   120,
     121,   122,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   116,     0,     0,   383,     0,
       0,   117,   118,   119,   120,   121,   122,   116,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,   122,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   202,    60,     0,     0,     1,
       2,   117,   118,   119,   120,   121,   122,     0,     0,     0,
       0,     0,     0,   204,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,     0,     3,     4,     5,     6,
       7,     8,     9,     0,    10,     0,    11,     1,     2,    12,
      13,    14,    15,     0,     0,     0,     0,    16,    17,    18,
      19,    20,    21,    22,     0,    23,    24,    25,    26,    27,
      28,    29,     0,     0,     3,     4,     5,     6,     7,     8,
       9,     0,    10,     0,    11,     0,     0,    12,    13,    14,
      15,     1,     2,     0,     0,    16,    17,    18,    19,    20,
      21,    22,     0,    23,    24,    25,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,     0,     0,    30,     0,
       0,     0,     0,     8,     9,    31,    10,     0,    11,     1,
       2,    12,    13,    14,    15,     0,     0,     0,     0,    16,
      17,    18,    19,    20,    21,    22,     0,    23,    24,    25,
      26,    27,    28,    29,     0,     0,    30,     0,     0,     0,
       0,     8,     9,    31,    10,     0,    11,     0,     0,    12,
      13,    14,    15,     0,     2,     0,     0,    16,    17,    18,
      19,    20,    21,    22,     0,    23,    24,    25,    26,    27,
      28,    29,     0,     0,     0,     0,     0,     0,     0,     0,
     334,   344,   287,     0,     0,     8,     9,    31,    10,     0,
      11,     0,     2,    12,    13,    14,    15,     0,     0,     0,
       0,    16,    17,    18,    19,    20,    21,    22,     0,    23,
      24,    25,    26,    27,    28,    29,     0,     0,   334,     0,
     287,     0,     0,     8,     9,    31,    10,     0,    11,     0,
       0,    12,    13,    14,    15,     0,     2,     0,     0,    16,
      17,    18,    19,    20,    21,    22,     0,    23,    24,    25,
      26,    27,    28,    29,     0,     0,     0,     0,     0,     0,
       0,     0,   286,   344,   287,     0,     0,     8,     9,    31,
      10,     0,    11,     0,     0,    12,    13,    14,    15,     0,
       0,     0,     2,    16,    17,    18,    19,    20,    21,    22,
       0,    23,    24,    25,    26,    27,    28,    29,     0,     0,
     286,     0,   287,     0,     0,     0,     0,    31,     3,     4,
       5,     6,     7,     8,     9,     0,    10,     0,    11,     0,
       0,    12,    13,    14,    15,     2,     0,     0,     0,    16,
      17,    18,    19,    20,    21,    22,     0,    23,    24,    25,
      26,    27,    28,    29,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,     0,     8,     9,     2,    10,
       0,    11,     0,     0,    12,    13,    14,    15,   374,     0,
       0,     0,    16,    17,    18,    19,    20,    21,    22,     0,
      23,    24,    25,    26,    27,    28,    29,     0,     0,     8,
       9,     0,    10,     0,    11,     0,     0,    12,    13,    14,
      15,     0,     0,     0,     0,    16,    17,    18,    19,    20,
      21,    22,     0,    23,    24,    25,    26,    27,    28,    29
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-357))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    30,     0,   184,   199,     0,     3,    70,    74,    51,
     116,    74,     0,    19,   166,   286,   172,   373,     3,     3,
     172,     3,   127,     3,   176,   116,    39,   288,    19,    29,
      30,     3,    32,     3,    32,   108,    36,    32,    50,     0,
     117,    36,    46,    43,    32,    14,    15,     3,   117,   405,
      50,   157,    50,     3,    54,   117,    51,     0,   135,    59,
     113,    59,    66,   334,   117,   114,   135,    67,   112,    67,
     114,    32,   117,   135,   116,   336,    37,    38,    82,    79,
      80,   147,   112,    83,   147,    46,    66,   113,   133,    32,
     112,   117,   114,    36,    82,   115,   202,   117,   204,     9,
      10,    11,   117,   103,    99,    66,   106,    50,   264,   215,
     113,   202,   113,   218,   219,   220,   117,   119,   133,    80,
       5,    82,   124,   125,    67,   131,   199,   112,   112,   195,
     114,   113,   195,     0,   119,   241,   242,   134,    99,   130,
     112,   214,   112,   120,   121,   134,   341,   119,   133,   119,
     133,   117,    12,    13,   154,   134,   112,   126,   127,   131,
     202,   132,   268,     5,   270,    32,   166,   133,   320,   321,
      37,    38,   172,   329,   113,   117,   176,   329,   117,   114,
     113,   132,   117,   171,   117,   129,   291,   260,    16,    17,
     118,   133,    70,   193,   128,   237,    74,   132,   133,   223,
     224,   382,   112,    18,   114,   134,   116,   221,   222,   115,
     171,   211,   229,   230,   209,   112,   216,   112,    37,   133,
     133,   287,    41,    42,   287,   133,   112,   131,   112,    48,
      49,    50,   113,   113,   112,   113,   114,   115,   117,   391,
     392,   393,   131,   272,   225,   226,   227,   228,   209,   127,
     133,    74,   113,   135,   327,   407,   131,   113,   117,   113,
     412,   112,    81,    82,    83,   265,   372,   373,   341,   147,
     117,   117,   272,   113,   113,   317,   133,   272,   278,   115,
     113,   354,   131,   115,   113,   351,    72,   113,   351,   133,
     319,   286,   133,    32,    94,   361,    66,   354,   361,   405,
     231,   233,   232,   314,   106,   334,   315,   317,   316,   388,
     103,   272,    36,   338,    80,    -1,   193,   195,   265,   319,
     320,   321,    -1,   386,   390,    -1,    -1,   390,    -1,   329,
      -1,    -1,    -1,    -1,   334,    -1,   336,    -1,   336,   334,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,    -1,    -1,   319,   388,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   388,    -1,
      -1,   391,   392,   393,    -1,    -1,    -1,    -1,     3,    -1,
       5,     6,     7,     8,    -1,    10,    11,   407,    -1,   287,
      -1,    -1,   412,   291,    -1,    -1,     1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   314,   315,   316,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    38,    -1,    40,    -1,    -1,    43,    44,
      45,    46,    -1,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,   351,    59,    60,    61,    62,    63,    64,
      65,   132,    -1,   361,    69,    70,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    80,     1,    -1,     3,    84,
       5,     6,     7,     8,    -1,    10,    11,   112,   386,    -1,
      -1,    -1,   390,   118,   119,   120,   121,   122,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   134,
     135,    -1,    -1,   118,   119,   120,   121,   122,   123,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,   133,   134,
     135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,     4,    -1,   112,    -1,    -1,
      -1,    -1,    -1,   118,   119,   120,   121,   122,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,   134,
     135,    30,    31,    32,    33,    34,    35,    36,    -1,    38,
      -1,    40,    -1,    -1,    43,    44,    45,    46,    -1,     4,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    63,    64,    65,    -1,     1,    -1,
       3,    -1,     5,     6,     7,     8,    -1,    10,    11,    -1,
      35,    36,    -1,    38,    -1,    40,    -1,    -1,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   134,    69,    70,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
       3,    84,     5,     6,     7,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
       6,     7,     8,    -1,    10,    11,     4,    -1,    -1,   112,
     135,    -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,
     123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     133,   134,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    -1,    40,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    62,    63,    64,    65,    -1,    -1,
       3,    -1,     5,     6,     7,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
      -1,     3,     4,    -1,    -1,   118,   119,   120,   121,   122,
     123,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,
      -1,   134,   118,   119,   120,   121,   122,   123,    -1,    -1,
      -1,    -1,    -1,    35,    36,    -1,    38,   133,    40,    -1,
      -1,    43,    44,    45,    46,    -1,    -1,   135,    -1,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      62,    63,    64,    65,     3,    -1,     5,     6,     7,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,   112,
      10,    11,   115,    -1,    -1,   118,   119,   120,   121,   122,
     123,     3,    -1,     5,     6,     7,     8,    -1,    10,    11,
     112,    -1,    -1,    -1,    -1,    35,    36,   119,    38,    -1,
      40,    -1,    -1,    43,    44,    45,    46,    -1,    -1,   131,
      -1,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    63,    64,    65,     3,    -1,     5,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,     3,    -1,
       5,     6,     7,     8,    -1,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,   112,   113,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,   123,    -1,     3,    -1,     5,     6,
       7,     8,   112,    10,    11,    -1,    -1,    -1,   118,   119,
     120,   121,   122,   123,     3,    -1,     5,     6,     7,     8,
     112,    10,    11,   115,    -1,    -1,   118,   119,   120,   121,
     122,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,   115,    -1,
      -1,   118,   119,   120,   121,   122,   123,   112,    -1,    -1,
      -1,    -1,    -1,   118,   119,   120,   121,   122,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,     0,    -1,    -1,     3,
       4,   118,   119,   120,   121,   122,   123,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,   123,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,    -1,    40,     3,     4,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    38,    -1,    40,    -1,    -1,    43,    44,    45,
      46,     3,     4,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    35,    36,   119,    38,    -1,    40,     3,
       4,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    35,    36,   119,    38,    -1,    40,    -1,    -1,    43,
      44,    45,    46,    -1,     4,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,   113,   114,    -1,    -1,    35,    36,   119,    38,    -1,
      40,    -1,     4,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    63,    64,    65,    -1,    -1,   112,    -1,
     114,    -1,    -1,    35,    36,   119,    38,    -1,    40,    -1,
      -1,    43,    44,    45,    46,    -1,     4,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   112,   113,   114,    -1,    -1,    35,    36,   119,
      38,    -1,    40,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,     4,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    62,    63,    64,    65,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,   119,    30,    31,
      32,    33,    34,    35,    36,    -1,    38,    -1,    40,    -1,
      -1,    43,    44,    45,    46,     4,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   119,    -1,    -1,    -1,    -1,    35,    36,     4,    38,
      -1,    40,    -1,    -1,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    63,    64,    65,    -1,    -1,    35,
      36,    -1,    38,    -1,    40,    -1,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    63,    64,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    30,    31,    32,    33,    34,    35,    36,
      38,    40,    43,    44,    45,    46,    51,    52,    53,    54,
      55,    56,    57,    59,    60,    61,    62,    63,    64,    65,
     112,   119,   137,   138,   139,   169,   170,   173,   175,   176,
     177,   178,   179,   181,   188,   193,   194,   195,   196,   197,
     199,   200,   237,    50,   134,   237,   192,   193,   195,   199,
       0,   138,   133,   171,   172,   192,   194,   199,   170,   170,
      39,   182,   183,   237,   114,     1,   134,   142,   169,   170,
     218,   220,   223,   112,    37,    41,    42,    48,    49,    50,
      81,    82,    83,   140,   141,   174,   195,   175,   199,   201,
     189,   190,   237,   134,   113,   193,   117,   133,   132,   142,
       5,     6,     7,     8,    10,    11,   112,   118,   119,   120,
     121,   122,   123,   143,   144,   145,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   160,   162,
     168,   237,   180,   115,   168,   133,    48,    69,    70,    71,
      73,    74,    75,    76,    77,    78,    79,    80,    84,   133,
     135,   147,   162,   164,   166,   213,   214,   215,   216,   219,
     220,   223,   224,   225,   227,   230,   231,   232,   233,   236,
     237,   169,   220,   113,   198,   202,   203,   237,     5,     5,
     140,   175,   199,   117,   135,   132,   191,   189,   172,   134,
     164,   211,   112,   147,   112,   147,   147,   147,   166,   201,
     207,     9,    10,    11,   112,   114,   116,   149,   119,   124,
     125,   120,   121,    12,    13,    14,    15,   126,   127,    16,
      17,   118,   128,   129,    18,    19,   130,   134,   115,   168,
     217,   112,   112,   237,   133,   133,   133,   166,   133,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,   132,
     165,   117,   133,   213,   221,   222,   213,   219,   112,   213,
     112,   131,   201,   204,   205,   206,   207,   113,   117,   190,
     168,   135,   211,   212,   207,   113,   112,   114,   199,   208,
     209,   113,   237,   113,   146,   164,   166,   237,   149,   149,
     149,   150,   150,   151,   151,   152,   152,   152,   152,   153,
     153,   154,   155,   156,   159,   161,   163,   184,   185,   201,
     131,   131,   166,   166,   133,   133,   164,   167,   219,   224,
     166,    74,   166,   235,   112,   192,   199,   113,   117,    66,
     237,   117,   135,   113,   113,   204,   208,   115,   168,   209,
     112,   114,   149,   113,   117,   115,   157,   158,   160,   135,
     185,   131,   186,   187,   192,   213,   213,   113,   113,   164,
     219,   113,   112,   133,    47,   206,   135,   211,   113,   113,
     115,   113,   210,   115,   168,   146,   131,   168,   117,   133,
     131,   228,   229,   234,   166,   235,   204,   115,   162,   187,
     168,   213,   213,   213,   113,   133,   113,    72,   226,   133,
     235,   213,   113,   213
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
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
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
        case 4:

/* Line 1806 of yacc.c  */
#line 140 "SDCC.y"
    { 
                               blockNo=0;
                             }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 143 "SDCC.y"
    { 
			       ignoreTypedefType = 0;
			       if ((yyvsp[(1) - (1)].sym) && (yyvsp[(1) - (1)].sym)->type
				&& IS_FUNC((yyvsp[(1) - (1)].sym)->type))
			       {
 				   /* The only legal storage classes for 
				    * a function prototype (declaration)
				    * are extern and static. extern is the
				    * default. Thus, if this function isn't
				    * explicitly marked static, mark it
				    * extern.
				    */
				   if ((yyvsp[(1) - (1)].sym)->etype 
				    && IS_SPEC((yyvsp[(1) - (1)].sym)->etype)
				    && !SPEC_STAT((yyvsp[(1) - (1)].sym)->etype))
				   {
				   	SPEC_EXTR((yyvsp[(1) - (1)].sym)->etype) = 1;
				   }
			       }
                               addSymChain ((yyvsp[(1) - (1)].sym));
                               allocVariables ((yyvsp[(1) - (1)].sym)) ;
			       cleanUpLevel (SymbolTab,1);
                             }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 169 "SDCC.y"
    {   /* function type not specified */
                                   /* assume it to be 'int'       */
                                   addDecl((yyvsp[(1) - (2)].sym),0,newIntLink());
				   (yyval.asts) = createFunction((yyvsp[(1) - (2)].sym),(yyvsp[(2) - (2)].asts)); 
                               }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 175 "SDCC.y"
    {   
				    pointerTypes((yyvsp[(2) - (3)].sym)->type,copyLinkChain((yyvsp[(1) - (3)].lnk)));
				    addDecl((yyvsp[(2) - (3)].sym),0,(yyvsp[(1) - (3)].lnk)); 
				    (yyval.asts) = createFunction((yyvsp[(2) - (3)].sym),(yyvsp[(3) - (3)].asts));   
				}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 184 "SDCC.y"
    { (yyval.lnk) = mergeSpec((yyvsp[(1) - (2)].lnk),(yyvsp[(2) - (2)].lnk),"function_attribute"); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 188 "SDCC.y"
    {
                        (yyval.lnk) = newLink(SPECIFIER) ;
			FUNC_REGBANK((yyval.lnk)) = (int) floatFromVal((yyvsp[(2) - (2)].val));
                     }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 192 "SDCC.y"
    {  (yyval.lnk) = newLink (SPECIFIER);
			FUNC_ISREENT((yyval.lnk))=1;
                     }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 195 "SDCC.y"
    {  (yyval.lnk) = newLink (SPECIFIER);
			FUNC_ISCRITICAL((yyval.lnk)) = 1;
                     }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 198 "SDCC.y"
    {  (yyval.lnk) = newLink (SPECIFIER);
			FUNC_ISNAKED((yyval.lnk))=1;
                     }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 201 "SDCC.y"
    {  (yyval.lnk) = newLink (SPECIFIER);
			FUNC_ISJAVANATIVE((yyval.lnk))=1;
                     }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 204 "SDCC.y"
    {  (yyval.lnk) = newLink (SPECIFIER);
			FUNC_ISOVERLAY((yyval.lnk))=1;
                     }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 207 "SDCC.y"
    {(yyval.lnk) = newLink (SPECIFIER);
                        FUNC_NONBANKED((yyval.lnk)) = 1;
			if (FUNC_BANKED((yyval.lnk))) {
			    werror(W_BANKED_WITH_NONBANKED);
			}
                     }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 213 "SDCC.y"
    {(yyval.lnk) = newLink (SPECIFIER);
                        FUNC_BANKED((yyval.lnk)) = 1;
			if (FUNC_NONBANKED((yyval.lnk))) {
			    werror(W_BANKED_WITH_NONBANKED);
			}
			if (SPEC_STAT((yyval.lnk))) {
			    werror(W_BANKED_WITH_STATIC);
			}
                     }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 223 "SDCC.y"
    {
                        (yyval.lnk) = newLink (SPECIFIER) ;
                        FUNC_INTNO((yyval.lnk)) = (yyvsp[(1) - (1)].yyint) ;
                        FUNC_ISISR((yyval.lnk)) = 1;
                     }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 233 "SDCC.y"
    {
            werror(E_OLD_STYLE,((yyvsp[(1) - (2)].sym) ? (yyvsp[(1) - (2)].sym)->name: "")) ;
	    exit(1);
         }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 240 "SDCC.y"
    {  (yyval.asts) = newAst_VALUE(symbolVal((yyvsp[(1) - (1)].sym)));  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 241 "SDCC.y"
    {  (yyval.asts) = newAst_VALUE((yyvsp[(1) - (1)].val));  }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 243 "SDCC.y"
    {  (yyval.asts) = (yyvsp[(2) - (3)].asts) ;                   }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 247 "SDCC.y"
    { (yyval.asts) = newAst_VALUE((yyvsp[(1) - (1)].val)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 252 "SDCC.y"
    { (yyval.asts) = newNode	('[', (yyvsp[(1) - (4)].asts), (yyvsp[(3) - (4)].asts)) ; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 253 "SDCC.y"
    { (yyval.asts) = newNode  (CALL,(yyvsp[(1) - (3)].asts),NULL); 
                                          (yyval.asts)->left->funcName = 1;}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 256 "SDCC.y"
    { 	   
	    (yyval.asts) = newNode  (CALL,(yyvsp[(1) - (4)].asts),(yyvsp[(3) - (4)].asts)) ; (yyval.asts)->left->funcName = 1;
	  }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 260 "SDCC.y"
    {    
			(yyvsp[(3) - (3)].sym) = newSymbol((yyvsp[(3) - (3)].sym)->name,NestLevel);
			(yyvsp[(3) - (3)].sym)->implicit = 1;
			(yyval.asts) = newNode(PTR_OP,newNode('&',(yyvsp[(1) - (3)].asts),NULL),newAst_VALUE(symbolVal((yyvsp[(3) - (3)].sym))));
/* 			$$ = newNode('.',$1,newAst(EX_VALUE,symbolVal($3))) ;		        */
		      }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 267 "SDCC.y"
    { 
			(yyvsp[(3) - (3)].sym) = newSymbol((yyvsp[(3) - (3)].sym)->name,NestLevel);
			(yyvsp[(3) - (3)].sym)->implicit = 1;			
			(yyval.asts) = newNode(PTR_OP,(yyvsp[(1) - (3)].asts),newAst_VALUE(symbolVal((yyvsp[(3) - (3)].sym))));
		      }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 273 "SDCC.y"
    {	(yyval.asts) = newNode(INC_OP,(yyvsp[(1) - (2)].asts),NULL);}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 275 "SDCC.y"
    {	(yyval.asts) = newNode(DEC_OP,(yyvsp[(1) - (2)].asts),NULL); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 280 "SDCC.y"
    { (yyval.asts) = newNode(PARAM,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 285 "SDCC.y"
    { (yyval.asts) = newNode(INC_OP,NULL,(yyvsp[(2) - (2)].asts));  }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 286 "SDCC.y"
    { (yyval.asts) = newNode(DEC_OP,NULL,(yyvsp[(2) - (2)].asts));  }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 287 "SDCC.y"
    { (yyval.asts) = newNode((yyvsp[(1) - (2)].yyint),(yyvsp[(2) - (2)].asts),NULL)    ;  }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 288 "SDCC.y"
    { (yyval.asts) = newNode(SIZEOF,NULL,(yyvsp[(2) - (2)].asts));  }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 289 "SDCC.y"
    { (yyval.asts) = newAst_VALUE(sizeofOp((yyvsp[(3) - (4)].lnk))); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 290 "SDCC.y"
    { (yyval.asts) = newNode(TYPEOF,NULL,(yyvsp[(2) - (2)].asts));  }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 294 "SDCC.y"
    { (yyval.yyint) = '&' ;}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 295 "SDCC.y"
    { (yyval.yyint) = '*' ;}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 296 "SDCC.y"
    { (yyval.yyint) = '+' ;}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 297 "SDCC.y"
    { (yyval.yyint) = '-' ;}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 298 "SDCC.y"
    { (yyval.yyint) = '~' ;}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 299 "SDCC.y"
    { (yyval.yyint) = '!' ;}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 304 "SDCC.y"
    { (yyval.asts) = newNode(CAST,newAst_LINK((yyvsp[(2) - (4)].lnk)),(yyvsp[(4) - (4)].asts)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 309 "SDCC.y"
    { (yyval.asts) = newNode('*',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 310 "SDCC.y"
    { (yyval.asts) = newNode('/',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 311 "SDCC.y"
    { (yyval.asts) = newNode('%',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 316 "SDCC.y"
    { (yyval.asts)=newNode('+',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 317 "SDCC.y"
    { (yyval.asts)=newNode('-',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 322 "SDCC.y"
    { (yyval.asts) = newNode(LEFT_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 323 "SDCC.y"
    { (yyval.asts) = newNode(RIGHT_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 328 "SDCC.y"
    { 
	(yyval.asts) = (port->lt_nge ? 
	      newNode('!',newNode(GE_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)),NULL) :
	      newNode('<', (yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)));
   }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 333 "SDCC.y"
    { 
	   (yyval.asts) = (port->gt_nle ? 
		 newNode('!',newNode(LE_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)),NULL) :
		 newNode('>',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)));
   }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 338 "SDCC.y"
    { 
	   (yyval.asts) = (port->le_ngt ? 
		 newNode('!', newNode('>', (yyvsp[(1) - (3)].asts) , (yyvsp[(3) - (3)].asts) ), NULL) :
		 newNode(LE_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)));
   }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 343 "SDCC.y"
    { 
	   (yyval.asts) = (port->ge_nlt ? 
		 newNode('!', newNode('<', (yyvsp[(1) - (3)].asts) , (yyvsp[(3) - (3)].asts) ), NULL) :
		 newNode(GE_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)));
   }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 352 "SDCC.y"
    { 
    (yyval.asts) = (port->eq_nne ? 
	  newNode('!',newNode(NE_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)),NULL) : 
	  newNode(EQ_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)));
   }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 357 "SDCC.y"
    { 
       (yyval.asts) = (port->ne_neq ? 
	     newNode('!', newNode(EQ_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)), NULL) : 
	     newNode(NE_OP,(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts)));
   }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 366 "SDCC.y"
    { (yyval.asts) = newNode('&',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 371 "SDCC.y"
    { (yyval.asts) = newNode('^',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 376 "SDCC.y"
    { (yyval.asts) = newNode('|',(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 381 "SDCC.y"
    { seqPointNo++;}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 382 "SDCC.y"
    { (yyval.asts) = newNode(AND_OP,(yyvsp[(1) - (4)].asts),(yyvsp[(4) - (4)].asts));}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 387 "SDCC.y"
    { seqPointNo++;}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 388 "SDCC.y"
    { (yyval.asts) = newNode(OR_OP,(yyvsp[(1) - (4)].asts),(yyvsp[(4) - (4)].asts)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 393 "SDCC.y"
    { seqPointNo++;}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 394 "SDCC.y"
    {
                        (yyval.asts) = newNode(':',(yyvsp[(4) - (6)].asts),(yyvsp[(6) - (6)].asts)) ;
                        (yyval.asts) = newNode('?',(yyvsp[(1) - (6)].asts),(yyval.asts)) ;
                     }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 403 "SDCC.y"
    { 
				 
			     switch ((yyvsp[(2) - (3)].yyint)) {
			     case '=':
				     (yyval.asts) = newNode((yyvsp[(2) - (3)].yyint),(yyvsp[(1) - (3)].asts),(yyvsp[(3) - (3)].asts));
				     break;
			     case MUL_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode('*',removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case DIV_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode('/',removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case MOD_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode('%',removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case ADD_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode('+',removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case SUB_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode('-',removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case LEFT_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode(LEFT_OP,removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case RIGHT_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode(RIGHT_OP,removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case AND_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode('&',removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case XOR_ASSIGN:
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode('^',removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     case OR_ASSIGN:
				     /* $$ = newNode('=',$1,newNode('|',removeIncDecOps(copyAst($1)),$3)); */
				     (yyval.asts) = newNode('=',removePostIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),
                                                      newNode('|',removePreIncDecOps(copyAst((yyvsp[(1) - (3)].asts))),(yyvsp[(3) - (3)].asts)));
				     break;
			     default :
				     (yyval.asts) = NULL;
			     }
				     
                     }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 458 "SDCC.y"
    { (yyval.yyint) = '=' ;}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 473 "SDCC.y"
    { seqPointNo++;}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 473 "SDCC.y"
    { (yyval.asts) = newNode(',',(yyvsp[(1) - (4)].asts),(yyvsp[(4) - (4)].asts));}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 482 "SDCC.y"
    {
         if (uselessDecl)
           werror(W_USELESS_DECL);
         uselessDecl = TRUE;
         (yyval.sym) = NULL ;
      }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 489 "SDCC.y"
    {
         /* add the specifier list to the id */
         symbol *sym , *sym1;

         for (sym1 = sym = reverseSyms((yyvsp[(2) - (3)].sym));sym != NULL;sym = sym->next) {
	     sym_link *lnk = copyLinkChain((yyvsp[(1) - (3)].lnk));
	     /* do the pointer stuff */
	     pointerTypes(sym->type,lnk);
	     addDecl (sym,0,lnk) ;
	 }
        
         uselessDecl = TRUE;
	 (yyval.sym) = sym1 ;
      }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 506 "SDCC.y"
    { (yyval.lnk) = (yyvsp[(1) - (1)].lnk); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 507 "SDCC.y"
    { 
     /* if the decl $2 is not a specifier */
     /* find the spec and replace it      */
     if ( !IS_SPEC((yyvsp[(2) - (2)].lnk))) {
       sym_link *lnk = (yyvsp[(2) - (2)].lnk) ;
       while (lnk && !IS_SPEC(lnk->next))
	 lnk = lnk->next;
       lnk->next = mergeSpec((yyvsp[(1) - (2)].lnk),lnk->next, "storage_class_specifier declaration_specifiers - skipped");
       (yyval.lnk) = (yyvsp[(2) - (2)].lnk) ;
     }
     else
       (yyval.lnk) = mergeSpec((yyvsp[(1) - (2)].lnk),(yyvsp[(2) - (2)].lnk), "storage_class_specifier declaration_specifiers");
   }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 520 "SDCC.y"
    { (yyval.lnk) = (yyvsp[(1) - (1)].lnk); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 521 "SDCC.y"
    { 
     /* if the decl $2 is not a specifier */
     /* find the spec and replace it      */
     if ( !IS_SPEC((yyvsp[(2) - (2)].lnk))) {
       sym_link *lnk = (yyvsp[(2) - (2)].lnk) ;
       while (lnk && !IS_SPEC(lnk->next))
	 lnk = lnk->next;
       lnk->next = mergeSpec((yyvsp[(1) - (2)].lnk),lnk->next, "type_specifier declaration_specifiers - skipped");
       (yyval.lnk) = (yyvsp[(2) - (2)].lnk) ;
     }
     else
       (yyval.lnk) = mergeSpec((yyvsp[(1) - (2)].lnk),(yyvsp[(2) - (2)].lnk), "type_specifier declaration_specifiers");
   }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 538 "SDCC.y"
    { (yyvsp[(3) - (3)].sym)->next = (yyvsp[(1) - (3)].sym) ; (yyval.sym) = (yyvsp[(3) - (3)].sym);}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 542 "SDCC.y"
    { (yyvsp[(1) - (1)].sym)->ival = NULL ; }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 543 "SDCC.y"
    { (yyvsp[(1) - (3)].sym)->ival = (yyvsp[(3) - (3)].ilist)   ; }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 548 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_TYPEDEF((yyval.lnk)) = 1 ;
               }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 552 "SDCC.y"
    {
                  (yyval.lnk) = newLink(SPECIFIER);
                  SPEC_EXTR((yyval.lnk)) = 1 ;
               }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 556 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_STAT((yyval.lnk)) = 1 ;
               }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 560 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_SCLS((yyval.lnk)) = S_AUTO  ;
               }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 564 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_REGISTER ;
               }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 571 "SDCC.y"
    { (yyval.yyint) = INTNO_UNSPEC ; }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 573 "SDCC.y"
    { int intno = (int) floatFromVal((yyvsp[(2) - (2)].val));
          if ((intno >= 0) && (intno <= INTNO_MAX))
            (yyval.yyint) = intno;
          else
            {
              werror(E_INT_BAD_INTNO, intno);
              (yyval.yyint) = INTNO_UNSPEC;
            }
        }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 587 "SDCC.y"
    {
	   /* add this to the storage class specifier  */
           SPEC_ABSA((yyvsp[(1) - (3)].lnk)) = 1;   /* set the absolute addr flag */
           /* now get the abs addr from value */
           SPEC_ADDR((yyvsp[(1) - (3)].lnk)) = (int) floatFromVal(constExprValue((yyvsp[(3) - (3)].asts),TRUE)) ;
        }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 596 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
               SPEC_NOUN((yyval.lnk)) = V_CHAR  ;
	       ignoreTypedefType = 1;
            }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 601 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
	       (yyval.lnk)->select.s._short = 1 ;
	       ignoreTypedefType = 1;
            }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 606 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
               SPEC_NOUN((yyval.lnk)) = V_INT   ;
	       ignoreTypedefType = 1;
            }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 611 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
	       SPEC_LONG((yyval.lnk)) = 1       ;
	       ignoreTypedefType = 1;
            }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 616 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
               (yyval.lnk)->select.s._signed = 1;
	       ignoreTypedefType = 1;
            }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 621 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
               SPEC_USIGN((yyval.lnk)) = 1      ;
	       ignoreTypedefType = 1;
            }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 626 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
               SPEC_NOUN((yyval.lnk)) = V_VOID  ;
	       ignoreTypedefType = 1;
            }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 631 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
	       SPEC_CONST((yyval.lnk)) = 1;
            }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 635 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
	       SPEC_VOLATILE((yyval.lnk)) = 1 ;
            }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 639 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
	       SPEC_NOUN((yyval.lnk)) = V_FLOAT;
	       ignoreTypedefType = 1;
            }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 644 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_XDATA  ;
               }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 648 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_SCLS((yyval.lnk)) = S_CODE ;                 
               }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 652 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER) ;
                  SPEC_SCLS((yyval.lnk)) = S_EEPROM ;
               }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 656 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_DATA   ;
               }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 660 "SDCC.y"
    {
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_IDATA  ;
               }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 664 "SDCC.y"
    { 
                  (yyval.lnk) = newLink (SPECIFIER);
                  SPEC_SCLS((yyval.lnk)) = S_PDATA  ;
               }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 668 "SDCC.y"
    {
               (yyval.lnk)=newLink(SPECIFIER);
               SPEC_NOUN((yyval.lnk)) = V_BIT   ;
	       SPEC_SCLS((yyval.lnk)) = S_BIT   ;
	       SPEC_BLEN((yyval.lnk)) = 1;
	       SPEC_BSTR((yyval.lnk)) = 0;
	       ignoreTypedefType = 1;
            }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 677 "SDCC.y"
    {
                                   uselessDecl = FALSE;
                                   (yyval.lnk) = (yyvsp[(1) - (1)].lnk) ;
	                           ignoreTypedefType = 1;
                                }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 682 "SDCC.y"
    {                           
                           cenum = NULL ;
                           uselessDecl = FALSE;
                           ignoreTypedefType = 1;
                           (yyval.lnk) = (yyvsp[(1) - (1)].lnk) ;                              
                        }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 689 "SDCC.y"
    {
            symbol *sym;
            sym_link   *p  ;
            sym = findSym(TypedefTab,NULL,(yyvsp[(1) - (1)].yychar)) ;
            (yyval.lnk) = p = copyLinkChain(sym->type);
	    SPEC_TYPEDEF(getSpec(p)) = 0;
            ignoreTypedefType = 1;
         }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 701 "SDCC.y"
    {
               (yyval.lnk) = newLink(SPECIFIER) ;
               SPEC_NOUN((yyval.lnk)) = V_SBIT;
               SPEC_SCLS((yyval.lnk)) = S_SBIT;
	       ignoreTypedefType = 1;
            }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 711 "SDCC.y"
    {
               (yyval.lnk) = newLink(SPECIFIER) ;
               FUNC_REGBANK((yyval.lnk)) = 0;
               SPEC_NOUN((yyval.lnk))    = V_CHAR;
               SPEC_SCLS((yyval.lnk))    = S_SFR ;
               SPEC_USIGN((yyval.lnk))   = 1 ;
	       ignoreTypedefType = 1;
            }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 719 "SDCC.y"
    {
               (yyval.lnk) = newLink(SPECIFIER) ;
               FUNC_REGBANK((yyval.lnk)) = 1;
               SPEC_NOUN((yyval.lnk))    = V_CHAR;
               SPEC_SCLS((yyval.lnk))    = S_SFR ;
               SPEC_USIGN((yyval.lnk))   = 1 ;
	       ignoreTypedefType = 1;
            }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 731 "SDCC.y"
    {
           if (!(yyvsp[(2) - (2)].sdef)->type)
             {
               (yyvsp[(2) - (2)].sdef)->type = (yyvsp[(1) - (2)].yyint);
             }
           else
             {
               if ((yyvsp[(2) - (2)].sdef)->type != (yyvsp[(1) - (2)].yyint))
                 werror(E_BAD_TAG, (yyvsp[(2) - (2)].sdef)->tag, (yyvsp[(1) - (2)].yyint)==STRUCT ? "struct" : "union");
             }

	}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 744 "SDCC.y"
    {
           structdef *sdef ;
	   symbol *sym, *dsym;

	   // check for errors in structure members
	   for (sym=(yyvsp[(5) - (6)].sym); sym; sym=sym->next) {
	     if (IS_ABSOLUTE(sym->etype)) {
	       werrorfl(sym->fileDef, sym->lineDef, E_NOT_ALLOWED, "'at'");
	       SPEC_ABSA(sym->etype) = 0;
	     }
	     if (IS_SPEC(sym->etype) && SPEC_SCLS(sym->etype)) {
	       werrorfl(sym->fileDef, sym->lineDef, E_NOT_ALLOWED, "storage class");
	       printTypeChainRaw (sym->type,NULL);
	       SPEC_SCLS(sym->etype) = 0;
	     }
	     for (dsym=sym->next; dsym; dsym=dsym->next) {
	       if (strcmp(sym->name, dsym->name)==0) {
		 werrorfl(sym->fileDef, sym->lineDef, E_DUPLICATE_MEMBER, 
			(yyvsp[(1) - (6)].yyint)==STRUCT ? "struct" : "union", sym->name);
	       }
	     }
	   }

           /* Create a structdef   */	   
           sdef = (yyvsp[(2) - (6)].sdef) ;
           sdef->fields   = reverseSyms((yyvsp[(5) - (6)].sym)) ;   /* link the fields */
           sdef->size  = compStructSize((yyvsp[(1) - (6)].yyint),sdef);   /* update size of  */

           /* Create the specifier */
           (yyval.lnk) = newLink (SPECIFIER) ;
           SPEC_NOUN((yyval.lnk)) = V_STRUCT;
           SPEC_STRUCT((yyval.lnk))= sdef ;
        }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 778 "SDCC.y"
    {
            (yyval.lnk) = newLink(SPECIFIER) ;
            SPEC_NOUN((yyval.lnk)) = V_STRUCT;
            SPEC_STRUCT((yyval.lnk)) = (yyvsp[(2) - (2)].sdef);

           if (!(yyvsp[(2) - (2)].sdef)->type)
             {
               (yyvsp[(2) - (2)].sdef)->type = (yyvsp[(1) - (2)].yyint);
             }
           else
             {
               if ((yyvsp[(2) - (2)].sdef)->type != (yyvsp[(1) - (2)].yyint))
                 werror(E_BAD_TAG, (yyvsp[(2) - (2)].sdef)->tag, (yyvsp[(1) - (2)].yyint)==STRUCT ? "struct" : "union");
             }
         }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 796 "SDCC.y"
    { (yyval.yyint) = STRUCT ; }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 797 "SDCC.y"
    { (yyval.yyint) = UNION  ; }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 802 "SDCC.y"
    {  /* synthesize a name add to structtable */
     (yyval.sdef) = newStruct(genSymName(NestLevel)) ;
     (yyval.sdef)->level = NestLevel ;
     addSym (StructTab, (yyval.sdef), (yyval.sdef)->tag,(yyval.sdef)->level,currBlockno, 0);
}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 809 "SDCC.y"
    {  /* add name to structure table */
     (yyval.sdef) = findSymWithBlock (StructTab,(yyvsp[(1) - (1)].sym),currBlockno);
     if (! (yyval.sdef) ) {
       (yyval.sdef) = newStruct((yyvsp[(1) - (1)].sym)->name) ;
       (yyval.sdef)->level = NestLevel ;
       addSym (StructTab, (yyval.sdef), (yyval.sdef)->tag,(yyval.sdef)->level,currBlockno,0);
     }
}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 822 "SDCC.y"
    {
	   symbol *sym=(yyvsp[(2) - (2)].sym);

	   /* go to the end of the chain */
	   while (sym->next) sym=sym->next;
           sym->next = (yyvsp[(1) - (2)].sym) ;
	 
           (yyval.sym) = (yyvsp[(2) - (2)].sym);
       }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 835 "SDCC.y"
    {
           /* add this type to all the symbols */
           symbol *sym ;
           for ( sym = (yyvsp[(2) - (3)].sym) ; sym != NULL ; sym = sym->next ) {
	       sym_link *btype = copyLinkChain((yyvsp[(1) - (3)].lnk));
	       
	       /* make the symbol one level up */
	       sym->level-- ;

	       pointerTypes(sym->type,btype);
	       if (!sym->type) {
		   sym->type = btype;
		   sym->etype = getSpec(sym->type);
	       }
	       else
		 addDecl (sym,0,btype);
	       /* make sure the type is complete and sane */
	       checkTypeSanity(sym->etype, sym->name);
	   }
	   ignoreTypedefType = 0;
	   (yyval.sym) = (yyvsp[(2) - (3)].sym);
       }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 862 "SDCC.y"
    {
           (yyvsp[(3) - (3)].sym)->next  = (yyvsp[(1) - (3)].sym) ;
           (yyval.sym) = (yyvsp[(3) - (3)].sym) ;
       }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 870 "SDCC.y"
    {
                           int bitsize;
                           (yyval.sym) = newSymbol (genSymName(NestLevel),NestLevel) ; 
                           bitsize= (int) floatFromVal(constExprValue((yyvsp[(2) - (2)].asts),TRUE));
                           if (bitsize > (port->s.int_size * 8)) {
                             bitsize = port->s.int_size * 8;
                             werror(E_BITFLD_SIZE, bitsize);
                           }
                           if (!bitsize)
                             bitsize = BITVAR_PAD;
                           (yyval.sym)->bitVar = bitsize;
                        }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 883 "SDCC.y"
    {
                          int bitsize;
                          bitsize= (int) floatFromVal(constExprValue((yyvsp[(3) - (3)].asts),TRUE));
                          if (bitsize > (port->s.int_size * 8)) {
                            bitsize = port->s.int_size * 8;
                            werror(E_BITFLD_SIZE, bitsize);
                          }
                          if (!bitsize) {
                            (yyval.sym) = newSymbol (genSymName(NestLevel),NestLevel) ; 
                            (yyval.sym)->bitVar = BITVAR_PAD;
                            werror(W_BITFLD_NAMED);
                          }
			  else
			    (yyvsp[(1) - (3)].sym)->bitVar = bitsize;
                        }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 901 "SDCC.y"
    {
	   (yyval.lnk) = newEnumType ((yyvsp[(3) - (4)].sym));	//copyLinkChain(cenum->type);
	   SPEC_SCLS(getSpec((yyval.lnk))) = 0;
         }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 906 "SDCC.y"
    {
     symbol *csym ;
     sym_link *enumtype;

     csym=findSym(enumTab,(yyvsp[(2) - (5)].sym),(yyvsp[(2) - (5)].sym)->name);
     if ((csym && csym->level == (yyvsp[(2) - (5)].sym)->level))
       werrorfl((yyvsp[(2) - (5)].sym)->fileDef, (yyvsp[(2) - (5)].sym)->lineDef, E_DUPLICATE_TYPEDEF,csym->name);
     
     enumtype = newEnumType ((yyvsp[(4) - (5)].sym));	//copyLinkChain(cenum->type);
     SPEC_SCLS(getSpec(enumtype)) = 0;
     (yyvsp[(2) - (5)].sym)->type = enumtype;
     
     /* add this to the enumerator table */
     if (!csym)
       addSym ( enumTab,(yyvsp[(2) - (5)].sym),(yyvsp[(2) - (5)].sym)->name,(yyvsp[(2) - (5)].sym)->level,(yyvsp[(2) - (5)].sym)->block, 0);
     (yyval.lnk) = copyLinkChain(enumtype);
   }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 923 "SDCC.y"
    {
     symbol *csym ;
     
     /* check the enumerator table */
     if ((csym = findSym(enumTab,(yyvsp[(2) - (2)].sym),(yyvsp[(2) - (2)].sym)->name)))
       (yyval.lnk) = copyLinkChain(csym->type);
     else  {
       (yyval.lnk) = newLink(SPECIFIER) ;
       SPEC_NOUN((yyval.lnk)) = V_INT   ;
     }
   }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 938 "SDCC.y"
    {
                         }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 941 "SDCC.y"
    {
       symbol *dsym;
       
       for (dsym=(yyvsp[(1) - (3)].sym); dsym; dsym=dsym->next)
         {
	   if (strcmp((yyvsp[(3) - (3)].sym)->name, dsym->name)==0)
	     werrorfl((yyvsp[(3) - (3)].sym)->fileDef, (yyvsp[(3) - (3)].sym)->lineDef, E_DUPLICATE_MEMBER, "enum", (yyvsp[(3) - (3)].sym)->name);
	 }
       
       (yyvsp[(3) - (3)].sym)->next = (yyvsp[(1) - (3)].sym) ;
       (yyval.sym) = (yyvsp[(3) - (3)].sym)  ;
     }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 957 "SDCC.y"
    {
       /* make the symbol one level up */
       (yyvsp[(1) - (2)].sym)->level-- ;
       (yyvsp[(1) - (2)].sym)->type = copyLinkChain((yyvsp[(2) - (2)].val)->type); 
       (yyvsp[(1) - (2)].sym)->etype= getSpec((yyvsp[(1) - (2)].sym)->type);
       SPEC_ENUM((yyvsp[(1) - (2)].sym)->etype) = 1;
       (yyval.sym) = (yyvsp[(1) - (2)].sym) ;
       // do this now, so we can use it for the next enums in the list
       addSymChain((yyvsp[(1) - (2)].sym));
     }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 970 "SDCC.y"
    {
                              value *val ;

                              val = constExprValue((yyvsp[(2) - (2)].asts),TRUE);
			      if (!IS_INT(val->type) && !IS_CHAR(val->type))
			        {
				  werror(E_ENUM_NON_INTEGER);
				  SNPRINTF(lbuff, sizeof(lbuff), 
				 	  "%d",(int) floatFromVal(val));
				  val = constVal(lbuff);
				}
                              (yyval.val) = cenum = val ;
                           }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 983 "SDCC.y"
    {                              
                              if (cenum)  {
                                 SNPRINTF(lbuff, sizeof(lbuff), 
				 	  "%d",(int) floatFromVal(cenum)+1);
                                 (yyval.val) = cenum = constVal(lbuff);
                              }
                              else {
                                 SNPRINTF(lbuff, sizeof(lbuff), 
				          "%d",0);
                                 (yyval.val) = cenum = constVal(lbuff);
                              }   
                           }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 998 "SDCC.y"
    { (yyval.sym) = (yyvsp[(1) - (1)].sym) ; }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 1000 "SDCC.y"
    {
	     addDecl ((yyvsp[(2) - (2)].sym),0,reverseLink((yyvsp[(1) - (2)].lnk)));
	     (yyval.sym) = (yyvsp[(2) - (2)].sym) ;
         }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 1007 "SDCC.y"
    { (yyval.sym) = (yyvsp[(1) - (1)].sym) ; }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 1008 "SDCC.y"
    { (yyval.sym) = (yyvsp[(1) - (1)].sym) ; }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 1012 "SDCC.y"
    { (yyval.sym) = (yyvsp[(1) - (1)].sym); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 1014 "SDCC.y"
    {
	     addDecl ((yyvsp[(2) - (2)].sym),0,reverseLink((yyvsp[(1) - (2)].lnk)));
	     (yyval.sym) = (yyvsp[(2) - (2)].sym) ;
         }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 1021 "SDCC.y"
    { (yyval.sym) = (yyvsp[(1) - (1)].sym) ; }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 1022 "SDCC.y"
    { 
           // copy the functionAttributes (not the args and hasVargs !!)
           struct value *args;
           unsigned hasVargs;
           sym_link *funcType=(yyvsp[(1) - (2)].sym)->type;

	   while (funcType && !IS_FUNC(funcType))
	     funcType = funcType->next;
	   
	   if (!funcType)
	     werror (E_FUNC_ATTR);
	   else
	     {
	       args=FUNC_ARGS(funcType);
               hasVargs=FUNC_HASVARARGS(funcType);

               memcpy (&funcType->funcAttrs, &(yyvsp[(2) - (2)].lnk)->funcAttrs, 
    	           sizeof((yyvsp[(2) - (2)].lnk)->funcAttrs));

               FUNC_ARGS(funcType)=args;
               FUNC_HASVARARGS(funcType)=hasVargs;

               // just to be sure
               memset (&(yyvsp[(2) - (2)].lnk)->funcAttrs, 0,
    	           sizeof((yyvsp[(2) - (2)].lnk)->funcAttrs));
           
               addDecl ((yyvsp[(1) - (2)].sym),0,(yyvsp[(2) - (2)].lnk)); 
	     }
   }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 1055 "SDCC.y"
    { (yyval.sym) = (yyvsp[(2) - (3)].sym); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 1057 "SDCC.y"
    {
            sym_link   *p;

            p = newLink (DECLARATOR);
            DCL_TYPE(p) = ARRAY ;
            DCL_ELEM(p) = 0     ;
            addDecl((yyvsp[(1) - (3)].sym),0,p);
         }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1066 "SDCC.y"
    {
            sym_link   *p ;
			value *tval;
			
            tval = constExprValue((yyvsp[(3) - (4)].asts),TRUE);
            /* if it is not a constant then Error  */
            p = newLink (DECLARATOR);
            DCL_TYPE(p) = ARRAY ;
            if ( !tval || (SPEC_SCLS(tval->etype) != S_LITERAL)) {
               werror(E_CONST_EXPECTED) ;
               /* Assume a single item array to limit the cascade */
               /* of additional errors. */
               DCL_ELEM(p) = 1;
            }
            else {
               DCL_ELEM(p) = (int) floatFromVal(tval) ;
            }		                
            addDecl((yyvsp[(1) - (4)].sym),0,p);
         }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 1088 "SDCC.y"
    {  addDecl ((yyvsp[(1) - (3)].sym),FUNCTION,NULL) ;   }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 1089 "SDCC.y"
    { NestLevel++ ; currBlockno++;  }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1091 "SDCC.y"
    {
             sym_link *funcType;
	   
	     addDecl ((yyvsp[(1) - (5)].sym),FUNCTION,NULL) ;

	     funcType = (yyvsp[(1) - (5)].sym)->type;
	     while (funcType && !IS_FUNC(funcType))
	       funcType = funcType->next;
	   
	     assert (funcType);
	     
	     FUNC_HASVARARGS(funcType) = IS_VARG((yyvsp[(4) - (5)].val));
	     FUNC_ARGS(funcType) = reverseVal((yyvsp[(4) - (5)].val));
	     
	     /* nest level was incremented to take care of the parms  */
	     NestLevel-- ;
	     currBlockno--;

	     // if this was a pointer (to a function)
	     if (!IS_FUNC((yyvsp[(1) - (5)].sym)->type))
	       cleanUpLevel(SymbolTab,NestLevel+1);
	     
	     (yyval.sym) = (yyvsp[(1) - (5)].sym);
         }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 1116 "SDCC.y"
    {	   
	   werror(E_OLD_STYLE,(yyvsp[(1) - (4)].sym)->name) ;	  
	   /* assume it returns an int */
	   (yyvsp[(1) - (4)].sym)->type = (yyvsp[(1) - (4)].sym)->etype = newIntLink();
	   (yyval.sym) = (yyvsp[(1) - (4)].sym) ;
         }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 1125 "SDCC.y"
    { (yyval.lnk) = (yyvsp[(1) - (1)].lnk) ;}
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 1127 "SDCC.y"
    {
	     (yyval.lnk) = (yyvsp[(1) - (2)].lnk)  ;
             if (IS_SPEC((yyvsp[(2) - (2)].lnk))) {
	         DCL_TSPEC((yyvsp[(1) - (2)].lnk)) = (yyvsp[(2) - (2)].lnk);
                 DCL_PTR_CONST((yyvsp[(1) - (2)].lnk)) = SPEC_CONST((yyvsp[(2) - (2)].lnk));
                 DCL_PTR_VOLATILE((yyvsp[(1) - (2)].lnk)) = SPEC_VOLATILE((yyvsp[(2) - (2)].lnk));
             }
             else
                 werror (W_PTR_TYPE_INVALID);
	 }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 1138 "SDCC.y"
    {
	     (yyval.lnk) = (yyvsp[(1) - (2)].lnk) ;		
	     (yyval.lnk)->next = (yyvsp[(2) - (2)].lnk) ;
	     DCL_TYPE((yyvsp[(2) - (2)].lnk))=port->unqualified_pointer;
	 }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1144 "SDCC.y"
    {
	     (yyval.lnk) = (yyvsp[(1) - (3)].lnk) ;  	     
	     if (IS_SPEC((yyvsp[(2) - (3)].lnk)) && DCL_TYPE((yyvsp[(3) - (3)].lnk)) == UPOINTER) {
		 DCL_PTR_CONST((yyvsp[(1) - (3)].lnk)) = SPEC_CONST((yyvsp[(2) - (3)].lnk));
		 DCL_PTR_VOLATILE((yyvsp[(1) - (3)].lnk)) = SPEC_VOLATILE((yyvsp[(2) - (3)].lnk));
		 switch (SPEC_SCLS((yyvsp[(2) - (3)].lnk))) {
		 case S_XDATA:
		     DCL_TYPE((yyvsp[(3) - (3)].lnk)) = FPOINTER;
		     break;
		 case S_IDATA:
		     DCL_TYPE((yyvsp[(3) - (3)].lnk)) = IPOINTER ;
		     break;
		 case S_PDATA:
		     DCL_TYPE((yyvsp[(3) - (3)].lnk)) = PPOINTER ;
		     break;
		 case S_DATA:
		     DCL_TYPE((yyvsp[(3) - (3)].lnk)) = POINTER ;
		     break;
		 case S_CODE:
		     DCL_TYPE((yyvsp[(3) - (3)].lnk)) = CPOINTER ;
		     break;
		 case S_EEPROM:
		     DCL_TYPE((yyvsp[(3) - (3)].lnk)) = EEPPOINTER;
		     break;
		 default:
		   // this could be just "constant" 
		   // werror(W_PTR_TYPE_INVALID);
		     ;
		 }
	     }
	     else 
		 werror (W_PTR_TYPE_INVALID);
	     (yyval.lnk)->next = (yyvsp[(3) - (3)].lnk) ;
	 }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 1182 "SDCC.y"
    {
	(yyval.lnk) = newLink(DECLARATOR);
	DCL_TYPE((yyval.lnk))=UPOINTER;
      }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 1191 "SDCC.y"
    {
     /* if the decl $2 is not a specifier */
     /* find the spec and replace it      */
     if ( !IS_SPEC((yyvsp[(2) - (2)].lnk))) {
       sym_link *lnk = (yyvsp[(2) - (2)].lnk) ;
       while (lnk && !IS_SPEC(lnk->next))
	 lnk = lnk->next;
       lnk->next = mergeSpec((yyvsp[(1) - (2)].lnk),lnk->next, "type_specifier_list type_specifier skipped");
       (yyval.lnk) = (yyvsp[(2) - (2)].lnk) ;
     }
     else
       (yyval.lnk) = mergeSpec((yyvsp[(1) - (2)].lnk),(yyvsp[(2) - (2)].lnk), "type_specifier_list type_specifier");
   }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 1214 "SDCC.y"
    {            
	   (yyvsp[(3) - (3)].sym)->next = (yyvsp[(1) - (3)].sym);
	   (yyval.sym) = (yyvsp[(3) - (3)].sym) ;
         }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 1222 "SDCC.y"
    { (yyvsp[(1) - (3)].val)->vArgs = 1;}
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 1228 "SDCC.y"
    {
            (yyvsp[(3) - (3)].val)->next = (yyvsp[(1) - (3)].val) ;
            (yyval.val) = (yyvsp[(3) - (3)].val) ;
         }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1236 "SDCC.y"
    {	
		  symbol *loop ;
		  pointerTypes((yyvsp[(2) - (2)].sym)->type,(yyvsp[(1) - (2)].lnk));
                  addDecl ((yyvsp[(2) - (2)].sym),0,(yyvsp[(1) - (2)].lnk));		  
		  for (loop=(yyvsp[(2) - (2)].sym);loop;loop->_isparm=1,loop=loop->next);
		  addSymChain ((yyvsp[(2) - (2)].sym));
		  (yyval.val) = symbolVal((yyvsp[(2) - (2)].sym));
		  ignoreTypedefType = 0;
               }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1245 "SDCC.y"
    { 
                  (yyval.val) = newValue() ; 
                  (yyval.val)->type = (yyvsp[(1) - (1)].lnk);
                  (yyval.val)->etype = getSpec((yyval.val)->type);
                  ignoreTypedefType = 0;
               }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1254 "SDCC.y"
    { (yyval.lnk) = (yyvsp[(1) - (1)].lnk); ignoreTypedefType = 0;}
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1256 "SDCC.y"
    {
		 /* go to the end of the list */
		 sym_link *p;
		 pointerTypes((yyvsp[(2) - (2)].lnk),(yyvsp[(1) - (2)].lnk));
		 for ( p = (yyvsp[(2) - (2)].lnk) ; p && p->next ; p=p->next);
		 if (!p) {
		   werror(E_SYNTAX_ERROR, yytext);
		 } else {
		   p->next = (yyvsp[(1) - (2)].lnk) ;
		 }
		 (yyval.lnk) = (yyvsp[(2) - (2)].lnk) ;
		 ignoreTypedefType = 0;
               }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 1272 "SDCC.y"
    { (yyval.lnk) = reverseLink((yyvsp[(1) - (1)].lnk)); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1274 "SDCC.y"
    { (yyvsp[(1) - (2)].lnk) = reverseLink((yyvsp[(1) - (2)].lnk)); (yyvsp[(1) - (2)].lnk)->next = (yyvsp[(2) - (2)].lnk) ; (yyval.lnk) = (yyvsp[(1) - (2)].lnk);
	  if (IS_PTR((yyvsp[(1) - (2)].lnk)) && IS_FUNC((yyvsp[(2) - (2)].lnk)))
	    DCL_TYPE((yyvsp[(1) - (2)].lnk)) = CPOINTER;
	}
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1281 "SDCC.y"
    { (yyval.lnk) = (yyvsp[(2) - (3)].lnk) ; }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1282 "SDCC.y"
    {             
                                       (yyval.lnk) = newLink (DECLARATOR);
                                       DCL_TYPE((yyval.lnk)) = ARRAY ;
                                       DCL_ELEM((yyval.lnk)) = 0     ;
                                    }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1287 "SDCC.y"
    { 
                                       value *val ;
                                       (yyval.lnk) = newLink (DECLARATOR);
                                       DCL_TYPE((yyval.lnk)) = ARRAY ;
                                       DCL_ELEM((yyval.lnk)) = (int) floatFromVal(val = constExprValue((yyvsp[(2) - (3)].asts),TRUE));
                                    }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1293 "SDCC.y"
    {
                                       (yyval.lnk) = newLink (DECLARATOR);
                                       DCL_TYPE((yyval.lnk)) = ARRAY ;
                                       DCL_ELEM((yyval.lnk)) = 0     ;
                                       (yyval.lnk)->next = (yyvsp[(1) - (3)].lnk) ;
                                    }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1300 "SDCC.y"
    {
                                       value *val ;
                                       (yyval.lnk) = newLink (DECLARATOR);
                                       DCL_TYPE((yyval.lnk)) = ARRAY ;
                                       DCL_ELEM((yyval.lnk)) = (int) floatFromVal(val = constExprValue((yyvsp[(3) - (4)].asts),TRUE));
                                       (yyval.lnk)->next = (yyvsp[(1) - (4)].lnk) ;
                                    }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1307 "SDCC.y"
    { (yyval.lnk) = NULL;}
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1308 "SDCC.y"
    { (yyval.lnk) = NULL;}
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1309 "SDCC.y"
    {
     // $1 must be a pointer to a function
     sym_link *p=newLink(DECLARATOR);
     DCL_TYPE(p) = FUNCTION;
     if (!(yyvsp[(1) - (3)].lnk)) {
       // ((void (code *) ()) 0) ()
       (yyvsp[(1) - (3)].lnk)=newLink(DECLARATOR);
       DCL_TYPE((yyvsp[(1) - (3)].lnk))=CPOINTER;
       (yyval.lnk) = (yyvsp[(1) - (3)].lnk);
     }
     (yyvsp[(1) - (3)].lnk)->next=p;
   }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1321 "SDCC.y"
    { NestLevel++ ; currBlockno++; }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1321 "SDCC.y"
    {
       sym_link *p=newLink(DECLARATOR);
       DCL_TYPE(p) = FUNCTION;
	   
       FUNC_HASVARARGS(p) = IS_VARG((yyvsp[(4) - (5)].val));
       FUNC_ARGS(p) = reverseVal((yyvsp[(4) - (5)].val));
	     
       /* nest level was incremented to take care of the parms  */
       NestLevel-- ;
       currBlockno--;
       p->next = (yyvsp[(1) - (5)].lnk);
       (yyval.lnk) = p;

       // remove the symbol args (if any)
       cleanUpLevel(SymbolTab,NestLevel+1);
   }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1340 "SDCC.y"
    { (yyval.ilist) = newiList(INIT_NODE,(yyvsp[(1) - (1)].asts)); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1341 "SDCC.y"
    { (yyval.ilist) = newiList(INIT_DEEP,revinit((yyvsp[(2) - (3)].ilist))); }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 1342 "SDCC.y"
    { (yyval.ilist) = newiList(INIT_DEEP,revinit((yyvsp[(2) - (4)].ilist))); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1347 "SDCC.y"
    {  (yyvsp[(3) - (3)].ilist)->next = (yyvsp[(1) - (3)].ilist); (yyval.ilist) = (yyvsp[(3) - (3)].ilist); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1358 "SDCC.y"
    {
                            ast *ex;
			    seqPointNo++;
			    ex = newNode(INLINEASM,NULL,NULL);
			    ex->values.inlineasm = strdup((yyvsp[(1) - (2)].yyinline));
			    seqPointNo++;
			    (yyval.asts) = ex;
                         }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1369 "SDCC.y"
    {
		   inCritical++;
		   STACK_PUSH(continueStack,NULL);
		   STACK_PUSH(breakStack,NULL);
                   (yyval.sym) = NULL;
                }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1378 "SDCC.y"
    {
		   STACK_POP(breakStack);
		   STACK_POP(continueStack);
		   inCritical--;
		   (yyval.asts) = newNode(CRITICAL,(yyvsp[(2) - (2)].asts),NULL);
                }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 1388 "SDCC.y"
    {  (yyval.asts) = createLabel((yyvsp[(1) - (2)].sym),NULL);  }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1390 "SDCC.y"
    {
       if (STACK_EMPTY(swStk))
         (yyval.asts) = createCase(NULL,(yyvsp[(2) - (4)].asts),(yyvsp[(4) - (4)].asts));
       else
         (yyval.asts) = createCase(STACK_PEEK(swStk),(yyvsp[(2) - (4)].asts),(yyvsp[(4) - (4)].asts));
     }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1396 "SDCC.y"
    { (yyval.asts) = newNode(DEFAULT,NULL,NULL); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1397 "SDCC.y"
    {
       if (STACK_EMPTY(swStk))
         (yyval.asts) = createDefault(NULL,(yyvsp[(2) - (4)].asts),(yyvsp[(4) - (4)].asts));
       else
         (yyval.asts) = createDefault(STACK_PEEK(swStk),(yyvsp[(2) - (4)].asts),(yyvsp[(4) - (4)].asts));
     }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1406 "SDCC.y"
    {
	        STACK_PUSH(blockNum,currBlockno);
		currBlockno = ++blockNo ;
		ignoreTypedefType = 0;
	      }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1413 "SDCC.y"
    { currBlockno = STACK_POP(blockNum); }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 1417 "SDCC.y"
    { (yyval.asts) = createBlock(NULL,NULL); }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1418 "SDCC.y"
    { (yyval.asts) = createBlock(NULL,(yyvsp[(2) - (3)].asts)) ;  }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1420 "SDCC.y"
    { addSymChain((yyvsp[(2) - (2)].sym)); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 1421 "SDCC.y"
    { (yyval.asts) = createBlock((yyvsp[(2) - (4)].sym),NULL) ;  }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1423 "SDCC.y"
    {  addSymChain ((yyvsp[(2) - (2)].sym)); }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 1425 "SDCC.y"
    {(yyval.asts) = createBlock((yyvsp[(2) - (5)].sym),(yyvsp[(4) - (5)].asts))   ;  }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 1426 "SDCC.y"
    { (yyval.asts) = NULL ; }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1431 "SDCC.y"
    {
       /* if this is typedef declare it immediately */
       if ( (yyvsp[(1) - (1)].sym) && IS_TYPEDEF((yyvsp[(1) - (1)].sym)->etype)) {
	 allocVariables ((yyvsp[(1) - (1)].sym));
	 (yyval.sym) = NULL ;
       }
       else
	 (yyval.sym) = (yyvsp[(1) - (1)].sym) ;
       ignoreTypedefType = 0;
     }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 1443 "SDCC.y"
    {
       symbol   *sym;
       
       /* if this is a typedef */
       if ((yyvsp[(2) - (2)].sym) && IS_TYPEDEF((yyvsp[(2) - (2)].sym)->etype)) {
	 allocVariables ((yyvsp[(2) - (2)].sym));
	 (yyval.sym) = (yyvsp[(1) - (2)].sym) ;
       }
       else {
				/* get to the end of the previous decl */
	 if ( (yyvsp[(1) - (2)].sym) ) {
	   (yyval.sym) = sym = (yyvsp[(1) - (2)].sym) ;
	   while (sym->next)
	     sym = sym->next ;
	   sym->next = (yyvsp[(2) - (2)].sym);
	 } 
	 else
	   (yyval.sym) = (yyvsp[(2) - (2)].sym) ;
       }
       ignoreTypedefType = 0;
     }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 1468 "SDCC.y"
    {  (yyval.asts) = newNode(NULLOP,(yyvsp[(1) - (2)].asts),(yyvsp[(2) - (2)].asts)) ;}
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 1472 "SDCC.y"
    { (yyval.asts) = NULL;}
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 1473 "SDCC.y"
    { (yyval.asts) = (yyvsp[(1) - (2)].asts); seqPointNo++;}
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 1477 "SDCC.y"
    { (yyval.asts) = (yyvsp[(2) - (2)].asts)  ; }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1478 "SDCC.y"
    { (yyval.asts) = NULL;}
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1483 "SDCC.y"
    { seqPointNo++;}
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1484 "SDCC.y"
    {
			      noLineno++ ;
			      (yyval.asts) = createIf ((yyvsp[(3) - (7)].asts), (yyvsp[(6) - (7)].asts), (yyvsp[(7) - (7)].asts) );
			      noLineno--;
			   }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1489 "SDCC.y"
    { 
                              ast *ex ;                              
                              static   int swLabel = 0 ;

			      seqPointNo++;
                              /* create a node for expression  */
                              ex = newNode(SWITCH,(yyvsp[(3) - (4)].asts),NULL);
                              STACK_PUSH(swStk,ex);   /* save it in the stack */
                              ex->values.switchVals.swNum = swLabel ;
                                 
                              /* now create the label */
                              SNPRINTF(lbuff, sizeof(lbuff), 
			      	       "_swBrk_%d",swLabel++);
                              (yyval.sym)  =  newSymbol(lbuff,NestLevel);
                              /* put label in the break stack  */
                              STACK_PUSH(breakStack,(yyval.sym));   
                           }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1506 "SDCC.y"
    {  
                              /* get back the switch form the stack  */
                              (yyval.asts) = STACK_POP(swStk)  ;
                              (yyval.asts)->right = newNode (NULLOP,(yyvsp[(6) - (6)].asts),createLabel((yyvsp[(5) - (6)].sym),NULL));
                              STACK_POP(breakStack);   
                           }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1514 "SDCC.y"
    {  /* create and push the continue , break & body labels */
                  static int Lblnum = 0 ;
		  /* continue */
                  SNPRINTF (lbuff, sizeof(lbuff), "_whilecontinue_%d",Lblnum);
		  STACK_PUSH(continueStack,newSymbol(lbuff,NestLevel));
		  /* break */
		  SNPRINTF (lbuff, sizeof(lbuff), "_whilebreak_%d",Lblnum);
		  STACK_PUSH(breakStack,newSymbol(lbuff,NestLevel));
		  /* body */
		  SNPRINTF (lbuff, sizeof(lbuff), "_whilebody_%d",Lblnum++);
		  (yyval.sym) = newSymbol(lbuff,NestLevel);
               }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 1528 "SDCC.y"
    {  /* create and push the continue , break & body Labels */
           static int Lblnum = 0 ;

	   /* continue */
	   SNPRINTF(lbuff, sizeof(lbuff), "_docontinue_%d",Lblnum);
	   STACK_PUSH(continueStack,newSymbol(lbuff,NestLevel));
	   /* break */
	   SNPRINTF(lbuff, sizeof(lbuff), "_dobreak_%d",Lblnum);
	   STACK_PUSH(breakStack,newSymbol(lbuff,NestLevel));
	   /* do body */
	   SNPRINTF(lbuff, sizeof(lbuff), "_dobody_%d",Lblnum++);
	   (yyval.sym) = newSymbol (lbuff,NestLevel);	   
        }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1543 "SDCC.y"
    { /* create & push continue, break & body labels */
            static int Lblnum = 0 ;
         
            /* continue */
	    SNPRINTF(lbuff, sizeof(lbuff), "_forcontinue_%d",Lblnum);
	    STACK_PUSH(continueStack,newSymbol(lbuff,NestLevel));
	    /* break    */
	    SNPRINTF(lbuff, sizeof(lbuff), "_forbreak_%d",Lblnum);
	    STACK_PUSH(breakStack,newSymbol(lbuff,NestLevel));
	    /* body */
	    SNPRINTF(lbuff, sizeof(lbuff), "_forbody_%d",Lblnum);
	    (yyval.sym) = newSymbol(lbuff,NestLevel);
	    /* condition */
	    SNPRINTF(lbuff, sizeof(lbuff), "_forcond_%d",Lblnum++);
	    STACK_PUSH(forStack,newSymbol(lbuff,NestLevel));
          }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1562 "SDCC.y"
    { seqPointNo++;}
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1563 "SDCC.y"
    { 
			   noLineno++ ;
			   (yyval.asts) = createWhile ( (yyvsp[(1) - (6)].sym), STACK_POP(continueStack),
					      STACK_POP(breakStack), (yyvsp[(3) - (6)].asts), (yyvsp[(6) - (6)].asts) ); 
			   (yyval.asts)->lineno = (yyvsp[(1) - (6)].sym)->lineDef ;
			   noLineno-- ;
			 }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1571 "SDCC.y"
    { 
			  seqPointNo++; 
			  noLineno++ ; 
			  (yyval.asts) = createDo ( (yyvsp[(1) - (7)].sym) , STACK_POP(continueStack), 
					  STACK_POP(breakStack), (yyvsp[(5) - (7)].asts), (yyvsp[(2) - (7)].asts));
			  (yyval.asts)->lineno = (yyvsp[(1) - (7)].sym)->lineDef ;
			  noLineno-- ;
			}
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 1580 "SDCC.y"
    {
			  noLineno++ ;	
			  
			  /* if break or continue statement present
			     then create a general case loop */
			  if (STACK_PEEK(continueStack)->isref ||
			      STACK_PEEK(breakStack)->isref) {
			      (yyval.asts) = createFor ((yyvsp[(1) - (9)].sym), STACK_POP(continueStack),
					      STACK_POP(breakStack) ,
					      STACK_POP(forStack)   ,
					      (yyvsp[(3) - (9)].asts) , (yyvsp[(5) - (9)].asts) , (yyvsp[(7) - (9)].asts), (yyvsp[(9) - (9)].asts) );
			  } else {
			      (yyval.asts) = newNode(FOR,(yyvsp[(9) - (9)].asts),NULL);
			      AST_FOR((yyval.asts),trueLabel) = (yyvsp[(1) - (9)].sym);
			      AST_FOR((yyval.asts),continueLabel) =  STACK_POP(continueStack);
			      AST_FOR((yyval.asts),falseLabel) = STACK_POP(breakStack);
			      AST_FOR((yyval.asts),condLabel)  = STACK_POP(forStack)  ;
			      AST_FOR((yyval.asts),initExpr)   = (yyvsp[(3) - (9)].asts);
			      AST_FOR((yyval.asts),condExpr)   = (yyvsp[(5) - (9)].asts);
			      AST_FOR((yyval.asts),loopExpr)   = (yyvsp[(7) - (9)].asts);
			  }
			  
			  noLineno-- ;
			}
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 1607 "SDCC.y"
    { (yyval.asts) = NULL ; seqPointNo++; }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 1608 "SDCC.y"
    { (yyval.asts) = (yyvsp[(1) - (1)].asts) ; seqPointNo++; }
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 1612 "SDCC.y"
    { 
                              (yyvsp[(2) - (3)].sym)->islbl = 1;
                              (yyval.asts) = newAst_VALUE(symbolVal((yyvsp[(2) - (3)].sym))); 
                              (yyval.asts) = newNode(GOTO,(yyval.asts),NULL);
                           }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 1617 "SDCC.y"
    {  
       /* make sure continue is in context */
       if (STACK_EMPTY(continueStack) || STACK_PEEK(continueStack) == NULL) {
	   werror(E_BREAK_CONTEXT);
	   (yyval.asts) = NULL;
       }
       else {
	   (yyval.asts) = newAst_VALUE(symbolVal(STACK_PEEK(continueStack)));      
	   (yyval.asts) = newNode(GOTO,(yyval.asts),NULL);
	   /* mark the continue label as referenced */
	   STACK_PEEK(continueStack)->isref = 1;
       }
   }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 1630 "SDCC.y"
    { 
       if (STACK_EMPTY(breakStack) || STACK_PEEK(breakStack) == NULL) {
	   werror(E_BREAK_CONTEXT);
	   (yyval.asts) = NULL;
       } else {
	   (yyval.asts) = newAst_VALUE(symbolVal(STACK_PEEK(breakStack)));
	   (yyval.asts) = newNode(GOTO,(yyval.asts),NULL);
	   STACK_PEEK(breakStack)->isref = 1;
       }
   }
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 1640 "SDCC.y"
    {
       seqPointNo++;
       if (inCritical) {
	   werror(E_INVALID_CRITICAL);
	   (yyval.asts) = NULL;
       } else {
	   (yyval.asts) = newNode(RETURN,NULL,NULL);
       }
   }
    break;

  case 271:

/* Line 1806 of yacc.c  */
#line 1649 "SDCC.y"
    {
       seqPointNo++;
       if (inCritical) {
	   werror(E_INVALID_CRITICAL);
	   (yyval.asts) = NULL;
       } else {
	   (yyval.asts) = newNode(RETURN,NULL,(yyvsp[(2) - (3)].asts));
       }
   }
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 1661 "SDCC.y"
    { (yyval.sym) = newSymbol ((yyvsp[(1) - (1)].yychar),NestLevel) ; }
    break;



/* Line 1806 of yacc.c  */
#line 4756 "SDCCy.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1663 "SDCC.y"



