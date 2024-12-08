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
#line 1 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"

    #include <iostream>
    #include <vector>
    #include <memory>

    #include "ast.h"
    #include "lexer.hpp"

    extern int yylex();
    // extern int yyset_in(FILE* in);
    extern FILE *yyin;
    // extern int yylineno;
    extern char* yytext;

    int yyerror(std::string);

    std::shared_ptr<Program> parsed_program = std::make_shared<Program>();


#line 91 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_END = 4,                        /* END  */
  YYSYMBOL_PROCEDURE = 5,                  /* PROCEDURE  */
  YYSYMBOL_IS = 6,                         /* IS  */
  YYSYMBOL_IN = 7,                         /* IN  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_THEN = 9,                       /* THEN  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_ENDIF = 11,                     /* ENDIF  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_DO = 13,                        /* DO  */
  YYSYMBOL_ENDWHILE = 14,                  /* ENDWHILE  */
  YYSYMBOL_REPEAT = 15,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 16,                     /* UNTIL  */
  YYSYMBOL_READ = 17,                      /* READ  */
  YYSYMBOL_WRITE = 18,                     /* WRITE  */
  YYSYMBOL_ASSIGNMENT = 19,                /* ASSIGNMENT  */
  YYSYMBOL_T = 20,                         /* T  */
  YYSYMBOL_NUMBER = 21,                    /* NUMBER  */
  YYSYMBOL_PIDENTIFIER = 22,               /* PIDENTIFIER  */
  YYSYMBOL_23_ = 23,                       /* '+'  */
  YYSYMBOL_24_ = 24,                       /* '-'  */
  YYSYMBOL_25_ = 25,                       /* '*'  */
  YYSYMBOL_26_ = 26,                       /* '/'  */
  YYSYMBOL_27_ = 27,                       /* '%'  */
  YYSYMBOL_ERROR = 28,                     /* ERROR  */
  YYSYMBOL_29_ = 29,                       /* '('  */
  YYSYMBOL_30_ = 30,                       /* ')'  */
  YYSYMBOL_31_ = 31,                       /* ';'  */
  YYSYMBOL_32_ = 32,                       /* ','  */
  YYSYMBOL_33_ = 33,                       /* '['  */
  YYSYMBOL_34_ = 34,                       /* ']'  */
  YYSYMBOL_35_ = 35,                       /* '='  */
  YYSYMBOL_36_ = 36,                       /* '!'  */
  YYSYMBOL_37_ = 37,                       /* '>'  */
  YYSYMBOL_38_ = 38,                       /* '<'  */
  YYSYMBOL_39_ = 39,                       /* '}'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program_all = 42,               /* program_all  */
  YYSYMBOL_procedures = 43,                /* procedures  */
  YYSYMBOL_main = 44,                      /* main  */
  YYSYMBOL_proc_head = 45,                 /* proc_head  */
  YYSYMBOL_commands = 46,                  /* commands  */
  YYSYMBOL_command = 47,                   /* command  */
  YYSYMBOL_proc_call = 48,                 /* proc_call  */
  YYSYMBOL_declarations = 49,              /* declarations  */
  YYSYMBOL_args_decl = 50,                 /* args_decl  */
  YYSYMBOL_args = 51,                      /* args  */
  YYSYMBOL_expression = 52,                /* expression  */
  YYSYMBOL_condition = 53,                 /* condition  */
  YYSYMBOL_value = 54,                     /* value  */
  YYSYMBOL_identifier = 55                 /* identifier  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   192

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


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
       2,     2,     2,    36,     2,     2,     2,    27,     2,     2,
      29,    30,    25,    23,    32,    24,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
      38,    35,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    39,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    28
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    85,    85,    89,    95,   101,   105,   109,   113,   120,
     125,   131,   135,   139,   143,   147,   151,   155,   159,   163,
     170,   178,   186,   195,   205,   213,   221,   231,   241,   248,
     256,   260,   264,   268,   272,   276,   280,   284,   288,   291,
     295,   299,   303,   308,   313,   318,   326
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "END",
  "PROCEDURE", "IS", "IN", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "ENDWHILE", "REPEAT", "UNTIL", "READ", "WRITE", "ASSIGNMENT", "T",
  "NUMBER", "PIDENTIFIER", "'+'", "'-'", "'*'", "'/'", "'%'", "ERROR",
  "'('", "')'", "';'", "','", "'['", "']'", "'='", "'!'", "'>'", "'<'",
  "'}'", "'{'", "$accept", "program_all", "procedures", "main",
  "proc_head", "commands", "command", "proc_call", "declarations",
  "args_decl", "args", "expression", "condition", "value", "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-27)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -27,     8,     9,   -27,    19,    15,   -27,    -3,   -13,    42,
     159,    28,    -2,    21,    -1,    23,    23,   159,    32,    23,
     -26,     5,   -27,    48,    62,    61,   159,    63,    66,   -27,
      -6,   159,     4,   -27,    51,    80,   147,   -27,    77,   132,
      64,    67,    71,    43,   -27,   -27,   -27,    23,    65,    34,
      69,   -27,   -27,    33,    79,   159,   159,    23,    23,    23,
      23,    23,    23,   159,    23,   -27,   -27,   -27,    30,    75,
      82,    72,   165,   -27,   -27,    96,    78,   -27,   -27,   111,
     124,   -27,   -27,   -27,   -27,   -27,   -27,   143,    87,   -27,
      98,   -27,   -27,   -27,    23,    23,    23,    23,    23,    88,
     -27,   -27,   159,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   151,   -27
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,     0,     0,     2,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,     0,     0,     0,
      44,     0,    10,     0,     0,     0,     0,     0,     0,    26,
       0,     0,     0,    42,    44,     0,     0,    43,     0,     0,
       0,     0,     0,     0,     7,     9,    16,     0,     0,     0,
      20,    27,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    18,    29,     0,     0,
       0,     0,    30,    23,     6,     0,     0,    24,     4,     0,
       0,    36,    37,    38,    39,    40,    41,     0,     0,    19,
       0,    45,    46,    11,     0,     0,     0,     0,     0,     0,
      25,     3,     0,    13,    14,    15,    28,    31,    32,    33,
      34,    35,    21,     0,    12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -27,   -27,   -27,   -27,   -27,   -16,   -21,   -27,   107,   -27,
     -27,   -27,   -14,    10,    16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,     9,    21,    22,    23,    12,    30,
      68,    71,    35,    36,    24
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      45,    39,    38,    42,    10,    26,    31,    43,     3,    44,
      49,    55,     4,    15,     5,    54,    13,    16,    45,    11,
      17,    11,    18,    19,    52,     7,    53,    20,    45,    41,
      27,    37,    37,    45,    40,    37,    27,     8,    74,    79,
      80,    28,    15,    29,    33,    34,    16,    87,    14,    17,
      88,    18,    19,    76,    34,    77,    20,    72,    45,    45,
      89,    25,    90,    37,    69,    70,    45,    81,    82,    83,
      84,    85,    86,    37,    37,    37,    37,    37,    37,    46,
      37,    47,    48,    78,    43,    50,   113,    15,    51,    56,
      63,    16,    45,    67,    17,    65,    18,    19,    66,    73,
     100,    20,    75,    93,   107,   108,   109,   110,   111,    91,
      37,    37,    37,    37,    37,   101,    92,    99,   105,    15,
     106,    32,   112,    16,     0,     0,    17,     0,    18,    19,
       0,     0,    15,    20,   102,   103,    16,     0,     0,    17,
      15,    18,    19,     0,    16,     0,    20,    17,    64,    18,
      19,    15,     0,     0,    20,    16,     0,   104,    17,    15,
      18,    19,   114,    16,     0,    20,    17,    15,    18,    19,
       0,    16,     0,    20,    17,     0,    18,    19,     0,     0,
       0,    20,    57,    58,    59,    60,    61,    62,    94,    95,
      96,    97,    98
};

static const yytype_int8 yycheck[] =
{
      21,    17,    16,    29,     7,     7,     7,    33,     0,     4,
      26,     7,     3,     8,     5,    31,    29,    12,    39,    22,
      15,    22,    17,    18,    30,     6,    32,    22,    49,    19,
      32,    15,    16,    54,    18,    19,    32,    22,     4,    55,
      56,    20,     8,    22,    21,    22,    12,    63,     6,    15,
      64,    17,    18,    20,    22,    22,    22,    47,    79,    80,
      30,    33,    32,    47,    21,    22,    87,    57,    58,    59,
      60,    61,    62,    57,    58,    59,    60,    61,    62,    31,
      64,    19,    21,     4,    33,    22,   102,     8,    22,     9,
      13,    12,   113,    22,    15,    31,    17,    18,    31,    34,
      22,    22,    33,    31,    94,    95,    96,    97,    98,    34,
      94,    95,    96,    97,    98,     4,    34,    21,    31,     8,
      22,    14,    34,    12,    -1,    -1,    15,    -1,    17,    18,
      -1,    -1,     8,    22,    10,    11,    12,    -1,    -1,    15,
       8,    17,    18,    -1,    12,    -1,    22,    15,    16,    17,
      18,     8,    -1,    -1,    22,    12,    -1,    14,    15,     8,
      17,    18,    11,    12,    -1,    22,    15,     8,    17,    18,
      -1,    12,    -1,    22,    15,    -1,    17,    18,    -1,    -1,
      -1,    22,    35,    36,    37,    38,    39,    40,    23,    24,
      25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    42,    43,     0,     3,     5,    44,     6,    22,    45,
       7,    22,    49,    29,     6,     8,    12,    15,    17,    18,
      22,    46,    47,    48,    55,    33,     7,    32,    20,    22,
      50,     7,    49,    21,    22,    53,    54,    55,    53,    46,
      55,    54,    29,    33,     4,    47,    31,    19,    21,    46,
      22,    22,    30,    32,    46,     7,     9,    35,    36,    37,
      38,    39,    40,    13,    16,    31,    31,    22,    51,    21,
      22,    52,    54,    34,     4,    33,    20,    22,     4,    46,
      46,    54,    54,    54,    54,    54,    54,    46,    53,    30,
      32,    34,    34,    31,    23,    24,    25,    26,    27,    21,
      22,     4,    10,    11,    14,    31,    22,    54,    54,    54,
      54,    54,    34,    46,    11
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    43,    44,    44,    45,    46,
      46,    47,    47,    47,    47,    47,    47,    47,    47,    48,
      49,    49,    49,    49,    50,    50,    50,    50,    51,    51,
      52,    52,    52,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    54,    54,    55,    55,    55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     8,     7,     0,     6,     5,     4,     2,
       1,     4,     7,     5,     5,     5,     2,     3,     3,     4,
       3,     6,     1,     4,     3,     4,     1,     2,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     4,     4
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
  case 2: /* program_all: procedures main  */
