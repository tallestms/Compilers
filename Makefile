all:	
	flex -i compiler.l
	bison compiler.y
	gcc -o compiler compiler.tab.c lists.c hash.c variables.c functions.c -lfl
