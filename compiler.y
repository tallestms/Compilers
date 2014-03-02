%{
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

%}

%token token_abrep
%token token_fechap
%token token_virgula
%token token_ponto
%token token_pontov
%token token_doisp
%token token_jogodav
%token token_apostrofe
%token token_abrec
%token token_fechac
%token token_abrecol
%token token_fechacol
%token token_numreal_comsinal
%token token_numreal
%token token_numinteiro_comsinal
%token token_numinteiro
%token token_algoritmo
%token token_ate
%token token_caracter
%token token_caracteres
%token token_caso
%token token_de
%token token_e
%token token_enquanto
%token token_entao
%token token_faca
%token token_falso
%token token_fim
%token token_fimenquanto
%token token_fimpara
%token token_fimse
%token token_fimvariaveis
%token token_funcao
%token token_imprima
%token token_imprimaln
%token token_inicio
%token token_inteiro
%token token_inteiros
%token token_leia
%token token_leialn
%token token_literais
%token token_literal
%token token_logico
%token token_logicos
%token token_matriz
%token token_minimo
%token token_nao
%token token_ou
%token token_padrao
%token token_para
%token token_parar
%token token_passo
%token token_reais
%token token_real
%token token_retorne
%token token_se
%token token_seleciona
%token token_fimseleciona
%token token_senao
%token token_variaveis
%token token_verdadeiro
%token token_mais
%token token_menos
%token token_vezes
%token token_dividir
%token token_mod
%token token_maismais
%token token_menosmenos
%token token_atribuicao
%token token_maior
%token token_menor
%token token_maiori
%token token_menori
%token token_igual
%token token_diferente
%token token_el
%token token_oul
%token token_negacao
%token token_variavel_caracter
%token token_string
%token token_identificador
%token token_circ

%start PROG

%%
PROG:  token_algoritmo token_identificador token_pontov { strcpy(identifiers, "\0");} BLOCO_FUNCOES BLOCO_VARIAVEIS token_inicio BLOCO token_fim  
{
  //verifyMatrix(hashVariables);
  //verifyUsed(hashVariables);

}
|
token_algoritmo token_identificador
token_pontov { strcpy(identifiers, "\0");} BLOCO_VARIAVEIS token_inicio BLOCO token_fim 
{
 // verifyMatrix(hashVariables);
 // verifyUsed(hashVariables);
}
;
BLOCO_VARIAVEIS: token_variaveis VARIAVEIS token_fimvariaveis |
		  token_variaveis token_fimvariaveis | /*Empty*/;
		  
VARIAVEIS: VARIAVEIS_IDENTIFICADORES token_doisp TIPOS_VARIAVEIS token_pontov
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
  | VARIAVEIS VARIAVEIS_IDENTIFICADORES token_doisp TIPOS_VARIAVEIS token_pontov
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
  };

TIPOS_VARIAVEIS: token_inteiro | token_real | token_caracter | token_literal | token_logico | INICIALIZAR_MATRIZ;
 
VARIAVEIS_IDENTIFICADORES: token_identificador | VARIAVEIS_IDENTIFICADORES token_virgula token_identificador
  
INICIALIZAR_MATRIZ: token_matriz token_abrecol token_numinteiro token_fechacol token_abrecol {dim1 = currentNumber;} token_numinteiro {dim2 = currentNumber;} token_fechacol token_de TIPOS_VARIAVEIS_MATRIZ {dimension=2;} | 
	token_matriz token_abrecol token_numinteiro token_fechacol token_de {dim1 = currentNumber;} TIPOS_VARIAVEIS_MATRIZ {dimension=1;};
TIPOS_VARIAVEIS_MATRIZ: token_inteiros | token_caracteres | token_literais | token_reais | token_logicos;

BLOCO:  /*Empty*/ | BLOCO COMANDO | BLOCO token_abrec BLOCO token_fechac;
BLOCO_FUNCOES: BLOCO_FUNCOES token_funcao token_identificador 
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
FUNCAO 
{
  List *identifier_temp = lookupStringFunction(hashFunction, currentScope); //Procurando funcao dentro da hash de funcoes
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
  currentFunctionArity = 0; //Variavel global de aridade retornando ao valor 0.
  strcpy(currentScope, "main"); //Escopo retornando ao valor global
  returnFlag = 0;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
| token_funcao token_identificador //Mesma coisa do de cima.
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
FUNCAO
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
};

