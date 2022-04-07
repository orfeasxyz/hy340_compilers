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
    #include "symtable.h"
    #include "structs.h"
    #include "func_stack.h"
	#include "rule_handler.h"
	#include "parser.h"

    int yyerror(char* message);
    int yylex(void);
    
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    SymTable_T head;
    SymTable_T current_table;

    int scope = 0;
    int anon_counter = 0;

#line 97 "parser.c"

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
  YYSYMBOL_statement = 52,                 /* statement  */
  YYSYMBOL_expression = 53,                /* expression  */
  YYSYMBOL_term = 54,                      /* term  */
  YYSYMBOL_assignexpr = 55,                /* assignexpr  */
  YYSYMBOL_prim = 56,                      /* prim  */
  YYSYMBOL_lvalue = 57,                    /* lvalue  */
  YYSYMBOL_member = 58,                    /* member  */
  YYSYMBOL_call = 59,                      /* call  */
  YYSYMBOL_callsuffix = 60,                /* callsuffix  */
  YYSYMBOL_normcall = 61,                  /* normcall  */
  YYSYMBOL_methodcall = 62,                /* methodcall  */
  YYSYMBOL_elist = 63,                     /* elist  */
  YYSYMBOL_elist_alt = 64,                 /* elist_alt  */
  YYSYMBOL_objectdef = 65,                 /* objectdef  */
  YYSYMBOL_indexed = 66,                   /* indexed  */
  YYSYMBOL_indexed_alt = 67,               /* indexed_alt  */
  YYSYMBOL_indexedelem = 68,               /* indexedelem  */
  YYSYMBOL_block = 69,                     /* block  */
  YYSYMBOL_70_1 = 70,                      /* $@1  */
  YYSYMBOL_funcdef = 71,                   /* funcdef  */
  YYSYMBOL_72_2 = 72,                      /* $@2  */
  YYSYMBOL_73_3 = 73,                      /* $@3  */
  YYSYMBOL_funcname = 74,                  /* funcname  */
  YYSYMBOL_const = 75,                     /* const  */
  YYSYMBOL_idlist = 76,                    /* idlist  */
  YYSYMBOL_idlist_alt = 77,                /* idlist_alt  */
  YYSYMBOL_ifstmt = 78,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 79,                 /* whilestmt  */
  YYSYMBOL_forstmt = 80,                   /* forstmt  */
  YYSYMBOL_returnstmt = 81                 /* returnstmt  */
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
#define YYLAST   583

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

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
       0,    65,    65,    67,    68,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
     100,   101,   102,   103,   104,   105,   106,   107,   110,   112,
     113,   114,   115,   116,   119,   120,   121,   122,   125,   126,
     127,   128,   131,   132,   133,   136,   137,   140,   142,   144,
     145,   148,   149,   152,   153,   154,   155,   156,   159,   160,
     163,   164,   167,   169,   169,   171,   171,   171,   173,   174,
     177,   177,   177,   177,   177,   179,   180,   183,   184,   187,
     188,   191,   193,   195,   196
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
  "LOWER_THAN_ELSE", "$accept", "program", "statements", "statement",
  "expression", "term", "assignexpr", "prim", "lvalue", "member", "call",
  "callsuffix", "normcall", "methodcall", "elist", "elist_alt",
  "objectdef", "indexed", "indexed_alt", "indexedelem", "block", "$@1",
  "funcdef", "$@2", "$@3", "funcname", "const", "idlist", "idlist_alt",
  "ifstmt", "whilestmt", "forstmt", "returnstmt", YY_NULLPTR
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

