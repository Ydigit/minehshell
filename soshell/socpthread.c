
/*
#include "shell.h"

void ioCopythread(int IN, int OUT, int buffsize)
{
    int n;
    char buf[buffsize];
    while ((n = read(IN, buf, buffsize)) > 0)
    {
        if (write(OUT, buf, n) != n)
            perror("Erro de escrita!\n");
    }
    if (n < 0)
        perror("Erro de leitura!\n");
}

void socpthread(char *dest, char *src, int buffsize){
    int fdIn, fdOut;

    fdIn=open(src, FILE_MODE);
    if(fdIn<0){
        perror(src);
        return;
    }
    fdOut = creat(dest, FILE_MODE);
    if(fdOut < 0){
        perror(dest);
        return;
    }
    ioCopythread(fdIn,fdOut, buffsize);
}
*/