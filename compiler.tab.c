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
char currentFunction[100];
int currentFunctionArity = 0;
char returnFunctionType[100];
function* globalFunction;
List* currentParameters;
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
#define YYLAST   451

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNRULES -- Number of states.  */
#define YYNSTATES  257

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
     240,   241,   247,   255,   265,   273,   281,   295,   301,   303,
     305,   307,   311,   312,   314,   318,   322,   324,   326,   328,
     330,   332,   334,   336,   340,   343,   345,   347,   349,   351,
     353,   355,   359,   363,   367,   369,   371,   373,   375,   378,
     380,   382,   386,   388,   390,   391,   397,   399,   401,   403,
     405,   409,   413,   419,   423,   425
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
      95,    -1,   104,    -1,    95,   104,    -1,    96,     5,   114,
      -1,   114,    -1,    99,    97,    -1,    99,    98,    -1,    48,
       8,    93,    50,     7,    57,    -1,    57,    -1,    23,     3,
     116,     4,     8,    93,    50,     7,    -1,    23,     3,   116,
       4,     8,    93,    -1,     3,   103,     4,    37,    94,    30,
      -1,     3,   103,     4,    84,    37,    94,    30,    -1,    -1,
       3,   103,     4,     8,    85,   101,    84,    37,    94,    30,
      -1,    -1,     3,   103,     4,     8,    85,   102,    37,    94,
      30,    -1,    80,     8,    85,    -1,   103,     5,    80,     8,
      85,    -1,    -1,    36,     3,    96,     4,     7,    -1,    80,
      68,    36,     3,    96,     4,     7,    -1,    80,    68,    40,
       3,     4,     7,    -1,    80,     3,   107,     4,     7,    -1,
      -1,    80,    68,   108,   105,     7,    -1,    55,     3,   108,
       4,    27,    93,    33,    -1,    55,     3,   108,     4,    27,
      93,    58,    93,    33,    -1,    28,    93,    26,     3,   108,
       4,     7,    -1,    26,     3,   108,     4,    28,    93,    31,
      -1,    49,     3,    80,    24,   114,    20,   114,    51,   114,
       4,    28,    93,    32,    -1,    56,     3,    80,     4,    97,
      -1,    25,    -1,    47,    -1,   108,    -1,   107,     5,   108,
      -1,    -1,   110,    -1,   108,   109,   110,    -1,   108,   106,
     110,    -1,    69,    -1,    71,    -1,    73,    -1,    70,    -1,
      72,    -1,    74,    -1,   113,    -1,   110,   111,   113,    -1,
     110,   112,    -1,    61,    -1,    62,    -1,    15,    -1,    17,
      -1,   117,    -1,   114,    -1,   113,    64,   114,    -1,   113,
      65,   114,    -1,   113,    63,   114,    -1,   112,    -1,    18,
      -1,    16,    -1,    80,    -1,    62,    80,    -1,    78,    -1,
      79,    -1,     3,   108,     4,    -1,    60,    -1,    29,    -1,
      -1,    80,   115,     3,   107,     4,    -1,   112,    -1,    18,
      -1,    16,    -1,    78,    -1,    11,   118,    12,    -1,    13,
     119,    14,    -1,   118,     5,    13,   119,    14,    -1,    13,
     119,    14,    -1,   114,    -1,   119,     5,   114,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   118,   124,   125,   125,   127,   172,   218,
     218,   218,   218,   218,   218,   227,   227,   231,   232,   233,
     233,   233,   233,   233,   235,   235,   235,   237,   236,   266,
     265,   293,   293,   293,   294,   294,   294,   295,   295,   297,
     297,   298,   299,   300,   300,   301,   301,   303,   306,   311,
     309,   320,   318,   327,   350,   374,   379,   380,   381,   382,
     384,   383,   493,   494,   495,   495,   496,   496,   498,   498,
     499,   499,   499,   500,   501,   502,   511,   511,   511,   511,
     511,   511,   513,   514,   515,   516,   516,   518,   525,   533,
     533,   533,   533,   533,   534,   535,   542,   549,   590,   631,
     637,   643,   644,   650,   657,   656,   696,   696,   696,   696,
     698,   698,   699,   699,   700,   700
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
  "$@4", "VARIAVEIS_FUNCAO", "COMANDO", "$@5", "LOGICOS",
  "ARGUMENTOS_FUNCAO", "EXPR", "COMPARACOES", "SIEXPR", "ADICAO_SUBTRACAO",
  "SINALFATOR", "TERMO", "FATOR", "$@6", "FATOR_CASE", "MATRIZ",
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
     100,   102,   100,   103,   103,   103,   104,   104,   104,   104,
     105,   104,   104,   104,   104,   104,   104,   104,   106,   106,
     107,   107,   107,   108,   108,   108,   109,   109,   109,   109,
     109,   109,   110,   110,   110,   111,   111,   112,   112,   113,
     113,   113,   113,   113,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   115,   114,   116,   116,   116,   116,
     117,   117,   118,   118,   119,   119
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     7,     3,     2,     0,     4,     5,     1,
       1,     1,     1,     1,     1,     1,     3,     9,     6,     1,
       1,     1,     1,     1,     0,     2,     4,     0,     5,     0,
       4,     0,     2,     3,     0,     4,     1,     1,     2,     3,
       1,     2,     2,     6,     1,     8,     6,     6,     7,     0,
      10,     0,     9,     3,     5,     0,     5,     7,     6,     5,
       0,     5,     7,     9,     7,     7,    13,     5,     1,     1,
       1,     3,     0,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     1,     1,     1,     1,     2,     1,
       1,     3,     1,     1,     0,     5,     1,     1,     1,     1,
       3,     3,     5,     3,     1,     3
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
      31,     3,     0,     0,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     7,     0,     0,    31,     0,     0,
       0,     0,     0,    72,     0,    28,     2,     0,     0,     0,
       8,     0,    26,     0,     0,     0,    87,    96,    88,    95,
     103,   102,     0,    99,   100,    97,     0,    73,    94,    82,
      90,    89,     0,     0,    32,     0,    40,     0,     0,     0,
       0,    70,     0,     0,    60,    53,     0,    34,     0,     0,
       0,     0,     0,     0,   114,     0,    98,     0,     0,    68,
      69,    76,    79,    77,    80,    78,    81,     0,     0,    85,
      86,     0,    84,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,     0,
      36,    37,    34,     0,     0,     0,   101,     0,     0,   110,
       0,   111,    72,    31,    75,    74,    83,    93,    91,    92,
       0,    56,    39,     0,    31,     0,    67,     0,    59,    71,
       0,     0,    61,     0,     0,    47,     0,    38,     0,    54,
       0,    20,    19,    21,    23,    22,    18,   113,     0,   115,
       0,     0,     0,     0,     0,     0,     0,    44,    41,    42,
       0,    58,     0,    34,     0,    48,     0,     0,   105,    65,
      64,     0,    62,    31,   108,   107,   109,   106,     0,    31,
      57,    34,     0,    35,     0,   112,     0,     0,     0,     0,
       0,    52,    17,     0,    63,    31,     0,    50,     0,    46,
       0,    31,     0,    43,     0,    45,    66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,    13,    36,    14,    37,   196,    23,     9,
      48,    18,    58,   149,   150,    95,   176,   209,   177,    27,
     183,   184,    51,    94,   147,   127,   100,   101,   128,    87,
     131,    88,    89,    90,   117,   228,    91,   113,   115
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -145
static const yytype_int16 yypact[] =
{
      -2,   -49,    33,    30,  -145,   -15,   -35,   -10,    10,     0,
    -145,  -145,  -145,    -9,    86,  -145,   -31,    31,    70,  -145,
     123,    -5,   398,   226,  -145,  -145,     1,  -145,   398,  -145,
    -145,  -145,  -145,  -145,    85,  -145,    97,  -145,  -145,   103,
     100,  -145,   119,   130,   139,   155,    11,  -145,    70,   229,
     118,   113,   144,   142,  -145,   215,    45,   100,   348,    35,
      87,    45,    98,    45,   132,  -145,  -145,   398,    20,   109,
    -145,   160,  -145,    45,   152,    35,  -145,  -145,  -145,  -145,
    -145,  -145,   116,  -145,  -145,   190,   112,     4,  -145,    75,
    -145,  -145,   241,   199,  -145,   149,  -145,   179,   148,   200,
     151,   361,   202,   203,   361,  -145,   398,   357,   -26,   205,
       3,   162,    35,    18,  -145,    94,  -145,   204,   186,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,    45,    45,  -145,
    -145,    45,  -145,    35,    35,    35,  -145,    45,   208,    35,
      35,   189,   201,   218,    45,    35,   224,   223,   192,   209,
     108,  -145,   357,   398,   220,   222,  -145,    96,   245,  -145,
      35,  -145,    45,   100,     4,     4,    75,  -145,  -145,  -145,
     176,  -145,  -145,   240,   100,   239,  -145,   -14,  -145,   361,
     166,   261,  -145,   193,   235,  -145,   196,  -145,   249,  -145,
     266,  -145,  -145,  -145,  -145,  -145,  -145,  -145,    35,  -145,
     172,   263,     8,    35,   274,    24,   275,  -145,  -145,  -145,
     279,  -145,    -8,   357,   280,  -145,   264,   107,  -145,  -145,
    -145,   242,  -145,   100,  -145,  -145,  -145,  -145,   288,   100,
    -145,   357,   268,  -145,   222,  -145,    35,   289,   293,   300,
     273,  -145,  -145,   301,  -145,   100,   297,  -145,   283,   311,
     251,   100,   306,  -145,   345,  -145,  -145
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,   305,   -64,   -21,   -12,  -145,    82,    42,  -145,
    -145,  -145,   -54,  -144,  -145,   175,   147,  -145,  -145,   285,
    -145,  -145,  -145,   -23,  -145,  -145,   165,   -51,  -145,    71,
    -145,   -75,   210,   -57,  -145,  -145,  -145,  -145,  -106
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -105
static const yytype_int16 yytable[] =
{
      47,    20,    96,    92,   108,    86,   157,    52,   188,   175,
      98,   152,   132,   104,    63,   220,   154,     1,   114,    76,
       6,    78,   111,   158,    11,    19,    47,   155,   106,   231,
     159,     3,    47,     4,   206,    16,   163,     5,    73,    76,
     224,    78,   225,   207,     7,    10,   105,    15,    73,    24,
      76,    77,    78,    79,    12,   114,    74,   107,    75,     7,
      76,    77,    78,    79,    80,   129,   130,    49,    25,   232,
      12,    12,    12,    26,    80,    29,   167,   168,   169,    64,
      55,    50,   172,   173,   151,   148,   170,   240,    96,   132,
     132,    21,   217,   179,    22,    81,    20,    82,    53,   160,
      12,   160,   226,   199,    54,    81,    56,    82,   161,   201,
     197,    57,   160,    83,    84,    85,   118,    68,    69,   212,
     204,   235,    59,    83,    84,    85,    67,   187,    21,   151,
     227,    28,   189,    60,    39,    73,    40,   119,   133,   134,
     135,   114,    61,    74,    42,    75,   221,    76,    77,    78,
      79,    70,   141,   138,   139,   143,   144,    43,    62,   120,
      71,    80,   186,    44,    45,   112,   156,    97,   102,   237,
     210,   139,   103,   119,   110,   239,   218,   144,    99,   243,
     202,   121,   122,   123,   124,   125,   126,   119,    46,   109,
     151,   249,    81,  -104,    82,   120,   116,   254,   164,   165,
      20,   119,   137,   140,   142,   145,   146,   162,   151,   120,
      83,    84,    85,   153,   163,   171,   174,   121,   122,   123,
     124,   125,   126,   120,   175,   178,    38,    72,   181,   -51,
     182,   121,   122,   123,   124,   125,   126,    38,   190,   185,
      38,    39,   205,    40,   191,   121,   122,   123,   124,   125,
     126,    42,    39,   136,    40,    39,    41,    40,   198,    66,
     203,   192,    42,   193,    43,    42,   194,    39,   211,    40,
      44,    45,   213,    12,   195,    43,   214,    42,    43,   215,
     216,    44,    45,   229,    44,    45,   230,   233,   234,    39,
      43,    40,   238,   236,   219,    46,    44,    45,   241,    42,
      39,   245,    40,   247,   250,   248,    46,   222,   253,    46,
      42,   251,    43,   255,    17,    39,   242,    40,    44,    45,
     180,    46,   244,    43,   208,    42,    39,   200,    40,    44,
      45,     0,   223,    65,     0,     0,    42,    39,    43,    40,
       0,   166,     0,    46,    44,    45,     0,    42,     0,    43,
     246,     0,     0,     0,    46,    44,    45,     0,     0,     0,
      43,   252,     0,     0,     0,     0,    44,    45,     0,    46,
       0,    39,     0,    40,    93,     0,    40,   256,     0,     0,
      46,    42,     0,    39,    42,    40,   119,     0,     0,     0,
       0,    46,     0,    42,    43,     0,     0,    43,     0,     0,
      44,    45,     0,    44,    45,     0,    43,     0,   120,     0,
       0,     0,    44,    45,     0,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,    46,     0,     0,    46,     0,
     121,   122,   123,   124,   125,   126,    31,    46,     0,     0,
      32,    33,     0,    34,     0,     0,     0,     0,     0,     0,
       0,    35
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-145))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      23,    13,    59,    57,    68,    56,   112,    28,   152,    23,
      61,    37,    87,    64,     3,     7,    13,    19,    75,    15,
      35,    17,    73,     5,    34,    34,    49,    24,     8,    37,
      12,    80,    55,     0,    48,    35,    28,     7,     3,    15,
      16,    17,    18,    57,    59,    80,    67,    37,     3,    80,
      15,    16,    17,    18,    80,   112,    11,    37,    13,    59,
      15,    16,    17,    18,    29,    61,    62,    25,    37,   213,
      80,    80,    80,     3,    29,    80,   133,   134,   135,    68,
      38,    80,   139,   140,   107,   106,   137,   231,   145,   164,
     165,     5,   198,   144,     8,    60,   108,    62,    13,     5,
      80,     5,    78,   160,     7,    60,     3,    62,    14,   163,
      14,    11,     5,    78,    79,    80,     4,     4,     5,   183,
     174,    14,     3,    78,    79,    80,     8,   150,     5,   152,
     205,     8,   153,     3,    26,     3,    28,    25,    63,    64,
      65,   198,     3,    11,    36,    13,   203,    15,    16,    17,
      18,     7,     4,     4,     5,     4,     5,    49,     3,    47,
      18,    29,    54,    55,    56,    13,     4,    80,    36,   223,
       4,     5,    40,    25,    14,   229,     4,     5,    80,   236,
       4,    69,    70,    71,    72,    73,    74,    25,    80,    80,
     213,   245,    60,     3,    62,    47,    80,   251,   127,   128,
     212,    25,     3,    24,     4,     3,     3,     3,   231,    47,
      78,    79,    80,     8,    28,     7,    27,    69,    70,    71,
      72,    73,    74,    47,    23,     7,    11,    12,     4,    37,
       7,    69,    70,    71,    72,    73,    74,    11,    18,    30,
      11,    26,     3,    28,    22,    69,    70,    71,    72,    73,
      74,    36,    26,    12,    28,    26,    30,    28,    13,    30,
      20,    39,    36,    41,    49,    36,    44,    26,     7,    28,
      55,    56,    37,    80,    52,    49,    80,    36,    49,    30,
      14,    55,    56,     8,    55,    56,     7,     7,    24,    26,
      49,    28,     4,    51,    31,    80,    55,    56,    30,    36,
      26,     8,    28,    30,     7,     4,    80,    33,    57,    80,
      36,    28,    49,     7,     9,    26,   234,    28,    55,    56,
     145,    80,    33,    49,   177,    36,    26,   162,    28,    55,
      56,    -1,    58,    48,    -1,    -1,    36,    26,    49,    28,
      -1,   131,    -1,    80,    55,    56,    -1,    36,    -1,    49,
      50,    -1,    -1,    -1,    80,    55,    56,    -1,    -1,    -1,
      49,    50,    -1,    -1,    -1,    -1,    55,    56,    -1,    80,
      -1,    26,    -1,    28,    26,    -1,    28,    32,    -1,    -1,
      80,    36,    -1,    26,    36,    28,    25,    -1,    -1,    -1,
      -1,    80,    -1,    36,    49,    -1,    -1,    49,    -1,    -1,
      55,    56,    -1,    55,    56,    -1,    49,    -1,    47,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    80,    -1,
      69,    70,    71,    72,    73,    74,    38,    80,    -1,    -1,
      42,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53
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
       3,     3,     3,     3,    68,   100,    30,     8,     4,     5,
       7,    18,    12,     3,    11,    13,    15,    16,    17,    18,
      29,    60,    62,    78,    79,    80,   108,   110,   112,   113,
     114,   117,    93,    26,   104,    96,   114,    80,   108,    80,
     107,   108,    36,    40,   108,    85,     8,    37,    84,    80,
      14,   108,    13,   118,   114,   119,    80,   115,     4,    25,
      47,    69,    70,    71,    72,    73,    74,   106,   109,    61,
      62,   111,   112,    63,    64,    65,    12,     3,     4,     5,
      24,     4,     4,     4,     5,     3,     3,   105,    85,    94,
      95,   104,    37,     8,    13,    24,     4,   119,     5,    12,
       5,    14,     3,    28,   110,   110,   113,   114,   114,   114,
     108,     7,   114,   114,    27,    23,    97,    99,     7,   108,
      96,     4,     7,   101,   102,    30,    54,   104,    94,    85,
      18,    22,    39,    41,    44,    52,    88,    14,    13,   114,
     107,    93,     4,    20,    93,     3,    48,    57,    97,    98,
       4,     7,    84,    37,    80,    30,    14,   119,     4,    31,
       7,   114,    33,    58,    16,    18,    78,   112,   116,     8,
       7,    37,    94,     7,    24,    14,    51,    93,     4,    93,
      94,    30,    88,   114,    33,     8,    50,    30,     4,    93,
       7,    28,    50,    57,    93,     7,    32
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
  verifyUsed(hashVariables);
}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 120 "compiler.y"
    {
  verifyUsed(hashVariables);
}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 128 "compiler.y"
    {
    if(strcmp(currentScope, "main")==0)
    {
      char *varName;
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
	  printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
	  exit(1);
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
	variable* newVar = createVariable();
	int intVarType = convertType(type);
	setVariable(newVar, auxVariable, currentScope, intVarType);
	if(lookupStringVariable(hashVariables, auxVariable)==NULL)
	  addInfoVariable(hashVariables, auxVariable, newVar);
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
#line 173 "compiler.y"
    {
    if(strcmp(currentScope, "main")==0)
    {
      char *varName;
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
	  printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
	  exit(1);
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
	variable* newVar = createVariable();
	int intVarType = convertType(type);
	setVariable(newVar, auxVariable, currentScope, intVarType);
	if(lookupStringVariable(hashVariables, auxVariable)==NULL)
	  addInfoVariable(hashVariables, auxVariable, newVar);
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
#line 237 "compiler.y"
    {
    currentParameters = startList();
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, 0, 0, NULL, 0, NULL, 0);
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
#line 254 "compiler.y"
    {
  List *functionParameter = currentParameters;
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

  case 29:

/* Line 1806 of yacc.c  */
#line 266 "compiler.y"
    {
    currentParameters = startList();
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, 0, 0, NULL, 0, NULL, 0);
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
#line 283 "compiler.y"
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
#line 311 "compiler.y"
    {
  List *aux = lookupStringFunction(hashFunction, currentScope);
  ((function*)(aux->info))->returnType = convertType(type); //A variavel type sempre e retornada no .l
}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 320 "compiler.y"
    {
  List *aux = lookupStringFunction(hashFunction, currentScope);
  ((function*)(aux->info))->returnType = convertType(type); //A variavel type sempre e retornada no .l
}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 328 "compiler.y"
    {
    currentFunctionArity++;
    char *varName;
    strcat(currentIdentifier, " ");
    strcat(currentIdentifier, currentScope);
    varName = strtok(currentIdentifier, "");
    if(lookupStringVariable(hashVariables, varName)==NULL)
    {
      variable* newVar = createVariable();
      int intVarType = convertType(type);
      setVariable(newVar, varName, currentScope, intVarType);
      addInfoVariable(hashVariables, varName, newVar);
      currentParameters = insertList(currentParameters, (void*)intVarType);
    }
    else
    {
      printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
    }
    
  strcpy(identifiers, "\0");
}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 351 "compiler.y"
    {
    currentFunctionArity++;
    char *varName;
    char varAux[100];
    strcpy(varAux,currentIdentifier);
    strcat(currentIdentifier, " ");
    strcat(currentIdentifier, currentScope);
    varName = strtok(currentIdentifier, "");
    if(lookupStringVariable(hashVariables, varName)==NULL)
    {
      variable* newVar = createVariable();
      int intVarType = convertType(type);
      setVariable(newVar, varName, currentScope, intVarType);
      addInfoVariable(hashVariables, varName, newVar);
      currentParameters = insertList(currentParameters, (void*)intVarType);
    }
    else
    {
      printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varAux);
    }
    
  strcpy(identifiers, "\0");
}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 384 "compiler.y"
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
      else
      {
	((variable*)(identifier_temp->info))->used=1;
      }
      strcpy(identifiers, "\0");
      if(!verifyRelationship(varRelations, currentRelationPos))
      {
	printf("Valores incompativeis na linha %d.\n", nLine);
      }
      else
      {
	List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
	if(identifier_temp == NULL)
	{
	  printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
	}
	else if(((variable*)(identifier_temp->info))->type != varRelations[0])
	{
	  printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  printf("Tipo da varivel: %d -> Tipo da expressao: %d.\n",((variable*)(identifier_temp->info))->type, varRelations[0]);
	}
      }
      currentRelationPos = 0;
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
}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 519 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("real com sinal\n");
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 526 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("inteiro com sinal\n");

}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 536 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("inteiro sem sinal\n");
}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 543 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("real sem sinal\n");
}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 550 "compiler.y"
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
      printf("Variavel %s nao declarada na linha %d\n",auxVariable, nLine);
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

  case 98:

