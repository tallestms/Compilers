#include <stdio.h>
#include "lists.h"

#define MAX_LITERAL_DECLARATION 53

int verifyRelationship(int *varRelations, int currentRelationPos);
void printRelationship(int *varRelations, int currentRelationPos);
int numSpaces(char *s);
int verifyRelationshipComparison(int *varRelations, int currentRelationComparison,int currentRelationPos);
int verifyRelationshipCondition(int *varRelations, int currentRelationComparison, int currentRelationPos);
int convertValuesTreeNode(char v[50],char t[50]);
double stringRealToDouble(char s[50]);
int findArgumentType(int argumentNumber, List* aux);
void retiraAspasFinal(char* s);
void *retornaValor(int type, void* point);
void terminate();
char getCharFromCharString(char s[50]);
int verifyPrimitivesMaxMinMed(char* currentFunction);
