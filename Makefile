all: clean
	flex scanner.flex
	bison -d parser.ypp
	g++ -std=gnu++0x -o hw3 *.c *.cpp
clean:
	rm -f lex.yy.c
	rm -f parser.tab.*pp
	rm -f hw3