/* Line 1806 of yacc.c  */
#line 591 "compiler.y"
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
      printf("Variavel %s nao declarada na linha %d\n",auxVariable, nLine);
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

  case 99:

/* Line 1806 of yacc.c  */
#line 632 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 638 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 645 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 651 "compiler.y"
    {
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 657 "compiler.y"
    {
  strcpy(currentFunction, currentIdentifier);
  in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments.
}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 662 "compiler.y"
    { 
  List *identifier_temp = lookupStringFunction(hashFunction, currentFunction);
  if(identifier_temp == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
  }
  else
  {
    List* parametersList = startList();
    char *argumentAux;
    argumentAux = strtok(functionArguments, " ");
    int flagOut = 0;
    while(argumentAux != NULL)
    {
      int type = convertFunctionArgument(argumentAux, hashVariables, nLine); //Caso seja variavel, ira buscar na tabela hash equivalente o tipo, assim como se a variavel foi inicializada para uso dentro da funcao.
      if(type==5)
      {
	printf("Variavel %s nao declarada na funcao %s na linha %d.\n", argumentAux, currentFunction, nLine); 
	flagOut = 1;
      }
      parametersList = insertList(parametersList,(void*) type);
      argumentAux = strtok(NULL, " ");
    }
   if(!flagOut)
   {
    //Se tipo 5 foi encontrado, houve erro de variavel nao declarada ou nao utilizada, entao nem iremos comparar a funcao com a da tabela hash.
      int arity = countList(parametersList);
      if(arity != ((function*)(identifier_temp->info))->arity)
	printf("Aridade da funcao %s esta errada na linha %d.\n", currentFunction, nLine);
   }
  }
  strcpy(functionArguments, "\0");
}
    break;



/* Line 1806 of yacc.c  */
#line 2353 "compiler.tab.c"
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
#line 703 "compiler.y"


#include "lex.yy.c"

main(){
      hashVariables = createHash(MAX_HASH);
      hashFunction = createHash(MAX_HASH);
      yyparse();
	
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void){
	printf("Erro na Linha: %d\n", nLine);
}



