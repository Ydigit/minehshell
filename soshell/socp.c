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
            if (write(OUT, buf, n) != n) //escreve ate escrever todos os chars
                perror("Erro de escrita!\n");
        }
        if (n < 0)
            perror("Erro de leitura!\n");
    }
}

void socp(char *dest, char *src){
    int fdIn, fdOut;

    fdIn=open(src, FILE_MODE); //abre o ficheiro
    if(fdIn<0){ //se nao abre erro de abertura
        perror(src);
        return;
    }
    fdOut = creat(dest, FILE_MODE); //cria o ficherio
    if(fdOut < 0){ //fd ser a descricao
        perror(dest);//erro destino nao criado
        return;
    }
    ioCopy(fdIn,fdOut); //ja criada e aberta a origem
    }

