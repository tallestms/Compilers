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
#line 1 "compiler.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "hash.h"
#include "lists.h"
#include "aux.h"

#define MAX_HASH 1000

extern int in_function;
extern int nLine;
extern char identifiers[500];
extern char functionArguments[500];
extern char type[10];
extern char currentType[10];
extern char currentIdentifier[100];
extern int varRelations[100];
int currentRelationPos = 0;
char currentScope[100] = "main";
char returnFunctionType[100];
function* globalFunction;
hashTable* hashVariables = NULL;
hashTable* hashFunctions = NULL;


/* Line 268 of yacc.c  */
#line 99 "compiler.tab.c"

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
     token_abrep = 258,
     token_fechap = 259,
     token_virgula = 260,
     token_ponto = 261,
     token_pontov = 262,
     token_doisp = 263,
     token_jogodav = 264,
     token_apostrofe = 265,
     token_abrec = 266,
     token_fechac = 267,
     token_abrecol = 268,
     token_fechacol = 269,
     token_numreal_comsinal = 270,
     token_numreal = 271,
     token_numinteiro_comsinal = 272,
     token_numinteiro = 273,
     token_algoritmo = 274,
     token_ate = 275,
     token_caracter = 276,
     token_caracteres = 277,
     token_caso = 278,
     token_de = 279,
     token_e = 280,
     token_enquanto = 281,
     token_entao = 282,
     token_faca = 283,
     token_falso = 284,
     token_fim = 285,
     token_fimequanto = 286,
     token_fimpara = 287,
     token_fimse = 288,
     token_fimvariaveis = 289,
     token_funcao = 290,
     token_imprima = 291,
     token_inicio = 292,
     token_inteiro = 293,
     token_inteiros = 294,
     token_leia = 295,
     token_literais = 296,
     token_literal = 297,
     token_logico = 298,
     token_logicos = 299,
     token_matriz = 300,
     token_nao = 301,
     token_ou = 302,
     token_padrao = 303,
     token_para = 304,
     token_parar = 305,
     token_passo = 306,
     token_reais = 307,
     token_real = 308,
     token_retorne = 309,
     token_se = 310,
     token_seleciona = 311,
     token_fimseleciona = 312,
     token_senao = 313,
     token_variaveis = 314,
     token_verdadeiro = 315,
     token_mais = 316,
     token_menos = 317,
     token_vezes = 318,
     token_dividir = 319,
     token_mod = 320,
     token_maismais = 321,
     token_menosmenos = 322,
     token_atribuicao = 323,
     token_maior = 324,
     token_menor = 325,
     token_maiori = 326,
     token_menori = 327,
     token_igual = 328,
     token_diferente = 329,
     token_el = 330,
     token_oul = 331,
     token_negacao = 332,
     token_variavel_caracter = 333,
     token_string = 334,
     token_identificador = 335
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 221 "compiler.tab.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   362

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNRULES -- Number of states.  */
#define YYNSTATES  241

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   335

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    11,    20,    24,    27,    28,    33,    39,
      41,    43,    45,    47,    49,    51,    53,    57,    67,    74,
      76,    78,    80,    82,    84,    85,    88,    93,    98,   102,
     103,   106,   110,   111,   116,   118,   122,   124,   127,   130,
     137,   139,   148,   155,   163,   173,   177,   183,   189,   197,
     204,   210,   211,   217,   225,   235,   243,   251,   265,   271,
     273,   275,   277,   281,   282,   284,   288,   292,   294,   296,
     298,   300,   302,   304,   306,   310,   313,   315,   317,   319,
     321,   323,   325,   329,   333,   337,   339,   341,   343,   345,
     348,   350,   352,   356,   358,   360,   361,   367,   369,   371,
     373,   375,   379,   383,   389,   393,   395
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      82,     0,    -1,    19,    80,     7,    83,    37,    89,    30,
      -1,    19,    80,     7,    83,    37,    89,    30,    90,    -1,
      59,    84,    34,    -1,    59,    34,    -1,    -1,    86,     8,
      85,     7,    -1,    84,    86,     8,    85,     7,    -1,    38,
      -1,    53,    -1,    21,    -1,    42,    -1,    43,    -1,    87,
      -1,    80,    -1,    86,     5,    80,    -1,    45,    13,    18,
      14,    13,    18,    14,    24,    88,    -1,    45,    13,    18,
      14,    24,    88,    -1,    39,    -1,    22,    -1,    41,    -1,
      52,    -1,    44,    -1,    -1,    89,    99,    -1,    89,    11,
      89,    12,    -1,    90,    35,    80,    97,    -1,    35,    80,
      97,    -1,    -1,    91,    99,    -1,    11,    91,    12,    -1,
      -1,    99,    54,    80,     7,    -1,    99,    -1,    93,     5,
     109,    -1,   109,    -1,    96,    94,    -1,    96,    95,    -1,
      48,     8,    91,    50,     7,    57,    -1,    57,    -1,    23,
       3,   111,     4,     8,    91,    50,     7,    -1,    23,     3,
     111,     4,     8,    91,    -1,     3,    98,     4,    84,    37,
      92,    30,    -1,     3,    98,     4,     8,    85,    84,    37,
      92,    30,    -1,    80,     8,    85,    -1,    98,     5,    80,
       8,    85,    -1,    36,     3,    93,     4,     7,    -1,    80,
      68,    36,     3,    93,     4,     7,    -1,    80,    68,    40,
       3,     4,     7,    -1,    80,     3,   102,     4,     7,    -1,
      -1,    80,    68,   103,   100,     7,    -1,    55,     3,   103,
       4,    27,    91,    33,    -1,    55,     3,   103,     4,    27,
      91,    58,    91,    33,    -1,    28,    91,    26,     3,   103,
       4,     7,    -1,    26,     3,   103,     4,    28,    91,    31,
      -1,    49,     3,    80,    24,   109,    20,   109,    51,   109,
       4,    28,    91,    32,    -1,    56,     3,    80,     4,    94,
      -1,    25,    -1,    47,    -1,   103,    -1,   102,     5,   103,
      -1,    -1,   105,    -1,   103,   104,   105,    -1,   103,   101,
     105,    -1,    69,    -1,    71,    -1,    73,    -1,    70,    -1,
      72,    -1,    74,    -1,   108,    -1,   105,   106,   108,    -1,
     105,   107,    -1,    61,    -1,    62,    -1,    15,    -1,    17,
      -1,   112,    -1,   109,    -1,   108,    64,   109,    -1,   108,
      65,   109,    -1,   108,    63,   109,    -1,   107,    -1,    18,
      -1,    16,    -1,    80,    -1,    62,    80,    -1,    78,    -1,
      79,    -1,     3,   103,     4,    -1,    60,    -1,    29,    -1,
      -1,    80,   110,     3,   102,     4,    -1,   107,    -1,    18,
      -1,    16,    -1,    78,    -1,    11,   113,    12,    -1,    13,
     114,    14,    -1,   113,     5,    13,   114,    14,    -1,    13,
     114,    14,    -1,   109,    -1,   114,     5,   109,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   116,   122,   123,   123,   125,   145,   166,
     166,   166,   166,   166,   166,   175,   175,   179,   180,   181,
     181,   181,   181,   181,   183,   183,   183,   184,   184,   185,
     185,   185,   186,   186,   186,   187,   187,   188,   189,   190,
     190,   191,   191,   193,   193,   194,   195,   198,   199,   200,
     201,   211,   209,   256,   257,   258,   258,   259,   259,   261,
     261,   262,   262,   262,   263,   264,   265,   274,   274,   274,
     274,   274,   274,   276,   277,   278,   279,   279,   281,   288,
     296,   296,   296,   296,   296,   297,   298,   305,   312,   324,
     336,   342,   348,   349,   355,   362,   361,   396,   396,   396,
     396,   398,   398,   399,   399,   400,   400
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "token_abrep", "token_fechap",
  "token_virgula", "token_ponto", "token_pontov", "token_doisp",
  "token_jogodav", "token_apostrofe", "token_abrec", "token_fechac",
  "token_abrecol", "token_fechacol", "token_numreal_comsinal",
  "token_numreal", "token_numinteiro_comsinal", "token_numinteiro",
  "token_algoritmo", "token_ate", "token_caracter", "token_caracteres",
  "token_caso", "token_de", "token_e", "token_enquanto", "token_entao",
  "token_faca", "token_falso", "token_fim", "token_fimequanto",
  "token_fimpara", "token_fimse", "token_fimvariaveis", "token_funcao",
  "token_imprima", "token_inicio", "token_inteiro", "token_inteiros",
  "token_leia", "token_literais", "token_literal", "token_logico",
  "token_logicos", "token_matriz", "token_nao", "token_ou", "token_padrao",
  "token_para", "token_parar", "token_passo", "token_reais", "token_real",
  "token_retorne", "token_se", "token_seleciona", "token_fimseleciona",
  "token_senao", "token_variaveis", "token_verdadeiro", "token_mais",
  "token_menos", "token_vezes", "token_dividir", "token_mod",
  "token_maismais", "token_menosmenos", "token_atribuicao", "token_maior",
  "token_menor", "token_maiori", "token_menori", "token_igual",
  "token_diferente", "token_el", "token_oul", "token_negacao",
  "token_variavel_caracter", "token_string", "token_identificador",
  "$accept", "PROG", "BLOCO_VARIAVEIS", "VARIAVEIS", "TIPOS_VARIAVEIS",
  "VARIAVEIS_IDENTIFICADORES", "INICIALIZAR_MATRIZ",
  "TIPOS_VARIAVEIS_MATRIZ", "BLOCO", "BLOCO_FUNCOES", "BLOCO_AUXILIAR",
  "BLOCO_FUNCAO", "BLOCO_IMPRIMA", "BLOCO_SWITCH", "FIM_BLOCO_SWITCH",
  "BLOCO_SWITCH_AUX", "FUNCAO", "VARIAVEIS_FUNCAO", "COMANDO", "$@1",
  "LOGICOS", "ARGUMENTOS_FUNCAO", "EXPR", "COMPARACOES", "SIEXPR",
  "ADICAO_SUBTRACAO", "SINALFATOR", "TERMO", "FATOR", "$@2", "FATOR_CASE",
  "MATRIZ", "MATRIZ_VARIAS_COLUNAS", "BLOCO_MATRIZ", 0
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
     335
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    82,    83,    83,    83,    84,    84,    85,
      85,    85,    85,    85,    85,    86,    86,    87,    87,    88,
      88,    88,    88,    88,    89,    89,    89,    90,    90,    91,
      91,    91,    92,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    98,    98,    99,    99,    99,
      99,   100,    99,    99,    99,    99,    99,    99,    99,   101,
     101,   102,   102,   102,   103,   103,   103,   104,   104,   104,
     104,   104,   104,   105,   105,   105,   106,   106,   107,   107,
     108,   108,   108,   108,   108,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   110,   109,   111,   111,   111,
     111,   112,   112,   113,   113,   114,   114
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     7,     8,     3,     2,     0,     4,     5,     1,
       1,     1,     1,     1,     1,     1,     3,     9,     6,     1,
       1,     1,     1,     1,     0,     2,     4,     4,     3,     0,
       2,     3,     0,     4,     1,     3,     1,     2,     2,     6,
       1,     8,     6,     7,     9,     3,     5,     5,     7,     6,
       5,     0,     5,     7,     9,     7,     7,    13,     5,     1,
       1,     1,     3,     0,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     1,     1,     1,     1,     2,
       1,     1,     3,     1,     1,     0,     5,     1,     1,     1,
       1,     3,     3,     5,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     6,     0,     0,     5,    15,
       0,     0,    24,     4,     0,     0,     0,     0,     0,    16,
      11,     9,    12,    13,     0,    10,     0,    14,    24,     0,
      29,     2,     0,     0,     0,     0,     0,    25,     0,     0,
       7,     0,     0,    29,     0,     0,     3,     0,     0,     0,
       0,    63,     0,     8,     0,    26,     0,     0,     0,    78,
      87,    79,    86,    94,    93,     0,    90,    91,    88,     0,
      64,    85,    73,    81,    80,     0,     0,    30,     0,     0,
       0,    36,     0,     0,     0,     0,    61,     0,     0,    51,
       0,     0,     0,     0,   105,     0,    89,     0,     0,    59,
      60,    67,    70,    68,    71,    69,    72,     0,     0,    76,
      77,     0,    75,     0,     0,     0,    31,     0,     0,    28,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,     0,     0,   101,     0,   102,    63,
      29,    66,    65,    74,    84,    82,    83,     0,     0,     0,
      27,    47,    35,     0,    29,     0,    58,     0,    50,    62,
       0,     0,    52,     0,    20,    19,    21,    23,    22,    18,
     104,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,    37,    38,     0,    49,     0,     0,
      96,    56,    55,    45,     0,     0,     0,     0,    53,    29,
      99,    98,   100,    97,     0,    29,    48,     0,   103,     0,
      32,     0,     0,     0,     0,     0,    17,     0,     0,    34,
      46,     0,    54,    29,     0,    32,    43,     0,     0,    42,
       0,     0,     0,    29,     0,    39,    44,    33,     0,    41,
      57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,    10,    26,    11,    27,   169,    17,    46,
      44,   218,    80,   156,   185,   157,   119,   149,    77,   130,
     107,    85,    86,   108,    70,   111,    71,    72,    73,    97,
     204,    74,    93,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -156
