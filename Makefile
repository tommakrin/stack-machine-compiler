CXX = gcc # use the gcc compiler
SRC = scanner.c parser.c  # project files
TST= main.c #Testbench

#CXXFLAGS = -Wall 
CXXFLAGS = -O3 
CXXDBGSYMS = -g   #GCC Debugging symbols

# Stage rules
#============

parse:
	bison -d parser.y -o parser.c
	./patch

parsedbg:
	bison -d -t parser.y -o parser.c

lex: parser.h
	flex -o scanner.c scanner.lex

# Compiler versions
#==================

all : parse lex			#Rule to create everything
	$(CXX)$(CXXFLAGS)$(SRC)$(TST)

debug: parsedbg lex		#Include debug symbols
	$(CXX)$(CXXFLAGS)$(CXXDBGSYMS)$(SRC)$(TST)

clean : # rule to delete unnecessary files
	rm -f *.o
