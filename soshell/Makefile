#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=main.o execute.o parse.o socp.o compare2txt.o calc.o redirect.o threads.o



#Alvo por defeito é o primeiro
all :  soshell

main.o : shell.h main.c
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
soshell : $(OBS)
	$(CC)  -o soshell  $(OBS) $(LIBS)
socp.o : shell.h socp.c
	$(CC) $(FLAGS) socp.c
compare2txt.o : shell.h compare2txt.c
	$(CC) $(FLAGS) compare2txt.c
calc.o : shell.h calc.c
	$(CC) $(FLAGS) calc.c
redirect.o : shell.h redirect.c
	$(CC) $(FLAGS) redirect.c
threads.o : shell.h threads.c
	$(CC) $(FLAGS) threads.c
clean limpar:
	rm -f soshell *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"