BLOCO_AUXILIAR: /*Empty*/ | BLOCO_AUXILIAR COMANDO | token_abrec BLOCO_AUXILIAR token_fechac;
BLOCO_FUNCAO: /*Empty*/ | REPETICAO_COMANDO ;
REPETICAO_COMANDO: COMANDO | REPETICAO_COMANDO COMANDO;

BLOCO_IMPRIMA: FATOR 
BLOCO_SWITCH:  BLOCO_SWITCH_AUX
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
BLOCO_SWITCH | 
BLOCO_SWITCH_AUX
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
FIM_BLOCO_SWITCH
{
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
};
FIM_BLOCO_SWITCH: token_padrao
{
  fillTreeNode(caseNode, "caso-padrao", "CASO");
  treeNode* padraoNode = newTreeNode();
  fillTreeNode(padraoNode, "padrao", "CASO");
  caseNode -> children[0] = padraoNode; 
}
token_doisp BLOCO_AUXILIAR token_parar
{
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children [2] = pararNode;
}
token_pontov token_fimseleciona |
token_fimseleciona ;
BLOCO_SWITCH_AUX: token_caso token_abrep FATOR_CASE token_fechap token_doisp BLOCO_AUXILIAR token_parar
{
  treeNode* pararNode = newTreeNode();
  fillTreeNode(pararNode, "parar-caso", "PARAR-CASO");
  caseNode -> children[2] = pararNode;
} token_pontov 
| token_caso token_abrep FATOR_CASE token_fechap token_doisp BLOCO_AUXILIAR;

FUNCAO: token_abrep VARIAVEIS_FUNCAO token_fechap token_inicio 
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
BLOCO_FUNCAO token_fim 
| token_abrep VARIAVEIS_FUNCAO token_fechap VARIAVEIS 
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


