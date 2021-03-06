%{
#include <stdio.h>
#include <string.h>

#define MAX_VARIABLE 32 //maior nome de variavel
#define MAX_FUNCTION 32 //maior nome de funcao
#define MAX_LITERAL 50 //maio string

int err = 0;
int nLine=1;
int in_function = 0;
int in_logico = 0;
int in_comparacao = 0;
int in_condicional = 0;
char identifiers[10*MAX_VARIABLE];
char functionArguments[10*MAX_VARIABLE];
int varRelations[50];
char currentType[10];
int currentNumber = 0;
char currentIdentifier[MAX_VARIABLE];
int isMatrix = 0;
char limitString[MAX_LITERAL]; //limitador de tamanho de string no programa
%}

/* definição de dígito */
letra						[a-zA-Z]
digito						[0-9]
int_bin						"0"[bB][01]+
int_oct						"0"[cC][0-7]+
int_dec_signed	 				("-")[0-9]+
int_dec	 					[0-9]+
int_hex						"0"[xX][0-9a-fA-F]+
caracter					"'"([^"'"\\\n]|\\.)?"'"
string						"\""([^\\\n"\""]|\\.)*"\""
comentario_linha				"//"[^\n]*[\n]
comentario_bloco				"/""*"([^*]|[\r\n]|("*"+([^*/]|[\r\n])))*"*"+"/"
real_signed					("-")[0-9]+("."[0-9]+([eE](("+"|"-")?[0-9]+))?)
real						[0-9]+("."[0-9]+([eE](("+"|"-")?[0-9]+))?)
identificador					[a-zA-Z_][a-zA-Z0-9_]*
%%
"^"						{return token_circ;}
"("						{return token_abrep;}
")"						{return token_fechap;}
","						{return token_virgula;}
"."						{return token_ponto;}
";"						{return token_pontov;}
":"						{return token_doisp;}
"#"						{return token_jogodav;}
"'"						{return token_apostrofe;}
"{"						{return token_abrec;}
"}"						{return token_fechac;}
"["						{return token_abrecol;}
"]"						{return token_fechacol;}
{real_signed}					{if(in_function == 1){strcat(functionArguments, "real"); strcat(functionArguments, " ");} strcpy(currentType, "real"); return token_numreal_comsinal;}
{real}						{if(in_function == 1){strcat(functionArguments, "real"); strcat(functionArguments, " ");} strcpy(currentType, "real"); return token_numreal;}
{int_dec_signed}				{if(in_function == 1){strcat(functionArguments, "inteiro"); strcat(functionArguments, " ");} strcpy(currentType, "inteiro"); return token_numinteiro_comsinal;}
{int_dec}					{currentNumber = atoi((char*)yytext); if(in_function == 1){strcat(functionArguments, "inteiro"); strcat(functionArguments, " ");} strcpy(currentType, "inteiro"); return token_numinteiro;}
"algoritmo"					{return token_algoritmo;}
"até"						{return token_ate;}
"caracter"					{strcpy(currentType, yytext); return token_caracter;}
"caracteres"					{strcpy(currentType, "caracter"); return token_caracteres;}
"caso"						{return token_caso;}
"de"						{return token_de;}
"e"						{return token_e;}
"enquanto"					{in_condicional=1; return token_enquanto;}
"então"						{in_condicional=0; in_logico=0; return token_entao;}
"faça"						{return token_faca;}
"falso"						{if(in_function == 1){strcat(functionArguments, "lógico"); strcat(functionArguments, " ");} strcpy(currentType, "lógico");return token_falso;}
"fim"						{return token_fim;}
"fim-enquanto"					{return token_fimenquanto;}
"fim-para"					{return token_fimpara;}
"fim-se"					{return token_fimse;}
"fim-faça"					{return token_fimfaca;}
"fim-variáveis"					{return token_fimvariaveis;}
"função"					{return token_funcao;}
"imprima"					{return token_imprima;}
"imprimaln"					{return token_imprimaln;}
"início"					{return token_inicio;}
"inteiro"					{strcpy(currentType, yytext); return token_inteiro;} 
"inteiros"					{strcpy(currentType, "inteiro"); return token_inteiros;}
"leia"						{return token_leia;}
"leialn"					{return token_leialn;}
"literais"					{strcpy(currentType, "literal"); return token_literais;}
"literal"					{strcpy(currentType, yytext); return token_literal;}
"lógico"					{strcpy(currentType, yytext); return token_logico;}
"lógicos"					{strcpy(currentType, "lógico"); return token_logicos;}
"matriz"					{isMatrix = 1; return token_matriz;}
"não"						{return token_nao;}
"ou"						{return token_ou;}
"padrão"					{return token_padrao;}
"para"						{return token_para;}
"parar"						{return token_parar;}
"passo"						{return token_passo;}
"reais"						{strcpy(currentType, "real"); return token_reais;}
"real"						{strcpy(currentType, yytext); return token_real;}
"retorne"					{return token_retorne;}
"se"						{in_condicional=1; return token_se;}
"seleciona"					{return token_seleciona;}
"fim-seleciona"					{return token_fimseleciona;}
"senão"						{return token_senao;}
"variáveis"					{return token_variaveis;}
"verdadeiro"					{if(in_function == 1){strcat(functionArguments, "lógico"); strcat(functionArguments, " ");} strcpy(currentType, "lógico");return token_verdadeiro;}
"+"						{return token_mais;}
"-"						{return token_menos;}
"*"						{return token_vezes;}
"/"						{return token_dividir;}
"%"						{return token_mod;}
"++"						{return token_maismais;}
"--"						{return token_menosmenos;}
":="						{return token_atribuicao;}
">"						{in_comparacao = 1; return token_maior;}
"<"						{in_comparacao = 1; return token_menor;}
">="						{in_comparacao = 1; return token_maiori;}
"<="						{in_comparacao = 1; return token_menori;}
"="						{in_comparacao = 1; return token_igual;}
"<>"						{in_comparacao = 1; return token_diferente;}
{caracter}					{if(in_function == 1){strcat(functionArguments, "caracter"); strcat(functionArguments, " ");} strcpy(currentType, "caracter");return token_variavel_caracter;}
{string}					{strcpy(limitString, yytext); if(in_function == 1){strcat(functionArguments, "literal"); strcat(functionArguments, " ");} strcpy(currentType, "literal");return token_string;}
{identificador}					{strcpy(currentIdentifier, yytext); if(in_function!=1){strcat(identifiers, yytext); strcat(identifiers, " ");} if(in_function == 1){strcat(functionArguments, yytext); strcat(functionArguments, " ");} return token_identificador;}
[ \t]						;
[\n]						{nLine++;}
{comentario_linha}				{nLine++;}
"/*"  						{  /* regra para o comentario */
						register int c;

						for ( ; ; )
						    {
						    while ( (c = input()) != '*' &&
							    c != EOF )
							    if (c == '\n') nLine++;
							    /* eat up text of comment or find \n */

						    if ( c == '*' )
							{
							while ( (c = input()) == '*' )
							    ;
							if ( c == '/' )
							    break;    /* found the end */
							if ( c == '\n' )
							  nLine++;
							}
						

						    if ( c == EOF )
							{
							break;
							}
						    }
						}

%%