#define YYPACT_NINF (-128)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -128,     6,   155,  -128,  -128,  -128,  -128,   -26,   -22,   -16,
       4,   200,   -23,   -14,   251,    21,  -128,  -128,  -128,    15,
      15,  -128,    11,   206,  -128,    30,   251,  -128,   319,  -128,
    -128,  -128,   228,  -128,    41,  -128,  -128,  -128,    -4,  -128,
    -128,  -128,  -128,  -128,   251,   251,   251,  -128,  -128,   340,
    -128,  -128,  -128,  -128,    29,    -1,    41,    -1,  -128,   251,
    -128,   277,   -31,   382,     7,  -128,  -128,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
    -128,   251,  -128,  -128,   251,   251,    49,    52,  -128,  -128,
    -128,   251,   251,    60,  -128,   403,   424,   298,    40,  -128,
      50,   105,    69,  -128,   251,  -128,    63,  -128,    82,   536,
     523,    80,    80,  -128,  -128,  -128,   549,   549,   253,   253,
     253,   253,   508,   445,    67,  -128,    87,   466,    79,  -128,
     123,   155,   155,   251,  -128,   251,    82,  -128,   251,    90,
      94,    95,   251,  -128,  -128,   251,  -128,  -128,    96,    99,
     136,  -128,   298,   361,   487,  -128,  -128,    63,  -128,   107,
     108,   141,  -128,  -128,   155,  -128,   251,  -128,    95,  -128,
    -128,    96,   115,  -128,   111,  -128,  -128,  -128,   155,  -128
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    80,    44,    81,     0,     0,     0,
      79,     0,     0,     0,     0,     0,    83,    84,    82,     0,
       0,    73,     0,     0,    14,     0,     0,     3,     0,    29,
      15,    37,    39,    47,    40,    41,    12,    13,     0,    43,
       6,     7,     8,     9,     0,     0,    60,    78,    93,     0,
      10,    11,    32,    45,     0,    33,     0,    35,     4,     0,
      67,     0,     0,     0,     0,    46,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     0,    34,    36,     0,    60,     0,     0,    53,    55,
      56,     0,    60,     0,    75,     0,     0,    62,     0,    94,
       0,     0,     0,    63,    60,    65,    69,    30,    42,    27,
      28,    16,    17,    18,    19,    20,    25,    26,    21,    23,
      22,    24,    38,     0,     0,    48,     0,     0,     0,    50,
      86,     0,     0,     0,    59,     0,     0,    74,     0,     0,
       0,    71,    60,    49,    57,    60,    51,    52,    88,     0,
      89,    91,    62,     0,     0,    64,    66,     0,    68,     0,
       0,     0,    85,    76,     0,    61,    60,    72,    71,    54,
      58,    88,     0,    90,     0,    70,    87,    77,     0,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -128,    97,  -127,    -2,  -128,  -128,  -128,    42,  -128,
      68,  -128,  -128,  -128,   -82,     1,  -128,  -128,   -12,  -105,
     -18,  -128,   -21,  -128,  -128,  -128,  -128,  -128,     0,  -128,
    -128,  -128,  -128
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    27,    97,    29,    30,    31,    32,    33,
      34,    88,    89,    90,    98,   134,    35,   140,   158,    62,
      36,    58,    37,   130,   172,    38,    39,   149,   162,    40,
      41,    42,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,   141,    64,   124,   150,   151,     3,   105,    47,    49,
     128,   106,    52,    44,     4,     5,     6,    45,    50,     5,
      61,    63,   139,    46,    66,    53,    14,    51,    15,    16,
      17,    18,    15,   100,    65,    94,    84,   173,    85,    10,
      19,    20,    95,    96,    86,    87,    59,   108,    22,    60,
      23,   179,   168,   125,    54,    25,   126,   102,    26,    25,
     159,    55,    57,   160,   129,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    91,   122,
      92,   135,   123,    67,   174,    68,    93,    56,    56,   127,
     136,    69,    70,    71,    72,    73,    74,    75,    59,    28,
      76,    77,    78,    79,    71,    72,    73,   144,     4,     5,
       6,     7,   138,     8,     9,    10,    11,    12,    13,   147,
      14,   142,    15,    16,    17,    18,   145,   148,   155,    28,
      28,   152,   156,   153,    19,    20,   154,   157,   161,   163,
      21,   137,    22,   164,    23,   171,    24,   169,   170,    25,
      21,   178,    26,   165,   177,   101,   175,     0,     4,     5,
       6,     7,    28,     8,     9,    10,    11,    12,    13,     0,
      14,   176,    15,    16,    17,    18,    28,     0,     0,     0,
       0,     0,     0,     0,    19,    20,     0,     0,     0,     0,
      21,     0,    22,     0,    23,     0,    24,     0,     0,    25,
       0,     0,    26,     4,     5,     6,     0,     0,     0,     4,
       5,     6,     0,     0,     0,    14,    10,    15,    16,    17,
      18,    14,     0,    15,    16,    17,    18,     0,     0,    19,
      20,     0,     0,     0,     0,    19,    20,    22,     0,    23,
       0,    48,     0,    22,    25,    23,     0,    26,     0,    81,
      25,     0,     0,    26,     4,     5,     6,    82,    83,     0,
       0,     0,     0,     0,     0,    84,    14,    85,    15,    16,
      17,    18,     0,    86,    87,    69,    70,    71,    72,    73,
      19,    20,     0,     0,    -1,    -1,    -1,    -1,    22,     0,
      23,    67,     0,    68,     0,    25,     0,     0,    26,    69,
      70,    71,    72,    73,    74,    75,     0,     0,    76,    77,
      78,    79,    67,     0,    68,   103,     0,     0,     0,   104,
      69,    70,    71,    72,    73,    74,    75,     0,     0,    76,
      77,    78,    79,    67,     0,    68,     0,     0,     0,     0,
     133,    69,    70,    71,    72,    73,    74,    75,     0,     0,
      76,    77,    78,    79,    67,     0,    68,     0,     0,     0,
      80,     0,    69,    70,    71,    72,    73,    74,    75,     0,
       0,    76,    77,    78,    79,    67,     0,    68,     0,     0,
       0,    99,     0,    69,    70,    71,    72,    73,    74,    75,
       0,     0,    76,    77,    78,    79,    67,     0,    68,     0,
       0,     0,   166,     0,    69,    70,    71,    72,    73,    74,
      75,     0,     0,    76,    77,    78,    79,    67,     0,    68,
       0,     0,   107,     0,     0,    69,    70,    71,    72,    73,
      74,    75,     0,     0,    76,    77,    78,    79,    67,     0,
      68,     0,     0,   131,     0,     0,    69,    70,    71,    72,
      73,    74,    75,     0,     0,    76,    77,    78,    79,    67,
       0,    68,     0,     0,   132,     0,     0,    69,    70,    71,
      72,    73,    74,    75,     0,     0,    76,    77,    78,    79,
      67,     0,    68,   143,     0,     0,     0,     0,    69,    70,
      71,    72,    73,    74,    75,     0,     0,    76,    77,    78,
      79,    67,     0,    68,   146,     0,     0,     0,     0,    69,
      70,    71,    72,    73,    74,    75,     0,     0,    76,    77,
      78,    79,    67,   167,    68,     0,     0,     0,     0,     0,
      69,    70,    71,    72,    73,    74,    75,    67,     0,    76,
      77,    78,    79,     0,     0,    69,    70,    71,    72,    73,
      74,    75,     0,     0,    76,    77,    78,    79,    69,    70,
      71,    72,    73,    74,    75,     0,     0,    76,    77,    78,
      79,    69,    70,    71,    72,    73,    -1,    -1,     0,     0,
      76,    77,    78,    79
};

