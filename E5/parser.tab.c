/* A Bison parser, made by GNU Bison 3.8.2.  */

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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

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

int yylex(void);
void yyerror (char const *mensagem);
extern void *arvore;
extern int get_line_number();
#include <string.h>
#include "ast.h"
#include "stack.h"
#include "hash_table.h"
#include "iloc.h"

stack *scope_stack = NULL;
ast_node* current_function = NULL;
int rbss = 0;
int rfp = 0;

#line 88 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_PR_INT = 3,                  /* TK_PR_INT  */
  YYSYMBOL_TK_PR_FLOAT = 4,                /* TK_PR_FLOAT  */
  YYSYMBOL_TK_PR_BOOL = 5,                 /* TK_PR_BOOL  */
  YYSYMBOL_TK_PR_IF = 6,                   /* TK_PR_IF  */
  YYSYMBOL_TK_PR_ELSE = 7,                 /* TK_PR_ELSE  */
  YYSYMBOL_TK_PR_WHILE = 8,                /* TK_PR_WHILE  */
  YYSYMBOL_TK_PR_RETURN = 9,               /* TK_PR_RETURN  */
  YYSYMBOL_TK_OC_LE = 10,                  /* TK_OC_LE  */
  YYSYMBOL_TK_OC_GE = 11,                  /* TK_OC_GE  */
  YYSYMBOL_TK_OC_EQ = 12,                  /* TK_OC_EQ  */
  YYSYMBOL_TK_OC_NE = 13,                  /* TK_OC_NE  */
  YYSYMBOL_TK_OC_AND = 14,                 /* TK_OC_AND  */
  YYSYMBOL_TK_OC_OR = 15,                  /* TK_OC_OR  */
  YYSYMBOL_TK_IDENTIFICADOR = 16,          /* TK_IDENTIFICADOR  */
  YYSYMBOL_TK_LIT_INT = 17,                /* TK_LIT_INT  */
  YYSYMBOL_TK_LIT_FLOAT = 18,              /* TK_LIT_FLOAT  */
  YYSYMBOL_TK_LIT_FALSE = 19,              /* TK_LIT_FALSE  */
  YYSYMBOL_TK_LIT_TRUE = 20,               /* TK_LIT_TRUE  */
  YYSYMBOL_TK_ERRO = 21,                   /* TK_ERRO  */
  YYSYMBOL_22_ = 22,                       /* ';'  */
  YYSYMBOL_23_ = 23,                       /* '{'  */
  YYSYMBOL_24_ = 24,                       /* '!'  */
  YYSYMBOL_25_ = 25,                       /* '('  */
  YYSYMBOL_26_ = 26,                       /* ')'  */
  YYSYMBOL_27_ = 27,                       /* ','  */
  YYSYMBOL_28_ = 28,                       /* '}'  */
  YYSYMBOL_29_ = 29,                       /* '='  */
  YYSYMBOL_30_ = 30,                       /* '-'  */
  YYSYMBOL_31_ = 31,                       /* '*'  */
  YYSYMBOL_32_ = 32,                       /* '/'  */
  YYSYMBOL_33_ = 33,                       /* '%'  */
  YYSYMBOL_34_ = 34,                       /* '+'  */
  YYSYMBOL_35_ = 35,                       /* '<'  */
  YYSYMBOL_36_ = 36,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_global_declaration = 39,        /* global_declaration  */
  YYSYMBOL_variable_declaration = 40,      /* variable_declaration  */
  YYSYMBOL_type = 41,                      /* type  */
  YYSYMBOL_function = 42,                  /* function  */
  YYSYMBOL_function_body = 43,             /* function_body  */
  YYSYMBOL_function_header = 44,           /* function_header  */
  YYSYMBOL_parameter_list = 45,            /* parameter_list  */
  YYSYMBOL_parameters = 46,                /* parameters  */
  YYSYMBOL_parameter = 47,                 /* parameter  */
  YYSYMBOL_commands = 48,                  /* commands  */
  YYSYMBOL_command = 49,                   /* command  */
  YYSYMBOL_open_block = 50,                /* open_block  */
  YYSYMBOL_close_block = 51,               /* close_block  */
  YYSYMBOL_command_block = 52,             /* command_block  */
  YYSYMBOL_attribution_command = 53,       /* attribution_command  */
  YYSYMBOL_return_command = 54,            /* return_command  */
  YYSYMBOL_arguments = 55,                 /* arguments  */
  YYSYMBOL_function_call = 56,             /* function_call  */
  YYSYMBOL_while_command = 57,             /* while_command  */
  YYSYMBOL_if_command = 58,                /* if_command  */
  YYSYMBOL_else_part = 59,                 /* else_part  */
  YYSYMBOL_identifier_list = 60,           /* identifier_list  */
  YYSYMBOL_identifier = 61,                /* identifier  */
  YYSYMBOL_literal = 62,                   /* literal  */
  YYSYMBOL_primary = 63,                   /* primary  */
  YYSYMBOL_unary = 64,                     /* unary  */
  YYSYMBOL_factor = 65,                    /* factor  */
  YYSYMBOL_term = 66,                      /* term  */
  YYSYMBOL_order = 67,                     /* order  */
  YYSYMBOL_identity = 68,                  /* identity  */
  YYSYMBOL_and_expr = 69,                  /* and_expr  */
  YYSYMBOL_expression = 70                 /* expression  */
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
typedef yytype_int8 yy_state_t;

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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   113

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,    24,     2,     2,     2,    33,     2,     2,
      25,    26,    31,    34,    27,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
      35,    29,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,    28,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    97,    97,   101,   102,   116,   121,   135,   139,   143,
     149,   159,   162,   184,   187,   188,   189,   192,   199,   200,
     207,   210,   211,   212,   213,   214,   215,   218,   221,   223,
     228,   252,   259,   260,   265,   270,   284,   291,   301,   302,
     309,   310,   312,   314,   315,   316,   317,   319,   333,   343,
     344,   349,   350,   351,   361,   362,   371,   380,   383,   384,
     393,   404,   405,   414,   423,   432,   443,   444,   453,   464,
     465,   476,   477
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
  "\"end of file\"", "error", "\"invalid token\"", "TK_PR_INT",
  "TK_PR_FLOAT", "TK_PR_BOOL", "TK_PR_IF", "TK_PR_ELSE", "TK_PR_WHILE",
  "TK_PR_RETURN", "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE",
  "TK_OC_AND", "TK_OC_OR", "TK_IDENTIFICADOR", "TK_LIT_INT",
  "TK_LIT_FLOAT", "TK_LIT_FALSE", "TK_LIT_TRUE", "TK_ERRO", "';'", "'{'",
  "'!'", "'('", "')'", "','", "'}'", "'='", "'-'", "'*'", "'/'", "'%'",
  "'+'", "'<'", "'>'", "$accept", "program", "global_declaration",
  "variable_declaration", "type", "function", "function_body",
  "function_header", "parameter_list", "parameters", "parameter",
  "commands", "command", "open_block", "close_block", "command_block",
  "attribution_command", "return_command", "arguments", "function_call",
  "while_command", "if_command", "else_part", "identifier_list",
  "identifier", "literal", "primary", "unary", "factor", "term", "order",
  "identity", "and_expr", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-85)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -85,    21,   -85,   -85,   -85,   -85,    78,   -85,    -8,     6,
     -85,    13,    16,     6,   -22,   -85,   -85,   -85,    15,   -85,
     -85,   -85,    78,   -85,   -85,    78,     6,     7,    20,   -85,
     -85,    24,    33,    35,   -85,   -85,    44,   -85,   -85,   -85,
      47,    68,    77,    80,    81,    82,    32,     6,    35,    35,
     -85,   -85,   -85,   -85,    55,    35,    55,   -85,    38,   -85,
     -85,   -85,    53,    34,    -2,    79,    86,    90,   -85,     7,
     -85,   -85,   -85,   -85,   -85,   -85,    35,    35,   -85,    17,
      22,   -85,    41,   -85,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    35,    35,   -85,    67,    90,
      90,    83,    83,   -85,   -85,   -85,   -85,    53,    53,    34,
      34,    34,    34,    -2,    -2,    79,    86,   -85,    35,    94,
     -85,    90,    83,   -85,   -85
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     7,     8,     9,    14,     3,     0,     0,
       4,     0,     0,     0,     0,    16,     5,    42,     6,    40,
      18,    10,     0,    17,    13,     0,     0,     0,     0,    15,
      41,     0,     0,     0,    27,    28,     0,    19,    18,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    46,    43,    44,     0,     0,     0,    49,    47,    48,
      51,    54,    58,    61,    66,    69,    71,    31,    21,     0,
      20,    22,    24,    23,    26,    25,    32,     0,    12,     0,
       0,    52,     0,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,    33,
      30,     0,     0,    50,    55,    56,    57,    60,    59,    65,
      64,    62,    63,    67,    68,    70,    72,    35,     0,    38,
      36,    34,     0,    37,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -85,   -85,   -85,   106,    25,   -85,   -85,   -85,   -85,   -85,
      84,    70,   -85,   -85,    42,   -84,   -85,   -85,   -85,   -24,
     -85,   -85,   -85,   -85,    -7,   -85,   -15,     3,     8,   -13,
       4,    18,    14,   -48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     7,    36,     9,    10,    21,    11,    12,    14,
      15,    27,    37,    38,    39,    40,    41,    42,    98,    57,
      44,    45,   123,    18,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      79,    80,    19,    43,    24,    25,    23,    82,    89,    90,
       3,     4,     5,    31,    16,    32,    33,   119,   120,    30,
      46,     2,    17,    17,     3,     4,     5,    22,    99,   100,
      34,    13,    96,    91,    92,    35,    20,    96,   124,    81,
      78,    83,    26,   101,    47,    43,     6,    28,   102,    48,
      13,    17,    50,    51,    52,    53,    96,    76,    49,    54,
      55,    77,    46,    76,    87,    56,    68,   103,    88,    70,
     121,    17,    50,    51,    52,    53,   109,   110,   111,   112,
      55,     3,     4,     5,    84,    85,    86,   104,   105,   106,
      71,    93,    94,   117,   118,   107,   108,   113,   114,    72,
      95,   122,    73,    74,    75,    96,    34,     8,    69,    29,
     116,    97,     0,   115
};