#line 85 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                            { 
                                                                                                ;
                                                                                            }
#line 1214 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 3: /* procedures: procedures PROCEDURE proc_head IS declarations IN commands END  */
#line 89 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            std::optional<Declarations> d(*(yyvsp[-3].decls));
                                                                                            Procedure p(*(yyvsp[-5].head), d, *(yyvsp[-1].cmds));
                                                                                            parsed_program->procedure_list.push_back(p);
                                                                                        }
#line 1224 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 4: /* procedures: procedures PROCEDURE proc_head IS IN commands END  */
#line 95 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            std::optional<Declarations> d = std::nullopt;
                                                                                            Procedure p(*(yyvsp[-4].head), d, *(yyvsp[-1].cmds));
                                                                                            parsed_program->procedure_list.push_back(p);   
                                                                                        }
#line 1234 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 5: /* procedures: %empty  */
#line 101 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        {   
                                                                                            ;   
                                                                                        }
#line 1242 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 6: /* main: PROGRAM IS declarations IN commands END  */
#line 105 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            parsed_program->declaration_list = *(yyvsp[-3].decls); parsed_program->commands_list = *(yyvsp[-1].cmds);   
                                                                                        }
#line 1250 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 7: /* main: PROGRAM IS IN commands END  */
#line 109 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            parsed_program->commands_list = *(yyvsp[-1].cmds); 
                                                                                        }
