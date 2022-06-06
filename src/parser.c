/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
	#include "../include/symtable.h"
	#include "../include/structs.h"
	#include "../include/stack.h"
	#include "../include/rule_handler.h"
	#include "../include/parser.h"
    #include "../include/target.h"

    int yyerror(char* message);
    int yylex(void);
    
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

#line 91 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 26 "parser.y"

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

#line 252 "parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   532

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

#define YYUNDEFTOK  2
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    73,    73,    76,    77,    80,    81,    81,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   117,   118,   119,   120,   121,   122,   123,
     124,   127,   129,   130,   131,   132,   133,   136,   137,   138,
     139,   142,   143,   144,   145,   148,   149,   150,   153,   154,
     157,   159,   161,   162,   163,   166,   168,   169,   172,   173,
     176,   178,   178,   181,   180,   195,   200,   203,   208,   202,
     219,   220,   223,   224,   225,   226,   227,   230,   231,   232,
     235,   237,   239,   240,   248,   250,   252,   254,   255,   257,
     257,   259,   261,   268,   278,   286
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "IDENT", "STRING", "IF", "ELSE",
  "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT",
  "OR", "LOCAL", "TRUE", "FALSE", "NIL", "ASSIGN", "PLUS", "MINUS", "MUL",
  "DIV", "MOD", "EQUAL", "NEQUAL", "INC", "DEC", "GT", "LT", "GET", "LET",
  "CURLY_OPEN", "CURLY_CLOSED", "SQUARE_OPEN", "SQUARE_CLOSED", "PAR_OPEN",
  "PAR_CLOSED", "SEMI_COLON", "COMMA", "COLON", "DOUBLE_COLON", "DOT",
  "DOUBLE_DOT", "UMINUS", "LOWER_THAN_ELSE", "$accept", "program",
  "statements", "statements_alt", "$@1", "statement", "expression", "term",
  "assignexpr", "prim", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "objectdef", "objectarg", "indexed",
  "indexedelem", "block", "$@2", "funcdef", "$@3", "funcbody",
  "funcprefix", "funcargs", "$@4", "$@5", "funcname", "const", "idlist",
  "ifprefix", "elseprefix", "ifstmt", "whileprefix", "whileargs",
  "whilestmt", "N", "M", "forprefix", "$@6", "forstmt", "returnstmt",
  "break", "continue", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF (-150)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     150,  -150,  -150,  -150,   -35,  -150,  -150,     5,    93,   -28,
     -24,   201,    22,  -150,  -150,  -150,   201,     6,     6,  -150,
      24,   178,  -150,    28,    48,  -150,     1,  -150,   268,  -150,
    -150,  -150,   -15,  -150,    64,  -150,  -150,  -150,  -150,  -150,
     150,  -150,    18,  -150,  -150,  -150,  -150,  -150,  -150,   201,
      19,  -150,  -150,  -150,   289,  -150,  -150,  -150,  -150,  -150,
      50,    80,    64,    80,   150,   201,   247,  -150,    29,  -150,
      20,   331,    30,  -150,  -150,   150,  -150,  -150,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,  -150,
     201,  -150,  -150,   201,   201,    68,    69,  -150,  -150,  -150,
     201,   201,    70,    37,    82,   201,   150,   201,   352,   201,
    -150,    51,    41,   225,   201,  -150,    57,  -150,    56,  -150,
     201,   201,    10,    10,  -150,  -150,  -150,   485,   485,   117,
     117,   117,   117,   457,   394,    59,  -150,    63,   415,    74,
    -150,  -150,    83,  -150,   150,   373,  -150,    75,  -150,    86,
      56,  -150,   201,  -150,  -150,   201,   498,   472,  -150,  -150,
     201,  -150,  -150,   100,  -150,  -150,  -150,  -150,  -150,  -150,
     436,    84,    88,    87,  -150,   150,   201,  -150,  -150,  -150,
     100,    91,  -150,   310,  -150,  -150,  -150,  -150
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    82,    47,    83,     0,    94,    99,    81,     0,     0,
       0,     0,     0,    85,    86,    84,     0,     0,     0,    71,
      64,     0,    17,     0,     0,     2,     6,     5,     0,    32,
      18,    40,    42,    50,    43,    44,    15,    16,    73,    46,
       0,     9,     0,    10,    97,    11,    12,    14,    13,     0,
       0,    80,    76,   102,     0,   104,   105,    35,    48,    34,
       0,    36,     0,    38,     4,     0,    62,    66,     0,    67,
      68,     0,     0,    49,     1,     0,    98,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,    37,    39,     0,    64,     0,     0,    56,    58,    59,
       0,    64,     0,     0,    92,     0,     0,    64,     0,    64,
     103,     0,     0,     0,    64,    65,     0,    33,    45,     7,
       0,     0,    19,    20,    21,    22,    23,    28,    29,    24,
      26,    25,    27,    41,     0,     0,    51,     0,     0,     0,
      53,    77,     0,    91,     0,     0,    96,     0,    90,     0,
       0,    72,     0,    63,    69,    64,    30,    31,    52,    60,
      64,    54,    55,    89,    75,    74,    93,    95,    97,    98,
       0,     0,     0,    87,    78,     0,     0,    70,    57,    61,
      89,     0,    97,     0,    88,    79,   101,   100
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -150,  -150,    71,  -150,  -150,   -37,     0,  -150,  -150,  -150,
      34,  -150,    38,  -150,  -150,  -150,   -89,  -150,  -150,    17,
    -150,    -6,  -150,   -14,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,   -34,  -150,  -150,  -150,  -150,  -150,  -150,  -149,
     -75,  -150,  -150,  -150,  -150,  -150,  -150
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    75,    27,    66,    29,    30,    31,
      32,    33,    34,    97,    98,    99,    67,    35,    68,    69,
      70,    36,    64,    37,   103,   165,    38,   142,   163,   181,
      52,    39,   174,    40,   144,    41,    42,   106,    43,   107,
     120,    44,    50,    45,    46,    47,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    -3,   121,   104,    49,   135,    90,    72,    54,    51,
       2,    57,   139,    55,    91,    92,    59,    56,   147,   175,
     149,    71,    93,    12,    94,   153,    58,     1,     2,     3,
      95,    96,    73,   186,    80,    81,    82,    -3,   119,    11,
      28,    12,    13,    14,    15,    60,   111,    16,    74,   108,
      23,    61,    63,    17,    18,    62,    62,   105,   109,    65,
       7,    20,   116,    21,    28,   113,   171,   115,    23,   146,
     118,   172,   136,   137,   140,    28,   141,   151,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   143,
     133,   150,    65,   134,   176,   155,     1,     2,     3,   159,
     138,   100,   160,   101,   173,   145,    28,   166,    11,   102,
      12,    13,    14,    15,   162,   168,    16,    93,    19,    94,
     156,   157,    17,    18,   178,    95,    96,   169,   179,   180,
      20,   185,    21,   154,    53,   112,   164,    23,   182,    78,
      79,    80,    81,    82,    28,     0,   184,     0,    -4,    -4,
      -4,    -4,   170,     1,     2,     3,     4,     0,     5,     6,
       7,     8,     9,    10,     0,    11,     0,    12,    13,    14,
      15,     0,     0,    16,     0,    28,   183,     0,     0,    17,
      18,     1,     2,     3,     0,    19,     0,    20,     7,    21,
       0,    22,     0,    11,    23,    12,    13,    14,    15,     0,
       0,    16,     0,     0,     1,     2,     3,    17,    18,     0,
       0,     0,     0,     0,     0,    20,    11,    21,    12,    13,
      14,    15,    23,     0,    16,     0,     0,     0,     0,     0,
      17,    18,     0,     0,     0,     0,     0,     0,    20,    76,
      21,    77,     0,     0,     0,    23,     0,    78,    79,    80,
      81,    82,    83,    84,     0,     0,    85,    86,    87,    88,
       0,    76,     0,    77,     0,     0,     0,     0,   152,    78,
      79,    80,    81,    82,    83,    84,     0,     0,    85,    86,
      87,    88,    76,     0,    77,     0,     0,     0,     0,   114,
      78,    79,    80,    81,    82,    83,    84,     0,     0,    85,
      86,    87,    88,    76,     0,    77,     0,     0,     0,    89,
       0,    78,    79,    80,    81,    82,    83,    84,     0,     0,
      85,    86,    87,    88,    76,     0,    77,     0,     0,     0,
     110,     0,    78,    79,    80,    81,    82,    83,    84,     0,
       0,    85,    86,    87,    88,    76,     0,    77,     0,     0,
       0,   187,     0,    78,    79,    80,    81,    82,    83,    84,
       0,     0,    85,    86,    87,    88,    76,     0,    77,     0,
       0,   117,     0,     0,    78,    79,    80,    81,    82,    83,
      84,     0,     0,    85,    86,    87,    88,    76,     0,    77,
       0,     0,   148,     0,     0,    78,    79,    80,    81,    82,
      83,    84,     0,     0,    85,    86,    87,    88,    76,     0,
      77,     0,     0,   167,     0,     0,    78,    79,    80,    81,
      82,    83,    84,     0,     0,    85,    86,    87,    88,    76,
       0,    77,   158,     0,     0,     0,     0,    78,    79,    80,
      81,    82,    83,    84,     0,     0,    85,    86,    87,    88,
      76,     0,    77,   161,     0,     0,     0,     0,    78,    79,
      80,    81,    82,    83,    84,     0,     0,    85,    86,    87,
      88,    76,   177,    77,     0,     0,     0,     0,     0,    78,
      79,    80,    81,    82,    83,    84,    76,     0,    85,    86,
      87,    88,     0,     0,    78,    79,    80,    81,    82,    83,
      84,     0,     0,    85,    86,    87,    88,    78,    79,    80,
      81,    82,    -4,    -4,     0,     0,    85,    86,    87,    88,
      78,    79,    80,    81,    82,    83,    84,     0,     0,    85,
      86,    87,    88
};