static const yytype_int8 yycheck[] =
{
      48,    49,     9,    27,    26,    27,    13,    55,    10,    11,
       3,     4,     5,     6,    22,     8,     9,   101,   102,    26,
      27,     0,    16,    16,     3,     4,     5,    11,    76,    77,
      23,     6,    15,    35,    36,    28,    23,    15,   122,    54,
      47,    56,    27,    26,    24,    69,    25,    22,    26,    25,
      25,    16,    17,    18,    19,    20,    15,    25,    25,    24,
      25,    29,    69,    25,    30,    30,    22,    26,    34,    22,
     118,    16,    17,    18,    19,    20,    89,    90,    91,    92,
      25,     3,     4,     5,    31,    32,    33,    84,    85,    86,
      22,    12,    13,    26,    27,    87,    88,    93,    94,    22,
      14,     7,    22,    22,    22,    15,    23,     1,    38,    25,
      96,    69,    -1,    95
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    38,     0,     3,     4,     5,    25,    39,    40,    41,
      42,    44,    45,    41,    46,    47,    22,    16,    60,    61,
      23,    43,    11,    61,    26,    27,    27,    48,    41,    47,
      61,     6,     8,     9,    23,    28,    40,    49,    50,    51,
      52,    53,    54,    56,    57,    58,    61,    24,    25,    25,
      17,    18,    19,    20,    24,    25,    30,    56,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    22,    48,
      22,    22,    22,    22,    22,    22,    25,    29,    61,    70,
      70,    63,    70,    63,    31,    32,    33,    30,    34,    10,
      11,    35,    36,    12,    13,    14,    15,    51,    55,    70,
      70,    26,    26,    26,    64,    64,    64,    65,    65,    66,
      66,    66,    66,    67,    67,    68,    69,    26,    27,    52,
      52,    70,     7,    59,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    39,    40,    41,    41,    41,
      42,    43,    44,    45,    46,    46,    46,    47,    48,    48,
      49,    49,    49,    49,    49,    49,    49,    50,    51,    52,
      53,    54,    55,    55,    55,    56,    57,    58,    59,    59,
      60,    60,    61,    62,    62,    62,    62,    63,    63,    63,
      63,    64,    64,    64,    65,    65,    65,    65,    66,    66,
      66,    67,    67,    67,    67,    67,    68,    68,    68,    69,
      69,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     1,     1,     1,
       2,     3,     5,     3,     0,     3,     1,     2,     0,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     3,
       3,     2,     0,     1,     3,     4,     5,     6,     0,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     2,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 2: /* program: %empty  */
#line 97 "parser.y"
                     { 
    (yyval.node) = ast_node_create(AST_NODE_TYPE_PROGRAM_START, NULL, TYPE_SYSTEM_TYPE_FAKE);
    arvore = (yyval.node);
}
#line 1233 "parser.tab.c"
    break;

  case 3: /* program: program global_declaration  */
#line 101 "parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1239 "parser.tab.c"
    break;

  case 4: /* program: program function  */
#line 102 "parser.y"
                       {
        if(current_function != NULL){
            ast_node_add_child(current_function, (yyvsp[0].node));
        }else{
            ast_node_add_child((yyvsp[-1].node), (yyvsp[0].node));

        }
        current_function = (yyvsp[0].node); (yyval.node) = (yyvsp[-1].node);
        iloc_instr_list_concat(ast_node_get_code((yyvsp[-1].node)), ast_node_get_code((yyvsp[0].node)));
    }
#line 1254 "parser.tab.c"
    break;

  case 5: /* global_declaration: variable_declaration ';'  */
#line 116 "parser.y"
                                             {
    rbss += 4;
}
#line 1262 "parser.tab.c"
    break;

  case 6: /* variable_declaration: type identifier_list  */
#line 121 "parser.y"
                                           {
    (yyval.node) = ast_node_create(AST_NODE_TYPE_EMPTY, NULL, (yyvsp[-1].data_type)); 
    // Add list of identifiers to the symbol table
    int size = ast_node_list_size((yyvsp[0].list)); 
    for(int i = 0; i < size; i++){
        ast_node *cur_node = ast_node_list_pop_front((yyvsp[0].list)); 
        fail_if_declared(scope_stack, cur_node); 
        ast_node_set_data_type(cur_node, (yyvsp[-1].data_type));
        symbol *sym = symbol_create((yyvsp[-1].data_type), SYMBOL_TYPE_IDENTIFIER, ast_node_get_lexeme(cur_node), rfp);
        rfp += 4;
        add_symbol_to_current_scope(scope_stack, sym);
    }
}
#line 1280 "parser.tab.c"
    break;

  case 7: /* type: TK_PR_INT  */
#line 135 "parser.y"
                {
    stack_create_if_null(&scope_stack);
    (yyval.data_type) = TYPE_SYSTEM_TYPE_INT;
    }
#line 1289 "parser.tab.c"
    break;

  case 8: /* type: TK_PR_FLOAT  */
#line 139 "parser.y"
                 {
    stack_create_if_null(&scope_stack);
    (yyval.data_type) = TYPE_SYSTEM_TYPE_FLOAT;
    }
#line 1298 "parser.tab.c"
    break;

  case 9: /* type: TK_PR_BOOL  */
#line 143 "parser.y"
                {
    stack_create_if_null(&scope_stack);
    (yyval.data_type) = TYPE_SYSTEM_TYPE_BOOL;
    }
#line 1307 "parser.tab.c"
    break;

  case 10: /* function: function_header function_body  */
#line 149 "parser.y"
                                        {
        ast_node *node = (yyvsp[-1].node);
        for(int i = 0; i < ast_node_list_size((yyvsp[0].list)); i++){
            iloc_instr_list_concat(ast_node_get_code(node), ast_node_get_code(ast_node_list_get((yyvsp[0].list), i)));
        }
        add_child_from_list(node, (yyvsp[0].list));
        (yyval.node) = node; 
}
#line 1320 "parser.tab.c"
    break;

  case 11: /* function_body: '{' commands close_block  */
#line 159 "parser.y"
                                        { (yyval.list) = (yyvsp[-1].list); rfp = rbss; }
#line 1326 "parser.tab.c"
    break;

  case 12: /* function_header: parameter_list TK_OC_GE type '!' identifier  */
#line 162 "parser.y"
                                                             {
    // Add function name
    fail_if_declared(scope_stack, (yyvsp[0].node)); 
    symbol *sym = symbol_create((yyvsp[-2].data_type), SYMBOL_TYPE_FUNCTION, ast_node_get_lexeme((yyvsp[0].node)), 0); // Does not matter where the function is stored
    add_symbol_to_current_scope(scope_stack, sym); 
    (yyval.node)=(yyvsp[0].node); ast_node_set_node_type((yyval.node), AST_NODE_TYPE_FUNCTION); 

    // Scope args
    add_new_scope(scope_stack); 
    // Add list of identifiers to the symbol table
    int size = ast_node_list_size((yyvsp[-4].list)); 
    for(int i = 0; i < size; i++){ 
        ast_node *cur_node = ast_node_list_pop_front((yyvsp[-4].list));  
        fail_if_declared(scope_stack, cur_node); 
        symbol *sym = symbol_create(ast_node_get_data_type(cur_node), SYMBOL_TYPE_IDENTIFIER, ast_node_get_lexeme(cur_node), rfp);
        rfp += 4; 
        add_symbol_to_current_scope(scope_stack, sym); 
    }
    rfp = 0; // Reset rfp as a new scope was created 
}
#line 1351 "parser.tab.c"
    break;

  case 13: /* parameter_list: '(' parameters ')'  */
#line 184 "parser.y"
                                { stack_create_if_null(&scope_stack); (yyval.list) = (yyvsp[-1].list);}
#line 1357 "parser.tab.c"
    break;

  case 14: /* parameters: %empty  */
#line 187 "parser.y"
                       { (yyval.list) = ast_node_list_create();}
#line 1363 "parser.tab.c"
    break;

  case 15: /* parameters: parameters ',' parameter  */
#line 188 "parser.y"
                               {ast_node_list_push_back((yyvsp[-2].list), (yyvsp[0].node)); (yyval.list) = (yyvsp[-2].list);}
#line 1369 "parser.tab.c"
    break;

  case 16: /* parameters: parameter  */
#line 189 "parser.y"
                {ast_node_list *list = ast_node_list_create(); ast_node_list_push_back(list, (yyvsp[0].node)); (yyval.list) = list;}
#line 1375 "parser.tab.c"
    break;

  case 17: /* parameter: type identifier  */
#line 192 "parser.y"
                           {
    fail_if_declared(scope_stack, (yyvsp[0].node));
    lexeme *lex = ast_node_get_lexeme((yyvsp[0].node));
    (yyval.node) = ast_node_create(AST_NODE_TYPE_IDENTIFIER, lex, (yyvsp[-1].data_type));
    }
#line 1385 "parser.tab.c"
    break;

  case 18: /* commands: %empty  */
#line 199 "parser.y"
                      { (yyval.list) = ast_node_list_create();}
#line 1391 "parser.tab.c"
    break;

  case 19: /* commands: commands command  */
#line 200 "parser.y"
                       {
        if((yyvsp[0].node) != NULL){
            ast_node_list_push_back((yyvsp[-1].list), (yyvsp[0].node)); (yyval.list) = (yyvsp[-1].list);
        }
    }
#line 1401 "parser.tab.c"
    break;

  case 20: /* command: command_block ';'  */
#line 207 "parser.y"
                           {
    (yyval.node) = unwind_ast_node_list((yyvsp[-1].list));
}
#line 1409 "parser.tab.c"
    break;

  case 21: /* command: variable_declaration ';'  */
#line 210 "parser.y"
                               { (yyval.node) = (yyvsp[-1].node);}
#line 1415 "parser.tab.c"
    break;

  case 22: /* command: attribution_command ';'  */
#line 211 "parser.y"
                              { (yyval.node) = (yyvsp[-1].node);}
#line 1421 "parser.tab.c"
    break;

  case 23: /* command: function_call ';'  */
#line 212 "parser.y"
                        { (yyval.node) = (yyvsp[-1].node);}
#line 1427 "parser.tab.c"
    break;

  case 24: /* command: return_command ';'  */
#line 213 "parser.y"
                         { (yyval.node) = (yyvsp[-1].node);}
#line 1433 "parser.tab.c"
    break;

  case 25: /* command: if_command ';'  */
#line 214 "parser.y"
                     { (yyval.node) = (yyvsp[-1].node);}
#line 1439 "parser.tab.c"
    break;

  case 26: /* command: while_command ';'  */
#line 215 "parser.y"
                        { (yyval.node) = (yyvsp[-1].node);}
#line 1445 "parser.tab.c"
    break;

  case 27: /* open_block: '{'  */
#line 218 "parser.y"
                {add_new_scope(scope_stack);}
#line 1451 "parser.tab.c"
    break;

  case 28: /* close_block: '}'  */
#line 221 "parser.y"
                 {remove_current_scope(scope_stack);}
#line 1457 "parser.tab.c"
    break;

  case 29: /* command_block: open_block commands close_block  */
#line 223 "parser.y"
                                               {
    (yyval.list) = (yyvsp[-1].list);
    }
#line 1465 "parser.tab.c"
    break;

  case 30: /* attribution_command: identifier '=' expression  */
#line 228 "parser.y"
                                               {
        fail_if_not_declared(scope_stack, (yyvsp[-2].node));
        fail_if_not_variable(scope_stack, (yyvsp[-2].node));
        symbol *sym = get_symbol_globally(scope_stack, ast_node_get_lexeme_value((yyvsp[-2].node)));
        
        if(sym == NULL){printf("Unexpected error: symbol not found\n"); exit(1);}
        
        ast_node *node = ast_node_create(AST_NODE_TYPE_ATTRIBUTION, NULL, symbol_get_data_type(sym));
        ast_node_add_child(node, (yyvsp[-2].node));
        ast_node_add_child(node, (yyvsp[0].node));
        (yyval.node) = node;
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* make_temp_zero = iloc_sub(temporary, temporary, temporary, NULL);
        ast_node_add_code((yyval.node), make_temp_zero);
        iloc_instr* add_expr_into_temp = iloc_addI(temporary, ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), add_expr_into_temp);
        iloc_instr* store_temp_into_memory = iloc_storeAI(temporary, "rfp", symbol_get_location(sym), NULL);
        ast_node_add_code((yyval.node), store_temp_into_memory);

    }
