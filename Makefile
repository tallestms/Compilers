all:
	flex -i trab1.l
	gcc -o trab1 lex.yy.c
	pdflatex trab1
	pdflatex trab1

clean:
	rm -rf trab1.aux trab1.blg trab1.bbl trab1.log trab1.toc trab1.out lex.yy.c
