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
#include "program.h"

#define MAX_HASH 1000
#define MAX_VARIABLE 32 //maior nome de variavel
#define MAX_FUNCTION 32 //maior nome de funcao
#define MAX_LITERAL 50
#define IN_DEBUG_MODE 1

extern FILE* yyin;

extern int err;
extern int in_logico;
extern int in_comparacao;
extern int in_condicional;
extern int nLine;
extern int varRelations[50]; //Vetor que armazena relacoes de uma dada expressao
extern int currentNumber;
extern int isMatrix;

extern char* yytext;
extern char identifiers[10*MAX_VARIABLE];
extern char functionArguments[10*MAX_VARIABLE];
extern char currentType[10];
extern char currentIdentifier[MAX_VARIABLE];

char currentVariable[MAX_VARIABLE + MAX_FUNCTION + 2];
char currentScope[MAX_FUNCTION] = "main";
char currentFunction[MAX_FUNCTION];
char returnVariableGlobal[MAX_VARIABLE];
char limitString[50]; //limitador de tamanho de string no programa

int currentFunctionArity = 0;
int currentRelationPos = 0;
int currentRelationComparison = 0;
int switchType;
int countLine = 0;
int countColumn = 0;
int typeAttribute;
int dimension, dim1, dim2;
int returnFlag = 0;
int argumentNumber = 0;

List* currentParameters = NULL;
List* listPrograms = NULL;

hashTable* hashVariables = NULL;
hashTable* hashFunction = NULL;

Stack* stackParenthesis = NULL;
Stack* stackGlobal = NULL;
Stack* stackIfThenElse = NULL;
Stack* stackExpressionNode = NULL;
Stack* stackVariables = NULL;
Stack* stackVariablesAux = NULL;

treeNode* globalTree = NULL;
treeNode* expressionNode = NULL;
treeNode* attributionNode = NULL;
treeNode* conditionNode = NULL;
treeNode* commandNode = NULL;
treeNode* caseNode = NULL;
treeNode* functionNode = NULL;
treeNode* functionInternalVariables = NULL;

treeNode* swapZeroMenor = NULL;
treeNode* swapUmZero = NULL;
treeNode* swapDoisUm = NULL;
treeNode* swapTresDois = NULL;
treeNode* tempDelimitadorNivelZero = NULL;
treeNode* tempDelimitadorNivelUm = NULL;

/**
*	FUNÇÕES
**/

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

void operadorDeMenorNivel(char tipo[10]){
	if (!strcmp(expressionNode->type,"OPERADOR-N-0") || !strcmp(expressionNode->type,"OPERADOR-N-1") || !strcmp(expressionNode->type,"OPERADOR-N-2") || !strcmp(expressionNode->type,"OPERADOR-N-3")){
		swapZeroMenor = expressionNode;
		treeNode *aux = newTreeNode();
		fillTreeNode(aux, tipo, "OPERADOR-M-N");
		aux->children[0] = expressionNode->children[1];
		expressionNode->children[1] = aux;
		expressionNode = aux;
	}else{
		treeNode *aux = newTreeNode();
		fillTreeNode(aux, tipo, "OPERADOR-M-N");
		aux->children[0] = expressionNode;
		expressionNode = aux;
	}
}

