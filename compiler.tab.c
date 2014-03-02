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

//extern YY_FLUSH_BUFFER;
extern int err;
extern char* yytext;
extern FILE* yyin;
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
char returnVariableGlobal[MAX_VARIABLE];
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
List* listPrograms = NULL;
hashTable* hashVariables = NULL;
hashTable* hashFunction = NULL;
char limitString[50]; //limitador de tamanho de string no programa
int returnFlag = 0;
int argumentNumber = 0;

Stack* stackParentesis = NULL;
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

treeNode* swapZeroMenor = NULL;
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
#line 337 "compiler.tab.c"

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
#line 463 "compiler.tab.c"

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
#define YYLAST   366

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  111
/* YYNRULES -- Number of rules.  */
#define YYNRULES  192
/* YYNRULES -- Number of states.  */
#define YYNSTATES  354

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
     146,   155,   157,   158,   168,   175,   182,   183,   192,   193,
     194,   206,   207,   217,   221,   227,   228,   229,   234,   240,
     246,   247,   254,   255,   262,   263,   264,   272,   273,   274,
     284,   285,   286,   287,   301,   302,   303,   310,   311,   312,
     313,   314,   326,   327,   328,   329,   330,   343,   344,   345,
     346,   347,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   389,   390,   391,   392,   401,   402,   403,   409,   411,
     412,   413,   417,   418,   419,   423,   425,   429,   430,   432,
     433,   438,   439,   444,   446,   448,   450,   452,   454,   456,
     458,   459,   464,   467,   469,   471,   473,   475,   477,   479,
     480,   485,   486,   487,   488,   495,   496,   501,   502,   507,
     509,   511,   513,   515,   518,   523,   524,   533,   535,   537,
     538,   543,   545,   547,   548,   554,   556,   558,   560,   562,
     563,   564,   570,   571,   572,   578,   579,   580,   588,   589,
     590,   596,   598
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
      55,    -1,    46,    -1,    -1,    98,   120,    -1,    98,    11,
      98,    12,    -1,    -1,    99,    35,    83,   100,   114,    -1,
      -1,    35,    83,   101,   114,    -1,    -1,   102,   120,    -1,
      11,   102,    12,    -1,    -1,   104,    -1,   120,    -1,   104,
     120,    -1,   180,    -1,    -1,   112,   107,   106,    -1,    -1,
     112,   108,   109,    -1,    -1,    -1,    51,   110,     8,   102,
      53,   111,     7,    60,    -1,    60,    -1,    -1,    23,     3,
     184,     4,     8,   102,    53,   113,     7,    -1,    23,     3,
     184,     4,     8,   102,    -1,     3,   119,     4,    38,   103,
      30,    -1,    -1,     3,   119,     4,    90,   115,    38,   103,
      30,    -1,    -1,    -1,     3,   119,     4,     8,    91,   116,
      90,   117,    38,   103,    30,    -1,    -1,     3,   119,     4,
       8,    91,   118,    38,   103,    30,    -1,    83,     8,    91,
      -1,   119,     5,    83,     8,    91,    -1,    -1,    -1,    57,
     121,   165,     7,    -1,    36,     3,   105,     4,     7,    -1,
      37,     3,   105,     4,     7,    -1,    -1,    41,     3,    83,
     122,     4,     7,    -1,    -1,    42,     3,    83,   123,     4,
       7,    -1,    -1,    -1,    83,   124,     3,   164,     4,   125,
       7,    -1,    -1,    -1,    83,    13,    18,    14,    71,   126,
     165,   127,     7,    -1,    -1,    -1,    -1,    83,    13,    18,
      14,    13,   128,    18,   129,    14,    71,   165,   130,     7,
      -1,    -1,    -1,    83,    71,   131,   165,   132,     7,    -1,
      -1,    -1,    -1,    -1,    58,   133,     3,   165,   134,     4,
     135,    27,   102,   136,   156,    -1,    -1,    -1,    -1,    -1,
      28,   137,   102,   138,     7,    26,     3,   165,   139,     4,
     140,     7,    -1,    -1,    -1,    -1,    -1,    26,     3,   141,
     165,   142,     4,   143,    28,   102,   144,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,   145,     3,
     146,    83,   147,    24,   180,   148,    20,   180,   149,    54,
     180,   150,     4,   151,    28,   102,   152,    32,    -1,    -1,
      -1,    -1,    59,   153,     3,    83,   154,     4,   155,   106,
      -1,    -1,    -1,    61,   157,   102,   158,    33,    -1,    33,
      -1,    -1,    -1,   160,   161,    25,    -1,    -1,    -1,   162,
     163,    50,    -1,   165,    -1,   164,     5,   165,    -1,    -1,
     169,    -1,    -1,   165,   168,   169,   166,    -1,    -1,   165,
     159,   167,   169,    -1,    72,    -1,    74,    -1,    76,    -1,
      73,    -1,    75,    -1,    77,    -1,   173,    -1,    -1,   169,
     171,   170,   173,    -1,   169,   172,    -1,    64,    -1,    65,
      -1,    15,    -1,    17,    -1,   185,    -1,   180,    -1,    -1,
     173,    67,   174,   180,    -1,    -1,    -1,    -1,   173,   175,
      68,   176,   180,   177,    -1,    -1,   173,    66,   178,   180,
      -1,    -1,   173,    84,   179,   180,    -1,   172,    -1,    18,
      -1,    16,    -1,    83,    -1,    65,    83,    -1,    83,    13,
      18,    14,    -1,    -1,    83,    13,    18,    14,    13,   181,
      18,    14,    -1,    81,    -1,    82,    -1,    -1,     3,   182,
     165,     4,    -1,    63,    -1,    29,    -1,    -1,    83,   183,
       3,   164,     4,    -1,   172,    -1,    18,    -1,    16,    -1,
      81,    -1,    -1,    -1,    11,   186,   190,   187,    12,    -1,
      -1,    -1,    13,   188,   195,   189,    14,    -1,    -1,    -1,
     190,     5,    13,   191,   195,   192,    14,    -1,    -1,    -1,
      13,   193,   195,   194,    14,    -1,   180,    -1,   195,     5,
     180,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   352,   352,   352,   360,   359,   366,   367,   367,   369,
     437,   507,   507,   507,   507,   507,   507,   509,   509,   511,
     511,   511,   512,   512,   513,   513,   513,   513,   513,   515,
     515,   515,   517,   516,   577,   576,   636,   636,   636,   637,
     637,   638,   638,   640,   642,   641,   670,   669,   706,   713,
     705,   719,   721,   720,   726,   728,   729,   729,   731,   740,
     730,   744,   742,   753,   796,   839,   842,   842,   894,   896,
     899,   898,   913,   912,   928,   942,   927,  1073,  1131,  1073,
    1158,  1204,  1218,  1158,  1246,  1279,  1245,  1397,  1408,  1422,
    1423,  1396,  1432,  1443,  1450,  1458,  1431,  1460,  1468,  1485,
    1488,  1459,  1500,  1506,  1507,  1519,  1525,  1540,  1588,  1598,
    1499,  1606,  1607,  1690,  1606,  1699,  1713,  1698,  1719,  1722,
    1723,  1722,  1752,  1753,  1752,  1782,  1852,  1929,  1930,  1932,
    1932,  1956,  1956,  1958,  1959,  1960,  1961,  1962,  1963,  1966,
    1967,  1967,  1968,  1969,  1969,  1971,  2019,  2064,  2064,  2066,
    2066,  2069,  2076,  2077,  2068,  2086,  2086,  2088,  2088,  2090,
    2091,  2111,  2133,  2213,  2302,  2359,  2358,  2450,  2468,  2497,
    2497,  2531,  2551,  2572,  2571,  2822,  2822,  2836,  2850,  2865,
    2865,  2865,  2890,  2890,  2890,  2914,  2915,  2914,  2938,  2938,
    2937,  2963,  2986
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
  "$@13", "$@14", "$@15", "$@16", "VARIAVEIS_FUNCAO", "COMANDO", "$@17",
  "$@18", "$@19", "$@20", "$@21", "$@22", "$@23", "$@24", "$@25", "$@26",
  "$@27", "$@28", "$@29", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35",
  "$@36", "$@37", "$@38", "$@39", "$@40", "$@41", "$@42", "$@43", "$@44",
  "$@45", "$@46", "$@47", "$@48", "$@49", "$@50", "$@51",
  "BLOCO_SENAO_FIMSE", "$@52", "$@53", "LOGICOS", "$@54", "$@55", "$@56",
  "$@57", "ARGUMENTOS_FUNCAO", "EXPR", "$@58", "$@59", "COMPARACOES",
  "SIEXPR", "$@60", "ADICAO_SUBTRACAO", "SINALFATOR", "TERMO", "$@61",
  "$@62", "$@63", "$@64", "$@65", "$@66", "FATOR", "$@67", "$@68", "$@69",
  "FATOR_CASE", "MATRIZ", "$@70", "$@71", "$@72", "$@73",
  "MATRIZ_VARIAS_COLUNAS", "$@74", "$@75", "$@76", "$@77", "BLOCO_MATRIZ", 0
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
     109,   109,   113,   112,   112,   114,   115,   114,   116,   117,
     114,   118,   114,   119,   119,   119,   121,   120,   120,   120,
     122,   120,   123,   120,   124,   125,   120,   126,   127,   120,
     128,   129,   130,   120,   131,   132,   120,   133,   134,   135,
     136,   120,   137,   138,   139,   140,   120,   141,   142,   143,
     144,   120,   145,   146,   147,   148,   149,   150,   151,   152,
     120,   153,   154,   155,   120,   157,   158,   156,   156,   160,
     161,   159,   162,   163,   159,   164,   164,   164,   165,   166,
     165,   167,   165,   168,   168,   168,   168,   168,   168,   169,
     170,   169,   169,   171,   171,   172,   172,   173,   173,   174,
     173,   175,   176,   177,   173,   178,   173,   179,   173,   180,
     180,   180,   180,   180,   180,   181,   180,   180,   180,   182,
     180,   180,   180,   183,   180,   184,   184,   184,   184,   186,
     187,   185,   188,   189,   185,   191,   192,   190,   193,   194,
     190,   195,   195
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     8,     3,     2,     0,     4,
       5,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       0,    11,     0,     7,     1,     1,     1,     1,     1,     0,
       2,     4,     0,     5,     0,     4,     0,     2,     3,     0,
       1,     1,     2,     1,     0,     3,     0,     3,     0,     0,
       8,     1,     0,     9,     6,     6,     0,     8,     0,     0,
      11,     0,     9,     3,     5,     0,     0,     4,     5,     5,
       0,     6,     0,     6,     0,     0,     7,     0,     0,     9,
       0,     0,     0,    13,     0,     0,     6,     0,     0,     0,
       0,    11,     0,     0,     0,     0,    12,     0,     0,     0,
       0,    11,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     0,     0,     0,     8,     0,     0,     5,     1,     0,
       0,     3,     0,     0,     3,     1,     3,     0,     1,     0,
       4,     0,     4,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     2,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     0,     0,     6,     0,     4,     0,     4,     1,
       1,     1,     1,     2,     4,     0,     8,     1,     1,     0,
       4,     1,     1,     0,     5,     1,     1,     1,     1,     0,
       0,     5,     0,     0,     5,     0,     0,     7,     0,     0,
       5,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     8,     0,     8,
       0,     0,    34,     0,     0,     7,    17,     0,     0,    29,
       0,    32,    29,     6,     0,     0,     0,     0,    65,    35,
       0,     0,     0,    18,    13,    11,    14,    15,     0,    12,
       0,    16,    29,     0,    92,     5,     0,     0,     0,     0,
     102,    66,    87,   111,    74,    30,     0,     0,    33,     3,
       0,     0,     9,     0,    97,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
      10,     0,    31,     0,    36,    93,   169,   145,   161,   146,
     160,   172,   171,     0,   167,   168,   162,     0,   159,    43,
       0,    70,    72,   103,   179,   182,   119,   128,   139,   148,
     147,     0,     0,     0,     0,   127,    63,     0,    39,    56,
       0,     0,    98,     0,    37,     0,     0,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    67,   133,   136,
     134,   137,   135,   138,   131,   120,   123,     0,   143,   144,
     140,   142,   155,   149,   157,     0,    88,   112,     0,    85,
       0,   125,    58,     0,    40,    41,     0,     0,    19,    22,
       0,    38,     0,   119,     0,   127,    68,    69,     0,     0,
     104,   188,   180,   191,   183,     0,     0,     0,   129,     0,
       0,     0,     0,   152,     0,     0,    80,    77,     0,    75,
       0,     0,     0,    55,    42,    39,    64,     0,     0,    99,
       0,   170,   164,     0,    71,    73,     0,     0,     0,     0,
       0,     0,   132,   121,   124,   130,   141,   156,   150,   158,
       0,    89,   113,     0,     0,    86,     0,   126,    59,    39,
       0,    20,    25,    24,    26,    28,    27,    23,     0,     0,
     165,   174,     0,   189,   185,   181,   192,   184,   153,     0,
       0,    81,    78,    76,     0,     0,    57,     0,    36,    94,
       0,   105,     0,     0,   154,    36,     0,   114,    46,     0,
       0,    39,    62,     0,   100,     0,     0,     0,   190,   186,
      90,     0,     0,     0,     0,    79,     0,     0,     0,    95,
     166,     0,     0,     0,   177,   176,   178,   175,     0,    45,
      48,    51,    47,     0,    60,    21,   101,     0,   106,   187,
     118,   115,    91,     0,     0,    82,    96,     0,    36,    36,
      36,     0,     0,   116,    54,     0,    83,   107,     0,    52,
      49,     0,   117,     0,     0,   108,    53,     0,     0,    50,
      36,   109,     0,   110
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     7,    11,    17,    40,    18,    41,   207,
     267,   208,   247,    27,     9,    30,    20,    85,   163,   164,
      97,   277,   292,   293,   312,   324,   344,   278,   343,    29,
     166,   201,   264,   202,    57,   124,    71,   132,   133,    76,
     236,   234,   280,   233,   279,   331,   114,   198,    72,   194,
     259,   303,    65,   125,   285,   317,    83,   170,   248,   298,
      70,   134,   216,   287,   327,   341,   348,   352,    73,   195,
     260,   322,   328,   338,   144,   145,   186,   146,   187,   160,
     161,   225,   185,   147,   107,   189,   150,    98,   108,   191,
     155,   230,   274,   190,   192,   109,   270,   126,   129,   308,
     110,   135,   219,   136,   221,   182,   273,   302,   217,   272,
     184
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -206
static const yytype_int16 yypact[] =
{
      20,   -41,    53,    60,  -206,    39,    49,    44,    25,    -7,
     -14,    48,  -206,    38,   100,  -206,  -206,    -1,   111,  -206,
     140,  -206,  -206,  -206,   132,    63,    36,   119,    65,  -206,
     140,   182,    36,  -206,  -206,  -206,  -206,  -206,   144,  -206,
     143,  -206,  -206,   150,  -206,  -206,   159,   160,   162,   163,
    -206,  -206,  -206,  -206,     1,  -206,   161,    56,  -206,  -206,
     165,   152,  -206,   147,  -206,   157,    14,    14,    91,    96,
     178,     8,   187,   189,   167,  -206,   192,    36,     2,   113,
    -206,   183,  -206,     8,   157,   273,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,   115,  -206,  -206,    45,   196,  -206,  -206,
     197,  -206,  -206,  -206,  -206,  -206,    28,    -2,    68,  -206,
    -206,     8,   120,   195,     8,     8,  -206,    36,   273,   128,
     207,    21,   272,   201,  -206,   209,     8,  -206,   199,   217,
     214,   215,   221,   224,   148,   219,    14,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,     8,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,   168,   272,  -206,     5,   272,
     124,   272,   206,   203,   273,  -206,   212,    36,  -206,  -206,
     241,  -206,   225,    37,   238,     8,  -206,  -206,   247,   248,
    -206,  -206,   252,  -206,   257,     8,   239,   218,    -2,     8,
      14,    14,    14,  -206,   263,   266,  -206,  -206,   267,  -206,
       8,   128,   237,  -206,  -206,   273,  -206,   255,    77,  -206,
     275,  -206,   268,   137,  -206,  -206,   259,    14,   276,   274,
      14,   265,    -2,  -206,  -206,  -206,    68,  -206,  -206,  -206,
      14,  -206,  -206,   280,     8,  -206,   278,   272,   128,   273,
     270,  -206,  -206,  -206,  -206,  -206,  -206,  -206,   277,     8,
    -206,  -206,    14,   257,  -206,  -206,  -206,  -206,  -206,   281,
     279,  -206,   272,  -206,   282,   286,  -206,   289,   157,   272,
     299,  -206,   290,    14,  -206,   157,   316,  -206,   298,   309,
     317,   273,  -206,   302,   273,   323,   314,   313,  -206,   257,
     273,    34,   279,    67,   258,  -206,   304,    77,   305,  -206,
    -206,    14,   321,     3,  -206,  -206,  -206,  -206,   334,  -206,
    -206,  -206,  -206,     8,  -206,  -206,  -206,   332,  -206,  -206,
    -206,  -206,  -206,   333,   335,   272,  -206,   288,   157,   157,
     157,   343,    14,   273,   235,   254,  -206,  -206,   307,  -206,
    -206,   347,  -206,   345,   346,  -206,  -206,   294,   327,  -206,
     157,   273,   325,  -206
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -206,  -206,  -206,  -206,   349,   -70,   -23,   -12,  -206,  -206,
    -206,  -206,    62,    24,  -206,  -206,  -206,   -81,  -183,  -206,
     293,    69,  -206,  -206,  -206,  -206,  -206,  -206,  -206,   336,
    -206,  -206,  -206,  -206,  -206,   -25,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,   188,
     -67,  -206,  -206,  -206,  -120,  -206,  -206,  -100,   173,  -206,
    -206,  -206,  -206,  -206,  -206,   -66,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -205
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -174
static const yytype_int16 yytable[] =
{
      99,    99,    55,   123,   106,    24,    55,   151,   119,    60,
     117,    86,   253,    87,    74,    89,   122,    86,   196,   104,
      15,   105,   240,    87,    88,    89,    90,   188,    13,    87,
      88,    89,    90,    23,   168,   137,   320,    91,    55,     1,
     118,   211,     3,    91,   156,   169,    31,   159,  -173,    87,
     304,    89,   305,     4,   116,    10,   265,    34,   128,   173,
      78,    79,   148,   149,   321,   222,    63,     5,   289,    16,
     183,    92,    75,    93,    -2,    35,   197,    92,  -122,    93,
      36,    37,    16,    38,     8,    16,    19,  -122,   151,    94,
      95,    96,    39,   165,   162,    94,    95,    96,   296,   242,
     138,   139,   140,   141,   142,   143,    10,    24,    12,   138,
     139,   140,   141,   142,   143,   306,    25,   243,   310,    26,
     244,    21,   151,   245,   227,   228,   229,   311,   199,   200,
      42,   238,   246,   237,   152,   153,  -151,    25,    22,   204,
      32,   251,   200,    28,   206,    43,    33,    44,    56,    45,
      62,   183,   154,    64,   256,    46,    47,    61,    42,    82,
      48,    49,    66,    67,   258,    68,    69,   262,    84,    77,
      81,    50,    80,    43,   101,    44,    51,    52,    53,   102,
     165,   103,   269,    46,    47,   113,   271,   284,    48,    49,
     111,   307,   112,    42,   290,   115,   120,   121,   127,    50,
     130,   131,    54,   157,    51,    52,    53,   183,    43,   158,
      44,    16,    59,   171,   165,   167,   172,   174,    46,    47,
     175,   176,   177,    48,    49,   178,    24,    43,   179,    44,
      54,   180,   181,   203,    50,   318,   193,    46,    47,    51,
      52,    53,    48,    49,   -61,   209,   325,   333,   334,   335,
     205,   210,   212,    50,   214,   215,   165,   218,    51,    52,
      53,    43,   220,    44,   223,    54,   337,   231,   224,   351,
     232,    46,    47,   241,   235,   239,    48,    49,   249,   257,
      43,   250,    44,   252,    54,   263,   255,    50,   339,   254,
      46,    47,    51,    52,    53,    48,    49,  -119,   261,    43,
     266,    44,   276,   283,   288,   268,    50,   340,   275,    46,
      47,    51,    52,    53,    48,    49,   282,   286,    54,   291,
     281,   -44,  -122,   294,   295,    50,   297,   299,   300,   313,
      51,    52,    53,   301,   314,   319,   316,    54,   323,   326,
     342,   329,   332,   330,   138,   139,   140,   141,   142,   143,
     336,   345,   346,   347,   349,   350,    54,   353,    14,   315,
     100,   309,   226,   213,     0,     0,    58
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-206))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      66,    67,    27,    84,    71,    17,    31,   107,    78,    32,
       8,     3,   217,    15,    13,    17,    83,     3,    13,    11,
      34,    13,   205,    15,    16,    17,    18,   147,    35,    15,
      16,    17,    18,    34,    13,     7,    33,    29,    63,    19,
      38,     4,    83,    29,   111,    24,    22,   114,     3,    15,
      16,    17,    18,     0,    77,    62,   239,    21,    13,   126,
       4,     5,    64,    65,    61,   185,    42,     7,   273,    83,
     136,    63,    71,    65,    35,    39,    71,    63,    50,    65,
      44,    45,    83,    47,    35,    83,    38,    50,   188,    81,
      82,    83,    56,   118,   117,    81,    82,    83,   281,    22,
      72,    73,    74,    75,    76,    77,    62,   119,    83,    72,
      73,    74,    75,    76,    77,    81,     5,    40,    51,     8,
      43,    83,   222,    46,   190,   191,   192,    60,     4,     5,
      11,   201,    55,   200,    66,    67,    68,     5,    38,   164,
       8,     4,     5,     3,   167,    26,    83,    28,    83,    30,
       7,   217,    84,     3,   220,    36,    37,    13,    11,    12,
      41,    42,     3,     3,   230,     3,     3,   234,    11,     8,
      18,    52,     7,    26,    83,    28,    57,    58,    59,    83,
     205,     3,   249,    36,    37,    18,   252,   268,    41,    42,
       3,   291,     3,    11,   275,     3,    83,    14,    83,    52,
       4,     4,    83,    83,    57,    58,    59,   273,    26,    14,
      28,    83,    30,    12,   239,     8,     7,    18,    36,    37,
       3,     7,     7,    41,    42,     4,   238,    26,     4,    28,
      83,    83,    13,    30,    52,   301,    68,    36,    37,    57,
      58,    59,    41,    42,    38,     4,   313,   328,   329,   330,
      38,    26,    14,    52,     7,     7,   281,     5,    57,    58,
      59,    26,     5,    28,    25,    83,   332,     4,    50,   350,
       4,    36,    37,    18,     7,    38,    41,    42,     3,    14,
      26,    13,    28,    24,    83,     7,    12,    52,    53,    13,
      36,    37,    57,    58,    59,    41,    42,    25,    18,    26,
      30,    28,    23,    14,    14,    28,    52,    53,    27,    36,
      37,    57,    58,    59,    41,    42,    30,    18,    83,     3,
      38,    23,    50,    14,     7,    52,    24,     4,    14,    71,
      57,    58,    59,    20,    30,    14,    31,    83,     4,     7,
      33,     8,    54,     8,    72,    73,    74,    75,    76,    77,
       7,     4,     7,     7,    60,    28,    83,    32,     9,   297,
      67,   292,   189,   175,    -1,    -1,    30
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
      52,    57,    58,    59,    83,   120,    83,   119,   114,    30,
      91,    13,     7,    98,     3,   137,     3,     3,     3,     3,
     145,   121,   133,   153,    13,    71,   124,     8,     4,     5,
       7,    18,    12,   141,    11,   102,     3,    15,    16,    17,
      18,    29,    63,    65,    81,    82,    83,   105,   172,   180,
     105,    83,    83,     3,    11,    13,   165,   169,   173,   180,
     185,     3,     3,    18,   131,     3,    91,     8,    38,    90,
      83,    14,   165,   102,   120,   138,   182,    83,    13,   183,
       4,     4,   122,   123,   146,   186,   188,     7,    72,    73,
      74,    75,    76,    77,   159,   160,   162,   168,    64,    65,
     171,   172,    66,    67,    84,   175,   165,    83,    14,   165,
     164,   165,    91,   103,   104,   120,   115,     8,    13,    24,
     142,    12,     7,   165,    18,     3,     7,     7,     4,     4,
      83,    13,   190,   180,   195,   167,   161,   163,   169,   170,
     178,   174,   179,    68,   134,   154,    13,    71,   132,     4,
       5,   116,   118,    30,   120,    38,    91,    94,    96,     4,
      26,     4,    14,   164,     7,     7,   147,   193,     5,   187,
       5,   189,   169,    25,    50,   166,   173,   180,   180,   180,
     176,     4,     4,   128,   126,     7,   125,   165,    90,    38,
     103,    18,    22,    40,    43,    46,    55,    97,   143,     3,
      13,     4,    24,   195,    13,    12,   180,    14,   180,   135,
     155,    18,   165,     7,   117,   103,    30,    95,    28,   165,
     181,   180,   194,   191,   177,    27,    23,   106,   112,   129,
     127,    38,    30,    14,   102,   139,    18,   148,    14,   195,
     102,     3,   107,   108,    14,     7,   103,    24,   144,     4,
      14,    20,   192,   136,    16,    18,    81,   172,   184,   106,
      51,    60,   109,    71,    30,    97,    31,   140,   180,    14,
      33,    61,   156,     4,   110,   165,     7,   149,   157,     8,
       8,   130,    54,   102,   102,   102,     7,   180,   158,    53,
      53,   150,    33,   113,   111,     4,     7,     7,   151,    60,
      28,   102,   152,    32
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
#line 352 "compiler.y"
    { strcpy(identifiers, "\0");}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 353 "compiler.y"
    {
  //verifyMatrix(hashVariables);
  //verifyUsed(hashVariables);

}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 360 "compiler.y"
    { strcpy(identifiers, "\0");}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 361 "compiler.y"
    {
 // verifyMatrix(hashVariables);
 // verifyUsed(hashVariables);
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 370 "compiler.y"
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
#line 438 "compiler.y"
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
	printf("%s\n", auxVariable);
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
#line 511 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 511 "compiler.y"
    {dim2 = currentNumber;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 511 "compiler.y"
    {dimension=2;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 512 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 512 "compiler.y"
    {dimension=1;}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 517 "compiler.y"
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
#line 553 "compiler.y"
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
		terminate();
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
#line 577 "compiler.y"
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
	expressionNode = NULL;
	functionNode->children[3] = commandNode;
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
#line 612 "compiler.y"
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
		terminate();
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
#line 642 "compiler.y"
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
#line 670 "compiler.y"
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
#line 700 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 706 "compiler.y"
    {
  fillTreeNode(caseNode, "caso-padrao", "CASO");
  treeNode* padraoNode = newTreeNode();
  fillTreeNode(padraoNode, "padrao", "CASO");
  caseNode -> children[0] = padraoNode; 
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 713 "compiler.y"
    {
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children [2] = pararNode;
}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 721 "compiler.y"
    {
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children[2] = pararNode;
}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 729 "compiler.y"
    {functionNode->children[2] = functionInternalVariables;}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 731 "compiler.y"
    {
// Em tipos_variaveis ira retornar o tipo de retorno da funcao, a qual sera acrescentada.
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
  convertTypeReverseUpper(convertType(currentType),functionNode->children[0]->type);  
  returnFlag = 0;
}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 740 "compiler.y"
    {functionNode->children[2] = functionInternalVariables;}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 744 "compiler.y"
    {
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
      convertTypeReverseUpper(convertType(currentType),functionNode->children[0]->type);  
  returnFlag = 0;
}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 754 "compiler.y"
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

  case 64:

/* Line 1806 of yacc.c  */
#line 797 "compiler.y"
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

  case 66:

/* Line 1806 of yacc.c  */
#line 842 "compiler.y"
    {expressionNode=NULL; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 843 "compiler.y"
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
      }
      else if( functionAux->returnType != varRelations[0] && in_comparacao == 0)
      {
	printf("Expressao de retorno nao e compativel com o retorno da funcao %s na linha %d.\n", currentScope, nLine);
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

  case 68:

/* Line 1806 of yacc.c  */
#line 895 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 897 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 899 "compiler.y"
    {
  	List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
	if(identifier_temp==NULL)
	{
	  printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
	  terminate();
	} 
	else
	{
	  ((variable*)(identifier_temp->info))->used = 1;
	}
}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 911 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 913 "compiler.y"
    {
  	List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
	if(identifier_temp==NULL)
	{
	  printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
	  terminate();
	} 
	else
	{
	  ((variable*)(identifier_temp->info))->used = 1;
	}
  
}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 926 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 928 "compiler.y"
    {
  strcpy(currentFunction, currentIdentifier);
  in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
  List *functionList = lookupStringFunction(hashFunction, currentFunction);
  if(functionList!=NULL)
  {
    function* functionAux = ((function*)(functionList)->info);
    functionNode = newTreeNode();
    fillTreeNode(functionNode, currentFunction, "CHAMADA-FUNCAO");
    functionNode->children[0] = functionAux -> functionTree; 
    //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  }
}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 942 "compiler.y"
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
  //expressionNode = popStack(stackExpressionNode);
  addNodeIntoGlobalTree(functionNode);
  
}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1073 "compiler.y"
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

  case 78:

/* Line 1806 of yacc.c  */
#line 1131 "compiler.y"
    {

	//adiciono o nó de expressão a direita do nó de atribuição
    attributionNode->children[1] = expressionNode;
    //retorno o nós de atribuição para null
    expressionNode=NULL;
    
    //adiciono o nó de atribuição na árvore de execução do programa (in main, falta fazer arvores para funções)
    //verifica que nao esta dentro de condicional tambem (enquanto ou se)
    addAttributionNodeIntoGlobalTree();

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
  in_function = 0;
}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1158 "compiler.y"
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

  case 81:

/* Line 1806 of yacc.c  */
#line 1204 "compiler.y"
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

  case 82:

/* Line 1806 of yacc.c  */
#line 1218 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
	
		//adiciono o nó de expressão a direita do nó de atribuição
    	attributionNode->children[1] = expressionNode;
    	//retorno o nós de atribuição para null
    	expressionNode=NULL;
    
    	//adiciono o nó de atribuição na árvore de execução do programa (in main, falta fazer arvores para funções)
    	//verifica que nao esta dentro de condicional tambem (enquanto ou se)
    	addAttributionNodeIntoGlobalTree();
	
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
  in_function = 0;
}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1246 "compiler.y"
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
      typeAttribute = T_SEMRETORNO;
      
  strcpy(currentVariable, auxVariable);
}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1279 "compiler.y"
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
	//printf("%s\n", identifiers);
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
	  //printRelationship(varRelations, currentRelationPos);
	  printf("Valores incompativeis na linha %d.\n", nLine);
	  terminate();
	}
	else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0)
	{	
	  printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  terminate();
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

  case 86:

/* Line 1806 of yacc.c  */
#line 1393 "compiler.y"
    {
currentRelationComparison = 0;
}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1397 "compiler.y"
    {
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-se","CONDICIONAL");   
    addConditionNodeIntoGlobalTree();
    
    //retorno os nós de atribuição para null
    expressionNode = NULL;
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1408 "compiler.y"
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

  case 89:

/* Line 1806 of yacc.c  */
#line 1422 "compiler.y"
    {currentRelationPos = 0;}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1423 "compiler.y"
    {
  commandNode = globalTree;
  conditionNode = commandNode -> children[0];
  commandNode->children[0] = NULL;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1432 "compiler.y"
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

  case 93:

/* Line 1806 of yacc.c  */
#line 1443 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1450 "compiler.y"
    {  
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-faca-enquanto","CONDICIONAL");
     conditionNode->children[0] = expressionNode;
     conditionNode->children[1] = commandNode;
     addConditionNodeIntoGlobalTree();
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1458 "compiler.y"
    {in_condicional = 0;}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1460 "compiler.y"
    {
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-enquanto","CONDICIONAL");
    //seta para null o nó de expressão (que será construído na parte de expressão)
    expressionNode = NULL;
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1468 "compiler.y"
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

  case 99:

/* Line 1806 of yacc.c  */
#line 1485 "compiler.y"
    {in_condicional = 0; currentRelationPos = 0 ; strcpy(identifiers,"\0");}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1488 "compiler.y"
    {

  //commandNode = NULL;
  expressionNode = NULL;
  //conditionNode = NULL;

  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1500 "compiler.y"
    {
  conditionNode = newTreeNode();
  fillTreeNode(conditionNode,"condicao-para","CONDICAO");
  addConditionNodeIntoGlobalTree();

}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1506 "compiler.y"
    {strcpy(identifiers,"\0"); currentRelationPos=0;}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1507 "compiler.y"
    {
  attributionNode = newTreeNode();
  fillTreeNode(attributionNode,":=","ATRIBUICAO");
  
  treeNode *idAux = newTreeNode();
  fillTreeNode(idAux, currentIdentifier, "VARIAVEL");
  //printf("%s", currentIdentifier);
  strcpy(currentVariable, currentIdentifier);
  attributionNode->children[0] = idAux;
  conditionNode->children[0] = attributionNode;
}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1519 "compiler.y"
    {
  attributionNode->children[1] = expressionNode;
  expressionNode = NULL;

}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1525 "compiler.y"
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

  case 107:

/* Line 1806 of yacc.c  */
#line 1540 "compiler.y"
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
  
 /* 
  treeNode *idAux = newTreeNode();
  fillTreeNode(idAux, currentIdentifier, "VARIAVEL");
  
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

  case 108:

/* Line 1806 of yacc.c  */
#line 1588 "compiler.y"
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

  case 109:

/* Line 1806 of yacc.c  */
#line 1598 "compiler.y"
    {
  expressionNode = NULL;
 
  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1606 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos=0;}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1607 "compiler.y"
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
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 &&((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else
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
    fillTreeNode(idAux, currentIdentifier, "VARIAVEL");
    
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

  case 113:

/* Line 1806 of yacc.c  */
#line 1690 "compiler.y"
    {
if(varRelations[0] != T_LITERAL && varRelations[0] != T_LOGICO)
  switchType = varRelations[0];
else
  switchType = T_SEMRETORNO;
}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1699 "compiler.y"
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

  case 116:

/* Line 1806 of yacc.c  */
#line 1713 "compiler.y"
    {currentRelationPos=0;}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1714 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1722 "compiler.y"
    {in_logico = 1;}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1723 "compiler.y"
    {
  if (in_comparacao = 1 && in_condicional == 0)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printRelationship(varRelations, currentRelationComparison);
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
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printf("%s", identifiers);
    //printRelationship(varRelations, currentRelationComparison);
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

  case 122:

/* Line 1806 of yacc.c  */
#line 1752 "compiler.y"
    {in_logico = 1;}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1753 "compiler.y"
    {
  if (in_comparacao = 1 && in_condicional == 0)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printRelationship(varRelations, currentRelationComparison);
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
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printf("%s", identifiers);
    //printRelationship(varRelations, currentRelationComparison);
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
#line 1783 "compiler.y"
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
      terminate();
    }
    else if(returnTypeArgument != varRelations[0] && in_comparacao == 0)
    {	
      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
      terminate();
    }
    
    if(functionNode->children[1] == NULL)
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
      //functionArgument->next=NULL;
      aux->next = argumentNode;
      argumentNode->children[0] = expressionNode;
      argumentNode->children[1] = functionArgument;
    }

  }
  //strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  currentRelationComparison = 0;
  expressionNode = NULL;
 }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1853 "compiler.y"
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
      terminate();
    }
    else if(returnTypeArgument != varRelations[0] && in_comparacao == 0)
    {	
      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
      terminate();
    }
    
    if(functionNode->children[1] == NULL)
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
  //strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  currentRelationComparison = 0;
  expressionNode = NULL;
}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1930 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1932 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1933 "compiler.y"
    {
    if (in_comparacao = 1 && in_condicional == 0)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printRelationship(varRelations, currentRelationComparison);
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

  case 131:

/* Line 1806 of yacc.c  */
#line 1956 "compiler.y"
    {operadorDeNivelTres();}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1956 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1958 "compiler.y"
    { operadorDeNivelDois(">"); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1959 "compiler.y"
    { operadorDeNivelDois(">="); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1960 "compiler.y"
    { operadorDeNivelDois("="); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1961 "compiler.y"
    { operadorDeNivelDois("<"); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1962 "compiler.y"
    { operadorDeNivelDois("<="); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1963 "compiler.y"
    { operadorDeNivelDois("<>"); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1966 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1967 "compiler.y"
    { operadorDeNivelUm(); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1967 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1972 "compiler.y"
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

  case 146:

/* Line 1806 of yacc.c  */
#line 2020 "compiler.y"
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

  case 149:

/* Line 1806 of yacc.c  */
#line 2066 "compiler.y"
    {	operadorDeNivelZero("/"); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 2066 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 2069 "compiler.y"
    {
  if(strcmp(currentType, "inteiro")!=0)
  {
    printf("Operador %% so aceita inteiros na linha %d.\n", nLine);
    terminate();
  }
}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 2076 "compiler.y"
    { operadorDeNivelZero("%"); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 2077 "compiler.y"
    {
    if(strcmp(currentType, "inteiro")!=0)
    {
      printf("Operador %% so aceita inteiro na linha %d.\n", nLine);
      terminate();
    }
}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 2084 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 2086 "compiler.y"
    { operadorDeNivelZero("*"); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 2086 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 2088 "compiler.y"
    { operadorDeMenorNivel("^"); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 2088 "compiler.y"
    { swapoutZeroMenor(); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 2092 "compiler.y"
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

  case 161:

/* Line 1806 of yacc.c  */
#line 2112 "compiler.y"
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

  case 162:

/* Line 1806 of yacc.c  */
#line 2139 "compiler.y"
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
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else
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

  case 163:

/* Line 1806 of yacc.c  */
#line 2214 "compiler.y"
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
      terminate();
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate();
    }else
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

  case 164:

/* Line 1806 of yacc.c  */
#line 2303 "compiler.y"
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

  case 165:

/* Line 1806 of yacc.c  */
#line 2359 "compiler.y"
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

  case 166:

/* Line 1806 of yacc.c  */
#line 2402 "compiler.y"
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
	terminate();
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

  case 167:

/* Line 1806 of yacc.c  */
#line 2451 "compiler.y"
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

  case 168:

/* Line 1806 of yacc.c  */
#line 2469 "compiler.y"
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

  case 169:

/* Line 1806 of yacc.c  */
#line 2497 "compiler.y"
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
	if(stackParentesis == NULL) stackParentesis = createStack();
	stackParentesis = addNodeIntoStack(swapZeroMenor, stackParentesis);
	stackParentesis = addNodeIntoStack(swapUmZero, stackParentesis);
	stackParentesis = addNodeIntoStack(swapDoisUm, stackParentesis);
	stackParentesis = addNodeIntoStack(swapTresDois, stackParentesis);
	stackParentesis = addNodeIntoStack(expressionNode, stackParentesis);
	
	swapZeroMenor = swapUmZero = swapDoisUm = swapTresDois = expressionNode = NULL;

}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 2516 "compiler.y"
    {
	treeNode* aux = (treeNode*) popStack(stackParentesis);
	if(aux->children[0] == NULL){
		aux->children[0] = expressionNode;
	} else {
		aux->children[1]->children[0] = expressionNode; 
	}
	expressionNode = aux;
	swapTresDois = 	(treeNode*) popStack(stackParentesis);
	swapDoisUm = (treeNode*) popStack(stackParentesis);
	swapUmZero = (treeNode*) popStack(stackParentesis);
	swapZeroMenor =(treeNode*) popStack(stackParentesis);
	printf("FINAL\n");
	//printNode(expressionNode,13,0);
}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 2532 "compiler.y"
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

  case 172:

/* Line 1806 of yacc.c  */
#line 2552 "compiler.y"
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

  case 173:

/* Line 1806 of yacc.c  */
#line 2572 "compiler.y"
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
	terminate();
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
	terminate();
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
	terminate();
	in_function = 0;
      }
     }
  
    List *functionList = lookupStringFunction(hashFunction, currentFunction);
    if(functionList!=NULL)
    {
      function* functionAux = ((function*)(functionList)->info);
      functionNode = newTreeNode();
      fillTreeNode(functionNode, currentFunction, "CHAMADA-FUNCAO");
      functionNode->children[0] = functionAux -> functionTree; 
      
      stackExpressionNode = addNodeIntoStack(expressionNode, stackExpressionNode);
      expressionNode=NULL;
    }
  }
}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 2672 "compiler.y"
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
    
    expressionNode = popStack(stackExpressionNode);   
   
   if(expressionNode==NULL) {
    expressionNode=functionNode;
    }
   else {
      expressionNode->children[1] = functionNode;
    }
    
  strcpy(functionArguments, "\0");
  //strcpy(identifiers, "\0");
  //currentRelationPos = 0;
  in_function = 0;
  }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 2823 "compiler.y"
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

  case 177:

/* Line 1806 of yacc.c  */
#line 2837 "compiler.y"
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

  case 178:

/* Line 1806 of yacc.c  */
#line 2851 "compiler.y"
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

  case 179:

/* Line 1806 of yacc.c  */
#line 2865 "compiler.y"
    { countLine=0; delimitadorNivelUm(); tempDelimitadorNivelUm = expressionNode;  expressionNode=NULL; }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 2865 "compiler.y"
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

  case 181:

/* Line 1806 of yacc.c  */
#line 2886 "compiler.y"
    {
	isMatrix = 1;
}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 2890 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 2890 "compiler.y"
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

  case 184:

/* Line 1806 of yacc.c  */
#line 2910 "compiler.y"
    {
	isMatrix = 1; 
	expressionNode = tempDelimitadorNivelZero;
 }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 2914 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 2915 "compiler.y"
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

  case 188:

/* Line 1806 of yacc.c  */
#line 2938 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 2938 "compiler.y"
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

  case 191:

/* Line 1806 of yacc.c  */
#line 2964 "compiler.y"
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

  case 192:

/* Line 1806 of yacc.c  */
#line 2988 "compiler.y"
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
//	printNode(tempDelimitadorNivelZero,13,0);
	
}
    break;



/* Line 1806 of yacc.c  */
#line 5381 "compiler.tab.c"
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
#line 3015 "compiler.y"


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

FILE *abre_arquivo(char *filename, char *modo) {
	FILE *file;

	if (!(file = fopen(filename, modo))) {
		printf("Erro na abertura do arquivo %s\n", filename);
	}
	return file;
}

Program* compila(char *nome_programa) {

	//Criando as hash
    hashVariables = createHash(MAX_HASH);
    hashFunction = createHash(MAX_HASH);
    createPrimitives();

	//Contador de linhas
	nLine = 1;
	
	//Erro
	err = 0;
    
	yyin = abre_arquivo(nome_programa, "r");
	if (yyin == NULL) exit(1);

	yyparse();
	
	//Reiniciando o buffer do flex
	YY_FLUSH_BUFFER;
	
	if(err==1){
		return NULL;
	}
	
	Program *p = createProgram();
	//Copia as paradas
	p->name = nome_programa;
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
			if(tam==0) printf("Não há programas a serem executados. Favor compilar algum programa e voltar a tentar.\n");
			else {
				for(i=0;i<tam;i++){
					printf("%d\n",tam);
					program = (Program*)getListPosition(listPrograms,i);
					if (program)
						printf("%d - %s\n", i+1, program->name);
				}
				scanf("%d",&option);
				scanf("%c",&lixo);
				if(program != NULL) {
					executeProgram(program);
					scanf("%c",&lixo);
				}else
					printf("O programa desejado não pode se executado ou não existe.\n");
			}
			break;
		case 3:
			printf("Entre com o programa do qual deseja ver a arvore\n");
			scanf("%d",&option);
			scanf("%c",&lixo);
			printNode(program->exec, 13, 0);		
			scanf("%c",&lixo);
			break;
		case 4:
			tam = sizeList(listPrograms);
			if(tam==0) printf("Não há programas compilados. Você pode compilar programas na opção 1 do menu.\n");
			else {
				for(i=0;i<tam;i++){
					printf("%d\n",tam);
					program = (Program*)getListPosition(listPrograms,i);
					if (program)
						printf("%d - %s\n", i+1, program->name);
				}
			}
			scanf("%c",&lixo);
			break;
		case 5: 
			listarFiles();
			scanf("%c",&lixo);
			break;
		case 6:
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


