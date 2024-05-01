/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
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



/* Line 2068 of yacc.c  */
#line 286 "SDCCy.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