void swapoutZeroMenor(){
	if (swapZeroMenor!=NULL){
		expressionNode = swapZeroMenor;
		swapZeroMenor=NULL;
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
#line 316 "compiler.tab.c"

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
     token_identificador = 338,
     token_circ = 339
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
#line 442 "compiler.tab.c"

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
#define YYLAST   401

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  114
/* YYNRULES -- Number of rules.  */
#define YYNRULES  195
/* YYNRULES -- Number of states.  */
#define YYNSTATES  357

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
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
     146,   155,   157,   158,   168,   175,   176,   184,   185,   194,
     195,   196,   208,   209,   219,   223,   229,   230,   231,   236,
     237,   244,   245,   252,   253,   260,   261,   268,   269,   270,
     278,   279,   280,   290,   291,   292,   293,   307,   308,   309,
     316,   317,   318,   319,   320,   332,   333,   334,   335,   336,
     349,   350,   351,   352,   353,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   395,   396,   397,   398,   407,   408,
     409,   415,   417,   418,   419,   423,   424,   425,   429,   431,
     435,   436,   438,   439,   444,   445,   450,   452,   454,   456,
     458,   460,   462,   464,   465,   470,   473,   475,   477,   479,
     481,   483,   485,   486,   491,   492,   493,   494,   501,   502,
     507,   508,   513,   515,   517,   519,   521,   524,   529,   530,
     539,   541,   543,   544,   549,   551,   553,   554,   560,   562,
     564,   566,   568,   569,   570,   576,   577,   578,   584,   585,
     586,   594,   595,   596,   602,   604
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      86,     0,    -1,    -1,    19,    83,     7,    87,    99,    89,
      38,    98,    30,    -1,    -1,    19,    83,     7,    88,    89,
      38,    98,    30,    -1,    62,    90,    34,    -1,    62,    34,
      -1,    -1,    92,     8,    91,     7,    -1,    90,    92,     8,
      91,     7,    -1,    39,    -1,    56,    -1,    21,    -1,    44,
      -1,    45,    -1,    93,    -1,    83,    -1,    92,     5,    83,
      -1,    -1,    -1,    47,    13,    18,    14,    13,    94,    18,
      95,    14,    24,    97,    -1,    -1,    47,    13,    18,    14,
      24,    96,    97,    -1,    40,    -1,    22,    -1,    43,    -1,
      55,    -1,    46,    -1,    -1,    98,   121,    -1,    98,    11,
      98,    12,    -1,    -1,    99,    35,    83,   100,   114,    -1,
      -1,    35,    83,   101,   114,    -1,    -1,   102,   121,    -1,
      11,   102,    12,    -1,    -1,   104,    -1,   121,    -1,   104,
     121,    -1,   183,    -1,    -1,   112,   107,   106,    -1,    -1,
     112,   108,   109,    -1,    -1,    -1,    51,   110,     8,   102,
      53,   111,     7,    60,    -1,    60,    -1,    -1,    23,     3,
     187,     4,     8,   102,    53,   113,     7,    -1,    23,     3,
     187,     4,     8,   102,    -1,    -1,     3,   120,     4,    38,
     115,   103,    30,    -1,    -1,     3,   120,     4,    90,   116,
      38,   103,    30,    -1,    -1,    -1,     3,   120,     4,     8,
      91,   117,    90,   118,    38,   103,    30,    -1,    -1,     3,
     120,     4,     8,    91,   119,    38,   103,    30,    -1,    83,
       8,    91,    -1,   120,     5,    83,     8,    91,    -1,    -1,
      -1,    57,   122,   168,     7,    -1,    -1,    36,     3,   105,
     123,     4,     7,    -1,    -1,    37,     3,   105,   124,     4,
       7,    -1,    -1,    41,     3,    83,   125,     4,     7,    -1,
      -1,    42,     3,    83,   126,     4,     7,    -1,    -1,    -1,
      83,   127,     3,   167,     4,   128,     7,    -1,    -1,    -1,
      83,    13,    18,    14,    71,   129,   168,   130,     7,    -1,
      -1,    -1,    -1,    83,    13,    18,    14,    13,   131,    18,
     132,    14,    71,   168,   133,     7,    -1,    -1,    -1,    83,
      71,   134,   168,   135,     7,    -1,    -1,    -1,    -1,    -1,
      58,   136,     3,   168,   137,     4,   138,    27,   102,   139,
     159,    -1,    -1,    -1,    -1,    -1,    28,   140,   102,   141,
       7,    26,     3,   168,   142,     4,   143,     7,    -1,    -1,
      -1,    -1,    -1,    26,     3,   144,   168,   145,     4,   146,
      28,   102,   147,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,   148,     3,   149,    83,   150,    24,
     183,   151,    20,   183,   152,    54,   183,   153,     4,   154,
      28,   102,   155,    32,    -1,    -1,    -1,    -1,    59,   156,
       3,    83,   157,     4,   158,   106,    -1,    -1,    -1,    61,
     160,   102,   161,    33,    -1,    33,    -1,    -1,    -1,   163,
     164,    25,    -1,    -1,    -1,   165,   166,    50,    -1,   168,
      -1,   167,     5,   168,    -1,    -1,   172,    -1,    -1,   168,
     171,   172,   169,    -1,    -1,   168,   162,   170,   172,    -1,
      72,    -1,    74,    -1,    76,    -1,    73,    -1,    75,    -1,
      77,    -1,   176,    -1,    -1,   172,   174,   173,   176,    -1,
     172,   175,    -1,    64,    -1,    65,    -1,    15,    -1,    17,
      -1,   188,    -1,   183,    -1,    -1,   176,    67,   177,   183,
      -1,    -1,    -1,    -1,   176,   178,    68,   179,   183,   180,
      -1,    -1,   176,    66,   181,   183,    -1,    -1,   176,    84,
     182,   183,    -1,   175,    -1,    18,    -1,    16,    -1,    83,
      -1,    65,    83,    -1,    83,    13,    18,    14,    -1,    -1,
      83,    13,    18,    14,    13,   184,    18,    14,    -1,    81,
      -1,    82,    -1,    -1,     3,   185,   168,     4,    -1,    63,
      -1,    29,    -1,    -1,    83,   186,     3,   167,     4,    -1,
     175,    -1,    18,    -1,    16,    -1,    81,    -1,    -1,    -1,
      11,   189,   193,   190,    12,    -1,    -1,    -1,    13,   191,
     198,   192,    14,    -1,    -1,    -1,   193,     5,    13,   194,
     198,   195,    14,    -1,    -1,    -1,    13,   196,   198,   197,
      14,    -1,   183,    -1,   198,     5,   183,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   331,   331,   331,   339,   338,   345,   346,   346,   348,
     416,   483,   483,   483,   483,   483,   483,   485,   485,   487,
     487,   487,   488,   488,   490,   490,   490,   490,   490,   492,
     492,   492,   494,   493,   550,   549,   604,   604,   604,   605,
     605,   606,   606,   608,   610,   609,   629,   628,   655,   663,
     654,   669,   672,   671,   677,   680,   679,   695,   694,   711,
     728,   710,   731,   730,   749,   791,   833,   836,   836,   889,
     888,   907,   906,   925,   924,   955,   954,   985,  1001,   984,
    1021,  1073,  1021,  1098,  1144,  1158,  1098,  1185,  1221,  1184,
    1332,  1343,  1358,  1359,  1331,  1368,  1379,  1386,  1394,  1367,
    1396,  1404,  1421,  1424,  1395,  1432,  1437,  1438,  1451,  1456,
    1471,  1505,  1515,  1431,  1521,  1522,  1593,  1521,  1602,  1616,
    1601,  1622,  1625,  1626,  1625,  1650,  1651,  1650,  1675,  1743,
    1823,  1824,  1826,  1826,  1848,  1848,  1850,  1851,  1852,  1853,
    1854,  1855,  1858,  1859,  1859,  1860,  1861,  1861,  1863,  1908,
    1951,  1951,  1953,  1953,  1956,  1963,  1964,  1955,  1973,  1973,
    1975,  1975,  1977,  1978,  1996,  2014,  2087,  2162,  2214,  2213,
    2304,  2320,  2349,  2349,  2383,  2399,  2417,  2416,  2570,  2570,
    2584,  2598,  2613,  2613,  2613,  2638,  2638,  2638,  2662,  2663,
    2662,  2686,  2686,  2685,  2711,  2734
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
  "token_circ", "$accept", "PROG", "$@1", "$@2", "BLOCO_VARIAVEIS",
  "VARIAVEIS", "TIPOS_VARIAVEIS", "VARIAVEIS_IDENTIFICADORES",
  "INICIALIZAR_MATRIZ", "$@3", "$@4", "$@5", "TIPOS_VARIAVEIS_MATRIZ",
  "BLOCO", "BLOCO_FUNCOES", "$@6", "$@7", "BLOCO_AUXILIAR", "BLOCO_FUNCAO",
  "REPETICAO_COMANDO", "BLOCO_IMPRIMA", "BLOCO_SWITCH", "$@8", "$@9",
  "FIM_BLOCO_SWITCH", "$@10", "$@11", "BLOCO_SWITCH_AUX", "$@12", "FUNCAO",
  "$@13", "$@14", "$@15", "$@16", "$@17", "VARIAVEIS_FUNCAO", "COMANDO",
  "$@18", "$@19", "$@20", "$@21", "$@22", "$@23", "$@24", "$@25", "$@26",
  "$@27", "$@28", "$@29", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35",
  "$@36", "$@37", "$@38", "$@39", "$@40", "$@41", "$@42", "$@43", "$@44",
  "$@45", "$@46", "$@47", "$@48", "$@49", "$@50", "$@51", "$@52", "$@53",
  "$@54", "BLOCO_SENAO_FIMSE", "$@55", "$@56", "LOGICOS", "$@57", "$@58",
  "$@59", "$@60", "ARGUMENTOS_FUNCAO", "EXPR", "$@61", "$@62",
  "COMPARACOES", "SIEXPR", "$@63", "ADICAO_SUBTRACAO", "SINALFATOR",
  "TERMO", "$@64", "$@65", "$@66", "$@67", "$@68", "$@69", "FATOR", "$@70",
  "$@71", "$@72", "FATOR_CASE", "MATRIZ", "$@73", "$@74", "$@75", "$@76",
  "MATRIZ_VARIAS_COLUNAS", "$@77", "$@78", "$@79", "$@80", "BLOCO_MATRIZ", 0
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
     335,   336,   337,   338,   339
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    87,    86,    88,    86,    89,    89,    89,    90,
      90,    91,    91,    91,    91,    91,    91,    92,    92,    94,
      95,    93,    96,    93,    97,    97,    97,    97,    97,    98,
      98,    98,   100,    99,   101,    99,   102,   102,   102,   103,
     103,   104,   104,   105,   107,   106,   108,   106,   110,   111,
     109,   109,   113,   112,   112,   115,   114,   116,   114,   117,
     118,   114,   119,   114,   120,   120,   120,   122,   121,   123,
     121,   124,   121,   125,   121,   126,   121,   127,   128,   121,
     129,   130,   121,   131,   132,   133,   121,   134,   135,   121,
     136,   137,   138,   139,   121,   140,   141,   142,   143,   121,
     144,   145,   146,   147,   121,   148,   149,   150,   151,   152,
     153,   154,   155,   121,   156,   157,   158,   121,   160,   161,
     159,   159,   163,   164,   162,   165,   166,   162,   167,   167,
     167,   168,   169,   168,   170,   168,   171,   171,   171,   171,
     171,   171,   172,   173,   172,   172,   174,   174,   175,   175,
     176,   176,   177,   176,   178,   179,   180,   176,   181,   176,
     182,   176,   183,   183,   183,   183,   183,   183,   184,   183,
     183,   183,   185,   183,   183,   183,   186,   183,   187,   187,
     187,   187,   189,   190,   188,   191,   192,   188,   194,   195,
     193,   196,   197,   193,   198,   198
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     8,     3,     2,     0,     4,
       5,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       0,    11,     0,     7,     1,     1,     1,     1,     1,     0,
       2,     4,     0,     5,     0,     4,     0,     2,     3,     0,
       1,     1,     2,     1,     0,     3,     0,     3,     0,     0,
       8,     1,     0,     9,     6,     0,     7,     0,     8,     0,
       0,    11,     0,     9,     3,     5,     0,     0,     4,     0,
       6,     0,     6,     0,     6,     0,     6,     0,     0,     7,
       0,     0,     9,     0,     0,     0,    13,     0,     0,     6,
       0,     0,     0,     0,    11,     0,     0,     0,     0,    12,
       0,     0,     0,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     8,     0,     0,
       5,     1,     0,     0,     3,     0,     0,     3,     1,     3,
       0,     1,     0,     4,     0,     4,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     2,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     0,     0,     6,     0,     4,
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
       0,    32,    29,     6,     0,     0,     0,     0,    66,    35,
       0,     0,     0,    18,    13,    11,    14,    15,     0,    12,
       0,    16,    29,     0,    95,     5,     0,     0,     0,     0,
     105,    67,    90,   114,    77,    30,     0,     0,    33,     3,
       0,     0,     9,     0,   100,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,     0,     0,     0,     0,
      10,     0,    31,     0,    36,    96,   172,   148,   164,   149,
     163,   175,   174,     0,   170,   171,   165,    69,   162,    43,
      71,    73,    75,   106,   182,   185,   122,   131,   142,   151,
     150,     0,     0,     0,     0,   130,    64,     0,    55,    57,
       0,     0,   101,     0,    37,     0,     0,   166,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,   136,   139,
     137,   140,   138,   141,   134,   123,   126,     0,   146,   147,
     143,   145,   158,   152,   160,     0,    91,   115,     0,    88,
       0,   128,    59,    39,     0,     0,    19,    22,     0,    38,
       0,   122,     0,   130,     0,     0,     0,     0,   107,   191,
     183,   194,   186,     0,     0,     0,   132,     0,     0,     0,
       0,   155,     0,     0,    83,    80,     0,    78,     0,     0,
       0,     0,    40,    41,    39,    65,     0,     0,   102,     0,
     173,   167,     0,    70,    72,    74,    76,     0,     0,     0,
       0,     0,     0,   135,   124,   127,   133,   144,   159,   153,
     161,     0,    92,   116,     0,     0,    89,     0,   129,    60,
      39,    56,    42,     0,    20,    25,    24,    26,    28,    27,
      23,     0,     0,   168,   177,     0,   192,   188,   184,   195,
     187,   156,     0,     0,    84,    81,    79,     0,     0,    58,
       0,    36,    97,     0,   108,     0,     0,   157,    36,     0,
     117,    46,     0,     0,    39,    63,     0,   103,     0,     0,
       0,   193,   189,    93,     0,     0,     0,     0,    82,     0,
       0,     0,    98,   169,     0,     0,     0,   180,   179,   181,
     178,     0,    45,    48,    51,    47,     0,    61,    21,   104,
       0,   109,   190,   121,   118,    94,     0,     0,    85,    99,
       0,    36,    36,    36,     0,     0,   119,    54,     0,    86,
     110,     0,    52,    49,     0,   120,     0,     0,   111,    53,
       0,     0,    50,    36,   112,     0,   113
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     7,    11,    17,    40,    18,    41,   206,
     270,   207,   250,    27,     9,    30,    20,    85,   201,   202,
      97,   280,   295,   296,   315,   327,   347,   281,   346,    29,
     163,   164,   199,   267,   200,    57,   124,    71,   130,   131,
     132,   133,    76,   237,   235,   283,   234,   282,   334,   114,
     196,    72,   192,   262,   306,    65,   125,   288,   320,    83,
     168,   251,   301,    70,   134,   217,   290,   330,   344,   351,
     355,    73,   193,   263,   325,   331,   341,   144,   145,   184,
     146,   185,   160,   161,   226,   183,   147,   107,   187,   150,
      98,   108,   189,   155,   231,   277,   188,   190,   109,   273,
     126,   129,   311,   110,   135,   220,   136,   222,   180,   276,
     305,   218,   275,   182
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -197
static const yytype_int16 yypact[] =
{
      17,   -41,    54,    61,  -197,    51,    69,    67,    49,     4,
     -16,    68,  -197,    53,   101,  -197,  -197,     0,   100,  -197,
     137,  -197,  -197,  -197,   125,    59,   122,   134,    63,  -197,
     137,   172,   122,  -197,  -197,  -197,  -197,  -197,   135,  -197,
     142,  -197,  -197,   148,  -197,  -197,   150,   151,   153,   154,
    -197,  -197,  -197,  -197,     1,  -197,   155,    56,  -197,  -197,
     165,   140,  -197,   234,  -197,   162,    14,    14,    91,    97,
     178,     8,   179,   181,   169,  -197,   185,   122,     2,   111,
    -197,   187,  -197,     8,   162,   318,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,   112,  -197,  -197,   124,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,    26,    -2,   -10,  -197,
    -197,     8,   116,   189,     8,     8,  -197,   122,  -197,   121,
     197,    22,    44,   206,  -197,   199,     8,  -197,   193,   204,
     208,   212,   215,   216,   138,   209,    14,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,     8,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,   157,    44,  -197,     7,    44,
      77,    44,   188,   318,   190,   122,  -197,  -197,   219,  -197,
     207,    37,   221,     8,   229,   230,   232,   233,  -197,  -197,
     236,  -197,   239,     8,   228,   211,    -2,     8,    14,    14,
      14,  -197,   250,   252,  -197,  -197,   259,  -197,     8,   121,
     235,   227,   318,  -197,   318,  -197,   249,   104,  -197,   265,
    -197,   261,   130,  -197,  -197,  -197,  -197,   253,    14,   266,
     268,    14,   264,    -2,  -197,  -197,  -197,   -10,  -197,  -197,
    -197,    14,  -197,  -197,   263,     8,  -197,   275,    44,   121,
     318,  -197,  -197,   254,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,   255,     8,  -197,  -197,    14,   239,  -197,  -197,  -197,
    -197,  -197,   258,   271,  -197,    44,  -197,   257,   267,  -197,
     273,   162,    44,   278,  -197,   286,    14,  -197,   162,   298,
    -197,   279,   291,   299,   318,  -197,   283,   318,   304,   295,
     292,  -197,   239,   318,    34,   271,    24,   240,  -197,   280,
     104,   282,  -197,  -197,    14,   308,    -6,  -197,  -197,  -197,
    -197,   319,  -197,  -197,  -197,  -197,     8,  -197,  -197,  -197,
     317,  -197,  -197,  -197,  -197,  -197,   320,   321,    44,  -197,
     276,   162,   162,   162,   326,    14,   318,   262,   290,  -197,
    -197,   301,  -197,  -197,   331,  -197,   329,   330,  -197,  -197,
     281,   297,  -197,   162,   318,   306,  -197
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -197,  -197,  -197,  -197,   341,   -71,   -24,   -12,  -197,  -197,
    -197,  -197,    39,    23,  -197,  -197,  -197,   -81,  -192,  -197,
     284,    45,  -197,  -197,  -197,  -197,  -197,  -197,  -197,   322,
    -197,  -197,  -197,  -197,  -197,  -197,   -25,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,   180,   -67,  -197,  -197,  -197,  -119,  -197,  -197,
     -98,   170,  -197,  -197,  -197,  -197,  -197,  -197,   -66,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -196
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -177
static const yytype_int16 yytable[] =
{
      99,    99,    55,   123,   106,    24,    55,   119,    60,   151,
     117,    86,   243,    87,    74,    89,   122,    86,    15,   104,
     194,   105,   256,    87,    88,    89,    90,   323,   186,    87,
      88,    89,    90,   137,    23,   166,     1,    91,    55,    13,
     118,   210,     3,    91,   156,    31,   167,   159,   268,    87,
     307,    89,   308,   116,     4,   324,   152,   153,  -154,   171,
      78,    79,   148,   149,   223,    63,    10,    16,     5,  -122,
     181,    92,    75,    93,   154,   313,  -125,    92,   195,    93,
     292,   197,   198,    16,   314,    16,    -2,  -125,   151,    94,
      95,    96,   299,   162,  -125,    94,    95,    96,   138,   139,
     140,   141,   142,   143,     8,    25,    19,    24,    26,   138,
     139,   140,   141,   142,   143,   309,   138,   139,   140,   141,
     142,   143,   228,   229,   230,   151,   245,  -176,   239,    10,
      25,   238,    12,    32,   254,   198,    21,   128,   203,    22,
      28,   205,    33,    34,   246,    42,    56,   247,    61,    62,
     248,    64,   181,    66,    67,   259,    68,    69,    81,   249,
      43,    35,    44,    77,    45,   261,    36,    37,   265,    38,
      46,    47,    80,    84,   101,    48,    49,   242,    39,   203,
     102,   103,   111,    42,   112,   272,    50,   113,   115,   274,
     287,    51,    52,    53,   120,   127,   310,   293,    43,   157,
      44,   121,    59,   158,    16,   165,   170,   173,    46,    47,
     181,   172,   174,    48,    49,   203,   175,    54,   169,   176,
     177,   178,   179,   208,    50,   191,   -62,    24,   204,    51,
      52,    53,    43,   209,    44,   211,   213,   214,   321,   215,
     216,   219,    46,    47,   221,    42,    82,    48,    49,   328,
     336,   337,   338,   224,   232,    54,   233,   241,    50,   203,
      43,   225,    44,    51,    52,    53,   236,   244,   252,   340,
      46,    47,   354,   240,   253,    48,    49,   255,   260,   257,
     258,   264,   266,   271,   269,   278,    50,   286,    43,    54,
      44,    51,    52,    53,   279,   284,   289,   285,    46,    47,
     291,   294,   -44,    48,    49,   297,   298,   300,   302,   303,
     317,   316,   304,   319,    50,   342,    43,    54,    44,    51,
      52,    53,   322,   326,   329,   353,    46,    47,   332,   333,
     335,    48,    49,   339,   345,   348,   349,   350,   356,   318,
     312,   352,    50,   343,    43,    54,    44,    51,    52,    53,
      14,   100,    58,   212,    46,    47,     0,   227,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,    54,     0,    51,    52,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-197))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      66,    67,    27,    84,    71,    17,    31,    78,    32,   107,
       8,     3,   204,    15,    13,    17,    83,     3,    34,    11,
      13,    13,   218,    15,    16,    17,    18,    33,   147,    15,
      16,    17,    18,     7,    34,    13,    19,    29,    63,    35,
      38,     4,    83,    29,   111,    22,    24,   114,   240,    15,
      16,    17,    18,    77,     0,    61,    66,    67,    68,   126,
       4,     5,    64,    65,   183,    42,    62,    83,     7,    25,
     136,    63,    71,    65,    84,    51,    50,    63,    71,    65,
     276,     4,     5,    83,    60,    83,    35,    50,   186,    81,
      82,    83,   284,   117,    50,    81,    82,    83,    72,    73,
      74,    75,    76,    77,    35,     5,    38,   119,     8,    72,
      73,    74,    75,    76,    77,    81,    72,    73,    74,    75,
      76,    77,   188,   189,   190,   223,    22,     3,   199,    62,
       5,   198,    83,     8,     4,     5,    83,    13,   163,    38,
       3,   165,    83,    21,    40,    11,    83,    43,    13,     7,
      46,     3,   218,     3,     3,   221,     3,     3,    18,    55,
      26,    39,    28,     8,    30,   231,    44,    45,   235,    47,
      36,    37,     7,    11,    83,    41,    42,   202,    56,   204,
      83,     3,     3,    11,     3,   252,    52,    18,     3,   255,
     271,    57,    58,    59,    83,    83,   294,   278,    26,    83,
      28,    14,    30,    14,    83,     8,     7,     3,    36,    37,
     276,    18,     4,    41,    42,   240,     4,    83,    12,     4,
       4,    83,    13,     4,    52,    68,    38,   239,    38,    57,
      58,    59,    26,    26,    28,    14,     7,     7,   304,     7,
       7,     5,    36,    37,     5,    11,    12,    41,    42,   316,
     331,   332,   333,    25,     4,    83,     4,    30,    52,   284,
      26,    50,    28,    57,    58,    59,     7,    18,     3,   335,
      36,    37,   353,    38,    13,    41,    42,    24,    14,    13,
      12,    18,     7,    28,    30,    27,    52,    14,    26,    83,
      28,    57,    58,    59,    23,    38,    18,    30,    36,    37,
      14,     3,    23,    41,    42,    14,     7,    24,     4,    14,
      30,    71,    20,    31,    52,    53,    26,    83,    28,    57,
      58,    59,    14,     4,     7,    28,    36,    37,     8,     8,
      54,    41,    42,     7,    33,     4,     7,     7,    32,   300,
     295,    60,    52,    53,    26,    83,    28,    57,    58,    59,
       9,    67,    30,   173,    36,    37,    -1,   187,    -1,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    83,    -1,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    86,    83,     0,     7,    87,    88,    35,    99,
      62,    89,    83,    35,    89,    34,    83,    90,    92,    38,
     101,    83,    38,    34,    92,     5,     8,    98,     3,   114,
     100,    98,     8,    83,    21,    39,    44,    45,    47,    56,
      91,    93,    11,    26,    28,    30,    36,    37,    41,    42,
      52,    57,    58,    59,    83,   121,    83,   120,   114,    30,
      91,    13,     7,    98,     3,   140,     3,     3,     3,     3,
     148,   122,   136,   156,    13,    71,   127,     8,     4,     5,
       7,    18,    12,   144,    11,   102,     3,    15,    16,    17,
      18,    29,    63,    65,    81,    82,    83,   105,   175,   183,
     105,    83,    83,     3,    11,    13,   168,   172,   176,   183,
     188,     3,     3,    18,   134,     3,    91,     8,    38,    90,
      83,    14,   168,   102,   121,   141,   185,    83,    13,   186,
     123,   124,   125,   126,   149,   189,   191,     7,    72,    73,
      74,    75,    76,    77,   162,   163,   165,   171,    64,    65,
     174,   175,    66,    67,    84,   178,   168,    83,    14,   168,
     167,   168,    91,   115,   116,     8,    13,    24,   145,    12,
       7,   168,    18,     3,     4,     4,     4,     4,    83,    13,
     193,   183,   198,   170,   164,   166,   172,   173,   181,   177,
     182,    68,   137,   157,    13,    71,   135,     4,     5,   117,
     119,   103,   104,   121,    38,    91,    94,    96,     4,    26,
       4,    14,   167,     7,     7,     7,     7,   150,   196,     5,
     190,     5,   192,   172,    25,    50,   169,   176,   183,   183,
     183,   179,     4,     4,   131,   129,     7,   128,   168,    90,
      38,    30,   121,   103,    18,    22,    40,    43,    46,    55,
      97,   146,     3,    13,     4,    24,   198,    13,    12,   183,
      14,   183,   138,   158,    18,   168,     7,   118,   103,    30,
      95,    28,   168,   184,   183,   197,   194,   180,    27,    23,
     106,   112,   132,   130,    38,    30,    14,   102,   142,    18,
     151,    14,   198,   102,     3,   107,   108,    14,     7,   103,
      24,   147,     4,    14,    20,   195,   139,    16,    18,    81,
     175,   187,   106,    51,    60,   109,    71,    30,    97,    31,
     143,   183,    14,    33,    61,   159,     4,   110,   168,     7,
     152,   160,     8,     8,   133,    54,   102,   102,   102,     7,
     183,   161,    53,    53,   153,    33,   113,   111,     4,     7,
       7,   154,    60,    28,   102,   155,    32
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
#line 331 "compiler.y"
    { strcpy(identifiers, "\0");}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 332 "compiler.y"
    {
  //verifyMatrix(hashVariables);
  //verifyUsed(hashVariables);

}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 339 "compiler.y"
    { strcpy(identifiers, "\0");}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 340 "compiler.y"
    {
 // verifyMatrix(hashVariables);
 // verifyUsed(hashVariables);
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 349 "compiler.y"
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
	  terminate();
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

	  treeNode* internalArgument = newTreeNode();
	  fillTreeNode(internalArgument, auxVariable, "VARIAVEL INTERNA FUNCAO");
	  if(functionInternalVariables==NULL)
	  {
	   functionInternalVariables=internalArgument; 
	  }
	  else
	  {
	    treeNode* auxInternalArgument = functionInternalVariables;
	    while(auxInternalArgument->next != NULL)
	      auxInternalArgument=auxInternalArgument->next;
	    auxInternalArgument->next = internalArgument;
	  }
	}
	else
	{
	  printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
	  terminate();
	}
	varName = strtok(NULL, " ");
      }
    }
  strcpy(identifiers, "\0");
  }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 417 "compiler.y"
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
		terminate();
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
	  
	  treeNode* internalArgument = newTreeNode();
	  fillTreeNode(internalArgument, auxVariable, "VARIAVEL INTERNA FUNCAO");
	  if(functionInternalVariables==NULL)
	  {
	   functionInternalVariables=internalArgument; 
	  }
	  else
	  {
	    treeNode* auxInternalArgument = functionInternalVariables;
	    while(auxInternalArgument->next != NULL)
	    auxInternalArgument=auxInternalArgument->next;
	    auxInternalArgument->next = internalArgument;
	  }
	} 
	else
	{
	  printf("Erro semantico na linha %d. Variavel %s redeclarada.\n", nLine, varName);
	  terminate();
	}
	varName = strtok(NULL, " ");
      }
    }
  strcpy(identifiers, "\0");
  }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 487 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 487 "compiler.y"
    {dim2 = currentNumber;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 487 "compiler.y"
    {dimension=2;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 488 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 488 "compiler.y"
    {dimension=1;}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 494 "compiler.y"
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
	fillTreeNode(returnNode, "TIPO RETORNO", "VOID");
	functionNode->children[0] = returnNode;
	//addNodeIntoGlobalTree(functionNode);
	
	commandNode = newTreeNode();
	fillTreeNode(commandNode, "comando-funcao", "COMANDO");
	stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
	globalTree = commandNode;
	expressionNode = NULL;
	functionNode->children[3] = commandNode;
    }
    else
    {
      printf("Erro semantico na linha %d. Funcao %s redeclarada.\n", nLine, currentIdentifier);
      terminate();
      destroyList(currentParameters);
    }
  strcpy(identifiers, "\0");
}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 529 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope); //Procurando funcao dentro da hash de funcoes
  if(identifier_temp!=NULL)
  {
    function* functionAux = ((function*)(identifier_temp->info));

    if(functionAux->returnType!=T_SEMRETORNO)
    {
      if(returnFlag == 0)
      {
		printf("Funcao %s precisa de retorno e nao possui.\n", currentScope);
		terminate();
      }
    }
  }
  currentFunctionArity = 0; //Variavel global de aridade retornando ao valor 0.
  strcpy(currentScope, "main"); //Escopo retornando ao valor global
  returnFlag = 0;	//Flag de retorno retornando ao valor original
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 550 "compiler.y"
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
	fillTreeNode(returnNode, "TIPO RETORNO","VOID");
	functionNode->children[0] = returnNode;
	//addNodeIntoGlobalTree(functionNode);
	
	commandNode = newTreeNode();
	fillTreeNode(commandNode, "comando-funcao", "COMANDO");
	stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
	globalTree = commandNode;
	functionNode->children[3] = commandNode;
	expressionNode = NULL;
    }
    else
    {
      printf("Erro semantico na linha %d. Funcao %s redeclarada.\n", nLine, currentIdentifier);
      terminate();
    }
  strcpy(identifiers, "\0");
}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 584 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope);
  if(identifier_temp!=NULL)
  {
    function* functionAux = ((function*)(identifier_temp->info));
    //Adicionando versao inversa da lista para facilitar mais tarde
    if(functionAux->returnType!=T_SEMRETORNO)
    {
      if(returnFlag == 0)
      {
		printf("Funcao %s precisa de retorno e nao possui.\n", currentScope);
		terminate();
      }
    }
  }
  strcpy(currentScope, "main");
  returnFlag = 0;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 610 "compiler.y"
    {
  treeNode* caseNodeAux = newTreeNode();
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  
  commandNode = newTreeNode();
  fillTreeNode(commandNode, "comando-caso", "COMANDO");
  fillTreeNode(caseNodeAux, "caso", "CASO");
  
  caseNode->next = caseNodeAux;
  caseNode = caseNodeAux;
  caseNode->children[1] = commandNode;
  
  stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
  globalTree = commandNode; 
  expressionNode = NULL;
}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 629 "compiler.y"
    {
  treeNode* caseNodeAux = newTreeNode();
    
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  
  commandNode = newTreeNode();
  fillTreeNode(commandNode, "comando-caso", "COMANDO");
  fillTreeNode(caseNodeAux, "caso", "CASO");
  
  caseNode->next = caseNodeAux;
  caseNode = caseNodeAux;
 
  caseNode->children[1] = commandNode;
  stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
  globalTree = commandNode;
  expressionNode = NULL;
}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 648 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 655 "compiler.y"
    {
  fillTreeNode(caseNode, "caso-padrao", "CASO");
  treeNode* padraoNode = newTreeNode();
  fillTreeNode(padraoNode, "padrao", "CASO");
  caseNode -> children[0] = padraoNode; 
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 663 "compiler.y"
    {
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children [2] = pararNode;
}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 672 "compiler.y"
    {
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children[2] = pararNode;
}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 680 "compiler.y"
    {
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope);
  if(identifier_temp!=NULL)
  {
    function* functionAux = ((function*)(identifier_temp->info));
    functionAux->arity = currentFunctionArity;
      currentFunctionArity = 0;

    currentParameters = reverseList(currentParameters);
    functionAux->parameters=currentParameters;
    currentParameters = startList();
  }
}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 695 "compiler.y"
    {
functionNode->children[2] = functionInternalVariables;
List *identifier_temp = lookupStringFunction(hashFunction, currentScope);
if(identifier_temp!=NULL)
  {
    function* functionAux = ((function*)(identifier_temp->info));    
    functionAux->arity = currentFunctionArity;
    currentFunctionArity = 0;

    currentParameters = reverseList(currentParameters);
    functionAux->parameters=currentParameters;
    currentParameters = startList();
  }
}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 711 "compiler.y"
    {
// Em tipos_variaveis ira retornar o tipo de retorno da funcao, a qual sera acrescentada.
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
  {
    ((function*)(aux->info))->returnType = convertType(currentType);
    convertTypeReverseUpper(convertType(currentType),functionNode->children[0]->type);  
    function* functionAux = ((function*)(aux->info));
    functionAux->arity = currentFunctionArity;
    currentFunctionArity = 0;
      
    currentParameters = reverseList(currentParameters);
    functionAux->parameters=currentParameters;
    currentParameters = startList();
  }
  returnFlag = 0;
}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 728 "compiler.y"
    {functionNode->children[2] = functionInternalVariables;}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 731 "compiler.y"
    {
/*Retorno sera verificado aqui em todas as funcoes com mesmo nome!*/
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
  {
    ((function*)(aux->info))->returnType = convertType(currentType);
    convertTypeReverseUpper(convertType(currentType),functionNode->children[0]->type);
    function* functionAux = ((function*)(aux->info));
    functionAux->arity = currentFunctionArity;
    currentFunctionArity = 0;
    currentParameters = reverseList(currentParameters);
    functionAux->parameters=currentParameters;
    currentParameters = startList();
   }
  returnFlag = 0;
}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 750 "compiler.y"
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
      fillTreeNode(functionVariableNode, varName,upperType);
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
      terminate();
    }
  strcpy(identifiers, "\0");
}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 792 "compiler.y"
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
      fillTreeNode(functionVariableNode, varName,upperType);
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
      terminate();
    }
  strcpy(identifiers, "\0");
}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 836 "compiler.y"
    {expressionNode=NULL; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 837 "compiler.y"
    {
  if(strcmp(currentScope, "main") != 0)
  {
    List* functionList = lookupStringFunction(hashFunction, currentScope);
    function* functionAux = ((function*)(functionList->info));
    if(functionAux->returnType==T_SEMRETORNO)
    {
      printf("A funcao %s nao possui retorno.\n", currentScope);
      terminate();
    }
    else
    {
      treeNode *returnNode = newTreeNode();
      fillTreeNode(returnNode, "RETORNO FUNCAO", "RETORNO FUNCAO");
      returnNode->children[0] = expressionNode; 
      addNodeIntoGlobalTree(returnNode);
      if(in_logico==1 && in_condicional == 0)
      {
	  if(functionAux->returnType != 4)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	    terminate();
	  }
	  in_logico=0;
      }
      else if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
      {
	printf("Tipos nao compativeis no retorno na funcao %s na linha %d\n", currentScope, nLine);
	terminate();
      }
      else if( functionAux->returnType != varRelations[0] && in_comparacao == 0)
      {
	printf("Expressao de retorno nao e compativel com o retorno da funcao %s na linha %d.\n", currentScope, nLine);
	terminate();
      }
      else
      {
	returnFlag = 1;
      }
    }
  }
  else
  {
    printf("Nao pode utilizar o retorno dentro do programa principal");
    terminate();
  }
  currentRelationPos = 0;
  expressionNode=NULL;
  strcpy(identifiers, "\0");
}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 889 "compiler.y"
    {
  treeNode* imprimaNode = newTreeNode();
  char typeImprima[10];
  
  convertTypeReverseUpper(convertType(currentType), typeImprima);
  fillTreeNode(imprimaNode,"CHAMADA FUNCAO", "imprima");
  
  treeNode* imprimaNodeChildren0 = newTreeNode();
  fillTreeNode(imprimaNodeChildren0, "RETORNO", "VOID");	  

  imprimaNode->children[0] = imprimaNodeChildren0;
  imprimaNode->children[1] = expressionNode;
	  
  addNodeIntoGlobalTree(imprimaNode);
  expressionNode = NULL;
}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 905 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 907 "compiler.y"
    {
  treeNode* imprimaNode = newTreeNode();
  
  char typeImprima[10];
  convertTypeReverseUpper(convertType(currentType), typeImprima);
  fillTreeNode(imprimaNode,"CHAMADA FUNCAO" , "imprimaln");
	  
  treeNode* imprimaNodeChildren0 = newTreeNode();
  fillTreeNode(imprimaNodeChildren0, "RETORNO", "VOID");
  
  imprimaNode->children[0] = imprimaNodeChildren0;
  imprimaNode->children[1] = expressionNode;
	  
  addNodeIntoGlobalTree(imprimaNode);
  expressionNode = NULL;
}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 923 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 925 "compiler.y"
    {
  List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
  if(identifier_temp==NULL)
  {
    printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
    terminate();
  } 
  else
  {
    variable* auxVariable =  ((variable*)(identifier_temp->info));
    auxVariable->used = 1;
    treeNode* leiaNode = newTreeNode();
    char typeLeia[10];
    convertTypeReverseUpper(auxVariable->type, typeLeia);
    fillTreeNode(leiaNode,"CHAMADA FUNCAO" , "leia");
	  
    treeNode* leiaNodeChildren0 = newTreeNode();
    treeNode* leiaNodeChildren1 = newTreeNode();
    fillTreeNode(leiaNodeChildren0, "RETORNO", typeLeia);
    fillTreeNode(leiaNodeChildren1,auxVariable->name, "VARIAVEL RETORNO");
	  
    leiaNode->children[0] = leiaNodeChildren0;
    leiaNode->children[1] = leiaNodeChildren1;
	  
    addNodeIntoGlobalTree(leiaNode);
  }
  expressionNode = NULL;
}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 953 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 955 "compiler.y"
    {
  List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
  if(identifier_temp==NULL)
  {
    printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
    terminate();
  } 
  else
  {
    variable* auxVariable =  ((variable*)(identifier_temp->info));
    auxVariable->used = 1;
    treeNode* leiaNode = newTreeNode();
    char typeLeia[10];
    convertTypeReverseUpper(auxVariable->type, typeLeia);
    fillTreeNode(leiaNode,"CHAMADA FUNCAO" , "leialn");
	  
    treeNode* leiaNodeChildren0 = newTreeNode();
    treeNode* leiaNodeChildren1 = newTreeNode();
    fillTreeNode(leiaNodeChildren0, "RETORNO", typeLeia);
    fillTreeNode(leiaNodeChildren1,auxVariable->name, "VARIAVEL RETORNO");
	  
    leiaNode->children[0] = leiaNodeChildren0;
    leiaNode->children[1] = leiaNodeChildren1;
	  
    addNodeIntoGlobalTree(leiaNode);
  }
    expressionNode = NULL;
}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 983 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 985 "compiler.y"
    {
  strcpy(currentFunction, currentIdentifier);
  List *functionList = lookupStringFunction(hashFunction, currentFunction);
  if(functionList!=NULL)
  {
    function* functionAux = ((function*)(functionList)->info);
    functionNode = newTreeNode();
    fillTreeNode(functionNode, currentFunction, "CHAMADA FUNCAO");
    treeNode* auxFunctionNode = newTreeNode();
    copyTreeNodes(auxFunctionNode, functionAux -> functionTree);
    functionNode->children[0] = auxFunctionNode;
    functionNode->children[0]->children[3] = NULL;
    expressionNode = NULL;
  }
}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1001 "compiler.y"
    { 
  List *functionList = lookupStringFunction(hashFunction, currentFunction);
  if(functionList == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
    terminate();
  }
  else
  {
    if(argumentNumber != ((function*)(functionList->info))->arity)
    {  
      printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
      terminate();
    }
  
  }
  argumentNumber=0;
addNodeIntoGlobalTree(functionNode);  
}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1021 "compiler.y"
    {
	strcpy(currentVariable, currentIdentifier);
	if (strcmp(currentScope, "main")!=0 ){
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
	}
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){\
		if(((variable*)(currVariable->info))->used!=1 && ((variable*)(currVariable->info))->matrix==0){
			printf("Erro, variavel nao inicializada na linha %d.\n", nLine);
			terminate();
		}
		if(((variable*)(currVariable->info))->matrix!=1){
			printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(currVariable->info))->name);
			terminate();
		}
		if(((variable*)(currVariable->info))->dimension != 1){
			printf("Erro na linha %d, %s possui dimensao 2.\n", nLine, ((variable*)(currVariable->info))->name);
			terminate();
		}
		if(((variable*)(currVariable->info))->nColumn <= currentNumber ){
			printf("Erro na linha %d, %s possui %d posicoes.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
			terminate();
		}
		else
		{
		   int currentTypeInt = ((variable *)(currVariable->info))->type;
		  // printf("%d \n", currentTypeInt);
		  varRelations[currentRelationPos] = currentTypeInt;
		  ++currentRelationPos;
		  ++currentRelationComparison;
		  
		  //cria o nó da arvore de atribuição
		  attributionNode = newTreeNode();
		  fillTreeNode(attributionNode,yytext,"ATRIBUICAO");
		  //cria o nó do identificador e insere a esquerda da atribuição
		  treeNode *idAux = newTreeNode();
		  fillTreeNode(idAux, currentIdentifier, "MATRIZ");
		  attributionNode->children[0] = idAux;
		  //cria o no com o valor da coluna acessada
		  char s[50];
		  sprintf(s,"%d",currentNumber);
		  treeNode *numCol = newTreeNode();
		  fillTreeNode(numCol,s,"INTEIRO");
		  idAux->children[0] = numCol;
		  //seta para null o nó de expressão (que será construído na parte de expressão)
		  expressionNode = NULL;  
		}
	}else{
		printf("Variavel nao declarada na linha %d\n",nLine);
		terminate();
	}
}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1073 "compiler.y"
    {

    //adiciono o nó de expressão a direita do nó de atribuição
    attributionNode->children[1] = expressionNode;
    //retorno o nós de atribuição para null
    expressionNode=NULL;
    //adiciono o nó de atribuição na árvore de execução do programa (in main, falta fazer arvores para funções)
    //verifica que nao esta dentro de condicional tambem (enquanto ou se)
    addNodeIntoGlobalTree(attributionNode);

	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(!verifyRelationship(varRelations, currentRelationPos))
		{
		  printf("Tipos incompativeis na linha %d\n", nLine);
		  terminate();
		}
		else if(((variable*)(currVariable->info))->type!=varRelations[0]){
			printf("Atribuição de tipos invalidos na linha %d.\n", nLine);
			terminate();
		}
	}
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1098 "compiler.y"
    {
	strcpy(currentVariable, currentIdentifier);
	if (strcmp(currentScope, "main")!=0 ){
		strcat(currentVariable, " ");
		strcat(currentVariable, currentScope);
	}
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(((variable*)(currVariable->info))->used!=1 && ((variable*)(currVariable->info))->matrix==0){
			printf("Erro, variavel nao inicializada na linha %d.\n", nLine);
			terminate();
		}
		if(((variable*)(currVariable->info))->matrix!=1){
			printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(currVariable->info))->name);
			terminate();
		}
		if(((variable*)(currVariable->info))->dimension != 2){
			printf("Erro na linha %d, %s possui dimensao 1.\n", nLine, ((variable*)(currVariable->info))->name);
			terminate();
		}
		if(((variable*)(currVariable->info))->nColumn <= currentNumber ){
			printf("Erro na linha %d, %s possui %d colunas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
			terminate();
		}
		
		  //cria o nó da arvore de atribuição
		  attributionNode = newTreeNode();
		  fillTreeNode(attributionNode,":=","ATRIBUICAO");
		  //cria o nó do identificador e insere a esquerda da atribuição
		  treeNode *idAux = newTreeNode();
		  fillTreeNode(idAux, currentIdentifier, "MATRIZ");
		  attributionNode->children[0] = idAux;
		  //cria o no com o valor da coluna acessada
		  char s[50];
		  sprintf(s,"%d",currentNumber);
		  treeNode *numCol = newTreeNode();
		  fillTreeNode(numCol,s,"INTEIRO");
		  idAux->children[0] = numCol;
		  //seta para null o nó de expressão (que será construído na parte de expressão)
		  expressionNode = NULL;
		
	}else{
		printf("Variavel nao declarada na linha %d.\n",nLine);
		terminate();
	}
}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1144 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(((variable*)(currVariable->info))->nLine <= currentNumber ){
			printf("Erro na linha %d, %s possui %d linhas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
			terminate();
		}
		  //cria o no com o valor da linha acessada
		  char s[50];
    	  sprintf(s,"%d",currentNumber);
		  treeNode *numLin = newTreeNode();
		  fillTreeNode(numLin,s,"INTEIRO");
		  attributionNode->children[0]->children[1] = numLin;
	}
}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1158 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
	
	//adiciono o nó de expressão a direita do nó de atribuição
    	attributionNode->children[1] = expressionNode;
    	//retorno o nós de atribuição para null
    	expressionNode=NULL;
    
    	//adiciono o nó de atribuição na árvore de execução do programa (in main, falta fazer arvores para funções)
    	//verifica que nao esta dentro de condicional tambem (enquanto ou se)
    	addNodeIntoGlobalTree(attributionNode);
    	
		if(!verifyRelationship(varRelations, currentRelationPos))
		{
		  printf("Tipos incompativeis na linha %d.\n", nLine);
		  terminate();
		}
		else if(((variable*)(currVariable->info))->type!=varRelations[0]){
			printf("Atribuição de tipos invalidos na linha %d.\n", nLine);
			terminate();
		}
	}
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1185 "compiler.y"
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
      strcpy(returnVariableGlobal, auxVariable);
      typeAttribute = ((variable *)(identifier_temp->info))->type;  
      //cria o nó da arvore de atribuição
      attributionNode = newTreeNode();
      fillTreeNode(attributionNode,yytext,"ATRIBUICAO");
      //cria o nó do identificador e insere a esquerda da atribuição
      treeNode *idAux = newTreeNode();
      fillTreeNode(idAux, auxVariable, "VARIAVEL");
      attributionNode->children[0] = idAux;
      //seta para null o nó de expressão (que será construído na parte de expressão)
      expressionNode = NULL;
    }
    else
    {
      printf("Variavel %s na linha %d nao foi declarada.\n", currentIdentifier, nLine);
      terminate();
    }
      
  strcpy(currentVariable, auxVariable);
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1221 "compiler.y"
    {
    //adiciono o nó de expressão a direita do nó de atribuição
    attributionNode->children[1] = expressionNode;
    //retorno o nós de atribuição para null
    expressionNode=NULL;
    //adiciono o nó de atribuição na árvore de execução do programa (in main, falta fazer arvores para funções)
    //verifica que nao esta dentro de condicional tambem (enquanto ou se)
    addNodeIntoGlobalTree(attributionNode);
    if(strcmp(currentScope, "main") == 0)
    { 
      char* returnVariable = returnVariableGlobal;
      if (returnVariable != NULL)
      { 
	List *identifier_temp = lookupStringVariable(hashVariables, returnVariable);

	if(identifier_temp==NULL)
	{
	  printf("Variavel %s nao declarada na linha %d.\n",returnVariable, nLine);
	  terminate();
	} 
	else if((varRelations[0] == T_LITERAL || varRelations[0] == T_CARACTER) && currentRelationPos > 1) //caracter ou literal
	{
	  printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	  terminate();
	}
	else if(in_logico==1 && in_condicional == 0)
	{
	  if((((variable*)(identifier_temp->info))->type) != 4)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	    terminate();
	  }
	  else
	    ((variable*)(identifier_temp->info))->used=1;
	  in_logico=0;
	}
	else if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
	{
	  printf("Valores incompativeis na linha %d.\n", nLine);
	  terminate();
	}
	//TODO
	else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0 && ((variable*)(identifier_temp->info))->type != 4)
	{	
	  printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  terminate();
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
	if(!verifyRelationship(varRelations, currentRelationPos))
	{
	  printf("Valores incompativeis na linha %d.\n", nLine);
	  terminate();
	}
	else
	{
	  strcat(auxVariable, " ");
	  strcat(auxVariable, currentScope);
	  List *identifier_temp = lookupStringVariable(hashVariables, auxVariable);
	  if(identifier_temp == NULL)
	  {
	    printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
	    terminate();
	  }
	  else if((varRelations[0] == T_CARACTER || varRelations[0] == T_LITERAL) && currentRelationPos > 1) //caracter ou literal
	  {
	    printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	    terminate();
	  }
	  else if(in_logico==1 && in_condicional == 0)
	  {
	    if((((variable*)(identifier_temp->info))->type) != 4)
	    {
	      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	      terminate();
	    }
	    else
	      ((variable*)(identifier_temp->info))->used=1;
	  in_logico=0;
	  }
	  else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	    terminate();
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
#line 1328 "compiler.y"
    {
currentRelationComparison = 0;
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1332 "compiler.y"
    {
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-se","CONDICIONAL");   
    addNodeIntoGlobalTree(conditionNode);
    
    //retorno os nós de atribuição para null
    expressionNode = NULL;
}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1343 "compiler.y"
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
  expressionNode = NULL;
}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1358 "compiler.y"
    {currentRelationPos = 0;}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1359 "compiler.y"
    {
  commandNode = globalTree;
  conditionNode = commandNode -> children[0];
  commandNode->children[0] = NULL;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1368 "compiler.y"
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

  case 96:

/* Line 1806 of yacc.c  */
#line 1379 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1386 "compiler.y"
    {  
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-faca-enquanto","CONDICIONAL");
    conditionNode->children[0] = expressionNode;
    conditionNode->children[1] = commandNode;
    addNodeIntoGlobalTree(conditionNode);
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1394 "compiler.y"
    {in_condicional = 0;}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1396 "compiler.y"
    {
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-enquanto","CONDICIONAL");
    //seta para null o nó de expressão (que será construído na parte de expressão)
    expressionNode = NULL;
}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1404 "compiler.y"
    {
    //adiciono o nó de expressão a direita do nó de condicao
    conditionNode->children[0] = expressionNode;
    commandNode = newTreeNode();
    
    //adiciona o no de comando a direita
    fillTreeNode(commandNode, "comando-enquanto", "COMANDO");
    conditionNode->children[1] = commandNode;
    addNodeIntoGlobalTree(conditionNode);
    
    //adicionando no global no stack, para ser recuperado depois
    stackGlobal = addNodeIntoStack(globalTree, stackGlobal);
    //mudando no global para o comando
    globalTree = commandNode;
    //retorno os nós de atribuição para null
    expressionNode = NULL;
}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1421 "compiler.y"
    {in_condicional = 0; currentRelationPos = 0 ; strcpy(identifiers,"\0");}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1424 "compiler.y"
    {
  expressionNode = NULL;

  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1432 "compiler.y"
    {
  conditionNode = newTreeNode();
  fillTreeNode(conditionNode,"condicao-para","CONDICAO");
  addNodeIntoGlobalTree(conditionNode);
}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1437 "compiler.y"
    {strcpy(identifiers,"\0"); currentRelationPos=0;}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1438 "compiler.y"
    {
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,":=","ATRIBUICAO");
  
  treeNode *idAux = newTreeNode();
  fillTreeNode(idAux, currentIdentifier, "VARIAVEL");

  strcpy(currentVariable, currentIdentifier);
  attributionNode->children[0] = idAux;
  conditionNode->children[0] = attributionNode;
  expressionNode = NULL;
}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1451 "compiler.y"
    {
  attributionNode->children[1] = expressionNode;
  expressionNode = NULL;
}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1456 "compiler.y"
    {
  treeNode *idAux = newTreeNode();
  fillTreeNode(idAux, currentVariable, "VARIAVEL");
  
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,"=","COMPARACAO");
  
  attributionNode->children[0] = idAux;
  attributionNode->children[1] = expressionNode;
  
  conditionNode->children[1] = attributionNode;
  
  expressionNode = NULL;
}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1471 "compiler.y"
    {
  treeNode *passoAux = newTreeNode();
  fillTreeNode(passoAux, "+", "SOMA");
  
  treeNode *idAux1 = newTreeNode();
  fillTreeNode(idAux1, currentVariable, "VARIAVEL");
 
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,":=","ATRIBUICAO");

  treeNode *idAux2 = newTreeNode();
  fillTreeNode(idAux2, currentVariable, "VARIAVEL");
  
  passoAux->children[0] = idAux1;
  passoAux->children[1] = expressionNode;
  
  attributionNode->children[1] = passoAux;
  attributionNode->children[0] = idAux2;
  
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

  case 111:

/* Line 1806 of yacc.c  */
#line 1505 "compiler.y"
    {
if(!verifyRelationship(varRelations, currentRelationPos))
  {
    printf("Valores incompativeis na linha %d\n", nLine);
    terminate();
  }
strcpy(identifiers,"\0"); 
currentRelationPos = 0;
}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1515 "compiler.y"
    {
  expressionNode = NULL;
  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1521 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos=0;}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1522 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else
    {  
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
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
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 &&((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else
    {  
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
    }
  }
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-seleciona","CONDICIONAL");
    
    treeNode* idAux = newTreeNode();
    fillTreeNode(idAux, currentIdentifier, "VARIAVEL");
    
    conditionNode->children[0] = idAux;
    addNodeIntoGlobalTree(conditionNode);
    
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

  case 116:

/* Line 1806 of yacc.c  */
#line 1593 "compiler.y"
    {
if(varRelations[0] != T_LITERAL && varRelations[0] != T_LOGICO)
  switchType = varRelations[0];
else
  switchType = T_SEMRETORNO;
}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1602 "compiler.y"
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

  case 119:

/* Line 1806 of yacc.c  */
#line 1616 "compiler.y"
    {currentRelationPos=0;}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1617 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1625 "compiler.y"
    {in_logico = 1;}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1626 "compiler.y"
    {
  if (in_comparacao = 1 && in_condicional == 0)
  {	
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate();
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
  else if (in_condicional == 1)
  {	
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate();
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1650 "compiler.y"
    {in_logico = 1;}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1651 "compiler.y"
    {
  if (in_comparacao = 1 && in_condicional == 0)
  {	
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate();
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
    else if (in_condicional == 1)
  {	
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate();
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1676 "compiler.y"
    {
  List* functionList = lookupStringVariable(hashFunction, currentFunction);
  function* functionAux = ((function*)(functionList->info));
  List* aux = functionAux->parameters;
  argumentNumber++;
  if(argumentNumber <= functionAux->arity)
  {
    int returnTypeArgument = findArgumentType(argumentNumber, aux);
    if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
    {
      printf("Valores incompativeis na linha %d.\n", nLine);
      terminate();
    }
    else if(returnTypeArgument != varRelations[0] && in_comparacao == 0)
    {	
      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
      terminate();
    }
    else if(verifyPrimitivesMaxMinMed(currentFunction))
    {
      functionNode->children[1] = expressionNode;
    }
    else if(functionNode->children[1] == NULL)
    {
      treeNode *functionArgument = newTreeNode();
      copyTreeNodes(functionArgument, functionAux->functionTree->children[1]);
      functionArgument->next = NULL;
      
      treeNode *argumentNode = newTreeNode();
      char strAux[10];
      sprintf(strAux, "%d", argumentNumber);
      fillTreeNode(argumentNode, strAux, "ARGUMENTO");
      
      functionNode->children[1] = argumentNode;
      argumentNode->children[0] = expressionNode;
      argumentNode->children[1] = functionArgument;
    }
    else
    {
      treeNode *functionArgument = newTreeNode();
      copyTreeNodes(functionArgument, functionAux->functionTree->children[1]);
      treeNode *argumentNode = newTreeNode();
      char strAux[10];
      sprintf(strAux, "%d", argumentNumber);
      fillTreeNode(argumentNode, strAux, "ARGUMENTO");
      
      treeNode *aux = functionNode->children[1];
      while(aux->next!=NULL)
      {
	aux = aux->next;
      }
      int count = 1;
      while(count!=argumentNumber)
      {
	functionArgument=functionArgument->next;
	++count;
      }
      aux->next = argumentNode;
      argumentNode->children[0] = expressionNode;
      argumentNode->children[1] = functionArgument;
    }
  }
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  currentRelationComparison = 0;
  expressionNode = NULL;
 }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1744 "compiler.y"
    {
  List* functionList = lookupStringVariable(hashFunction, currentFunction);
  function* functionAux = ((function*)(functionList->info));
  List* aux = functionAux->parameters;
  argumentNumber++;

  if(argumentNumber <= functionAux->arity)
  {
    int returnTypeArgument = findArgumentType(argumentNumber, aux);

    if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
    {
      printf("Valores incompativeis na linha %d.\n", nLine);
      terminate();
    }
    else if(returnTypeArgument != varRelations[0] && in_comparacao == 0)
    {	
      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
      terminate();
    }
    
    if(verifyPrimitivesMaxMinMed(currentFunction))
    {
    functionNode->children[2] = expressionNode;
    expressionNode = NULL;
    }
    else if(functionNode->children[1] == NULL)
    {
      treeNode *functionArgument = newTreeNode();
      copyTreeNodes(functionArgument, functionAux->functionTree->children[1]);
      functionArgument->next = NULL;
      
      treeNode *argumentNode = newTreeNode();
      char strAux[10];
      sprintf(strAux, "%d", argumentNumber);
      fillTreeNode(argumentNode, strAux, "ARGUMENTO");
      
      functionNode->children[1] = argumentNode;
      argumentNode->children[0] = expressionNode;
      argumentNode->children[1] = functionArgument;
    }
    else
    {
      treeNode *auxFunction;
      auxFunction = functionAux->functionTree->children[1];
      //copyTreeNodes(functionArgument, functionAux->functionTree->children[1]);
      treeNode *argumentNode = newTreeNode();
      char strAux[10];
      sprintf(strAux, "%d", argumentNumber);
      fillTreeNode(argumentNode, strAux, "ARGUMENTO");
      
      treeNode *aux = functionNode->children[1];
      while(aux->next!=NULL)
      {
	aux = aux->next;
      }
          int count = 1;
      while(count!=argumentNumber)
      {
	auxFunction=auxFunction->next;
	++count;
      }
     
      treeNode* functionArgument = newTreeNode();
      copyTreeNodes(functionArgument, auxFunction);
      
      aux->next = argumentNode;
    
      argumentNode->children[0] = expressionNode;
      argumentNode->children[1] = functionArgument;
      functionArgument->next=NULL;
    }

  }
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  currentRelationComparison = 0;
  expressionNode = NULL;
}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1824 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1826 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1827 "compiler.y"
    {
    if (in_comparacao = 1 && in_condicional == 0)
    {	
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate();
	}
    currentRelationComparison=0;
    in_comparacao = 1;
  }
    else if (in_condicional == 1)
  {
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate();
	}
    currentRelationComparison=0;
  }
}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1848 "compiler.y"
    {operadorDeNivelTres();}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1848 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1850 "compiler.y"
    { operadorDeNivelDois(">"); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1851 "compiler.y"
    { operadorDeNivelDois(">="); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1852 "compiler.y"
    { operadorDeNivelDois("="); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1853 "compiler.y"
    { operadorDeNivelDois("<"); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1854 "compiler.y"
    { operadorDeNivelDois("<="); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1855 "compiler.y"
    { operadorDeNivelDois("<>"); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1858 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1859 "compiler.y"
    { operadorDeNivelUm(); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1859 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1864 "compiler.y"
    {
  /*
  Convertendo tipo do numero real e adicionando no vetor de relacoes, por exemplo (varRelations = {0, 0, 0, 1, 2})
  O vetor sera usado mais tarde para fazer comparacao de tipos de maneira tal que apenas mesmos tipos podem realizar operacoes. 
  */  
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    
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

  case 149:

/* Line 1806 of yacc.c  */
#line 1909 "compiler.y"
    {
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  
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

  case 152:

/* Line 1806 of yacc.c  */
#line 1953 "compiler.y"
    {	operadorDeNivelZero("/"); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1953 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1956 "compiler.y"
    {
  if(strcmp(currentType, "inteiro")!=0)
  {
    printf("Operador %% so aceita inteiros na linha %d.\n", nLine);
    terminate();
  }
}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1963 "compiler.y"
    { operadorDeNivelZero("%"); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1964 "compiler.y"
    {
    if(strcmp(currentType, "inteiro")!=0)
    {
      printf("Operador %% so aceita inteiro na linha %d.\n", nLine);
      terminate();
    }
}
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1971 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 1973 "compiler.y"
    { operadorDeNivelZero("*"); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1973 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 1975 "compiler.y"
    { operadorDeMenorNivel("^"); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 1975 "compiler.y"
    { swapoutZeroMenor(); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 1979 "compiler.y"
    {
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    
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

  case 164:

/* Line 1806 of yacc.c  */
#line 1997 "compiler.y"
    {
  {  
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  
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

  case 165:

/* Line 1806 of yacc.c  */
#line 2020 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else
    {  
    {
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
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
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }
    else
    {  
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;      
    }
    
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

  case 166:

/* Line 1806 of yacc.c  */
#line 2088 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0)
    {  printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
       terminate();
    }
    else
    {  
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
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
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else
    {  
      int currentTypeInt = ((variable*)(identifier_temp->info))->type;
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
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

  case 167:

/* Line 1806 of yacc.c  */
#line 2163 "compiler.y"
    {
  List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate();
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
      terminate();
    }
  }
  if(identifier_temp != NULL)
  {
  	//monta a arvore
  	treeMatrixOneDimension( ((variable*)(identifier_temp->info))->name , currentNumber);
  	
    if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else if(((variable*)(identifier_temp->info))->matrix!=1){
      printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(identifier_temp->info))->name);
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->nColumn <= currentNumber ){
	printf("Erro na linha %d, %s possui %d posicoes.\n", nLine, ((variable*)(identifier_temp->info))->name,((variable*)(identifier_temp->info))->nColumn );
	terminate();
    }
    else
    {  
	int currentTypeInt = ((variable*)(identifier_temp->info))->type;
	varRelations[currentRelationPos] = currentTypeInt;
	++currentRelationPos;
	++currentRelationComparison;
    }
  }
}
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 2214 "compiler.y"
    {
  List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate();
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
      terminate();
    }
  }
  if(identifier_temp != NULL)
  {
  	//monta a arvore com uma dimensão
  	treeMatrixOneDimension( ((variable*)(identifier_temp->info))->name , currentNumber);
  
    if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else if(((variable*)(identifier_temp->info))->matrix!=1){
      printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(identifier_temp->info))->name);
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->nColumn <= currentNumber ){
	printf("Erro na linha %d, %s possui %d colunas.\n", nLine, ((variable*)(identifier_temp->info))->name,((variable*)(identifier_temp->info))->nColumn );
	terminate();
    }
  }
}
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 2257 "compiler.y"
    {
   List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate();
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
    if(identifier_temp == NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }
    else{
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
	terminate();
      }
	int currentTypeInt = ((variable*)(identifier_temp->info))->type;
	varRelations[currentRelationPos] = currentTypeInt;
	++currentRelationPos;
	++currentRelationComparison;
    }
  }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 2305 "compiler.y"
    {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
	
    //preenche arvore de expressão
    treeNode* aux = newTreeNode();
    fillTreeNode(aux, yytext, "CARACTER");
    if (expressionNode == NULL) {
      expressionNode = aux;
    }else{
    	expressionNode->children[1] = aux;
    }
}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 2321 "compiler.y"
    {
  if(strlen(limitString) > MAX_LITERAL+2)
  {
    printf("Tamanho de literal passou do limite de %d caracteres na linha %d\n", MAX_LITERAL,nLine);
    terminate();
  }
  else
  {
   
      int currentTypeInt = convertType(currentType);
      varRelations[currentRelationPos] = currentTypeInt;
      ++currentRelationPos;
      ++currentRelationComparison;
      
    	char s[50];
    	strcpy(s,yytext+1);
    	retiraAspasFinal(s);
    	//preenche arvore de expressão
    	treeNode* aux = newTreeNode();
    	fillTreeNode(aux, s, "LITERAL");
    	if (expressionNode == NULL) {
    	  expressionNode = aux;
    	}else{
    		expressionNode->children[1] = aux;
    	}
    
  }
}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 2349 "compiler.y"
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
	if(stackParenthesis == NULL) stackParenthesis = createStack();
	stackParenthesis = addNodeIntoStack(swapZeroMenor, stackParenthesis);
	stackParenthesis = addNodeIntoStack(swapUmZero, stackParenthesis);
	stackParenthesis = addNodeIntoStack(swapDoisUm, stackParenthesis);
	stackParenthesis = addNodeIntoStack(swapTresDois, stackParenthesis);
	stackParenthesis = addNodeIntoStack(expressionNode, stackParenthesis);
	
	swapZeroMenor = swapUmZero = swapDoisUm = swapTresDois = expressionNode = NULL;

}
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 2368 "compiler.y"
    {
	treeNode* aux = (treeNode*) popStack(stackParenthesis);
	if(aux->children[0] == NULL){
		aux->children[0] = expressionNode;
	} else {
		aux->children[1]->children[0] = expressionNode; 
	}
	expressionNode = aux;
	swapTresDois = 	(treeNode*) popStack(stackParenthesis);
	swapDoisUm = (treeNode*) popStack(stackParenthesis);
	swapUmZero = (treeNode*) popStack(stackParenthesis);
	swapZeroMenor =(treeNode*) popStack(stackParenthesis);
	printf("FINAL\n");
	//printNode(expressionNode,13,0);
}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 2384 "compiler.y"
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
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 2400 "compiler.y"
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
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 2417 "compiler.y"
    {

    functionNode = newTreeNode();
    treeNode* returnNode = newTreeNode();
      
  //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
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
	fillTreeNode(returnNode, "RETORNO", "INTEIRO");
	
      }
      else if (typeAttribute==T_REAL)
      {
	strcpy(currentFunction, "maximo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "real");
	fillTreeNode(returnNode, "RETORNO", "REAL");
      }
      else if (typeAttribute==T_CARACTER)
      {
	strcpy(currentFunction, "maximo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "caracter");
	fillTreeNode(returnNode, "RETORNO", "CARACTER");
      }
      else
      {
	printf("Retorno nao valido na funcao maximo na linha %d\n", nLine);
	terminate();
      }
     }
     if(strcmp(currentIdentifier, "minimo")==0)
     {
      if (typeAttribute==T_INTEIRO)
      {
	strcpy(currentFunction, "minimo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "inteiro");
	fillTreeNode(returnNode, "RETORNO", "INTEIRO");

      }
      else if (typeAttribute==T_REAL)
      {
	strcpy(currentFunction, "minimo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "real");
	fillTreeNode(returnNode, "RETORNO", "REAL");

      }
      else if (typeAttribute==T_CARACTER)
      {
	strcpy(currentFunction, "minimo");
	strcat(currentFunction, " ");
	strcat(currentFunction, "caracter");
	fillTreeNode(returnNode, "RETORNO", "CARACTER");

      }
      else
      {
	printf("Retorno nao valido na funcao minimo na linha %d\n", nLine);
	terminate();
      }
     }
     if(strcmp(currentIdentifier, "media")==0)
     {
      if (typeAttribute==T_INTEIRO)
      {
	strcpy(currentFunction, "media");
	strcat(currentFunction, " ");
	strcat(currentFunction, "inteiro");
	fillTreeNode(returnNode, "RETORNO", "INTEIRO");

      }
      else if (typeAttribute==T_REAL)
      {
	strcpy(currentFunction, "media");
	strcat(currentFunction, " ");
	strcat(currentFunction, "real");
	fillTreeNode(returnNode, "RETORNO", "REAL");

      }
      else
      {
	printf("Retorno nao valido na funcao media na linha %d\n", nLine);
	terminate();
      }
     }
  
    List *functionList = lookupStringFunction(hashFunction, currentFunction);
    if(verifyPrimitivesMaxMinMed(currentFunction)) 
    {
      functionNode->children[0] = returnNode;
      fillTreeNode(functionNode, currentIdentifier, "PRIMITIVA");   
      stackExpressionNode = addNodeIntoStack(expressionNode, stackExpressionNode);
      expressionNode=NULL;
    }
    else if(functionList!=NULL)
    {
      function* functionAux = ((function*)(functionList)->info);
      functionNode = newTreeNode();
      fillTreeNode(functionNode, currentFunction, "CHAMADA FUNCAO");
      
      treeNode* auxFunctionNode = newTreeNode();
      copyTreeNodes(auxFunctionNode, functionAux -> functionTree);
      functionNode->children[0] = auxFunctionNode;
      functionNode->children[0]->children[3] = NULL;
      stackExpressionNode = addNodeIntoStack(expressionNode, stackExpressionNode);
      expressionNode=NULL;
    }
    
  }
}
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 2541 "compiler.y"
    { 
  List *functionList = lookupStringFunction(hashFunction, currentFunction);
  if(functionList == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
    terminate();
  }
  else
  {
    if(argumentNumber != ((function*)(functionList->info))->arity)
    {  
      printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
      terminate();
    }
  
  }
  argumentNumber=0;   
    expressionNode = popStack(stackExpressionNode);   
   
   if(expressionNode==NULL) {
    expressionNode=functionNode;
    }
   else {
      expressionNode->children[1] = functionNode;
    }
    
  strcpy(functionArguments, "\0");
  }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 2571 "compiler.y"
    {
  if(switchType != T_INTEIRO)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
    terminate();
  }
  {
    treeNode* fatorAux = newTreeNode();
    fillTreeNode(fatorAux, yytext, "FATOR_CASE");
    
    caseNode->children[0] = fatorAux;
  }
}
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 2585 "compiler.y"
    {
  if(switchType != T_REAL)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
    terminate();
  }
    {
    treeNode* fatorAux = newTreeNode();
    fillTreeNode(fatorAux, yytext, "FATOR_CASE");
    
    caseNode->children[0] = fatorAux;
  }
  }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 2599 "compiler.y"
    {
  if(switchType != T_CARACTER)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
    terminate();
  }
    {
    treeNode* fatorAux = newTreeNode();
    fillTreeNode(fatorAux, yytext, "FATOR_CASE");
    
    caseNode->children[0] = fatorAux;
  }
}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 2613 "compiler.y"
    { countLine=0; delimitadorNivelUm(); tempDelimitadorNivelUm = expressionNode;  expressionNode=NULL; }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 2613 "compiler.y"
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
			terminate();
			((variable*)(identifier_temp->info))->used = 0;
		}else{
			((variable*)(identifier_temp->info))->used = 1;
		}
	}
	expressionNode = tempDelimitadorNivelUm;
}
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 2634 "compiler.y"
    {
	isMatrix = 1;
}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 2638 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 2638 "compiler.y"
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
			terminate();
			((variable*)(identifier_temp->info))->used = 0;
		}else{
			((variable*)(identifier_temp->info))->used = 1;
		}
	}
}
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 2658 "compiler.y"
    {
	isMatrix = 1; 
	expressionNode = tempDelimitadorNivelZero;
 }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 2662 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 2663 "compiler.y"
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
			terminate();
			((variable*)(identifier_temp->info))->used = 0;
		}
	}
}
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 2686 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 2686 "compiler.y"
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
			terminate();
			((variable*)(identifier_temp->info))->used =0;
		}
	}
}
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 2712 "compiler.y"
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
			terminate();
		} 
	}
	countColumn++;
	
	//primeiro no da lista
	tempDelimitadorNivelZero->children[0] = expressionNode;
	expressionNode = NULL;
}
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 2736 "compiler.y"
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
			terminate();
		}
	}	
	countColumn++;
	
	//adiciona na lista
	treeNode* auxList = tempDelimitadorNivelZero->children[0];
	while(auxList->next != NULL) auxList = auxList->next;
	auxList->next = expressionNode;
	expressionNode = NULL;
	
}
    break;



