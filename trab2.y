%{
#include <stdio.h>
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
// Matriz como fatores ( m := [1,2,3,4,5,6] ) 
// chamadas de funçoes

PROG: token_algoritmo token_identificador token_pontov BLOCO_VARIAVEIS token_inicio BLOCO token_fim BLOCO_FUNCOES ;
BLOCO_VARIAVEIS: token_variaveis VARIAVEIS token_fimvariaveis |
		  token_variaveis token_fimvariaveis | /*Empty*/;
		  
VARIAVEIS: token_identificador token_doisp TIPOS_VARIAVEIS token_pontov |
VARIAVEIS token_identificador token_doisp TIPOS_VARIAVEIS token_pontov ; 
TIPOS_VARIAVEIS: token_inteiro | token_real | token_caracter | token_literal | token_logico | INICIALIZAR_MATRIZ;

INICIALIZAR_MATRIZ: token_matriz token_abrecol token_numinteiro token_fechacol token_abrecol token_numinteiro token_fechacol token_de TIPOS_VARIAVEIS_MATRIZ | 
	token_matriz token_abrecol token_numinteiro token_fechacol token_de TIPOS_VARIAVEIS_MATRIZ;
TIPOS_VARIAVEIS_MATRIZ: token_inteiros | token_caracteres | token_literais | token_reais | token_logicos;

BLOCO: /*Empty*/ | BLOCO COMANDO | BLOCO token_abrec BLOCO token_fechac;
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
token_identificador token_atribuicao EXPR_FUNCAO token_pontov |
token_identificador token_atribuicao MATRIZ |
token_se token_abrep EXPR token_fechap token_entao BLOCO_AUXILIAR token_fimse | 
token_se token_abrep EXPR token_fechap token_entao BLOCO_AUXILIAR token_senao BLOCO_AUXILIAR token_fimse |
token_faca BLOCO_AUXILIAR token_enquanto token_abrep EXPR token_fechap token_pontov | token_enquanto token_abrep EXPR token_fechap token_faca BLOCO_AUXILIAR token_fimequanto | 
token_para token_abrep token_identificador token_de FATOR token_ate FATOR token_passo FATOR token_fechap token_faca BLOCO_AUXILIAR token_fimpara | token_seleciona token_abrep token_identificador token_fechap BLOCO_SWITCH;
 
//LOGEXPR: EXPR | LOGEXPR LOGICOS EXPR;
LOGICOS: token_e | token_ou;
EXPR_FUNCAO: EXPR;
EXPR: SIEXPR | EXPR COMPARACOES SIEXPR | EXPR LOGICOS SIEXPR;
COMPARACOES: token_maior | token_maiori | token_igual | token_menor | token_menori | token_diferente;

SIEXPR: TERMO | SIEXPR ADICAO_SUBTRACAO TERMO | SIEXPR SINALFATOR ; 
ADICAO_SUBTRACAO: token_mais | token_menos ;

SINALFATOR:  token_numreal_comsinal | token_numinteiro_comsinal;
TERMO: MATRIZ | FATOR | TERMO token_dividir FATOR | TERMO token_mod FATOR | TERMO token_vezes FATOR;
FATOR: SINALFATOR | token_numinteiro | token_numreal | SINAL token_identificador | token_variavel_caracter | token_string | token_abrep EXPR token_fechap | token_verdadeiro | token_falso;
FATOR_CASE: SINALFATOR | token_numinteiro | token_numreal | token_variavel_caracter; 

SINAL: /*Empty*/ | token_menos;

MATRIZ: token_abrec MATRIZ_VARIAS_COLUNAS token_fechac | token_abrecol BLOCO_MATRIZ token_fechacol;
MATRIZ_VARIAS_COLUNAS: MATRIZ_VARIAS_COLUNAS token_virgula token_abrecol BLOCO_MATRIZ token_fechacol | token_abrecol BLOCO_MATRIZ token_fechacol;
BLOCO_MATRIZ: FATOR | BLOCO_MATRIZ token_virgula FATOR;

//BLOCO_ARGUMENTOS: /*Empty*/ | EXPR | BLOCO_ARGUMENTOS token_virgula EXPR;
%%

#include "lex.yy.c"

main(){
	yyparse();
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void){
	printf("Erro na Linha: %d\n", nLinha);
}


