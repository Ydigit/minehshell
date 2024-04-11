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
#include <stdbool.h>
#include <math.h>
#define BUFFSIZE 128
#define FILE_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


void parse(char *buf, char **args);

void execute(char **args);

int builtin (char **args);

void socp(char *fonte, char *destino) ;

void ioCopy(int IN,int OUT);

bool justsee(int entrada1, int entrada2);

bool compare2txt(char *INONE, char *INTWO);


/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1