#line 1258 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 8: /* proc_head: PIDENTIFIER '(' args_decl ')'  */
#line 113 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         {   
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[-3].id)}); 
                                                                                            Pidentifier p(token_id);

                                                                                            (yyval.head) = new ProcedureHead(p, *(yyvsp[-1].proc_args));   
                                                                                         }
#line 1269 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 9: /* commands: commands command  */
#line 120 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        {   
                                                                                            std::shared_ptr<Command> ptr((yyvsp[0].cmd));
                                                                                            ((yyvsp[-1].cmds))->cmds.push_back(ptr);     
                                                                                         }
#line 1278 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 10: /* commands: command  */
#line 125 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            (yyval.cmds) = new Commands(); 
                                                                                            std::shared_ptr<Command> ptr((yyvsp[0].cmd));
                                                                                            (yyval.cmds)->cmds.push_back(ptr);  
                                                                                         }
#line 1288 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 11: /* command: identifier ASSIGNMENT expression ';'  */
#line 131 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.cmd) = new AssignmentStatement((yyvsp[-3].value), (yyvsp[-1].expression));   
                                                                                         }
#line 1296 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 12: /* command: IF condition THEN commands ELSE commands ENDIF  */
#line 135 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.cmd) = new IfElseStatement(*(yyvsp[-5].condition), *(yyvsp[-3].cmds), *(yyvsp[-1].cmds));   
                                                                                         }
