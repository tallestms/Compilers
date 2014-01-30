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
	setFunction(newFunction, currentIdentifier, 0, 0, NULL, 0); //A funcao foi setada com valores default, estes valores serao alterados depois.
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
	setFunction(newFunction, currentIdentifier, 0, 0, NULL, 0);
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
    ((function*)(identifier_temp->info))->parameters=currentParameters;
  }
  currentFunctionArity = 0;
  strcpy(currentScope, "main");
};
BLOCO_AUXILIAR: /*Empty*/ | BLOCO_AUXILIAR COMANDO | token_abrec BLOCO_AUXILIAR token_fechac;
BLOCO_FUNCAO: /*Empty*/ | REPETICAO_COMANDO token_retorne token_identificador token_pontov | REPETICAO_COMANDO;
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
VARIAVEIS token_inicio BLOCO_FUNCAO token_fim

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
} token_pontov
| token_identificador token_atribuicao EXPR
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
} token_pontov |
token_se token_abrep EXPR token_fechap token_entao BLOCO_AUXILIAR token_fimse | 
token_se token_abrep EXPR token_fechap token_entao BLOCO_AUXILIAR token_senao BLOCO_AUXILIAR token_fimse |
token_faca BLOCO_AUXILIAR token_enquanto token_abrep EXPR token_fechap token_pontov | token_enquanto token_abrep EXPR token_fechap token_faca BLOCO_AUXILIAR token_fimequanto | 
token_para token_abrep token_identificador token_de FATOR token_ate FATOR token_passo FATOR token_fechap token_faca BLOCO_AUXILIAR token_fimpara | token_seleciona token_abrep token_identificador token_fechap BLOCO_SWITCH;
 
LOGICOS: token_e | token_ou;
ARGUMENTOS_FUNCAO: EXPR | ARGUMENTOS_FUNCAO token_virgula EXPR | /*Empty*/;
EXPR: SIEXPR 
| EXPR COMPARACOES SIEXPR
| EXPR LOGICOS SIEXPR;

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
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("real com sinal\n");
}
| token_numinteiro_comsinal
{
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("inteiro com sinal\n");

};
TERMO: MATRIZ | FATOR | TERMO token_dividir FATOR | TERMO token_mod FATOR | TERMO token_vezes FATOR ;
FATOR: SINALFATOR
| token_numinteiro
{
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("inteiro sem sinal\n");
}
| token_numreal 
{
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("real sem sinal\n");
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
| token_variavel_caracter 
{
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
| token_string 
{
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
| token_abrep EXPR token_fechap 
| token_verdadeiro 
{
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
}
| token_falso 
{
  int currentTypeInt = convertType(currentType);
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
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