static const yytype_int16 yycheck[] =
{
       2,   106,    23,    85,   131,   132,     0,    38,     4,    11,
      92,    42,    14,    39,     3,     4,     5,    39,    41,     4,
      22,    23,   104,    39,    26,     4,    15,    41,    17,    18,
      19,    20,    17,    54,     4,    39,    37,   164,    39,    10,
      29,    30,    44,    45,    45,    46,    35,    40,    37,    38,
      39,   178,   157,     4,    39,    44,     4,    59,    47,    44,
     142,    19,    20,   145,     4,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    37,    81,
      39,    41,    84,    14,   166,    16,    45,    19,    20,    91,
      40,    22,    23,    24,    25,    26,    27,    28,    35,   101,
      31,    32,    33,    34,    24,    25,    26,    40,     3,     4,
       5,     6,    43,     8,     9,    10,    11,    12,    13,    40,
      15,    39,    17,    18,    19,    20,    39,     4,    38,   131,
     132,   133,    38,   135,    29,    30,   138,    42,    42,    40,
      35,    36,    37,     7,    39,     4,    41,    40,    40,    44,
      35,    40,    47,   152,   172,    58,   168,    -1,     3,     4,
       5,     6,   164,     8,     9,    10,    11,    12,    13,    -1,
      15,   171,    17,    18,    19,    20,   178,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      35,    -1,    37,    -1,    39,    -1,    41,    -1,    -1,    44,
      -1,    -1,    47,     3,     4,     5,    -1,    -1,    -1,     3,
       4,     5,    -1,    -1,    -1,    15,    10,    17,    18,    19,
      20,    15,    -1,    17,    18,    19,    20,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    29,    30,    37,    -1,    39,
      -1,    41,    -1,    37,    44,    39,    -1,    47,    -1,    21,
      44,    -1,    -1,    47,     3,     4,     5,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    15,    39,    17,    18,
      19,    20,    -1,    45,    46,    22,    23,    24,    25,    26,
      29,    30,    -1,    -1,    31,    32,    33,    34,    37,    -1,
      39,    14,    -1,    16,    -1,    44,    -1,    -1,    47,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    32,
      33,    34,    14,    -1,    16,    38,    -1,    -1,    -1,    42,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    31,
      32,    33,    34,    14,    -1,    16,    -1,    -1,    -1,    -1,
      42,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    14,    -1,    16,    -1,    -1,    -1,
      41,    -1,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    31,    32,    33,    34,    14,    -1,    16,    -1,    -1,
      -1,    41,    -1,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    31,    32,    33,    34,    14,    -1,    16,    -1,
      -1,    -1,    41,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,    33,    34,    14,    -1,    16,
      -1,    -1,    40,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    14,    -1,
      16,    -1,    -1,    40,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,    33,    34,    14,
      -1,    16,    -1,    -1,    40,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    31,    32,    33,    34,
      14,    -1,    16,    38,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    33,
      34,    14,    -1,    16,    38,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    32,
      33,    34,    14,    36,    16,    -1,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    26,    27,    28,    14,    -1,    31,
      32,    33,    34,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    33,
      34,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,     3,     4,     5,     6,     8,     9,
      10,    11,    12,    13,    15,    17,    18,    19,    20,    29,
      30,    35,    37,    39,    41,    44,    47,    52,    53,    54,
      55,    56,    57,    58,    59,    65,    69,    71,    74,    75,
      78,    79,    80,    81,    39,    39,    39,     4,    41,    53,
      41,    41,    53,     4,    39,    57,    59,    57,    70,    35,
      38,    53,    68,    53,    71,     4,    53,    14,    16,    22,
      23,    24,    25,    26,    27,    28,    31,    32,    33,    34,
      41,    21,    29,    30,    37,    39,    45,    46,    60,    61,
      62,    37,    39,    45,    39,    53,    53,    53,    63,    41,
      71,    51,    53,    38,    42,    38,    42,    40,    40,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    63,     4,     4,    53,    63,     4,
      72,    40,    40,    42,    64,    41,    40,    36,    43,    63,
      66,    68,    39,    38,    40,    39,    38,    40,     4,    76,
      52,    52,    53,    53,    53,    38,    38,    42,    67,    63,
      63,    42,    77,    40,     7,    64,    41,    36,    68,    40,
      40,     4,    73,    52,    63,    67,    77,    69,    40,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    59,    60,    60,    61,    62,    63,
      63,    64,    64,    65,    65,    65,    65,    65,    66,    66,
      67,    67,    68,    70,    69,    72,    73,    71,    74,    74,
      75,    75,    75,    75,    75,    76,    76,    77,    77,    78,
      78,    79,    80,    81,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     2,     6,     1,     1,     3,     5,     2,
       0,     3,     0,     3,     5,     3,     5,     2,     2,     0,
       3,     0,     5,     0,     4,     0,     0,     7,     2,     1,
       1,     1,     1,     1,     1,     2,     0,     3,     0,     5,
       7,     5,     9,     2,     3
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
  case 33: /* term: INC lvalue  */
#line 103 "parser.y"
                                        {HANDLE_TERM_TO_INC_LVALUE((yyvsp[0].exprval), func_stack_top());}
#line 1378 "parser.c"
    break;

  case 34: /* term: lvalue INC  */
#line 104 "parser.y"
                                        {HANDLE_TERM_TO_LVALUE_INC((yyvsp[-1].exprval), func_stack_top());}
#line 1384 "parser.c"
    break;

  case 35: /* term: DEC lvalue  */
#line 105 "parser.y"
                                        {HANDLE_TERM_TO_DEC_LVALUE((yyvsp[0].exprval), func_stack_top());}
#line 1390 "parser.c"
    break;

  case 36: /* term: lvalue DEC  */
#line 106 "parser.y"
                                        {HANDLE_TERM_TO_LVALUE_DEC((yyvsp[-1].exprval), func_stack_top());}
#line 1396 "parser.c"
    break;

  case 38: /* assignexpr: lvalue ASSIGN expression  */
#line 110 "parser.y"
                                        {HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION((yyvsp[-2].exprval), func_stack_top());}
#line 1402 "parser.c"
    break;

  case 39: /* prim: lvalue  */
#line 112 "parser.y"
                                        {HANDLE_PRIM_TO_LVALUE((yyvsp[0].exprval), func_stack_top());}
#line 1408 "parser.c"
    break;

  case 44: /* lvalue: IDENT  */
#line 119 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_IDENT(current_table, (yyvsp[0].sval), yylineno, scope);}
#line 1414 "parser.c"
    break;

  case 45: /* lvalue: LOCAL IDENT  */
#line 120 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_LOCAL_IDENT(current_table, head, (yyvsp[0].sval), yylineno, scope);}
#line 1420 "parser.c"
    break;

  case 46: /* lvalue: DOUBLE_COLON IDENT  */
#line 121 "parser.y"
                                        {(yyval.exprval) = HANDLE_LVALUE_TO_GLOBAL_IDENT(head, (yyvsp[0].sval), yylineno, scope);}
#line 1426 "parser.c"
    break;

  case 47: /* lvalue: member  */
#line 122 "parser.y"
                                        {}
#line 1432 "parser.c"
    break;

  case 73: /* $@1: %empty  */
#line 169 "parser.y"
                           {scope++; current_table = SymTable_next(current_table);}
#line 1438 "parser.c"
    break;

  case 74: /* block: CURLY_OPEN $@1 statements CURLY_CLOSED  */
#line 169 "parser.y"
                                                                                                            {scope--; SymTable_hide(current_table); current_table = SymTable_prev(current_table);}
#line 1444 "parser.c"
    break;

  case 75: /* $@2: %empty  */
#line 171 "parser.y"
                                  {scope++; current_table = SymTable_next(current_table);}
#line 1450 "parser.c"
    break;

  case 76: /* $@3: %empty  */
#line 171 "parser.y"
                                                                                                             {scope--; current_table = SymTable_prev(current_table); func_stack_push(scope);}
#line 1456 "parser.c"
    break;

  case 77: /* funcdef: funcname PAR_OPEN $@2 idlist PAR_CLOSED $@3 block  */
#line 171 "parser.y"
                                                                                                                                                                                                    {func_stack_pop();}
#line 1462 "parser.c"
    break;

  case 78: /* funcname: FUNCTION IDENT  */
#line 173 "parser.y"
                                        {(yyval.sval) = HANDLE_FUNCTION_WITH_NAME(current_table, (yyvsp[0].sval), yylineno, scope);}
#line 1468 "parser.c"
    break;

  case 79: /* funcname: FUNCTION  */
#line 174 "parser.y"
                                        {(yyval.sval) = HANDLE_FUNCTION_WITHOUT_NAME(current_table, anon_counter++, yylineno, scope);}
#line 1474 "parser.c"
    break;

  case 85: /* idlist: IDENT idlist_alt  */
#line 179 "parser.y"
                                        {HANDLE_IDLIST_IDENT(current_table, (yyvsp[-1].sval), yylineno, scope);}
#line 1480 "parser.c"
    break;

  case 87: /* idlist_alt: COMMA IDENT idlist_alt  */
#line 183 "parser.y"
                                        {HANDLE_IDLIST_IDENT(current_table, (yyvsp[-1].sval), yylineno, scope);}
#line 1486 "parser.c"
    break;


#line 1490 "parser.c"

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

#line 199 "parser.y"


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
    return 0;	
}