#line 1304 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 13: /* command: IF condition THEN commands ENDIF  */
#line 139 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.cmd) = new IfStatement(*(yyvsp[-3].condition), *(yyvsp[-1].cmds));   
                                                                                         }
#line 1312 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 14: /* command: WHILE condition DO commands ENDWHILE  */
#line 143 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.cmd) = new WhileStatement(*(yyvsp[-3].condition), *(yyvsp[-1].cmds));   
                                                                                         }
#line 1320 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 15: /* command: REPEAT commands UNTIL condition ';'  */
#line 147 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                       { 
                                                                                             (yyval.cmd) = new RepeatStatement(*(yyvsp[-1].condition), *(yyvsp[-3].cmds));   
                                                                                         }
#line 1328 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 16: /* command: proc_call ';'  */
#line 151 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                             (yyval.cmd) = (yyvsp[-1].cmd);   
                                                                                         }
#line 1336 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 17: /* command: READ identifier ';'  */
#line 155 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.cmd) = new ReadStatement((yyvsp[-1].value));   
                                                                                        }
#line 1344 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 18: /* command: WRITE value ';'  */
#line 159 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.cmd) = new WriteStatement((yyvsp[-1].value));   
                                                                                         }
#line 1352 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 19: /* proc_call: PIDENTIFIER '(' args ')'  */
#line 163 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[-3].id)}); 
                                                                                            Pidentifier p(token_id);

                                                                                            (yyval.cmd) = new ProcedureCall(p, *(yyvsp[-1].call_args));
                                                                                         }
#line 1363 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 20: /* declarations: declarations ',' PIDENTIFIER  */
#line 170 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            Pidentifier p(token_id);
                                                                                            PidentifierDeclaration pd(p);

                                                                                            ((yyvsp[-2].decls))->decls.push_back(std::make_shared<PidentifierDeclaration>(pd));
                                                                                         }
#line 1375 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 21: /* declarations: declarations ',' PIDENTIFIER '[' NUMBER ']'  */
#line 178 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[-3].id)}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArrayDeclaration ad(p, (yyvsp[-1].num));

                                                                                            ((yyvsp[-5].decls))->decls.push_back(std::make_shared<ArrayDeclaration>(ad));
                                                                                         }
#line 1387 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 22: /* declarations: PIDENTIFIER  */
#line 186 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            Pidentifier p(token_id);
                                                                                            PidentifierDeclaration pd(p);

                                                                                            (yyval.decls) = new Declarations();
                                                                                            (yyval.decls)->decls.push_back(std::make_shared<PidentifierDeclaration>(pd));   
                                                                                         }
#line 1400 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 23: /* declarations: PIDENTIFIER '[' NUMBER ']'  */
#line 195 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 

                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[-3].id)}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArrayDeclaration ad(p, (yyvsp[-1].num));

                                                                                            (yyval.decls) = new Declarations();
                                                                                            (yyval.decls)->decls.push_back(std::make_shared<ArrayDeclaration>(ad));  
                                                                                         }
#line 1414 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 24: /* args_decl: args_decl ',' PIDENTIFIER  */
#line 205 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArgDeclaration arg_dec(p, false);

                                                                                            ((yyvsp[-2].proc_args))->args.push_back(arg_dec); 
                                                                                         }
#line 1426 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 25: /* args_decl: args_decl ',' T PIDENTIFIER  */
#line 213 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         {   
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArgDeclaration arg_dec(p, true);  

                                                                                            ((yyvsp[-3].proc_args))->args.push_back(arg_dec);   
                                                                                         }
#line 1438 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 26: /* args_decl: PIDENTIFIER  */
#line 222 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArgDeclaration arg_dec(p, false);

                                                                                             (yyval.proc_args) = new ProcedureArgumentDeclarations(); 
                                                                                             (yyval.proc_args)->args.push_back(arg_dec);   
                                                                                         }
#line 1451 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 27: /* args_decl: T PIDENTIFIER  */
#line 232 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArgDeclaration arg_dec(p, true);
                                                                                             
                                                                                            (yyval.proc_args) = new ProcedureArgumentDeclarations();
                                                                                            (yyval.proc_args)->args.push_back(arg_dec);
                                                                                         }
#line 1464 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 28: /* args: args ',' PIDENTIFIER  */
#line 241 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         {
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            Pidentifier p(token_id); 
                                                                                             
                                                                                            ((yyvsp[-2].call_args))->args.push_back(p); 
                                                                                         }
#line 1475 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 29: /* args: PIDENTIFIER  */
#line 248 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            Pidentifier p(token_id); 

                                                                                            (yyval.call_args) = new CallArguments(); 
                                                                                            (yyval.call_args)->args.push_back(p);   
                                                                                         }
