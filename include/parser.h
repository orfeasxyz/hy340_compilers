/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUM = 258,                     /* NUM  */
    IDENT = 259,                   /* IDENT  */
    STRING = 260,                  /* STRING  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    WHILE = 263,                   /* WHILE  */
    FOR = 264,                     /* FOR  */
    FUNCTION = 265,                /* FUNCTION  */
    RETURN = 266,                  /* RETURN  */
    BREAK = 267,                   /* BREAK  */
    CONTINUE = 268,                /* CONTINUE  */
    AND = 269,                     /* AND  */
    NOT = 270,                     /* NOT  */
    OR = 271,                      /* OR  */
    LOCAL = 272,                   /* LOCAL  */
    TRUE = 273,                    /* TRUE  */
    FALSE = 274,                   /* FALSE  */
    NIL = 275,                     /* NIL  */
    ASSIGN = 276,                  /* ASSIGN  */
    PLUS = 277,                    /* PLUS  */
    MINUS = 278,                   /* MINUS  */
    MUL = 279,                     /* MUL  */
    DIV = 280,                     /* DIV  */
    MOD = 281,                     /* MOD  */
    EQUAL = 282,                   /* EQUAL  */
    NEQUAL = 283,                  /* NEQUAL  */
    INC = 284,                     /* INC  */
    DEC = 285,                     /* DEC  */
    GT = 286,                      /* GT  */
    LT = 287,                      /* LT  */
    GET = 288,                     /* GET  */
    LET = 289,                     /* LET  */
    CURLY_OPEN = 290,              /* CURLY_OPEN  */
    CURLY_CLOSED = 291,            /* CURLY_CLOSED  */
    SQUARE_OPEN = 292,             /* SQUARE_OPEN  */
    SQUARE_CLOSED = 293,           /* SQUARE_CLOSED  */
    PAR_OPEN = 294,                /* PAR_OPEN  */
    PAR_CLOSED = 295,              /* PAR_CLOSED  */
    SEMI_COLON = 296,              /* SEMI_COLON  */
    COMMA = 297,                   /* COMMA  */
    COLON = 298,                   /* COLON  */
    DOUBLE_COLON = 299,            /* DOUBLE_COLON  */
    DOT = 300,                     /* DOT  */
    DOUBLE_DOT = 301,              /* DOUBLE_DOT  */
    UMINUS = 302,                  /* UMINUS  */
    LOWER_THAN_ELSE = 303          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NUM 258
#define IDENT 259
#define STRING 260
#define IF 261
#define ELSE 262
#define WHILE 263
#define FOR 264
#define FUNCTION 265
#define RETURN 266
#define BREAK 267
#define CONTINUE 268
#define AND 269
#define NOT 270
#define OR 271
#define LOCAL 272
#define TRUE 273
#define FALSE 274
#define NIL 275
#define ASSIGN 276
#define PLUS 277
#define MINUS 278
#define MUL 279
#define DIV 280
#define MOD 281
#define EQUAL 282
#define NEQUAL 283
#define INC 284
#define DEC 285
#define GT 286
#define LT 287
#define GET 288
#define LET 289
#define CURLY_OPEN 290
#define CURLY_CLOSED 291
#define SQUARE_OPEN 292
#define SQUARE_CLOSED 293
#define PAR_OPEN 294
#define PAR_CLOSED 295
#define SEMI_COLON 296
#define COMMA 297
#define COLON 298
#define DOUBLE_COLON 299
#define DOT 300
#define DOUBLE_DOT 301
#define UMINUS 302
#define LOWER_THAN_ELSE 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "parser.y"

    double nval;
    char* sval;
    struct SymbolTableEntry* exprval;

#line 169 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
