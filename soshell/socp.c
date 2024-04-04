#include "shell.h"



//mudar o kaefile
//o destino no inicioe a source no
void ioCopy(int IN, int OUT)
{
    {
        int n;
        char buf[BUFFSIZE];
        while ((n = read(IN, buf, BUFFSIZE)) > 0)
        {
            if (write(OUT, buf, n) != n)
                perror("Erro de escrita!\n");
        }
        if (n < 0)
            perror("Erro de leitura!\n");
    }
}

void socp(char *dest, char *src){
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
    ioCopy(fdIn,fdOut);
    }

