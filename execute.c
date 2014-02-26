#include <string.h>
#include "execute.h"
#include "variables.h"
#include "hash.h"

extern hashTable* hashVariables;
char globalVarName[50];

char* findType(treeNode *t, char* s){
	treeNode* aux = t;
	while(aux->children[0] != NULL) aux = aux->children[0];
	strcpy(s,aux->type);
	variable *var;
	if(!strcmp(s, "VARIAVEL")){
		List *l = lookupStringVariable(hashVariables, aux->value);
		var = (variable*) l->info;
		if (var->type == 3) strcpy(s, "REAL");
		else if (var->type == 0) strcpy(s, "INTEIRO");
	}
}

void executeTree(treeNode* t){
	while(t != NULL){
		executeNode(t);
		t = t->next;
	}

	return;
}

void* executeNode(treeNode* t){
	int *intReturn = (int*)malloc(sizeof(int));
	double *doubleReturn = (double*)malloc(sizeof(double));
	char stringReturn[50];
	char charReturn;
	variable* var;
	List* list;
	char type[50];
	treeNode* aux;
	treeNode* aux2;
	int i,j;
	int j1;
	
	int c = convertValuesTreeNode(t->value,t->type);
	printf("tipo convertido: %d\n",c);
	switch (c) {
	case 1: //inteiro
		*intReturn = atoi(t->value);
		return (void*)intReturn;
	case 2: //real
		*doubleReturn = stringRealToDouble(t->value);
		return (void*)doubleReturn;
		return;
	case 3: // :=
		 list = (lookupStringVariable(hashVariables, t->children[0]->value));
		 var = (variable*) ( list->info );
		 if(var->matrix) strcpy(globalVarName,  var->name);
		 if(var->type == 4 || var->type == 0){ var->value = (int*)(executeNode(t->children[1]) ) ; return; }
		 //if(var->type == 1){ var->value = (char) (executeNode(t->children[1])); return; }
		 if(var->type == 2){ strcpy(var->value, (char*)(executeNode(t->children[0]))); return; }
		 if(var->type == 3){ var->value = (double*)executeNode(t->children[1]); return; }
		 return;	
	case 4: // /
		//Percorre os filhos a esquerda para identificar o tipo que só pode ser inteiro ou float
		findType(t, type);
		 if(!strcmp(type,"INTEIRO")){ 
		 	*intReturn = *((int*)executeNode(t->children[0])) / *((int*)executeNode(t->children[1])); 
		 	return intReturn; 
		 }
		 if(!strcmp(type,"REAL")){
		 	*doubleReturn = *((double*)(executeNode(t->children[0]))) / *((double*)(executeNode(t->children[1]))); 
		 	return doubleReturn;
		return;
		 }
		 return;
	case 5: // *
		//Percorre os filhos a esquerda para identificar o tipo que só pode ser inteiro ou float
		findType(t, type);
		 if(!strcmp(type,"INTEIRO")){ 
		 	*intReturn = *((int*)executeNode(t->children[0])) * *((int*)executeNode(t->children[1])); 
		 	return intReturn; 
		 }
		 if(!strcmp(type,"REAL")){
		 	*doubleReturn = *((double*)executeNode(t->children[0])) * *((double*)executeNode(t->children[1])); 
		 	return doubleReturn;
		 }
		 return;
	case 6: // %
		//Percorre os filhos a esquerda para identificar o tipo que só pode ser inteiro ou float
		findType(t, type);
		 if(!strcmp(type,"INTEIRO")){ 
		 	*intReturn = *((int*)executeNode(t->children[0])) % *((int*)executeNode(t->children[1])); 
		 	return intReturn; 
		 }
		 return;
	case 7: // +
		//Percorre os filhos a esquerda para identificar o tipo que só pode ser inteiro ou float
		findType(t, type);
		 if(!strcmp(type,"INTEIRO")){ 
		 	*intReturn = *((int*)executeNode(t->children[0])) + *((int*)executeNode(t->children[1])); 
		 	return intReturn; 
		 }
		 if(!strcmp(type,"REAL")){
		 	*doubleReturn = *((double*)executeNode(t->children[0])) + *((double*)executeNode(t->children[1])); 
		 	return doubleReturn;
		 }
		 return;
	case 8: // - UNARIO
		//Percorre os filhos a esquerda para identificar o tipo que só pode ser inteiro ou float
		findType(t, type);
		 if(!strcmp(type,"INTEIRO")){ 
		 	*intReturn = -1 * *((int*)executeNode(t->children[0])); 
		 	return intReturn; 
		 }
		 if(!strcmp(type,"REAL")){
		 	*doubleReturn = -1.0 * *((double*)executeNode(t->children[0])); 
		 	return doubleReturn;
		 }
		 return;
	case 9: // -
		//Percorre os filhos a esquerda para identificar o tipo que só pode ser inteiro ou float
		findType(t, type);
		 if(!strcmp(type,"INTEIRO")){ 
		 	*intReturn = *((int*)executeNode(t->children[0])) - *((int*)executeNode(t->children[1])); 
		 	return intReturn; 
		 }
		 if(!strcmp(type,"REAL")){
		 	*doubleReturn = *((double*)executeNode(t->children[0])) - *((double*)executeNode(t->children[1])); 
		 	return doubleReturn;
		 }
		 return;
	case 10: // Variavel	
		 list = (List*)(lookupStringVariable(hashVariables, t->value)); 
		 var = (variable*) list->info;
		 if(var->type == 0 || var->type == 4) {
		 	*intReturn = *((int*)var->value);
		 	return intReturn;
		 } 
		 if(var->type == 1){
		 //	charReturn = (char*)var->value;
		 //	return &charReturn;
		 }
		 if(var->type == 2){
		 	strcpy(stringReturn,(char*)var->value);
		 //	return &stringReturn;
		 }
		 if(var->type == 3){
		 	*doubleReturn = *((double*)var->value);
		 	return doubleReturn;
		 }		 
		 return;
	case 11: // ()
		return executeNode(t->children[0]);
	case 12: // [] ou {}
		
		list = (List*)(lookupStringVariable(hashVariables, globalVarName)); 
		var = (variable*) list->info;
		if(var->dimension == 1){
			aux = t->children[0];
			for (i=0;i<var->nColumn;i++){
				if (var->type == 0 || var->type == 4) {
					((int*)var->value)[i] = *((int*)(executeNode(aux)));
				}
				aux = aux->next;
			}
			printf("aqui\n");	
			printf("n = [%d,%d,%d,%d]\n", ((int*)(var->value))[0], ((int*)(var->value))[1] , ((int*)(var->value))[2], ((int*)(var->value))[3]);
			
			
		} else { /*
			aux = t->children[0];
			for(i = 0; i<globalVar->nLine;i++){
				aux2 = aux->children[0];
				for(j=0;j<globalVar->nColumn;j++){
					if (globalVar->type == 0 || globalVar->type == 4) {
						((int**)globalVar->value +  j*sizeof(int*))[i]  = executeNode(aux2);
					}
					aux2 = aux2->next;
				}
				aux = aux->next;
			}
			
			/*for(i=0;i<globalVar->nLine;i++){
				printf("%d , %d , %d , %d \n", *((int*)(globalVar->value+(globalVar->nColumn*0+i)*sizeof(int))), *((int*)(globalVar->value+(globalVar->nColumn+i)*sizeof(int))), *((int*)(globalVar->value+(globalVar->nColumn*2+i)*sizeof(int))), *((int*)(globalVar->value+(globalVar->nColumn*3+i)*sizeof(int))) );
			}*/
					
		}
		
		return;
	case 13: //Matriz
		 list = (List*)(lookupStringVariable(hashVariables, t->value)); 
		 var = (variable*) list->info;
		 if(var->dimension == 1){
		 	i = *((int*)executeNode(t->children[0]));
		 	printf("i: %d\n",i);
		 	*((int*) var->value) = 10;
		 	*intReturn = *((int*) var->value);
	//	 	*intReturn = ((int*)( var->value ))[i];
		 	return intReturn;
		 }else{ /*
		 	i = *((int*)executeNode(t->children[0]));
		 	j = *((int*)executeNode(t->children[1]));
		 	*intReturn = ((int*) (var->value + var->nColumn*sizeof(int)) )[i];
	*/	 	return ;//intReturn;
		 }
		return;
	case 14: // >
		findType(t,type);
		*intReturn = (*((int*)executeNode(t->children[0]))) > (*((int*)executeNode(t->children[1])));
		return intReturn; 
	case 15: // <
		findType(t,type);
		*intReturn = (*((int*)executeNode(t->children[0]))) < (*((int*)executeNode(t->children[1])));
		return intReturn;
	case 16: // <>
		findType(t,type);
		*intReturn = (*((int*)executeNode(t->children[0]))) != (*((int*)executeNode(t->children[1])));
		return intReturn;
	case 17: // =
		findType(t,type);
		*intReturn = (*((int*)executeNode(t->children[0]))) == (*((int*)executeNode(t->children[1])));
		return intReturn;
	case 18: // >=
		findType(t,type);
		*intReturn = (*((int*)executeNode(t->children[0]))) >= (*((int*)executeNode(t->children[1])));
		return intReturn;
	case 19: //	<=
		findType(t,type);
		*intReturn = (*((int*)executeNode(t->children[0]))) <= (*((int*)executeNode(t->children[1])));
		return intReturn;
	default: return;
	
	}


}