#line 1487 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 30: /* expression: value  */
#line 256 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         {  
                                                                                             (yyval.expression) = new UnaryExpression((yyvsp[0].value));   
                                                                                         }
#line 1495 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 31: /* expression: value '+' value  */
#line 260 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.expression) = new BinaryExpression((yyvsp[-2].value), (yyvsp[0].value), ExpressionType::ADD);   
                                                                                         }
#line 1503 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 32: /* expression: value '-' value  */
#line 264 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.expression) = new BinaryExpression((yyvsp[-2].value), (yyvsp[0].value), ExpressionType::SUB);   
                                                                                         }
#line 1511 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 33: /* expression: value '*' value  */
#line 268 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.expression) = new BinaryExpression((yyvsp[-2].value), (yyvsp[0].value), ExpressionType::MULT);   
                                                                                         }
#line 1519 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 34: /* expression: value '/' value  */
#line 272 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.expression) = new BinaryExpression((yyvsp[-2].value), (yyvsp[0].value), ExpressionType::DIV);   
                                                                                         }
#line 1527 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 35: /* expression: value '%' value  */
#line 276 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.expression) = new BinaryExpression((yyvsp[-2].value), (yyvsp[0].value), ExpressionType::MOD);   
                                                                                         }
#line 1535 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 36: /* condition: value '=' value  */
#line 280 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.condition) = new Condition((yyvsp[-2].value), (yyvsp[0].value), ConditionType::EQUAL);   
                                                                                         }
#line 1543 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 37: /* condition: value '!' value  */
#line 284 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                             (yyval.condition) = new Condition((yyvsp[-2].value), (yyvsp[0].value), ConditionType::NOT_EQUAL);   
                                                                                         }
#line 1551 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 38: /* condition: value '>' value  */
#line 288 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.condition) = new Condition((yyvsp[-2].value), (yyvsp[0].value), ConditionType::BIGGER);                                                                                            }
#line 1558 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 39: /* condition: value '<' value  */
#line 291 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                         { 
                                                                                             (yyval.condition) = new Condition((yyvsp[-2].value), (yyvsp[0].value), ConditionType::SMALLER);   
                                                                                         }
#line 1566 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 40: /* condition: value '}' value  */
#line 295 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                       { 
                                                                                             (yyval.condition) = new Condition((yyvsp[-2].value), (yyvsp[0].value), ConditionType::BIGGER_EQUAL);   
                                                                                         }
#line 1574 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 41: /* condition: value '{' value  */
#line 299 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            (yyval.condition) = new Condition((yyvsp[-2].value), (yyvsp[0].value), ConditionType::SMALLER_EQUAL);   
                                                                                        }
#line 1582 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 42: /* value: NUMBER  */
#line 303 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            Token token_num({ .line_number = yylineno, .numerical_value = (yyvsp[0].num)});
                                                                                            (yyval.value) = new Number(token_num);
                                                                                        }
#line 1591 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 43: /* value: identifier  */
#line 308 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            //pass Value* further up
                                                                                            (yyval.value) = (yyvsp[0].value);
                                                                                        }
#line 1600 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 44: /* identifier: PIDENTIFIER  */
#line 313 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        {
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[0].id)}); 
                                                                                            (yyval.value) = new Pidentifier(token_id); 
                                                                                        }
#line 1609 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 45: /* identifier: PIDENTIFIER '[' NUMBER ']'  */
#line 318 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[-3].id)});
                                                                                            Token token_num({ .line_number = yylineno, .numerical_value = (yyvsp[-1].num)});
                                                                                            Number n(token_num);

                                                                                            (yyval.value) = new ArrayIdentifier(token_id, n);
                                                                                        }
#line 1621 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;

  case 46: /* identifier: PIDENTIFIER '[' PIDENTIFIER ']'  */
#line 326 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"
                                                                                        { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = (yyvsp[-3].id)});
                                                                                            Token token_idx({ .line_number = yylineno, .string_value = (yyvsp[-1].id)});
                                                                                            Pidentifier p(token_idx);

                                                                                            (yyval.value) = new ArrayIdentifier(token_id, p);
                                                                                        }
#line 1633 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"
    break;


#line 1637 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.tab.cpp"

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

#line 334 "/home/jadr/EngineeringThesis/code-editor/src/code_parser/parser.y"


int yyerror(std::string error_msg) 
{
    std::cout << "[GEBALANG ERROR]: Line " << yylineno << "\n";
    std::cout << "[GEBALANG MESSAGE]: " << error_msg << "\n";
    exit(1);
}
