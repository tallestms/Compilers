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
#include "tree.h"
#include "stack.h"

#define MAX_HASH 1000
#define MAX_VARIABLE 32 //maior nome de variavel
#define MAX_FUNCTION 32 //maior nome de funcao
#define MAX_LITERAL 203
#define IN_DEBUG_MODE 1

extern char* yytext;
extern int in_function;
extern int in_logico;
extern int in_comparacao;
extern int in_condicional;
extern int nLine;
extern char identifiers[10*MAX_VARIABLE];
extern char functionArguments[10*MAX_VARIABLE];
extern char currentType[10];
extern char currentIdentifier[MAX_VARIABLE];
extern int varRelations[50]; //Vetor que armazena relacoes de uma dada expressao
extern int currentNumber;
char currentVariable[MAX_VARIABLE + MAX_FUNCTION + 2];
char currentScope[MAX_FUNCTION] = "main";
char currentFunction[MAX_FUNCTION];
int currentFunctionArity = 0;
int currentRelationPos = 0;
int currentRelationComparison = 0;
char returnFunctionType[10];
int switchType;
int countLine = 0;
int countColumn = 0;
int typeAttribute;
extern int isMatrix;
int dimension, dim1, dim2;
List* currentParameters = NULL;
hashTable* hashVariables = NULL;
hashTable* hashFunction = NULL;
char limitString[203]; //limitador de tamanho de string no programa

Stack* stackGlobal = NULL;
Stack* stackIfThenElse = NULL;

treeNode* globalTree = NULL;
treeNode* expressionNode = NULL;
treeNode* attributionNode = NULL;
treeNode* conditionNode = NULL;
treeNode* commandNode = NULL;
treeNode* caseNode = NULL;

//Adiciona no no stack global que ficara responsavel para controlar escopo dentro do programa
Stack* addNodeIntoStack(treeNode *info, Stack* aux){
	if(aux==NULL){

		aux = createStack();
		pushStack(aux, (void*)info);
		return aux;
	}else{
		pushStack(aux, (void*)info);
		return aux;
	}
}

treeNode* swapUmZero = NULL;
treeNode* swapDoisUm = NULL;
treeNode* swapTresDois = NULL;
/**
*	FUNÇÕES
**/
void addAttributionNodeIntoGlobalTree(){
	if(globalTree==NULL){
		globalTree = attributionNode;
	}else{
		treeNode *aux = globalTree;
		while(aux->next!=NULL) aux = aux->next;
		aux->next = attributionNode;
	}
	attributionNode = NULL;	
}

void addConditionNodeIntoGlobalTree(){
	if(globalTree==NULL){
		globalTree = conditionNode;
	}else{
		treeNode *aux = globalTree;
		while(aux->next!=NULL) aux = aux->next;
		aux->next = conditionNode;
	}
}

void operadorDeNivelTres(){
	treeNode *aux = newTreeNode();
	fillTreeNode(aux, yytext,"OPERADOR-N-3");
	aux->children[0] = expressionNode;
	expressionNode = aux;
}

void operadorDeNivelDois(char tipo[10]){
	if(!strcmp(expressionNode->type,"OPERADOR-N-3")){
		swapTresDois = expressionNode;
		treeNode *aux = newTreeNode();
		fillTreeNode(aux, tipo,"OPERADOR-N-2");
		aux->children[0] = expressionNode->children[1];
		expressionNode->children[1] = aux;
		expressionNode = aux;
	} else {
		treeNode *aux = newTreeNode();
		fillTreeNode(aux, tipo,"OPERADOR-N-2");
		aux->children[0] = expressionNode;
		expressionNode = aux;
	}
}

void operadorDeNivelUm(){
	if(!strcmp(expressionNode->type,"OPERADOR-N-2") || !strcmp(expressionNode->type,"OPERADOR-N-3")){
		swapDoisUm = expressionNode;
		treeNode *aux = newTreeNode();
		fillTreeNode(aux, yytext, "OPERADOR-N-1");
		aux->children[0] = expressionNode->children[1];
		expressionNode->children[1] = aux;
		expressionNode = aux;
	}else{
		treeNode *aux = newTreeNode();
		fillTreeNode(aux,yytext,"OPERADOR-N-1");
		aux->children[0]=expressionNode;
		expressionNode = aux;
	}
}

void operadorDeNivelZero(char tipo[10]){
	if (!strcmp(expressionNode->type,"OPERADOR-N-1") || !strcmp(expressionNode->type,"OPERADOR-N-2") || !strcmp(expressionNode->type,"OPERADOR-N-3")){
		swapUmZero = expressionNode;
		treeNode *aux = newTreeNode();
		fillTreeNode(aux, tipo, "OPERADOR-N-0");
		aux->children[0] = expressionNode->children[1];
		expressionNode->children[1] = aux;
		expressionNode = aux;
	}else{
		treeNode *aux = newTreeNode();
		fillTreeNode(aux, tipo, "OPERADOR-N-0");
		aux->children[0] = expressionNode;
		expressionNode = aux;
	}
}

void swapoutUmZero(){
	if (swapUmZero!=NULL){
		expressionNode = swapUmZero;
		swapUmZero=NULL;
	}
}

void swapoutDoisUm(){
	if (swapDoisUm!=NULL){
		expressionNode = swapDoisUm;
		swapDoisUm=NULL;
	}
}

void swapoutTresDois(){
	if (swapTresDois!=NULL){
		expressionNode = swapTresDois;
		swapTresDois=NULL;
	}
}