/* Line 1806 of yacc.c  */
#line 5153 "compiler.tab.c"
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
#line 2761 "compiler.y"


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
  
  //imprima, aridade 1, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "imprima");
  addInfoFunction(hashFunction, functionAux, newFunction);
  setFunction(newFunction, functionAux,T_SEMRETORNO, 1, NULL, 1);

  //leia, aridade 1, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "leia");
  addInfoFunction(hashFunction, functionAux, newFunction);
  setFunction(newFunction, functionAux,T_SEMRETORNO, 1, NULL, 1);
    
  //imprimaln, aridade 1, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "imprimaln");
  addInfoFunction(hashFunction, functionAux, newFunction);
  setFunction(newFunction, functionAux,T_SEMRETORNO, 1, NULL, 1);

  //leialn, aridade 1, garantir que nao haja conflito
  newFunction = createFunction();
  strcpy(functionAux, "leialn");
  addInfoFunction(hashFunction, functionAux, newFunction);
  setFunction(newFunction, functionAux,T_SEMRETORNO, 1, NULL, 1);
}

FILE *abre_arquivo(char *filename, char *modo) {
	FILE *file;

	if (!(file = fopen(filename, modo))) {
		printf("Erro na abertura do arquivo %s\n", filename);
		err=1;
	}
	return file;
}