#line 1492 "parser.tab.c"
    break;

  case 31: /* return_command: TK_PR_RETURN expression  */
#line 252 "parser.y"
                                       {
        ast_node *node = ast_node_create(AST_NODE_TYPE_RETURN, NULL, ast_node_get_data_type((yyvsp[0].node)));
        ast_node_add_child(node, (yyvsp[0].node));
        (yyval.node) = node;
    }
#line 1502 "parser.tab.c"
    break;

  case 32: /* arguments: %empty  */
#line 259 "parser.y"
                       { (yyval.list) = ast_node_list_create();}
#line 1508 "parser.tab.c"
    break;

  case 33: /* arguments: expression  */
#line 260 "parser.y"
                 {
        ast_node_list *list = ast_node_list_create();
        ast_node_list_push_back(list, (yyvsp[0].node));
        (yyval.list) = list;
    }
#line 1518 "parser.tab.c"
    break;

  case 34: /* arguments: arguments ',' expression  */
#line 265 "parser.y"
                               {
        ast_node_list_push_back((yyvsp[-2].list), (yyvsp[0].node));
        (yyval.list) = (yyvsp[-2].list);
    }
#line 1527 "parser.tab.c"
    break;

  case 35: /* function_call: identifier '(' arguments ')'  */
#line 270 "parser.y"
                                           {
    fail_if_not_declared(scope_stack, (yyvsp[-3].node));
    fail_if_not_function(scope_stack, (yyvsp[-3].node));
    ast_node *node = (yyvsp[-3].node);
    symbol *sym = get_symbol_globally(scope_stack, ast_node_get_lexeme_value((yyvsp[-3].node)));

    if(sym == NULL){printf("Unexpected error: symbol not found\n"); exit(1);}

    ast_node_set_node_type(node, AST_NODE_TYPE_FUNCTION_CALL);
    ast_node_set_data_type(node, symbol_get_data_type(sym));
    add_child_from_list(node, (yyvsp[-1].list));
    (yyval.node) = node;
}
#line 1545 "parser.tab.c"
    break;

  case 36: /* while_command: TK_PR_WHILE '(' expression ')' command_block  */
