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
extern int nLine;
extern char identifiers[10*MAX_VARIABLE];
extern char functionArguments[10*MAX_VARIABLE];
extern char currentType[10];
extern char currentIdentifier[100];
extern int varRelations[100];
int currentRelationPos = 0;
char currentScope[MAX_FUNCTION] = "main";
char currentFunction[MAX_FUNCTION];
int currentFunctionArity = 0;
char returnFunctionType[10];
List* currentParameters = NULL;
hashTable* hashVariables = NULL;
hashTable* hashFunction = NULL;


/* Line 268 of yacc.c  */
#line 102 "compiler.tab.c"

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
#line 224 "compiler.tab.c"

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
#define YYLAST   449

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNRULES -- Number of states.  */
#define YYNSTATES  259

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
       0,     0,     3,    12,    20,    24,    27,    28,    33,    39,
      41,    43,    45,    47,    49,    51,    53,    57,    67,    74,
      76,    78,    80,    82,    84,    85,    88,    93,    94,   100,
     101,   106,   107,   110,   114,   115,   120,   122,   124,   127,
     131,   133,   136,   139,   146,   148,   157,   164,   171,   179,
     180,   191,   192,   202,   206,   212,   213,   219,   227,   234,
     235,   236,   244,   245,   251,   259,   269,   277,   285,   299,
     305,   307,   309,   311,   315,   316,   318,   322,   326,   328,
     330,   332,   334,   336,   338,   340,   344,   347,   349,   351,
     353,   355,   357,   359,   363,   367,   371,   373,   375,   377,
     379,   382,   384,   386,   390,   392,   394,   395,   401,   403,
     405,   407,   409,   413,   417,   423,   427,   429
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      82,     0,    -1,    19,    80,     7,    90,    83,    37,    89,
      30,    -1,    19,    80,     7,    83,    37,    89,    30,    -1,
      59,    84,    34,    -1,    59,    34,    -1,    -1,    86,     8,
      85,     7,    -1,    84,    86,     8,    85,     7,    -1,    38,
      -1,    53,    -1,    21,    -1,    42,    -1,    43,    -1,    87,
      -1,    80,    -1,    86,     5,    80,    -1,    45,    13,    18,
      14,    13,    18,    14,    24,    88,    -1,    45,    13,    18,
      14,    24,    88,    -1,    39,    -1,    22,    -1,    41,    -1,
      52,    -1,    44,    -1,    -1,    89,   104,    -1,    89,    11,
      89,    12,    -1,    -1,    90,    35,    80,    91,   100,    -1,
      -1,    35,    80,    92,   100,    -1,    -1,    93,   104,    -1,
      11,    93,    12,    -1,    -1,    95,    54,    80,     7,    -1,
      95,    -1,   104,    -1,    95,   104,    -1,    96,     5,   116,
      -1,   116,    -1,    99,    97,    -1,    99,    98,    -1,    48,
       8,    93,    50,     7,    57,    -1,    57,    -1,    23,     3,
     118,     4,     8,    93,    50,     7,    -1,    23,     3,   118,
       4,     8,    93,    -1,     3,   103,     4,    37,    94,    30,
      -1,     3,   103,     4,    84,    37,    94,    30,    -1,    -1,
       3,   103,     4,     8,    85,   101,    84,    37,    94,    30,
      -1,    -1,     3,   103,     4,     8,    85,   102,    37,    94,
      30,    -1,    80,     8,    85,    -1,   103,     5,    80,     8,
      85,    -1,    -1,    36,     3,    96,     4,     7,    -1,    80,
      68,    36,     3,    96,     4,     7,    -1,    80,    68,    40,
       3,     4,     7,    -1,    -1,    -1,    80,   105,     3,   109,
       4,   106,     7,    -1,    -1,    80,    68,   110,   107,     7,
      -1,    55,     3,   110,     4,    27,    93,    33,    -1,    55,
       3,   110,     4,    27,    93,    58,    93,    33,    -1,    28,
      93,    26,     3,   110,     4,     7,    -1,    26,     3,   110,
       4,    28,    93,    31,    -1,    49,     3,    80,    24,   116,
      20,   116,    51,   116,     4,    28,    93,    32,    -1,    56,
       3,    80,     4,    97,    -1,    25,    -1,    47,    -1,   110,
      -1,   109,     5,   110,    -1,    -1,   112,    -1,   110,   111,
     112,    -1,   110,   108,   112,    -1,    69,    -1,    71,    -1,
      73,    -1,    70,    -1,    72,    -1,    74,    -1,   115,    -1,
     112,   113,   115,    -1,   112,   114,    -1,    61,    -1,    62,
      -1,    15,    -1,    17,    -1,   119,    -1,   116,    -1,   115,
      64,   116,    -1,   115,    65,   116,    -1,   115,    63,   116,
      -1,   114,    -1,    18,    -1,    16,    -1,    80,    -1,    62,
      80,    -1,    78,    -1,    79,    -1,     3,   110,     4,    -1,
      60,    -1,    29,    -1,    -1,    80,   117,     3,   109,     4,
      -1,   114,    -1,    18,    -1,    16,    -1,    78,    -1,    11,
     120,    12,    -1,    13,   121,    14,    -1,   120,     5,    13,
     121,    14,    -1,    13,   121,    14,    -1,   116,    -1,   121,
       5,   116,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   118,   124,   125,   125,   127,   177,   226,
     226,   226,   226,   226,   226,   235,   235,   239,   240,   241,
     241,   241,   241,   241,   243,   243,   243,   245,   244,   273,
     272,   300,   300,   300,   301,   301,   301,   302,   302,   304,
     304,   305,   306,   307,   307,   308,   308,   310,   311,   313,
     312,   323,   321,   330,   352,   374,   382,   383,   384,   386,
     392,   385,   426,   425,   528,   529,   530,   530,   531,   531,
     533,   533,   534,   534,   534,   535,   536,   537,   546,   546,
     546,   546,   546,   546,   548,   549,   550,   551,   551,   553,
     564,   572,   572,   572,   572,   572,   573,   574,   581,   588,
     635,   676,   682,   688,   689,   695,   702,   701,   742,   742,
     742,   742,   744,   744,   745,   745,   746,   746
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
  "TIPOS_VARIAVEIS_MATRIZ", "BLOCO", "BLOCO_FUNCOES", "$@1", "$@2",
  "BLOCO_AUXILIAR", "BLOCO_FUNCAO", "REPETICAO_COMANDO", "BLOCO_IMPRIMA",
  "BLOCO_SWITCH", "FIM_BLOCO_SWITCH", "BLOCO_SWITCH_AUX", "FUNCAO", "$@3",
  "$@4", "VARIAVEIS_FUNCAO", "COMANDO", "$@5", "$@6", "$@7", "LOGICOS",
  "ARGUMENTOS_FUNCAO", "EXPR", "COMPARACOES", "SIEXPR", "ADICAO_SUBTRACAO",
  "SINALFATOR", "TERMO", "FATOR", "$@8", "FATOR_CASE", "MATRIZ",
  "MATRIZ_VARIAS_COLUNAS", "BLOCO_MATRIZ", 0
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
      88,    88,    88,    88,    89,    89,    89,    91,    90,    92,
      90,    93,    93,    93,    94,    94,    94,    95,    95,    96,
      96,    97,    97,    98,    98,    99,    99,   100,   100,   101,
     100,   102,   100,   103,   103,   103,   104,   104,   104,   105,
     106,   104,   107,   104,   104,   104,   104,   104,   104,   104,
     108,   108,   109,   109,   109,   110,   110,   110,   111,   111,
     111,   111,   111,   111,   112,   112,   112,   113,   113,   114,
     114,   115,   115,   115,   115,   115,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   117,   116,   118,   118,
     118,   118,   119,   119,   120,   120,   121,   121
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     7,     3,     2,     0,     4,     5,     1,
       1,     1,     1,     1,     1,     1,     3,     9,     6,     1,
       1,     1,     1,     1,     0,     2,     4,     0,     5,     0,
       4,     0,     2,     3,     0,     4,     1,     1,     2,     3,
       1,     2,     2,     6,     1,     8,     6,     6,     7,     0,
      10,     0,     9,     3,     5,     0,     5,     7,     6,     0,
       0,     7,     0,     5,     7,     9,     7,     7,    13,     5,
       1,     1,     1,     3,     0,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     1,     1,     1,     1,
       2,     1,     1,     3,     1,     1,     0,     5,     1,     1,
       1,     1,     3,     3,     5,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     6,     0,     0,     0,     6,
      29,     5,    15,     0,     0,    24,     0,     0,     0,     4,
       0,     0,     0,     0,    27,    24,    55,    30,     0,    16,
      11,     9,    12,    13,     0,    10,     0,    14,    24,     0,
      31,     3,     0,     0,     0,     0,    59,    25,     0,     0,
       0,     0,     0,     0,     7,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,    28,     2,     0,     0,     0,
       8,     0,    26,     0,     0,     0,    89,    98,    90,    97,
     105,   104,     0,   101,   102,    99,     0,    75,    96,    84,
      92,    91,     0,     0,    32,     0,    40,     0,     0,     0,
       0,     0,    62,    74,    53,     0,    34,     0,     0,     0,
       0,     0,     0,   116,     0,   100,     0,     0,    70,    71,
      78,    81,    79,    82,    80,    83,     0,     0,    87,    88,
       0,    86,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    72,    49,     0,    36,
      37,    34,     0,     0,     0,   103,     0,     0,   112,     0,
     113,    74,    31,    77,    76,    85,    95,    93,    94,     0,
      56,    39,     0,    31,     0,    69,     0,     0,     0,    63,
      60,     0,     0,     0,    47,     0,    38,     0,    54,     0,
      20,    19,    21,    23,    22,    18,   115,     0,   117,     0,
       0,     0,     0,     0,     0,     0,    44,    41,    42,     0,
      58,     0,    73,     0,    34,     0,    48,     0,     0,   107,
      67,    66,     0,    64,    31,   110,   109,   111,   108,     0,
      31,    57,    61,    34,     0,    35,     0,   114,     0,     0,
       0,     0,     0,    52,    17,     0,    65,    31,     0,    50,
       0,    46,     0,    31,     0,    43,     0,    45,    68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,    13,    36,    14,    37,   195,    23,     9,
      48,    18,    58,   148,   149,    95,   175,   208,   176,    27,
     182,   183,    51,    94,    64,   211,   144,   126,   145,   146,
     127,    87,   130,    88,    89,    90,   116,   229,    91,   112,
     114
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -145
static const yytype_int16 yypact[] =
{
      10,   -47,    52,    67,  -145,    -8,     2,   -26,    56,     9,
    -145,  -145,  -145,    -9,    29,  -145,    19,    82,   135,  -145,
     115,    64,   217,    17,  -145,  -145,    66,  -145,   217,  -145,
    -145,  -145,  -145,  -145,   141,  -145,   157,  -145,  -145,   159,
     168,  -145,   180,   182,   186,   187,   129,  -145,   135,    20,
     185,    12,   192,   188,  -145,   237,   134,   168,   336,    98,
     123,   134,   124,    93,   197,  -145,  -145,   217,     1,   127,
    -145,   191,  -145,   134,   196,    98,  -145,  -145,  -145,  -145,
    -145,  -145,   131,  -145,  -145,   213,   155,     3,  -145,   103,
    -145,  -145,   240,   215,  -145,   120,  -145,   195,   161,   216,
     218,   219,   -11,   134,  -145,   217,   369,   -25,   229,     6,
     170,    98,   130,  -145,    89,  -145,   220,   222,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,   134,   134,  -145,  -145,
     134,  -145,    98,    98,    98,  -145,   134,   238,    98,    98,
     224,   223,    98,   243,   246,   136,   -11,   227,   226,   283,
    -145,   369,   217,   236,   357,  -145,   107,   244,  -145,    98,
    -145,   134,   168,     3,     3,   103,  -145,  -145,  -145,   211,
    -145,  -145,   241,   168,   264,  -145,   113,   152,   262,  -145,
    -145,   134,   194,   234,  -145,   198,  -145,   242,  -145,   261,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,    98,  -145,   177,
     287,    70,    98,   272,    24,   269,  -145,  -145,  -145,   280,
    -145,   281,   -11,   -13,   369,   284,  -145,   255,   125,  -145,
    -145,  -145,   239,  -145,   168,  -145,  -145,  -145,  -145,   290,
     168,  -145,  -145,   369,   267,  -145,   357,  -145,    98,   298,
     291,   320,   271,  -145,  -145,   299,  -145,   168,   295,  -145,
     276,   332,   249,   168,   300,  -145,   358,  -145,  -145
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,   301,   -65,   -18,   -12,  -145,    76,    -3,  -145,
    -145,  -145,   -55,  -144,  -145,   172,   140,  -145,  -145,   274,
    -145,  -145,  -145,   -23,  -145,  -145,  -145,  -145,   164,   -50,
    -145,    61,  -145,   -72,   199,   -54,  -145,  -145,  -145,  -145,
    -107
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -107
static const yytype_int16 yytable[] =
{
      47,    20,    92,   107,   156,    96,    86,   187,    11,   105,
      52,    98,   151,   102,   118,   131,    68,    69,    76,   153,
      78,   113,    49,   110,   233,    19,    47,     6,    38,     1,
     154,    38,    47,     3,    21,    55,   119,    22,   106,    76,
     225,    78,   226,    39,    16,    40,    39,    41,    40,   104,
      66,     7,     4,    42,    12,    12,    42,   113,   120,   121,
     122,   123,   124,   125,   128,   129,    43,    12,     7,    43,
     234,    12,    44,    45,     5,    44,    45,   221,   166,   167,
     168,    12,    10,   150,   171,   172,   169,   147,    96,   242,
     218,   131,   131,    15,   159,    20,    73,    46,   162,    24,
      46,    73,   227,   160,    74,   198,    75,   200,    76,    77,
      78,    79,   159,    76,    77,    78,    79,   213,   203,    25,
      21,   196,    80,    28,   137,   138,   186,    80,   150,   100,
     159,   212,   228,   101,   188,   157,   174,    73,    26,   237,
     180,   181,   158,   113,    29,    74,    50,    75,   222,    76,
      77,    78,    79,    81,    53,    82,   209,   138,    81,   117,
      82,   205,    56,    80,    54,   140,   132,   133,   134,   239,
     206,    83,    84,    85,   155,   241,    83,    84,    85,    57,
     118,   219,   181,    59,   245,    60,   118,   163,   164,    61,
      62,   150,   251,    67,    81,   118,    82,    63,   256,    70,
     103,    20,   119,    97,    99,   109,    71,   108,   119,   111,
     150,   115,    83,    84,    85,   201,  -106,   119,   136,   139,
     141,   142,   143,   161,   120,   121,   122,   123,   124,   125,
     120,   121,   122,   123,   124,   125,   118,   152,    30,   120,
     121,   122,   123,   124,   125,   170,   174,   178,    38,    72,
     162,   173,   135,   179,   189,    31,   184,   197,   119,    32,
      33,   202,    34,    39,   -51,    40,    39,   204,    40,   210,
      35,   214,   216,    42,    12,   217,    42,   230,   215,   236,
     120,   121,   122,   123,   124,   125,    43,   231,   232,    43,
     238,   235,    44,    45,   240,    44,    45,   243,    39,   247,
      40,   249,   252,   250,   253,   223,   255,   257,    42,    39,
      17,    40,   244,    39,   177,    40,   207,    46,   220,    42,
      46,    43,    65,    42,    39,   199,    40,    44,    45,   165,
     224,   246,    43,     0,    42,     0,    43,   185,    44,    45,
       0,     0,    44,    45,     0,     0,    39,    43,    40,     0,
       0,     0,    46,    44,    45,     0,    42,     0,    39,     0,
      40,     0,    93,    46,    40,     0,     0,    46,    42,    43,
     248,     0,    42,     0,     0,    44,    45,     0,    46,   190,
       0,    43,   254,     0,    39,    43,    40,    44,    45,     0,
     258,    44,    45,     0,    42,    39,   191,    40,   192,     0,
      46,   193,     0,     0,     0,    42,     0,    43,     0,   194,
       0,     0,    46,    44,    45,     0,    46,     0,    43,     0,
       0,     0,     0,     0,    44,    45,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-145))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      23,    13,    57,    68,   111,    59,    56,   151,    34,     8,
      28,    61,    37,    63,    25,    87,     4,     5,    15,    13,
      17,    75,    25,    73,    37,    34,    49,    35,    11,    19,
      24,    11,    55,    80,     5,    38,    47,     8,    37,    15,
      16,    17,    18,    26,    35,    28,    26,    30,    28,    67,
      30,    59,     0,    36,    80,    80,    36,   111,    69,    70,
      71,    72,    73,    74,    61,    62,    49,    80,    59,    49,
     214,    80,    55,    56,     7,    55,    56,     7,   132,   133,
     134,    80,    80,   106,   138,   139,   136,   105,   142,   233,
     197,   163,   164,    37,     5,   107,     3,    80,    28,    80,
      80,     3,    78,    14,    11,   159,    13,   162,    15,    16,
      17,    18,     5,    15,    16,    17,    18,   182,   173,    37,
       5,    14,    29,     8,     4,     5,   149,    29,   151,    36,
       5,   181,   204,    40,   152,     5,    23,     3,     3,    14,
       4,     5,    12,   197,    80,    11,    80,    13,   202,    15,
      16,    17,    18,    60,    13,    62,     4,     5,    60,     4,
      62,    48,     3,    29,     7,     4,    63,    64,    65,   224,
      57,    78,    79,    80,     4,   230,    78,    79,    80,    11,
      25,     4,     5,     3,   238,     3,    25,   126,   127,     3,
       3,   214,   247,     8,    60,    25,    62,    68,   253,     7,
       3,   213,    47,    80,    80,    14,    18,    80,    47,    13,
     233,    80,    78,    79,    80,     4,     3,    47,     3,    24,
       4,     3,     3,     3,    69,    70,    71,    72,    73,    74,
      69,    70,    71,    72,    73,    74,    25,     8,    21,    69,
      70,    71,    72,    73,    74,     7,    23,     4,    11,    12,
      28,    27,    12,     7,    18,    38,    30,    13,    47,    42,
      43,    20,    45,    26,    37,    28,    26,     3,    28,     7,
      53,    37,    30,    36,    80,    14,    36,     8,    80,    24,
      69,    70,    71,    72,    73,    74,    49,     7,     7,    49,
      51,     7,    55,    56,     4,    55,    56,    30,    26,     8,
      28,    30,     7,     4,    28,    33,    57,     7,    36,    26,
       9,    28,   236,    26,   142,    28,   176,    80,    31,    36,
      80,    49,    48,    36,    26,   161,    28,    55,    56,   130,
      58,    33,    49,    -1,    36,    -1,    49,    54,    55,    56,
      -1,    -1,    55,    56,    -1,    -1,    26,    49,    28,    -1,
      -1,    -1,    80,    55,    56,    -1,    36,    -1,    26,    -1,
      28,    -1,    26,    80,    28,    -1,    -1,    80,    36,    49,
      50,    -1,    36,    -1,    -1,    55,    56,    -1,    80,    22,
      -1,    49,    50,    -1,    26,    49,    28,    55,    56,    -1,
      32,    55,    56,    -1,    36,    26,    39,    28,    41,    -1,
      80,    44,    -1,    -1,    -1,    36,    -1,    49,    -1,    52,
      -1,    -1,    80,    55,    56,    -1,    80,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    82,    80,     0,     7,    35,    59,    83,    90,
      80,    34,    80,    84,    86,    37,    35,    83,    92,    34,
      86,     5,     8,    89,    80,    37,     3,   100,     8,    80,
      21,    38,    42,    43,    45,    53,    85,    87,    11,    26,
      28,    30,    36,    49,    55,    56,    80,   104,    91,    89,
      80,   103,    85,    13,     7,    89,     3,    11,    93,     3,
       3,     3,     3,    68,   105,   100,    30,     8,     4,     5,
       7,    18,    12,     3,    11,    13,    15,    16,    17,    18,
      29,    60,    62,    78,    79,    80,   110,   112,   114,   115,
     116,   119,    93,    26,   104,    96,   116,    80,   110,    80,
      36,    40,   110,     3,    85,     8,    37,    84,    80,    14,
     110,    13,   120,   116,   121,    80,   117,     4,    25,    47,
      69,    70,    71,    72,    73,    74,   108,   111,    61,    62,
     113,   114,    63,    64,    65,    12,     3,     4,     5,    24,
       4,     4,     3,     3,   107,   109,   110,    85,    94,    95,
     104,    37,     8,    13,    24,     4,   121,     5,    12,     5,
      14,     3,    28,   112,   112,   115,   116,   116,   116,   110,
       7,   116,   116,    27,    23,    97,    99,    96,     4,     7,
       4,     5,   101,   102,    30,    54,   104,    94,    85,    18,
      22,    39,    41,    44,    52,    88,    14,    13,   116,   109,
      93,     4,    20,    93,     3,    48,    57,    97,    98,     4,
       7,   106,   110,    84,    37,    80,    30,    14,   121,     4,
      31,     7,   116,    33,    58,    16,    18,    78,   114,   118,
       8,     7,     7,    37,    94,     7,    24,    14,    51,    93,
       4,    93,    94,    30,    88,   116,    33,     8,    50,    30,
       4,    93,     7,    28,    50,    57,    93,     7,    32
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
#line 114 "compiler.y"
    {
  //verifyUsed(hashVariables);
}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 120 "compiler.y"
    {
  //verifyUsed(hashVariables);
}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 128 "compiler.y"
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
	  setVariable(newVar, varName, currentScope, intVarType);  
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
	  setVariable(newVar, auxVariable, currentScope, intVarType);
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

  case 8:

/* Line 1806 of yacc.c  */
#line 178 "compiler.y"
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
	setVariable(newVar, varName, currentScope, intVarType);
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
	  setVariable(newVar, auxVariable, currentScope, intVarType);
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

  case 27:

/* Line 1806 of yacc.c  */
#line 245 "compiler.y"
    {
    currentParameters = startList(); //Sempre inicia uma nova lista de parametros.
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, 0, 0, NULL, 0); //A funcao foi setada com valores default, estes valores serao alterados depois.
    }
    else
    {
      printf("Erro semantico na linha %d. Funcao %s redeclarada.\n", nLine, currentIdentifier);
    }

  strcpy(identifiers, "\0");
}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 262 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope); //Procurando funcao dentro da hash de funcoes
  if(identifier_temp!=NULL)
  {
    ((function*)(identifier_temp->info))->arity=currentFunctionArity; //Adicionando aridade
    ((function*)(identifier_temp->info))->parameters=currentParameters; //Adicionando parametros
  }
  currentFunctionArity = 0; //Variavel global de aridade retornando ao valor 0.
  strcpy(currentScope, "main"); //Escopo retornando ao valor global
}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 273 "compiler.y"
    {
    currentParameters = startList();
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, 0, 0, NULL, 0);
    }
    else
    {
      printf("Erro semantico na linha %d. Funcao %s redeclarada.\n", nLine, currentIdentifier);
    }

  strcpy(identifiers, "\0");
}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 290 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope);
  if(identifier_temp!=NULL)
  {
    ((function*)(identifier_temp->info))->arity=currentFunctionArity;
    ((function*)(identifier_temp->info))->parameters=currentParameters;
  }
  currentFunctionArity = 0;
  strcpy(currentScope, "main");
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 313 "compiler.y"
    {
// Em tipos_variaveis ira retornar o tipo de retorno da funcao, a qual sera acrescentada.
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 323 "compiler.y"
    {
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 331 "compiler.y"
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
      setVariable(newVar, varName, currentScope, intVarType);
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

  case 54:

/* Line 1806 of yacc.c  */
#line 353 "compiler.y"
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
      setVariable(newVar, varName, currentScope, intVarType);
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

  case 59:

/* Line 1806 of yacc.c  */
#line 386 "compiler.y"
    {
  //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 392 "compiler.y"
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
      while(argumentAux != NULL)
      {
	int type = convertFunctionArgument(argumentAux, hashVariables, nLine); //Caso seja variavel, ira buscar na tabela hash equivalente o tipo, assim como se a variavel foi inicializada para uso dentro da funcao.
      
	//currentParameters = insertList(currentParameters,(void*) type);
	argumentAux = strtok(NULL, " ");
      }
    }
  }
  strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  in_function = 0;
}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 426 "compiler.y"
    {
  if(strcmp(currentScope, "main") == 0)
  {
    if(in_function == 1)
    {
      char* returnVariable = strtok(identifiers, " ");
      List *identifier_temp = lookupStringVariable(hashVariables, returnVariable);
      if(identifier_temp==NULL)
      {
	printf("Variavel %s nao declarada na linha %d.\n",returnVariable, nLine);
      }
      else
      {
	int currentTypeInt = ((variable*)(identifier_temp->info))->type;  
	((variable*)(identifier_temp->info))->used=1;
      }
      in_function = 0; //Nao e mais funcao
      currentRelationPos = 0; //Vetor de tipos volta para posicao inicial
      strcpy(currentScope,"main");
      strcpy(returnFunctionType, "\0");
      strcpy(identifiers, "\0");
    }
    else
    { 
      char* returnVariable = strtok(identifiers, " ");
      List *identifier_temp = lookupStringVariable(hashVariables, returnVariable);
      if(identifier_temp==NULL)
      {
	printf("Variavel %s nao declarada na linha %d.\n",returnVariable, nLine);
      }
      else if(!verifyRelationship(varRelations, currentRelationPos))
      {
	printf("Valores incompativeis na linha %d aaa.\n", nLine);
      }
      else if(((variable*)(identifier_temp->info))->type != varRelations[0])
      {	
	printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	printf("Tipo da varivel: %d -> Tipo da expressao: %d.\n",((variable*)(identifier_temp->info))->type, varRelations[0]);
      }
      else
      {
	((variable*)(identifier_temp->info))->used=1;
      }
      currentRelationPos = 0;
      strcpy(identifiers, "\0");
    }
   }
   else
   {
    if(in_function == 1)
    {
      char* returnVariable = strtok(identifiers, " ");
      strcat(returnVariable, " ");
      strcat(returnVariable, currentScope);
      List *identifier_temp = lookupStringVariable(hashVariables, returnVariable);
      if(identifier_temp == NULL)
      {
	printf("Variavel %s nao declarada na linha %d.\n",returnVariable, nLine);
      }
      else
      {
	int currentTypeInt = ((variable*)(identifier_temp->info))->type;  
	((variable*)(identifier_temp->info))->used=1;
      }
      in_function = 0; //Nao e mais funcao
      currentRelationPos = 0; //Vetor de tipos volta para posicao inicial
      strcpy(returnFunctionType, "\0");
      strcpy(identifiers, "\0");
    }
    else
    {
      char* varName = strtok(identifiers, " "); //Pegando o primeiro caracter
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
	else if(((variable*)(identifier_temp->info))->type != varRelations[0])
	{
	  printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  printf("Tipo da varivel: %d -> Tipo da expressao: %d\n",((variable*)(identifier_temp->info))->type, varRelations[0]);
	}
	else
	  ((variable*)(identifier_temp->info))->used=1;
      }
      currentRelationPos = 0;
      }
   }
}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 554 "compiler.y"
    {
  /*
  Convertendo tipo do numero real e adicionando no vetor de relacoes, por exemplo (varRelations = {0, 0, 0, 1, 2})
  O vetor sera usado mais tarde para fazer comparacao de tipos de maneira tal que apenas mesmos tipos podem realizar operacoes. 
  */
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("real com sinal\n");
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 565 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("inteiro com sinal\n");

}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 575 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("inteiro sem sinal\n");
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 582 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("real sem sinal\n");
}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 594 "compiler.y"
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
    int currentTypeInt = ((variable*)(identifier_temp->info))->type;
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    //printf("identificador\n");
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
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
    }
    //printf("identificador\n");
  }
}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 636 "compiler.y"
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
    int currentTypeInt = ((variable*)(identifier_temp->info))->type;
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
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
    int currentTypeInt = ((variable*)(identifier_temp->info))->type;
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    //printf("identificador\n");
    }
  }
}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 677 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 683 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 690 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 696 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 702 "compiler.y"
    {
  //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 708 "compiler.y"
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
      while(argumentAux != NULL)
      {
	int type = convertFunctionArgument(argumentAux, hashVariables, nLine); //Caso seja variavel, ira buscar na tabela hash equivalente o tipo, assim como se a variavel foi inicializada para uso dentro da funcao.
      
	//currentParameters = insertList(currentParameters,(void*) type);
	argumentAux = strtok(NULL, " ");
      }
    }
  }
  strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  in_function = 0;
}
    break;



/* Line 1806 of yacc.c  */
#line 2410 "compiler.tab.c"
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
#line 749 "compiler.y"


#include "lex.yy.c"

main(){
      hashVariables = createHash(MAX_HASH);
      hashFunction = createHash(MAX_HASH);
      yyparse();
      freeTable(hashVariables);
      freeTableFunction(hashFunction);
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void){
	printf("Erro na Linha: %d\n", nLine);
}



