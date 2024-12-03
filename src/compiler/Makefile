.PHONY = all clean cleanall

all: compiler.tab.cpp compiler.l.c
	g++ -std=c++2a -g -o kompilator frontend/compiler.tab.cpp frontend/compiler.l.c intermediate/*.cpp backend/*.cpp compiler.cpp

compiler.tab.cpp: frontend/parser.y
	bison -d -o frontend/compiler.tab.cpp frontend/parser.y

compiler.l.c: frontend/lexer.l
	flex -o frontend/compiler.l.c frontend/lexer.l

clean:
	rm -f */*.tab.h* */*.tab.c* */*.l.c*

cleanall: clean
	rm -f compiler