static const yytype_int16 yypact[] =
{
      -2,   -61,    32,    36,  -156,     6,   -24,    60,  -156,  -156,
     -20,   159,  -156,  -156,   160,   -13,   309,   222,   309,  -156,
    -156,  -156,  -156,  -156,    56,  -156,   104,  -156,  -156,   116,
     120,   100,   126,   143,   145,   150,     5,  -156,   168,   162,
    -156,    19,    92,   120,   273,   115,   157,   122,   117,    92,
     119,    92,    22,  -156,   192,  -156,    92,   194,   122,  -156,
    -156,  -156,  -156,  -156,  -156,   146,  -156,  -156,   231,   141,
      31,  -156,   154,  -156,  -156,    78,   232,  -156,   233,   165,
     137,  -156,   213,   151,   243,   155,   265,   248,   253,   265,
      -1,   158,   122,   112,  -156,    45,  -156,   254,   237,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,    92,    92,  -156,
    -156,    92,  -156,   122,   122,   122,  -156,    92,   179,  -156,
     233,   259,   122,   122,   234,   245,   262,    92,   122,   266,
     272,   257,    74,  -156,   118,   267,  -156,   122,  -156,    92,
     120,    31,    31,   154,  -156,  -156,  -156,   169,   276,   173,
    -156,  -156,  -156,   261,   120,   284,  -156,    30,  -156,   265,
     181,   281,  -156,   275,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,   122,  -156,   185,   218,    14,   309,     3,   215,   122,
       8,    11,   285,  -156,  -156,  -156,   290,  -156,   282,   142,
    -156,  -156,  -156,  -156,   309,   -28,   300,   260,  -156,   120,
    -156,  -156,  -156,  -156,   306,   120,  -156,    74,  -156,   235,
     277,   309,   122,   227,   310,    94,  -156,   -19,   289,   271,
    -156,   316,  -156,   120,   307,   277,  -156,   241,   299,   236,
     274,   311,   333,   120,   335,  -156,  -156,  -156,   268,  -156,
    -156
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -156,  -156,  -156,  -155,   -15,    -8,  -156,   136,   317,  -156,
     -42,   121,   216,   193,  -156,  -156,   229,  -156,   -17,  -156,
    -156,   217,   -36,  -156,    96,  -156,   -65,   244,   -43,  -156,
    -156,  -156,  -156,   -85
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -96
static const yytype_int16 yytable[] =
{
      37,    75,    14,    38,    81,   112,    69,   134,    51,   210,
       8,   194,   131,    83,    13,    94,    89,     1,   225,     3,
      91,   192,   195,   132,    37,    56,    59,   200,    61,   201,
      28,    55,     4,    57,    29,    58,    30,    59,    60,    61,
      62,   198,   140,     5,    32,    29,    59,    30,    61,    94,
     137,    63,     9,   155,   217,    32,     9,    33,    87,   138,
       9,     9,    88,    34,    35,     6,   199,    19,    33,    39,
     144,   145,   146,    52,    34,    35,   112,   112,   182,   152,
     153,   147,    64,     9,    65,    81,   189,   183,    36,   202,
     116,   159,   109,   110,   172,    56,   164,    12,   174,    36,
      66,    67,    68,    57,    29,    58,    30,    59,    60,    61,
      62,    40,   180,   165,    32,   166,   203,   135,   167,    42,
      29,    63,    30,   137,   136,    56,   168,    33,    94,    47,
      32,    43,   170,    34,    35,    45,   197,    59,    60,    61,
      62,   121,   122,    33,   224,    98,    48,   137,    49,    34,
      35,    63,    64,    50,    65,   124,   208,   213,    36,   126,
     127,   193,   133,   215,    15,    15,    99,    16,    18,   221,
      66,    67,    68,   175,    36,    53,    99,   177,   178,   209,
      54,   229,    64,    99,    65,   186,   122,    14,   100,   190,
     127,   238,    79,   219,    99,    78,   220,    82,   100,    84,
      66,    67,    68,   141,   142,   100,    90,    92,   219,    14,
     101,   102,   103,   104,   105,   106,   100,   113,   114,   115,
     101,   102,   103,   104,   105,   106,    96,   101,   102,   103,
     104,   105,   106,    28,   -95,   117,   118,   123,   101,   102,
     103,   104,   105,   106,    29,   120,    30,   125,    29,   191,
      30,   128,    31,    29,    32,    30,   129,   139,    32,   148,
     222,   154,    29,    32,    30,   140,   151,    33,   155,   158,
     161,    33,    32,    34,    35,   163,    33,    34,    35,   162,
     171,   179,    34,    35,   176,    33,   234,   181,   187,   188,
      99,    34,    35,   205,    29,   196,    30,   206,    36,    76,
     240,    30,    36,    29,    32,    30,   207,    36,   211,    32,
     214,   212,   100,    32,   230,     9,    36,    33,   223,   226,
     228,   232,    33,    34,    35,   227,    33,   233,    34,    35,
      20,   235,    34,    35,   101,   102,   103,   104,   105,   106,
     237,   236,   239,   216,   160,    41,   231,    21,    36,   150,
     184,    22,    23,    36,    24,   143,   173,    36,     0,     0,
       0,     0,    25
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-156))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      17,    43,    10,    18,    47,    70,    42,    92,     3,    37,
      34,     8,    13,    49,    34,    58,    52,    19,    37,    80,
      56,     7,   177,    24,    41,     3,    15,    16,    17,    18,
      11,    12,     0,    11,    26,    13,    28,    15,    16,    17,
      18,    33,    28,     7,    36,    26,    15,    28,    17,    92,
       5,    29,    80,    23,   209,    36,    80,    49,    36,    14,
      80,    80,    40,    55,    56,    59,    58,    80,    49,    13,
     113,   114,   115,    68,    55,    56,   141,   142,    48,   122,
     123,   117,    60,    80,    62,   128,   171,    57,    80,    78,
      12,   127,    61,    62,   137,     3,    22,    37,   140,    80,
      78,    79,    80,    11,    26,    13,    28,    15,    16,    17,
      18,     7,   154,    39,    36,    41,   181,     5,    44,     3,
      26,    29,    28,     5,    12,     3,    52,    49,   171,     3,
      36,    11,    14,    55,    56,    35,   179,    15,    16,    17,
      18,     4,     5,    49,    50,     4,     3,     5,     3,    55,
      56,    29,    60,     3,    62,     4,    14,   199,    80,     4,
       5,   176,     4,   205,     5,     5,    25,     8,     8,   212,
      78,    79,    80,     4,    80,     7,    25,     4,     5,   194,
      18,   223,    60,    25,    62,     4,     5,   195,    47,     4,
       5,   233,    35,   210,    25,    80,   211,    80,    47,    80,
      78,    79,    80,   107,   108,    47,    14,    13,   225,   217,
      69,    70,    71,    72,    73,    74,    47,    63,    64,    65,
      69,    70,    71,    72,    73,    74,    80,    69,    70,    71,
      72,    73,    74,    11,     3,     3,     3,    24,    69,    70,
      71,    72,    73,    74,    26,    80,    28,     4,    26,    31,
      28,     3,    30,    26,    36,    28,     3,     3,    36,    80,
      33,    27,    26,    36,    28,    28,     7,    49,    23,     7,
       4,    49,    36,    55,    56,    18,    49,    55,    56,     7,
      13,    20,    55,    56,     8,    49,    50,     3,     7,    14,
      25,    55,    56,     8,    26,    80,    28,     7,    80,    26,
      32,    28,    80,    26,    36,    28,    24,    80,     8,    36,
       4,    51,    47,    36,     7,    80,    80,    49,     8,    30,
       4,    80,    49,    55,    56,    54,    49,    28,    55,    56,
      21,    57,    55,    56,    69,    70,    71,    72,    73,    74,
       7,    30,     7,   207,   128,    28,   225,    38,    80,   120,
     157,    42,    43,    80,    45,   111,   139,    80,    -1,    -1,
      -1,    -1,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    82,    80,     0,     7,    59,    83,    34,    80,
      84,    86,    37,    34,    86,     5,     8,    89,     8,    80,
      21,    38,    42,    43,    45,    53,    85,    87,    11,    26,
      28,    30,    36,    49,    55,    56,    80,    99,    85,    13,
       7,    89,     3,    11,    91,    35,    90,     3,     3,     3,
       3,     3,    68,     7,    18,    12,     3,    11,    13,    15,
      16,    17,    18,    29,    60,    62,    78,    79,    80,   103,
     105,   107,   108,   109,   112,    91,    26,    99,    80,    35,
      93,   109,    80,   103,    80,   102,   103,    36,    40,   103,
      14,   103,    13,   113,   109,   114,    80,   110,     4,    25,
      47,    69,    70,    71,    72,    73,    74,   101,   104,    61,
      62,   106,   107,    63,    64,    65,    12,     3,     3,    97,
      80,     4,     5,    24,     4,     4,     4,     5,     3,     3,
     100,    13,    24,     4,   114,     5,    12,     5,    14,     3,
      28,   105,   105,   108,   109,   109,   109,   103,    80,    98,
      97,     7,   109,   109,    27,    23,    94,    96,     7,   103,
      93,     4,     7,    18,    22,    39,    41,    44,    52,    88,
      14,    13,   109,   102,    91,     4,     8,     4,     5,    20,
      91,     3,    48,    57,    94,    95,     4,     7,    14,   114,
       4,    31,     7,    85,     8,    84,    80,   109,    33,    58,
      16,    18,    78,   107,   111,     8,     7,    24,    14,    85,
      37,     8,    51,    91,     4,    91,    88,    84,    92,    99,
      85,   109,    33,     8,    50,    37,    30,    54,     4,    91,
       7,    92,    80,    28,    50,    57,    30,     7,    91,     7,
      32
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
        case 2:

