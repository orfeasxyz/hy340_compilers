/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    IDENT = 259,
    STRING = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    FOR = 264,
    FUNCTION = 265,
    RETURN = 266,
    BREAK = 267,
    CONTINUE = 268,
    AND = 269,
    NOT = 270,
    OR = 271,
    LOCAL = 272,
    TRUE = 273,
    FALSE = 274,
    NIL = 275,
    ASSIGN = 276,
    PLUS = 277,
    MINUS = 278,
    MUL = 279,
    DIV = 280,
    MOD = 281,
    EQUAL = 282,
    NEQUAL = 283,
    INC = 284,
    DEC = 285,
    GT = 286,
    LT = 287,
    GET = 288,
    LET = 289,
    CURLY_OPEN = 290,
    CURLY_CLOSED = 291,
    SQUARE_OPEN = 292,
    SQUARE_CLOSED = 293,
    PAR_OPEN = 294,
    PAR_CLOSED = 295,
    SEMI_COLON = 296,
    COMMA = 297,
    COLON = 298,
    DOUBLE_COLON = 299,
    DOT = 300,
    DOUBLE_DOT = 301,
    UMINUS = 302,
    LOWER_THAN_ELSE = 303
  };
#endif
/* Tokens.  */
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
#line 25 "parser.y"

    unsigned labelval;
    double nval;
    char* sval;
	unsigned int func_addr;
	char* lib_addr;
    struct ForLoopPrefix* forprefixval;
    struct SymbolTableEntry* symval;
    struct Expr* exprval;
    struct Call* callval;
	struct stmt_t* stmtval;

#line 166 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
