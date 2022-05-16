/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_FOR = 9,                        /* FOR  */
  YYSYMBOL_FUNCTION = 10,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_BREAK = 12,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_NOT = 15,                       /* NOT  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_LOCAL = 17,                     /* LOCAL  */
  YYSYMBOL_TRUE = 18,                      /* TRUE  */
  YYSYMBOL_FALSE = 19,                     /* FALSE  */
  YYSYMBOL_NIL = 20,                       /* NIL  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 22,                      /* PLUS  */
  YYSYMBOL_MINUS = 23,                     /* MINUS  */
  YYSYMBOL_MUL = 24,                       /* MUL  */
  YYSYMBOL_DIV = 25,                       /* DIV  */
  YYSYMBOL_MOD = 26,                       /* MOD  */
  YYSYMBOL_EQUAL = 27,                     /* EQUAL  */
  YYSYMBOL_NEQUAL = 28,                    /* NEQUAL  */
  YYSYMBOL_INC = 29,                       /* INC  */
  YYSYMBOL_DEC = 30,                       /* DEC  */
  YYSYMBOL_GT = 31,                        /* GT  */
  YYSYMBOL_LT = 32,                        /* LT  */
  YYSYMBOL_GET = 33,                       /* GET  */
  YYSYMBOL_LET = 34,                       /* LET  */
  YYSYMBOL_CURLY_OPEN = 35,                /* CURLY_OPEN  */
  YYSYMBOL_CURLY_CLOSED = 36,              /* CURLY_CLOSED  */
  YYSYMBOL_SQUARE_OPEN = 37,               /* SQUARE_OPEN  */
  YYSYMBOL_SQUARE_CLOSED = 38,             /* SQUARE_CLOSED  */
  YYSYMBOL_PAR_OPEN = 39,                  /* PAR_OPEN  */
  YYSYMBOL_PAR_CLOSED = 40,                /* PAR_CLOSED  */
  YYSYMBOL_SEMI_COLON = 41,                /* SEMI_COLON  */
  YYSYMBOL_COMMA = 42,                     /* COMMA  */
  YYSYMBOL_COLON = 43,                     /* COLON  */
  YYSYMBOL_DOUBLE_COLON = 44,              /* DOUBLE_COLON  */
  YYSYMBOL_DOT = 45,                       /* DOT  */
  YYSYMBOL_DOUBLE_DOT = 46,                /* DOUBLE_DOT  */
  YYSYMBOL_UMINUS = 47,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 48,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_statements = 51,                /* statements  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_statement = 53,                 /* statement  */
  YYSYMBOL_expression = 54,                /* expression  */
  YYSYMBOL_term = 55,                      /* term  */
  YYSYMBOL_assignexpr = 56,                /* assignexpr  */
  YYSYMBOL_prim = 57,                      /* prim  */
  YYSYMBOL_lvalue = 58,                    /* lvalue  */
  YYSYMBOL_member = 59,                    /* member  */
  YYSYMBOL_call = 60,                      /* call  */
  YYSYMBOL_callsuffix = 61,                /* callsuffix  */
  YYSYMBOL_normcall = 62,                  /* normcall  */
  YYSYMBOL_methodcall = 63,                /* methodcall  */
  YYSYMBOL_elist = 64,                     /* elist  */
  YYSYMBOL_objectdef = 65,                 /* objectdef  */
  YYSYMBOL_objectarg = 66,                 /* objectarg  */
  YYSYMBOL_indexed = 67,                   /* indexed  */
  YYSYMBOL_indexedelem = 68,               /* indexedelem  */
  YYSYMBOL_block = 69,                     /* block  */
  YYSYMBOL_70_2 = 70,                      /* $@2  */
  YYSYMBOL_funcdef = 71,                   /* funcdef  */
  YYSYMBOL_funcbody = 72,                  /* funcbody  */
  YYSYMBOL_funcprefix = 73,                /* funcprefix  */
  YYSYMBOL_funcargs = 74,                  /* funcargs  */
  YYSYMBOL_75_3 = 75,                      /* $@3  */
  YYSYMBOL_76_4 = 76,                      /* $@4  */
  YYSYMBOL_funcname = 77,                  /* funcname  */
  YYSYMBOL_const = 78,                     /* const  */
  YYSYMBOL_idlist = 79,                    /* idlist  */
  YYSYMBOL_ifstmt = 80,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 81,                 /* whilestmt  */
  YYSYMBOL_forstmt = 82,                   /* forstmt  */
  YYSYMBOL_returnstmt = 83                 /* returnstmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   550

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
static const yytype_uint8 yyrline[] =
{
       0,    68,    68,    71,    71,    72,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   104,   105,   106,   107,   108,   109,   110,   111,   114,
     116,   117,   118,   119,   120,   123,   124,   125,   126,   129,
     130,   131,   132,   135,   136,   137,   140,   141,   144,   146,
     148,   149,   150,   153,   155,   156,   159,   160,   163,   165,
     165,   167,   169,   174,   177,   182,   176,   193,   194,   197,
     198,   199,   200,   201,   204,   205,   208,   209,   212,   214,
     216,   217
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "IDENT",
  "STRING", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK",
  "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE", "NIL",
  "ASSIGN", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQUAL", "NEQUAL", "INC",
  "DEC", "GT", "LT", "GET", "LET", "CURLY_OPEN", "CURLY_CLOSED",
  "SQUARE_OPEN", "SQUARE_CLOSED", "PAR_OPEN", "PAR_CLOSED", "SEMI_COLON",
  "COMMA", "COLON", "DOUBLE_COLON", "DOT", "DOUBLE_DOT", "UMINUS",
  "LOWER_THAN_ELSE", "$accept", "program", "statements", "$@1",
  "statement", "expression", "term", "assignexpr", "prim", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "objectdef", "objectarg", "indexed", "indexedelem", "block", "$@2",
  "funcdef", "funcbody", "funcprefix", "funcargs", "$@3", "$@4",
  "funcname", "const", "idlist", "ifstmt", "whilestmt", "forstmt",
  "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
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
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -107,     6,    10,  -107,   101,  -107,  -107,  -107,   -18,     8,
      13,    18,   149,    14,    17,   217,    45,  -107,  -107,  -107,
       1,     1,  -107,     9,   194,  -107,    47,   217,  -107,   286,
    -107,  -107,  -107,   155,  -107,   -20,  -107,  -107,  -107,    20,
    -107,  -107,  -107,  -107,  -107,   217,   217,   217,  -107,  -107,
    -107,   307,  -107,  -107,  -107,  -107,    50,   -30,   -20,   -30,
    -107,   217,   265,  -107,    24,  -107,    22,   349,    25,  -107,
    -107,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,  -107,   217,  -107,  -107,   217,   217,
      62,    76,  -107,  -107,  -107,   217,   217,    78,  -107,    48,
     370,   391,    49,  -107,    52,    57,   243,   217,  -107,    64,
    -107,    61,   503,   490,    11,    11,  -107,  -107,  -107,   516,
     516,    63,    63,    63,    63,   475,   412,    68,  -107,    83,
     433,    77,  -107,    98,  -107,  -107,   101,   101,   217,    61,
    -107,   217,  -107,  -107,   217,  -107,  -107,   217,  -107,  -107,
      81,  -107,    96,  -107,   328,   454,    84,    85,    98,    86,
     101,   217,  -107,  -107,  -107,  -107,  -107,  -107,    87,   101,
    -107
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     3,     1,     0,    79,    45,    80,     0,     0,
       0,    78,     0,     0,     0,     0,     0,    82,    83,    81,
       0,     0,    69,    62,     0,    15,     0,     0,     4,     0,
      30,    16,    38,    40,    48,    41,    42,    13,    14,     0,
      44,     7,     8,     9,    10,     0,     0,    62,    77,    73,
      90,     0,    11,    12,    33,    46,     0,    34,     0,    36,
       5,     0,    60,    64,     0,    65,    66,     0,     0,    47,
      32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     0,    35,    37,     0,    62,
       0,     0,    54,    56,    57,     0,    62,     0,    74,     0,
       0,     0,     0,    91,     0,     3,     0,    62,    63,     0,
      31,    43,    28,    29,    17,    18,    19,    20,    21,    26,
      27,    22,    24,    23,    25,    39,     0,     0,    49,     0,
       0,     0,    51,     0,    72,    71,     0,     0,     0,     0,
      70,     0,    61,    67,    62,    50,    58,    62,    52,    53,
      84,    75,    86,    88,     0,     0,     0,     0,     0,     0,
       0,    62,    68,    55,    59,    85,    76,    87,     0,     0,
      89
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -107,  -107,    69,  -107,  -106,    -4,  -107,  -107,  -107,   -17,
    -107,    12,  -107,  -107,  -107,   -46,  -107,  -107,    19,  -107,
      36,  -107,   -22,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
     -19,  -107,  -107,  -107,  -107
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     4,    28,    62,    30,    31,    32,    33,
      34,    35,    92,    93,    94,    63,    36,    64,    65,    66,
      37,    60,    38,   135,    39,    99,   133,   159,    49,    40,
     151,    41,    42,    43,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   102,    68,    57,    59,     6,     3,    88,    51,    89,
      -2,    54,     5,     6,     7,    90,    91,    95,    16,    96,
      67,    45,    48,    70,    15,    97,    16,    17,    18,    19,
     152,   153,    58,    58,   104,    75,    76,    77,    20,    21,
      56,   100,   101,   127,    61,    26,    23,    46,    24,    55,
     131,    69,    47,    26,   167,    52,    27,   106,    53,    98,
      11,   142,   108,   170,   109,   111,   128,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     129,   125,   132,    22,   126,    73,    74,    75,    76,    77,
     138,   130,   139,   140,    -3,    -3,    -3,    -3,   156,    61,
     144,   157,   150,   160,     5,     6,     7,     8,   146,     9,
      10,    11,    12,    13,    14,   168,    15,   149,    16,    17,
      18,    19,   147,   158,   163,   164,   166,   169,   143,   105,
      20,    21,    29,    29,   154,   134,    22,   155,    23,   165,
      24,     0,    25,     0,     0,    26,     0,     0,    27,     0,
       0,     0,     5,     6,     7,     0,    29,     0,     0,     0,
       0,     0,     0,     0,    15,    29,    16,    17,    18,    19,
       0,     0,     0,     0,     0,     0,    85,     0,    20,    21,
       0,     0,     0,     0,    86,    87,    23,     0,    24,     0,
      50,     0,    88,    26,    89,     0,    27,     5,     6,     7,
      90,    91,     0,     0,    11,     0,     0,     0,     0,    15,
       0,    16,    17,    18,    19,     0,     0,     0,     0,     0,
       5,     6,     7,    20,    21,     0,     0,     0,     0,     0,
       0,    23,    15,    24,    16,    17,    18,    19,    26,     0,
       0,    27,     0,     0,     0,     0,    20,    21,     0,     0,
       0,     0,     0,     0,    23,     0,    24,    71,     0,    72,
       0,    26,     0,     0,    27,    73,    74,    75,    76,    77,
      78,    79,     0,     0,    80,    81,    82,    83,     0,    71,
       0,    72,     0,     0,     0,     0,   141,    73,    74,    75,
      76,    77,    78,    79,     0,     0,    80,    81,    82,    83,
      71,     0,    72,     0,     0,     0,     0,   107,    73,    74,
      75,    76,    77,    78,    79,     0,     0,    80,    81,    82,
      83,    71,     0,    72,     0,     0,     0,    84,     0,    73,
      74,    75,    76,    77,    78,    79,     0,     0,    80,    81,
      82,    83,    71,     0,    72,     0,     0,     0,   103,     0,
      73,    74,    75,    76,    77,    78,    79,     0,     0,    80,
      81,    82,    83,    71,     0,    72,     0,     0,     0,   161,
       0,    73,    74,    75,    76,    77,    78,    79,     0,     0,
      80,    81,    82,    83,    71,     0,    72,     0,     0,   110,
       0,     0,    73,    74,    75,    76,    77,    78,    79,     0,
       0,    80,    81,    82,    83,    71,     0,    72,     0,     0,
     136,     0,     0,    73,    74,    75,    76,    77,    78,    79,
       0,     0,    80,    81,    82,    83,    71,     0,    72,     0,
       0,   137,     0,     0,    73,    74,    75,    76,    77,    78,
      79,     0,     0,    80,    81,    82,    83,    71,     0,    72,
     145,     0,     0,     0,     0,    73,    74,    75,    76,    77,
      78,    79,     0,     0,    80,    81,    82,    83,    71,     0,
      72,   148,     0,     0,     0,     0,    73,    74,    75,    76,
      77,    78,    79,     0,     0,    80,    81,    82,    83,    71,
     162,    72,     0,     0,     0,     0,     0,    73,    74,    75,
      76,    77,    78,    79,    71,     0,    80,    81,    82,    83,
       0,     0,    73,    74,    75,    76,    77,    78,    79,     0,
       0,    80,    81,    82,    83,    73,    74,    75,    76,    77,
      78,    79,     0,     0,    80,    81,    82,    83,    73,    74,
      75,    76,    77,    -3,    -3,     0,     0,    80,    81,    82,
      83
};

static const yytype_int16 yycheck[] =
{
       4,    47,    24,    20,    21,     4,     0,    37,    12,    39,
       0,    15,     3,     4,     5,    45,    46,    37,    17,    39,
      24,    39,     4,    27,    15,    45,    17,    18,    19,    20,
     136,   137,    20,    21,    56,    24,    25,    26,    29,    30,
      39,    45,    46,    89,    35,    44,    37,    39,    39,     4,
      96,     4,    39,    44,   160,    41,    47,    61,    41,    39,
      10,   107,    38,   169,    42,    40,     4,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       4,    85,     4,    35,    88,    22,    23,    24,    25,    26,
      41,    95,    40,    36,    31,    32,    33,    34,   144,    35,
      39,   147,     4,     7,     3,     4,     5,     6,    40,     8,
       9,    10,    11,    12,    13,   161,    15,    40,    17,    18,
      19,    20,    39,    42,    40,    40,    40,    40,   109,    60,
      29,    30,   136,   137,   138,    99,    35,   141,    37,   158,
      39,    -1,    41,    -1,    -1,    44,    -1,    -1,    47,    -1,
      -1,    -1,     3,     4,     5,    -1,   160,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,   169,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    29,    30,
      -1,    -1,    -1,    -1,    29,    30,    37,    -1,    39,    -1,
      41,    -1,    37,    44,    39,    -1,    47,     3,     4,     5,
      45,    46,    -1,    -1,    10,    -1,    -1,    -1,    -1,    15,
      -1,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    29,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    15,    39,    17,    18,    19,    20,    44,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    39,    14,    -1,    16,
      -1,    44,    -1,    -1,    47,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    -1,    14,
      -1,    16,    -1,    -1,    -1,    -1,    43,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    31,    32,    33,    34,
      14,    -1,    16,    -1,    -1,    -1,    -1,    42,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    33,
      34,    14,    -1,    16,    -1,    -1,    -1,    41,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    32,
      33,    34,    14,    -1,    16,    -1,    -1,    -1,    41,    -1,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    31,
      32,    33,    34,    14,    -1,    16,    -1,    -1,    -1,    41,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    14,    -1,    16,    -1,    -1,    40,
      -1,    -1,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    31,    32,    33,    34,    14,    -1,    16,    -1,    -1,
      40,    -1,    -1,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    31,    32,    33,    34,    14,    -1,    16,    -1,
      -1,    40,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,    33,    34,    14,    -1,    16,
      38,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    14,    -1,
      16,    38,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,    33,    34,    14,
      36,    16,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    14,    -1,    31,    32,    33,    34,
      -1,    -1,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    31,    32,    33,    34,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    33,
      34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,    52,     3,     4,     5,     6,     8,
       9,    10,    11,    12,    13,    15,    17,    18,    19,    20,
      29,    30,    35,    37,    39,    41,    44,    47,    53,    54,
      55,    56,    57,    58,    59,    60,    65,    69,    71,    73,
      78,    80,    81,    82,    83,    39,    39,    39,     4,    77,
      41,    54,    41,    41,    54,     4,    39,    58,    60,    58,
      70,    35,    54,    64,    66,    67,    68,    54,    71,     4,
      54,    14,    16,    22,    23,    24,    25,    26,    27,    28,
      31,    32,    33,    34,    41,    21,    29,    30,    37,    39,
      45,    46,    61,    62,    63,    37,    39,    45,    39,    74,
      54,    54,    64,    41,    71,    51,    54,    42,    38,    42,
      40,    40,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    64,     4,     4,
      54,    64,     4,    75,    69,    72,    40,    40,    41,    40,
      36,    43,    64,    67,    39,    38,    40,    39,    38,    40,
       4,    79,    53,    53,    54,    54,    64,    64,    42,    76,
       7,    41,    36,    40,    40,    79,    40,    53,    64,    40,
      53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    52,    51,    51,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    62,    63,
      64,    64,    64,    65,    66,    66,    67,    67,    68,    70,
      69,    71,    72,    73,    75,    76,    74,    77,    77,    78,
      78,    78,    78,    78,    79,    79,    80,    80,    81,    82,
      83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     3,     0,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     2,     2,     2,     2,     2,     2,     1,     3,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       1,     3,     0,     3,     1,     1,     1,     3,     5,     0,
       4,     3,     1,     2,     0,     0,     5,     1,     0,     1,
       1,     1,     1,     1,     1,     3,     5,     7,     5,     9,
       2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

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
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 3: /* $@1: %empty  */
#line 71 "parser.y"
                           {resetTemp();}