#line 284 "parser.y"
                                                           {
    ast_node *node = ast_node_create(AST_NODE_TYPE_WHILE, NULL, ast_node_get_data_type((yyvsp[-2].node)));
    ast_node_add_child(node, (yyvsp[-2].node));
    add_child_from_list(node, (yyvsp[0].list));
    (yyval.node) = node;
}
#line 1556 "parser.tab.c"
    break;

  case 37: /* if_command: TK_PR_IF '(' expression ')' command_block else_part  */
#line 291 "parser.y"
                                                               {
    ast_node *node = ast_node_create(AST_NODE_TYPE_IF, NULL, ast_node_get_data_type((yyvsp[-3].node)));
    ast_node_add_child(node, (yyvsp[-3].node));
    add_child_from_list(node, (yyvsp[-1].list));
    if((yyvsp[0].node) != NULL)
        ast_node_set_data_type((yyvsp[0].node), ast_node_get_data_type((yyvsp[-3].node)));
        ast_node_add_child(node, (yyvsp[0].node));
    (yyval.node) = node;
}
#line 1570 "parser.tab.c"
    break;

  case 38: /* else_part: %empty  */
#line 301 "parser.y"
                       { (yyval.node) = NULL;}
#line 1576 "parser.tab.c"
    break;

  case 39: /* else_part: TK_PR_ELSE command_block  */
