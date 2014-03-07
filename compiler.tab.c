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
#define IN_DEBUG_MODE 0

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

void desallocEverything()
{
      List *auxDesalloc = listPrograms;
      while(auxDesalloc!=NULL)
      {	
	//freeTable(((Program*)(auxDesalloc->info))->hashVariables);
	//freeTableFunction(((Program*)(auxDesalloc->info))->hashFunctions);
	desallocNodes(((Program*)(auxDesalloc->info))->exec);
	auxDesalloc = auxDesalloc->next;
      }
}



/* Line 268 of yacc.c  */
#line 328 "compiler.tab.c"

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
     token_fimfaca = 289,
     token_fimvariaveis = 290,
     token_funcao = 291,
     token_imprima = 292,
     token_imprimaln = 293,
     token_inicio = 294,
     token_inteiro = 295,
     token_inteiros = 296,
     token_leia = 297,
     token_leialn = 298,
     token_literais = 299,
     token_literal = 300,
     token_logico = 301,
     token_logicos = 302,
     token_matriz = 303,
     token_minimo = 304,
     token_nao = 305,
     token_ou = 306,
     token_padrao = 307,
     token_para = 308,
     token_parar = 309,
     token_passo = 310,
     token_reais = 311,
     token_real = 312,
     token_retorne = 313,
     token_se = 314,
     token_seleciona = 315,
     token_fimseleciona = 316,
     token_senao = 317,
     token_variaveis = 318,
     token_verdadeiro = 319,
     token_mais = 320,
     token_menos = 321,
     token_vezes = 322,
     token_dividir = 323,
     token_mod = 324,
     token_maismais = 325,
     token_menosmenos = 326,
     token_atribuicao = 327,
     token_maior = 328,
     token_menor = 329,
     token_maiori = 330,
     token_menori = 331,
     token_igual = 332,
     token_diferente = 333,
     token_el = 334,
     token_oul = 335,
     token_negacao = 336,
     token_variavel_caracter = 337,
     token_string = 338,
     token_identificador = 339,
     token_circ = 340
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
#line 455 "compiler.tab.c"

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
#define YYLAST   379

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  114
/* YYNRULES -- Number of rules.  */
#define YYNRULES  195
/* YYNRULES -- Number of states.  */
#define YYNSTATES  357

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
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
      87,     0,    -1,    -1,    19,    84,     7,    88,   100,    90,
      39,    99,    30,    -1,    -1,    19,    84,     7,    89,    90,
      39,    99,    30,    -1,    63,    91,    35,    -1,    63,    35,
      -1,    -1,    93,     8,    92,     7,    -1,    91,    93,     8,
      92,     7,    -1,    40,    -1,    57,    -1,    21,    -1,    45,
      -1,    46,    -1,    94,    -1,    84,    -1,    93,     5,    84,
      -1,    -1,    -1,    48,    13,    18,    14,    13,    95,    18,
      96,    14,    24,    98,    -1,    -1,    48,    13,    18,    14,
      24,    97,    98,    -1,    41,    -1,    22,    -1,    44,    -1,
      56,    -1,    47,    -1,    -1,    99,   122,    -1,    99,    11,
      99,    12,    -1,    -1,   100,    36,    84,   101,   115,    -1,
      -1,    36,    84,   102,   115,    -1,    -1,   103,   122,    -1,
      11,   103,    12,    -1,    -1,   105,    -1,   122,    -1,   105,
     122,    -1,   184,    -1,    -1,   113,   108,   107,    -1,    -1,
     113,   109,   110,    -1,    -1,    -1,    52,   111,     8,   103,
      54,   112,     7,    61,    -1,    61,    -1,    -1,    23,     3,
     188,     4,     8,   103,    54,   114,     7,    -1,    23,     3,
     188,     4,     8,   103,    -1,    -1,     3,   121,     4,    39,
     116,   104,    30,    -1,    -1,     3,   121,     4,    91,   117,
      39,   104,    30,    -1,    -1,    -1,     3,   121,     4,     8,
      92,   118,    91,   119,    39,   104,    30,    -1,    -1,     3,
     121,     4,     8,    92,   120,    39,   104,    30,    -1,    84,
       8,    92,    -1,   121,     5,    84,     8,    92,    -1,    -1,
      -1,    58,   123,   169,     7,    -1,    -1,    37,     3,   106,
     124,     4,     7,    -1,    -1,    38,     3,   106,   125,     4,
       7,    -1,    -1,    42,     3,    84,   126,     4,     7,    -1,
      -1,    43,     3,    84,   127,     4,     7,    -1,    -1,    -1,
      84,   128,     3,   168,     4,   129,     7,    -1,    -1,    -1,
      84,    13,    18,    14,    72,   130,   169,   131,     7,    -1,
      -1,    -1,    -1,    84,    13,    18,    14,    13,   132,    18,
     133,    14,    72,   169,   134,     7,    -1,    -1,    -1,    84,
      72,   135,   169,   136,     7,    -1,    -1,    -1,    -1,    -1,
      59,   137,     3,   169,   138,     4,   139,    27,   103,   140,
     160,    -1,    -1,    -1,    -1,    -1,    28,   141,   103,   142,
      34,    26,     3,   169,   143,     4,   144,     7,    -1,    -1,
      -1,    -1,    -1,    26,     3,   145,   169,   146,     4,   147,
      28,   103,   148,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,   149,     3,   150,    84,   151,    24,
     184,   152,    20,   184,   153,    55,   184,   154,     4,   155,
      28,   103,   156,    32,    -1,    -1,    -1,    -1,    60,   157,
       3,    84,   158,     4,   159,   107,    -1,    -1,    -1,    62,
     161,   103,   162,    33,    -1,    33,    -1,    -1,    -1,   164,
     165,    25,    -1,    -1,    -1,   166,   167,    51,    -1,   169,
      -1,   168,     5,   169,    -1,    -1,   173,    -1,    -1,   169,
     172,   173,   170,    -1,    -1,   169,   163,   171,   173,    -1,
      73,    -1,    75,    -1,    77,    -1,    74,    -1,    76,    -1,
      78,    -1,   177,    -1,    -1,   173,   175,   174,   177,    -1,
     173,   176,    -1,    65,    -1,    66,    -1,    15,    -1,    17,
      -1,   189,    -1,   184,    -1,    -1,   177,    68,   178,   184,
      -1,    -1,    -1,    -1,   177,   179,    69,   180,   184,   181,
      -1,    -1,   177,    67,   182,   184,    -1,    -1,   177,    85,
     183,   184,    -1,   176,    -1,    18,    -1,    16,    -1,    84,
      -1,    66,    84,    -1,    84,    13,    18,    14,    -1,    -1,
      84,    13,    18,    14,    13,   185,    18,    14,    -1,    82,
      -1,    83,    -1,    -1,     3,   186,   169,     4,    -1,    64,
      -1,    29,    -1,    -1,    84,   187,     3,   168,     4,    -1,
     176,    -1,    18,    -1,    16,    -1,    82,    -1,    -1,    -1,
      11,   190,   194,   191,    12,    -1,    -1,    -1,    13,   192,
     199,   193,    14,    -1,    -1,    -1,   194,     5,    13,   195,
     199,   196,    14,    -1,    -1,    -1,    13,   197,   199,   198,
      14,    -1,   184,    -1,   199,     5,   184,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   344,   344,   344,   352,   351,   358,   359,   359,   361,
     429,   496,   496,   496,   496,   496,   496,   498,   498,   500,
     500,   500,   501,   501,   503,   503,   503,   503,   503,   505,
     505,   505,   507,   506,   563,   562,   617,   617,   617,   618,
     618,   619,   619,   621,   623,   622,   642,   641,   668,   676,
     667,   682,   685,   684,   690,   693,   692,   708,   707,   724,
     741,   723,   744,   743,   762,   804,   846,   849,   849,   902,
     901,   920,   919,   938,   937,   968,   967,   998,  1014,   997,
    1036,  1088,  1036,  1113,  1159,  1173,  1113,  1200,  1239,  1199,
    1353,  1364,  1379,  1380,  1352,  1389,  1400,  1407,  1416,  1388,
    1418,  1426,  1443,  1446,  1417,  1454,  1459,  1460,  1473,  1478,
    1493,  1527,  1537,  1453,  1543,  1544,  1615,  1543,  1624,  1638,
    1623,  1644,  1647,  1648,  1647,  1672,  1673,  1672,  1697,  1765,
    1845,  1846,  1848,  1848,  1870,  1870,  1872,  1873,  1874,  1875,
    1876,  1877,  1880,  1881,  1881,  1882,  1883,  1883,  1885,  1930,
    1973,  1973,  1975,  1975,  1978,  1985,  1986,  1977,  1995,  1995,
    1997,  1997,  1999,  2000,  2018,  2036,  2109,  2184,  2236,  2235,
    2326,  2342,  2371,  2371,  2404,  2420,  2438,  2437,  2592,  2592,
    2606,  2620,  2635,  2635,  2635,  2660,  2660,  2660,  2684,  2685,
    2684,  2708,  2708,  2707,  2733,  2756
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
  "token_fimpara", "token_fimse", "token_fimfaca", "token_fimvariaveis",
  "token_funcao", "token_imprima", "token_imprimaln", "token_inicio",
  "token_inteiro", "token_inteiros", "token_leia", "token_leialn",
  "token_literais", "token_literal", "token_logico", "token_logicos",
  "token_matriz", "token_minimo", "token_nao", "token_ou", "token_padrao",
  "token_para", "token_parar", "token_passo", "token_reais", "token_real",
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
     335,   336,   337,   338,   339,   340
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    88,    87,    89,    87,    90,    90,    90,    91,
      91,    92,    92,    92,    92,    92,    92,    93,    93,    95,
      96,    94,    97,    94,    98,    98,    98,    98,    98,    99,
      99,    99,   101,   100,   102,   100,   103,   103,   103,   104,
     104,   105,   105,   106,   108,   107,   109,   107,   111,   112,
     110,   110,   114,   113,   113,   116,   115,   117,   115,   118,
     119,   115,   120,   115,   121,   121,   121,   123,   122,   124,
     122,   125,   122,   126,   122,   127,   122,   128,   129,   122,
     130,   131,   122,   132,   133,   134,   122,   135,   136,   122,
     137,   138,   139,   140,   122,   141,   142,   143,   144,   122,
     145,   146,   147,   148,   122,   149,   150,   151,   152,   153,
     154,   155,   156,   122,   157,   158,   159,   122,   161,   162,
     160,   160,   164,   165,   163,   166,   167,   163,   168,   168,
     168,   169,   170,   169,   171,   169,   172,   172,   172,   172,
     172,   172,   173,   174,   173,   173,   175,   175,   176,   176,
     177,   177,   178,   177,   179,   180,   181,   177,   182,   177,
     183,   177,   184,   184,   184,   184,   184,   184,   185,   184,
     184,   184,   186,   184,   184,   184,   187,   184,   188,   188,
     188,   188,   190,   191,   189,   192,   193,   189,   195,   196,
     194,   197,   198,   194,   199,   199
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
#define YYPACT_NINF -202
static const yytype_int16 yypact[] =
{
      38,   -44,    64,    67,  -202,    45,    74,    22,    31,    -5,
     -16,    93,  -202,    37,    96,  -202,  -202,     2,   104,  -202,
     134,  -202,  -202,  -202,   121,    59,   294,    24,    63,  -202,
     134,   116,   294,  -202,  -202,  -202,  -202,  -202,   136,  -202,
     141,  -202,  -202,   147,  -202,  -202,   148,   157,   158,   159,
    -202,  -202,  -202,  -202,     0,  -202,   155,    51,  -202,  -202,
     160,   152,  -202,   145,  -202,   161,    12,    12,    94,    97,
     163,     7,   177,   183,   166,  -202,   188,   294,     3,   108,
    -202,   185,  -202,     7,   161,   295,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,   111,  -202,  -202,    36,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,   204,    48,    49,  -202,
    -202,     7,   117,   192,     7,     7,  -202,   294,  -202,   118,
     200,    21,   169,   181,  -202,   178,     7,  -202,   195,   211,
     212,   213,   217,   218,   142,   215,    12,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,     7,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,   156,   169,  -202,     8,   169,
     115,   169,   191,   295,   193,   294,  -202,  -202,   227,  -202,
     207,    28,   221,     7,   229,   230,   241,   246,  -202,  -202,
     249,  -202,   251,     7,   232,   209,    48,     7,    12,    12,
      12,  -202,   254,   257,  -202,  -202,   255,  -202,     7,   118,
     224,   234,   295,  -202,   295,  -202,   248,    89,  -202,   264,
    -202,   258,   135,  -202,  -202,  -202,  -202,   244,    12,   261,
     271,    12,   256,    48,  -202,  -202,  -202,    49,  -202,  -202,
    -202,    12,  -202,  -202,   269,     7,  -202,   284,   169,   118,
     295,  -202,  -202,   262,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,   265,     7,  -202,  -202,    12,   251,  -202,  -202,  -202,
    -202,  -202,   267,   253,  -202,   169,  -202,   270,   266,  -202,
     281,   161,   169,   286,  -202,   285,    12,  -202,   161,   305,
    -202,   287,   297,   309,   295,  -202,   288,   295,   313,   308,
     304,  -202,   251,   295,    82,   253,    -1,   263,  -202,   296,
      89,   298,  -202,  -202,    12,   311,   -19,  -202,  -202,  -202,
    -202,   323,  -202,  -202,  -202,  -202,     7,  -202,  -202,  -202,
     321,  -202,  -202,  -202,  -202,  -202,   322,   328,   169,  -202,
     290,   161,   161,   161,   334,    12,   295,   247,   260,  -202,
    -202,   310,  -202,  -202,   342,  -202,   340,   343,  -202,  -202,
     291,   329,  -202,   161,   295,   317,  -202
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -202,  -202,  -202,  -202,   347,   -71,   -24,   -12,  -202,  -202,
    -202,  -202,    58,     4,  -202,  -202,  -202,   -81,  -192,  -202,
     292,    65,  -202,  -202,  -202,  -202,  -202,  -202,  -202,   331,
    -202,  -202,  -202,  -202,  -202,  -202,   -25,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,   189,   -67,  -202,  -202,  -202,  -114,  -202,  -202,
     -98,   176,  -202,  -202,  -202,  -202,  -202,  -202,   -66,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -201
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -177
static const yytype_int16 yytable[] =
{
      99,    99,    55,   123,   106,    24,    55,   119,    60,   151,
      86,   117,   243,    74,   323,    86,   122,   256,   104,    15,
     105,   194,    87,    88,    89,    90,    31,    87,    88,    89,
      90,    13,   210,   186,   166,    42,    91,    23,    55,  -176,
       3,    91,   118,   324,   156,   167,    63,   159,   268,   128,
      43,   313,    44,   116,    45,    78,    79,     1,    10,   171,
     314,    46,    47,    87,     4,    89,    48,    49,    16,   223,
     181,    92,    75,    93,     5,   292,    92,    50,    93,  -125,
     195,    -2,    51,    52,    53,    10,    16,    16,   151,    94,
      95,    96,   299,   162,    94,    95,    96,    87,   307,    89,
     308,   138,   139,   140,   141,   142,   143,    24,    54,    25,
       8,   245,    26,   148,   149,    12,   152,   153,  -154,   197,
     198,    21,   228,   229,   230,   151,    25,    42,   239,    32,
     246,   238,    19,   247,   154,    22,   248,    28,   203,   254,
     198,   205,    43,    33,    44,   249,    59,    56,    62,    61,
      64,    66,   181,    46,    47,   259,    42,    82,    48,    49,
      67,    68,    69,    77,   309,   261,   103,    80,   265,    50,
      81,    43,    84,    44,    51,    52,    53,   242,   101,   203,
     111,   102,    46,    47,   113,   272,   112,    48,    49,   274,
     287,   115,   120,   169,  -122,   127,   310,   293,    50,   121,
      54,   157,    16,    51,    52,    53,   158,    43,   165,    44,
     181,   137,   170,   172,   173,   203,   174,   175,    46,    47,
    -125,   176,   177,    48,    49,   191,   178,    24,   179,    54,
     -62,   208,   204,   209,    50,   211,   213,   214,   321,    51,
      52,    53,   138,   139,   140,   141,   142,   143,   215,   328,
     336,   337,   338,   216,   219,  -125,   221,   224,   232,   203,
     225,   233,   236,   240,   241,    54,   244,   252,   255,   340,
     260,   253,   354,    43,   257,    44,   279,   138,   139,   140,
     141,   142,   143,   258,    46,    47,    43,   264,    44,    48,
      49,   266,   269,   271,   278,   286,   285,    46,    47,   291,
      50,   342,    48,    49,   289,    51,    52,    53,   294,   284,
     -44,   297,   300,    50,   343,    34,   298,   302,    51,    52,
      53,    43,   303,    44,   304,   322,   317,   326,   329,   319,
     332,    54,    46,    47,    35,   316,   333,    48,    49,    36,
      37,   339,    38,   345,    54,   335,   348,   349,    50,   356,
     350,    39,   352,    51,    52,    53,    14,   353,   318,   100,
     312,    58,   212,   227,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-202))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      66,    67,    27,    84,    71,    17,    31,    78,    32,   107,
       3,     8,   204,    13,    33,     3,    83,   218,    11,    35,
      13,    13,    15,    16,    17,    18,    22,    15,    16,    17,
      18,    36,     4,   147,    13,    11,    29,    35,    63,     3,
      84,    29,    39,    62,   111,    24,    42,   114,   240,    13,
      26,    52,    28,    77,    30,     4,     5,    19,    63,   126,
      61,    37,    38,    15,     0,    17,    42,    43,    84,   183,
     136,    64,    72,    66,     7,   276,    64,    53,    66,    51,
      72,    36,    58,    59,    60,    63,    84,    84,   186,    82,
      83,    84,   284,   117,    82,    83,    84,    15,    16,    17,
      18,    73,    74,    75,    76,    77,    78,   119,    84,     5,
      36,    22,     8,    65,    66,    84,    67,    68,    69,     4,
       5,    84,   188,   189,   190,   223,     5,    11,   199,     8,
      41,   198,    39,    44,    85,    39,    47,     3,   163,     4,
       5,   165,    26,    84,    28,    56,    30,    84,     7,    13,
       3,     3,   218,    37,    38,   221,    11,    12,    42,    43,
       3,     3,     3,     8,    82,   231,     3,     7,   235,    53,
      18,    26,    11,    28,    58,    59,    60,   202,    84,   204,
       3,    84,    37,    38,    18,   252,     3,    42,    43,   255,
     271,     3,    84,    12,    25,    84,   294,   278,    53,    14,
      84,    84,    84,    58,    59,    60,    14,    26,     8,    28,
     276,     7,    34,    18,     3,   240,     4,     4,    37,    38,
      51,     4,     4,    42,    43,    69,    84,   239,    13,    84,
      39,     4,    39,    26,    53,    14,     7,     7,   304,    58,
      59,    60,    73,    74,    75,    76,    77,    78,     7,   316,
     331,   332,   333,     7,     5,    51,     5,    25,     4,   284,
      51,     4,     7,    39,    30,    84,    18,     3,    24,   335,
      14,    13,   353,    26,    13,    28,    23,    73,    74,    75,
      76,    77,    78,    12,    37,    38,    26,    18,    28,    42,
      43,     7,    30,    28,    27,    14,    30,    37,    38,    14,
      53,    54,    42,    43,    18,    58,    59,    60,     3,    39,
      23,    14,    24,    53,    54,    21,     7,     4,    58,    59,
      60,    26,    14,    28,    20,    14,    30,     4,     7,    31,
       8,    84,    37,    38,    40,    72,     8,    42,    43,    45,
      46,     7,    48,    33,    84,    55,     4,     7,    53,    32,
       7,    57,    61,    58,    59,    60,     9,    28,   300,    67,
     295,    30,   173,   187,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    87,    84,     0,     7,    88,    89,    36,   100,
      63,    90,    84,    36,    90,    35,    84,    91,    93,    39,
     102,    84,    39,    35,    93,     5,     8,    99,     3,   115,
     101,    99,     8,    84,    21,    40,    45,    46,    48,    57,
      92,    94,    11,    26,    28,    30,    37,    38,    42,    43,
      53,    58,    59,    60,    84,   122,    84,   121,   115,    30,
      92,    13,     7,    99,     3,   141,     3,     3,     3,     3,
     149,   123,   137,   157,    13,    72,   128,     8,     4,     5,
       7,    18,    12,   145,    11,   103,     3,    15,    16,    17,
      18,    29,    64,    66,    82,    83,    84,   106,   176,   184,
     106,    84,    84,     3,    11,    13,   169,   173,   177,   184,
     189,     3,     3,    18,   135,     3,    92,     8,    39,    91,
      84,    14,   169,   103,   122,   142,   186,    84,    13,   187,
     124,   125,   126,   127,   150,   190,   192,     7,    73,    74,
      75,    76,    77,    78,   163,   164,   166,   172,    65,    66,
     175,   176,    67,    68,    85,   179,   169,    84,    14,   169,
     168,   169,    92,   116,   117,     8,    13,    24,   146,    12,
      34,   169,    18,     3,     4,     4,     4,     4,    84,    13,
     194,   184,   199,   171,   165,   167,   173,   174,   182,   178,
     183,    69,   138,   158,    13,    72,   136,     4,     5,   118,
     120,   104,   105,   122,    39,    92,    95,    97,     4,    26,
       4,    14,   168,     7,     7,     7,     7,   151,   197,     5,
     191,     5,   193,   173,    25,    51,   170,   177,   184,   184,
     184,   180,     4,     4,   132,   130,     7,   129,   169,    91,
      39,    30,   122,   104,    18,    22,    41,    44,    47,    56,
      98,   147,     3,    13,     4,    24,   199,    13,    12,   184,
      14,   184,   139,   159,    18,   169,     7,   119,   104,    30,
      96,    28,   169,   185,   184,   198,   195,   181,    27,    23,
     107,   113,   133,   131,    39,    30,    14,   103,   143,    18,
     152,    14,   199,   103,     3,   108,   109,    14,     7,   104,
      24,   148,     4,    14,    20,   196,   140,    16,    18,    82,
     176,   188,   107,    52,    61,   110,    72,    30,    98,    31,
     144,   184,    14,    33,    62,   160,     4,   111,   169,     7,
     153,   161,     8,     8,   134,    55,   103,   103,   103,     7,
     184,   162,    54,    54,   154,    33,   114,   112,     4,     7,
       7,   155,    61,    28,   103,   156,    32
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
#line 344 "compiler.y"
    {in_logico = 0 ; in_comparacao = 0; in_condicional = 0; currentRelationPos = 0; isMatrix = 0; argumentNumber = 0; strcpy(identifiers, "\0");}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 345 "compiler.y"
    {
  //verifyMatrix(hashVariables);
  verifyUsed(hashVariables);

}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 352 "compiler.y"
    {in_logico = 0 ; in_comparacao = 0; in_condicional = 0;currentRelationPos = 0; isMatrix = 0; argumentNumber = 0; strcpy(identifiers, "\0");}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 353 "compiler.y"
    {
 // verifyMatrix(hashVariables);
 verifyUsed(hashVariables);
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 362 "compiler.y"
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
	  terminate(); return;
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
	  terminate(); return;
	}
	varName = strtok(NULL, " ");
      }
    }
  strcpy(identifiers, "\0");
  }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 430 "compiler.y"
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
		terminate(); return;
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
	  terminate(); return;
	}
	varName = strtok(NULL, " ");
      }
    }
  strcpy(identifiers, "\0");
  }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 500 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 500 "compiler.y"
    {dim2 = currentNumber;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 500 "compiler.y"
    {dimension=2;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 501 "compiler.y"
    {dim1 = currentNumber;}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 501 "compiler.y"
    {dimension=1;}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 507 "compiler.y"
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
      terminate(); return;
      destroyList(currentParameters);
    }
  strcpy(identifiers, "\0");
}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 542 "compiler.y"
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
		terminate(); return;
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
#line 563 "compiler.y"
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
      terminate(); return;
    }
  strcpy(identifiers, "\0");
}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 597 "compiler.y"
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
		terminate(); return;
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
#line 623 "compiler.y"
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
#line 642 "compiler.y"
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
#line 661 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 668 "compiler.y"
    {
  fillTreeNode(caseNode, "caso-padrao", "CASO");
  treeNode* padraoNode = newTreeNode();
  fillTreeNode(padraoNode, "padrao", "CASO");
  caseNode -> children[0] = padraoNode; 
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 676 "compiler.y"
    {
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children [2] = pararNode;
}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 685 "compiler.y"
    {
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children[2] = pararNode;
}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 693 "compiler.y"
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
#line 708 "compiler.y"
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
#line 724 "compiler.y"
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
#line 741 "compiler.y"
    {functionNode->children[2] = functionInternalVariables;}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 744 "compiler.y"
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
#line 763 "compiler.y"
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
      terminate(); return;
    }
  strcpy(identifiers, "\0");
}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 805 "compiler.y"
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
      terminate(); return;
    }
  strcpy(identifiers, "\0");
}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 849 "compiler.y"
    {expressionNode=NULL; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 850 "compiler.y"
    {
  if(strcmp(currentScope, "main") != 0)
  {
    List* functionList = lookupStringFunction(hashFunction, currentScope);
    function* functionAux = ((function*)(functionList->info));
    if(functionAux->returnType==T_SEMRETORNO)
    {
      printf("A funcao %s nao possui retorno.\n", currentScope);
      terminate(); return;
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
	    terminate(); return;
	  }
	  in_logico=0;
      }
      else if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
      {
	printf("Tipos nao compativeis no retorno na funcao %s na linha %d\n", currentScope, nLine);
	terminate(); return;
      }
      else if( functionAux->returnType != varRelations[0] && in_comparacao == 0)
      {
	printf("Expressao de retorno nao e compativel com o retorno da funcao %s na linha %d.\n", currentScope, nLine);
	terminate(); return;
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
    terminate(); return;
  }
  currentRelationPos = 0;
  expressionNode=NULL;
  strcpy(identifiers, "\0");
}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 902 "compiler.y"
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
#line 918 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 920 "compiler.y"
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
#line 936 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 938 "compiler.y"
    {
  List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
  if(identifier_temp==NULL)
  {
    printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
    terminate(); return;
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
#line 966 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 968 "compiler.y"
    {
  List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
  if(identifier_temp==NULL)
  {
    printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
    terminate(); return;
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
#line 996 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos = 0;}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 998 "compiler.y"
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
#line 1014 "compiler.y"
    { 
  List *functionList = lookupStringFunction(hashFunction, currentFunction);
  if(functionList == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
    terminate(); return;
  }
  else
  {
    if(argumentNumber != ((function*)(functionList->info))->arity)
    {  
          printf("%d\n", argumentNumber);

      printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
      terminate(); return;
    }
  
  }
  argumentNumber=0;
addNodeIntoGlobalTree(functionNode);  
}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1036 "compiler.y"
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
			terminate(); return;
		}
		if(((variable*)(currVariable->info))->matrix!=1){
			printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(currVariable->info))->name);
			terminate(); return;
		}
		if(((variable*)(currVariable->info))->dimension != 1){
			printf("Erro na linha %d, %s possui dimensao 2.\n", nLine, ((variable*)(currVariable->info))->name);
			terminate(); return;
		}
		if(((variable*)(currVariable->info))->nColumn <= currentNumber ){
			printf("Erro na linha %d, %s possui %d posicoes.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
			terminate(); return;
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
		terminate(); return;
	}
}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1088 "compiler.y"
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
		  terminate(); return;
		}
		else if(((variable*)(currVariable->info))->type!=varRelations[0]){
			printf("Atribuição de tipos invalidos na linha %d.\n", nLine);
			terminate(); return;
		}
	}
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1113 "compiler.y"
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
			terminate(); return;
		}
		if(((variable*)(currVariable->info))->matrix!=1){
			printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(currVariable->info))->name);
			terminate(); return;
		}
		if(((variable*)(currVariable->info))->dimension != 2){
			printf("Erro na linha %d, %s possui dimensao 1.\n", nLine, ((variable*)(currVariable->info))->name);
			terminate(); return;
		}
		if(((variable*)(currVariable->info))->nColumn <= currentNumber ){
			printf("Erro na linha %d, %s possui %d colunas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
			terminate(); return;
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
		terminate(); return;
	}
}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1159 "compiler.y"
    {
	List* currVariable = lookupStringVariable(hashVariables, currentVariable);
	if (currVariable != NULL){
		if(((variable*)(currVariable->info))->nLine <= currentNumber ){
			printf("Erro na linha %d, %s possui %d linhas apenas.\n", nLine, ((variable*)(currVariable->info))->name,((variable*)(currVariable->info))->nColumn );
			terminate(); return;
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
#line 1173 "compiler.y"
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
		  terminate(); return;
		}
		else if(((variable*)(currVariable->info))->type!=varRelations[0]){
			printf("Atribuição de tipos invalidos na linha %d.\n", nLine);
			terminate(); return;
		}
	}
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1200 "compiler.y"
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
      terminate(); return;
    }
      
  strcpy(currentVariable, auxVariable);
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1239 "compiler.y"
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
	  terminate(); return;
	} 
	else if((varRelations[0] == T_LITERAL || varRelations[0] == T_CARACTER) && currentRelationPos > 1) //caracter ou literal
	{
	  printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	  terminate(); return;
	}
	else if(in_logico==1 && in_condicional == 0)
	{
	  if((((variable*)(identifier_temp->info))->type) != 4)
	  {
	    printf("%d %d", in_logico, in_condicional);
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel. aaa\n",nLine);
	    terminate(); return;
	  }
	  else
	    ((variable*)(identifier_temp->info))->used=1;
	  in_logico=0;
	}
	else if(!verifyRelationship(varRelations, currentRelationPos) && in_comparacao == 0)
	{
	  printf("Valores incompativeis na linha %d.\n", nLine);
	  terminate(); return;
	}
	else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0 && ((variable*)(identifier_temp->info))->type != 4)
	{	
	  printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  terminate(); return;
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
	  terminate(); return;
	}
	else
	{
	  strcat(auxVariable, " ");
	  strcat(auxVariable, currentScope);
	  List *identifier_temp = lookupStringVariable(hashVariables, auxVariable);
	  if(identifier_temp == NULL)
	  {
	    printf("Variavel %s nao declarada na linha %d.\n",currentIdentifier, nLine);
	    terminate(); return;
	  }
	  else if((varRelations[0] == T_CARACTER || varRelations[0] == T_LITERAL) && currentRelationPos > 1) //caracter ou literal
	  {
	    printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	    terminate(); return;
	  }
	  else if(in_logico==1 && in_condicional == 0)
	  {
	    if((((variable*)(identifier_temp->info))->type) != 4)
	    {
	      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	      terminate(); return;
	    }
	    else
	      ((variable*)(identifier_temp->info))->used=1;
	  in_logico=0;
	  }
	  else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0 && ((variable*)(identifier_temp->info))->type != 4)
	  {
		printf("1338");
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	    terminate(); return;
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
#line 1349 "compiler.y"
    {
currentRelationComparison = 0;
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1353 "compiler.y"
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
#line 1364 "compiler.y"
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
#line 1379 "compiler.y"
    {currentRelationPos = 0;}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1380 "compiler.y"
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
#line 1389 "compiler.y"
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
#line 1400 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1407 "compiler.y"
    {  
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-faca-enquanto","CONDICIONAL");
    conditionNode->children[0] = expressionNode;
    conditionNode->children[1] = commandNode;
    addNodeIntoGlobalTree(conditionNode);
    expressionNode = NULL;
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1416 "compiler.y"
    {in_condicional = 0;}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1418 "compiler.y"
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
#line 1426 "compiler.y"
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
#line 1443 "compiler.y"
    {in_condicional = 0; currentRelationPos = 0 ; strcpy(identifiers,"\0");}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1446 "compiler.y"
    {
  expressionNode = NULL;

  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1454 "compiler.y"
    {
  conditionNode = newTreeNode();
  fillTreeNode(conditionNode,"condicao-para","CONDICAO");
  addNodeIntoGlobalTree(conditionNode);
}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1459 "compiler.y"
    {strcpy(identifiers,"\0"); currentRelationPos=0;}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1460 "compiler.y"
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
#line 1473 "compiler.y"
    {
  attributionNode->children[1] = expressionNode;
  expressionNode = NULL;
}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1478 "compiler.y"
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
#line 1493 "compiler.y"
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
#line 1527 "compiler.y"
    {
if(!verifyRelationship(varRelations, currentRelationPos))
  {
    printf("Valores incompativeis na linha %d\n", nLine);
    terminate(); return;
  }
strcpy(identifiers,"\0"); 
currentRelationPos = 0;
}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1537 "compiler.y"
    {
  expressionNode = NULL;
  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1543 "compiler.y"
    {strcpy(identifiers, "\0"); currentRelationPos=0;}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1544 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate(); return;
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate(); return;
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
      terminate(); return;
    }
    else if(((variable*)(identifier_temp->info))->used == 0 &&((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate(); return;
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
#line 1615 "compiler.y"
    {
if(varRelations[0] != T_LITERAL && varRelations[0] != T_LOGICO)
  switchType = varRelations[0];
else
  switchType = T_SEMRETORNO;
}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1624 "compiler.y"
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
#line 1638 "compiler.y"
    {currentRelationPos=0;}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1639 "compiler.y"
    {
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1647 "compiler.y"
    {in_logico = 1; }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1648 "compiler.y"
    {
  if (in_comparacao = 1 && in_condicional == 0)
  {	
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate(); return;
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
  else if (in_condicional == 1)
  {	
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate(); return;
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1672 "compiler.y"
    {in_logico = 1;}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1673 "compiler.y"
    {
  if (in_comparacao = 1 && in_condicional == 0)
  {	
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate(); return;
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
    else if (in_condicional == 1)
  {	
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate(); return;
	}
    currentRelationComparison=0;
    in_comparacao = 0;
  }
}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1698 "compiler.y"
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
      terminate(); return;
    }
    else if(returnTypeArgument != varRelations[0] && in_comparacao == 0)
    {	
      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
      terminate(); return;
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
#line 1766 "compiler.y"
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
      terminate(); return;
    }
    else if(returnTypeArgument != varRelations[0] && in_comparacao == 0)
    {	
      printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
      terminate(); return;
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
#line 1846 "compiler.y"
    { swapoutTresDois(); in_logico = 0;}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1848 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1849 "compiler.y"
    {
    if (in_comparacao = 1 && in_condicional == 0)
    {	
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate(); return;
	}
    currentRelationComparison=0;
    in_comparacao = 1;
  }
    else if (in_condicional == 1)
  {
    if(!verifyRelationshipCondition(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	  terminate(); return;
	}
    currentRelationComparison=0;
  }
}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1870 "compiler.y"
    {operadorDeNivelTres();}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1870 "compiler.y"
    { swapoutTresDois(); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1872 "compiler.y"
    { operadorDeNivelDois(">"); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1873 "compiler.y"
    { operadorDeNivelDois(">="); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1874 "compiler.y"
    { operadorDeNivelDois("="); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1875 "compiler.y"
    { operadorDeNivelDois("<"); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1876 "compiler.y"
    { operadorDeNivelDois("<="); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1877 "compiler.y"
    { operadorDeNivelDois("<>"); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1880 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1881 "compiler.y"
    { operadorDeNivelUm(); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1881 "compiler.y"
    { swapoutDoisUm(); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1886 "compiler.y"
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
#line 1931 "compiler.y"
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
#line 1975 "compiler.y"
    {	operadorDeNivelZero("/"); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1975 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1978 "compiler.y"
    {
  if(strcmp(currentType, "inteiro")!=0)
  {
    printf("Operador %% so aceita inteiros na linha %d.\n", nLine);
    terminate(); return;
  }
}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1985 "compiler.y"
    { operadorDeNivelZero("%"); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1986 "compiler.y"
    {
    if(strcmp(currentType, "inteiro")!=0)
    {
      printf("Operador %% so aceita inteiro na linha %d.\n", nLine);
      terminate(); return;
    }
}
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1993 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 1995 "compiler.y"
    { operadorDeNivelZero("*"); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1995 "compiler.y"
    { swapoutUmZero(); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 1997 "compiler.y"
    { operadorDeMenorNivel("^"); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 1997 "compiler.y"
    { swapoutZeroMenor(); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 2001 "compiler.y"
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
#line 2019 "compiler.y"
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
#line 2042 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate(); return;
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate(); return;
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
      terminate(); return;
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate(); return;
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
#line 2110 "compiler.y"
    {
  if(strcmp(currentScope, "main")==0)
  {
    List *identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate(); return;
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0)
    {  printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
       terminate(); return;
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
      terminate(); return;
    }
    else if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate(); return;
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
#line 2185 "compiler.y"
    {
  List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate(); return;
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
      terminate(); return;
    }
  }
  if(identifier_temp != NULL)
  {
  	//monta a arvore
  	treeMatrixOneDimension( ((variable*)(identifier_temp->info))->name , currentNumber);
  	
    if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate(); return;
    }else if(((variable*)(identifier_temp->info))->matrix!=1){
      printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(identifier_temp->info))->name);
      terminate(); return;
    }
    else if(((variable*)(identifier_temp->info))->nColumn <= currentNumber ){
	printf("Erro na linha %d, %s possui %d posicoes.\n", nLine, ((variable*)(identifier_temp->info))->name,((variable*)(identifier_temp->info))->nColumn );
	terminate(); return;
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
#line 2236 "compiler.y"
    {
  List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate(); return;
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
      terminate(); return;
    }
  }
  if(identifier_temp != NULL)
  {
  	//monta a arvore com uma dimensão
  	treeMatrixOneDimension( ((variable*)(identifier_temp->info))->name , currentNumber);
  
    if(((variable*)(identifier_temp->info))->used == 0 && ((variable*)(identifier_temp->info))->matrix == 0){
      printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
      terminate(); return;
    }else if(((variable*)(identifier_temp->info))->matrix!=1){
      printf("Erro na linha %d, %s nao e uma matriz.\n", nLine, ((variable*)(identifier_temp->info))->name);
      terminate(); return;
    }
    else if(((variable*)(identifier_temp->info))->nColumn <= currentNumber ){
	printf("Erro na linha %d, %s possui %d colunas.\n", nLine, ((variable*)(identifier_temp->info))->name,((variable*)(identifier_temp->info))->nColumn );
	terminate(); return;
    }
  }
}
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 2279 "compiler.y"
    {
   List *identifier_temp = NULL;
  if(strcmp(currentScope, "main")==0)
  {
    identifier_temp = lookupStringVariable(hashVariables, currentIdentifier);
    if(identifier_temp==NULL)
    {
      printf("Variavel %s nao declarada na linha %d\n",currentIdentifier, nLine);
      terminate(); return;
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
      terminate(); return;
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
	terminate(); return;
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
#line 2327 "compiler.y"
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
#line 2343 "compiler.y"
    {
  if(strlen(limitString) > MAX_LITERAL+2)
  {
    printf("Tamanho de literal passou do limite de %d caracteres na linha %d\n", MAX_LITERAL,nLine);
    terminate(); return;
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
#line 2371 "compiler.y"
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
#line 2390 "compiler.y"
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
	//printNode(expressionNode,13,0);
}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 2405 "compiler.y"
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
#line 2421 "compiler.y"
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
#line 2438 "compiler.y"
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
	terminate(); return;
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
	terminate(); return;
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
	terminate(); return;
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
#line 2562 "compiler.y"
    { 
  List *functionList = lookupStringFunction(hashFunction, currentFunction);
  if(functionList == NULL)
  {
    printf("Funcao %s nao declarada na linha %d.\n", currentFunction, nLine);
    terminate(); return;
  }
  else
  {
    if(argumentNumber != ((function*)(functionList->info))->arity)
    {  
      printf("%d\n", argumentNumber);
      printf("Funcao %s com aridade errada na linha %d.\n", currentFunction, nLine);
      terminate(); return;
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
#line 2593 "compiler.y"
    {
  if(switchType != T_INTEIRO)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
    terminate(); return;
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
#line 2607 "compiler.y"
    {
  if(switchType != T_REAL)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
    terminate(); return;
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
#line 2621 "compiler.y"
    {
  if(switchType != T_CARACTER)
  {
    printf("Caso nao compativel com variavel associada na linha %d\n", nLine);
    terminate(); return;
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
#line 2635 "compiler.y"
    { countLine=0; delimitadorNivelUm(); tempDelimitadorNivelUm = expressionNode;  expressionNode=NULL; }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 2635 "compiler.y"
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
			terminate(); return;
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
#line 2656 "compiler.y"
    {
	isMatrix = 1;
}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 2660 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 2660 "compiler.y"
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
			terminate(); return;
			((variable*)(identifier_temp->info))->used = 0;
		}else{
			((variable*)(identifier_temp->info))->used = 1;
		}
	}
}
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 2680 "compiler.y"
    {
	isMatrix = 1; 
	expressionNode = tempDelimitadorNivelZero;
 }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 2684 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 2685 "compiler.y"
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
			terminate(); return;
			((variable*)(identifier_temp->info))->used = 0;
		}
	}
}
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 2708 "compiler.y"
    {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;}
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 2708 "compiler.y"
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
			terminate(); return;
			((variable*)(identifier_temp->info))->used =0;
		}
	}
}
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 2734 "compiler.y"
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
			terminate(); return;
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
#line 2758 "compiler.y"
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
			terminate(); return;
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
#line 5170 "compiler.tab.c"
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
#line 2783 "compiler.y"


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
    Program *auxProgram;
    int option, tam, i;
    char lixo;
    char * programa;
    
    showBoasVindas();
    while(1){
    
		option = showMenu();
		
		switch(option){
		case 1: //Compilar
			makeStartLine();
			programa = (char*) solicitaNomePrograma();
			makeStartLine();
			printf("## Abrindo %s\n", programa);
			program = compila(programa);
			if(program==NULL || err == 1){
				printf("## Não foi possível compilar o programa devido a discordâncias da linguagem de entrada.\n## Por favor verifique as linhas indicadas acima e tente novamente.\n");
				
			}else {
				tam = sizeList(listPrograms);
				for(i=0;i<tam;i++){
					auxProgram = (Program*)getListPosition(listPrograms,i);
					if(!strcmp(auxProgram->name, programa)) break;
				}
				
				if(i==tam){
					listPrograms = insertList(listPrograms, program);
				}else{
					freeTable(auxProgram->hashVariables);
					freeTableFunction(auxProgram->hashFunctions);
					desallocNodes(auxProgram->exec);
					auxProgram->hashVariables = program->hashVariables;
					auxProgram->hashFunctions = program->hashFunctions;
					auxProgram->exec = program->exec;
				}
	   			
	   			printf("## Programa compilado com éxito, pronto para ser executado.\n");
	   		}
	   		makeEndLine();
	   		printf("## Pressione <enter> para voltar ao menu principal\n");	
			printf("## ");
	   		scanf("%c",&lixo);
			break;
		case 2: //Executar
			tam = sizeList(listPrograms);
			if(tam==0){ 
				printf("##Não há programas a serem executados. Favor compilar algum programa e voltar a tentar.\n"); 
				makeEndLine();
				printf("## Pressione <enter> para voltar ao menu principal\n");	
				printf("## ");
				scanf("%c",&lixo);
			} else {
				makeStartLine();
				printf("## Programas compilados e prontos para serem executados\n");
				makeStartLine();
				for(i=0;i<tam;i++){
					program = (Program*)getListPosition(listPrograms,i);
					if (program){
						
						printf("## %d - %s\n", i+1, program->name);
					}
				}
				makeEndLine();
				printf("## Entre com o número do programa que deseja executar\n");
				printf("## ");
				scanf("%d",&option);
				scanf("%c",&lixo);
				if(option<1 || option> tam){ 
					makeStartLine();
					printf("O programa desejado não pode se executado ou não existe.\n");
					makeEndLine();
					printf("## Pressione <enter> para voltar ao menu principal\n");	
					printf("## ");
					scanf("%c",&lixo);
					break; 
				}
				program = (Program*)getListPosition(listPrograms,option-1);
				if(program != NULL) {
					makeStartLine();
					printf("## Executando o programa: %s\n", program->name);
					makeStartLine();
					executeProgram(program);
					printf("\n");
					makeEndLine();
					printf("## Pressione <enter> para voltar ao menu principal\n");	
					printf("## ");
					scanf("%c",&lixo);
				}else {
					makeStartLine();
					printf("O programa desejado não pode se executado ou não existe.\n");
					makeEndLine();
					printf("## Pressione <enter> para voltar ao menu principal\n");
					printf("## ");
					scanf("%c",&lixo);
				}
			}
			break;
		case 3: //Mostrar a árvore  
			tam = sizeList(listPrograms);
			makeStartLine();
			if(tam==0){ printf("## Não há programas compilados.\n## Favor compilar algum programa e voltar a tentar.\n"); makeEndLine();
			printf("## Pressione <enter> para voltar ao menu principal\n");
			printf("## "); scanf("%c",&lixo); break;}			
			
			makeStartLine();
			printf("## Programas compilados:\n");
			makeStartLine();
			for(i=0;i<tam;i++){
				program = (Program*)getListPosition(listPrograms,i);
				if (program){
					
					printf("## %d - %s\n", i+1, program->name);
				}
			}
			makeEndLine();
			printf("## Entre com o número do programa do qual deseja ver a arvore\n");
			printf("## ");
			scanf("%d",&option);
			scanf("%c",&lixo);
			if(option<1 || option>tam){ makeStartLine(); printf("## O programa desejado não pode ser encontrado.\n");
			printf("## Pressione <enter> para voltar ao menu principal\n"); printf("## "); scanf("%d",&option); }
			else { 
				program = (Program*)getListPosition(listPrograms,option-1);
				makeStartLine();
				printf("## Árvore do programa %s\n", program->name);
				makeStartLine();
				printNode(program->exec, 13, 0, 0);		
			}
			makeEndLine();
			printf("## Pressione <enter> para voltar ao menu principal\n");	
			printf("## ");
			scanf("%c",&lixo);
			break;
		case 4: //Listar programas compilados
			tam = sizeList(listPrograms);
			if(tam==0) {
				makeStartLine(); 
				printf("##Não há programas compilados.\n## Você pode compilar programas na opção 1 do menu.\n");
				makeEndLine();
			} else {
				for(i=0;i<tam;i++){
					program = (Program*)getListPosition(listPrograms,i);
					if (program)
						printf("## %d - %s\n", i+1, program->name);
				}
			}
			printf("## Pressione <enter> para voltar ao menu principal\n");
			printf("## ");
			scanf("%c",&lixo);
			break;
		case 5: //listar aquivos .gpt
			listarFiles();
			printf("## Pressione <enter> para voltar ao menu principal\n");
			printf("## ");
			scanf("%c",&lixo);
			break;
		case 6: //sobre
			showSobre();
			break;
		case 7: //sair
			desallocEverything();
			showDespedida();
			desallocEverything();
			return 0;
		default: break;
		}
		
	}
	
    
	if(IN_DEBUG_MODE){
	  	treeNode* aux = globalTree;
  	printNode(aux, 13, 0, 0);
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
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void)
{
	printf("Erro na Linha: %d\n", nLine);
	err = 1;
}

void terminate(){

	freeTable(hashVariables);
	freeTableFunction(hashFunction);
	desallocNodes(globalTree);
	 err = 1;
}

