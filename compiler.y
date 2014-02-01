%{
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
extern int nLine;
extern char identifiers[10*MAX_VARIABLE];
extern char functionArguments[10*MAX_VARIABLE];
extern char currentType[10];
extern char currentIdentifier[100];
extern int varRelations[100];
int currentRelationPos = 0;
int currentRelationComparison = 0;
char currentScope[MAX_FUNCTION] = "main";
char currentFunction[MAX_FUNCTION];
int currentFunctionArity = 0;
char returnFunctionType[10];
List* currentParameters = NULL;
hashTable* hashVariables = NULL;
hashTable* hashFunction = NULL;
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
%token token_fimequanto
%token token_fimpara
%token token_fimse
%token token_fimvariaveis
%token token_funcao
%token token_imprima
%token token_inicio
%token token_inteiro
%token token_inteiros
%token token_leia
%token token_literais
%token token_literal
%token token_logico
%token token_logicos
%token token_matriz
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

%start PROG

%%
PROG:  token_algoritmo token_identificador token_pontov BLOCO_FUNCOES BLOCO_VARIAVEIS token_inicio BLOCO token_fim  
{
  //verifyUsed(hashVariables);
}
|
token_algoritmo token_identificador
token_pontov BLOCO_VARIAVEIS token_inicio BLOCO token_fim 
{
  //verifyUsed(hashVariables);
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
  };

TIPOS_VARIAVEIS: token_inteiro | token_real | token_caracter | token_literal | token_logico | INICIALIZAR_MATRIZ;

/*
 *
 *Tarefa: Fazer funcionar analise semantica para matrizes
 *
 */

 
VARIAVEIS_IDENTIFICADORES: token_identificador | VARIAVEIS_IDENTIFICADORES token_virgula token_identificador
  


INICIALIZAR_MATRIZ: token_matriz token_abrecol token_numinteiro token_fechacol token_abrecol token_numinteiro token_fechacol token_de TIPOS_VARIAVEIS_MATRIZ | 
	token_matriz token_abrecol token_numinteiro token_fechacol token_de TIPOS_VARIAVEIS_MATRIZ;
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
	setFunction(newFunction, currentIdentifier, 5, 0, NULL, 0); //A funcao foi setada com valores default, estes valores serao alterados depois.
    }
    else
    {
      printf("Erro semantico na linha %d. Funcao %s redeclarada.\n", nLine, currentIdentifier);
    }

  strcpy(identifiers, "\0");
}
FUNCAO 
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
| token_funcao token_identificador //Mesma coisa do de cima.
{
    currentParameters = startList();
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
FUNCAO
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
};
BLOCO_AUXILIAR: /*Empty*/ | BLOCO_AUXILIAR COMANDO | token_abrec BLOCO_AUXILIAR token_fechac;
BLOCO_FUNCAO_RETORNO: token_retorne token_identificador 
{
	//foi retornada uma variável, verificar tipo de retorno
	char aux[MAX_VARIABLE + MAX_FUNCTION + 1];
	strcpy(aux, currentIdentifier);
	strcat(aux, " ");
	strcat(aux, currentScope);
	List *returned_variable = lookupStringVariable(hashVariables, aux);	
	if(returned_variable != NULL){
		List *current_function = lookupStringFunction(hashFunction, currentScope);
		int typeReturnedFunction = ((function*)(current_function->info))->returnType;
		int typeReturnedVariable = ((variable*)(returned_variable->info))->type; 
		if ( typeReturnedFunction != typeReturnedVariable ) {
			printf("Funcao %s espera um retorno do tipo %d e a variavel %s e do tipo %d na linha %d\n", currentScope, typeReturnedFunction, currentIdentifier, typeReturnedVariable, nLine);
		}
		if ( ((variable*)(returned_variable->info))->used == 0) {
			printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
		}
	} else {
		printf("Variavel %s não declarada na linha %d\n", currentIdentifier, nLine);
	}
	strcpy(identifiers, "\0");
}
token_pontov | REPETICAO_COMANDO token_retorne token_identificador
{
	//foi retornada uma variável, verificar tipo de retorno
	char aux[MAX_VARIABLE + MAX_FUNCTION + 1];
	strcpy(aux, currentIdentifier);
	strcat(aux, " ");
	strcat(aux, currentScope);
	List *returned_variable = lookupStringVariable(hashVariables, aux);	
	if(returned_variable != NULL){
		List *current_function = lookupStringFunction(hashFunction, currentScope);
		int typeReturnedFunction = ((function*)(current_function->info))->returnType;
		int typeReturnedVariable = ((variable*)(returned_variable->info))->type; 
		if ( typeReturnedFunction != typeReturnedVariable ) {
			printf("Funcao %s espera um retorno do tipo %d e a variavel %s e do tipo %d na linha %d\n", currentScope, typeReturnedFunction, currentIdentifier, typeReturnedVariable, nLine);
		}
		if ( ((variable*)(returned_variable->info))->used == 0) {
			printf("Variavel %s nao foi inicializada na linha %d\n", currentIdentifier, nLine);
		}
	} else {
		printf("Variavel %s não declarada na linha %d\n", currentIdentifier, nLine);
	}
	strcpy(identifiers, "\0");
} 
token_pontov;
BLOCO_FUNCAO: /*Empty*/ | REPETICAO_COMANDO;
REPETICAO_COMANDO: COMANDO | REPETICAO_COMANDO COMANDO;

