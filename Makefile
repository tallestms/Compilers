all:	
	flex -i trab2.l
	bison trab2.y
	gcc -o trab2 trab2.tab.c -lfl