#line 302 "parser.y"
                               {
    ast_node *node = ast_node_create(AST_NODE_TYPE_ELSE, NULL, TYPE_SYSTEM_TYPE_FAKE);
    add_child_from_list(node, (yyvsp[0].list));
    (yyval.node) = node;
}
#line 1586 "parser.tab.c"
    break;

  case 40: /* identifier_list: identifier  */
#line 309 "parser.y"
                            {(yyval.list) = ast_node_list_create(); ast_node_list_push_back((yyval.list), (yyvsp[0].node));}
#line 1592 "parser.tab.c"
    break;

  case 41: /* identifier_list: identifier_list ',' identifier  */
#line 310 "parser.y"
                                     {ast_node_list_push_back((yyvsp[-2].list), (yyvsp[0].node)); (yyval.list) = (yyvsp[-2].list);}
#line 1598 "parser.tab.c"
    break;

  case 42: /* identifier: TK_IDENTIFICADOR  */
#line 312 "parser.y"
                             { ast_node *node = ast_node_create(AST_NODE_TYPE_IDENTIFIER, (yyvsp[0].lex), TYPE_SYSTEM_TYPE_FAKE); (yyval.node) = node;}
#line 1604 "parser.tab.c"
    break;

  case 43: /* literal: TK_LIT_FALSE  */