static const yytype_int16 yycheck[] =
{
       0,     0,    77,    40,    39,    94,    21,    21,     8,     4,
       4,    11,   101,    41,    29,    30,    16,    41,   107,   168,
     109,    21,    37,    17,    39,   114,     4,     3,     4,     5,
      45,    46,     4,   182,    24,    25,    26,    36,    75,    15,
      40,    17,    18,    19,    20,    39,    60,    23,     0,    49,
      44,    17,    18,    29,    30,    17,    18,    39,    39,    35,
      10,    37,    42,    39,    64,    65,   155,    38,    44,   106,
      40,   160,     4,     4,     4,    75,    39,    36,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     7,
      90,    40,    35,    93,   169,    39,     3,     4,     5,    40,
     100,    37,    39,    39,     4,   105,   106,   144,    15,    45,
      17,    18,    19,    20,    40,    40,    23,    37,    35,    39,
     120,   121,    29,    30,    40,    45,    46,    41,    40,    42,
      37,    40,    39,   116,    41,    64,   142,    44,   175,    22,
      23,    24,    25,    26,   144,    -1,   180,    -1,    31,    32,
      33,    34,   152,     3,     4,     5,     6,    -1,     8,     9,
      10,    11,    12,    13,    -1,    15,    -1,    17,    18,    19,
      20,    -1,    -1,    23,    -1,   175,   176,    -1,    -1,    29,
      30,     3,     4,     5,    -1,    35,    -1,    37,    10,    39,
      -1,    41,    -1,    15,    44,    17,    18,    19,    20,    -1,
      -1,    23,    -1,    -1,     3,     4,     5,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    15,    39,    17,    18,
      19,    20,    44,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    14,
      39,    16,    -1,    -1,    -1,    44,    -1,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    31,    32,    33,    34,
      -1,    14,    -1,    16,    -1,    -1,    -1,    -1,    43,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    32,
      33,    34,    14,    -1,    16,    -1,    -1,    -1,    -1,    42,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    31,
      32,    33,    34,    14,    -1,    16,    -1,    -1,    -1,    41,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    14,    -1,    16,    -1,    -1,    -1,
      41,    -1,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    31,    32,    33,    34,    14,    -1,    16,    -1,    -1,
      -1,    41,    -1,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    31,    32,    33,    34,    14,    -1,    16,    -1,
      -1,    40,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,    33,    34,    14,    -1,    16,
      -1,    -1,    40,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    14,    -1,
      16,    -1,    -1,    40,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,    33,    34,    14,
      -1,    16,    38,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    31,    32,    33,    34,
      14,    -1,    16,    38,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    33,
      34,    14,    36,    16,    -1,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    27,    28,    14,    -1,    31,    32,
      33,    34,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,    33,    34,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    31,    32,    33,    34,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    31,
      32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      13,    15,    17,    18,    19,    20,    23,    29,    30,    35,
      37,    39,    41,    44,    50,    51,    52,    54,    55,    56,
      57,    58,    59,    60,    61,    66,    70,    72,    75,    80,
      82,    84,    85,    87,    90,    92,    93,    94,    95,    39,
      91,     4,    79,    41,    55,    41,    41,    55,     4,    55,
      39,    59,    61,    59,    71,    35,    55,    65,    67,    68,
      69,    55,    72,     4,     0,    53,    14,    16,    22,    23,
      24,    25,    26,    27,    28,    31,    32,    33,    34,    41,
      21,    29,    30,    37,    39,    45,    46,    62,    63,    64,
      37,    39,    45,    73,    54,    39,    86,    88,    55,    39,
      41,    72,    51,    55,    42,    38,    42,    40,    40,    54,
      89,    89,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    65,     4,     4,    55,    65,
       4,    39,    76,     7,    83,    55,    54,    65,    40,    65,
      40,    36,    43,    65,    68,    39,    55,    55,    38,    40,
      39,    38,    40,    77,    70,    74,    54,    40,    40,    41,
      55,    65,    65,     4,    81,    88,    89,    36,    40,    40,
      42,    78,    54,    55,    81,    40,    88,    41
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    53,    52,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    56,    56,    56,    56,    56,
      56,    57,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    60,    60,    60,    60,    61,    61,    61,    62,    62,
      63,    64,    65,    65,    65,    66,    67,    67,    68,    68,
      69,    71,    70,    73,    72,    74,    75,    77,    78,    76,
      79,    79,    80,    80,    80,    80,    80,    81,    81,    81,
      82,    83,    84,    84,    85,    86,    87,    88,    89,    91,
      90,    92,    93,    93,    94,    95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     0,     1,     0,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     4,     1,     3,     2,     2,     2,     2,     2,     2,
       1,     3,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     2,     6,     1,     1,
       3,     5,     1,     3,     0,     3,     1,     1,     1,     3,
       5,     0,     4,     0,     4,     1,     2,     0,     0,     5,
       1,     0,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     1,     2,     4,     1,     3,     3,     0,     0,     0,
       8,     7,     2,     3,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3:
#line 76 "parser.y"
                                        { (yyval.stmtval) = (yyvsp[0].stmtval); }
#line 1634 "parser.c"
    break;

  case 4:
#line 77 "parser.y"
                                        { (yyval.stmtval) = (stmt_t*) 0;}
#line 1640 "parser.c"
    break;

  case 5:
#line 80 "parser.y"
                                                          { (yyval.stmtval) = (yyvsp[0].stmtval); }
#line 1646 "parser.c"
    break;

  case 6:
#line 81 "parser.y"
                                 {resetTemp();}
#line 1652 "parser.c"
    break;

  case 7:
#line 81 "parser.y"
                                                          {
                                            if((yyvsp[-2].stmtval)) (yyval.stmtval) = (yyvsp[-2].stmtval);
                                            else if((yyvsp[0].stmtval)) (yyval.stmtval) = (yyvsp[0].stmtval);
                                            else (yyval.stmtval) = (stmt_t*) 0;
                                        }
#line 1662 "parser.c"
    break;

  case 8:
#line 88 "parser.y"
                                        {(yyval.stmtval) = (stmt_t*) 0; makeBoolStmt((yyvsp[-1].exprval));}
#line 1668 "parser.c"
    break;

  case 9:
#line 89 "parser.y"
                                        {(yyval.stmtval) = (yyvsp[0].stmtval);}
#line 1674 "parser.c"
    break;

  case 10:
#line 90 "parser.y"
                                        {(yyval.stmtval) = (stmt_t*) 0;}
#line 1680 "parser.c"
    break;

  case 11:
#line 91 "parser.y"
                                        {(yyval.stmtval) = (stmt_t*) 0;}
#line 1686 "parser.c"
    break;

  case 12:
#line 92 "parser.y"
                                        {(yyval.stmtval) = (stmt_t*) 0;}
#line 1692 "parser.c"
    break;

  case 13:
#line 93 "parser.y"
                                        {(yyval.stmtval) = (yyvsp[0].stmtval);}
#line 1698 "parser.c"
    break;

  case 14:
#line 94 "parser.y"
                                        {(yyval.stmtval) = (yyvsp[0].stmtval);}
#line 1704 "parser.c"
    break;

  case 15:
#line 95 "parser.y"
                                        {(yyval.stmtval) = (yyvsp[0].stmtval);}
#line 1710 "parser.c"
    break;

  case 16:
#line 96 "parser.y"
                                        {(yyval.stmtval) = (stmt_t*) 0;}
#line 1716 "parser.c"
    break;

  case 17:
#line 97 "parser.y"
                                        {(yyval.stmtval) = (stmt_t*) 0;}
#line 1722 "parser.c"
    break;

  case 18:
#line 100 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1728 "parser.c"
    break;

  case 19:
#line 101 "parser.y"
                                                {(yyval.exprval) = HANDLE_ARITH_OP(add, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1734 "parser.c"
    break;

  case 20:
#line 102 "parser.y"
                                                {(yyval.exprval) = HANDLE_ARITH_OP(sub, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1740 "parser.c"
    break;

  case 21:
#line 103 "parser.y"
                                                {(yyval.exprval) = HANDLE_ARITH_OP(mul, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1746 "parser.c"
    break;

  case 22:
#line 104 "parser.y"
                                                {(yyval.exprval) = HANDLE_ARITH_OP(mydiv, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1752 "parser.c"
    break;

  case 23:
#line 105 "parser.y"
                                                {(yyval.exprval) = HANDLE_ARITH_OP(mod, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1758 "parser.c"
    break;

  case 24:
#line 106 "parser.y"
                                                {(yyval.exprval) = HANDLE_REL_OP(if_greater, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1764 "parser.c"
    break;

  case 25:
#line 107 "parser.y"
                                                {(yyval.exprval) = HANDLE_REL_OP(if_geatereq, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1770 "parser.c"
    break;

  case 26:
#line 108 "parser.y"
                                                {(yyval.exprval) = HANDLE_REL_OP(if_less, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1776 "parser.c"
    break;

  case 27:
#line 109 "parser.y"
                                                {(yyval.exprval) = HANDLE_REL_OP(if_lesseq, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1782 "parser.c"
    break;

  case 28:
#line 110 "parser.y"
                                                {makeBoolStmt((yyvsp[-2].exprval)); makeBoolStmt((yyvsp[0].exprval)); (yyval.exprval) = HANDLE_REL_OP(if_eq, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1788 "parser.c"
    break;

  case 29:
#line 111 "parser.y"
                                                {makeBoolStmt((yyvsp[-2].exprval)); makeBoolStmt((yyvsp[0].exprval)); (yyval.exprval) = HANDLE_REL_OP(if_noteq, (yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1794 "parser.c"
    break;

  case 30:
#line 112 "parser.y"
                                                {(yyval.exprval) = HANDLE_BOOL_OP(and, (yyvsp[-3].exprval), (yyvsp[0].exprval), (yyvsp[-1].labelval));}
#line 1800 "parser.c"
    break;

  case 31:
#line 113 "parser.y"
                                                {(yyval.exprval) = HANDLE_BOOL_OP(or, (yyvsp[-3].exprval), (yyvsp[0].exprval), (yyvsp[-1].labelval));}
#line 1806 "parser.c"
    break;

  case 32:
#line 114 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1812 "parser.c"
    break;

  case 33:
#line 117 "parser.y"
                                                {(yyval.exprval) = (yyvsp[-1].exprval);}
#line 1818 "parser.c"
    break;

  case 34:
#line 118 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_UMINUS_EXPR((yyvsp[0].exprval));}
#line 1824 "parser.c"
    break;

  case 35:
#line 119 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_NOT_EXPR((yyvsp[0].exprval));}
#line 1830 "parser.c"
    break;

  case 36:
#line 120 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_INC_LVALUE((yyvsp[0].exprval), yylineno);}
#line 1836 "parser.c"
    break;

  case 37:
#line 121 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_LVALUE_INC((yyvsp[-1].exprval), yylineno);}
#line 1842 "parser.c"
    break;

  case 38:
#line 122 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_DEC_LVALUE((yyvsp[0].exprval), yylineno);}
#line 1848 "parser.c"
    break;

  case 39:
#line 123 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_LVALUE_DEC((yyvsp[-1].exprval), yylineno);}
#line 1854 "parser.c"
    break;

  case 40:
#line 124 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1860 "parser.c"
    break;

  case 41:
#line 127 "parser.y"
                                                {makeBoolStmt((yyvsp[0].exprval)); (yyval.exprval) = HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION((yyvsp[-2].exprval), (yyvsp[0].exprval), yylineno);}
#line 1866 "parser.c"
    break;

  case 42:
#line 129 "parser.y"
                                                {(yyval.exprval) = HANDLE_PRIM_TO_LVALUE((yyvsp[0].exprval), yylineno);}
#line 1872 "parser.c"
    break;

  case 43:
#line 130 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1878 "parser.c"
    break;

  case 44:
#line 131 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1884 "parser.c"
    break;

  case 45:
#line 132 "parser.y"
                                                {(yyval.exprval) = HANDLE_PRIM_TO_FUNCDEF((yyvsp[-1].symval));}
#line 1890 "parser.c"
    break;

  case 46:
#line 133 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1896 "parser.c"
    break;

  case 47:
#line 136 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_IDENT((yyvsp[0].sval), yylineno);}
#line 1902 "parser.c"
    break;

  case 48:
#line 137 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_LOCAL_IDENT((yyvsp[0].sval), yylineno);}
#line 1908 "parser.c"
    break;

  case 49:
#line 138 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_GLOBAL_IDENT((yyvsp[0].sval), yylineno);}
#line 1914 "parser.c"
    break;

  case 50:
#line 139 "parser.y"
                                        {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1920 "parser.c"
    break;

  case 51:
#line 142 "parser.y"
                                                                {(yyval.exprval) = HANDLE_MEMBER_TO_LVALUE_DOT_IDENT((yyvsp[-2].exprval), (yyvsp[0].sval));}
#line 1926 "parser.c"
    break;

  case 52:
#line 143 "parser.y"
                                                                {(yyval.exprval) = HANDLE_MEMBER_TO_LVALUE_SQUARE_EXPR((yyvsp[-3].exprval), (yyvsp[-1].exprval));}
#line 1932 "parser.c"
    break;

  case 53:
#line 144 "parser.y"
                                                                {(yyval.exprval) = HANDLE_MEMBER_TO_LVALUE_DOT_IDENT((yyvsp[-2].exprval), (yyvsp[0].sval));}
#line 1938 "parser.c"
    break;

  case 54:
#line 145 "parser.y"
                                                                {(yyval.exprval) = HANDLE_MEMBER_TO_LVALUE_SQUARE_EXPR((yyvsp[-3].exprval), (yyvsp[-1].exprval));}
#line 1944 "parser.c"
    break;

  case 55:
#line 148 "parser.y"
                                                                            {(yyval.exprval) = HANDLE_CALL_ELIST((yyvsp[-3].exprval), (yyvsp[-1].exprval));}
#line 1950 "parser.c"
    break;

  case 56:
#line 149 "parser.y"
                                                                            {(yyval.exprval) = HANDLE_CALL_LVALUE_SUFFIX((yyvsp[-1].exprval), (yyvsp[0].callval));}
#line 1956 "parser.c"
    break;

  case 57:
#line 150 "parser.y"
                                                                            {(yyval.exprval) = HANDLE_CALL_FUNCDEF_ELIST((yyvsp[-4].symval), (yyvsp[-1].exprval));}
#line 1962 "parser.c"
    break;

  case 58:
#line 153 "parser.y"
                                {(yyval.callval) = (yyvsp[0].callval);}
#line 1968 "parser.c"
    break;

  case 59:
#line 154 "parser.y"
                                {(yyval.callval) = (yyvsp[0].callval);}
#line 1974 "parser.c"
    break;

  case 60:
#line 157 "parser.y"
                                                               {(yyval.callval) = HANDLE_NORMCALL((yyvsp[-1].exprval));}
#line 1980 "parser.c"
    break;

  case 61:
#line 159 "parser.y"
                                                               {(yyval.callval) = HANDLE_METHODCALL((yyvsp[-3].sval), (yyvsp[-1].exprval));}
#line 1986 "parser.c"
    break;

  case 62:
#line 161 "parser.y"
                                            {makeBoolStmt((yyvsp[0].exprval)); (yyval.exprval) = (yyvsp[0].exprval); (yyval.exprval)->next = NULL;}
#line 1992 "parser.c"
    break;

  case 63:
#line 162 "parser.y"
                                            {(yyval.exprval) = HANDLE_ELIST_ADD((yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 1998 "parser.c"
    break;

  case 64:
#line 163 "parser.y"
                                                            {(yyval.exprval) = (Expr*) 0;}
#line 2004 "parser.c"
    break;

  case 65:
#line 166 "parser.y"
                                                     {(yyval.exprval) = (yyvsp[-1].exprval);}
#line 2010 "parser.c"
    break;

  case 66:
#line 168 "parser.y"
                            {(yyval.exprval) = HANDLE_OBJECTDEF_TO_ELIST((yyvsp[0].exprval));}
#line 2016 "parser.c"
    break;

  case 67:
#line 169 "parser.y"
                            {(yyval.exprval) = HANDLE_OBJECTDEF_TO_INDEXED((yyvsp[0].exprval));}
#line 2022 "parser.c"
    break;

  case 68:
#line 172 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 2028 "parser.c"
    break;

  case 69:
#line 173 "parser.y"
                                                {(yyval.exprval) = HANDLE_INDEXED_ADD((yyvsp[-2].exprval), (yyvsp[0].exprval));}
#line 2034 "parser.c"
    break;

  case 70:
#line 176 "parser.y"
                                                                    {makeBoolStmt((yyvsp[-1].exprval)); (yyval.exprval) = HANDLE_INDEXELEM((yyvsp[-3].exprval), (yyvsp[-1].exprval));}
#line 2040 "parser.c"
    break;

  case 71:
#line 178 "parser.y"
                           {scope++; current_table = SymTable_next(current_table);}
#line 2046 "parser.c"
    break;

  case 72:
#line 178 "parser.y"
                                                                                                            {scope--; SymTable_hide(current_table); current_table = SymTable_prev(current_table); (yyval.stmtval) = (yyvsp[-1].stmtval);}
#line 2052 "parser.c"
    break;

  case 73:
#line 181 "parser.y"
                                {
					funcCounter++;
					loopCounterStack = stack_push(loopCounterStack, loopCounter);
					loopCounter = 0;
				}
#line 2062 "parser.c"
    break;

  case 74:
#line 188 "parser.y"
                                {
					(yyval.symval) = HANDLE_FUNCDEF((yyvsp[-3].symval), (yyvsp[0].func_addr), yylineno);
					funcCounter--;
					loopCounter = stack_top(loopCounterStack);
					loopCounterStack = stack_pop(loopCounterStack);
				}
#line 2073 "parser.c"
    break;

  case 75:
#line 195 "parser.y"
                      {
                    (yyval.func_addr) = currScopeOffset();
                    exitScopeSpace();
                }
#line 2082 "parser.c"
    break;

  case 76:
#line 200 "parser.y"
                                  {(yyval.symval) = HANDLE_FUNCPREFIX((yyvsp[0].sval), yylineno);}
#line 2088 "parser.c"
    break;

  case 77:
#line 203 "parser.y"
                {
                    scope++; 
                    current_table = SymTable_next(current_table);
                }
#line 2097 "parser.c"
    break;

  case 78:
#line 208 "parser.y"
                {
                    scope--;
                    current_table = SymTable_prev(current_table); 
                    functionScopeStack = stack_push(functionScopeStack, scope);
                }
#line 2107 "parser.c"
    break;

  case 79:
#line 214 "parser.y"
                {
                    enterScopeSpace();
                    resetFunctionLocalOffset();
                }
#line 2116 "parser.c"
    break;

  case 80:
#line 219 "parser.y"
                               {(yyval.sval) = HANDLE_FUNCTION_WITH_NAME((yyvsp[0].sval), yylineno);}
#line 2122 "parser.c"
    break;

  case 81:
#line 220 "parser.y"
                               {(yyval.sval) = HANDLE_FUNCTION_WITHOUT_NAME(yylineno);}
#line 2128 "parser.c"
    break;

  case 82:
#line 223 "parser.y"
                            {(yyval.exprval) = newExprConstNum((yyvsp[0].nval));}
#line 2134 "parser.c"
    break;

  case 83:
#line 224 "parser.y"
                            {(yyval.exprval) = newExprConstString((yyvsp[0].sval));}
#line 2140 "parser.c"
    break;

  case 84:
#line 225 "parser.y"
                            {(yyval.exprval) = newExpr(nil_e);}
#line 2146 "parser.c"
    break;

  case 85:
#line 226 "parser.y"
                            {(yyval.exprval) = newExprConstBool(1);}
#line 2152 "parser.c"
    break;

  case 86:
#line 227 "parser.y"
                            {(yyval.exprval) = newExprConstBool(0);}
#line 2158 "parser.c"
    break;

  case 87:
#line 230 "parser.y"
                                        {HANDLE_IDLIST_IDENT((yyvsp[0].sval), yylineno);}
#line 2164 "parser.c"
    break;

  case 88:
#line 231 "parser.y"
                                        {HANDLE_IDLIST_IDENT((yyvsp[-2].sval), yylineno);}
#line 2170 "parser.c"
    break;

  case 90:
#line 235 "parser.y"
                                                    {makeBoolStmt((yyvsp[-1].exprval)); (yyval.labelval) = HANDLE_IFPREFIX((yyvsp[-1].exprval));}
#line 2176 "parser.c"
    break;

  case 91:
#line 237 "parser.y"
                                                    {(yyval.labelval) = HANDLE_ELSEPREFIX(yylineno);}
#line 2182 "parser.c"
    break;

  case 92:
#line 239 "parser.y"
                                   {patchLabel((yyvsp[-1].labelval), nextQuadLabel()); (yyval.stmtval) = (yyvsp[0].stmtval);}
#line 2188 "parser.c"
    break;

  case 93:
#line 240 "parser.y"
                                                          {
                    patchLabel((yyvsp[-3].labelval), (yyvsp[-1].labelval) + 1);
                    patchLabel((yyvsp[-1].labelval), nextQuadLabel());
                    (yyval.stmtval) = (yyvsp[-2].stmtval);
                    if(!(yyval.stmtval)) (yyval.stmtval) = (yyvsp[0].stmtval);
                }
#line 2199 "parser.c"
    break;

  case 94:
#line 248 "parser.y"
                                                    {(yyval.labelval) = nextQuadLabel(); loopCounter++;}
#line 2205 "parser.c"
    break;

  case 95:
#line 250 "parser.y"
                                                    {makeBoolStmt((yyvsp[-1].exprval)); (yyval.labelval) = HANDLE_WHILEARGS((yyvsp[-1].exprval));}
#line 2211 "parser.c"
    break;

  case 96:
#line 252 "parser.y"
                                                        {HANDLE_WHILE((yyvsp[-2].labelval), (yyvsp[-1].labelval), (yyvsp[0].stmtval)); loopCounter--;}
#line 2217 "parser.c"
    break;

  case 97:
#line 254 "parser.y"
                {(yyval.labelval) = nextQuadLabel(); emit(jump, NULL, NULL, NULL, 0, yylineno);}
#line 2223 "parser.c"
    break;

  case 98:
#line 255 "parser.y"
                {(yyval.labelval) = nextQuadLabel();}
#line 2229 "parser.c"
    break;

  case 99:
#line 257 "parser.y"
                    {loopCounter++;}
#line 2235 "parser.c"
    break;

  case 100:
#line 257 "parser.y"
                                                                                       {makeBoolStmt((yyvsp[-1].exprval)); (yyval.forprefixval) = HANDLE_FORPREFIX((yyvsp[-2].labelval), (yyvsp[-1].exprval));}
#line 2241 "parser.c"
    break;

  case 101:
#line 259 "parser.y"
                                                           {HANDLE_FORSTMT((yyvsp[-6].forprefixval), (yyvsp[-5].labelval), (yyvsp[-2].labelval), (yyvsp[0].labelval), (yyvsp[-1].stmtval)); loopCounter--;}
#line 2247 "parser.c"
    break;

  case 102:
#line 261 "parser.y"
                                                        {
                                                    if(funcCounter == 0) {
                                                        fprintf(stderr, "Line %d: Return used outside function", yylineno);
                                                        exit(1);
                                                    }
                                                    emit(ret, NULL, NULL, NULL, 0, yylineno);
                                                }
#line 2259 "parser.c"
    break;

  case 103:
#line 268 "parser.y"
                                                {
                                                    makeBoolStmt((yyvsp[-1].exprval));
                                                    if(funcCounter == 0) {
                                                        fprintf(stderr, "Line %d: Return used outside function", yylineno);
                                                        exit(1);
                                                    }
                                                    emit(ret, NULL, NULL, (yyvsp[-1].exprval), 0, yylineno);
                                                }
#line 2272 "parser.c"
    break;

  case 104:
#line 278 "parser.y"
                                         { 
                        if(loopCounter > 0) (yyval.stmtval) = HANDLE_BREAK(); 
                        else {
                            fprintf(stderr, "Line %d: Break outside loop\n", yylineno);
                            exit(1);
                        }
                    }
#line 2284 "parser.c"
    break;

  case 105:
#line 286 "parser.y"
                                            {
                        if(loopCounter > 0) (yyval.stmtval) = HANDLE_CONTINUE(); 
                        else {
                            fprintf(stderr, "Line %d: Continue outside loop\n", yylineno);
                            exit(1);
                        }
                }
#line 2296 "parser.c"
    break;


#line 2300 "parser.c"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 294 "parser.y"


int yyerror(char *message){
    printf("Error on line %d: %s\n", yylineno, message);
    return -1;
}

int main(int argc, char **argv) {
    head = SymTable_new();
    current_table = head;

    libFunc(head, "print");
    libFunc(head, "input");
    libFunc(head, "objectmemberkeys");
    libFunc(head, "objecttotalmembers");
    libFunc(head, "objectcopy");
    libFunc(head, "totalarguments");
    libFunc(head, "argument");
    libFunc(head, "typeof");
    libFunc(head, "strtonum");
    libFunc(head, "sqrt");
    libFunc(head, "cos");
    libFunc(head, "sin");

	if(argc > 3) {
		fprintf(stderr, "Invalid argument format\nUsage: %s <input_file> [<output_file>]", argv[0]);
		exit(0);
	}

    if(argc == 1) {
		yyin = stdin;
    }
	else {
		if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "There was an error reading the input file, make sure it exists and the path is written correnctly");
            exit(0);
        }
	}

	// If an output file was given, redirect what would be printed in stdout to that file
	if(argc == 3 && !freopen(argv[2], "w", stdout)) {
		fprintf(stderr, "There was an error reading the output file, make sure it exists and the path is written correnctly");
		exit(0);
	}

	yyparse();
    SymTable_print(head);

	FILE *fptr = fopen(argv[1], "r");
	char c;

	printf("Source: \n");
	c = fgetc(fptr);
    while (c != EOF) {
        printf ("%c", c);
        c = fgetc(fptr);
	}
	printf("\n");

    printQuads();
    generate_all();
    return 0;	
}