#line 1369 "parser.c"
    break;

  case 16: /* expression: assignexpr  */
#line 87 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1375 "parser.c"
    break;

  case 31: /* term: PAR_OPEN expression PAR_CLOSED  */
#line 104 "parser.y"
                                                {(yyval.exprval) = (yyvsp[-1].exprval);}
#line 1381 "parser.c"
    break;

  case 32: /* term: UMINUS expression  */
#line 105 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_UMINUS_EXPR((yyvsp[0].exprval));}
#line 1387 "parser.c"
    break;

  case 33: /* term: NOT expression  */
#line 106 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_NOT_EXPR((yyvsp[0].exprval));}
#line 1393 "parser.c"
    break;

  case 34: /* term: INC lvalue  */
#line 107 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_INC_LVALUE((yyvsp[0].exprval), yylineno);}
#line 1399 "parser.c"
    break;

  case 35: /* term: lvalue INC  */
#line 108 "parser.y"
                                                {(yyval.exprval) = HANDLE_TERM_TO_LVALUE_INC((yyvsp[-1].exprval), yylineno);}
#line 1405 "parser.c"
    break;

  case 36: /* term: DEC lvalue  */
#line 109 "parser.y"
                                                {HANDLE_TERM_TO_DEC_LVALUE((yyvsp[0].exprval), yylineno);}