#line 314 "parser.y"
                      { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, (yyvsp[0].lex), TYPE_SYSTEM_TYPE_BOOL); (yyval.node) = node;}
#line 1610 "parser.tab.c"
    break;

  case 44: /* literal: TK_LIT_TRUE  */
#line 315 "parser.y"
                  { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, (yyvsp[0].lex), TYPE_SYSTEM_TYPE_BOOL); (yyval.node) = node;}
#line 1616 "parser.tab.c"
    break;

  case 45: /* literal: TK_LIT_INT  */
#line 316 "parser.y"
                 { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, (yyvsp[0].lex), TYPE_SYSTEM_TYPE_INT); (yyval.node) = node;}
#line 1622 "parser.tab.c"
    break;

  case 46: /* literal: TK_LIT_FLOAT  */
#line 317 "parser.y"
                   { ast_node *node = ast_node_create(AST_NODE_TYPE_LITERAL, (yyvsp[0].lex), TYPE_SYSTEM_TYPE_FLOAT); (yyval.node) = node;}
#line 1628 "parser.tab.c"
    break;

  case 47: /* primary: identifier  */
#line 319 "parser.y"
                    {
    // Check if identifier is declared
    fail_if_not_declared(scope_stack, (yyvsp[0].node));
    // Check if identifier is not a function
    fail_if_not_variable(scope_stack, (yyvsp[0].node));
    (yyval.node) = (yyvsp[0].node);
    symbol *sym = get_symbol_globally(scope_stack, ast_node_get_lexeme_value((yyvsp[0].node)));
    if(sym == NULL){printf("Unexpected error: symbol not found\n"); exit(1);} // Fail if symbol is not found
    ast_node_set_data_type((yyval.node), symbol_get_data_type(sym));
    char *temporary = iloc_make_temp();
    ast_node_set_temporary((yyval.node), temporary);
    iloc_instr* load_into_temp = iloc_loadAI("rfp", symbol_get_location(sym), temporary, NULL);
    ast_node_add_code((yyval.node), load_into_temp);
    }
