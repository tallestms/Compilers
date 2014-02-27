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
#include "execute.h"

#define MAX_HASH 1000
#define MAX_VARIABLE 32 //maior nome de variavel
#define MAX_FUNCTION 32 //maior nome de funcao
#define MAX_LITERAL 50
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
char limitString[50]; //limitador de tamanho de string no programa
int returnFlag = 0;
int argumentNumber = 0;

Stack* stackParentesis = NULL;
Stack* stackGlobal = NULL;
Stack* stackIfThenElse = NULL;

treeNode* globalTree = NULL;
treeNode* expressionNode = NULL;
treeNode* attributionNode = NULL;
treeNode* conditionNode = NULL;
treeNode* commandNode = NULL;
treeNode* caseNode = NULL;
treeNode* functionNode = NULL;

List* functionVariablesList = NULL;
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
treeNode* tempDelimitadorNivelZero = NULL;
treeNode* tempDelimitadorNivelUm = NULL;

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

void addNodeIntoGlobalTree(treeNode* auxNode)
{
	if(globalTree==NULL){
		globalTree = auxNode;
	}else{
		treeNode *aux = globalTree;
		while(aux->next!=NULL) aux = aux->next;
		aux->next = auxNode;
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

/**
* MATRIZES
*/
void treeMatrixOneDimension(char identifier[50], int currentNumber){
	char s[50];
	sprintf(s,"%d",currentNumber);
	//nó contendo nome do identificador
	treeNode* aux = newTreeNode();
	fillTreeNode(aux, identifier, "MATRIX");
	//nó contendo o tamanho da primeira dimensão
	treeNode* dim = newTreeNode();
	fillTreeNode(dim, s, "INTEIRO");
	//seto primeira dimensão no filho 0
	aux->children[0] = dim;
	//se expressionNode é null seto no primeiro filho, caso contrário no segundo
	if(expressionNode == NULL){
		expressionNode = aux;
	} else {
		expressionNode->children[1] = aux;
	}
}

void delimitadorNiveLZero(){
	treeNode* aux= newTreeNode();
	fillTreeNode(aux,"[]","DELIMITADOR-N-0");
	expressionNode = aux; //expressionNode sempre será NULL pela definição de matrizes
}

void delimitadorNivelUm(){
	treeNode* aux= newTreeNode();
	fillTreeNode(aux,"{}","DELIMITADOR-N-1");
	expressionNode = aux; //expressionNode sempre será NULL pela definição de matrizes
}



/* Line 268 of yacc.c  */
#line 302 "compiler.tab.c"

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
#line 427 "compiler.tab.c"

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
#define YYLAST   392

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  105
/* YYNRULES -- Number of rules.  */
#define YYNRULES  185
/* YYNRULES -- Number of states.  */
#define YYNSTATES  346

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
     125,   127,   129,   132,   134,   135,   139,   140,   144,   145,
     146,   155,   157,   158,   168,   175,   182,   190,   191,   202,
     203,   213,   217,   223,   224,   228,   234,   240,   241,   248,
     249,   256,   257,   258,   266,   267,   268,   278,   279,   280,
     281,   295,   296,   297,   304,   305,   306,   307,   308,   320,
     321,   322,   323,   324,   337,   338,   339,   340,   341,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   383,   384,
     385,   386,   395,   396,   397,   403,   405,   406,   407,   411,
     412,   413,   417,   419,   423,   424,   426,   427,   432,   433,
     438,   440,   442,   444,   446,   448,   450,   452,   453,   458,
     461,   463,   465,   467,   469,   471,   473,   474,   479,   480,
     485,   486,   491,   493,   495,   497,   499,   502,   507,   508,
     517,   519,   521,   522,   527,   529,   531,   532,   538,   540,
     542,   544,   546,   547,   548,   554,   555,   556,   562,   563,
     564,   572,   573,   574,   580,   582
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
      55,    -1,    46,    -1,    -1,    97,   117,    -1,    97,    11,
      97,    12,    -1,    -1,    98,    35,    83,    99,   113,    -1,
      -1,    35,    83,   100,   113,    -1,    -1,   101,   117,    -1,
      11,   101,    12,    -1,    -1,   103,    -1,   117,    -1,   103,
     117,    -1,   173,    -1,    -1,   111,   106,   105,    -1,    -1,
     111,   107,   108,    -1,    -1,    -1,    51,   109,     8,   101,
      53,   110,     7,    60,    -1,    60,    -1,    -1,    23,     3,
     177,     4,     8,   101,    53,   112,     7,    -1,    23,     3,
     177,     4,     8,   101,    -1,     3,   116,     4,    38,   102,
      30,    -1,     3,   116,     4,    89,    38,   102,    30,    -1,
      -1,     3,   116,     4,     8,    90,   114,    89,    38,   102,
      30,    -1,    -1,     3,   116,     4,     8,    90,   115,    38,
     102,    30,    -1,    83,     8,    90,    -1,   116,     5,    83,
       8,    90,    -1,    -1,    57,    83,     7,    -1,    36,     3,
     104,     4,     7,    -1,    37,     3,   104,     4,     7,    -1,
      -1,    41,     3,    83,   118,     4,     7,    -1,    -1,    42,
       3,    83,   119,     4,     7,    -1,    -1,    -1,    83,   120,
       3,   160,     4,   121,     7,    -1,    -1,    -1,    83,    13,
      18,    14,    71,   122,   161,   123,     7,    -1,    -1,    -1,
      -1,    83,    13,    18,    14,    13,   124,    18,   125,    14,
      71,   161,   126,     7,    -1,    -1,    -1,    83,    71,   127,
     161,   128,     7,    -1,    -1,    -1,    -1,    -1,    58,   129,
       3,   161,   130,     4,   131,    27,   101,   132,   152,    -1,
      -1,    -1,    -1,    -1,    28,   133,   101,   134,     7,    26,
       3,   161,   135,     4,   136,     7,    -1,    -1,    -1,    -1,
      -1,    26,     3,   137,   161,   138,     4,   139,    28,   101,
     140,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,   141,     3,   142,    83,   143,    24,   173,   144,
      20,   173,   145,    54,   173,   146,     4,   147,    28,   101,
     148,    32,    -1,    -1,    -1,    -1,    59,   149,     3,    83,
     150,     4,   151,   105,    -1,    -1,    -1,    61,   153,   101,
     154,    33,    -1,    33,    -1,    -1,    -1,   156,   157,    25,
      -1,    -1,    -1,   158,   159,    50,    -1,   161,    -1,   160,
       5,   161,    -1,    -1,   165,    -1,    -1,   161,   164,   165,
     162,    -1,    -1,   161,   155,   163,   165,    -1,    72,    -1,
      74,    -1,    76,    -1,    73,    -1,    75,    -1,    77,    -1,
     169,    -1,    -1,   165,   167,   166,   169,    -1,   165,   168,
      -1,    64,    -1,    65,    -1,    15,    -1,    17,    -1,   178,
      -1,   173,    -1,    -1,   169,    67,   170,   173,    -1,    -1,
     169,    68,   171,   173,    -1,    -1,   169,    66,   172,   173,
      -1,   168,    -1,    18,    -1,    16,    -1,    83,    -1,    65,
      83,    -1,    83,    13,    18,    14,    -1,    -1,    83,    13,
      18,    14,    13,   174,    18,    14,    -1,    81,    -1,    82,
      -1,    -1,     3,   175,   161,     4,    -1,    63,    -1,    29,
      -1,    -1,    83,   176,     3,   160,     4,    -1,   168,    -1,
      18,    -1,    16,    -1,    81,    -1,    -1,    -1,    11,   179,
     183,   180,    12,    -1,    -1,    -1,    13,   181,   188,   182,
      14,    -1,    -1,    -1,   183,     5,    13,   184,   188,   185,
      14,    -1,    -1,    -1,    13,   186,   188,   187,    14,    -1,
     173,    -1,   188,     5,   173,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   316,   316,   316,   324,   323,   330,   331,   331,   333,
     385,   436,   436,   436,   436,   436,   436,   438,   438,   440,
     440,   440,   441,   441,   442,   442,   442,   442,   442,   444,
     444,   444,   446,   445,   504,   503,   561,   561,   561,   562,
     562,   563,   563,   565,   567,   566,   595,   594,   631,   638,
     630,   644,   646,   645,   651,   653,   654,   656,   655,   667,
     665,   676,   718,   760,   763,   804,   805,   807,   806,   820,
     819,   834,   842,   833,   968,   999,   968,  1014,  1038,  1045,
    1014,  1061,  1093,  1060,  1201,  1212,  1226,  1227,  1200,  1236,
    1247,  1254,  1262,  1235,  1264,  1272,  1289,  1292,  1263,  1304,
    1310,  1311,  1323,  1329,  1344,  1392,  1401,  1303,  1409,  1410,
    1489,  1409,  1498,  1512,  1497,  1518,  1521,  1522,  1521,  1549,
    1550,  1549,  1577,  1603,  1630,  1631,  1633,  1633,  1655,  1655,
    1657,  1658,  1659,  1660,  1661,  1662,  1665,  1666,  1666,  1667,
    1668,  1668,  1670,  1718,  1763,  1763,  1765,  1765,  1767,  1767,
    1769,  1769,  1770,  1771,  1792,  1814,  1890,  1974,  2026,  2025,
    2110,  2121,  2138,  2138,  2160,  2180,  2201,  2200,  2424,  2424,
    2437,  2450,  2464,  2464,  2464,  2488,  2488,  2488,  2511,  2512,
    2511,  2534,  2534,  2533,  2558,  2580
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
  "$@6", "$@7", "BLOCO_AUXILIAR", "BLOCO_FUNCAO", "REPETICAO_COMANDO",
  "BLOCO_IMPRIMA", "BLOCO_SWITCH", "$@8", "$@9", "FIM_BLOCO_SWITCH",
  "$@10", "$@11", "BLOCO_SWITCH_AUX", "$@12", "FUNCAO", "$@13", "$@14",
  "VARIAVEIS_FUNCAO", "COMANDO", "$@15", "$@16", "$@17", "$@18", "$@19",
  "$@20", "$@21", "$@22", "$@23", "$@24", "$@25", "$@26", "$@27", "$@28",
  "$@29", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35", "$@36", "$@37",
  "$@38", "$@39", "$@40", "$@41", "$@42", "$@43", "$@44", "$@45", "$@46",
  "$@47", "$@48", "BLOCO_SENAO_FIMSE", "$@49", "$@50", "LOGICOS", "$@51",
  "$@52", "$@53", "$@54", "ARGUMENTOS_FUNCAO", "EXPR", "$@55", "$@56",
  "COMPARACOES", "SIEXPR", "$@57", "ADICAO_SUBTRACAO", "SINALFATOR",
  "TERMO", "$@58", "$@59", "$@60", "FATOR", "$@61", "$@62", "$@63",
  "FATOR_CASE", "MATRIZ", "$@64", "$@65", "$@66", "$@67",
  "MATRIZ_VARIAS_COLUNAS", "$@68", "$@69", "$@70", "$@71", "BLOCO_MATRIZ", 0
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
      97,    97,    99,    98,   100,    98,   101,   101,   101,   102,
     102,   103,   103,   104,   106,   105,   107,   105,   109,   110,
     108,   108,   112,   111,   111,   113,   113,   114,   113,   115,
     113,   116,   116,   116,   117,   117,   117,   118,   117,   119,
     117,   120,   121,   117,   122,   123,   117,   124,   125,   126,
     117,   127,   128,   117,   129,   130,   131,   132,   117,   133,
     134,   135,   136,   117,   137,   138,   139,   140,   117,   141,
     142,   143,   144,   145,   146,   147,   148,   117,   149,   150,
     151,   117,   153,   154,   152,   152,   156,   157,   155,   158,
     159,   155,   160,   160,   160,   161,   162,   161,   163,   161,
     164,   164,   164,   164,   164,   164,   165,   166,   165,   165,
     167,   167,   168,   168,   169,   169,   170,   169,   171,   169,
     172,   169,   173,   173,   173,   173,   173,   173,   174,   173,
     173,   173,   175,   173,   173,   173,   176,   173,   177,   177,
     177,   177,   179,   180,   178,   181,   182,   178,   184,   185,
     183,   186,   187,   183,   188,   188
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     8,     3,     2,     0,     4,
       5,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       0,    11,     0,     7,     1,     1,     1,     1,     1,     0,
       2,     4,     0,     5,     0,     4,     0,     2,     3,     0,
       1,     1,     2,     1,     0,     3,     0,     3,     0,     0,
       8,     1,     0,     9,     6,     6,     7,     0,    10,     0,
       9,     3,     5,     0,     3,     5,     5,     0,     6,     0,
       6,     0,     0,     7,     0,     0,     9,     0,     0,     0,
      13,     0,     0,     6,     0,     0,     0,     0,    11,     0,
       0,     0,     0,    12,     0,     0,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,     8,     0,     0,     5,     1,     0,     0,     3,     0,
       0,     3,     1,     3,     0,     1,     0,     4,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     2,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     2,     4,     0,     8,
       1,     1,     0,     4,     1,     1,     0,     5,     1,     1,
       1,     1,     0,     0,     5,     0,     0,     5,     0,     0,
       7,     0,     0,     5,     1,     3
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
       0,    16,    29,     0,    89,     5,     0,     0,     0,     0,
      99,     0,    84,   108,    71,    30,     0,     0,    33,     3,
       0,     0,     9,     0,    94,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,     0,     0,     0,     0,
      10,     0,    31,     0,    36,    90,   162,   142,   154,   143,
     153,   165,   164,     0,   160,   161,   155,     0,   152,    43,
       0,    67,    69,   100,    64,     0,     0,     0,     0,   124,
      61,     0,    39,     0,     0,     0,   172,   175,    95,   125,
     136,   145,   144,     0,    37,     0,     0,   156,     0,     0,
       0,     0,     0,     0,     0,    85,   109,     0,    82,     0,
     122,    57,     0,    40,    41,    39,     0,    19,    22,     0,
       0,   130,   133,   131,   134,   132,   135,     0,   128,   117,
     120,     0,   140,   141,   137,   139,   150,   146,   148,    38,
       0,   116,     0,   124,    65,    66,     0,     0,   101,     0,
       0,    77,    74,     0,    72,     0,     0,     0,    55,    42,
       0,    62,     0,     0,   181,   173,   184,   176,    96,     0,
       0,     0,   126,     0,     0,     0,     0,     0,   163,   157,
       0,    68,    70,     0,    86,   110,     0,     0,    83,     0,
     123,     0,    39,    56,    20,    25,    24,    26,    28,    27,
      23,     0,     0,     0,     0,     0,     0,   129,   118,   121,
     127,   138,   151,   147,   149,     0,   158,   167,     0,     0,
       0,    78,    75,    73,    39,     0,     0,   182,   178,   174,
     185,   177,    36,    91,     0,   102,    36,     0,   111,    46,
       0,     0,     0,    60,     0,     0,     0,    97,     0,     0,
       0,    87,     0,     0,     0,     0,    76,    58,     0,   183,
     179,     0,    92,   159,     0,     0,   170,   169,   171,   168,
       0,    45,    48,    51,    47,     0,    21,     0,    98,     0,
     103,   115,   112,    88,     0,     0,    79,   180,    93,     0,
      36,    36,    36,     0,     0,   113,    54,     0,    80,   104,
       0,    52,    49,     0,   114,     0,     0,   105,    53,     0,
       0,    50,    36,   106,     0,   107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     7,    11,    17,    40,    18,    41,   192,
     256,   193,   230,    27,     9,    30,    20,    85,   142,   143,
      97,   268,   283,   284,   304,   315,   336,   269,   335,    29,
     186,   187,    57,   124,   132,   133,    76,   219,   217,   271,
     216,   270,   323,   108,   183,    72,   179,   249,   295,    65,
     125,   278,   309,    83,   157,   236,   291,    70,   134,   213,
     280,   319,   333,   340,   344,    73,   180,   250,   313,   320,
     330,   158,   159,   200,   160,   201,   139,   140,   240,   199,
     161,   119,   203,   164,    98,   120,   205,   206,   204,   121,
     264,   126,   129,   300,   122,   149,   233,   150,   235,   195,
     276,   307,   231,   275,   197
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -207
static const yytype_int16 yypact[] =
{
      40,   -16,    62,    65,  -207,    51,    63,    50,    30,    13,
     -14,    77,  -207,    34,    80,  -207,  -207,    12,    45,  -207,
     117,  -207,  -207,  -207,    55,    39,    52,   136,    53,  -207,
     117,   185,    52,  -207,  -207,  -207,  -207,  -207,   110,  -207,
     130,  -207,  -207,   138,  -207,  -207,   139,   141,   142,   143,
    -207,    66,  -207,  -207,    -3,  -207,   140,    60,  -207,  -207,
     144,   132,  -207,   235,  -207,   149,    20,    20,    69,    70,
     158,   156,   164,   167,   163,  -207,   171,    52,     4,    92,
    -207,   162,  -207,    11,   149,   309,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,   100,  -207,  -207,    44,   181,  -207,  -207,
     182,  -207,  -207,  -207,  -207,    11,   104,   175,    11,    11,
    -207,    52,   309,   -17,   183,    31,  -207,  -207,    82,    15,
      67,  -207,  -207,   238,  -207,   192,    11,  -207,   172,   189,
     194,   195,   200,   201,   123,    82,  -207,     6,    82,   101,
      82,   169,   179,   309,  -207,   309,    52,  -207,  -207,   203,
      20,  -207,  -207,  -207,  -207,  -207,  -207,   210,  -207,  -207,
    -207,    11,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
     191,    54,   204,    11,  -207,  -207,   213,   216,  -207,   220,
     221,  -207,  -207,   222,  -207,    11,   150,   196,  -207,  -207,
     202,  -207,   217,   157,  -207,   231,  -207,   236,  -207,    11,
     223,   199,    15,    11,    20,    20,    20,   242,  -207,   239,
     105,  -207,  -207,   227,  -207,  -207,   237,    11,  -207,   246,
      82,    -5,   309,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,    20,   241,   244,    20,   243,   234,    15,  -207,  -207,
    -207,    67,  -207,  -207,  -207,    11,  -207,  -207,    20,   232,
     247,  -207,    82,  -207,   309,   248,   251,   236,  -207,  -207,
    -207,  -207,   149,    82,   249,  -207,   149,   266,  -207,   250,
     267,   276,   252,  -207,   260,   271,    20,   309,   282,   274,
     269,   309,     0,   247,    -6,   228,  -207,  -207,   157,  -207,
     236,   273,  -207,  -207,    20,    10,  -207,  -207,  -207,  -207,
     287,  -207,  -207,  -207,  -207,    11,  -207,   288,  -207,   298,
    -207,  -207,  -207,  -207,   299,   302,    82,  -207,  -207,   261,
     149,   149,   149,   312,    20,   309,   272,   275,  -207,  -207,
     289,  -207,  -207,   316,  -207,   319,   329,  -207,  -207,   263,
     278,  -207,   149,   309,   306,  -207
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -207,  -207,  -207,  -207,   330,   -70,   -21,   -13,  -207,  -207,
    -207,  -207,    56,    19,  -207,  -207,  -207,   -82,  -140,  -207,
     280,    57,  -207,  -207,  -207,  -207,  -207,  -207,  -207,   311,
    -207,  -207,  -207,   -24,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -207,  -207,   170,   -74,  -207,  -207,
    -207,  -148,  -207,  -207,  -113,   145,  -207,  -207,  -207,   -66,
    -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,  -206
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -167
static const yytype_int16 yytable[] =
{
      99,    99,   123,    55,    24,   190,   165,    55,   113,   118,
      74,    60,   111,   202,    86,    87,   296,    89,   297,   181,
      15,   145,   116,    86,   117,   257,    87,    88,    89,    90,
      87,   135,    89,   254,   138,    87,    88,    89,    90,    55,
      91,    31,   112,   311,   147,   302,    23,  -166,    13,    91,
      25,   237,   171,    26,   303,   148,   110,   128,   208,     1,
      25,    63,     4,    32,    78,    79,    16,     3,    75,    16,
     290,   312,     5,    34,    92,    10,    93,   182,    16,   162,
     163,   298,   255,    92,   196,    93,    -2,    16,   144,   165,
     141,    35,    94,    95,    96,    16,    36,    37,     8,    38,
      24,    94,    95,    96,  -119,   184,   185,  -116,    39,   247,
     185,   220,    10,    12,   272,    19,   221,    21,    22,   189,
      28,   144,    33,    61,   165,   191,   151,   152,   153,   154,
     155,   156,  -119,   166,   167,   168,    56,    62,   242,   243,
     244,    64,    66,   252,    67,    68,    69,    42,    77,    71,
      81,    80,   101,   102,   151,   152,   153,   154,   155,   156,
      84,   103,    43,   104,    44,   196,    45,   105,   260,   299,
     106,   263,    46,    47,   109,   114,   115,    48,    49,   225,
     277,   107,   265,   127,   281,   130,   131,   136,    50,   137,
     172,   146,   173,    51,    52,    53,    42,   226,   144,   170,
     227,   174,   175,   228,   176,   177,   178,   -59,    24,   188,
     196,    43,   229,    44,   198,    59,   194,   207,   209,    54,
     211,    46,    47,   212,   214,   215,    48,    49,   310,   218,
     144,   316,   223,    16,   222,   224,   232,    50,   325,   326,
     327,   234,    51,    52,    53,   245,    42,    82,   238,   239,
     169,   248,   246,   253,   258,   251,   259,   261,   329,   266,
     343,    43,   262,    44,    43,   274,    44,   279,    54,   282,
     267,    46,    47,   -44,    46,    47,    48,    49,   273,    48,
      49,   285,   287,   286,   288,   289,   292,    50,   293,   294,
      50,   314,    51,    52,    53,    51,    52,    53,    43,   305,
      44,    43,   317,    44,   308,   318,   342,   321,    46,    47,
     322,    46,    47,    48,    49,   324,    48,    49,    54,   328,
     337,    54,   334,   341,    50,   331,   338,    50,   332,    51,
      52,    53,    51,    52,    53,    43,   339,    44,   345,    14,
     301,    58,     0,   210,   306,    46,    47,   100,   241,     0,
      48,    49,     0,     0,     0,    54,     0,     0,    54,     0,
       0,    50,     0,     0,     0,     0,    51,    52,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-207))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      66,    67,    84,    27,    17,   145,   119,    31,    78,    83,
      13,    32,     8,   161,     3,    15,    16,    17,    18,    13,
      34,    38,    11,     3,    13,   231,    15,    16,    17,    18,
      15,   105,    17,    38,   108,    15,    16,    17,    18,    63,
      29,    22,    38,    33,    13,    51,    34,     3,    35,    29,
       5,   199,   126,     8,    60,    24,    77,    13,     4,    19,
       5,    42,     0,     8,     4,     5,    83,    83,    71,    83,
     276,    61,     7,    21,    63,    62,    65,    71,    83,    64,
      65,    81,   222,    63,   150,    65,    35,    83,   112,   202,
     111,    39,    81,    82,    83,    83,    44,    45,    35,    47,
     113,    81,    82,    83,    50,     4,     5,    25,    56,     4,
       5,   185,    62,    83,   254,    38,   186,    83,    38,   143,
       3,   145,    83,    13,   237,   146,    72,    73,    74,    75,
      76,    77,    50,    66,    67,    68,    83,     7,   204,   205,
     206,     3,     3,   217,     3,     3,     3,    11,     8,    83,
      18,     7,    83,    83,    72,    73,    74,    75,    76,    77,
      11,     3,    26,     7,    28,   231,    30,     3,   234,   282,
       3,   245,    36,    37,     3,    83,    14,    41,    42,    22,
     262,    18,   248,    83,   266,     4,     4,    83,    52,    14,
      18,     8,     3,    57,    58,    59,    11,    40,   222,     7,
      43,     7,     7,    46,     4,     4,    83,    38,   221,    30,
     276,    26,    55,    28,     4,    30,    13,    26,    14,    83,
       7,    36,    37,     7,     4,     4,    41,    42,   294,     7,
     254,   305,    30,    83,    38,    18,     5,    52,   320,   321,
     322,     5,    57,    58,    59,     3,    11,    12,    25,    50,
      12,    24,    13,     7,    13,    18,    12,    14,   324,    27,
     342,    26,    28,    28,    26,    14,    28,    18,    83,     3,
      23,    36,    37,    23,    36,    37,    41,    42,    30,    41,
      42,    14,    30,     7,    24,    14,     4,    52,    14,    20,
      52,     4,    57,    58,    59,    57,    58,    59,    26,    71,
      28,    26,    14,    28,    31,     7,    28,     8,    36,    37,
       8,    36,    37,    41,    42,    54,    41,    42,    83,     7,
       4,    83,    33,    60,    52,    53,     7,    52,    53,    57,
      58,    59,    57,    58,    59,    26,     7,    28,    32,     9,
     283,    30,    -1,   173,   288,    36,    37,    67,   203,    -1,
      41,    42,    -1,    -1,    -1,    83,    -1,    -1,    83,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    85,    83,     0,     7,    86,    87,    35,    98,
      62,    88,    83,    35,    88,    34,    83,    89,    91,    38,
     100,    83,    38,    34,    91,     5,     8,    97,     3,   113,
      99,    97,     8,    83,    21,    39,    44,    45,    47,    56,
      90,    92,    11,    26,    28,    30,    36,    37,    41,    42,
      52,    57,    58,    59,    83,   117,    83,   116,   113,    30,
      90,    13,     7,    97,     3,   133,     3,     3,     3,     3,
     141,    83,   129,   149,    13,    71,   120,     8,     4,     5,
       7,    18,    12,   137,    11,   101,     3,    15,    16,    17,
      18,    29,    63,    65,    81,    82,    83,   104,   168,   173,
     104,    83,    83,     3,     7,     3,     3,    18,   127,     3,
      90,     8,    38,    89,    83,    14,    11,    13,   161,   165,
     169,   173,   178,   101,   117,   134,   175,    83,    13,   176,
       4,     4,   118,   119,   142,   161,    83,    14,   161,   160,
     161,    90,   102,   103,   117,    38,     8,    13,    24,   179,
     181,    72,    73,    74,    75,    76,    77,   138,   155,   156,
     158,   164,    64,    65,   167,   168,    66,    67,    68,    12,
       7,   161,    18,     3,     7,     7,     4,     4,    83,   130,
     150,    13,    71,   128,     4,     5,   114,   115,    30,   117,
     102,    90,    93,    95,    13,   183,   173,   188,     4,   163,
     157,   159,   165,   166,   172,   170,   171,    26,     4,    14,
     160,     7,     7,   143,     4,     4,   124,   122,     7,   121,
     161,    89,    38,    30,    18,    22,    40,    43,    46,    55,
      96,   186,     5,   180,     5,   182,   139,   165,    25,    50,
     162,   169,   173,   173,   173,     3,    13,     4,    24,   131,
     151,    18,   161,     7,    38,   102,    94,   188,    13,    12,
     173,    14,    28,   161,   174,   173,    27,    23,   105,   111,
     125,   123,   102,    30,    14,   187,   184,   101,   135,    18,
     144,   101,     3,   106,   107,    14,     7,    30,    24,    14,
     188,   140,     4,    14,    20,   132,    16,    18,    81,   168,
     177,   105,    51,    60,   108,    71,    96,   185,    31,   136,
     173,    33,    61,   152,     4,   109,   161,    14,     7,   145,
     153,     8,     8,   126,    54,   101,   101,   101,     7,   173,
     154,    53,    53,   146,    33,   112,   110,     4,     7,     7,
     147,    60,    28,   101,   148,    32
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
#line 316 "compiler.y"
    { strcpy(identifiers, "\0");}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 317 "compiler.y"
    {
  //verifyMatrix(hashVariables);
  verifyUsed(hashVariables);

}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 324 "compiler.y"
    { strcpy(identifiers, "\0");}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 325 "compiler.y"
    {
 // verifyMatrix(hashVariables);
  verifyUsed(hashVariables);
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 334 "compiler.y"
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
#line 386 "compiler.y"
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
#line 440 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 440 "compiler.y"
    {dim2 = currentNumber;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 440 "compiler.y"
    {dimension=2;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 441 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 441 "compiler.y"
    {dimension=1;}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 446 "compiler.y"
    {
    currentParameters = startList(); //Sempre inicia uma nova lista de parametros.
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, T_SEMRETORNO, 0, NULL, 0); //A funcao foi setada com valores default, estes valores serao alterados depois.
	
	functionNode = newTreeNode();
	newFunction->functionTree = functionNode;
	
	fillTreeNode(functionNode, yytext, "FUNCAO");
	//Default eh funcao sem retorno...
	treeNode *returnNode = newTreeNode();
	fillTreeNode(returnNode, "RETORNO VARIAVEL", "VOID");
	functionNode->children[0] = returnNode;
	addNodeIntoGlobalTree(functionNode);
	
	commandNode = newTreeNode();
	fillTreeNode(commandNode, "comando-funcao", "COMANDO");
	stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
	globalTree = commandNode;
	expressionNode = NULL;
	functionNode->children[2] = commandNode;
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
#line 481 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope); //Procurando funcao dentro da hash de funcoes
  if(identifier_temp!=NULL)
  {
    function* functionAux = ((function*)(identifier_temp->info));
    functionAux->arity=currentFunctionArity;
    //Adicionando versao inversa da lista para facilitar mais tarde
    currentParameters = reverseList(currentParameters);
    functionAux->parameters=currentParameters;
    if(functionAux->returnType!=T_SEMRETORNO)
    {
      if(returnFlag == 0)
      {
	printf("Funcao %s precisa de retorno e nao possui.\n", currentScope);
      }
    }
  }
  currentFunctionArity = 0; //Variavel global de aridade retornando ao valor 0.
  strcpy(currentScope, "main"); //Escopo retornando ao valor global
  returnFlag = 0;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 504 "compiler.y"
    {
    currentParameters = startList(); //Sempre inicia uma nova lista de parametros.
    strcpy(currentScope, currentIdentifier); //O escopo passa a ser a funcao.
    if(lookupStringFunction(hashFunction, currentIdentifier) == NULL)
    {
	function* newFunction = createFunction();
	addInfoFunction(hashFunction, currentIdentifier, newFunction);
	setFunction(newFunction, currentIdentifier, T_SEMRETORNO, 0, NULL, 0);

	functionNode = newTreeNode();
	newFunction->functionTree = functionNode;

	fillTreeNode(functionNode, yytext, "FUNCAO");
	//Default eh funcao sem retorno...
	treeNode *returnNode = newTreeNode();
	fillTreeNode(returnNode, "RETORNO VARIAVEL","VOID");
	functionNode->children[0] = returnNode;
	addNodeIntoGlobalTree(functionNode);
	
	commandNode = newTreeNode();
	fillTreeNode(commandNode, "comando-funcao", "COMANDO");
	stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
	globalTree = commandNode;
	expressionNode = NULL;
	functionNode->children[2] = commandNode;
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
#line 538 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope);
  if(identifier_temp!=NULL)
  {
    function* functionAux = ((function*)(identifier_temp->info));
    functionAux->arity=currentFunctionArity;
    //Adicionando versao inversa da lista para facilitar mais tarde
    currentParameters = reverseList(currentParameters);
    functionAux->parameters=currentParameters;
    if(functionAux->returnType!=T_SEMRETORNO)
    {
      if(returnFlag == 0)
      {
	printf("Funcao %s precisa de retorno e nao possui.\n", currentScope);
      }
    }
  }
  currentFunctionArity = 0;
  strcpy(currentScope, "main");
  returnFlag = 0;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 567 "compiler.y"
    {
  //treeNode* aux = caseNode; //Ponteiro que sera utilizado no final desta expressao
  treeNode* caseNodeAux = newTreeNode();
    
      //if(aux->children[2] == NULL)
   // aux->children[1]->next = caseNodeAux;
  //    if(aux->children[2] == NULL)
  //  aux->children[1]->next = caseNodeAux;
    
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
  
  commandNode = newTreeNode();
  
  fillTreeNode(commandNode, "comando-caso", "COMANDO");
  fillTreeNode(caseNodeAux, "caso", "CASO");
   
  caseNode->next = caseNodeAux;
  caseNode = caseNodeAux;
 
  caseNode->children[1] = commandNode;
  
  stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
  globalTree = commandNode; 
}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 595 "compiler.y"
    {

  treeNode* caseNodeAux = newTreeNode();
  
  //Se parar case for 0, ou seja, nao ha existencia do 0, o proximo da ultima expressao do ultimo caso ira apontar para o proximo caso. 
  /*
  if(!pararCase)
  {
    pararCase = 1;
    commandNode -> next = caseNodeAux; 
  }
  */
  
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
  
  commandNode = newTreeNode();
  
  fillTreeNode(commandNode, "comando-caso", "COMANDO");
  fillTreeNode(caseNodeAux, "caso", "CASO");
  
  caseNode->next = caseNodeAux;
  caseNode = caseNodeAux;
 
  caseNode->children[1] = commandNode;
  stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
  globalTree = commandNode;  
}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 625 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 631 "compiler.y"
    {
  fillTreeNode(caseNode, "caso-padrao", "CASO");
  treeNode* padraoNode = newTreeNode();
  fillTreeNode(padraoNode, "padrao", "CASO");
  caseNode -> children[0] = padraoNode; 
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 638 "compiler.y"
    {
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children [2] = pararNode;
}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 646 "compiler.y"
    {
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children[2] = pararNode;
}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 656 "compiler.y"
    {
// Em tipos_variaveis ira retornar o tipo de retorno da funcao, a qual sera acrescentada.
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
    
  returnFlag = 0;
}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 667 "compiler.y"
    {
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
    
  returnFlag = 0;
}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 677 "compiler.y"
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
      
      treeNode *aux = functionNode->children[1];
      treeNode *functionVariableNode = newTreeNode();
      char upperType[10];
      convertTypeReverseUpper(intVarType, upperType);
      fillTreeNode(functionVariableNode, currentIdentifier,upperType);
      if(functionNode->children[1] == NULL)
	functionNode->children[1] = functionVariableNode;
      else
      {
	while(functionNode->children[1]!=NULL)
	{
	  functionNode->children[1] = functionNode->children[1]->next;  
	}
	functionNode->children[1] = functionVariableNode;
	functionNode->children[1]= aux;
      }
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
#line 719 "compiler.y"
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
      
      treeNode *aux = functionNode->children[1];
      treeNode *functionVariableNode = newTreeNode();
      char upperType[10];
      convertTypeReverseUpper(intVarType, upperType);
      fillTreeNode(functionVariableNode, currentIdentifier,upperType);
      if(functionNode->children[1] == NULL)
      {
	functionNode->children[1] = functionVariableNode;
      }
      else
      {
	while(functionNode->children[1]->next!=NULL)
	  functionNode->children[1] = functionNode->children[1]->next;

	functionNode->children[1]->next = functionVariableNode;
	functionNode->children[1] = aux;
      }
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
#line 764 "compiler.y"
    {
  if(strcmp(currentScope, "main") != 0)
  {
    List* functionList = lookupStringFunction(hashFunction, currentScope);
    function* functionAux = ((function*)(functionList->info));
    if(functionAux->returnType==T_SEMRETORNO)
      printf("A funcao %s nao possui retorno.\n", currentScope);
    else
    {
      char auxVariable[100];
      strcpy(auxVariable, currentIdentifier);
      strcat(auxVariable, " ");
      strcat(auxVariable, currentScope);
      List* variableList = lookupStringVariable(hashVariables, auxVariable);
      if(variableList != NULL)
      {
	  variable* variableAux = ((variable*)(variableList->info));
	  if(variableAux -> used == 0)
	  {
	    printf("Variavel %s nao foi utilizada durante a funcao %s.\n", currentIdentifier, currentScope);
	  }
	  else if(variableAux->type!=functionAux->returnType)
	  {
	    printf("Variavel de retorno %s nao e compativel com o retorno da funcao %s.\n", currentIdentifier, currentScope);
	  }
	  else
	    returnFlag = 1;
      }
      else
	printf("Variavel %s nao foi declarada na funcao %s.\n", currentIdentifier, currentScope);
    }
  }
  else
  {
    printf("Nao pode utilizar o retorno dentro do programa principal");
  }
  
  strcpy(identifiers, "\0");
}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 804 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 805 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 807 "compiler.y"
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

  case 68:

/* Line 1806 of yacc.c  */
#line 818 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 820 "compiler.y"
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

  case 70:

/* Line 1806 of yacc.c  */
#line 832 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 834 "compiler.y"
    {

 //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
  
}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 842 "compiler.y"
    { 
  List *functionList = lookupStringFunction(hashFunction, currentFunction);
  if(functionList == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
  }
  else
  {
    if(argumentNumber != ((function*)(functionList->info))->arity)
    {  
      printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
    }
  
  }
  argumentNumber=0;
  /*
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
  */
}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 968 "compiler.y"
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

  case 75:

/* Line 1806 of yacc.c  */
#line 999 "compiler.y"
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

  case 77:

/* Line 1806 of yacc.c  */
#line 1014 "compiler.y"
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

  case 78:

/* Line 1806 of yacc.c  */
#line 1038 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(((variable*)(currVariable->info))->nLine <= currentNumber ){
			printf("Erro na linha %d, %s possui %d linhas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
		}
	}
}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1045 "compiler.y"
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

  case 81:

/* Line 1806 of yacc.c  */
#line 1061 "compiler.y"
    {  
  currentRelationComparison = 0;
  char auxVariable[100];
  if(strcmp(currentScope, "main") == 0)
    strcpy(auxVariable, currentIdentifier);
  else
  {
    strcpy(auxVariable, currentIdentifier);
    strcat(auxVariable, " ");
    strcat(auxVariable, currentScope);
  }
  
    List *identifier_temp = lookupStringVariable(hashVariables, auxVariable);
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
      
  strcpy(currentVariable, auxVariable);
}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1093 "compiler.y"
    {
    //adiciono o nó de expressão a direita do nó de atribuição
    attributionNode->children[1] = expressionNode;
    //retorno o nós de atribuição para null
    expressionNode=NULL;
    
    //adiciono o nó de atribuição na árvore de execução do programa (in main, falta fazer arvores para funções)
    //verifica que nao esta dentro de condicional tambem (enquanto ou se)
    addAttributionNodeIntoGlobalTree();

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

  case 83:

/* Line 1806 of yacc.c  */
#line 1197 "compiler.y"
    {
currentRelationComparison = 0;
}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1201 "compiler.y"
    {
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-se","CONDICIONAL");   
    addConditionNodeIntoGlobalTree();
    
    //retorno os nós de atribuição para null
    expressionNode = NULL;
}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1212 "compiler.y"
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

  case 86:

/* Line 1806 of yacc.c  */
#line 1226 "compiler.y"
    {currentRelationPos = 0;}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1227 "compiler.y"
    {
  commandNode = globalTree;
  conditionNode = commandNode -> children[0];
  commandNode->children[0] = NULL;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1236 "compiler.y"
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

  case 90:

/* Line 1806 of yacc.c  */
#line 1247 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1254 "compiler.y"
    {  
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-faca-enquanto","CONDICIONAL");
     conditionNode->children[0] = expressionNode;
     conditionNode->children[1] = commandNode;
     addConditionNodeIntoGlobalTree();
}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1262 "compiler.y"
    {in_condicional = 0;}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1264 "compiler.y"
    {
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-enquanto","CONDICIONAL");
    //seta para null o nó de expressão (que será construído na parte de expressão)
    expressionNode = NULL;
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1272 "compiler.y"
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

  case 96:

/* Line 1806 of yacc.c  */
#line 1289 "compiler.y"
    {in_condicional = 0; currentRelationPos = 0 ; strcpy(identifiers,"\0");}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1292 "compiler.y"
    {

  //commandNode = NULL;
  expressionNode = NULL;
  //conditionNode = NULL;

  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1304 "compiler.y"
    {
  conditionNode = newTreeNode();
  fillTreeNode(conditionNode,"condicao-para","CONDICAO");
  addConditionNodeIntoGlobalTree();

}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1310 "compiler.y"
    {strcpy(identifiers,"\0"); currentRelationPos=0;}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1311 "compiler.y"
    {
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,":=","ATRIBUICAO");
  
  treeNode *idAux = newTreeNode();
  fillTreeNode(idAux, currentIdentifier, "IDENTIFICADOR");
  //printf("%s", currentIdentifier);
  strcpy(currentVariable, currentIdentifier);
  attributionNode->children[0] = idAux;
  conditionNode->children[0] = attributionNode;
}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1323 "compiler.y"
    {
  attributionNode->children[1] = expressionNode;
  expressionNode = NULL;

}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1329 "compiler.y"
    {
  treeNode *idAux = newTreeNode();
  fillTreeNode(idAux, currentVariable, "IDENTIFICADOR");
  
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,"=","COMPARACAO");
  
  attributionNode->children[0] = idAux;
  attributionNode->children[1] = expressionNode;
  
  conditionNode->children[1] = attributionNode;
  
  expressionNode = NULL;
}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1344 "compiler.y"
    {
  treeNode *passoAux = newTreeNode();
  fillTreeNode(passoAux, "+", "SOMA");
  
  treeNode *idAux1 = newTreeNode();
  fillTreeNode(idAux1, currentVariable, "IDENTIFICADOR");
 
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,":=","ATRIBUICAO");

  treeNode *idAux2 = newTreeNode();
  fillTreeNode(idAux2, currentVariable, "IDENTIFICADOR");
  
  passoAux->children[0] = idAux1;
  passoAux->children[1] = expressionNode;
  
  attributionNode->children[1] = passoAux;
  attributionNode->children[0] = idAux2;
  
 /* 
  treeNode *idAux = newTreeNode();
  fillTreeNode(idAux, currentIdentifier, "IDENTIFICADOR");
  
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,":=","ATRIBUICAO");

  
  
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,":=","ATRIBUICAO");

  
   */
  conditionNode->children[2] = attributionNode;
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

  case 105:

/* Line 1806 of yacc.c  */
#line 1392 "compiler.y"
    {
if(!verifyRelationship(varRelations, currentRelationPos))
  {
    printf("Valores incompativeis na linha %d\n", nLine);
  }
strcpy(identifiers,"\0"); 
currentRelationPos = 0;
}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1401 "compiler.y"
    {
  expressionNode = NULL;
 
  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1409 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos=0;}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1410 "compiler.y"
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
    //if(in_function!=1)
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
    //if(in_function!=1)
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
    
    fillTreeNode(caseNode, "caso", "CASO");
    fillTreeNode(commandNode, "comando-caso", "COMANDO");
    
    conditionNode->children[1] = caseNode;
    caseNode->children[1] = commandNode;
    
    stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
    globalTree = commandNode;
    
    
    //retorno os nós de atribuição para null
    expressionNode = NULL;
    
    
    
}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1489 "compiler.y"
    {
if(varRelations[0] != T_LITERAL && varRelations[0] != T_LOGICO)
  switchType = varRelations[0];
else
  switchType = T_SEMRETORNO;
}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1498 "compiler.y"
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

  case 113:

/* Line 1806 of yacc.c  */
#line 1512 "compiler.y"
    {currentRelationPos=0;}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1513 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1521 "compiler.y"
    {in_logico = 1;}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1522 "compiler.y"
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

  case 119:

/* Line 1806 of yacc.c  */
#line 1549 "compiler.y"
    {in_logico = 1;}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1550 "compiler.y"
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

  case 122:

/* Line 1806 of yacc.c  */
#line 1578 "compiler.y"
    {
  List* functionList = lookupStringVariable(hashFunction, currentFunction);
  function* functionAux = ((function*)(functionList->info));
  List* aux = functionAux->parameters;
  argumentNumber++;
  if(argumentNumber <= functionAux->arity)
  {
    int returnTypeArgument = findArgumentType(argumentNumber, aux);
   
    //printf("%d %d\n", returnTypeArgument, varRelations[0]);

  if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
  {
    printf("Valores incompativeis na linha %d.\n", nLine);
  }
  else if(returnTypeArgument != varRelations[0] && in_comparacao == 0)
  {	
    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
  }
  }
  //strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  currentRelationComparison = 0;
 }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1604 "compiler.y"
    {
  List* functionList = lookupStringVariable(hashFunction, currentFunction);
  function* functionAux = ((function*)(functionList->info));
  List* aux = functionAux->parameters;
  argumentNumber++;

  if(argumentNumber <= functionAux->arity)
  {
  
   int returnTypeArgument = findArgumentType(argumentNumber, aux);

  //("%d %d\n", returnTypeArgument, varRelations[0]);
  if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
  {
    printf("Valores incompativeis na linha %d.\n", nLine);
  }
  else if(returnTypeArgument != varRelations[0] && in_comparacao == 0)
  {	
    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
  }
  }
  //strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  currentRelationComparison = 0;
}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1631 "compiler.y"
    { swapoutDoisUm(); swapoutTresDois(); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1633 "compiler.y"
    { swapoutDoisUm();swapoutTresDois(); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1634 "compiler.y"
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

  case 128:

/* Line 1806 of yacc.c  */
#line 1655 "compiler.y"
    {operadorDeNivelTres();}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1655 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1657 "compiler.y"
    { operadorDeNivelDois(">"); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1658 "compiler.y"
    { operadorDeNivelDois(">="); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1659 "compiler.y"
    { operadorDeNivelDois("="); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1660 "compiler.y"
    { operadorDeNivelDois("<"); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1661 "compiler.y"
    { operadorDeNivelDois("<="); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1662 "compiler.y"
    { operadorDeNivelDois("<>"); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1665 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1666 "compiler.y"
    { operadorDeNivelUm(); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1666 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1671 "compiler.y"
    {
  /*
  Convertendo tipo do numero real e adicionando no vetor de relacoes, por exemplo (varRelations = {0, 0, 0, 1, 2})
  O vetor sera usado mais tarde para fazer comparacao de tipos de maneira tal que apenas mesmos tipos podem realizar operacoes. 
  */
  //if(in_function!=1)
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

  case 143:

/* Line 1806 of yacc.c  */
#line 1719 "compiler.y"
    {
  //if(in_function!=1)
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

  case 146:

/* Line 1806 of yacc.c  */
#line 1765 "compiler.y"
    {	operadorDeNivelZero("/"); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1765 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1767 "compiler.y"
    { operadorDeNivelZero("%"); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1767 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1769 "compiler.y"
    { operadorDeNivelZero("*"); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1769 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1772 "compiler.y"
    {
  //if(in_function!=1)
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

  case 154:

/* Line 1806 of yacc.c  */
#line 1793 "compiler.y"
    {
  //if(in_function!=1)
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

  case 155:

/* Line 1806 of yacc.c  */
#line 1820 "compiler.y"
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
    //if(in_function!=1)
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
    //if(in_function!=1)
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

  case 156:

/* Line 1806 of yacc.c  */
#line 1891 "compiler.y"
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
    //if(in_function!=1)
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
    }
    //printf("identificador\n");
    }
    
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, ((variable*)(identifier_temp->info))->name, "VARIAVEL");
    treeNode* signalAux = newTreeNode();
    fillTreeNode(signalAux, "-", "OPERADOR-UNARIO");
	signalAux->children[0] = aux;
    if (expressionNode == NULL) {
      expressionNode = signalAux;
    }else{
    	expressionNode->children[1] = signalAux;
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
    //if(in_function!=1)
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      // printf("%d %s\n", currentTypeInt, currentIdentifier);
    }
    //printf("identificador\n");
    }
    
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, ((variable*)(identifier_temp->info))->name, "VARIAVEL");
    treeNode* signalAux = newTreeNode();
    fillTreeNode(signalAux, "-", "OPERADOR-UNARIO");
	signalAux->children[0] = aux;
    if (expressionNode == NULL) {
      expressionNode = signalAux;
    }else{
    	expressionNode->children[1] = signalAux;
    }
  
  }
  
  	
  
}
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1975 "compiler.y"
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
  	//monta a arvore
  	treeMatrixOneDimension( ((variable*)(identifier_temp->info))->name , currentNumber);
  	
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
      //if(in_function!=1)
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

  case 158:

/* Line 1806 of yacc.c  */
#line 2026 "compiler.y"
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
  	//monta a arvore com uma dimensão
  	treeMatrixOneDimension( ((variable*)(identifier_temp->info))->name , currentNumber);
  
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

  case 159:

/* Line 1806 of yacc.c  */
#line 2064 "compiler.y"
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
    	//completa a arvore com a segunda dimensão
    	char s[50];
    	sprintf(s,"%d",currentNumber);
    	treeNode *aux = newTreeNode();
	 	fillTreeNode(aux, s, "INTEIRO");
	 	//Se  children[1] for null estamos no nó do identificador, caso contrário estamos no nó do operador
	 	if(expressionNode->children[1] == NULL){
		 	expressionNode->children[1] = aux; 		
    	}else{
    		expressionNode->children[1]->children[1] = aux;
    	}
      if(((variable*)(identifier_temp->info))->nLine <= currentNumber )
      {
	printf("Erro na linha %d, %s possui %d linhas.\n", nLine, ((variable*)(identifier_temp->info))->name,((variable*)(identifier_temp->info))->nLine );
      }
      //else if(in_function!=1)
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

  case 160:

/* Line 1806 of yacc.c  */
#line 2111 "compiler.y"
    {
  //if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
  
}
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 2122 "compiler.y"
    {
  if(strlen(limitString) > MAX_LITERAL)
  {
    printf("Tamanho de literal passou do limite de 200 caracteres na linha %d\n", nLine);
  }
  else
  {
    //if(in_function!=1)
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
#line 2138 "compiler.y"
    {
	//crio o no parentesis
	treeNode *aux = newTreeNode();
	fillTreeNode(aux,"()", "PARENTESIS");
	if(expressionNode==NULL){
		expressionNode = aux;
	}else{
		expressionNode->children[1] = aux;
	}
	//coloco o nó atual de expressão na pilha e seto para null
	stackParentesis = addNodeIntoStack(expressionNode, stackParentesis);
	expressionNode = NULL;

}
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 2151 "compiler.y"
    {
	treeNode* aux = (treeNode*) popStack(stackParentesis);
	if(aux->children[0] == NULL){
		aux->children[0] = expressionNode;
	} else {
		aux->children[1]->children[0] = expressionNode; 
	}
	expressionNode = aux;	
}
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 2161 "compiler.y"
    {
  //if(in_function!=1)
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

  case 165:

/* Line 1806 of yacc.c  */
#line 2181 "compiler.y"
    {
  //if(in_function!=1)
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

  case 166:

/* Line 1806 of yacc.c  */
#line 2201 "compiler.y"
    {

  //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
  in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
  List *identifier_temp = lookupStringFunction(hashFunction, currentIdentifier);
  if(identifier_temp!=NULL)
  {
    //treeNode* functionNode = ((function*)(identifier_temp->info))->functionTree;
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

  case 167:

/* Line 1806 of yacc.c  */
#line 2286 "compiler.y"
    { 
  List *functionList = lookupStringFunction(hashFunction, currentFunction);
  if(functionList == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
  }
  else
  {
    if(argumentNumber != ((function*)(functionList->info))->arity)
    {  
      printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
    }
  
  }
  argumentNumber=0;
/*
  List *identifier_temp = lookupStringFunction(hashFunction, currentFunction);
  if(identifier_temp == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
  }
  else
  {
    int arity = numSpaces(functionArguments);
    printf("%d\n", arity);
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
      */
  strcpy(functionArguments, "\0");
  //strcpy(identifiers, "\0");
  //currentRelationPos = 0;
  in_function = 0;
  }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 2425 "compiler.y"
    {
  if(switchType != T_INTEIRO)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
  {
    treeNode* fatorAux = newTreeNode();
    fillTreeNode(fatorAux, yytext, "FATOR_CASE");
    
    caseNode->children[0] = fatorAux;
  }
}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 2438 "compiler.y"
    {
  if(switchType != T_REAL)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
    {
    treeNode* fatorAux = newTreeNode();
    fillTreeNode(fatorAux, yytext, "FATOR_CASE");
    
    caseNode->children[0] = fatorAux;
  }
  }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 2451 "compiler.y"
    {
  if(switchType != T_CARACTER)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
  }
    {
    treeNode* fatorAux = newTreeNode();
    fillTreeNode(fatorAux, yytext, "FATOR_CASE");
    
    caseNode->children[0] = fatorAux;
  }
}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 2464 "compiler.y"
    { countLine=0; delimitadorNivelUm(); tempDelimitadorNivelUm = expressionNode;  expressionNode=NULL; }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 2464 "compiler.y"
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
	expressionNode = tempDelimitadorNivelUm;
}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 2484 "compiler.y"
    {
	isMatrix = 1;
}
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 2488 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 2488 "compiler.y"
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

  case 177:

/* Line 1806 of yacc.c  */
#line 2507 "compiler.y"
    {
	isMatrix = 1; 
	expressionNode = tempDelimitadorNivelZero;
 }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 2511 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 2512 "compiler.y"
    {
	treeNode *auxList = tempDelimitadorNivelUm->children[0];
	while(auxList->next != NULL) auxList = auxList->next;
	auxList->next = tempDelimitadorNivelZero;
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

  case 181:

/* Line 1806 of yacc.c  */
#line 2534 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 2534 "compiler.y"
    {

	
	 tempDelimitadorNivelUm->children[0] = tempDelimitadorNivelZero;
	

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

  case 184:

/* Line 1806 of yacc.c  */
#line 2559 "compiler.y"
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
	
	//primeiro no da lista
	tempDelimitadorNivelZero->children[0] = expressionNode;
	expressionNode = NULL;
}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 2582 "compiler.y"
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
	
	//adiciona na lista
	treeNode* auxList = tempDelimitadorNivelZero->children[0];
	while(auxList->next != NULL) auxList = auxList->next;
	auxList->next = expressionNode;
	expressionNode = NULL;
//	printNode(tempDelimitadorNivelZero,13,0);
	
}
    break;



/* Line 1806 of yacc.c  */
#line 4930 "compiler.tab.c"
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
#line 2608 "compiler.y"


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

main()
{
      hashVariables = createHash(MAX_HASH);
      hashFunction = createHash(MAX_HASH);
      createPrimitives();
      yyparse(); 
 
     if(IN_DEBUG_MODE){
  	treeNode* aux = globalTree;

  	printNode(aux, 12, 0);
	printf("\n ---------- \n");
	printf(" ---------- \n");
      }

	//execute
	executeTree(globalTree);
	
 	//	List* l = lookupStringVariable(hashVariables, "c");
 	//	printf("c: %d\n", *( (int*) ( (variable*) l->info )->value) );
 		List* l = lookupStringVariable(hashVariables, "a");
 		printf("a: %d\n", *( (int*) ( (variable*) l->info )->value) );
 		l = lookupStringVariable(hashVariables, "b");
 		printf("b: %d\n", *( (int*) ( (variable*) l->info )->value) );
 	//	l = lookupStringVariable(hashVariables, "b");
	//	printf("b: %.2f\n", *( (double*) ( (variable*) l->info )->value) );
	//veriicando a matriz
	
	  //freeTable(hashVariables);
      //freeTableFunction(hashFunction);
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void)
{
	printf("Erro na Linha: %d\n", nLine);
}


