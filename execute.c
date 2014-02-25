#include "execute.h"

void* executeTree(treeNode* t){
	int intReturn;
	double doubleReturn;
	char[50] stringReturn;
	char charReturn;
	Variables* var;
	char type[50];
	treeNode* aux;
	
	int c = convertValuesTreeNode(t->value,t->type);
	switch (c) {
	case 1: //inteiro
		intReturn = atoi(t->value);
		return &intReturn;
	case 2: //real
		doubleReturn = stringRealToDouble(t->value);
		return &doubleReturn;
	case 3: // :=
		 var = lookupStringVariable(hashVariables, t->children[0]->value);
		 if(var->type == 4 || var->type == 0){ var->value = (int*) (executeTree(t->children[1]); break; }
		 if(var->type == 1 || var->type == 2){ var->value = (char*)  executeTree(t->children[1]); break; }
		 if(var->type == 3){ var->value = (double*)  executeTree(t->children[1]); break; }
		 break;	
	case 4: // /
		//Percorre os filhos a esquerda para identificar o tipo que só pode ser inteiro ou float
		 aux = t;
		 while(aux->children[0] != NULL) aux = aux->children[0];
		 type = aux->type;
		 if(!strcmp(type, "VARIAVEL")){
		 	var = lookupStringVariable(hashVariables, t->children[0]->value);
		 	type = //var->type;
		 	//TODO adicionar nome e nao valor do tipo
		 }
		 if(!strcmp(type,"INTEIRO")){ 
		 	intReturn = *((int*)execute(t->children[0])) / *((int*)execute(t->children[1])); 
		 	return &intReturn; 
		 }
		 if(!strcmp(type,"REAL")){
		 	doubleReturn = *((double*)execute(t->children[0])) / *((double*)execute(t->children[1])); 
		 	return &intReturn;
		 }
		 
	case 5: // *
	case 6: // %
	case 7: // +
	case 8: // -

	}


}
