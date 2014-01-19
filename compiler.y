%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "hash.h"
#include "lists.h"
#include "aux.h"

#define MAX_HASH 1000

extern int nLine;
extern char identifiers[500];
extern char type[10];
extern char currentType[10];
extern char currentIdentifier[100];
extern int varRelations[100];
int currentRelationPos = 0;
char currentScope[50] = "main"; 
hashTable* hashCompiler = NULL;
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
PROG:  token_algoritmo token_identificador
token_pontov BLOCO_VARIAVEIS token_inicio BLOCO token_fim  
{
  verifyUsed(hashCompiler);
}
|
token_algoritmo token_identificador
token_pontov BLOCO_VARIAVEIS token_inicio BLOCO token_fim BLOCO_FUNCOES
{
  verifyUsed(hashCompiler);
}
;
BLOCO_VARIAVEIS: token_variaveis VARIAVEIS token_fimvariaveis |
		  token_variaveis token_fimvariaveis | /*Empty*/;
		  
VARIAVEIS: VARIAVEIS_IDENTIFICADORES token_doisp TIPOS_VARIAVEIS token_pontov
  {
    char *varName, *varType;
    varName = strtok(identifiers, " ");
    while(varName != NULL)
    {
      variable* newVar = createVariable();
      int intVarType = convertType(type);
      setVariable(newVar, varName, currentScope, intVarType);
      if(lookupStringVariable(hashCompiler, varName)==NULL)
	addInfoVariable(hashCompiler, varName, newVar);
      else
      {
	printf("Erro semantico na linha %d. Variavel redeclarada.\n", nLine);
	exit(1);
      }
      varName = strtok(NULL, " ");
    }
  strcpy(identifiers, "\0");
  }
  | VARIAVEIS VARIAVEIS_IDENTIFICADORES token_doisp TIPOS_VARIAVEIS token_pontov
  {
    char *varName, *varType;
    varName = strtok(identifiers, " ");
    while(varName != NULL)
    {
      variable* newVar = createVariable();
      int intVarType = convertType(type);
      setVariable(newVar, varName, currentScope, intVarType);
      if(lookupStringVariable(hashCompiler, varName)==NULL)
	addInfoVariable(hashCompiler, varName, newVar);
      else
      {
	printf("Erro semantico na linha %d. Variavel redeclarada.\n", nLine);
	exit(1);
      }
      varName = strtok(NULL, " ");
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
BLOCO_FUNCOES: BLOCO_FUNCOES token_funcao token_identificador FUNCAO | token_funcao token_identificador FUNCAO;
BLOCO_AUXILIAR: /*Empty*/ | BLOCO_AUXILIAR COMANDO | token_abrec BLOCO_AUXILIAR token_fechac;
BLOCO_FUNCAO: /*Empty*/ | COMANDO token_retorne token_identificador token_pontov | COMANDO;
BLOCO_IMPRIMA: BLOCO_IMPRIMA token_virgula FATOR | FATOR;
BLOCO_SWITCH:  BLOCO_SWITCH_AUX BLOCO_SWITCH | 
BLOCO_SWITCH_AUX FIM_BLOCO_SWITCH;
FIM_BLOCO_SWITCH: token_padrao token_doisp BLOCO_AUXILIAR token_parar token_pontov token_fimseleciona | token_fimseleciona ;
BLOCO_SWITCH_AUX: token_caso token_abrep FATOR_CASE token_fechap token_doisp BLOCO_AUXILIAR token_parar token_pontov | token_caso token_abrep FATOR_CASE token_fechap token_doisp BLOCO_AUXILIAR;

FUNCAO: token_abrep VARIAVEIS_FUNCAO token_fechap VARIAVEIS token_inicio BLOCO_FUNCAO token_fim | token_abrep VARIAVEIS_FUNCAO token_fechap token_doisp TIPOS_VARIAVEIS VARIAVEIS token_inicio BLOCO_FUNCAO token_fim;
VARIAVEIS_FUNCAO: token_identificador token_doisp TIPOS_VARIAVEIS |
VARIAVEIS_FUNCAO token_virgula token_identificador token_doisp TIPOS_VARIAVEIS ;  

COMANDO: 
token_imprima token_abrep BLOCO_IMPRIMA token_fechap token_pontov | 
token_identificador token_atribuicao token_imprima token_abrep BLOCO_IMPRIMA token_fechap token_pontov |
token_identificador token_atribuicao token_leia token_abrep token_fechap token_pontov| 
token_identificador token_abrep ARGUMENTOS_FUNCAO token_fechap token_pontov |

/*
 *
 *Tarefa: Checar aridade de funcao e argumentos (trocar de lugar funcoes para isso? Perguntar para a professora)
 *
 */

token_identificador token_atribuicao EXPR
{
  if(!verifyRelationship(varRelations, currentRelationPos))
  {
    printf("Valores incompativeis na linha %d\n",nLine);
  }
  else
  {
    List *identifier_temp = lookupStringVariable(hashCompiler, currentIdentifier);
    if(identifier_temp == NULL)
    {
      printf("Variavel nao declarada na linha %d\n", nLine);
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
token_pontov |
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
 *Tarefa: Fazer funcionar analise semantica juntando logiocs
 *
 */

 
COMPARACOES: token_maior | token_maiori | token_igual | token_menor | token_menori | token_diferente;

SIEXPR: TERMO 
| SIEXPR ADICAO_SUBTRACAO TERMO
| SIEXPR SINALFATOR ; 
ADICAO_SUBTRACAO: token_mais | token_menos ;

SINALFATOR:  token_numreal_comsinal 
{
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
{
  List *identifier_temp = lookupStringVariable(hashCompiler, currentIdentifier);
  if(identifier_temp==NULL)
  {
    printf("Variavel nao declarada na linha %d\n", nLine);
  }
  int currentTypeInt = ((variable*)(identifier_temp->info))->type;
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("identificador\n");
}
| token_menos token_identificador 
{
  List *identifier_temp = lookupStringVariable(hashCompiler, currentIdentifier);
  if(identifier_temp==NULL)
  {
    printf("Variavel nao declarada na linha %d\n", nLine);
  }
  int currentTypeInt = ((variable*)(identifier_temp->info))->type;
  varRelations[currentRelationPos] = currentTypeInt;
  ++currentRelationPos;
  //printf("identificador\n");
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
| token_identificador token_abrep ARGUMENTOS_FUNCAO token_fechap;

FATOR_CASE: SINALFATOR | token_numinteiro | token_numreal | token_variavel_caracter; 

MATRIZ: token_abrec MATRIZ_VARIAS_COLUNAS token_fechac | token_abrecol BLOCO_MATRIZ token_fechacol;
MATRIZ_VARIAS_COLUNAS: MATRIZ_VARIAS_COLUNAS token_virgula token_abrecol BLOCO_MATRIZ token_fechacol | token_abrecol BLOCO_MATRIZ token_fechacol;
BLOCO_MATRIZ: FATOR | BLOCO_MATRIZ token_virgula FATOR;

//BLOCO_ARGUMENTOS: /*Empty*/ | EXPR | BLOCO_ARGUMENTOS token_virgula EXPR;
%%

#include "lex.yy.c"

main(){
      hashCompiler = createHash(MAX_HASH);
      yyparse();
	
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void){
	printf("Erro na Linha: %d\n", nLine);
}