token_inicio BLOCO_FUNCAO token_fim 
| token_abrep VARIAVEIS_FUNCAO token_fechap token_doisp 
TIPOS_VARIAVEIS 
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
VARIAVEIS 
{functionNode->children[2] = functionInternalVariables;}
token_inicio BLOCO_FUNCAO token_fim
| token_abrep VARIAVEIS_FUNCAO token_fechap token_doisp TIPOS_VARIAVEIS 
/*Retorno sera verificado aqui em todas as funcoes com mesmo nome!*/
{

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
token_inicio BLOCO_FUNCAO token_fim

VARIAVEIS_FUNCAO: token_identificador token_doisp TIPOS_VARIAVEIS
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
|
VARIAVEIS_FUNCAO token_virgula token_identificador token_doisp TIPOS_VARIAVEIS
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
| /*Empty*/;  

COMANDO:
token_retorne {expressionNode=NULL; } EXPR token_pontov
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
|
token_imprima token_abrep BLOCO_IMPRIMA 
{
  treeNode* imprimaNode = newTreeNode();
  
  char typeImprima[10];
  convertTypeReverseUpper(convertType(currentType), typeImprima);
  fillTreeNode(imprimaNode,"CHAMADA FUNCAO" , "imprima");
	  
	  treeNode* imprimaNodeChildren0 = newTreeNode();
	  fillTreeNode(imprimaNodeChildren0, "RETORNO", "VOID");
	  
	  
	  imprimaNode->children[0] = imprimaNodeChildren0;
	  imprimaNode->children[1] = expressionNode;
	  
	  addNodeIntoGlobalTree(imprimaNode);
	expressionNode = NULL;
}
token_fechap token_pontov {strcpy(identifiers, "\0"); currentRelationPos = 0;} | 
token_imprimaln token_abrep BLOCO_IMPRIMA
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
token_fechap token_pontov {strcpy(identifiers, "\0"); currentRelationPos = 0;} | 
token_leia token_abrep token_identificador
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
}
token_fechap token_pontov {strcpy(identifiers, "\0"); currentRelationPos = 0;} | 
token_leialn token_abrep token_identificador
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
  
}
token_fechap token_pontov {strcpy(identifiers, "\0"); currentRelationPos = 0;} |
token_identificador
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
    //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  }
}
token_abrep ARGUMENTOS_FUNCAO token_fechap
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
  
} token_pontov
| token_identificador token_abrecol token_numinteiro token_fechacol token_atribuicao {
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
	
	
	
	
	
} EXPR {

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
} token_pontov
| token_identificador token_abrecol token_numinteiro token_fechacol token_abrecol {
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
 token_numinteiro {
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
} token_fechacol token_atribuicao EXPR {
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
} token_pontov
| token_identificador token_atribuicao 
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
EXPR
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
	//TODO
	else if(((variable*)(identifier_temp->info))->type != varRelations[0] && in_comparacao == 0 && ((variable*)(identifier_temp->info))->type != 4)
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
token_pontov {
currentRelationComparison = 0;
}
| token_se
{
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-se","CONDICIONAL");   
    addNodeIntoGlobalTree(conditionNode);
    
    //retorno os nós de atribuição para null
    expressionNode = NULL;
}

token_abrep EXPR
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

token_fechap {currentRelationPos = 0;} token_entao BLOCO_AUXILIAR
{
  commandNode = globalTree;
  conditionNode = commandNode -> children[0];
  commandNode->children[0] = NULL;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
BLOCO_SENAO_FIMSE  | 
token_faca
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
BLOCO_AUXILIAR
{
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
token_pontov
token_enquanto token_abrep EXPR
{  
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-faca-enquanto","CONDICIONAL");
     conditionNode->children[0] = expressionNode;
     conditionNode->children[1] = commandNode;
     addNodeIntoGlobalTree(conditionNode);
}
token_fechap {in_condicional = 0;} token_pontov | 
token_enquanto token_abrep 
{
    //cria o nó da arvore de condicao
    conditionNode = newTreeNode();
    fillTreeNode(conditionNode,"condicao-enquanto","CONDICIONAL");
    //seta para null o nó de expressão (que será construído na parte de expressão)
    expressionNode = NULL;
}
EXPR
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
token_fechap {in_condicional = 0; currentRelationPos = 0 ; strcpy(identifiers,"\0");} token_faca

BLOCO_AUXILIAR
{

  //commandNode = NULL;
  expressionNode = NULL;
  //conditionNode = NULL;

  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
} //functionArgument->next=NULL;
token_fimenquanto | 

token_para 
{
  conditionNode = newTreeNode();
  fillTreeNode(conditionNode,"condicao-para","CONDICAO");
  addNodeIntoGlobalTree(conditionNode);

}
token_abrep {strcpy(identifiers,"\0"); currentRelationPos=0;} token_identificador
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
token_de FATOR
{
  attributionNode->children[1] = expressionNode;
  expressionNode = NULL;

}
token_ate FATOR
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
token_passo FATOR
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
token_fechap  
{
if(!verifyRelationship(varRelations, currentRelationPos))
  {
    printf("Valores incompativeis na linha %d\n", nLine);
    terminate();
  }
strcpy(identifiers,"\0"); 
currentRelationPos = 0;
}
token_faca BLOCO_AUXILIAR
{
  expressionNode = NULL;
 
  //no global passa a ser o anterior
  globalTree = ((treeNode*)(popStack(stackGlobal)));
}
token_fimpara | 

token_seleciona {strcpy(identifiers, "\0"); currentRelationPos=0;} token_abrep token_identificador
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
token_fechap 
{
if(varRelations[0] != T_LITERAL && varRelations[0] != T_LOGICO)
  switchType = varRelations[0];
else
  switchType = T_SEMRETORNO;
}
BLOCO_SWITCH;

BLOCO_SENAO_FIMSE: token_senao
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
BLOCO_AUXILIAR {currentRelationPos=0;} token_fimse
{
  commandNode = globalTree;
  globalTree = ((treeNode*)(popStack(stackGlobal)));
  expressionNode = NULL;
}
| token_fimse;

LOGICOS: 
{in_logico = 1;}
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
token_e |

{in_logico = 1;}
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
token_ou;

ARGUMENTOS_FUNCAO: EXPR
{
  List* functionList = lookupStringVariable(hashFunction, currentFunction);
  function* functionAux = ((function*)(functionList->info));
  List* aux = functionAux->parameters;
  argumentNumber++;
  if(argumentNumber <= functionAux->arity)
  {
    //printf("%d\n", functionAux->arity);
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
    
    

    else if(verifyPrimitivesMaxMinMed(currentFunction))
    {
      functionNode->children[1] = expressionNode;
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
| ARGUMENTOS_FUNCAO token_virgula EXPR
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
  //strcpy(functionArguments, "\0");
  strcpy(identifiers, "\0");
  currentRelationPos = 0;
  currentRelationComparison = 0;
  expressionNode = NULL;
}
| /*Empty*/;
EXPR: SIEXPR { swapoutTresDois(); }

| EXPR COMPARACOES SIEXPR { swapoutTresDois(); }
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
| EXPR LOGICOS {operadorDeNivelTres();} SIEXPR { swapoutTresDois(); };
 
COMPARACOES: token_maior { operadorDeNivelDois(">"); } 
| token_maiori  { operadorDeNivelDois(">="); }
| token_igual  { operadorDeNivelDois("="); }
| token_menor  { operadorDeNivelDois("<"); }
| token_menori { operadorDeNivelDois("<="); }
| token_diferente { operadorDeNivelDois("<>"); }; 


SIEXPR: TERMO { swapoutDoisUm(); }
| SIEXPR ADICAO_SUBTRACAO { operadorDeNivelUm(); } TERMO { swapoutDoisUm(); }
| SIEXPR SINALFATOR ; 
ADICAO_SUBTRACAO: token_mais | token_menos ;

SINALFATOR:  token_numreal_comsinal 
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
| token_numinteiro_comsinal
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

};
TERMO: MATRIZ | FATOR 
//Dividir
| TERMO token_dividir {	operadorDeNivelZero("/"); } FATOR { swapoutUmZero(); }
//Módulo
| TERMO 
{
  if(strcmp(currentType, "inteiro")!=0)
  {
    printf("Operador %% so aceita inteiros na linha %d.\n", nLine);
    terminate();
  }
} 
token_mod { operadorDeNivelZero("%"); } FATOR 
{
    if(strcmp(currentType, "inteiro")!=0)
    {
      printf("Operador %% so aceita inteiro na linha %d.\n", nLine);
      terminate();
    }
} 
{ swapoutUmZero(); }
//Multiplicar
| TERMO token_vezes { operadorDeNivelZero("*"); } FATOR { swapoutUmZero(); }
//Pow
| TERMO token_circ { operadorDeMenorNivel("^"); } FATOR { swapoutZeroMenor(); };

FATOR: SINALFATOR
| token_numinteiro
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
| token_numreal 
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
| token_identificador 
// Aqui esta sendo feito conversao de tipo para os identificadores.
/*
Procura-se na tabela hash a variavel e o seu tipo equivalente, antes sao feitas varias verificacoes, do tipo se a variavel foi usada
e se ela foi declarada.
*/
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
| token_menos token_identificador 
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
/*
Aqui sera feita analise de matriz com apenas um index
-- Fazer verificacoes de matriz
*/
| token_identificador token_abrecol token_numinteiro token_fechacol
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
//Matrizes de duas dimensões
| token_identificador token_abrecol token_numinteiro token_fechacol token_abrecol 
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
 token_numinteiro token_fechacol
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
 
| token_variavel_caracter 
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
| token_string 
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
| token_abrep {
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

} EXPR token_fechap {
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
| token_verdadeiro 
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
| token_falso 
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
| token_identificador
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
token_abrep ARGUMENTOS_FUNCAO token_fechap
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
  };

FATOR_CASE: SINALFATOR | token_numinteiro
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
| token_numreal 
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
| token_variavel_caracter
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
};
//Matriz de duas dimensões
MATRIZ: token_abrec { countLine=0; delimitadorNivelUm(); tempDelimitadorNivelUm = expressionNode;  expressionNode=NULL; } MATRIZ_VARIAS_COLUNAS {
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
} token_fechac 
{
	isMatrix = 1;
}
//vetor
 | token_abrecol {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;} BLOCO_MATRIZ {
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
}token_fechacol
 {
	isMatrix = 1; 
	expressionNode = tempDelimitadorNivelZero;
 };
MATRIZ_VARIAS_COLUNAS: MATRIZ_VARIAS_COLUNAS token_virgula token_abrecol {countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;} BLOCO_MATRIZ 
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
}token_fechacol
| token_abrecol 
{countColumn=0; delimitadorNiveLZero(); tempDelimitadorNivelZero = expressionNode; expressionNode=NULL;} BLOCO_MATRIZ {

	
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
token_fechacol ;

BLOCO_MATRIZ: FATOR 
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
	
| BLOCO_MATRIZ token_virgula FATOR 

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
	
};

//BLOCO_ARGUMENTOS: /*Empty*/ | EXPR | BLOCO_ARGUMENTOS token_virgula EXPR;
%%

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

