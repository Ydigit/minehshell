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
LIBS=-lm -lpthread #-lssl -lcrypto   # Adiciona as bibliotecas OpenSSL
OBS=main.o execute.o parse.o socp.o compare2txt.o calc.o calcularbits.o isjpg.o redirect.o threads.o ficheirosinfo.o filefunctions.o music.o historic.o pipe.o #blockchain.o

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
calcularbits.o : shell.h calcularbits.c
	$(CC) $(FLAGS) calcularbits.c
redirect.o : shell.h redirect.c
	$(CC) $(FLAGS) redirect.c
threads.o : shell.h threads.c
	$(CC) $(FLAGS) threads.c
ficheirosinfo.o : shell.h ficheirosinfo.c
	$(CC) $(FLAGS) ficheirosinfo.c
filefunctions.o : shell.h filefunctions.c
	$(CC) $(FLAGS) filefunctions.c
music.o : shell.h music.c
	$(CC) $(FLAGS) music.c
isjpeg.o : shell.h isjpg.c
	$(CC) $(FLAGS) isjpeg.c
historic.o : shell.h historic.c
	$(CC) $(FLAGS) historic.c
pipe.o : shell.h pipe.c
	$(CC) $(FLAGS) pipe.c
#blockchain.o : shell.h blockchain.c
#	$(CC) $(FLAGS) blockchain.c -lm -lssl -lcrypto




clean limpar:
	rm -f soshell *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e limpeza de tralha"