void ZerarGlobais(){
	currentParameters = NULL;

	hashVariables = NULL;
	hashFunction = NULL;

	stackParenthesis = NULL;
	stackGlobal = NULL;
	stackIfThenElse = NULL;
	stackExpressionNode = NULL;
	stackVariables = NULL;
	stackVariablesAux = NULL;

	globalTree = NULL;
	expressionNode = NULL;
	attributionNode = NULL;
	conditionNode = NULL;
	commandNode = NULL;
	caseNode = NULL;
	functionNode = NULL;
	functionInternalVariables = NULL;

	swapZeroMenor = NULL;
	swapUmZero = NULL;
	swapDoisUm = NULL;
	swapTresDois = NULL;
	tempDelimitadorNivelZero = NULL;
	tempDelimitadorNivelUm = NULL;
}

void terminate(){
      freeTable(hashVariables);
      freeTableFunction(hashFunction);
      err = 1;
}

Program* compila(char *nome_programa) {
	
	//Limpando coisas necessárias: TODO dar free
	ZerarGlobais();

	//Criando as hash
    hashVariables = createHash(MAX_HASH);
    hashFunction = createHash(MAX_HASH);
    createPrimitives();

	//Contador de linhas
	nLine = 1;
	
	//Erro
	err = 0;
    
	yyin = abre_arquivo(nome_programa, "r");
	if (yyin != NULL) {
		yyparse();
	} else {
		err = 1;
		return NULL;
	}
	
	//Reiniciando o buffer do flex
	YY_FLUSH_BUFFER;
	

	if(err==1){
		return NULL;
	}
	
	Program *p = createProgram();
	//Copia as paradas
	p->name = (char*)malloc(strlen(nome_programa+2)*sizeof(char));
	strcpy(p->name, nome_programa);
	p->exec = globalTree;
	p->hashVariables = hashVariables;
	p->hashFunctions = hashFunction;
	
	//Seta como null
	globalTree = NULL;
	hashVariables = NULL;
	hashFunction = NULL;
	
	fclose(yyin);
	return p;
}

