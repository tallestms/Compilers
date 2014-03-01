#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"

char* solicitaNomePrograma(){
	char *programa;
    char lixo;
      
    printf("Compilar Programa\n");
	programa = (char *) calloc(50, sizeof(char));
	//printf("Digite o nome do programa: \n");
	//scanf("%[^\n]", programa);
	//scanf("%c", &lixo);
	strcpy(programa, "exemplos/in10.gpt"); //executando exemplo in10.gpt
	
	return programa;
}

int showMenu(){
	int i;
	char lixo;

	system("clear");
	printf("#########################\n");
	printf("#########################\n");
	printf("##                     ##\n");
	printf("##     COMPILADORES    ##\n");
	printf("##      G-PORTUGOL     ##\n");
	printf("##                     ##\n");
	printf("##  JACKSON ; TALLES   ##\n");	
	printf("#########################\n");
	printf("#########################\n");
	printf("##                     ##\n");
	printf("## 1 - Compilar        ##\n");
	printf("##                     ##\n");
	printf("## 2 - Executar        ##\n");
	printf("##                     ##\n");
	printf("## 3 - Mostrar árvore  ##\n");
	printf("##                     ##\n");
	printf("## 4 - Ver programas   ##\n");
	printf("##                     ##\n");
	printf("#########################\n");
	printf("#########################\n\n");
	
	scanf("%d",&i);
	scanf("%c",&lixo);
	
	return i;
}