#line 1647 "parser.tab.c"
    break;

  case 48: /* primary: literal  */
#line 333 "parser.y"
              {
        (yyval.node) = (yyvsp[0].node);
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* zero_the_register = iloc_sub(temporary, temporary, temporary, NULL);
        ast_node_add_code((yyval.node), zero_the_register);

        iloc_instr* load_into_temp = iloc_addI(temporary, ast_node_get_lexeme_value((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), load_into_temp);
    }
#line 1662 "parser.tab.c"
    break;

  case 49: /* primary: function_call  */
#line 343 "parser.y"
                    { (yyval.node) = (yyvsp[0].node);}
#line 1668 "parser.tab.c"
    break;

  case 50: /* primary: '(' expression ')'  */
#line 344 "parser.y"
                         {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1676 "parser.tab.c"
    break;

  case 51: /* unary: primary  */
#line 349 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1682 "parser.tab.c"
    break;

  case 52: /* unary: '!' primary  */
#line 350 "parser.y"
                  { (yyval.node) =  make_unary_expression(AST_NODE_TYPE_LOGICAL_NEGATION, (yyvsp[0].node), scope_stack);}
#line 1688 "parser.tab.c"
    break;

  case 53: /* unary: '-' primary  */
#line 351 "parser.y"
                  {
        (yyval.node) = make_unary_expression(AST_NODE_TYPE_NUMERICAL_NEGATION, (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* neg = iloc_subI(temporary, "0", ast_node_get_temporary((yyvsp[0].node)), NULL);
        ast_node_add_code((yyval.node), neg);
        }
#line 1701 "parser.tab.c"
    break;

  case 54: /* factor: unary  */
#line 361 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1707 "parser.tab.c"
    break;

  case 55: /* factor: factor '*' unary  */
#line 362 "parser.y"
                       {
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_MULTIPLICATION, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* mult = iloc_mult(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), mult);
        }
#line 1721 "parser.tab.c"
    break;

  case 56: /* factor: factor '/' unary  */
#line 371 "parser.y"
                       {
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_DIVISION, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* div = iloc_div(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), div);
        }
#line 1735 "parser.tab.c"
    break;

  case 57: /* factor: factor '%' unary  */
#line 380 "parser.y"
                       { (yyval.node) = make_binary_expression(AST_NODE_TYPE_MODULO, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);}
#line 1741 "parser.tab.c"
    break;

  case 58: /* term: factor  */
#line 383 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1747 "parser.tab.c"
    break;

  case 59: /* term: term '+' factor  */
#line 384 "parser.y"
                      {
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_ADDITION, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* add = iloc_add(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), add);
    }
#line 1761 "parser.tab.c"
    break;

  case 60: /* term: term '-' factor  */
#line 393 "parser.y"
                      {
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_SUBTRACTION, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* sub = iloc_sub(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), sub);
    }
