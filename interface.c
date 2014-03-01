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