BLOCO_IMPRIMA: BLOCO_IMPRIMA token_virgula FATOR | FATOR;
BLOCO_SWITCH:  BLOCO_SWITCH_AUX BLOCO_SWITCH | 
BLOCO_SWITCH_AUX FIM_BLOCO_SWITCH;
FIM_BLOCO_SWITCH: token_padrao token_doisp BLOCO_AUXILIAR token_parar token_pontov token_fimseleciona | token_fimseleciona ;
BLOCO_SWITCH_AUX: token_caso token_abrep FATOR_CASE token_fechap token_doisp BLOCO_AUXILIAR token_parar token_pontov | token_caso token_abrep FATOR_CASE token_fechap token_doisp BLOCO_AUXILIAR;

FUNCAO: token_abrep VARIAVEIS_FUNCAO token_fechap token_inicio BLOCO_FUNCAO token_fim 
| token_abrep VARIAVEIS_FUNCAO token_fechap VARIAVEIS token_inicio BLOCO_FUNCAO token_fim 
| token_abrep VARIAVEIS_FUNCAO token_fechap token_doisp TIPOS_VARIAVEIS 
{
// Em tipos_variaveis ira retornar o tipo de retorno da funcao, a qual sera acrescentada.
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
}
VARIAVEIS token_inicio BLOCO_FUNCAO_RETORNO token_fim

| token_abrep VARIAVEIS_FUNCAO token_fechap token_doisp TIPOS_VARIAVEIS 
/*Retorno sera verificado aqui em todas as funcoes com mesmo nome!*/
{
  List *aux = lookupStringFunction(hashFunction, currentScope);
  if(aux!=NULL)
    ((function*)(aux->info))->returnType = convertType(currentType);
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
| /*Empty*/;  

/*
 *
 *Tarefa: Fazer funcoes primitivas.
 *
 */
COMANDO: 
token_imprima token_abrep BLOCO_IMPRIMA token_fechap token_pontov | 
token_identificador token_atribuicao token_imprima token_abrep BLOCO_IMPRIMA token_fechap token_pontov |
token_identificador token_atribuicao token_leia token_abrep token_fechap token_pontov | 
token_identificador
{
  //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
}
token_abrep ARGUMENTOS_FUNCAO token_fechap
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
} token_pontov
| token_identificador token_atribuicao 
{
currentRelationComparison = 0;
}
EXPR
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
	else if((varRelations[0] == 2 || varRelations[0] == 1) && currentRelationPos > 1) //caracter ou literal
	{
	  printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	}
	else if(in_logico==1)
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

	else if(((variable*)(identifier_temp->info))->type != varRelations[0])
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
	  else if((varRelations[0] == 2 || varRelations[0] == 1) && currentRelationPos > 1) //caracter ou literal
	  {
	    printf("Literais ou caracteres nao aceitam operacoes (mais, menos e etc) na linha %d.\n", nLine);
	  }
	  else if(in_logico==1)
	  {
	  if((((variable*)(identifier_temp->info))->type) != 4)
	  {
	    printf("Erro semantico na linha %d. Tipo invalido associado a variavel.\n",nLine);
	  }
	  in_logico=0;
	  }
	  else if(((variable*)(identifier_temp->info))->type != varRelations[0])
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
token_pontov |
token_se token_abrep EXPR token_fechap token_entao BLOCO_AUXILIAR token_fimse | 
token_se token_abrep EXPR token_fechap token_entao BLOCO_AUXILIAR token_senao BLOCO_AUXILIAR token_fimse |
token_faca BLOCO_AUXILIAR token_enquanto token_abrep EXPR token_fechap token_pontov | token_enquanto token_abrep EXPR token_fechap token_faca BLOCO_AUXILIAR token_fimequanto | 
token_para token_abrep token_identificador token_de FATOR token_ate FATOR token_passo FATOR token_fechap token_faca BLOCO_AUXILIAR token_fimpara | token_seleciona token_abrep token_identificador token_fechap BLOCO_SWITCH;
 
