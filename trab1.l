%{
%}
/* definição de dígito */
letra						[a-zA-Z]
digito						[0-9]
int_bin						"0"[bB][01]+
int_oct						"0"[cC][0-7]+
int_dec	 					("+"|"-")?[0-9]+
int_hex						"0"[xX][0-9a-fA-F]+
caractere					"'"([^"'"\\\n]|\\.)?"'"
string						"\""([^\\\n"\""]|\\.)*"\""
comentario_linha				"//"[^\n]*[\n]
comentario_bloco				"/""*"([^*]|[\r\n]|("*"+([^*/]|[\r\n])))*"*"+"/"
real						("+"|"-")?[0-9]+("."[0-9]+([eE](("+"|"-")?[0-9]+))?)
identificador					[a-zA-Z_][a-zA-Z0-9_]*
%%
"\""						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"("						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
")"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
","						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"."						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
";"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
":"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"#"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"'"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"{"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"}"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"\\"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"["						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
"]"						{printf("%s -> SIMBOLOESPECIAL\n", yytext);}
{real}						{printf("%s -> REAL\n",yytext);}
{int_dec}|{int_bin}|{int_oct}|{int_hex}		{printf("%s -> INTEIRO\n",yytext);}
"algoritmo"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"até"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"caractere"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"caracteres"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"caso"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"de"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"e"						{printf("%s -> OPERADORLOGICO\n", yytext);}
"enquanto"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"então"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"faça"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"falso"						{printf("%s -> LOGICO\n", yytext);}
"fim"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"fim-enquanto"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"fim-para"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"fim-se"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"fim-variáveis"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"função"					{printf("%s -> PALAVRARESERVADA\n", yytext);}	
"início"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"inteiro"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"inteiros"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"literais"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"literal"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"lógico"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"lógicos"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"matriz"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"não"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"ou"						{printf("%s -> LOGICO\n", yytext);}
"padrão"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"para"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"parar"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"passo"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"reais"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"real"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"retorne"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"se"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"seleciona"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"fim-seleciona"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"senão"						{printf("%s -> PALAVRARESERVADA\n", yytext);}
"variáveis"					{printf("%s -> PALAVRARESERVADA\n", yytext);}
"verdadeiro"					{printf("%s -> LOGICO\n", yytext);}
"+"						{printf("%s -> OPERADORARITMETICO\n", yytext);}
"-"						{printf("%s -> OPERADORARITMETICO\n", yytext);}
"*"						{printf("%s -> OPERADORARITMETICO\n", yytext);}
"/"						{printf("%s -> OPERADORARITMETICO\n", yytext);}
"%"						{printf("%s -> OPERADORARITMETICO\n", yytext);}
"++"						{printf("%s -> OPERADORARITMETICO\n", yytext);}
"--"						{printf("%s -> OPERADORARITMETICO\n", yytext);}
":="						{printf("%s -> ATRIBUICAO\n", yytext);}
">"						{printf("%s -> OPERADORRELACIONAL\n", yytext);}
"<"						{printf("%s -> OPERADORRELACIONAL\n", yytext);}
">="						{printf("%s -> OPERADORRELACIONAL\n", yytext);}
"<="						{printf("%s -> OPERADORRELACIONAL\n", yytext);}
"="						{printf("%s -> OPERADORRELACIONAL\n", yytext);}
"<>"						{printf("%s -> OPERADORRELACIONAL\n", yytext);}
"&&"						{printf("%s -> OPERADORLOGICO\n", yytext);}
"||"						{printf("%s -> OPERADORLOGICO\n", yytext);}
"!"						{printf("%s -> OPERADORLOGICO\n", yytext);}
{caractere}					{printf("%s -> CARACTER\n", yytext);}
{string}					{printf("%s -> LITERAL\n", yytext);}
{comentario_linha}				;
{comentario_bloco}				;
{identificador}					{printf("%s -> IDENTIFICADOR\n",yytext);}
[ \t\n]						;
<<EOF>>						{return;} /* ctrl+D*/
%%
int main()
{
  
  yylex();

}

/* se definir esta função não necessita compilar com o parâmetro -lfl */
int yywrap()
{
	return(1);
}