/* Line 268 of yacc.c  */
#line 248 "compiler.tab.c"

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
     token_fimenquanto = 286,
     token_fimpara = 287,
     token_fimse = 288,
     token_fimvariaveis = 289,
     token_funcao = 290,
     token_imprima = 291,
     token_imprimaln = 292,
     token_inicio = 293,
     token_inteiro = 294,
     token_inteiros = 295,
     token_leia = 296,
     token_leialn = 297,
     token_literais = 298,
     token_literal = 299,
     token_logico = 300,
     token_logicos = 301,
     token_matriz = 302,
     token_minimo = 303,
     token_nao = 304,
     token_ou = 305,
     token_padrao = 306,
     token_para = 307,
     token_parar = 308,
     token_passo = 309,
     token_reais = 310,
     token_real = 311,
     token_retorne = 312,
     token_se = 313,
     token_seleciona = 314,
     token_fimseleciona = 315,
     token_senao = 316,
     token_variaveis = 317,
     token_verdadeiro = 318,
     token_mais = 319,
     token_menos = 320,
     token_vezes = 321,
     token_dividir = 322,
     token_mod = 323,
     token_maismais = 324,
     token_menosmenos = 325,
     token_atribuicao = 326,
     token_maior = 327,
     token_menor = 328,
     token_maiori = 329,
     token_menori = 330,
     token_igual = 331,
     token_diferente = 332,
     token_el = 333,
     token_oul = 334,
     token_negacao = 335,
     token_variavel_caracter = 336,
     token_string = 337,
     token_identificador = 338
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
#line 373 "compiler.tab.c"

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
#define YYLAST   395

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  103
/* YYNRULES -- Number of rules.  */
#define YYNRULES  183
/* YYNRULES -- Number of states.  */
#define YYNSTATES  347

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   338

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
      75,    76,    77,    78,    79,    80,    81,    82,    83
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
     125,   130,   131,   137,   138,   140,   142,   145,   147,   148,
     152,   155,   162,   164,   173,   180,   187,   195,   196,   207,
     208,   218,   222,   228,   229,   235,   241,   242,   249,   250,
     257,   258,   259,   267,   268,   269,   279,   280,   281,   282,
     296,   297,   298,   305,   306,   307,   308,   309,   321,   322,
     323,   324,   325,   338,   339,   340,   341,   342,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   384,   385,   386,
     387,   396,   397,   398,   404,   406,   407,   408,   412,   413,
     414,   418,   420,   424,   425,   427,   428,   433,   434,   439,
     441,   443,   445,   447,   449,   451,   453,   454,   459,   462,
     464,   466,   468,   470,   472,   474,   475,   480,   481,   486,
     487,   492,   494,   496,   498,   500,   503,   508,   509,   518,
     520,   522,   526,   528,   530,   531,   537,   539,   541,   543,
     545,   546,   547,   553,   554,   555,   561,   562,   563,   571,
     572,   573,   579,   581
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      85,     0,    -1,    -1,    19,    83,     7,    86,    98,    88,
      38,    97,    30,    -1,    -1,    19,    83,     7,    87,    88,
      38,    97,    30,    -1,    62,    89,    34,    -1,    62,    34,
      -1,    -1,    91,     8,    90,     7,    -1,    89,    91,     8,
      90,     7,    -1,    39,    -1,    56,    -1,    21,    -1,    44,
      -1,    45,    -1,    92,    -1,    83,    -1,    91,     5,    83,
      -1,    -1,    -1,    47,    13,    18,    14,    13,    93,    18,
      94,    14,    24,    96,    -1,    -1,    47,    13,    18,    14,
      24,    95,    96,    -1,    40,    -1,    22,    -1,    43,    -1,
      55,    -1,    46,    -1,    -1,    97,   116,    -1,    97,    11,
      97,    12,    -1,    -1,    98,    35,    83,    99,   112,    -1,
      -1,    35,    83,   100,   112,    -1,    -1,   101,   116,    -1,
      11,   101,    12,    -1,    -1,    57,    83,   103,     7,    -1,
      -1,   106,    57,    83,   104,     7,    -1,    -1,   106,    -1,
     116,    -1,   106,   116,    -1,   172,    -1,    -1,   111,   109,
     108,    -1,   111,   110,    -1,    51,     8,   101,    53,     7,
      60,    -1,    60,    -1,    23,     3,   175,     4,     8,   101,
      53,     7,    -1,    23,     3,   175,     4,     8,   101,    -1,
       3,   115,     4,    38,   105,    30,    -1,     3,   115,     4,
      89,    38,   105,    30,    -1,    -1,     3,   115,     4,     8,
      90,   113,    89,    38,   102,    30,    -1,    -1,     3,   115,
       4,     8,    90,   114,    38,   105,    30,    -1,    83,     8,
      90,    -1,   115,     5,    83,     8,    90,    -1,    -1,    36,
       3,   107,     4,     7,    -1,    37,     3,   107,     4,     7,
      -1,    -1,    41,     3,    83,   117,     4,     7,    -1,    -1,
      42,     3,    83,   118,     4,     7,    -1,    -1,    -1,    83,
     119,     3,   159,     4,   120,     7,    -1,    -1,    -1,    83,
      13,    18,    14,    71,   121,   160,   122,     7,    -1,    -1,
      -1,    -1,    83,    13,    18,    14,    13,   123,    18,   124,
      14,    71,   160,   125,     7,    -1,    -1,    -1,    83,    71,
     126,   160,   127,     7,    -1,    -1,    -1,    -1,    -1,    58,
     128,     3,   160,   129,     4,   130,    27,   101,   131,   151,
      -1,    -1,    -1,    -1,    -1,    28,   132,   101,   133,     7,
      26,     3,   160,   134,     4,   135,     7,    -1,    -1,    -1,
      -1,    -1,    26,     3,   136,   160,   137,     4,   138,    28,
     101,   139,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,   140,     3,   141,    83,   142,    24,   172,
     143,    20,   172,   144,    54,   172,   145,     4,   146,    28,
     101,   147,    32,    -1,    -1,    -1,    -1,    59,   148,     3,
      83,   149,     4,   150,   108,    -1,    -1,    -1,    61,   152,
     101,   153,    33,    -1,    33,    -1,    -1,    -1,   155,   156,
      25,    -1,    -1,    -1,   157,   158,    50,    -1,   160,    -1,
     159,     5,   160,    -1,    -1,   164,    -1,    -1,   160,   163,
     164,   161,    -1,    -1,   160,   154,   162,   164,    -1,    72,
      -1,    74,    -1,    76,    -1,    73,    -1,    75,    -1,    77,
      -1,   168,    -1,    -1,   164,   166,   165,   168,    -1,   164,
     167,    -1,    64,    -1,    65,    -1,    15,    -1,    17,    -1,
     176,    -1,   172,    -1,    -1,   168,    67,   169,   172,    -1,
      -1,   168,    68,   170,   172,    -1,    -1,   168,    66,   171,
     172,    -1,   167,    -1,    18,    -1,    16,    -1,    83,    -1,
      65,    83,    -1,    83,    13,    18,    14,    -1,    -1,    83,
      13,    18,    14,    13,   173,    18,    14,    -1,    81,    -1,
      82,    -1,     3,   160,     4,    -1,    63,    -1,    29,    -1,
      -1,    83,   174,     3,   159,     4,    -1,   167,    -1,    18,
      -1,    16,    -1,    81,    -1,    -1,    -1,    11,   177,   181,
     178,    12,    -1,    -1,    -1,    13,   179,   186,   180,    14,
      -1,    -1,    -1,   181,     5,    13,   182,   186,   183,    14,
      -1,    -1,    -1,    13,   184,   186,   185,    14,    -1,   172,
      -1,   186,     5,   172,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   262,   262,   262,   270,   269,   276,   277,   277,   279,
     331,   382,   382,   382,   382,   382,   382,   384,   384,   386,
     386,   386,   387,   387,   388,   388,   388,   388,   388,   390,
     390,   390,   392,   391,   423,   422,   452,   452,   452,   454,
     453,   481,   480,   508,   508,   509,   509,   511,   513,   512,
     518,   522,   523,   524,   524,   526,   527,   529,   528,   539,
     537,   546,   570,   594,   602,   603,   605,   604,   619,   618,
     633,   641,   632,   752,   783,   752,   798,   822,   829,   798,
     845,   872,   844,   979,   991,  1005,  1006,   978,  1015,  1026,
    1033,  1044,  1014,  1046,  1054,  1071,  1074,  1045,  1086,  1092,
    1093,  1104,  1110,  1115,  1131,  1140,  1085,  1148,  1149,  1223,
    1148,  1232,  1246,  1231,  1252,  1255,  1256,  1255,  1283,  1284,
    1283,  1311,  1311,  1311,  1312,  1314,  1314,  1336,  1336,  1338,
    1339,  1340,  1341,  1342,  1343,  1346,  1347,  1347,  1348,  1349,
    1349,  1351,  1399,  1444,  1444,  1446,  1446,  1448,  1448,  1450,
    1450,  1451,  1452,  1473,  1495,  1571,  1626,  1674,  1673,  1744,
    1755,  1772,  1773,  1793,  1814,  1813,  2019,  2019,  2026,  2033,
    2040,  2040,  2040,  2062,  2062,  2062,  2084,  2085,  2084,  2103,
    2103,  2102,  2122,  2140
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
  "token_faca", "token_falso", "token_fim", "token_fimenquanto",
  "token_fimpara", "token_fimse", "token_fimvariaveis", "token_funcao",
  "token_imprima", "token_imprimaln", "token_inicio", "token_inteiro",
  "token_inteiros", "token_leia", "token_leialn", "token_literais",
  "token_literal", "token_logico", "token_logicos", "token_matriz",
  "token_minimo", "token_nao", "token_ou", "token_padrao", "token_para",
  "token_parar", "token_passo", "token_reais", "token_real",
  "token_retorne", "token_se", "token_seleciona", "token_fimseleciona",
  "token_senao", "token_variaveis", "token_verdadeiro", "token_mais",
  "token_menos", "token_vezes", "token_dividir", "token_mod",
  "token_maismais", "token_menosmenos", "token_atribuicao", "token_maior",
  "token_menor", "token_maiori", "token_menori", "token_igual",
  "token_diferente", "token_el", "token_oul", "token_negacao",
  "token_variavel_caracter", "token_string", "token_identificador",
  "$accept", "PROG", "$@1", "$@2", "BLOCO_VARIAVEIS", "VARIAVEIS",
  "TIPOS_VARIAVEIS", "VARIAVEIS_IDENTIFICADORES", "INICIALIZAR_MATRIZ",
  "$@3", "$@4", "$@5", "TIPOS_VARIAVEIS_MATRIZ", "BLOCO", "BLOCO_FUNCOES",
  "$@6", "$@7", "BLOCO_AUXILIAR", "BLOCO_FUNCAO_RETORNO", "$@8", "$@9",
  "BLOCO_FUNCAO", "REPETICAO_COMANDO", "BLOCO_IMPRIMA", "BLOCO_SWITCH",
  "$@10", "FIM_BLOCO_SWITCH", "BLOCO_SWITCH_AUX", "FUNCAO", "$@11", "$@12",
  "VARIAVEIS_FUNCAO", "COMANDO", "$@13", "$@14", "$@15", "$@16", "$@17",
  "$@18", "$@19", "$@20", "$@21", "$@22", "$@23", "$@24", "$@25", "$@26",
  "$@27", "$@28", "$@29", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35",
  "$@36", "$@37", "$@38", "$@39", "$@40", "$@41", "$@42", "$@43", "$@44",
  "$@45", "$@46", "BLOCO_SENAO_FIMSE", "$@47", "$@48", "LOGICOS", "$@49",
  "$@50", "$@51", "$@52", "ARGUMENTOS_FUNCAO", "EXPR", "$@53", "$@54",
  "COMPARACOES", "SIEXPR", "$@55", "ADICAO_SUBTRACAO", "SINALFATOR",
  "TERMO", "$@56", "$@57", "$@58", "FATOR", "$@59", "$@60", "FATOR_CASE",
  "MATRIZ", "$@61", "$@62", "$@63", "$@64", "MATRIZ_VARIAS_COLUNAS",
  "$@65", "$@66", "$@67", "$@68", "BLOCO_MATRIZ", 0
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
     335,   336,   337,   338
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    86,    85,    87,    85,    88,    88,    88,    89,
      89,    90,    90,    90,    90,    90,    90,    91,    91,    93,
      94,    92,    95,    92,    96,    96,    96,    96,    96,    97,
      97,    97,    99,    98,   100,    98,   101,   101,   101,   103,
     102,   104,   102,   105,   105,   106,   106,   107,   109,   108,
     108,   110,   110,   111,   111,   112,   112,   113,   112,   114,
     112,   115,   115,   115,   116,   116,   117,   116,   118,   116,
     119,   120,   116,   121,   122,   116,   123,   124,   125,   116,
     126,   127,   116,   128,   129,   130,   131,   116,   132,   133,
     134,   135,   116,   136,   137,   138,   139,   116,   140,   141,
     142,   143,   144,   145,   146,   147,   116,   148,   149,   150,
     116,   152,   153,   151,   151,   155,   156,   154,   157,   158,
     154,   159,   159,   159,   160,   161,   160,   162,   160,   163,
     163,   163,   163,   163,   163,   164,   165,   164,   164,   166,
     166,   167,   167,   168,   168,   169,   168,   170,   168,   171,
     168,   172,   172,   172,   172,   172,   172,   173,   172,   172,
     172,   172,   172,   172,   174,   172,   175,   175,   175,   175,
     177,   178,   176,   179,   180,   176,   182,   183,   181,   184,
     185,   181,   186,   186
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     8,     3,     2,     0,     4,
       5,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       0,    11,     0,     7,     1,     1,     1,     1,     1,     0,
       2,     4,     0,     5,     0,     4,     0,     2,     3,     0,
       4,     0,     5,     0,     1,     1,     2,     1,     0,     3,
       2,     6,     1,     8,     6,     6,     7,     0,    10,     0,
       9,     3,     5,     0,     5,     5,     0,     6,     0,     6,
       0,     0,     7,     0,     0,     9,     0,     0,     0,    13,
       0,     0,     6,     0,     0,     0,     0,    11,     0,     0,
       0,     0,    12,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     0,     0,     0,
       8,     0,     0,     5,     1,     0,     0,     3,     0,     0,
       3,     1,     3,     0,     1,     0,     4,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     2,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     2,     4,     0,     8,     1,
       1,     3,     1,     1,     0,     5,     1,     1,     1,     1,
       0,     0,     5,     0,     0,     5,     0,     0,     7,     0,
       0,     5,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     8,     0,     8,
       0,     0,    34,     0,     0,     7,    17,     0,     0,    29,
       0,    32,    29,     6,     0,     0,     0,     0,    63,    35,
       0,     0,     0,    18,    13,    11,    14,    15,     0,    12,
       0,    16,    29,     0,    88,     5,     0,     0,     0,     0,
      98,    83,   107,    70,    30,     0,     0,    33,     3,     0,
       0,     9,     0,    93,    36,     0,     0,     0,     0,     0,
       0,     0,     0,    80,     0,     0,     0,     0,    10,     0,
      31,     0,    36,    89,     0,   141,   153,   142,   152,   163,
     162,     0,   159,   160,   154,     0,   151,    47,     0,    66,
      68,    99,     0,     0,     0,     0,   123,    61,     0,    43,
       0,     0,     0,   170,   173,    94,   124,   135,   144,   143,
       0,    37,     0,   115,   155,     0,     0,     0,     0,     0,
       0,     0,    84,   108,     0,    81,     0,   121,    57,     0,
      44,    45,    43,     0,    19,    22,     0,     0,   129,   132,
     130,   133,   131,   134,     0,   127,   116,   119,     0,   139,
     140,   136,   138,   149,   145,   147,    38,     0,   161,     0,
     123,    64,    65,     0,     0,   100,     0,     0,    76,    73,
       0,    71,     0,     0,     0,    55,    46,     0,    62,     0,
       0,   179,   171,   182,   174,    95,     0,     0,     0,   125,
       0,     0,     0,     0,     0,   156,     0,    67,    69,     0,
      85,   109,     0,     0,    82,     0,   122,     0,    43,    56,
      20,    25,    24,    26,    28,    27,    23,     0,     0,     0,
       0,     0,     0,   128,   117,   120,   126,   137,   150,   146,
     148,     0,   157,   165,     0,     0,     0,    77,    74,    72,
       0,     0,     0,   180,   176,   172,   183,   175,    36,    90,
       0,   101,    36,     0,   110,    48,     0,     0,     0,     0,
       0,    60,     0,     0,     0,    96,     0,     0,     0,    86,
       0,     0,    52,     0,    50,     0,    75,    39,    58,     0,
       0,   181,   177,     0,    91,   158,     0,     0,   168,   167,
     169,   166,     0,    36,    49,     0,     0,    41,    21,     0,
      97,     0,   102,   114,   111,    87,     0,     0,    78,    40,
       0,   178,    92,     0,    36,    36,     0,     0,    42,     0,
     112,    54,     0,    79,   103,     0,     0,    51,     0,   113,
      53,   104,     0,    36,   105,     0,   106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     7,    11,    17,    40,    18,    41,   189,
     252,   190,   226,    27,     9,    30,    20,    83,   269,   306,
     320,   139,   140,    95,   264,   283,   284,   265,    29,   183,
     184,    56,   121,   129,   130,    74,   215,   213,   267,   212,
     266,   327,   105,   180,    70,   176,   245,   297,    64,   122,
     276,   311,    81,   154,   232,   293,    69,   131,   209,   278,
     323,   338,   342,   345,    71,   177,   246,   315,   324,   335,
     155,   156,   197,   157,   198,   136,   137,   236,   196,   158,
     116,   200,   161,    96,   117,   202,   203,   201,   118,   260,
     126,   302,   119,   146,   229,   147,   231,   192,   274,   309,
     227,   273,   194
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -181
static const yytype_int16 yypact[] =
{
      25,   -37,    54,    49,  -181,    31,    37,    17,    -9,    -1,
      -3,    51,  -181,    13,    66,  -181,  -181,     1,    47,  -181,
     103,  -181,  -181,  -181,    60,    34,   168,   115,    36,  -181,
     103,   118,   168,  -181,  -181,  -181,  -181,  -181,   107,  -181,
     132,  -181,  -181,   139,  -181,  -181,   150,   155,   158,   160,
    -181,  -181,  -181,    -4,  -181,   156,   110,  -181,  -181,   140,
     153,  -181,   169,  -181,   161,    42,    42,    92,   100,   182,
     183,   185,   173,  -181,   189,   168,     4,   113,  -181,   179,
    -181,    10,   161,   312,    10,  -181,  -181,  -181,  -181,  -181,
    -181,   117,  -181,  -181,    38,   198,  -181,  -181,   199,  -181,
    -181,  -181,    10,   125,   200,    10,    10,  -181,   168,   312,
      -5,   208,    24,  -181,  -181,    58,     5,    44,  -181,  -181,
     213,  -181,   210,    26,  -181,   201,   215,   222,   223,   216,
     218,   151,    58,  -181,     6,    58,   123,    58,   195,   205,
     312,  -181,   312,   168,  -181,  -181,   224,    42,  -181,  -181,
    -181,  -181,  -181,  -181,   232,  -181,  -181,  -181,    10,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,   212,  -181,   226,
      10,  -181,  -181,   235,   236,  -181,   243,   244,  -181,  -181,
     249,  -181,    10,   174,   220,  -181,  -181,   229,  -181,   242,
     144,  -181,   263,  -181,   265,  -181,    10,   248,   219,     5,
      10,    42,    42,    42,   271,   262,   145,  -181,  -181,   255,
    -181,  -181,   258,    10,  -181,   274,    58,    12,   312,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,    42,   272,   275,
      42,   277,   267,     5,  -181,  -181,  -181,    44,  -181,  -181,
    -181,    10,  -181,  -181,    42,   259,   276,  -181,    58,  -181,
     225,   268,   283,   265,  -181,  -181,  -181,  -181,   161,    58,
     284,  -181,   161,   300,  -181,   -11,   293,   305,   230,   285,
     252,  -181,   290,   307,    42,   312,   315,   310,   306,   312,
       0,   317,  -181,   276,  -181,   256,  -181,  -181,  -181,   247,
     144,  -181,   265,   301,  -181,  -181,    42,     3,  -181,  -181,
    -181,  -181,   327,   161,  -181,    10,   329,  -181,  -181,   323,
    -181,   332,  -181,  -181,  -181,  -181,   333,   264,    58,  -181,
     335,  -181,  -181,   289,   161,   161,   339,   345,  -181,    42,
     312,   292,   295,  -181,  -181,   324,   349,  -181,   354,  -181,
    -181,  -181,   331,   161,   312,   328,  -181
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -181,  -181,  -181,  -181,   352,   -70,   -22,   -13,  -181,  -181,
    -181,  -181,    72,    21,  -181,  -181,  -181,   -80,  -181,  -181,
    -181,  -128,   116,   297,    82,  -181,  -181,  -181,   337,  -181,
    -181,  -181,   -24,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,   202,   -73,  -181,  -181,  -181,
    -134,  -181,  -181,  -111,   176,  -181,  -181,  -181,   -65,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -180
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -165
static const yytype_int16 yytable[] =
{
      97,    97,   120,    54,    24,   162,   110,    54,   115,    72,
      59,   123,   108,    84,   187,    85,   298,    87,   299,   178,
      85,   113,    87,   114,   199,    85,    86,    87,    88,   132,
     168,    15,   135,   142,    13,    23,   313,   144,    54,    89,
     281,  -164,   109,    31,     1,    84,     3,   253,   145,   282,
     250,   125,    25,   107,     4,    26,     5,    85,    86,    87,
      88,    10,   233,    62,   314,    25,    -2,    73,    32,   159,
     160,    89,     8,    90,    12,    91,  -118,   179,    16,    10,
      16,   300,   193,  -115,    16,   141,   138,    16,   162,    19,
     251,    92,    93,    94,   292,    16,    21,    24,   148,   149,
     150,   151,   152,   153,    22,    90,    28,    91,  -118,   216,
     163,   164,   165,   217,    76,    77,   186,    33,   141,    55,
      60,   188,   162,    92,    93,    94,    42,   181,   182,    42,
     148,   149,   150,   151,   152,   153,   238,   239,   240,    61,
     248,    43,    63,    44,    43,    45,    44,    78,    58,   243,
     182,    46,    47,    65,    46,    47,    48,    49,    66,    48,
      49,    67,   193,    68,    75,   256,   221,    50,   259,   301,
      50,    79,    82,    51,    52,    99,    51,    52,   275,   261,
      42,    80,   279,   100,   222,   101,   102,   223,   103,    34,
     224,   104,   106,   112,   141,    43,   111,    44,    53,   225,
     124,    53,   127,   128,    24,    46,    47,    35,   133,   193,
      48,    49,    36,    37,   134,    38,   143,   167,   170,   169,
     173,    50,   174,   317,    39,   166,   141,    51,    52,   171,
     172,   312,   318,   -59,   175,   185,   195,   191,   204,    43,
     205,    44,   207,   208,   330,   331,   186,   210,   211,    46,
      47,    43,    53,    44,    48,    49,   214,    16,   218,   219,
     220,    46,    47,   344,   334,    50,    48,    49,   228,   235,
     230,    51,    52,   234,   241,   242,   247,    50,    43,   244,
      44,   249,   268,    51,    52,   254,   262,   255,    46,    47,
      43,   257,    44,    48,    49,   258,    53,   272,   271,   263,
      46,    47,   277,   280,    50,    48,    49,   285,    53,   289,
      51,    52,   286,   287,   290,   288,    50,   326,    43,   294,
      44,   291,    51,    52,   295,   303,   296,   305,    46,    47,
     307,   316,   310,    48,    49,    53,   319,   321,    43,   322,
      44,   325,   328,   329,    50,   336,   332,    53,    46,    47,
      51,    52,   333,    48,    49,   337,   340,   339,   341,   343,
     346,    14,   308,    98,    50,   304,   270,    57,     0,     0,
      51,    52,   206,     0,     0,    53,   237,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-181))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      65,    66,    82,    27,    17,   116,    76,    31,    81,    13,
      32,    84,     8,     3,   142,    15,    16,    17,    18,    13,
      15,    11,    17,    13,   158,    15,    16,    17,    18,   102,
       4,    34,   105,    38,    35,    34,    33,    13,    62,    29,
      51,     3,    38,    22,    19,     3,    83,   227,    24,    60,
      38,    13,     5,    75,     0,     8,     7,    15,    16,    17,
      18,    62,   196,    42,    61,     5,    35,    71,     8,    64,
      65,    29,    35,    63,    83,    65,    50,    71,    83,    62,
      83,    81,   147,    25,    83,   109,   108,    83,   199,    38,
     218,    81,    82,    83,   274,    83,    83,   110,    72,    73,
      74,    75,    76,    77,    38,    63,     3,    65,    50,   182,
      66,    67,    68,   183,     4,     5,   140,    83,   142,    83,
      13,   143,   233,    81,    82,    83,    11,     4,     5,    11,
      72,    73,    74,    75,    76,    77,   201,   202,   203,     7,
     213,    26,     3,    28,    26,    30,    28,     7,    30,     4,
       5,    36,    37,     3,    36,    37,    41,    42,     3,    41,
      42,     3,   227,     3,     8,   230,    22,    52,   241,   280,
      52,    18,    11,    58,    59,    83,    58,    59,   258,   244,
      11,    12,   262,    83,    40,     3,     3,    43,     3,    21,
      46,    18,     3,    14,   218,    26,    83,    28,    83,    55,
      83,    83,     4,     4,   217,    36,    37,    39,    83,   274,
      41,    42,    44,    45,    14,    47,     8,     7,     3,    18,
       4,    52,     4,   303,    56,    12,   250,    58,    59,     7,
       7,   296,   305,    38,    83,    30,     4,    13,    26,    26,
      14,    28,     7,     7,   324,   325,   270,     4,     4,    36,
      37,    26,    83,    28,    41,    42,     7,    83,    38,    30,
      18,    36,    37,   343,   329,    52,    41,    42,     5,    50,
       5,    58,    59,    25,     3,    13,    18,    52,    26,    24,
      28,     7,    57,    58,    59,    13,    27,    12,    36,    37,
      26,    14,    28,    41,    42,    28,    83,    14,    30,    23,
      36,    37,    18,     3,    52,    41,    42,    14,    83,    57,
      58,    59,     7,    83,    24,    30,    52,    53,    26,     4,
      28,    14,    58,    59,    14,     8,    20,    71,    36,    37,
      83,     4,    31,    41,    42,    83,     7,    14,    26,     7,
      28,     8,     7,    54,    52,    53,     7,    83,    36,    37,
      58,    59,     7,    41,    42,    60,     7,    33,     4,    28,
      32,     9,   290,    66,    52,   283,   250,    30,    -1,    -1,
      58,    59,   170,    -1,    -1,    83,   200,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    85,    83,     0,     7,    86,    87,    35,    98,
      62,    88,    83,    35,    88,    34,    83,    89,    91,    38,
     100,    83,    38,    34,    91,     5,     8,    97,     3,   112,
      99,    97,     8,    83,    21,    39,    44,    45,    47,    56,
      90,    92,    11,    26,    28,    30,    36,    37,    41,    42,
      52,    58,    59,    83,   116,    83,   115,   112,    30,    90,
      13,     7,    97,     3,   132,     3,     3,     3,     3,   140,
     128,   148,    13,    71,   119,     8,     4,     5,     7,    18,
      12,   136,    11,   101,     3,    15,    16,    17,    18,    29,
      63,    65,    81,    82,    83,   107,   167,   172,   107,    83,
      83,     3,     3,     3,    18,   126,     3,    90,     8,    38,
      89,    83,    14,    11,    13,   160,   164,   168,   172,   176,
     101,   116,   133,   160,    83,    13,   174,     4,     4,   117,
     118,   141,   160,    83,    14,   160,   159,   160,    90,   105,
     106,   116,    38,     8,    13,    24,   177,   179,    72,    73,
      74,    75,    76,    77,   137,   154,   155,   157,   163,    64,
      65,   166,   167,    66,    67,    68,    12,     7,     4,    18,
       3,     7,     7,     4,     4,    83,   129,   149,    13,    71,
     127,     4,     5,   113,   114,    30,   116,   105,    90,    93,
      95,    13,   181,   172,   186,     4,   162,   156,   158,   164,
     165,   171,   169,   170,    26,    14,   159,     7,     7,   142,
       4,     4,   123,   121,     7,   120,   160,    89,    38,    30,
      18,    22,    40,    43,    46,    55,    96,   184,     5,   178,
       5,   180,   138,   164,    25,    50,   161,   168,   172,   172,
     172,     3,    13,     4,    24,   130,   150,    18,   160,     7,
      38,   105,    94,   186,    13,    12,   172,    14,    28,   160,
     173,   172,    27,    23,   108,   111,   124,   122,    57,   102,
     106,    30,    14,   185,   182,   101,   134,    18,   143,   101,
       3,    51,    60,   109,   110,    14,     7,    83,    30,    57,
      24,    14,   186,   139,     4,    14,    20,   131,    16,    18,
      81,   167,   175,     8,   108,    71,   103,    83,    96,   183,
      31,   135,   172,    33,    61,   151,     4,   101,   160,     7,
     104,    14,     7,   144,   152,     8,    53,   125,     7,    54,
     101,   101,     7,     7,   172,   153,    53,    60,   145,    33,
       7,     4,   146,    28,   101,   147,    32
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
#line 262 "compiler.y"
    { strcpy(identifiers, "\0");}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 263 "compiler.y"
    {
  //verifyMatrix(hashVariables);
  verifyUsed(hashVariables);

}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 270 "compiler.y"
    { strcpy(identifiers, "\0");}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 271 "compiler.y"
    {
 // verifyMatrix(hashVariables);
  verifyUsed(hashVariables);
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 280 "compiler.y"
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
#line 332 "compiler.y"
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
#line 386 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 386 "compiler.y"
    {dim2 = currentNumber;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 386 "compiler.y"
    {dimension=2;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 387 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 387 "compiler.y"
    {dimension=1;}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 392 "compiler.y"
    {
    currentParameters = startList(); //Sempre inicia uma nova lista de parametros.
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, T_SEMRETORNO, 0, NULL, 0); //A funcao foi setada com valores default, estes valores serao alterados depois.
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
#line 410 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope); //Procurando funcao dentro da hash de funcoes
  if(identifier_temp!=NULL)
  {
    ((function*)(identifier_temp->info))->arity=currentFunctionArity; //Adicionando aridade
    //Irei adicionar a versao inversa da lista de tipos de parametros para facilitar mais tarde com a comparacao de parametros.
    currentParameters = reverseList(currentParameters);
    ((function*)(identifier_temp->info))->parameters=currentParameters; //Adicionando parametros
  }
  currentFunctionArity = 0; //Variavel global de aridade retornando ao valor 0.
  strcpy(currentScope, "main"); //Escopo retornando ao valor global
}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 423 "compiler.y"
    {
    currentParameters = startList(); //Sempre inicia uma nova lista de parametros.
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, T_SEMRETORNO, 0, NULL, 0);
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
#line 440 "compiler.y"
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
#line 454 "compiler.y"
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
#line 481 "compiler.y"
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

  case 48:

/* Line 1806 of yacc.c  */
#line 513 "compiler.y"
    {
  

}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 519 "compiler.y"
    {
	
}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 529 "compiler.y"
    {
// Em tipos_variaveis ira retornar o tipo de retorno da funcao, a qual sera acrescentada.
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 539 "compiler.y"
    {
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 547 "compiler.y"
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
      newVar->used = 1;
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

  case 62:

/* Line 1806 of yacc.c  */
#line 571 "compiler.y"
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
        newVar->used = 1;
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

  case 64:

/* Line 1806 of yacc.c  */
#line 602 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 603 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 605 "compiler.y"
    {
  	List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
	if(identifier_temp==NULL)
	{
	  printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
	} 
	else
	{
	  ((variable*)(identifier_temp->info))->used = 1;
	}
  
}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 617 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 619 "compiler.y"
    {
  	List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
	if(identifier_temp==NULL)
	{
	  printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
	} 
	else
	{
	  ((variable*)(identifier_temp->info))->used = 1;
	}
  
}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 631 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 633 "compiler.y"
    {

 //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
  
}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 641 "compiler.y"
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
      if(strcmp(currentFunction, "media") != 0 && strcmp(currentFunction, "maximo") != 0 && strcmp(currentFunction, "minimo") != 0)  
	printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
      else
	printf("Funcao primitiva maximo, minimo ou media precisam de um retorno.\n");
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
	if(T_INTEIRO != ((int)(functionTypes->info))) //inteiro
	  {
	    printf("Inteiro na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "real")==0)
	{
	if(T_REAL != ((int)(functionTypes->info))) //real
	  {
	    printf("Real na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "caracter")==0)
	{
	if(T_CARACTER != ((int)(functionTypes->info))) //caracter
	  {
	    printf("Caracter na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "literal")==0)
	{
	if(T_LITERAL != ((int)(functionTypes->info))) //literal
	  {
	    printf("Literal na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "lógico")==0)
	{
	if(T_LOGICO != ((int)(functionTypes->info))) //logico
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
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      //++currentRelationComparison;
  }
  strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  in_function = 0;
  
}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 752 "compiler.y"
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
		if(((variable*)(currVariable->info))->nColumn <= currentNumber ){
			printf("Erro na linha %d, %s possui %d posicoes.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
		}
		else
		{
		   int currentTypeInt = ((variable *)(currVariable->info))->type;
		  // printf("%d \n", currentTypeInt);
		  varRelations[currentRelationPos] = currentTypeInt;
		  ++currentRelationPos;
		  ++currentRelationComparison;
		}
	}else{
		printf("Variavel nao declarada na linha %d\n",nLine);
	}
}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 783 "compiler.y"
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
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  in_function = 0;
}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 798 "compiler.y"
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
		if(((variable*)(currVariable->info))->nColumn <= currentNumber ){
			printf("Erro na linha %d, %s possui %d colunas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
		}
	}else{
		printf("Variavel nao declarada na linha %d.\n",nLine);
	}
}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 822 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(((variable*)(currVariable->info))->nLine <= currentNumber ){
			printf("Erro na linha %d, %s possui %d linhas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
		}
	}
}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 829 "compiler.y"
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
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  in_function = 0;
}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 845 "compiler.y"
    {
  currentRelationComparison = 0;
  char* IdentifierTemp = (char*)malloc(sizeof(identifiers));
  strcpy(IdentifierTemp, identifiers);
  IdentifierTemp = strtok(IdentifierTemp, " ");
  List *identifier_temp = lookupStringVariable(hashVariables, IdentifierTemp);
  if(identifier_temp != NULL)
  {
    typeAttribute = ((variable *)(identifier_temp->info))->type;
    
    //cria o nó da arvore de atribuição
    attributionNode = newTreeNode();
    fillTreeNode(attributionNode,yytext,"ATRIBUICAO");
    //cria o nó do identificador e insere a esquerda da atribuição
    treeNode *idAux = newTreeNode();
    fillTreeNode(idAux, currentIdentifier, "IDENTIFICADOR");
    attributionNode->children[0] = idAux;
    //seta para null o nó de expressão (que será construído na parte de expressão)
    expressionNode = NULL;
  }
  else
    typeAttribute = T_SEMRETORNO;
      
  free(IdentifierTemp);
  strcpy(currentVariable, currentIdentifier);
}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 872 "compiler.y"
    {
    //adiciono o nó de expressão a direita do nó de atribuição
    attributionNode->children[1] = expressionNode;
    //retorno o nós de atribuição para null
    expressionNode=NULL;
  
  if(strcmp(currentScope, "main") == 0)
    { 
	//adiciono o nó de atribuição na árvore de execução do programa (in main, falta fazer arvores para funções)
	//verifica que nao esta dentro de condicional tambem (enquanto ou se)
	addAttributionNodeIntoGlobalTree();
  			  	
      char* returnVariable = strtok(identifiers, " ");
      if (returnVariable != NULL)
      { 
	List *identifier_temp = lookupStringVariable(hashVariables, returnVariable);

	if(identifier_temp==NULL)
	{
	  printf("Variavel %s nao declarada na linha %d.\n",returnVariable, nLine);
	} 
	else if((varRelations[0] == T_LITERAL || varRelations[0] == T_CARACTER) && currentRelationPos > 1) //caracter ou literal
	{
	  printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	}
	else if(in_logico==1 && in_condicional == 0)
	{
	  if((((variable*)(identifier_temp->info))->type) != 4)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  }
	  else
	    ((variable*)(identifier_temp->info))->used=1;
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
	  else if((varRelations[0] == T_CARACTER || varRelations[0] == T_LITERAL) && currentRelationPos > 1) //caracter ou literal
	  {
	    printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	  }
	  else if(in_logico==1 && in_condicional == 0)
	  {
	    if((((variable*)(identifier_temp->info))->type) != 4)
	    {
	      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	    }
	    else
	      ((variable*)(identifier_temp->info))->used=1;
	  in_logico=0;
	  }
	  else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  //  printf("Tipo da varivel: %d -> Tipo da expressao: %d\n",((variable*)(identifier_temp->info))->type, varRelations[0]);
	  }
	  else
	    ((variable*)(identifier_temp->info))->used=1;
	  }
	currentRelationPos = 0;
	}
      }
   }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 975 "compiler.y"
    {
currentRelationComparison = 0;
}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 979 "compiler.y"
    {
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-se","CONDICIONAL");   
    addConditionNodeIntoGlobalTree();
    
    //retorno os nós de atribuição para null
    expressionNode = NULL;
      
}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 991 "compiler.y"
    {
  commandNode = newTreeNode();
  fillTreeNode(commandNode, "comando-se", "COMANDO");
  //adicionando no global no stack, para ser recuperado depois
  stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
  //mudando no global para o comando
  globalTree = commandNode;
  
  //colocando a expressao como filho 
  conditionNode -> children[0] = expressionNode; 
  conditionNode -> children[1] = commandNode;
  commandNode ->children[0] = conditionNode;
}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1005 "compiler.y"
    {currentRelationPos = 0;}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1006 "compiler.y"
    {
  commandNode = globalTree;
  conditionNode = commandNode -> children[0];
  commandNode->children[0] = NULL;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1015 "compiler.y"
    {
    commandNode = newTreeNode();
    fillTreeNode(commandNode, "comando-faca", "COMANDO");
    //adicionando no global no stack, para ser recuperado depois
    stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
    //mudando no global para o comando
    globalTree = commandNode;
    //retorno os nós de atribuição para null
    expressionNode = NULL;
}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1026 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1033 "compiler.y"
    {  
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-enquanto","CONDICIONAL");
     conditionNode->children[0] = expressionNode;
     conditionNode->children[1] = commandNode;
     addConditionNodeIntoGlobalTree();
}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1044 "compiler.y"
    {in_condicional = 0;}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1046 "compiler.y"
    {
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-enquanto","CONDICIONAL");
    //seta para null o nó de expressão (que será construído na parte de expressão)
    expressionNode = NULL;
}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1054 "compiler.y"
    {
    //adiciono o nó de expressão a direita do nó de condicao
    conditionNode->children[0] = expressionNode;
    commandNode = newTreeNode();
    
    //adiciona o no de comando a direita
    fillTreeNode(commandNode, "comando-enquanto", "COMANDO");
    conditionNode->children[1] = commandNode;
    addConditionNodeIntoGlobalTree();

    //adicionando no global no stack, para ser recuperado depois
    stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
    //mudando no global para o comando
    globalTree = commandNode;
    //retorno os nós de atribuição para null
    expressionNode = NULL;
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1071 "compiler.y"
    {in_condicional = 0; currentRelationPos = 0 ; strcpy(identifiers,"\0");}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1074 "compiler.y"
    {

  //commandNode = NULL;
  expressionNode = NULL;
  //conditionNode = NULL;

  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1086 "compiler.y"
    {
  conditionNode = newTreeNode();
  fillTreeNode(conditionNode,"condicao-para","CONDICAO");
  addConditionNodeIntoGlobalTree();

}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1092 "compiler.y"
    {strcpy(identifiers,"\0"); currentRelationPos=0;}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1093 "compiler.y"
    {
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,":=","ATRIBUICAO");
  
  treeNode *idAux = newTreeNode();
  fillTreeNode(idAux, currentIdentifier, "IDENTIFICADOR");
  attributionNode->children[0] = idAux;
  
  conditionNode->children[0] = attributionNode;
}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1104 "compiler.y"
    {
  attributionNode->children[1] = expressionNode;
  expressionNode = NULL;

}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1110 "compiler.y"
    {
  conditionNode->children[1] = expressionNode;
  expressionNode = NULL;
}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1115 "compiler.y"
    {
  conditionNode->children[2] = expressionNode;
  expressionNode = NULL;
  
  commandNode = newTreeNode();
  fillTreeNode(commandNode, "comando-para", "COMANDO");
   
  conditionNode->children[3] = commandNode;
   
  //adicionando no global no stack, para ser recuperado depois
  stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
    
  //mudando no global para o comando
  globalTree = commandNode;
}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1131 "compiler.y"
    {
if(!verifyRelationship(varRelations, currentRelationPos))
  {
    printf("Valores incompativeis na linha %d\n", nLine);
  }
strcpy(identifiers,"\0"); 
currentRelationPos = 0;
}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1140 "compiler.y"
    {
  expressionNode = NULL;
 
  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1148 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos=0;}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1149 "compiler.y"
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
  
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-seleciona","CONDICIONAL");
    
    treeNode* idAux = newTreeNode();
    fillTreeNode(idAux, currentIdentifier, "IDENTIFICADOR");
    
    conditionNode->children[0] = idAux;
    addConditionNodeIntoGlobalTree();

    caseNode = newTreeNode();
    commandNode = newTreeNode();
    
    stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
    globalTree = caseNode;
    
    
    //retorno os nós de atribuição para null
    expressionNode = NULL;
    
    
    
}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1223 "compiler.y"
    {
if(varRelations[0] != T_LITERAL && varRelations[0] != T_LOGICO)
  switchType = varRelations[0];
else
  switchType = T_SEMRETORNO;
}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1232 "compiler.y"
    {
  //atualizando no de condicao para se-senao
  fillTreeNode(conditionNode,"condicao-se-senao","CONDICIONAL");   

  commandNode = newTreeNode();
  fillTreeNode(commandNode, "comando-senao", "COMANDO");
  
  conditionNode->children[2] = commandNode;
  //adicionando no global no stack, para ser recuperado depois
  stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
  //mudando no global para o comando
  globalTree = commandNode;
  
}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1246 "compiler.y"
    {currentRelationPos=0;}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1247 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1255 "compiler.y"
    {in_logico = 1;}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1256 "compiler.y"
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

  case 118:

/* Line 1806 of yacc.c  */
#line 1283 "compiler.y"
    {in_logico = 1;}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1284 "compiler.y"
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

  case 124:

/* Line 1806 of yacc.c  */
#line 1312 "compiler.y"
    { swapoutDoisUm(); swapoutTresDois(); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1314 "compiler.y"
    { swapoutDoisUm();swapoutTresDois(); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1315 "compiler.y"
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
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	}
    currentRelationComparison=0;
  }
}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1336 "compiler.y"
    {operadorDeNivelTres();}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1336 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1338 "compiler.y"
    { operadorDeNivelDois(">"); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1339 "compiler.y"
    { operadorDeNivelDois(">="); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1340 "compiler.y"
    { operadorDeNivelDois("="); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1341 "compiler.y"
    { operadorDeNivelDois("<"); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1342 "compiler.y"
    { operadorDeNivelDois("<="); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1343 "compiler.y"
    { operadorDeNivelDois("<>"); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1346 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1347 "compiler.y"
    { operadorDeNivelUm(); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1347 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1352 "compiler.y"
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
    
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, yytext, "REAL");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	if(!strcmp(expressionNode->type,"OPERADOR-N-1") & expressionNode->children[1]==NULL){
    		expressionNode->children[1] = aux;
    	}else{
    		if (!strcmp(expressionNode->type,"OPERADOR-N-2")){
    			swapDoisUm = expressionNode;
    			treeNode* aux2 = newTreeNode();
	    		fillTreeNode(aux2, "-", "OPERADOR-N-1");
	    		aux2->children[0] = expressionNode->children[1];
	    		aux2->children[1] = aux;
	    		expressionNode->children[1] = aux2;
	    		//retirando o '-'
		 		strcpy(aux->value, aux->value+1);
	    		aux2 = expressionNode;
    		} else {
    			treeNode* aux2 = newTreeNode();
	    		fillTreeNode(aux2, "-", "OPERADOR-N-1");
	    		aux2->children[0] = expressionNode;
	 		aux2->children[1] = aux;
	 		//retirando o '-'
	 		strcpy(aux->value, aux->value+1);
	    		expressionNode = aux2;
    		}
    		
    	}
    }
    
  }
}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1400 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    //printf("real com sinal\n");
  
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, yytext, "INTEIRO");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	if(!strcmp(expressionNode->type,"OPERADOR-N-1") & expressionNode->children[1]==NULL){
    		expressionNode->children[1] = aux;
    	}else{
    		if (!strcmp(expressionNode->type,"OPERADOR-N-2")){
    			swapDoisUm = expressionNode;
    			treeNode* aux2 = newTreeNode();
	    		fillTreeNode(aux2, "-", "OPERADOR-N-1");
	    		aux2->children[0] = expressionNode->children[1];
	    		aux2->children[1] = aux;
	    		expressionNode->children[1] = aux2;
	    		//retirando o '-'
		 		strcpy(aux->value, aux->value+1);
	    		aux2 = expressionNode;
    		} else {
    			treeNode* aux2 = newTreeNode();
	    		fillTreeNode(aux2, "-", "OPERADOR-N-1");
	    		aux2->children[0] = expressionNode;
		 		aux2->children[1] = aux;
		 		//retirando o '-'
		 		strcpy(aux->value, aux->value+1);
	    		expressionNode = aux2;
    		}
    		
    	}
    }
  
  }

}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1446 "compiler.y"
    {	operadorDeNivelZero("/"); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1446 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1448 "compiler.y"
    { operadorDeNivelZero("%"); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1448 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1450 "compiler.y"
    { operadorDeNivelZero("*"); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1450 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1453 "compiler.y"
    {
  if(in_function!=1)
  {
     
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    //printf("real com sinal\n");    
    
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, yytext, "INTEIRO");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	expressionNode->children[1] = aux;
    } 
  }
}
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1474 "compiler.y"
    {
  if(in_function!=1)
  {
  
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    //printf("real com sinal\n");
  
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, yytext, "REAL");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	expressionNode->children[1] = aux;
    }
    
  }
}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1501 "compiler.y"
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
   
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, ((variable*)(identifier_temp->info))->name, "VARIAVEL");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	expressionNode->children[1] = aux;
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
  
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, auxVariable, "VARIAVEL");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	expressionNode->children[1] = aux;
    }
    
  }
}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1572 "compiler.y"
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

  case 156:

/* Line 1806 of yacc.c  */
#line 1627 "compiler.y"
    {
  List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
  }
  else
  {
    char auxVariable[100];
    strcpy(auxVariable, currentIdentifier);
    strcat(auxVariable, " ");
    strcat(auxVariable, currentScope);
    identifier_temp = lookupStringVariable(hashVariables, auxVariable);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
  }
  if(identifier_temp != NULL)
  {
    if(((variable*)(identifier_temp->info))->used == 0)
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
    else if(((variable*)(identifier_temp->info))->matrix!=1){
      printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(identifier_temp->info))->name);
    }
    else if(((variable*)(identifier_temp->info))->nColumn <= currentNumber ){
	printf("Erro na linha %d, %s possui %d posicoes.\n", nLine, ((variable*)(identifier_temp->info))->name,((variable*)(identifier_temp->info))->nColumn );
    }
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

  case 157:

/* Line 1806 of yacc.c  */
#line 1674 "compiler.y"
    {
  List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
  }
  else
  {
    char auxVariable[100];
    strcpy(auxVariable, currentIdentifier);
    strcat(auxVariable, " ");
    strcat(auxVariable, currentScope);
    identifier_temp = lookupStringVariable(hashVariables, auxVariable);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
  }
  if(identifier_temp != NULL)
  {
    if(((variable*)(identifier_temp->info))->used == 0)
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
    else if(((variable*)(identifier_temp->info))->matrix!=1){
      printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(identifier_temp->info))->name);
    }
    else if(((variable*)(identifier_temp->info))->nColumn <= currentNumber ){
	printf("Erro na linha %d, %s possui %d colunas.\n", nLine, ((variable*)(identifier_temp->info))->name,((variable*)(identifier_temp->info))->nColumn );
    }
  }
}
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 1709 "compiler.y"
    {
   List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
    }
  }
  else
  {
    char auxVariable[100];
    strcpy(auxVariable, currentIdentifier);
    strcat(auxVariable, " ");
    strcat(auxVariable, currentScope);
    identifier_temp = lookupStringVariable(hashVariables, auxVariable);
  }
    if(identifier_temp != NULL)
    {
      if(((variable*)(identifier_temp->info))->nLine <= currentNumber )
      {
	printf("Erro na linha %d, %s possui %d linhas.\n", nLine, ((variable*)(identifier_temp->info))->name,((variable*)(identifier_temp->info))->nLine );
      }
      else if(in_function!=1)
      {
	int currentTypeInt = ((variable*)(identifier_temp->info))->type;
	varRelations[currentRelationPos] = currentTypeInt;
	++currentRelationPos;
	++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
      }
    }
  }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1745 "compiler.y"
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

  case 160:

