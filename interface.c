#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include <sys/types.h>
#include <dirent.h>

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

void listarFiles(){

	DIR *dirp; 
	struct dirent *dp;
	int errno = 0;
	int len = 0;
	int i=0;
	dirp = opendir(".");
	char* p;
	
	while (dirp && !errno) {
    	errno = 0;
    	if ((dp = readdir(dirp)) != NULL) {
    		len = strlen(dp->d_name);
    		if(len>4){
    			if( p = strstr(dp->d_name, ".gpt") ){
    				if(p[4] == '\0')
	    				printf("%d - %s\n", ++i,dp->d_name);	
    			}	
    		}
   	     }else{
   	     	errno = 1;
   	     }
   	 }
   	 if(i==0)
   	 	printf("Não há nenhum arquivo .gpt no diretório local.\n");
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
	printf("## 5 - Ver .gpt	       ##\n");
	printf("##                     ##\n");
	printf("## 6 - Sair    	       ##\n");
	printf("##                     ##\n");
	printf("#########################\n");
	printf("#########################\n\n");
	
	scanf("%d",&i);
	scanf("%c",&lixo);
	
	return i;
}