#line 1411 "parser.c"
    break;

  case 37: /* term: lvalue DEC  */
#line 110 "parser.y"
                                                {HANDLE_TERM_TO_LVALUE_DEC((yyvsp[-1].exprval), yylineno);}
#line 1417 "parser.c"
    break;

  case 38: /* term: prim  */
#line 111 "parser.y"
                                                {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1423 "parser.c"
    break;

  case 39: /* assignexpr: lvalue ASSIGN expression  */
#line 114 "parser.y"
                                                {HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION((yyvsp[-2].exprval), (yyvsp[0].exprval), yylineno);}
#line 1429 "parser.c"
    break;

  case 40: /* prim: lvalue  */
#line 116 "parser.y"
                                                {HANDLE_PRIM_TO_LVALUE((yyvsp[0].exprval), yylineno);}
#line 1435 "parser.c"
    break;

  case 43: /* prim: PAR_OPEN funcdef PAR_CLOSED  */
#line 119 "parser.y"
                                                {(yyval.exprval) = HANDLE_PRIM_TO_FUNCDEF((yyvsp[-1].symval));}
#line 1441 "parser.c"
    break;

  case 45: /* lvalue: IDENT  */
#line 123 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_IDENT((yyvsp[0].sval), yylineno);}
#line 1447 "parser.c"
    break;

  case 46: /* lvalue: LOCAL IDENT  */
#line 124 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_LOCAL_IDENT((yyvsp[0].sval), yylineno);}
#line 1453 "parser.c"
    break;

  case 47: /* lvalue: DOUBLE_COLON IDENT  */
#line 125 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_GLOBAL_IDENT((yyvsp[0].sval), yylineno);}
#line 1459 "parser.c"
    break;

  case 48: /* lvalue: member  */
#line 126 "parser.y"
                                        {(yyval.exprval) = (yyvsp[0].exprval);}
#line 1465 "parser.c"
    break;

  case 49: /* member: lvalue DOT IDENT  */
#line 129 "parser.y"
                                                                {(yyval.exprval) = HANDLE_MEMBER_TO_LVALUE_DOT_IDENT((yyvsp[-2].exprval), (yyvsp[0].sval));}
#line 1471 "parser.c"
    break;

  case 50: /* member: lvalue SQUARE_OPEN expression SQUARE_CLOSED  */
#line 130 "parser.y"
                                                                {(yyval.exprval) = HANDLE_MEMBER_TO_LVALUE_SQUARE_EXPR((yyvsp[-3].exprval), (yyvsp[-1].exprval));}
#line 1477 "parser.c"
    break;

  case 53: /* call: call PAR_OPEN elist PAR_CLOSED  */
#line 135 "parser.y"
                                                                            {(yyval.exprval) = HANDLE_CALL_ELIST((yyvsp[-3].exprval), (yyvsp[-1].exprval));}
#line 1483 "parser.c"
    break;

  case 54: /* call: lvalue callsuffix  */
#line 136 "parser.y"
                                                                            {(yyval.exprval) = HANDLE_CALL_LVALUE_SUFFIX((yyvsp[-1].exprval), (yyvsp[0].callval));}
#line 1489 "parser.c"
    break;

  case 55: /* call: PAR_OPEN funcdef PAR_CLOSED PAR_OPEN elist PAR_CLOSED  */
#line 137 "parser.y"
                                                                            {(yyval.exprval) = HANDLE_CALL_FUNCDEF_ELIST((yyvsp[-4].symval), (yyvsp[-1].exprval));}
#line 1495 "parser.c"
    break;

  case 56: /* callsuffix: normcall  */
#line 140 "parser.y"
                                {(yyval.callval) = (yyvsp[0].callval);}
#line 1501 "parser.c"
    break;

  case 57: /* callsuffix: methodcall  */
#line 141 "parser.y"
                                {(yyval.callval) = (yyvsp[0].callval);}
#line 1507 "parser.c"
    break;

  case 58: /* normcall: PAR_OPEN elist PAR_CLOSED  */
#line 144 "parser.y"
                                                               {(yyval.callval) = HANDLE_NORMCALL((yyvsp[-1].exprval));}
#line 1513 "parser.c"
    break;

  case 59: /* methodcall: DOUBLE_DOT IDENT PAR_OPEN elist PAR_CLOSED  */
#line 146 "parser.y"
                                                               {(yyval.callval) = HANDLE_METHODCALL((yyvsp[-3].sval), (yyvsp[-1].exprval));}
#line 1519 "parser.c"
    break;

  case 63: /* objectdef: SQUARE_OPEN objectarg SQUARE_CLOSED  */
#line 153 "parser.y"
                                                     {(yyval.exprval) = (yyvsp[-1].exprval);}
#line 1525 "parser.c"
    break;

  case 64: /* objectarg: elist  */
#line 155 "parser.y"
                            {(yyval.exprval) = HANDLE_OBJECTDEF_TO_ELIST((yyvsp[0].exprval));}
#line 1531 "parser.c"
    break;

  case 65: /* objectarg: indexed  */
#line 156 "parser.y"
                            {(yyval.exprval) = HANDLE_OBJECTDEF_TO_INDEXED((yyvsp[0].exprval));}
#line 1537 "parser.c"
    break;

  case 68: /* indexedelem: CURLY_OPEN expression COLON expression CURLY_CLOSED  */
#line 163 "parser.y"
                                                                    {(yyval.exprval) = HANDLE_INDEXELEM((yyvsp[-3].exprval), (yyvsp[-1].exprval));}
#line 1543 "parser.c"
    break;

  case 69: /* $@2: %empty  */
#line 165 "parser.y"
                           {scope++; current_table = SymTable_next(current_table);}
#line 1549 "parser.c"
    break;

  case 70: /* block: CURLY_OPEN $@2 statements CURLY_CLOSED  */
#line 165 "parser.y"
                                                                                                            {scope--; SymTable_hide(current_table); current_table = SymTable_prev(current_table);}
#line 1555 "parser.c"
    break;

  case 71: /* funcdef: funcprefix funcargs funcbody  */
#line 167 "parser.y"
                                             {(yyval.symval) = HANDLE_FUNCDEF((yyvsp[-2].symval), (yyvsp[0].func_addr), yylineno);}
#line 1561 "parser.c"
    break;

  case 72: /* funcbody: block  */
#line 169 "parser.y"
                      {
                    (yyval.func_addr) = currScopeOffset();
                    exitScopeSpace();
                }
#line 1570 "parser.c"
    break;

  case 73: /* funcprefix: FUNCTION funcname  */
#line 174 "parser.y"
                                  {(yyval.symval) = HANDLE_FUNCPREFIX((yyvsp[0].sval), yylineno);}
#line 1576 "parser.c"
    break;

  case 74: /* $@3: %empty  */
#line 177 "parser.y"
                {
                    scope++; 
                    current_table = SymTable_next(current_table);
                }
#line 1585 "parser.c"
    break;

  case 75: /* $@4: %empty  */
#line 182 "parser.y"
                {
                    scope--;
                    current_table = SymTable_prev(current_table); 
                    functionScopeStack = stack_push(functionScopeStack, scope);
                }
#line 1595 "parser.c"
    break;

  case 76: /* funcargs: PAR_OPEN $@3 idlist $@4 PAR_CLOSED  */
#line 188 "parser.y"
                {
                    enterScopeSpace();
                    resetFunctionLocalOffset();
                }
#line 1604 "parser.c"
    break;

  case 77: /* funcname: IDENT  */
#line 193 "parser.y"
                               {(yyval.sval) = HANDLE_FUNCTION_WITH_NAME((yyvsp[0].sval), yylineno);}
#line 1610 "parser.c"
    break;

  case 78: /* funcname: %empty  */
#line 194 "parser.y"
                               {(yyval.sval) = HANDLE_FUNCTION_WITHOUT_NAME(yylineno);}
#line 1616 "parser.c"
    break;

  case 79: /* const: NUM  */
#line 197 "parser.y"
                            {(yyval.exprval) = newExprConstNum((yyvsp[0].nval));}
#line 1622 "parser.c"
    break;

  case 80: /* const: STRING  */
#line 198 "parser.y"
                            {(yyval.exprval) = newExprConstString((yyvsp[0].sval));}
#line 1628 "parser.c"
    break;

  case 81: /* const: NIL  */
#line 199 "parser.y"
                            {(yyval.exprval) = (struct Expr*) 0;}
#line 1634 "parser.c"
    break;

  case 82: /* const: TRUE  */
#line 200 "parser.y"
                            {(yyval.exprval) = newExprConstBool(1);}
#line 1640 "parser.c"
    break;

  case 83: /* const: FALSE  */
#line 201 "parser.y"
                            {(yyval.exprval) = newExprConstBool(0);}
#line 1646 "parser.c"
    break;

  case 84: /* idlist: IDENT  */
#line 204 "parser.y"
                                        {HANDLE_IDLIST_IDENT((yyvsp[0].sval), yylineno);}
#line 1652 "parser.c"
    break;

  case 85: /* idlist: IDENT COMMA idlist  */
#line 205 "parser.y"
                                        {/* TODO */}
#line 1658 "parser.c"
    break;


#line 1662 "parser.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 220 "parser.y"


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
    printQuads();
    return 0;	
}
