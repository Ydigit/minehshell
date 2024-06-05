#include "shell.h"

//mudar o kaefile
//o destino no inicioe a source no

/* IN case of buffspec is neededd!
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
*/



/*.---------------------------.--------------------------.--------------------------.-------------------------.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.*/
/**
 * @brief Copia dados de um descritor de ficheiro para outro.
 * 
 * @param IN O descritor de ficheiro de entrada.
 * @param OUT O descritor de ficheiro de saída.
 * 
 * Esta função lê dados do descritor de ficheiro de entrada e escreve-os no descritor de ficheiro de saída.
 * Ela continua a ler e escrever até que não haja mais dados para ler.
 * Se ocorrer um erro de escrita ou leitura, ela imprime uma mensagem de erro.
 */
void ioCopy(int IN, int OUT)
{
    int n; // Número de bytes lidos
    char buf[BUFFSIZE]; // Buffer para armazenar os dados lidos
    while ((n = read(IN, buf, BUFFSIZE)) > 0) // Enquanto houver dados para ler
    {
        if (write(OUT, buf, n) != n) // Se ocorrer um erro de escrita
            perror("Erro de escrita!\n"); // Imprime uma mensagem de erro
    }
    if (n < 0) // Se ocorrer um erro de leitura
        perror("Erro de leitura!\n"); // Imprime uma mensagem de erro
}



/**
 * @brief Copia o conteúdo de um ficheiro para outro.
 * 
 * @param dest O nome do ficheiro de destino.
 * @param src O nome do ficheiro de origem.
 * 
 * Esta função abre o ficheiro de origem para leitura e cria o ficheiro de destino para escrita.
 * Se não conseguir abrir o ficheiro de origem ou criar o ficheiro de destino, ela imprime uma mensagem de erro e retorna.
 * Em seguida, ela copia os dados do ficheiro de origem para o ficheiro de destino usando a função ioCopy.
 */
void socp(char *dest, char *src){ // A chamada será diferente
    int fdIn, fdOut; // Descritores de ficheiro para o ficheiro de origem e o ficheiro de destino

    fdIn=open(src, FILE_MODE); // Abre o ficheiro de origem para leitura
    if(fdIn<0){ // Se não conseguiu abrir o ficheiro de origem
        perror(src); // Imprime uma mensagem de erro
        return; // Retorna
    }
    fdOut = creat(dest, FILE_MODE); // Cria o ficheiro de destino para escrita
    if(fdOut < 0){ // Se não conseguiu criar o ficheiro de destino
        perror(dest); // Imprime uma mensagem de erro
        return; // Retorna
    }
    ioCopy(fdIn,fdOut); // Copia os dados do ficheiro de origem para o ficheiro de destino
}