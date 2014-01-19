%{
#include <stdio.h>
#include <string.h>
int nLine=1;
char identifiers[500];
char type[10];
int varRelations[100];
char currentType[10];
char currentIdentifier[100];
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
{real_signed}					{strcpy(currentType, "real"); return token_numreal_comsinal;}
{real}						{strcpy(currentType, "real"); return token_numreal;}
{int_dec_signed}				{strcpy(currentType, "inteiro"); return token_numinteiro_comsinal;}
{int_dec}					{strcpy(currentType, "inteiro"); return token_numinteiro;}
"algoritmo"					{return token_algoritmo;}
"até"						{return token_ate;}
"caracter"					{strcpy(type, yytext); return token_caracter;}
"caracteres"					{return token_caracteres;}
"caso"						{return token_caso;}
"de"						{return token_de;}
"e"						{return token_e;}
"enquanto"					{return token_enquanto;}
"então"						{return token_entao;}
"faça"						{return token_faca;}
"falso"						{strcpy(currentType, "lógico");return token_falso;}
"fim"						{return token_fim;}
"fim-enquanto"					{return token_fimequanto;}
"fim-para"					{return token_fimpara;}
"fim-se"					{return token_fimse;}
"fim-variáveis"					{return token_fimvariaveis;}
"função"					{return token_funcao;}
"imprima"					{return token_imprima;}
"início"					{return token_inicio;}
"inteiro"					{strcpy(type, yytext); return token_inteiro;} 
"inteiros"					{return token_inteiros;}
"leia"						{return token_leia;}
"literais"					{return token_literais;}
"literal"					{strcpy(type, yytext); return token_literal;}
"lógico"					{strcpy(type, yytext); return token_logico;}
"lógicos"					{return token_logicos;}
"matriz"					{return token_matriz;}
"não"						{return token_nao;}
"ou"						{return token_ou;}
"padrão"					{return token_padrao;}
"para"						{return token_para;}
"parar"						{return token_parar;}
"passo"						{return token_passo;}
"reais"						{return token_reais;}
"real"						{strcpy(type, yytext); return token_real;}
"retorne"					{return token_retorne;}
"se"						{return token_se;}
"seleciona"					{return token_seleciona;}
"fim-seleciona"					{return token_fimseleciona;}
"senão"						{return token_senao;}
"variáveis"					{return token_variaveis;}
"verdadeiro"					{strcpy(currentType, "lógico");return token_verdadeiro;}
"+"						{return token_mais;}
"-"						{return token_menos;}
"*"						{return token_vezes;}
"/"						{return token_dividir;}
"%"						{return token_mod;}
"++"						{return token_maismais;}
"--"						{return token_menosmenos;}
":="						{return token_atribuicao;}
">"						{return token_maior;}
"<"						{return token_menor;}
">="						{return token_maiori;}
"<="						{return token_menori;}
"="						{return token_igual;}
"<>"						{return token_diferente;}
"&&"						{return token_el;}
"||"						{return token_oul;}
"!"						{return token_negacao;}
{caracter}					{strcpy(currentType, "caracter");return token_variavel_caracter;}
{string}					{strcpy(currentType, "literal");return token_string;}
{identificador}					{strcpy(currentIdentifier, yytext); strcat(identifiers, yytext); strcat(identifiers, " "); return token_identificador;}
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