/* Line 1806 of yacc.c  */
#line 1756 "compiler.y"
    {
  if(strlen(limitString) > MAX_LITERAL)
  {
    printf("Tamanho de literal passou do limite de 200 caracteres na linha %d\n", nLine);
  }
  else
  {
    if(in_function!=1)
    {
      int currentTypeInt = convertType(currentType);
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
    }
  }
}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 1774 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, yytext, "LOGICO");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	expressionNode->children[1] = aux;
    } 
    
  }
}
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 1794 "compiler.y"
    {
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, yytext, "LOGICO");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	expressionNode->children[1] = aux;
    } 
    
  }
}
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 1814 "compiler.y"
    {

  //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
List *identifier_temp = lookupStringFunction(hashFunction, currentIdentifier);
  if(identifier_temp!=NULL)
  {
    if(strcmp(currentIdentifier, "maximo")==0)
    {

      if (typeAttribute==T_INTEIRO)
      {
	strcpy(currentFunction, "maximo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "inteiro");
      }
      else if (typeAttribute==T_REAL)
      {
	strcpy(currentFunction, "maximo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "real");
      }
      else if (typeAttribute==T_CARACTER)
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
      if (typeAttribute==T_INTEIRO)
      {
	strcpy(currentFunction, "minimo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "inteiro");
      }
      else if (typeAttribute==T_REAL)
      {
	strcpy(currentFunction, "minimo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "real");
      }
      else if (typeAttribute==T_CARACTER)
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
      if (typeAttribute==T_INTEIRO)
      {
	strcpy(currentFunction, "media");
	strcat(currentFunction, " ");
	strcat(currentFunction, "inteiro");
      }
      else if (typeAttribute==T_REAL)
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

  case 165:

/* Line 1806 of yacc.c  */
#line 1898 "compiler.y"
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
	if(T_INTEIRO != ((int)(functionTypes->info))) //inteiro
	  {
	    printf("Inteiro na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "real")==0)
	{
	if(T_REAL != ((int)(functionTypes->info))) //real
	  {
	    printf("Real na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "caracter")==0)
	{
	if(T_CARACTER != ((int)(functionTypes->info))) //caracter
	  {
	    printf("Caracter na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "literal")==0)
	{
	if(T_LITERAL != ((int)(functionTypes->info))) //literal
	  {
	    printf("Literal na linha %d nao tem tipo correto equivalente na funcao %s.\n", nLine, currentFunction);
	  }
	}
	else if	(strcmp(argumentAux, "lógico")==0)
	{
	if(T_LOGICO != ((int)(functionTypes->info))) //logico
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

  case 167:

/* Line 1806 of yacc.c  */
#line 2020 "compiler.y"
    {
  if(switchType != T_INTEIRO)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
}
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 2027 "compiler.y"
    {
  if(switchType != T_REAL)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
  }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 2034 "compiler.y"
    {
  if(switchType != T_CARACTER)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 2040 "compiler.y"
    {countLine=0;}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 2040 "compiler.y"
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
			((variable*)(identifier_temp->info))->used = 0;
		}else{
			((variable*)(identifier_temp->info))->used = 1;
		}
	}
}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 2059 "compiler.y"
    {
	isMatrix = 1;
}
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 2062 "compiler.y"
    {countColumn=0;}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 2062 "compiler.y"
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
		int numColumn = ((variable*)(identifier_temp->info))->nColumn;
		if(countColumn != numColumn) {
			printf("Erro ao inicializar matriz na linha %d. Quantidade de termos incorreta.\n",nLine);
			((variable*)(identifier_temp->info))->used = 0;
		}else{
			((variable*)(identifier_temp->info))->used = 1;
		}
	}
}
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 2081 "compiler.y"
    {
	isMatrix = 1; 
 }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 2084 "compiler.y"
    {countColumn=0;}
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 2085 "compiler.y"
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
		int numColum = ((variable*)(identifier_temp->info))->nColumn;
		if(countColumn != numColum) {
			printf("Erro ao inicializar matriz na linha %d. Quantidade de termos incorreta.\n",nLine);
			((variable*)(identifier_temp->info))->used = 0;
		}
	}
}
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 2103 "compiler.y"
    {countColumn=0;}
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 2103 "compiler.y"
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
		if (((variable*)(identifier_temp->info))->nColumn != countColumn){
			printf("Erro ao inicializar matriz na linha %d. Quantidade de termos incorreta.\n",nLine);
			((variable*)(identifier_temp->info))->used =0;
		}
	}
}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 2123 "compiler.y"
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
	countColumn++;
}
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 2142 "compiler.y"
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
	countColumn++;
}
    break;



/* Line 1806 of yacc.c  */
#line 4439 "compiler.tab.c"
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
#line 2160 "compiler.y"


#include "lex.yy.c"

void createPrimitives()
{
  //maximo, aridade 2, inteiro
  function* newFunction = createFunction();
  char functionAux[100];
  strcpy(functionAux, "maximo");
  setFunction(newFunction, functionAux,T_SEMRETORNO, 0, NULL, 0);
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
  setFunction(newFunction, functionAux,T_INTEIRO, 2, argumentsFunction, 1);

  
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
  setFunction(newFunction, functionAux,T_REAL, 2, argumentsFunction, 1);
  
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
  setFunction(newFunction, functionAux,T_CARACTER, 2, argumentsFunction, 1);
  
  //minimo, aridade 2, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "minimo");
  setFunction(newFunction, functionAux,T_SEMRETORNO, 0, NULL, 0);
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
  setFunction(newFunction, functionAux,T_INTEIRO, 2, argumentsFunction, 1);

  
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
  setFunction(newFunction, functionAux,T_REAL, 2, argumentsFunction, 1);
  
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
  setFunction(newFunction, functionAux,T_CARACTER, 2, argumentsFunction, 1);
  
  //media, aridade 2, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "media");
  setFunction(newFunction, functionAux,T_SEMRETORNO, 0, NULL, 0);
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
  setFunction(newFunction, functionAux,T_INTEIRO, 2, argumentsFunction, 1);

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
  setFunction(newFunction, functionAux,T_REAL, 2, argumentsFunction, 1);
  
  //imprime, aridade 1, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "imprima");
  addInfoFunction(hashFunction, functionAux, newFunction);
  setFunction(newFunction, functionAux,T_SEMRETORNO, 1, NULL, 1);

  //leia, aridade 1, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "leia");
  addInfoFunction(hashFunction, functionAux, newFunction);
  setFunction(newFunction, functionAux,T_SEMRETORNO, 1, NULL, 1);

}

main(){
      hashVariables = createHash(MAX_HASH);
      hashFunction = createHash(MAX_HASH);
      createPrimitives();
      yyparse();
      
 
     if(IN_DEBUG_MODE){
  	treeNode* aux = globalTree;

  	printNode(aux, 12, 0);
	printf("\n ---------- \n");
      }

	
      freeTable(hashVariables);
      freeTableFunction(hashFunction);
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void){
	printf("Erro na Linha: %d\n", nLine);
}