main()
{

    Program *program;
    int option, tam, i;
    char lixo;
    char * programa;
    
    showBoasVindas();
    while(1){
    
		option = showMenu();
		
		switch(option){
		case 1: //Compilar
			programa = (char*) solicitaNomePrograma();
			printf("Abrindo %s\n", programa);
			program = compila(programa);
			if(program==NULL || err == 1){
				printf("Não foi possível compilar o programa devido a discordâncias da linguagem de entrada. Por favor verifique as linhas indicadas acima e tente novamente.\n");
			}else {
	   			listPrograms = insertList(listPrograms, program);
	   			printf("Programa compilado com éxito, pronto para executar-se.\n");
	   		}
	   		scanf("%c",&lixo);
			break;
		case 2: //Executar
			tam = sizeList(listPrograms);
			if(tam==0){ printf("Não há programas a serem executados. Favor compilar algum programa e voltar a tentar.\n"); scanf("%c",&lixo);}
			else {
				for(i=0;i<tam;i++){
					program = (Program*)getListPosition(listPrograms,i);
					if (program)
						printf("%d - %s\n", i+1, program->name);
				}
				scanf("%d",&option);
				scanf("%c",&lixo);
				if(option<1 || option> tam){ 
					printf("O programa desejado não pode se executado ou não existe.\n");
					break; 
				}
				program = (Program*)getListPosition(listPrograms,option-1);
				if(program != NULL) {
					executeProgram(program);
					scanf("%c",&lixo);
				}else
					printf("O programa desejado não pode se executado ou não existe.\n");
			}
			break;
		case 3: //Mostrar a árvore  
			tam = sizeList(listPrograms);
			if(tam==0){ printf("Não há programas compilados. Favor compilar algum programa e voltar a tentar.\n"); scanf("%c",&lixo); break;}
			printf("Entre com o programa do qual deseja ver a arvore\n");
			scanf("%d",&option);
			scanf("%c",&lixo);
			if(option<1 || option>tam){printf("O programa desejado não pode ser encontrado.\n"); }
			else { 
				program = (Program*)getListPosition(listPrograms,option-1);
				printNode(program->exec, 13, 0);		
			}
			scanf("%c",&lixo);
			break;
		case 4: //Listar programas compilados
			tam = sizeList(listPrograms);
			if(tam==0) printf("Não há programas compilados. Você pode compilar programas na opção 1 do menu.\n");
			else {
				for(i=0;i<tam;i++){
					program = (Program*)getListPosition(listPrograms,i);
					if (program)
						printf("%d - %s\n", i+1, program->name);
				}
			}
			scanf("%c",&lixo);
			break;
		case 5: //listar aquivos .gpt
			listarFiles();
			scanf("%c",&lixo);
			break;
		case 6: //sobre
			showSobre();
			break;
		case 7: //sair
			showDespedida();
			return 0;
		default: break;
		}
		
	}
	
    
	if(IN_DEBUG_MODE){
	  	treeNode* aux = globalTree;
  	printNode(aux, 13, 0);
	printf("\n ---------- \n");
	printf(" ---------- \n");
      }


	
	
 	//	List* l = lookupStringVariable(hashVariables, "c");
 	//	printf("c: %d\n", *( (int*) ( (variable*) l->info )->value) );
 	//	List* l = lookupStringVariable(hashVariables, "str");
 	//	printf("str: %s\n", ( (char*) ( (variable*) l->info )->value) );
 	//	List* l = lookupStringVariable(hashVariables, "a");
 	//	printf("a: %.2f\n", *( (double*) ( (variable*) l->info )->value) );
 	//	l = lookupStringVariable(hashVariables, "ch");
 	//	printf("ch: %c\n", *( (char*) ( (variable*) l->info )->value) );
 		//l = lookupStringVariable(hashVariables, "b");
 		//printf("b: %d\n", *( (int*) ( (variable*) l->info )->value) );
 	//	List* l = lookupStringVariable(hashVariables, "a");
 	//	printf("a: %.2f\n", *( (double*) ( (variable*) l->info )->value) );
 	//	l = lookupStringVariable(hashVariables, "b");
 	//	printf("b: %d\n", *( (int*) ( (variable*) l->info )->value) );
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
	terminate();
}

