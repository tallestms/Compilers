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
#define MAX_VARIABLE 32 //maior nome de variavel
#define MAX_FUNCTION 32 //maior nome de funcao

extern int in_function;
extern int in_logico;
extern int in_comparacao;
extern int in_condicional;
extern int nLine;
extern char identifiers[10*MAX_VARIABLE];
extern char functionArguments[10*MAX_VARIABLE];
extern char currentType[10];
extern char currentIdentifier[100];
extern int varRelations[100];
extern int currentNumber;
char currentVariable[MAX_VARIABLE + MAX_FUNCTION + 2];
int currentRelationPos = 0;
int currentRelationComparison = 0;
char currentScope[MAX_FUNCTION] = "main";
char currentFunction[MAX_FUNCTION];
int currentFunctionArity = 0;
char returnFunctionType[10];
int switchType;
int countLine = 0;
int countColum = 0;
int typeAttribute;
extern int isMatrix;
int dimension, dim1, dim2;
List* currentParameters = NULL;
hashTable* hashVariables = NULL;
hashTable* hashFunction = NULL;


/* Line 268 of yacc.c  */
#line 114 "compiler.tab.c"

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
     token_minimo = 301,
     token_nao = 302,
     token_ou = 303,
     token_padrao = 304,
     token_para = 305,
     token_parar = 306,
     token_passo = 307,
     token_reais = 308,
     token_real = 309,
     token_retorne = 310,
     token_se = 311,
     token_seleciona = 312,
     token_fimseleciona = 313,
     token_senao = 314,
     token_variaveis = 315,
     token_verdadeiro = 316,
     token_mais = 317,
     token_menos = 318,
     token_vezes = 319,
     token_dividir = 320,
     token_mod = 321,
     token_maismais = 322,
     token_menosmenos = 323,
     token_atribuicao = 324,
     token_maior = 325,
     token_menor = 326,
     token_maiori = 327,
     token_menori = 328,
     token_igual = 329,
     token_diferente = 330,
     token_el = 331,
     token_oul = 332,
     token_negacao = 333,
     token_variavel_caracter = 334,
     token_string = 335,
     token_identificador = 336
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
#line 237 "compiler.tab.c"

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
#define YYLAST   478

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  151
/* YYNRULES -- Number of states.  */
#define YYNSTATES  306

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   336

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
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    14,    15,    24,    28,    31,    32,
      37,    43,    45,    47,    49,    51,    53,    55,    57,    61,
      62,    63,    75,    76,    84,    86,    88,    90,    92,    94,
      95,    98,   103,   104,   110,   111,   116,   117,   120,   124,
     125,   130,   131,   137,   138,   140,   142,   145,   147,   150,
     153,   160,   162,   171,   178,   185,   193,   194,   205,   206,
     216,   220,   226,   227,   233,   241,   247,   248,   249,   257,
     258,   259,   269,   270,   271,   272,   286,   287,   288,   295,
     303,   313,   314,   323,   324,   333,   334,   335,   351,   352,
     353,   354,   363,   364,   365,   369,   370,   371,   375,   377,
     381,   382,   384,   388,   392,   394,   396,   398,   400,   402,
     404,   406,   410,   413,   415,   417,   419,   421,   423,   425,
     429,   433,   437,   439,   441,   443,   445,   448,   450,   452,
     456,   458,   460,   461,   467,   469,   471,   473,   475,   476,
     477,   483,   484,   485,   491,   492,   493,   501,   502,   503,
     509,   511
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      83,     0,    -1,    -1,    19,    81,     7,    84,    96,    86,
      37,    95,    30,    -1,    -1,    19,    81,     7,    85,    86,
      37,    95,    30,    -1,    60,    87,    34,    -1,    60,    34,
      -1,    -1,    89,     8,    88,     7,    -1,    87,    89,     8,
      88,     7,    -1,    38,    -1,    54,    -1,    21,    -1,    42,
      -1,    43,    -1,    90,    -1,    81,    -1,    89,     5,    81,
      -1,    -1,    -1,    45,    13,    18,    14,    13,    91,    18,
      92,    14,    24,    94,    -1,    -1,    45,    13,    18,    14,
      24,    93,    94,    -1,    39,    -1,    22,    -1,    41,    -1,
      53,    -1,    44,    -1,    -1,    95,   113,    -1,    95,    11,
      95,    12,    -1,    -1,    96,    35,    81,    97,   109,    -1,
      -1,    35,    81,    98,   109,    -1,    -1,    99,   113,    -1,
      11,    99,    12,    -1,    -1,    55,    81,   101,     7,    -1,
      -1,   104,    55,    81,   102,     7,    -1,    -1,   104,    -1,
     113,    -1,   104,   113,    -1,   142,    -1,   108,   106,    -1,
     108,   107,    -1,    49,     8,    99,    51,     7,    58,    -1,
      58,    -1,    23,     3,   144,     4,     8,    99,    51,     7,
      -1,    23,     3,   144,     4,     8,    99,    -1,     3,   112,
       4,    37,   103,    30,    -1,     3,   112,     4,    87,    37,
     103,    30,    -1,    -1,     3,   112,     4,     8,    88,   110,
      87,    37,   100,    30,    -1,    -1,     3,   112,     4,     8,
      88,   111,    37,   103,    30,    -1,    81,     8,    88,    -1,
     112,     5,    81,     8,    88,    -1,    -1,    36,     3,   105,
       4,     7,    -1,    81,    69,    40,     3,    81,     4,     7,
      -1,    40,     3,    81,     4,     7,    -1,    -1,    -1,    81,
     114,     3,   135,     4,   115,     7,    -1,    -1,    -1,    81,
      13,    18,    14,    69,   116,   136,   117,     7,    -1,    -1,
      -1,    -1,    81,    13,    18,    14,    13,   118,    18,   119,
      14,    69,   136,   120,     7,    -1,    -1,    -1,    81,    69,
     121,   136,   122,     7,    -1,    56,     3,   136,     4,    27,
      99,    33,    -1,    56,     3,   136,     4,    27,    99,    59,
      99,    33,    -1,    -1,    28,    99,    26,     3,   136,     4,
     123,     7,    -1,    -1,    26,     3,   136,     4,   124,    28,
      99,    31,    -1,    -1,    -1,    50,     3,   125,    81,    24,
     142,    20,   142,    52,   142,     4,   126,    28,    99,    32,
      -1,    -1,    -1,    -1,    57,   127,     3,    81,   128,     4,
     129,   106,    -1,    -1,    -1,   131,   132,    25,    -1,    -1,
      -1,   133,   134,    48,    -1,   136,    -1,   135,     5,   136,
      -1,    -1,   138,    -1,   136,   137,   138,    -1,   136,   130,
     138,    -1,    70,    -1,    72,    -1,    74,    -1,    71,    -1,
      73,    -1,    75,    -1,   141,    -1,   138,   139,   141,    -1,
     138,   140,    -1,    62,    -1,    63,    -1,    15,    -1,    17,
      -1,   145,    -1,   142,    -1,   141,    65,   142,    -1,   141,
      66,   142,    -1,   141,    64,   142,    -1,   140,    -1,    18,
      -1,    16,    -1,    81,    -1,    63,    81,    -1,    79,    -1,
      80,    -1,     3,   136,     4,    -1,    61,    -1,    29,    -1,
      -1,    81,   143,     3,   135,     4,    -1,   140,    -1,    18,
      -1,    16,    -1,    79,    -1,    -1,    -1,    11,   146,   150,
     147,    12,    -1,    -1,    -1,    13,   148,   155,   149,    14,
      -1,    -1,    -1,   150,     5,    13,   151,   155,   152,    14,
      -1,    -1,    -1,    13,   153,   155,   154,    14,    -1,   142,
      -1,   155,     5,   142,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   126,   126,   126,   133,   132,   139,   140,   140,   142,
     194,   245,   245,   245,   245,   245,   245,   254,   254,   258,
     258,   258,   259,   259,   260,   260,   260,   260,   260,   262,
     262,   262,   264,   263,   295,   294,   324,   324,   324,   326,
     325,   353,   352,   380,   380,   381,   381,   383,   386,   387,
     388,   388,   389,   389,   391,   392,   394,   393,   404,   402,
     411,   434,   457,   465,   467,   468,   470,   478,   469,   588,
     611,   588,   623,   647,   654,   623,   667,   683,   666,   783,
     784,   785,   785,   786,   786,   787,   788,   787,   798,   799,
     850,   798,   859,   860,   859,   887,   888,   887,   915,   915,
     915,   916,   918,   944,   947,   947,   947,   947,   947,   947,
     949,   950,   951,   952,   952,   954,   969,   981,   981,   981,
     981,   981,   982,   983,   994,  1005,  1061,  1112,  1123,  1133,
    1134,  1144,  1155,  1154,  1362,  1362,  1369,  1376,  1383,  1383,
    1383,  1404,  1404,  1404,  1425,  1426,  1425,  1443,  1443,  1442,
    1461,  1479
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
  "token_logicos", "token_matriz", "token_minimo", "token_nao", "token_ou",
  "token_padrao", "token_para", "token_parar", "token_passo",
  "token_reais", "token_real", "token_retorne", "token_se",
  "token_seleciona", "token_fimseleciona", "token_senao",
  "token_variaveis", "token_verdadeiro", "token_mais", "token_menos",
  "token_vezes", "token_dividir", "token_mod", "token_maismais",
  "token_menosmenos", "token_atribuicao", "token_maior", "token_menor",
  "token_maiori", "token_menori", "token_igual", "token_diferente",
  "token_el", "token_oul", "token_negacao", "token_variavel_caracter",
  "token_string", "token_identificador", "$accept", "PROG", "$@1", "$@2",
  "BLOCO_VARIAVEIS", "VARIAVEIS", "TIPOS_VARIAVEIS",
  "VARIAVEIS_IDENTIFICADORES", "INICIALIZAR_MATRIZ", "$@3", "$@4", "$@5",
  "TIPOS_VARIAVEIS_MATRIZ", "BLOCO", "BLOCO_FUNCOES", "$@6", "$@7",
  "BLOCO_AUXILIAR", "BLOCO_FUNCAO_RETORNO", "$@8", "$@9", "BLOCO_FUNCAO",
  "REPETICAO_COMANDO", "BLOCO_IMPRIMA", "BLOCO_SWITCH", "FIM_BLOCO_SWITCH",
  "BLOCO_SWITCH_AUX", "FUNCAO", "$@10", "$@11", "VARIAVEIS_FUNCAO",
  "COMANDO", "$@12", "$@13", "$@14", "$@15", "$@16", "$@17", "$@18",
  "$@19", "$@20", "$@21", "$@22", "$@23", "$@24", "$@25", "$@26", "$@27",
  "LOGICOS", "$@28", "$@29", "$@30", "$@31", "ARGUMENTOS_FUNCAO", "EXPR",
  "COMPARACOES", "SIEXPR", "ADICAO_SUBTRACAO", "SINALFATOR", "TERMO",
  "FATOR", "$@32", "FATOR_CASE", "MATRIZ", "$@33", "$@34", "$@35", "$@36",
  "MATRIZ_VARIAS_COLUNAS", "$@37", "$@38", "$@39", "$@40", "BLOCO_MATRIZ", 0
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
     335,   336
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    84,    83,    85,    83,    86,    86,    86,    87,
      87,    88,    88,    88,    88,    88,    88,    89,    89,    91,
      92,    90,    93,    90,    94,    94,    94,    94,    94,    95,
      95,    95,    97,    96,    98,    96,    99,    99,    99,   101,
     100,   102,   100,   103,   103,   104,   104,   105,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   109,   111,   109,
     112,   112,   112,   113,   113,   113,   114,   115,   113,   116,
     117,   113,   118,   119,   120,   113,   121,   122,   113,   113,
     113,   123,   113,   124,   113,   125,   126,   113,   127,   128,
     129,   113,   131,   132,   130,   133,   134,   130,   135,   135,
     135,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     138,   138,   138,   139,   139,   140,   140,   141,   141,   141,
     141,   141,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   143,   142,   144,   144,   144,   144,   146,   147,
     145,   148,   149,   145,   151,   152,   150,   153,   154,   150,
     155,   155
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     8,     3,     2,     0,     4,
       5,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       0,    11,     0,     7,     1,     1,     1,     1,     1,     0,
       2,     4,     0,     5,     0,     4,     0,     2,     3,     0,
       4,     0,     5,     0,     1,     1,     2,     1,     2,     2,
       6,     1,     8,     6,     6,     7,     0,    10,     0,     9,
       3,     5,     0,     5,     7,     5,     0,     0,     7,     0,
       0,     9,     0,     0,     0,    13,     0,     0,     6,     7,
       9,     0,     8,     0,     8,     0,     0,    15,     0,     0,
       0,     8,     0,     0,     3,     0,     0,     3,     1,     3,
       0,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     1,     1,     1,     1,     2,     1,     1,     3,
       1,     1,     0,     5,     1,     1,     1,     1,     0,     0,
       5,     0,     0,     5,     0,     0,     7,     0,     0,     5,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     8,     0,     8,
       0,     0,    34,     0,     0,     7,    17,     0,     0,    29,
       0,    32,    29,     6,     0,     0,     0,     0,    62,    35,
       0,     0,     0,    18,    13,    11,    14,    15,     0,    12,
       0,    16,    29,     0,    36,     5,     0,     0,     0,     0,
      88,    66,    30,     0,     0,    33,     3,     0,     0,     9,
       0,     0,    36,     0,     0,     0,    85,     0,     0,     0,
      76,     0,     0,     0,     0,    10,     0,    31,     0,   138,
     141,   115,   124,   116,   123,   131,   130,     0,   127,   128,
     125,    92,   101,   122,   110,   118,   117,     0,     0,    37,
       0,    47,     0,     0,    92,     0,     0,     0,     0,   100,
      60,     0,    43,     0,     0,     0,    92,     0,     0,   126,
       0,    83,   104,   107,   105,   108,   106,   109,     0,    93,
      96,     0,   113,   114,     0,   112,     0,     0,     0,    38,
       0,     0,     0,     0,     0,    89,     0,     0,    77,     0,
      98,    56,     0,    44,    45,    43,     0,    19,    22,   129,
     147,   139,   150,   142,   100,     0,   103,     0,     0,   102,
     111,   121,   119,   120,    92,    63,    65,     0,    36,     0,
      72,    69,     0,     0,    67,     0,     0,     0,    54,    46,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    94,    97,    81,     0,     0,    90,     0,     0,     0,
      78,     0,    99,     0,    43,    55,    20,    25,    24,    26,
      28,    27,    23,   148,   144,   140,   151,   143,   133,     0,
       0,     0,    79,    36,     0,    73,    70,    64,    68,     0,
       0,     0,     0,     0,    84,    82,     0,     0,     0,    91,
       0,     0,     0,     0,     0,     0,    59,     0,   149,   145,
       0,    80,     0,     0,    51,    48,    49,     0,    71,    39,
      57,     0,     0,     0,     0,   136,   135,   137,   134,     0,
      36,     0,     0,    41,    21,   146,    86,     0,     0,    74,
      40,     0,     0,    36,     0,     0,    42,    36,    53,     0,
      75,     0,     0,    50,    87,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     7,    11,    17,    40,    18,    41,   192,
     241,   193,   222,    27,     9,    30,    20,    63,   254,   282,
     291,   152,   153,   100,   249,   266,   250,    29,   186,   187,
      54,    99,    71,   211,   208,   252,   207,   251,   295,   108,
     183,   230,   165,   103,   292,    68,   179,   234,   128,   129,
     167,   130,   168,   149,   150,   131,    92,   134,    93,    94,
      95,   120,   279,    96,   117,   196,   118,   198,   161,   243,
     273,   194,   242,   163
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -181
static const yytype_int16 yypact[] =
{
      16,   -42,    61,    64,  -181,    38,    47,    53,    34,   -12,
     -19,    60,  -181,    44,    63,  -181,  -181,   -17,    28,  -181,
     127,  -181,  -181,  -181,    50,    51,   116,   170,    52,  -181,
     127,   204,   116,  -181,  -181,  -181,  -181,  -181,   121,  -181,
     124,  -181,  -181,   132,   130,  -181,   139,   147,   148,   149,
    -181,    -2,  -181,   145,    41,  -181,  -181,   150,   138,  -181,
     213,     9,   130,   374,    13,    79,  -181,     9,   166,   157,
     136,   175,   116,    10,    98,  -181,   168,  -181,     9,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,   102,  -181,  -181,
     181,    37,    39,  -181,    40,  -181,  -181,   231,   184,  -181,
     185,  -181,   193,   122,    73,   123,   187,   202,     9,     9,
    -181,   116,   397,   -16,   199,    19,    92,   195,    13,  -181,
     206,  -181,  -181,  -181,  -181,  -181,  -181,  -181,     9,  -181,
    -181,     9,  -181,  -181,     9,  -181,    13,    13,    13,  -181,
       9,   205,   207,   192,   190,  -181,     0,   140,   387,   113,
     387,   174,   189,   397,  -181,   397,   116,  -181,  -181,  -181,
    -181,   218,  -181,   223,     9,   208,    39,   212,   194,    39,
      40,  -181,  -181,  -181,   120,  -181,  -181,    13,   130,   229,
    -181,  -181,   234,   238,  -181,     9,   165,   210,  -181,  -181,
     220,  -181,   230,   133,    13,   239,   243,    13,   242,   118,
     130,  -181,  -181,   236,   245,   240,  -181,   244,     9,   251,
    -181,   265,   387,    22,   397,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,   223,  -181,  -181,  -181,  -181,  -181,   267,
     268,    13,  -181,   130,   254,  -181,   387,  -181,  -181,   278,
     248,   260,   269,    13,  -181,  -181,   227,   304,   279,  -181,
      17,   270,   282,   211,   256,   313,  -181,   276,  -181,   223,
      13,  -181,    35,   283,  -181,  -181,  -181,   232,  -181,  -181,
    -181,   221,   133,   291,   305,  -181,  -181,  -181,  -181,   306,
     130,     9,   301,  -181,  -181,  -181,  -181,   303,   336,   387,
    -181,   308,   285,   130,   309,   312,  -181,   130,   339,   262,
    -181,   371,   315,  -181,  -181,  -181
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -181,  -181,  -181,  -181,   316,   -66,   -28,   -14,  -181,  -181,
    -181,  -181,    54,    15,  -181,  -181,  -181,   -62,  -181,  -181,
    -181,  -146,    88,  -181,    81,  -181,  -181,   299,  -181,  -181,
    -181,   -26,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,   172,   -59,  -181,   -33,  -181,   -82,   209,
     -58,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -180
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -133
static const yytype_int16 yytable[] =
{
      97,    52,    91,    24,    57,    52,   101,   113,   104,   190,
     135,    69,    78,   180,   223,    15,    78,    23,   111,   116,
      79,   155,    80,    13,    81,    82,    83,    84,    81,    82,
      83,    84,   157,    25,    52,     1,    26,    31,    85,     3,
     248,   121,    85,   158,   110,    73,    74,   112,    10,   148,
      81,   275,    83,   276,    81,    25,    83,    60,    32,   239,
     162,     4,    16,   259,    16,    16,   263,    70,   240,   181,
      86,     5,    87,    -2,    86,   264,    87,   144,   171,   172,
     173,   174,     8,   151,   135,   -95,   154,   135,    88,    89,
      90,    16,    88,    89,    90,   166,   159,    19,   169,    24,
      22,   132,   133,    16,   136,   137,   138,   122,   123,   124,
     125,   126,   127,    10,   277,    12,   205,   184,   185,   204,
     213,   -95,   228,   185,   203,    21,   212,   189,   191,   154,
      28,    59,    33,    53,    58,    61,   162,    34,   229,   226,
     -95,    62,    64,   122,   123,   124,   125,   126,   127,   236,
      65,    66,    67,    72,    35,   217,    76,    75,    36,    37,
     102,    38,   122,   123,   124,   125,   126,   127,   -95,   105,
      39,   247,   218,   246,   219,   106,   107,   220,   109,   114,
     278,    42,   115,   119,  -132,   162,   221,   140,   154,   141,
     122,   123,   124,   125,   126,   127,    43,   142,    44,    24,
      45,   146,   274,   143,   145,   147,    46,   156,   160,   164,
      47,   -58,   175,   154,   176,    42,   177,   178,   288,   188,
      48,   182,   289,   195,    42,    77,    49,    50,   197,   189,
      43,   298,    44,   206,    56,   301,   200,   201,   209,    43,
      46,    44,   202,   139,    47,   210,    16,   214,   216,    46,
     215,    51,   224,    47,    48,   225,   227,    43,   237,    44,
      49,    50,   235,    48,   -83,   231,    43,    46,    44,    49,
      50,    47,   238,   232,   257,   245,    46,   248,   256,   260,
      47,    48,   262,   258,   267,    51,   270,    49,    50,   268,
      48,   280,   269,    43,    51,    44,    49,    50,   244,   233,
     272,   281,   283,    46,    43,   285,    44,    47,   290,   286,
     287,   293,    51,   297,    46,   296,   299,    48,    47,   300,
     303,    51,   305,    49,    50,    14,   284,   255,    48,    55,
      43,   265,    44,   253,    49,    50,   199,   261,     0,    43,
      46,    44,     0,   170,    47,     0,     0,     0,    51,    46,
       0,     0,     0,    47,    48,     0,     0,     0,     0,    51,
      49,    50,    43,    48,    44,    43,     0,    44,   271,    49,
      50,     0,    46,     0,     0,    46,    47,     0,     0,    47,
       0,     0,     0,     0,     0,    51,    48,   294,     0,    48,
     302,     0,    49,    50,    51,    49,    50,    43,     0,    44,
      98,     0,    44,   304,     0,     0,     0,    46,     0,     0,
      46,    47,   -92,     0,    47,     0,     0,    51,     0,     0,
      51,    48,     0,    43,    48,    44,     0,    49,    50,     0,
      49,    50,     0,    46,     0,   -95,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,     0,
       0,     0,    51,    49,    50,    51,     0,   122,   123,   124,
     125,   126,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-181))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      62,    27,    61,    17,    32,    31,    64,    73,    67,   155,
      92,    13,     3,    13,   194,    34,     3,    34,     8,    78,
      11,    37,    13,    35,    15,    16,    17,    18,    15,    16,
      17,    18,    13,     5,    60,    19,     8,    22,    29,    81,
      23,     4,    29,    24,    72,     4,     5,    37,    60,   108,
      15,    16,    17,    18,    15,     5,    17,    42,     8,    37,
     118,     0,    81,   243,    81,    81,    49,    69,   214,    69,
      61,     7,    63,    35,    61,    58,    63,     4,   136,   137,
     138,   140,    35,   111,   166,    48,   112,   169,    79,    80,
      81,    81,    79,    80,    81,   128,     4,    37,   131,   113,
      37,    62,    63,    81,    64,    65,    66,    70,    71,    72,
      73,    74,    75,    60,    79,    81,   178,     4,     5,   177,
     186,    48,     4,     5,     4,    81,   185,   153,   156,   155,
       3,     7,    81,    81,    13,     3,   194,    21,   200,   197,
      48,    11,     3,    70,    71,    72,    73,    74,    75,   208,
       3,     3,     3,     8,    38,    22,    18,     7,    42,    43,
      81,    45,    70,    71,    72,    73,    74,    75,    48,     3,
      54,   233,    39,   231,    41,    18,    40,    44,     3,    81,
     262,    11,    14,    81,     3,   243,    53,     3,   214,     4,
      70,    71,    72,    73,    74,    75,    26,     4,    28,   213,
      30,    14,   260,    81,    81,     3,    36,     8,    13,     3,
      40,    37,     7,   239,     7,    11,    24,    27,   280,    30,
      50,    81,   281,     5,    11,    12,    56,    57,     5,   255,
      26,   293,    28,     4,    30,   297,    28,    25,     4,    26,
      36,    28,    48,    12,    40,     7,    81,    37,    18,    36,
      30,    81,    13,    40,    50,    12,    14,    26,     7,    28,
      56,    57,    18,    50,    28,    20,    26,    36,    28,    56,
      57,    40,     7,    33,    14,     7,    36,    23,    30,    52,
      40,    50,     3,    14,    14,    81,    30,    56,    57,     7,
      50,     8,    81,    26,    81,    28,    56,    57,    31,    59,
      24,    69,    81,    36,    26,    14,    28,    40,     7,     4,
       4,     8,    81,    28,    36,     7,     7,    50,    40,     7,
      58,    81,     7,    56,    57,     9,   272,   239,    50,    30,
      26,   250,    28,    55,    56,    57,   164,    33,    -1,    26,
      36,    28,    -1,   134,    40,    -1,    -1,    -1,    81,    36,
      -1,    -1,    -1,    40,    50,    -1,    -1,    -1,    -1,    81,
      56,    57,    26,    50,    28,    26,    -1,    28,    55,    56,
      57,    -1,    36,    -1,    -1,    36,    40,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    81,    50,    51,    -1,    50,
      51,    -1,    56,    57,    81,    56,    57,    26,    -1,    28,
      26,    -1,    28,    32,    -1,    -1,    -1,    36,    -1,    -1,
      36,    40,    25,    -1,    40,    -1,    -1,    81,    -1,    -1,
      81,    50,    -1,    26,    50,    28,    -1,    56,    57,    -1,
      56,    57,    -1,    36,    -1,    48,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    81,    56,    57,    81,    -1,    70,    71,    72,
      73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    83,    81,     0,     7,    84,    85,    35,    96,
      60,    86,    81,    35,    86,    34,    81,    87,    89,    37,
      98,    81,    37,    34,    89,     5,     8,    95,     3,   109,
      97,    95,     8,    81,    21,    38,    42,    43,    45,    54,
      88,    90,    11,    26,    28,    30,    36,    40,    50,    56,
      57,    81,   113,    81,   112,   109,    30,    88,    13,     7,
      95,     3,    11,    99,     3,     3,     3,     3,   127,    13,
      69,   114,     8,     4,     5,     7,    18,    12,     3,    11,
      13,    15,    16,    17,    18,    29,    61,    63,    79,    80,
      81,   136,   138,   140,   141,   142,   145,    99,    26,   113,
     105,   142,    81,   125,   136,     3,    18,    40,   121,     3,
      88,     8,    37,    87,    81,    14,   136,   146,   148,    81,
     143,     4,    70,    71,    72,    73,    74,    75,   130,   131,
     133,   137,    62,    63,   139,   140,    64,    65,    66,    12,
       3,     4,     4,    81,     4,    81,    14,     3,   136,   135,
     136,    88,   103,   104,   113,    37,     8,    13,    24,     4,
      13,   150,   142,   155,     3,   124,   138,   132,   134,   138,
     141,   142,   142,   142,   136,     7,     7,    24,    27,   128,
      13,    69,    81,   122,     4,     5,   110,   111,    30,   113,
     103,    88,    91,    93,   153,     5,   147,     5,   149,   135,
      28,    25,    48,     4,   142,    99,     4,   118,   116,     4,
       7,   115,   136,    87,    37,    30,    18,    22,    39,    41,
      44,    53,    94,   155,    13,    12,   142,    14,     4,    99,
     123,    20,    33,    59,   129,    18,   136,     7,     7,    37,
     103,    92,   154,   151,    31,     7,   142,    99,    23,   106,
     108,   119,   117,    55,   100,   104,    30,    14,    14,   155,
      52,    33,     3,    49,    58,   106,   107,    14,     7,    81,
      30,    55,    24,   152,   142,    16,    18,    79,   140,   144,
       8,    69,   101,    81,    94,    14,     4,     4,    99,   136,
       7,   102,   126,     8,    51,   120,     7,    28,    99,     7,
       7,    99,    51,    58,    32,     7
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
#line 126 "compiler.y"
    {strcpy(identifiers, "\0");}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 127 "compiler.y"
    {
  //verifyMatrix(hashVariables);
  //verifyUsed(hashVariables);
}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 133 "compiler.y"
    {strcpy(identifiers, "\0");}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 134 "compiler.y"
    {
  //verifyMatrix(hashVariables);
  //verifyUsed(hashVariables);
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 143 "compiler.y"
    {
  //Adiciona todas as variaveis em "identifiers" na hash de variaveis.
    if(strcmp(currentScope, "main")==0)
    {
      char *varName;
      varName = strtok(identifiers, " ");
      while(varName != NULL)
      {
	if(lookupStringVariable(hashVariables, varName)==NULL)
	{
	  variable* newVar = createVariable();
	  int intVarType = convertType(currentType);
	  setVariable(newVar, varName, currentScope, intVarType, isMatrix, dimension, dim1, dim2); 
	  isMatrix = 0;  //Próxima variável entrar como não matriz
 	  addInfoVariable(hashVariables, varName, newVar);
	}
	else
	{
	  printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
	}
	varName = strtok(NULL, " ");
      }
    }
    //Neste caso, o escopo nao e global, portanto cada variavel ficara do tipo (nome_variavel nome_funcao).
    else
    {
      char *varName;
      varName = strtok(identifiers, " ");
      while(varName != NULL)
      {
	char auxVariable[100];
	strcpy(auxVariable, varName);
	strcat(auxVariable, " ");
	strcat(auxVariable, currentScope);
	if(lookupStringVariable(hashVariables, auxVariable)==NULL)
	{
	  variable* newVar = createVariable();
	  int intVarType = convertType(currentType);
	  setVariable(newVar, auxVariable, currentScope, intVarType, isMatrix, dimension, dim1, dim2); 
	  isMatrix = 0;  //Próxima variável entrar como não matriz
	  addInfoVariable(hashVariables, auxVariable, newVar);  
	}
	else
	{
	  printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
	}
	varName = strtok(NULL, " ");
      }
    }
  strcpy(identifiers, "\0");
  }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 195 "compiler.y"
    {
    if(strcmp(currentScope, "main")==0)
    {
      char *varName;
      varName = strtok(identifiers, " ");
      while(varName != NULL)
      {
      if(lookupStringVariable(hashVariables, varName)==NULL)
      {
		variable* newVar = createVariable();
		int intVarType = convertType(currentType);
		setVariable(newVar, varName, currentScope, intVarType, isMatrix, dimension, dim1, dim2); 
		isMatrix = 0;  //Próxima variável entrar como não matriz
		addInfoVariable(hashVariables, varName, newVar);
      }  
      else
      {
		printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
      }
      varName = strtok(NULL, " ");
    }
   }
   else
   {
      char *varName;
      varName = strtok(identifiers, " ");
      while(varName != NULL)
      {
	char auxVariable[100];
	strcpy(auxVariable, varName);
	strcat(auxVariable, " ");
	strcat(auxVariable, currentScope);
	if(lookupStringVariable(hashVariables, auxVariable)==NULL)
	{
	  variable* newVar = createVariable();
	  int intVarType = convertType(currentType);
	  setVariable(newVar, auxVariable, currentScope, intVarType, isMatrix, dimension, dim1, dim2); 
	  isMatrix = 0;  //Próxima variável entrar como não matriz
	  addInfoVariable(hashVariables, auxVariable, newVar);
	} 
	else
	{
	  printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
	}
	varName = strtok(NULL, " ");
      }
    }
  strcpy(identifiers, "\0");
  }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 258 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 258 "compiler.y"
    {dim2 = currentNumber;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 258 "compiler.y"
    {dimension=2;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 259 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 259 "compiler.y"
    {dimension=1;}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 264 "compiler.y"
    {
    currentParameters = startList(); //Sempre inicia uma nova lista de parametros.
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, 5, 0, NULL, 0); //A funcao foi setada com valores default, estes valores serao alterados depois.
    }
    else
    {
      printf("Erro semantico na linha %d. Funcao %s redeclarada.\n", nLine, currentIdentifier);
      destroyList(currentParameters);
    }

  strcpy(identifiers, "\0");
}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 282 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope); //Procurando funcao dentro da hash de funcoes
  if(identifier_temp!=NULL)
  {
    ((function*)(identifier_temp->info))->arity=currentFunctionArity; //Adicionando aridade
    //Irei adicionar a versao inversa da lista de tipos de parametros para facilitar mais tarde com a comparacao.
    currentParameters = reverseList(currentParameters);
    ((function*)(identifier_temp->info))->parameters=currentParameters; //Adicionando parametros
  }
  currentFunctionArity = 0; //Variavel global de aridade retornando ao valor 0.
  strcpy(currentScope, "main"); //Escopo retornando ao valor global
}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 295 "compiler.y"
    {
    currentParameters = startList(); //Sempre inicia uma nova lista de parametros.
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, 5, 0, NULL, 0);
    }
    else
    {
      printf("Erro semantico na linha %d. Funcao %s redeclarada.\n", nLine, currentIdentifier);
    }

  strcpy(identifiers, "\0");
}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 312 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope);
  if(identifier_temp!=NULL)
  {
    ((function*)(identifier_temp->info))->arity=currentFunctionArity;
    //Adicionando versao inversa da lista para facilitar mais tarde
    currentParameters = reverseList(currentParameters);
    ((function*)(identifier_temp->info))->parameters=currentParameters;
  }
  currentFunctionArity = 0;
  strcpy(currentScope, "main");
}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 326 "compiler.y"
    {
	//foi retornada uma variável, verificar tipo de retorno
	char aux[MAX_VARIABLE + MAX_FUNCTION + 1];
	strcpy(aux, currentIdentifier);
	strcat(aux, " ");
	strcat(aux, currentScope);
	List *returned_variable = lookupStringVariable(hashVariables, aux);	
	if(returned_variable != NULL){
		List *current_function = lookupStringFunction(hashFunction, currentScope);
		int variableIsMatrix = ((variable*)(returned_variable->info))->matrix;
		if(variableIsMatrix){
			printf("Funcoes nao podem retornar matrizes. Erro linha %d.\n", nLine);
		}
		int typeReturnedFunction = ((function*)(current_function->info))->returnType;
		int typeReturnedVariable = ((variable*)(returned_variable->info))->type; 
		if ( typeReturnedFunction != typeReturnedVariable ) {
			printf("Funcao %s espera um retorno do tipo %d e a variavel %s e do tipo %d na linha %d.\n", currentScope, typeReturnedFunction, currentIdentifier, typeReturnedVariable, nLine);
		}
		if ( ((variable*)(returned_variable->info))->used == 0) {
			printf("Variavel %s nao foi inicializada na linha %d.\n", currentIdentifier, nLine);
		}
	} else {
		printf("Variavel %s não declarada na linha %d.\n", currentIdentifier, nLine);
	}
	strcpy(identifiers, "\0");
}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 353 "compiler.y"
    {
	//foi retornada uma variável, verificar tipo de retorno
	char aux[MAX_VARIABLE + MAX_FUNCTION + 1];
	strcpy(aux, currentIdentifier);
	strcat(aux, " ");
	strcat(aux, currentScope);
	List *returned_variable = lookupStringVariable(hashVariables, aux);	
	if(returned_variable != NULL){
		List *current_function = lookupStringFunction(hashFunction, currentScope);
		int variableIsMatrix = ((variable*)(returned_variable->info))->matrix;
		if(variableIsMatrix){
			printf("Funcoes nao podem retornar matrizes. Erro na linha %d.\n", nLine);
		}
		int typeReturnedFunction = ((function*)(current_function->info))->returnType;
		int typeReturnedVariable = ((variable*)(returned_variable->info))->type; 
		if ( typeReturnedFunction != typeReturnedVariable ) {
			printf("Funcao %s espera um retorno do tipo %d e a variavel %s e do tipo %d na linha %d.\n", currentScope, typeReturnedFunction, currentIdentifier, typeReturnedVariable, nLine);
		}
		if ( ((variable*)(returned_variable->info))->used == 0) {
			printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
		}
	} else {
		printf("Variavel %s não declarada na linha %d.\n", currentIdentifier, nLine);
	}
	strcpy(identifiers, "\0");
}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 384 "compiler.y"
    {
}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 394 "compiler.y"
    {
// Em tipos_variaveis ira retornar o tipo de retorno da funcao, a qual sera acrescentada.
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 404 "compiler.y"
    {
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 412 "compiler.y"
    {
    currentFunctionArity++; //Variavel global controlando aridade sendo incrementada.
    char varName[MAX_FUNCTION+MAX_VARIABLE+1];
    strcpy(varName, currentIdentifier);
    strcat(varName, " ");
    strcat(varName, currentScope); //Colocando a variavel no formato desejado (nome_variavel nome_funcao)
    if(lookupStringVariable(hashVariables, varName)==NULL)
    {
      variable* newVar = createVariable();
      int intVarType = convertType(currentType);
      setVariable(newVar, varName, currentScope, intVarType, isMatrix, dimension, dim1, dim2); 
	isMatrix = 0;  //Próxima variável entrar como não matriz
	addInfoVariable(hashVariables, varName, newVar);
      currentParameters = insertList(currentParameters, (void*)intVarType);
    }
    else
    {
      printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, currentScope);
    }
  strcpy(identifiers, "\0");
}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 435 "compiler.y"
    {
    currentFunctionArity++;
    char varName[MAX_FUNCTION+MAX_VARIABLE+1];
    strcpy(varName,currentIdentifier);
    strcat(varName, " ");
    strcat(varName, currentScope);
    if(lookupStringVariable(hashVariables, varName)==NULL)
    {
      variable* newVar = createVariable();
      int intVarType = convertType(currentType);
      setVariable(newVar, varName, currentScope, intVarType, isMatrix, dimension, dim1, dim2); 
	isMatrix = 0;  //Próxima variável entrar como não matriz
      addInfoVariable(hashVariables, varName, newVar);
      currentParameters = insertList(currentParameters, (void*)intVarType);
    }
    else
    {
      printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, currentIdentifier);
    }
    
  strcpy(identifiers, "\0");
}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 465 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 468 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 470 "compiler.y"
    {

 //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
  
}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 478 "compiler.y"
    { 
  List *identifier_temp = lookupStringFunction(hashFunction, currentFunction);
  if(identifier_temp == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
  }
  else
  {
    char auxArguments[100];
    strcpy(auxArguments, functionArguments);
    int arity = numSpaces(auxArguments);
    if(arity != ((function*)(identifier_temp->info))->arity)
    {  
      printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
    }
    else
    {
      char *argumentAux;
      argumentAux = strtok(functionArguments, " ");
      List *functionTypes = (((function *)(identifier_temp->info))->parameters);
      while(argumentAux != NULL)
      {
	if(strcmp(argumentAux, "inteiro")==0)
	{
	if(0 != ((int)(functionTypes->info))) //inteiro
	  {
	    printf("Inteiro na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "real")==0)
	{
	if(3 != ((int)(functionTypes->info))) //real
	  {
	    printf("Real na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "caracter")==0)
	{
	if(1 != ((int)(functionTypes->info))) //caracter
	  {
	    printf("Caracter na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "literal")==0)
	{
	if(2 != ((int)(functionTypes->info))) //literal
	  {
	    printf("Literal na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "lógico")==0)
	{
	if(4 != ((int)(functionTypes->info))) //logico
	  {
	    printf("Logico na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else
	{
	  if(strcmp("main",currentScope)==0)
	  {
	    List *arguments_temp = lookupStringFunction(hashVariables, argumentAux);
	    if(arguments_temp==NULL)
	    {
	      //printf("Variavel %s nao declarada na linha %d\n",argumentAux, nLine);
	    }
	    else if(((variable*)(arguments_temp->info))->used == 0)
	      printf("Variavel %s nao foi inicializada na linha %d\n", argumentAux, nLine);
	    else if (((variable*)(arguments_temp->info))->type != ((int)(functionTypes->info))) 
	    {
	      printf("Variavel %s na linha %d nao tem tipo correto equivalente na funcao %s.\n", argumentAux, nLine, currentFunction);
	    }
	  }
	  else
	  {
	    char variableAux[MAX_FUNCTION+MAX_VARIABLE+1];
	    strcpy(variableAux, argumentAux);
	    strcat(variableAux, " ");
	    strcat(variableAux, currentScope);
	    
	    List *arguments_temp = lookupStringFunction(hashVariables, variableAux);
	    if(arguments_temp==NULL)
	    {
	      //printf("Variavel %s nao declarada na linha %d\n",argumentAux, nLine);
	    }
	    else if(((variable*)(arguments_temp->info))->used == 0)
	      printf("Variavel %s nao foi inicializada na linha %d\n", argumentAux, nLine);
	    else if (((variable*)(arguments_temp->info))->type != ((int)(functionTypes->info))) 
	    {
	      printf("Variavel %s na linha %d nao tem tipo correto equivalente na funcao %s.\n", argumentAux, nLine, currentFunction);
	    }
	  }
	}
	argumentAux = strtok(NULL, " ");
	functionTypes=functionTypes->next;
      }
    }
    
      int currentTypeInt = ((function *)(identifier_temp->info))->returnType;
     // printf("%d \n", currentTypeInt);
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
  }
  strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  in_function = 0;
  
}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 588 "compiler.y"
    {
	strcpy(currentVariable, currentIdentifier);
	if (strcmp(currentScope, "main")!=0 ){
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
	}
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(((variable*)(currVariable->info))->used!=1){
			printf("Erro, variavel nao inicializada na linha %d.\n", nLine);
		}
		if(((variable*)(currVariable->info))->matrix!=1){
			printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(currVariable->info))->name);
		}
		if(((variable*)(currVariable->info))->dimension != 1){
			printf("Erro na linha %d, %s possui dimensao 2.\n", nLine, ((variable*)(currVariable->info))->name);
		}
		if(((variable*)(currVariable->info))->nColum <= currentNumber ){
			printf("Erro na linha %d, %s possui %d posicoes.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColum );
		}
	}else{
		printf("Variavel nao declarada na linha %d\n",nLine);
	}
}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 611 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(!verifyRelationship(varRelations, currentRelationPos))
		{
		  printf("Tipos incompativeis na linha %d\n", nLine);
		}
		else if(((variable*)(currVariable->info))->type!=varRelations[0]){
			printf("Atribuição de tipos invalidos na linha %d.\n", nLine);
		}
	}
}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 623 "compiler.y"
    {
	strcpy(currentVariable, currentIdentifier);
	if (strcmp(currentScope, "main")!=0 ){
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
	}
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(((variable*)(currVariable->info))->used!=1){
			printf("Erro, variavel nao inicializada na linha %d.\n", nLine);
		}
		if(((variable*)(currVariable->info))->matrix!=1){
			printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(currVariable->info))->name);
		}
		if(((variable*)(currVariable->info))->dimension != 2){
			printf("Erro na linha %d, %s possui dimensao 1.\n", nLine, ((variable*)(currVariable->info))->name);
		}
		if(((variable*)(currVariable->info))->nColum <= currentNumber ){
			printf("Erro na linha %d, %s possui %d colunas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColum );
		}
	}else{
		printf("Variavel nao declarada na linha %d.\n",nLine);
	}
}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 647 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(((variable*)(currVariable->info))->nLine <= currentNumber ){
			printf("Erro na linha %d, %s possui %d linhas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColum );
		}
	}
}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 654 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(!verifyRelationship(varRelations, currentRelationPos))
		{
		  printf("Tipos incompativeis na linha %d.\n", nLine);
		}
		else if(((variable*)(currVariable->info))->type!=varRelations[0]){
			printf("Atribuição de tipos invalidos na linha %d.\n", nLine);
		}
	}
}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 667 "compiler.y"
    {

  currentRelationComparison = 0;
  char* IdentifierTemp = (char*)malloc(sizeof(identifiers));
  strcpy(IdentifierTemp, identifiers);
  IdentifierTemp = strtok(IdentifierTemp, " ");
  List *identifier_temp = lookupStringVariable(hashVariables, IdentifierTemp);
  if(identifier_temp != NULL)
    typeAttribute = ((variable *)(identifier_temp->info))->type;
  else
    typeAttribute = 5;
      
  free(IdentifierTemp);
  strcpy(currentVariable, currentIdentifier);
}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 683 "compiler.y"
    {
  if(strcmp(currentScope, "main") == 0)
    { 
      char* returnVariable = strtok(identifiers, " ");
      if (returnVariable != NULL)
      {
	List *identifier_temp = lookupStringVariable(hashVariables, returnVariable);
	if(identifier_temp==NULL)
	{
	  printf("Variavel %s nao declarada na linha %d.\n",returnVariable, nLine);
	} 
	else if (((variable*)(identifier_temp->info))->matrix != isMatrix){
		printf("Erro semântico na linha %d. Matriz e nao matriz sendo atribuidas.\n", nLine);
	}
	else if((varRelations[0] == 2 || varRelations[0] == 1) && currentRelationPos > 1) //caracter ou literal
	{
	  printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	}
	else if(in_logico==1 && in_condicional == 0)
	{
	  if((((variable*)(identifier_temp->info))->type) != 4)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  }
	  in_logico=0;
	}
	else if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
	{
	  //printRelationship(varRelations, currentRelationPos);
	  printf("Valores incompativeis na linha %d.\n", nLine);
	}
	else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0)
	{	
	  printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	 // printf("Tipo da varivel: %d -> Tipo da expressao: %d.\n",((variable*)(identifier_temp->info))->type, varRelations[0]);
	}
	else
	{
	  ((variable*)(identifier_temp->info))->used=1;
	}
	currentRelationPos = 0;
	in_comparacao = 0;
	strcpy(identifiers, "\0");
	}
	isMatrix = 0; //Limpando
      }
   else
    {
      char* varName = strtok(identifiers, " "); //Pegando o primeiro caracter
      if (varName != NULL)
      {
	char auxVariable[100];
	strcpy(auxVariable, varName);
	strcpy(identifiers, "\0");
	//printf("Funcao %s\n", currentScope);
	//printRelationship(varRelations, currentRelationPos);
	if(!verifyRelationship(varRelations, currentRelationPos))
	{
	  printf("Valores incompativeis na linha %d.\n", nLine);
	}
	else
	{
	  strcat(auxVariable, " ");
	  strcat(auxVariable, currentScope);
	  List *identifier_temp = lookupStringVariable(hashVariables, auxVariable);
	  if(identifier_temp == NULL)
	  {
	    printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
	  }
	  else if (((variable*)(identifier_temp->info))->matrix != isMatrix){
		printf("Erro semântico na linha %d. Matriz e nao matriz sendo atribuidas.\n", nLine);
	  }
	  else if((varRelations[0] == 2 || varRelations[0] == 1) && currentRelationPos > 1) //caracter ou literal
	  {
	    printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	  }
	  else if(in_logico==1 && in_condicional == 0)
	  {
	  if((((variable*)(identifier_temp->info))->type) != 4)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  }
	  in_logico=0;
	  }
	  else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  //  printf("Tipo da varivel: %d -> Tipo da expressao: %d\n",((variable*)(identifier_temp->info))->type, varRelations[0]);
	  }
	  else
	    ((variable*)(identifier_temp->info))->used=1;
	  isMatrix = 0; //Limpando
	}
	currentRelationPos = 0;
	}
      }
   }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 780 "compiler.y"
    {
currentRelationComparison = 0;
}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 785 "compiler.y"
    {in_condicional=0;}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 786 "compiler.y"
    {in_condicional=0;currentRelationPos=0;strcpy(identifiers,"\0");}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 787 "compiler.y"
    {strcpy(identifiers,"\0"); currentRelationPos=0;}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 788 "compiler.y"
    {
if(!verifyRelationship(varRelations, currentRelationPos))
  {
    printf("Valores incompativeis na linha %d\n", nLine);
  }
strcpy(identifiers,"\0"); 
currentRelationPos=0;
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 798 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos=0;}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 799 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
    else if(((variable*)(identifier_temp->info))->used == 0)
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
    else
    {  
    if(in_function!=1)
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
    }
   }
  }
  else
  //Caso em que escopo nao e funcao global, portanto precisa-se utilizar o tipo de variavel (nome_variavel nome_funcao)
  {
  char auxVariable[MAX_VARIABLE+MAX_FUNCTION+1];
  strcpy(auxVariable, currentIdentifier);
  strcat(auxVariable, " ");
  strcat(auxVariable, currentScope);
   List *identifier_temp = lookupStringVariable(hashVariables, auxVariable);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
    else if(((variable*)(identifier_temp->info))->used == 0)
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
    else
    {  
    if(in_function!=1)
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
    }
    }
    //printf("identificador\n");
  }
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 850 "compiler.y"
    {
if(varRelations[0] != 2 && varRelations[0] != 4)
  switchType = varRelations[0];
else
  switchType = 5;
}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 859 "compiler.y"
    {in_logico = 1;}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 860 "compiler.y"
    {
  if (in_comparacao = 1 && in_condicional == 0)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printRelationship(varRelations, currentRelationComparison);
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
  else if (in_condicional == 1)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printf("%s", identifiers);
    //printRelationship(varRelations, currentRelationComparison);
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 887 "compiler.y"
    {in_logico = 1;}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 888 "compiler.y"
    {
  if (in_comparacao = 1 && in_condicional == 0)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printRelationship(varRelations, currentRelationComparison);
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
    else if (in_condicional == 1)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printf("%s", identifiers);
    //printRelationship(varRelations, currentRelationComparison);
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 919 "compiler.y"
    {
    if (in_comparacao = 1 && in_condicional == 0)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printRelationship(varRelations, currentRelationComparison);
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	}
    currentRelationComparison=0;
    in_comparacao = 1;
  }
    else if (in_condicional == 1)
  {
    //printf("%d %d ", currentRelationPos, currentRelationComparison);
    //printf("%s\n", identifiers);
    //printRelationship(varRelations, currentRelationComparison);
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	}
    currentRelationComparison=0;
    //in_comparacao = 1;
  }
}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 955 "compiler.y"
    {
  /*
  Convertendo tipo do numero real e adicionando no vetor de relacoes, por exemplo (varRelations = {0, 0, 0, 1, 2})
  O vetor sera usado mais tarde para fazer comparacao de tipos de maneira tal que apenas mesmos tipos podem realizar operacoes. 
  */
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    //printf("real com sinal\n");
  }
}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 970 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    //printf("real com sinal\n");
  }

}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 984 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    //printf("real com sinal\n");
  }
}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 995 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    //printf("real com sinal\n");
  }
}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1011 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
    else if(((variable*)(identifier_temp->info))->used == 0)
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
    else
    {  
    if(in_function!=1)
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
    }
   }
  }
  else
  //Caso em que escopo nao e funcao global, portanto precisa-se utilizar o tipo de variavel (nome_variavel nome_funcao)
  {
  char auxVariable[MAX_VARIABLE+MAX_FUNCTION+1];
  strcpy(auxVariable, currentIdentifier);
  strcat(auxVariable, " ");
  strcat(auxVariable, currentScope);
   List *identifier_temp = lookupStringVariable(hashVariables, auxVariable);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
    else if(((variable*)(identifier_temp->info))->used == 0)
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
    else
    {  
    if(in_function!=1)
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
    }
    }
    //printf("identificador\n");
  }
}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1062 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
    else if(((variable*)(identifier_temp->info))->used == 0)
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
    else
    {  
    if(in_function!=1)
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
    }
    //printf("identificador\n");
    }
  }
   else
  {
  char auxVariable[100];
  strcpy(auxVariable, currentIdentifier);
  strcat(auxVariable, " ");
  strcat(auxVariable, currentScope);
   List *identifier_temp = lookupStringVariable(hashVariables, auxVariable);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
    else if(((variable*)(identifier_temp->info))->used == 0)
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
    else
    {  
    if(in_function!=1)
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
    }
    //printf("identificador\n");
    }
  }
}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1113 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
  
}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1124 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1135 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1145 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1155 "compiler.y"
    {

  //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
//printRelationship(varRelations, currentRelationPos);
List *identifier_temp = lookupStringFunction(hashFunction, currentIdentifier);
  if(identifier_temp!=NULL)
  {
    if(strcmp(currentIdentifier, "maximo")==0)
    {

      if (typeAttribute==0)
      {
	strcpy(currentFunction, "maximo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "inteiro");
      }
      else if (typeAttribute==3)
      {
	strcpy(currentFunction, "maximo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "real");
      }
      else if (typeAttribute==1)
      {
	strcpy(currentFunction, "maximo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "caracter");
      }
      else
      {
	printf("Retorno nao valido na funcao maximo na linha %d\n", nLine);
	in_function = 0;
      }
     }
     if(strcmp(currentIdentifier, "minimo")==0)
     {
      if (typeAttribute==0)
      {
	strcpy(currentFunction, "minimo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "inteiro");
      }
      else if (typeAttribute==3)
      {
	strcpy(currentFunction, "minimo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "real");
      }
      else if (typeAttribute==1)
      {
	strcpy(currentFunction, "minimo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "caracter");
      }
      else
      {
	printf("Retorno nao valido na funcao minimo na linha %d\n", nLine);
	in_function = 0;
      }
     }
     if(strcmp(currentIdentifier, "media")==0)
     {
      if (typeAttribute==0)
      {
	strcpy(currentFunction, "media");
	strcat(currentFunction, " ");
	strcat(currentFunction, "inteiro");
      }
      else if (typeAttribute==3)
      {
	strcpy(currentFunction, "media");
	strcat(currentFunction, " ");
	strcat(currentFunction, "real");
      }
      else
      {
	printf("Retorno nao valido na funcao media na linha %d\n", nLine);
	in_function = 0;
      }
     }
  }
 
}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1241 "compiler.y"
    { 
  List *identifier_temp = lookupStringFunction(hashFunction, currentFunction);
  if(identifier_temp == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
  }
  else
  {
    int arity = numSpaces(functionArguments);
    if(arity != ((function*)(identifier_temp->info))->arity)
    {  
      printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
    }
    else
    {
      char *argumentAux;
      argumentAux = strtok(functionArguments, " ");
      List *functionTypes = (((function *)(identifier_temp->info))->parameters);
      while(argumentAux != NULL)
      {
	if(strcmp(argumentAux, "inteiro")==0)
	{
	if(0 != ((int)(functionTypes->info))) //inteiro
	  {
	    printf("Inteiro na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "real")==0)
	{
	if(3 != ((int)(functionTypes->info))) //real
	  {
	    printf("Real na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "caracter")==0)
	{
	if(1 != ((int)(functionTypes->info))) //caracter
	  {
	    printf("Caracter na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "literal")==0)
	{
	if(2 != ((int)(functionTypes->info))) //literal
	  {
	    printf("Literal na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "lógico")==0)
	{
	if(4 != ((int)(functionTypes->info))) //logico
	  {
	    printf("Logico na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else
	{
	  if(strcmp("main",currentScope)==0)
	  {
	    List *arguments_temp = lookupStringFunction(hashVariables, argumentAux);
	    if(arguments_temp==NULL)
	    {
	      //printf("Variavel %s nao declarada na linha %d\n",argumentAux, nLine);
	    }
	    else if(((variable*)(arguments_temp->info))->used == 0)
	      printf("Variavel %s nao foi inicializada na linha %d\n", argumentAux, nLine);
	    else if (((variable*)(arguments_temp->info))->type != ((int)(functionTypes->info))) 
	    {
	      printf("Variavel %s na linha %d nao tem tipo correto equivalente na funcao %s.\n", argumentAux, nLine, currentFunction);
	    }
	  }
	  else
	  {
	    char variableAux[MAX_FUNCTION+MAX_VARIABLE+1];
	    strcpy(variableAux, argumentAux);
	    strcat(variableAux, " ");
	    strcat(variableAux, currentScope);
	    
	    List *arguments_temp = lookupStringFunction(hashVariables, variableAux);
	    if(arguments_temp==NULL)
	    {
	      //printf("Variavel %s nao declarada na linha %d\n",argumentAux, nLine);
	    }
	    else if(((variable*)(arguments_temp->info))->used == 0)
	      printf("Variavel %s nao foi inicializada na linha %d\n", argumentAux, nLine);
	    else if (((variable*)(arguments_temp->info))->type != ((int)(functionTypes->info))) 
	    {
	      printf("Variavel %s na linha %d nao tem tipo correto equivalente na funcao %s.\n", argumentAux, nLine, currentFunction);
	    }
	  }
	}
	argumentAux = strtok(NULL, " ");
	functionTypes=functionTypes->next;
	}
    }
      int currentTypeInt = ((function *)(identifier_temp->info))->returnType;
     // printf("%d \n", currentTypeInt);
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
  }
      if(identifier_temp!=NULL)
      {
	int currentTypeInt = ((function *)(identifier_temp->info))->returnType;
      // printf("%d \n", currentTypeInt);
	varRelations[currentRelationPos] = currentTypeInt;
	if(currentTypeInt==5)
	{
	  printf("Na linha %d, a funcao %s nao possui retorno. ", nLine, currentFunction);
	  // printf("%d \n", currentTypeInt);
	  varRelations[currentRelationPos] = currentTypeInt;
	  ++currentRelationPos;
	  ++currentRelationComparison;
	}
      }
  strcpy(functionArguments, "\0");
  //strcpy(identifiers, "\0");
  //currentRelationPos = 0;
  in_function = 0;
  }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1363 "compiler.y"
    {
  if(switchType != 0 && switchType !=5)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1370 "compiler.y"
    {
  if(switchType != 3 && switchType != 5)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
  }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1377 "compiler.y"
    {
  if(switchType != 1 && switchType !=5)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1383 "compiler.y"
    {countLine=0;}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1383 "compiler.y"
    {
	List *identifier_temp = NULL;
	if (strcmp(currentScope, "main") == 0 ){
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}else{
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}
	if(identifier_temp != NULL){
		int numLine = ((variable*)(identifier_temp->info))->nLine;
		if(countLine != numLine) {
			printf("Erro ao inicializar matriz na linha %d. Quantidade de termos incorreta.\n",nLine);
		}else{
			((variable*)(identifier_temp->info))->used = 1;
		}
	}
}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1401 "compiler.y"
    {
	isMatrix = 1;
}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1404 "compiler.y"
    {countColum=0;}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1404 "compiler.y"
    {
	List *identifier_temp = NULL;
	if (strcmp(currentScope, "main") == 0 ){
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}else{
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}
	if(identifier_temp != NULL){
		int numLine = ((variable*)(identifier_temp->info))->nLine;
		if(countLine != numLine) {
			printf("Erro ao inicializar matriz na linha %d. Quantidade de termos incorreta.\n",nLine);
		}else{
			((variable*)(identifier_temp->info))->used = 1;
		}
	}
}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1422 "compiler.y"
    {
	isMatrix = 1; 
 }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1425 "compiler.y"
    {countColum=0;}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1426 "compiler.y"
    {
countLine++;
List *identifier_temp = NULL;
	if (strcmp(currentScope, "main") == 0 ){
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}else{
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}
	if(identifier_temp != NULL){
		int numColum = ((variable*)(identifier_temp->info))->nColum;
		if(countColum != numColum) {
			printf("Erro ao inicializar matriz na linha %d. Quantidade de termos incorreta.\n",nLine);
		}
	}
}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1443 "compiler.y"
    {countColum=0;}
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1443 "compiler.y"
    {
	countLine++;
	List *identifier_temp = NULL;
	if (strcmp(currentScope, "main") == 0 ){
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}else{
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}
	if(identifier_temp != NULL){
		if (((variable*)(identifier_temp->info))->nColum != countColum){
			printf("Erro ao inicializar matriz na linha %d. Quantidade de termos incorreta.\n",nLine);	
		}
	}
}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1462 "compiler.y"
    {
	List *identifier_temp = NULL;
	if (strcmp(currentScope, "main") == 0 ){
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}else{
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}
	if(identifier_temp != NULL){
		if (((variable*)(identifier_temp->info))->type != varRelations[0]){
			printf("Tipo errado associado a matriz na linha %d\n",nLine);
		} 
	}
	countColum++;
}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1481 "compiler.y"
    {
	List *identifier_temp = NULL;
	if (strcmp(currentScope, "main") == 0 ){
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}else{
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
		identifier_temp = lookupStringVariable(hashVariables, currentVariable);
	}
	if(identifier_temp != NULL){
		if (((variable*)(identifier_temp->info))->type != varRelations[0]){
			printf("Tipo errado associado a matriz na linha %d\n",nLine);
		}
	}	
	countColum++;
}
    break;



/* Line 1806 of yacc.c  */
#line 3495 "compiler.tab.c"
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
#line 1499 "compiler.y"


#include "lex.yy.c"

void createPrimitives()
{
  //maximo, aridade 2, inteiro
  function* newFunction = createFunction();
  char functionAux[100];
  strcpy(functionAux, "maximo");
  setFunction(newFunction, functionAux,5, 0, NULL, 0);
  addInfoFunction(hashFunction, functionAux, newFunction);


  //maximo, aridade 2, inteiro
  newFunction = createFunction();
  strcpy(functionAux, "\0");
  strcpy(functionAux, "maximo");
  strcat(functionAux, " ");
  strcat(functionAux, "inteiro");
  addInfoFunction(hashFunction, functionAux, newFunction);
  
  List*argumentsFunction = startList();
  argumentsFunction = insertList(argumentsFunction, (void*)0);
  argumentsFunction = insertList(argumentsFunction, (void*)0);
  setFunction(newFunction, functionAux,0, 2, argumentsFunction, 1);

  
  //maximo, aridade 2, real
  newFunction = createFunction();
  strcpy(functionAux, "\0");
  strcpy(functionAux, "maximo");
  strcat(functionAux, " ");
  strcat(functionAux, "real");
  addInfoFunction(hashFunction, functionAux, newFunction);
  
  argumentsFunction = startList();
  argumentsFunction = insertList(argumentsFunction, (void*)3);
  argumentsFunction = insertList(argumentsFunction, (void*)3);
  setFunction(newFunction, functionAux,3, 2, argumentsFunction, 1);
  
  //maximo, aridade 2, caracter
  newFunction = createFunction();
  strcpy(functionAux, "\0");
  strcpy(functionAux, "maximo");
  strcat(functionAux, " ");
  strcat(functionAux, "caracter");
  addInfoFunction(hashFunction, functionAux, newFunction);
  
  argumentsFunction = startList();
  argumentsFunction = insertList(argumentsFunction, (void*)1);
  argumentsFunction = insertList(argumentsFunction, (void*)1);
  setFunction(newFunction, functionAux,1, 2, argumentsFunction, 1);
  
  //minimo, aridade 2, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "minimo");
  setFunction(newFunction, functionAux,0, 0, NULL, 0);
  addInfoFunction(hashFunction, functionAux, newFunction);


  //minimo, aridade 2, inteiro
  newFunction = createFunction();
  strcpy(functionAux, "\0");
  strcpy(functionAux, "minimo");
  strcat(functionAux, " ");
  strcat(functionAux, "inteiro");
  addInfoFunction(hashFunction, functionAux, newFunction);
  
  argumentsFunction = startList();
  argumentsFunction = insertList(argumentsFunction, (void*)0);
  argumentsFunction = insertList(argumentsFunction, (void*)0);
  setFunction(newFunction, functionAux,0, 2, argumentsFunction, 1);

  
  //maximo, aridade 2, real
  newFunction = createFunction();
  strcpy(functionAux, "\0");
  strcpy(functionAux, "minimo");
  strcat(functionAux, " ");
  strcat(functionAux, "real");
  addInfoFunction(hashFunction, functionAux, newFunction);
  
  argumentsFunction = startList();
  argumentsFunction = insertList(argumentsFunction, (void*)3);
  argumentsFunction = insertList(argumentsFunction, (void*)3);
  setFunction(newFunction, functionAux,3, 2, argumentsFunction, 1);
  
  //maximo, aridade 2, caracter
  newFunction = createFunction();
  strcpy(functionAux, "\0");
  strcpy(functionAux, "minimo");
  strcat(functionAux, " ");
  strcat(functionAux, "caracter");
  addInfoFunction(hashFunction, functionAux, newFunction);
  
  argumentsFunction = startList();
  argumentsFunction = insertList(argumentsFunction, (void*)1);
  argumentsFunction = insertList(argumentsFunction, (void*)1);
  setFunction(newFunction, functionAux,1, 2, argumentsFunction, 1);
  
  //media, aridade 2, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "media");
  setFunction(newFunction, functionAux,0, 0, NULL, 0);
  addInfoFunction(hashFunction, functionAux, newFunction);

  //media, aridade 2, inteiro
  newFunction = createFunction();
  strcpy(functionAux, "\0");
  strcpy(functionAux, "media");
  strcat(functionAux, " ");
  strcat(functionAux, "inteiro");
  addInfoFunction(hashFunction, functionAux, newFunction);
  
  argumentsFunction = startList();
  argumentsFunction = insertList(argumentsFunction, (void*)0);
  argumentsFunction = insertList(argumentsFunction, (void*)0);
  setFunction(newFunction, functionAux,0, 2, argumentsFunction, 1);

  //media, aridade 2, real
  newFunction = createFunction();
  strcpy(functionAux, "\0");
  strcpy(functionAux, "media");
  strcat(functionAux, " ");
  strcat(functionAux, "real");
  addInfoFunction(hashFunction, functionAux, newFunction);
  
  argumentsFunction = startList();
  argumentsFunction = insertList(argumentsFunction, (void*)3);
  argumentsFunction = insertList(argumentsFunction, (void*)3);
  setFunction(newFunction, functionAux,3, 2, argumentsFunction, 1);
  
  //imprime, aridade 1, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "imprima");
  addInfoFunction(hashFunction, functionAux, newFunction);
  setFunction(newFunction, functionAux,5, 1, NULL, 1);

  //leia, aridade 1, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "leia");
  addInfoFunction(hashFunction, functionAux, newFunction);
  setFunction(newFunction, functionAux,5, 1, NULL, 1);

}

main(){
      hashVariables = createHash(MAX_HASH);
      hashFunction = createHash(MAX_HASH);
      createPrimitives();
      yyparse();
      freeTable(hashVariables);
      freeTableFunction(hashFunction);
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void){
	printf("Erro na Linha: %d\n", nLine);
}


