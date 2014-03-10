#include <string.h>
#include <math.h>
#include "execute.h"

hashTable* hashExecuteVariables = NULL;
hashTable* hashExecuteFunctions = NULL;
Stack* stackExecuteVariables = NULL;
Stack* stackExecuteVariablesAux = NULL;
char globalVarName[50];
int globalRetornoFlag = 0;

char* findType(treeNode *t, char* s){
	treeNode* aux = t;
	while(aux->children[0] != NULL && strcmp(aux->type,"MATRIX")) aux = aux->children[0];
	strcpy(s,aux->type);
	variable *var;
	if(!strcmp(s, "VARIAVEL") || !strcmp(s, "MATRIX")){
		List *l = lookupStringVariable(hashExecuteVariables, aux->value);
		var = (variable*) l->info;
		if (var->type == 3) strcpy(s, "REAL");
		else if (var->type == 0) strcpy(s, "INTEIRO");
		else if (var->type == 4) strcpy(s, "LOGICO");
		else if (var->type == 2) strcpy(s, "LITERAL");
		else if (var->type == 1) strcpy(s, "CARACTER");
	}
}

void *executeFunction(treeNode *func){
	treeNode *auxParam;
	treeNode *auxFunc;
	List *list;
	variable *var;
	int numVariables = 0;
	int numParams = 0;
	void* retorno = NULL;
	void* flag = (void*)0x1;
	int i;
	
	/*empilhar variaveis da função chamada*/
	if (stackExecuteVariables==NULL)
		stackExecuteVariables = createStack();
	//percorrer a lista de variáveis empilhando-as
	//Empilhando parametros
	auxParam = func->children[0]->children[1];
	while(auxParam!=NULL){
		list = (lookupStringVariable(hashExecuteVariables, auxParam->value));
		if(list!=NULL){
			var = (variable*) ( list->info );
			pushStack(stackExecuteVariables, (void*)retornaValor(var->type, var->value));
			numVariables++;
		}
		auxParam = auxParam->next;
	}
	auxParam = func->children[0]->children[2];
	while(auxParam!=NULL){
		list = lookupStringVariable(hashExecuteVariables, auxParam->value);
		if(list!=NULL) {
			var = (variable*) ( list->info );
		
			pushStack(stackExecuteVariables, (void*)retornaValor(var->type, var->value));
			numVariables++;
		}
		auxParam = auxParam->next;
	}
	
	/**
	*** Passagem de parametros
	*** Coloco os valores na pilha, passo para  a pilha auxiliar para manter a ordem
	*** e depois desempilho na variável correta.
	**/
	auxParam = func->children[1];
	while(auxParam!=NULL) {
		//list = lookupStringVariable(hashExecuteVariables, auxParam->children[0]->type);
		//printf(">>>%s\n",auxParam->children[0]->value);
				//empilha
		var = (variable*) ( list->info );
		pushStack(stackExecuteVariables, (void*)executeNode(auxParam->children[0]));
		//printNode(auxParam->children[0],3,6);
		//printf("empilhado %d\n", *((int*)executeNode(auxParam->children[0])));
		numParams++;
		auxParam = auxParam->next;		
	}
	//Usa pilha auxiliar
	if(stackExecuteVariablesAux==NULL)
		stackExecuteVariablesAux = createStack();
	for (i=0;i<numParams;i++){
		pushStack(stackExecuteVariablesAux, popStack(stackExecuteVariables));
	}
	//Desempilham na ordem
	auxParam = func->children[1];
	while(auxParam!=NULL){
		list = lookupStringVariable(hashExecuteVariables, auxParam->children[1]->value);
		if(list!=NULL) {
			var = (variable*) ( list->info );
			if(var->type == 0 || var->type == 4){ //int
				*((int*)var->value) = *((int*)popStack(stackExecuteVariablesAux));
				//printf("variavel %s recebendo da pilha valor %d\n", var->name, *((int*)var->value) );
			}
			if(var->type == 1){ //char
				*((char*)var->value) = *((char*)popStack(stackExecuteVariablesAux));
			}
			if(var->type == 2){ //literal
				strcpy(((char*)var->value), (char*)popStack(stackExecuteVariablesAux));
			}
			if(var->type == 3){ //real
				*((double*)var->value) = *((double*)popStack(stackExecuteVariablesAux));
			}
		}
		auxParam = auxParam->next;
	}
	

	//	executar a função empilhando o retorno quando houver 
	list = lookupStringFunction(hashExecuteFunctions, func->children[0]->value);
	if(list != NULL){
		function* funcAux = (function*) list->info;
		auxFunc = funcAux->functionTree->children[3];
		//printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		//printNode(auxFunc, 13, 2,0);
		//printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		//printNode(auxFunc, 13,6);
		while(auxFunc!=NULL && globalRetornoFlag == 0){
			executeNode(auxFunc);
			auxFunc = auxFunc->next;
		}
	
		/*desempilhar o retorno*/
		if(strcmp(func->children[0]->children[0]->type,"VOID")!=0) {
			retorno = popStack(stackExecuteVariables);
			globalRetornoFlag = 0;
		}
	}	
	/*desempilhar as variaveis da função chamada usando o size e a pilha auxiliar*/
	if(stackExecuteVariablesAux==NULL)
		stackExecuteVariablesAux = createStack();
	for (i=0;i<numVariables;i++){
		pushStack(stackExecuteVariablesAux, popStack(stackExecuteVariables));
	}
	auxParam = func->children[0]->children[1];
	while(auxParam!=NULL){
		list = (lookupStringVariable(hashExecuteVariables, auxParam->value));
		if(list!=NULL){
			var = (variable*) ( list->info );
			var->value = popStack(stackExecuteVariablesAux);
		}
		auxParam = auxParam->next;
	}
	auxParam = func->children[0]->children[2];
	while(auxParam!=NULL){
		list = lookupStringVariable(hashExecuteVariables, auxParam->value);
		if(list!=NULL) {
			var = (variable*) ( list->info );
			var->value = popStack(stackExecuteVariablesAux);
		}
		auxParam = auxParam->next;
	}
	
	return retorno;
}