LOGICOS: 
{in_logico = 1;}
{
  if (in_comparacao = 1)
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
}
token_e |

{in_logico = 1;}
{
  if (in_comparacao = 1)
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
}
token_ou;

ARGUMENTOS_FUNCAO: EXPR | ARGUMENTOS_FUNCAO token_virgula EXPR | /*Empty*/;
EXPR: SIEXPR 

| EXPR COMPARACOES SIEXPR
{
    if (in_comparacao = 1)
  {	
    //printf("%d %d\n", currentRelationPos, currentRelationComparison);
    //printRelationship(varRelations, currentRelationComparison);
    if(!verifyRelationshipComparison(varRelations, currentRelationComparison, currentRelationPos))
	{
	  printf("Valores incompativeis ou nao validos na linha %d.\n", nLine);
	}
    currentRelationComparison=0;
    in_comparacao = 1
    
    
    
    ;
  }
}
| EXPR LOGICOS SIEXPR 
;

/*
 *
 *Tarefa: Fazer funcionar analise semantica juntando logicos
 *
 */

 
COMPARACOES: token_maior | token_maiori | token_igual | token_menor | token_menori | token_diferente;

SIEXPR: TERMO 
| SIEXPR ADICAO_SUBTRACAO TERMO
| SIEXPR SINALFATOR ; 
ADICAO_SUBTRACAO: token_mais | token_menos ;

SINALFATOR:  token_numreal_comsinal 
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
| token_numinteiro_comsinal
{
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
    //printf("real com sinal\n");
  }

};
TERMO: MATRIZ | FATOR | TERMO token_dividir FATOR | TERMO token_mod FATOR | TERMO token_vezes FATOR ;
FATOR: SINALFATOR
| token_numinteiro
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
| token_numreal 
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
| token_menos token_identificador 
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
| token_variavel_caracter 
{
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
  
}
| token_string 
{
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
}
| token_abrep EXPR token_fechap 
| token_verdadeiro 
{
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
}
| token_falso 
{
  if(in_function!=1)
  {
    int currentTypeInt = convertType(currentType);
    varRelations[currentRelationPos] = currentTypeInt;
    ++currentRelationPos;
    ++currentRelationComparison;
  }
}
| token_identificador
{
  //Aqui estamos entrando dentro de uma funcao dentro, isto e, funcao(a,b,c)
  strcpy(currentFunction, currentIdentifier);
    in_function = 1; //Dentro de funcao, a partir de agora havera copia de tipos na string functionArguments (olha no arquivo .l)
}
token_abrep ARGUMENTOS_FUNCAO token_fechap
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
  }
    
      int currentTypeInt = ((function *)(identifier_temp->info))->returnType;
     // printf("%d \n", currentTypeInt);
      varRelations[currentRelationPos] = currentTypeInt;
      if(currentTypeInt==5)
      {
	printf("Na linha %d, a funcao %s nao possui retorno. ", nLine, currentFunction);
      }
      ++currentRelationPos;
      ++currentRelationComparison;
  strcpy(functionArguments, "\0");
  //strcpy(identifiers, "\0");
  //currentRelationPos = 0;
  in_function = 0;
  };

FATOR_CASE: SINALFATOR | token_numinteiro | token_numreal | token_variavel_caracter; 

MATRIZ: token_abrec MATRIZ_VARIAS_COLUNAS token_fechac | token_abrecol BLOCO_MATRIZ token_fechacol;
MATRIZ_VARIAS_COLUNAS: MATRIZ_VARIAS_COLUNAS token_virgula token_abrecol BLOCO_MATRIZ token_fechacol | token_abrecol BLOCO_MATRIZ token_fechacol;
BLOCO_MATRIZ: FATOR | BLOCO_MATRIZ token_virgula FATOR;

//BLOCO_ARGUMENTOS: /*Empty*/ | EXPR | BLOCO_ARGUMENTOS token_virgula EXPR;
%%

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


