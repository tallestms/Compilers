%{
#include <stdio.h>
%}

%token token_doido
%token token_doido2
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
%token token_numreal
%token token_numinteiro
%token token_algoritmo
%token token_ate
%token token_caractere
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
%token token_inicio
%token token_inteiro
%token token_inteiros
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
%token token_caracter
%token token_string
%token token_identificador



%start PROG

%%

PROG:	token_algoritmo token_identificador token_pontov BLOCO_VARIAVEIS token_inicio BLOCO token_fim;
BLOCO_VARIAVEIS: token_variaveis VARIAVEIS token_fimvariaveis |
		  token_variaveis token_fimvariaveis | /*Empty*/;
VARIAVEIS: token_identificador token_doisp TIPOS_VARIAVEIS token_pontov | VARIAVEIS token_identificador token_doisp TIPOS_VARIAVEIS token_pontov ;  
TIPOS_VARIAVEIS: token_inteiro | token_real | token_caracter | token_literal | token_logico | MATRIZ;
MATRIZ: token_matriz token_abrecol token_numinteiro token_fechacol token_de TIPOS_VARIAVEIS_MATRIZ;
TIPOS_VARIAVEIS_MATRIZ: token_inteiros | token_caracteres | token_literais | token_reais | token_logicos;

BLOCO: /*Empty*/ | BLOCO COMANDO | BLOCO token_funcao token_identificador FUNCAO | token_inicio BLOCO token_fim;
FUNCAO: token_abrep VARIAVEIS_FUNCAO token_fechap token_doisp TIPOS_VARIAVEIS VARIAVEIS token_inicio BLOCO_FUNCAO token_fim;
VARIAVEIS_FUNCAO: token_identificador token_doisp TIPOS_VARIAVEIS | VARIAVEIS_FUNCAO token_virgula token_identificador token_doisp TIPOS_VARIAVEIS ;  
BLOCO_FUNCAO: /*Empty*/ | token_retorne token_identificador token_pontov;

COMANDO: token_identificador token_atribuicao EXPR token_pontov;

EXPR: SIEXPR | SIEXPR COMPARACOES SIEXPR;
COMPARACOES: token_maior | token_maiori | token_igual | token_menor | token_menori | token_diferente;

SIEXPR: TERMO | TERMO ADICAO_SUBTRACAO SIEXPR;
ADICAO_SUBTRACAO: token_mais | token_menos;

TERMO: FATOR | FATOR token_dividir FATOR | FATOR token_mod FATOR | FATOR token_vezes FATOR;
FATOR: token_numinteiro | token_numreal | token_identificador;


%%

#include "lex.yy.c"

main(){
	yyparse();
}

/* rotina chamada por yyparse quando encontra erro */
yyerror (void){
	printf("Erro na Linha: %d\n", nLinha);
}


