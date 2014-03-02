all:	
	flex -i compiler.l
	bison compiler.y
	gcc -o trab4 compiler.tab.c lists.c hash.c variables.c functions.c aux.c tree.c stack.c execute.c interface.c program.c -lfl -g -lm -lncurses

	
clean:
	rm -rf *~ trab3.aux trab3.blg trab3.bbl trab3.toc trab3.out lex.yy.c compiler.tab.c trab3.log