void executeProgram(Program* p){
	if(p!=NULL){
		//restaura hashVariables 
		hashExecuteVariables = p->hashVariables;
		//restaura hashFunction 
		hashExecuteFunctions = p->hashFunctions;
		//Executa programa 
		executeTree(p->exec);
		//Limpa estruturas 
		hashExecuteVariables = NULL;
		hashExecuteFunctions = NULL;
	}
	return;
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
	char* stringReturn = (char*)malloc(sizeof(char) * MAX_LITERAL_DECLARATION);
	char *charReturn = (char*) malloc(sizeof(char));
	variable* var;
	List* list;
	char type[50];
	char lixo;
	treeNode* aux;
	treeNode* aux2;
	int i,j, intA, intB;
	int j1;
	int flag=0;
	double doubleA, doubleB;
	
	int c = convertValuesTreeNode(t->value,t->type);
	switch (c) {
	case -2: //literal
		strcpy(stringReturn, t->value);
		return stringReturn;
	case -1: //caracter
		*charReturn = getCharFromCharString((char*)t->value);
		return charReturn;
	case 0: // verdadeiro - falso
		if(!strcmp(t->value, "verdadeiro")) *intReturn = 1;
		else *intReturn = 0;
		return intReturn;
	case 1: //inteiro
		*intReturn = atoi(t->value);
		return (void*)intReturn;
	case 2: //real
		*doubleReturn = stringRealToDouble(t->value);
		return (void*)doubleReturn;
		return;
	case 3: // :=
		 list = (lookupStringVariable(hashExecuteVariables, t->children[0]->value));
		 var = (variable*) ( list->info );
		 //atribuição de matrizes completa
		 if(var->matrix && !strcmp(t->children[0]->type,"VARIAVEL") ) {  strcpy(globalVarName,  var->name); executeNode(t->children[1]); return; }
		 //atribuição de matrizes por posição
		 if(var->matrix && var->dimension == 1) {
		 	i = *((int*)executeNode(t->children[0]->children[0]));
		 	//inteiros
		 	if ( var->type == 0 ) { 
		 		((int*)var->value)[i] = * ((int*)executeNode(t->children[1]));
		 		return;
		 	}
		 	//reais
		 	if ( var->type == 3 ) { 
		 		((double*)var->value)[i] = * ((double*)executeNode(t->children[1]));
		 		return;
		 	}
		 	//caracter
		 	if ( var->type == 1 ) { 
		 		((char*)var->value)[i] = * ((char*)executeNode(t->children[1]));
		 		return;
		 	}
		 	//literais
		 	if ( var->type == 2 ) { 
		 		strcpy( ((char*)var->value + MAX_LITERAL_DECLARATION*i*sizeof(char) ) , ((char*)executeNode(t->children[1])) );
		 		return;
		 	}
		 } 
		 if(var->matrix && var->dimension == 2){
		 	i = *((int*)executeNode(t->children[0]->children[0]));
		 	j = *((int*)executeNode(t->children[0]->children[1]));
			int nColumnAux = var->nColumn;
		 	//inteiros
		 	if ( var->type == 0 ) { 
			    
		 		((int*)var->value)[i*nColumnAux+j] = *((int*)executeNode(t->children[1]));
		 		return;
		 	}
		 	//reais
		 	if ( var->type == 3 ) { 
		 		((double*)var->value)[i*nColumnAux+j] = *((double*)executeNode(t->children[1]));
		 		return;
		 	}
		 	//caracter
		 	if ( var->type == 1 ) { 
		 		((char*)var->value)[i*nColumnAux+j] = *((char*)executeNode(t->children[1]));
		 		return;
		 	}
		 	//literais
		 	if ( var->type == 2 ) { 
		 		strcpy( ((char*)var->value + (i*var->nColumn+j)*MAX_LITERAL_DECLARATION*sizeof(char) ), ((char*)executeNode(t->children[1])) );
		 		return;
		 	}
		 }
		 //inteiro ou logico
		 if(var->type == 4 || var->type == 0){ var->value = (int*)(executeNode(t->children[1]) ) ; return; }
		 //caracter
		 if(var->type == 1){ var->value = (char*) (executeNode(t->children[1])); return; }
		 //literal
		 if(var->type == 2){ strcpy((char*)var->value, (char*)(executeNode(t->children[1]))); return; }
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
		 //Não funciona para real
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
		 list = (List*)(lookupStringVariable(hashExecuteVariables, t->value)); 
		 var = (variable*) list->info;
		 if(var->type == 0 || var->type == 4) {
		 	*intReturn = *((int*)var->value);
		 	return intReturn;
		 } 
		 if(var->type == 1){
		 	*charReturn = *((char*)var->value);
		 	return charReturn;
		 }
		 if(var->type == 2){
		 	strcpy(stringReturn,(char*)var->value);
		 	return stringReturn;
		 }
		 if(var->type == 3){
		 	*doubleReturn = *((double*)var->value);
		 	return doubleReturn;
		 }		 
		 return;
	case 11: // ()
		return executeNode(t->children[0]);
	case 12: // [] ou {}
		
		list = (List*)(lookupStringVariable(hashExecuteVariables, globalVarName)); 
		var = (variable*) list->info;
		if(var->dimension == 1){
			aux = t->children[0];
			for (i=0;i<var->nColumn;i++){
				//inteiro
				if (var->type == 0) {
					((int*)var->value)[i] = *((int*)(executeNode(aux)));
				}
				//caracter
				if (var->type == 1) {
					((char*)var->value)[i] = *((char*)(executeNode(aux)));
				}
				//literal
				if (var->type == 2) {
					strcpy( ((char*)var->value + MAX_LITERAL_DECLARATION*i*sizeof(char) ) , ((char*)executeNode(aux)) );
				}
				//real
				if (var->type == 3) {
					((double*)var->value)[i] = *((double*)(executeNode(aux)));
				}
				//incrementa
				aux = aux->next;
			}
		} else { 
			aux = t->children[0];
			for(i = 0; i<var->nLine;i++){
				aux2 = aux->children[0];
				for(j=0;j<var->nColumn;j++){
					//inteiro
					if (var->type == 0) {
						((int*)(var->value+j*sizeof(int)))[i] = *((int*)(executeNode(aux2)));
					}
					//caracter
					if (var->type == 1) {
						((char*)(var->value+j*sizeof(char)))[i] = *((char*)(executeNode(aux2)));
					}
					//literal
					if (var->type == 2) {
						strcpy( ((char*)var->value + (i*var->nColumn+j)*MAX_LITERAL_DECLARATION*sizeof(char) ), ((char*)executeNode(aux2)) );
					}
					//real
					if (var->type == 3) {
						((double*)(var->value+j*sizeof(double)))[i] = *((double*)(executeNode(aux2)));
					}
					//incrementa coluna
					aux2 = aux2->next;
				}
				//incrementa linha
				aux = aux->next;
			}
		}
		return;
	case 13: //Matriz
		 list = (List*)(lookupStringVariable(hashExecuteVariables, t->value)); 
		 var = (variable*) list->info;
		 if(var->dimension == 1){
		 	i = *((int*)executeNode(t->children[0]));
		 	//inteiro
		 	if(var->type == 0){
		 		*intReturn = ((int*) var->value)[i];
		 		return intReturn;
			}
			//caracter
			if(var->type == 1){
				*charReturn = ((char*) var->value)[i];
				return charReturn;
			}		 
		 	//literal
			if(var->type == 2){
				strcpy(stringReturn, ((char*) var->value + i*MAX_LITERAL_DECLARATION*sizeof(char)));
				return stringReturn;
			}
			//real
			if(var->type == 3){
				*doubleReturn = ((double*) var->value)[i];
		 		return doubleReturn;
			}
			
		 }else{ 
		 	i = *((int*)executeNode(t->children[0]));
		 	j = *((int*)executeNode(t->children[1]));
			int nColumnAux = var->nColumn;
		 	if(var->type == 0) {
			 	*intReturn = ((int*) var->value)[i*nColumnAux+j];
			 	return intReturn;
			}
			//caracter
			if(var->type == 1) {
			 	*charReturn = ((char*)var->value)[i*nColumnAux+j];
			 	return charReturn;
			}
			//literais
			if(var->type == 2){
				strcpy( stringReturn, ((char*)var->value + (j*var->nColumn+i)*MAX_LITERAL_DECLARATION*sizeof(char)) );
				return stringReturn;
			}
			//reais 
			if(var->type == 3) {
			 	*doubleReturn = ((double*) var->value)[i*nColumnAux+j];
			 	return doubleReturn;
			}
		 }
		return;
	case 14: // >
		findType(t,type);
		if(!strcmp(type, "INTEIRO")){
			*intReturn = (*((int*)executeNode(t->children[0]))) > (*((int*)executeNode(t->children[1])));
			return intReturn; 
		}
		if(!strcmp(type, "REAL")){
			*intReturn = (int)( (*((double*)executeNode(t->children[0]))) > (*((double*)executeNode(t->children[1]))) );
			return intReturn; 
		}
	case 15: // <
		findType(t,type);
		if(!strcmp(type, "INTEIRO")){
			*intReturn = (*((int*)executeNode(t->children[0]))) < (*((int*)executeNode(t->children[1])));
			return intReturn; 
		}
		if(!strcmp(type, "REAL")){
			*intReturn = (int)( (*((double*)executeNode(t->children[0]))) < (*((double*)executeNode(t->children[1]))) );
			return intReturn; 
		}
	case 16: // <>
		findType(t,type);
		if(!strcmp(type, "INTEIRO")){
			*intReturn = (*((int*)executeNode(t->children[0]))) != (*((int*)executeNode(t->children[1])));
			return intReturn; 
		}
		if(!strcmp(type, "REAL")){
			*intReturn = (int)( (*((double*)executeNode(t->children[0]))) != (*((double*)executeNode(t->children[1]))) );
			return intReturn; 
		}
	case 17: // =
		findType(t,type);
		if(!strcmp(type, "INTEIRO")){
			*intReturn = (*((int*)executeNode(t->children[0]))) == (*((int*)executeNode(t->children[1])));
			return intReturn; 
		}
		if(!strcmp(type, "REAL")){
			*intReturn = (int)( (*((double*)executeNode(t->children[0]))) == (*((double*)executeNode(t->children[1]))) );
			return intReturn; 
		}
		if(!strcmp(type, "LOGICO")){
			intA = *((int*)executeNode(t->children[0]));
			intB = *((int*)executeNode(t->children[1]));
			*intReturn = (intA && intB || intA == 0 && intB == 0) ? 1 : 0;
			return intReturn;
		}
	case 18: // >=
		findType(t,type);
		if(!strcmp(type, "INTEIRO")){
			*intReturn = (*((int*)executeNode(t->children[0]))) >= (*((int*)executeNode(t->children[1])));
			return intReturn; 
		}
		if(!strcmp(type, "REAL")){
			*intReturn = (int)( (*((double*)executeNode(t->children[0]))) >= (*((double*)executeNode(t->children[1]))) );
			return intReturn; 
		}
	case 19: //	<=
		findType(t,type);
		if(!strcmp(type, "INTEIRO")){
			*intReturn = (*((int*)executeNode(t->children[0]))) <= (*((int*)executeNode(t->children[1])));
			return intReturn; 
		}
		if(!strcmp(type, "REAL")){
			*intReturn = (int)( (*((double*)executeNode(t->children[0]))) <= (*((double*)executeNode(t->children[1]))) );
			return intReturn; 
		}
	case 20: // e
		*intReturn = *((int*)executeNode(t->children[0])) && *((int*)executeNode(t->children[1]));
		return intReturn; 
	case 21: // ou
		*intReturn = *((int*)executeNode(t->children[0])) || *((int*)executeNode(t->children[1]));
		return intReturn;
	case 22: //enquanto
		while( *((int*)executeNode(t->children[0])) ){
			executeTree(t->children[1]);
		}
		return;
	case 23: //faça enquanto
		do{
			executeTree(t->children[1]);
		}while( *((int*)executeNode(t->children[0])) );
		return;
	case 24: //se-senao
		if(*((int*)executeNode(t->children[0]))){
			executeTree(t->children[1]);
		}else{
			executeTree(t->children[2]);
		}
		return;
	case 25: //se
		if(*((int*)executeNode(t->children[0]))){
			executeTree(t->children[1]);
		}
		return;
	case 26: //para
		//executa condição inicial
		executeNode(t->children[0]);
		while ( ! ( *((int*)executeNode(t->children[1])) ) ){
			executeTree(t->children[3]);
			executeNode(t->children[2]);
		}	
		return;
	case 27: //seleciona
		findType(t, type);		
	//	list = (List*)(lookupStringVariable(hashExecuteVariables, t->children[0]->value)); 
	//	 var = (variable*) list->info;
		 treeNode* cases = t->children[1];
		 if(!strcmp(type, "INTEIRO")){
		 	flag = 1;
		 	while( cases != NULL && ( *((int*)executeNode(t->children[0])) != atoi(cases->children[0]->value) ) && strcmp(cases->children[0]->value,"padrao") ){
		 		cases = cases->next;	 		
		 	}
		}
		if(!strcmp(type, "REAL")){
		 	flag = 1;
		 	while( cases != NULL && ( *((double*)executeNode(t->children[0])) != stringRealToDouble((char*)cases->children[0]->value) ) && strcmp(cases->children[0]->value,"padrao") ){
		 		cases = cases->next;	 		
		 	}
		}
		if(!strcmp(type, "CARACTER")){
		 	flag = 1;
		 	while( cases != NULL && ( *((char*)executeNode(t->children[0])) != getCharFromCharString((char*)cases->children[0]->value) ) && strcmp(cases->children[0]->value,"padrao") ){
		 		cases = cases->next;	 		
		 	}
		}
		if(!strcmp(type, "LITERAL")){
		 	flag = 1;
		 	while( cases != NULL && ( strcmp( ((char*)executeNode(t->children[0])) , ((char*)cases->children[0]->value) ) ) && strcmp(cases->children[0]->value,"padrao") ){
		 		cases = cases->next;	 		
		 	}
		}
		if (flag){
		 	//executa uma vez
		 	if(cases!=NULL){
		 		executeTree(cases->children[1]);
		 	}
		 	//Executa o próximo caso o atual não tenha parar
			while(cases != NULL && cases->children[2]==NULL){
		 		cases = cases->next;
		 		
				if(cases){
					executeTree(cases->children[1]);
				}
		 	}
		 	
		 }
		 return;
	case 28: // ^
		//Percorre os filhos a esquerda para identificar o tipo que só pode ser inteiro ou float
		findType(t, type);
		if(!strcmp(type,"INTEIRO") ){
			*doubleReturn = pow ( *((int*)executeNode(t->children[0])) , *((int*)executeNode(t->children[1])) ); 
		 	return doubleReturn;
		}
		if(!strcmp(type,"REAL")){
			*doubleReturn = pow ( *((double*)executeNode(t->children[0])) , *((double*)executeNode(t->children[1])) ); 
		 	return doubleReturn;
		}
		 return;
	case 29: // Chamada de função
		return executeFunction(t);
	case 30: // Retorno
		//empilha valor do retorno
		pushStack(stackExecuteVariables, executeNode(t->children[0]));
		globalRetornoFlag = 1;
		return;
	case 31: //maximo
		findType(t, type);
		if(!strcmp(type, "INTEIRO")){
			intA = *((int*)executeNode(t->children[1]));
			intB = *((int*)executeNode(t->children[2]));
			if (intA > intB) *intReturn = intA; else *intReturn = intB;
			return intReturn;
		}
		if(!strcmp(type, "REAL")){
			doubleA = *((double*)executeNode(t->children[1]));
			doubleB = *((double*)executeNode(t->children[2]));
			if (doubleA > doubleB) *doubleReturn = doubleA; else *doubleReturn = doubleB;
			return doubleReturn;
		}
		return;
	case 32: //minimo
		findType(t, type);
		if(!strcmp(type, "INTEIRO")){
			intA = *((int*)executeNode(t->children[1]));
			intB = *((int*)executeNode(t->children[2]));
			if (intA < intB) *intReturn = intA; else *intReturn = intB;
			return intReturn;
		}
		if(!strcmp(type, "REAL")){
			doubleA = *((double*)executeNode(t->children[1]));
			doubleB = *((double*)executeNode(t->children[2]));
			if (doubleA < doubleB) *doubleReturn = doubleA; else *doubleReturn = doubleB;
			return doubleReturn;
		}
		return;
	case 33: //media
		findType(t, type);		
		if(!strcmp(type, "INTEIRO")){
			intA = *((int*)executeNode(t->children[1]));
			intB = *((int*)executeNode(t->children[2]));
			*intReturn = (intA + intB) / 2;
			return intReturn;
		}
		if(!strcmp(type, "REAL")){
			doubleA = *((double*)executeNode(t->children[1]));
			doubleB = *((double*)executeNode(t->children[2]));
			*doubleReturn = (doubleA + doubleB) / 2;
			return doubleReturn;
		}
		return;
	case 34: //imprima
		findType(t->children[1], type);
		if(!strcmp(type, "INTEIRO")){
			printf("%d", *((int*)executeNode(t->children[1])));
		}
		if(!strcmp(type, "REAL")){
			printf("%.2f", *((double*)executeNode(t->children[1])));
		}
		if(!strcmp(type, "LITERAL")){
			printf("%s", ((char*)executeNode(t->children[1])));
		}
		if(!strcmp(type, "CARACTER")){
			printf("%c", *((char*)executeNode(t->children[1])));
		}
		if(!strcmp(type, "LOGICO")){
			if(*((char*)executeNode(t->children[1])))
				printf("verdadeiro\n");
			else
				printf("falso\n");
		}
		return;
	case 35: //leia
		list = (List*)(lookupStringVariable(hashExecuteVariables, t->children[1]->value)); 
		var = (variable*) list->info;
		if(var->type == 0){ //inteiro
			scanf("%d", intReturn);
			scanf("%c", &lixo);
			*((int*)var->value) = *intReturn;
		}
		if(var->type==3){ //real
			scanf("%s", stringReturn);
			scanf("%c", &lixo);
			*doubleReturn = stringRealToDouble(stringReturn);
			*((double*)(var->value)) = *doubleReturn;
		}
		if(var->type==2){ //literal
			scanf("%s", stringReturn);
			scanf("%c", &lixo);
			strcpy((char*)var->value,stringReturn);
		}
		if( var->type==1 ){
			scanf("%c", charReturn);
			scanf("%c", &lixo);
			*((char*)var->value) = *charReturn;		
		}
		if(var->type == 4) {
			scanf("%s", stringReturn);
			scanf("%c", &lixo);
			if(!strcmp(stringReturn, "verdadeiro"))
			*((int*)var->value) = 1;
			else
			*((int*)var->value) = 0;
		}
		return;
	case 36: //imprimaln
		findType(t->children[1], type);
		if(!strcmp(type, "INTEIRO")){
			printf("%d\n", *((int*)executeNode(t->children[1])));
		}
		if(!strcmp(type, "REAL")){
			printf("%.2f\n", *((double*)executeNode(t->children[1])));
		}
		if(!strcmp(type, "LITERAL")){
			printf("%s\n", ((char*)executeNode(t->children[1])));
		}
		if(!strcmp(type, "CARACTER")){
			printf("%c\n", *((char*)executeNode(t->children[1])));
		}
		if(!strcmp(type, "LOGICO")){
			if(*((char*)executeNode(t->children[1])))
				printf("verdadeiro\n");
			else
				printf("falso\n");
		}
		return;
	case 37: //leialn
		list = (List*)(lookupStringVariable(hashExecuteVariables, t->children[1]->value)); 
		var = (variable*) list->info;
		//Só faz sentido para string
		if(var->type==2){
			scanf("%[^\n]", stringReturn);
			scanf("%c", &lixo);
			strcpy((char*)var->value,stringReturn);
		}
		return;
	default: return;
	}


}