#line 1775 "parser.tab.c"
    break;

  case 61: /* order: term  */
#line 404 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1781 "parser.tab.c"
    break;

  case 62: /* order: order '<' term  */
#line 405 "parser.y"
                     {
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_LESS_THAN, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* less_than = iloc_cmp_LT(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), less_than);
        }
#line 1795 "parser.tab.c"
    break;

  case 63: /* order: order '>' term  */
#line 414 "parser.y"
                     {
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_GREATER_THAN, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* greater_than = iloc_cmp_GT(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), greater_than);
    }
#line 1809 "parser.tab.c"
    break;

  case 64: /* order: order TK_OC_GE term  */
#line 423 "parser.y"
                         { 
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_GREATER_EQUAL, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* greater_equal = iloc_cmp_GE(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), greater_equal);
    }
#line 1823 "parser.tab.c"
    break;

  case 65: /* order: order TK_OC_LE term  */
#line 432 "parser.y"
                         { 
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_LESS_EQUAL, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* less_equal = iloc_cmp_LE(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), less_equal);
    }
#line 1837 "parser.tab.c"
    break;

  case 66: /* identity: order  */
#line 443 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1843 "parser.tab.c"
    break;

  case 67: /* identity: identity TK_OC_EQ order  */
#line 444 "parser.y"
                             { 
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_EQUAL, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* equal = iloc_cmp_EQ(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), equal);
    }
#line 1857 "parser.tab.c"
    break;

  case 68: /* identity: identity TK_OC_NE order  */
#line 453 "parser.y"
                             { 
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_NOT_EQUAL, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* not_equal = iloc_cmp_NE(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), not_equal);
        }
#line 1871 "parser.tab.c"
    break;

  case 69: /* and_expr: identity  */
#line 464 "parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1877 "parser.tab.c"
    break;

  case 70: /* and_expr: and_expr TK_OC_AND identity  */
#line 465 "parser.y"
                                 {
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_LOGICAL_AND, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* and = iloc_and(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), and);
        }
#line 1891 "parser.tab.c"
    break;

  case 71: /* expression: and_expr  */
#line 476 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1897 "parser.tab.c"
    break;

  case 72: /* expression: expression TK_OC_OR and_expr  */
#line 477 "parser.y"
                                  {
        (yyval.node) = make_binary_expression(AST_NODE_TYPE_LOGICAL_OR, (yyvsp[-2].node), (yyvsp[0].node), scope_stack);
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[-2].node)));
        iloc_instr_list_concat(ast_node_get_code((yyval.node)), ast_node_get_code((yyvsp[0].node)));
        char *temporary = iloc_make_temp();
        ast_node_set_temporary((yyval.node), temporary);
        iloc_instr* or = iloc_or(ast_node_get_temporary((yyvsp[-2].node)), ast_node_get_temporary((yyvsp[0].node)), temporary, NULL);
        ast_node_add_code((yyval.node), or);
        }
#line 1911 "parser.tab.c"
    break;


#line 1915 "parser.tab.c"

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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 488 "parser.y"

void yyerror (char const *s) {
    fprintf (stderr, "In line %d... %s.\n", get_line_number(), s);
} 
