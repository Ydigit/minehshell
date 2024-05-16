#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/wait.h>
#include <stdbool.h>//mudar isto
#include <math.h>
#include <pthread.h>


#define BUFFSIZE 128
#define FILE_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin (char **args);

void socp(char *fonte, char *destino) ;

void ioCopy(int IN,int OUT);

bool justsee(int entrada1, int entrada2);

bool compare2txt(char *INONE, char *INTWO);

void calc(char *value1,char *op, char*value2);

int dupAndClose(int oldFd, int newFd, int argc, char **argv);

int redir(int numargs, char *args[]);

void aviso (char *mesg, int tempo);

void *avisowrapper(void *args);


/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1