/* Line 1806 of yacc.c  */
#line 112 "compiler.y"
    {
  verifyUsed(hashVariables);
}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 118 "compiler.y"
    {
  verifyUsed(hashVariables);
}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 126 "compiler.y"
    {
    char *varName, *varType;
    varName = strtok(identifiers, " ");
    while(varName != NULL)
    {
      variable* newVar = createVariable();
      int intVarType = convertType(type);
      setVariable(newVar, varName, currentScope, intVarType);
      if(lookupStringVariable(hashVariables, varName)==NULL)
	addInfoVariable(hashVariables, varName, newVar);
      else
      {
	printf("Erro semantico na linha %d. Variavel redeclarada.\n", nLine);
	exit(1);
      }
      varName = strtok(NULL, " ");
    }
  strcpy(identifiers, "\0");
  }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 146 "compiler.y"
    {
    char *varName, *varType;
    varName = strtok(identifiers, " ");
    while(varName != NULL)
    {
      variable* newVar = createVariable();
      int intVarType = convertType(type);
      setVariable(newVar, varName, currentScope, intVarType);
      if(lookupStringVariable(hashVariables, varName)==NULL)
	addInfoVariable(hashVariables, varName, newVar);
      else
      {
	printf("Erro semantico na linha %d. Variavel redeclarada.\n", nLine);
	exit(1);
      }
      varName = strtok(NULL, " ");
    }
  strcpy(identifiers, "\0");
  }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 211 "compiler.y"
    {
  if(in_function == 1)
  {
    char* returnVariable = strtok(identifiers, " ");
    List *identifier_temp = lookupStringVariable(hashVariables, returnVariable);
    if(identifier_temp==NULL)
    {
      printf("Variavel nao declarada na linha %d.\n", nLine);
      globalFunction->returnType = 5; //default sem tipo de retorno.
    }
    else
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;  
      globalFunction->returnType = currentTypeInt;
    }
    in_function = 0; //Nao e mais funcao
    currentRelationPos = 0; //Vetor de tipos volta para posicao inicial
    strcpy(currentScope,"main");
    strcpy(returnFunctionType, "\0");
    strcpy(identifiers, "\0");
  }
  else
  { 
    strcpy(identifiers, "\0");
    if(!verifyRelationship(varRelations, currentRelationPos))
    {
      printf("Valores incompativeis na linha %d\n", nLine);
    }
    else
    {
      List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
      if(identifier_temp == NULL)
      {
	printf("Variavel nao declarada na linha %d\n", nLine);
      }
      if(((variable*)(identifier_temp->info))->type != varRelations[0])
      {
	printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	printf("Tipo da varivel: %d -> Tipo da expressao: %d\n",((variable*)(identifier_temp->info))->type, varRelations[0]);
      }
    ((variable*)(identifier_temp->info))->used=1;
    }
    currentRelationPos = 0;
   }
}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 282 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("real com sinal\n");
}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 289 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("inteiro com sinal\n");

}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 299 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("inteiro sem sinal\n");
}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 306 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("real sem sinal\n");
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 313 "compiler.y"
    {
  List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
  if(identifier_temp==NULL)
  {
    printf("Variavel nao declarada na linha %d\n", nLine);
  }
  int currentTypeInt = ((variable*)(identifier_temp->info))->type;
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("identificador\n");
}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 325 "compiler.y"
    {
  List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
  if(identifier_temp==NULL)
  {
    printf("Variavel nao declarada na linha %d\n", nLine);
  }
  int currentTypeInt = ((variable*)(identifier_temp->info))->type;
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("identificador\n");
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 337 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 343 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 350 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 356 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 362 "compiler.y"
    {
  strcpy(currentScope, currentIdentifier);
  in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments.
}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 367 "compiler.y"
    { 
  List *identifier_temp = lookupStringFunction(hashFunctions, currentScope);
  if(identifier_temp == NULL)
  {
    function* newFunction = createFunction();
    globalFunction = newFunction;
    List* functionList = startList();
    List* parametersList = startList();
    //printf("%s\n",functionArguments); //Argumentos das funcoes separados
    //Tipo de retorno sera definido de acordo com variavel sendo atribuida, no final que sera feita a verificacao.

    char *argumentType;
    argumentType = strtok(functionArguments, " ");
    while(argumentType != NULL)
    {
      int type = convertFunctionArgument(argumentType, hashVariables, nLine); //Caso seja variavel, ira buscar na tabela hash equivalente o tipo, assim como se a variavel foi inicializada para uso dentro da funcao.
      parametersList = insertList(parametersList,(void*) type);
      argumentType = strtok(NULL, " ");
    } 
    if(seekList(parametersList, (void*)5, compareInt) == NULL) 
    //Se tipo 5 foi encontrado, houve erro de variavel nao declarada ou nao utilizada, entao nao adicionaremos a funcao na tabela hash.
    {
      int arity = countList(parametersList);
      setFunction(newFunction, currentScope, 0, arity, parametersList, nLine, functionList);
    }
  }
  strcpy(functionArguments, "\0");
}
    break;



/* Line 1806 of yacc.c  */
#line 1991 "compiler.tab.c"
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
#line 403 "compiler.y"


#include "lex.yy.c"

main(){
      hashVariables = createHash(MAX_HASH);
      hashFunctions = createHash(MAX_HASH);
      yyparse();
	
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void){
	printf("Erro na Linha: %d\n", nLine);
}



