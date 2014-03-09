#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include <sys/types.h>
#include <dirent.h>
//#include <ncurses.h>

char* solicitaNomePrograma(){
	char *programa;
    char lixo;
    
    void makeStartLine();
    printf("## Compilar Programa\n");
	programa = (char *) calloc(50, sizeof(char));
	printf("## Digite o nome do programa: \n");
	printf("## ");
	scanf("%[^\n]", programa);
	scanf("%c", &lixo);
	//strcpy(programa, "exemplos/in10.gpt"); //executando exemplo in10.gpt
	void makeEndLine();
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
	makeStartLine();
	printf("## Arquivos .gpt no diretório atual.\n");
	makeStartLine();
	while (dirp && !errno) {
    	errno = 0;
    	if ((dp = readdir(dirp)) != NULL) {
    		len = strlen(dp->d_name);
    		if(len>4){
    			if( p = strstr(dp->d_name, ".gpt") ){
    				if(p[4] == '\0'){
	    				printf("## - %s\n", dp->d_name);	
	    				i++;
	    			}
    			}	
    		}
   	     }else{
   	     	errno = 1;
   	     }
   	 }
   	 if(i==0)
   	 	printf("## Não há nenhum arquivo .gpt no diretório local.\n");
	makeEndLine();
}

void showSobre(){
	char lixo;
	system("clear");
	printf(" ############################################################################### \n");
	printf(" ############################################################################### \n");
	printf(" ##    UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO - UFES                          ## \n");
	printf(" ##    CENTRO TECNOLÓGICO - CT                                                ## \n");
	printf(" ##    DEPARTAMENTO DE INFORMATICA - DI                                       ## \n");
	printf(" ##    CURSO DE ENGENHARIA DE COMPUTAÇÃO - ENG. COMP.                         ## \n");
	printf(" ##                                                                           ## \n");
	printf(" ##    INTERPRETADOR DE G-PORTUGOL                                            ## \n");
	printf(" ##    DISCIPLINA DE COMPILADORES                                             ## \n");
	printf(" ##    PROFESSORA: MARIELLA BERGER                                            ## \n");
	printf(" ##    COMPONENTES: JACKSON WILLIAN BRITO; TALLES TATAGIBA MARTINS DE SOUZA   ## \n");
	printf(" ############################################################################### \n");
	printf(" ############################################################################### \n");
	printf("## Pressione <enter> para voltar ao menu principal\n");
	printf("## ");
	scanf("%c",&lixo);
}

int showMenu(){
	int i,j;
	char lixo;
	
	
    system("clear");
	printf("############################################################################### \n");
	printf("############################################################################### \n");
	printf("##                                                                           ## \n");
	printf("##                      INTERPRETADOR DE G-PORTUGOL                          ## \n");
	printf("##                                                                           ## \n");
	printf("############################################################################### \n");
	printf("##                                                                           ## \n");
	printf("## 1 - Compilar um programa                                                  ## \n");
	printf("##                                                                           ## \n");
	printf("## 2 - Executar um programa já compilado                                     ## \n");
	printf("##                                                                           ## \n");
	printf("## 3 - Mostrar árvore de execução de um programa compilado                   ## \n");
	printf("##                                                                           ## \n");
	printf("## 4 - Ver programas compilados                                              ## \n");
	printf("##                                                                           ## \n");
	printf("## 5 - Listar arquivos .gpt no diretório atual                               ## \n");
	printf("##                                                                           ## \n");
	printf("## 6 - Sobre o interpretador                                                 ## \n");
	printf("##                                                                           ## \n");
	printf("## 7 - Sair do interpretador                                                 ## \n");
	printf("##                                                                           ## \n");
	printf("############################################################################### \n");
	i = getOption();

	return i;
}

void showDespedida(){
	printf("############################################################################### \n");
	printf("############################################################################### \n");
	printf("##                                                                           ## \n");
	printf("##         Obrigado por utilizar nosso interpretador de G-Portugol           ## \n");
	printf("##                  Esperamos uma nova visita em breve!!                     ## \n");
	printf("##                                                                           ## \n");
	printf("############################################################################### \n");
	printf("############################################################################### \n\n");

}


void showBoasVindas(){
	system("clear");
	printf("############################################################################### \n");
	printf("############################################################################### \n");
	printf("##                                                                           ## \n");
	printf("##              Seja bem vindo ao interpretador de G-Portugol                ## \n");
	printf("##                                                                           ## \n");
	printf("##     By: JACKSON WILLIAN BRITO                                             ## \n");
	printf("##         TALLES TATAGIBA MARTINS DE SOUZA                                  ## \n");
	printf("##                                                     Março - 2014          ## \n");
	printf("############################################################################### \n");
	printf("############################################################################### \n");
	printf("##  Aguarde 5 segundos..                                                     ## \n");
	printf("############################################################################### \n");
	sleep(2);
}

int getOption(){
	char lixo;
	int i;
	printf("############################################################################### \n");
	printf("## Entre com a opção desejada -                                                 \n");
	printf("## ");	
	scanf("%d",&i);
	scanf("%c",&lixo);
	printf("############################################################################### \n\n");	
	return i;
}

void makeStartLine(){
		printf("############################################################################### \n");
}

void makeEndLine(){
		printf("############################################################################### \n\n");
}
