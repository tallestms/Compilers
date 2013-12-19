%{
int nLinha=1;
%}
/* definição de dígito */
letra						[a-zA-Z]
digito						[0-9]
int_bin						"0"[bB][01]+
int_oct						"0"[cC][0-7]+
int_dec	 					("-")?[0-9]+
int_hex						"0"[xX][0-9a-fA-F]+
caracter					"'"([^"'"\\\n]|\\.)?"'"
string						"\""([^\\\n"\""]|\\.)*"\""
comentario_linha				"//"[^\n]*[\n]
comentario_bloco				"/""*"([^*]|[\r\n]|("*"+([^*/]|[\r\n])))*"*"+"/"
real						("-")?[0-9]+("."[0-9]+([eE](("+"|"-")?[0-9]+))?)
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
{real}						{return token_numreal;}
{int_dec}|{int_bin}|{int_oct}|{int_hex}	{return token_numinteiro;}
"algoritmo"					{return token_algoritmo;}
"até"						{return token_ate;}
"caracter"					{return token_caracter;}
"caracteres"					{return token_caracteres;}
"caso"						{return token_caso;}
"de"						{return token_de;}
"e"						{return token_e;}
"enquanto"					{return token_enquanto;}
"então"						{return token_entao;}
"faça"						{return token_faca;}
"falso"						{return token_falso;}
"fim"						{return token_fim;}
"fim-enquanto"					{return token_fimequanto;}
"fim-para"					{return token_fimpara;}
"fim-se"					{return token_fimse;}
"fim-variáveis"					{return token_fimvariaveis;}
"função"					{return token_funcao;}
"imprima"					{return token_imprima;}
"início"					{return token_inicio;}
"inteiro"					{return token_inteiro;} 
"inteiros"					{return token_inteiros;}
"leia"						{return token_leia;}
"literais"					{return token_literais;}
"literal"					{return token_literal;}
"lógico"					{return token_logico;}
"lógicos"					{return token_logicos;}
"matriz"					{return token_matriz;}
"não"						{return token_nao;}
"ou"						{return token_ou;}
"padrão"					{return token_padrao;}
"para"						{return token_para;}
"parar"						{return token_parar;}
"passo"						{return token_passo;}
"reais"						{return token_reais;}
"real"						{return token_real;}
"retorne"					{return token_retorne;}
"se"						{return token_se;}
"seleciona"					{return token_seleciona;}
"fim-seleciona"					{return token_fimseleciona;}
"senão"						{return token_senao;}
"variáveis"					{return token_variaveis;}
"verdadeiro"					{return token_verdadeiro;}
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
{caracter}					{return token_variavel_caracter;}
{string}					{return token_string;}
{identificador}					{return token_identificador;}
[ \t]						;
[\n]						{nLinha++;}
{comentario_linha}				{nLinha++;}
"/*"  						{  /* regra para o comentario */
						register int c;

						for ( ; ; )
						    {
						    while ( (c = input()) != '*' &&
							    c != EOF )
							    if (c == '\n') nLinha++;
							    /* eat up text of comment or find \n */

						    if ( c == '*' )
							{
							while ( (c = input()) == '*' )
							    ;
							if ( c == '/' )
							    break;    /* found the end */
							if ( c == '\n' )
							  nLinha++;
							}
						

						    if ( c == EOF )
							{
							error( "EOF in comment" );
							break;
							}
						    }
						}

%%