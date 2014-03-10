all:	
	flex -i compiler.l
	bison compiler.y
	gcc -o trab4 compiler.tab.c lists.c hash.c variables.c functions.c aux.c tree.c stack.c execute.c interface.c program.c -lfl -g -lm
	pdflatex documentacao.tex
	pdflatex documentacao.tex
	
clean:
	rm -rf *~ documentacao.aux documentacao.blg documentacao.bbl documentacao.toc documentacao.out lex.yy.c compiler.tab.c documentacao.log
