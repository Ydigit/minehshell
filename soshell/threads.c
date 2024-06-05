#include "shell.h" // Inclui o cabeçalho "shell.h"

char strings[MAX][130]; // Declara um array de strings para armazenar as cópias de arquivos registradas
int k = 0; // Declara um contador para o array de strings
pthread_mutex_t fecho; // Declara um mutex para sincronizar o acesso ao array de strings



/**
 * @brief Função que copia o conteúdo de um arquivo para outro.
 * @param dest O nome do arquivo de destino.
 * @param src O nome do arquivo de origem.
 */
void socpthread(char *dest, char *src)
{
    int fdIn, fdOut; // Declara os descritores de arquivo para os arquivos de origem e destino

    fdIn = open(src, FILE_MODE); // Abre o arquivo de origem
    if (fdIn < 0) // Se a abertura falhar, imprime uma mensagem de erro e retorna
    {
        perror(src);
        return;
    }
    fdOut = creat(dest, FILE_MODE); // Cria o arquivo de destino
    if (fdOut < 0) // Se a criação falhar, imprime uma mensagem de erro e retorna
    {
        perror(dest);
        return;
    }
    ioCopy(fdIn, fdOut); // Copia o conteúdo do arquivo de origem para o arquivo de destino
    register_copy(dest); // Registra a cópia do arquivo, com a matriz de strings
}



/**
 * @brief Função que exibe uma mensagem após um certo período de tempo.
 * @param mesg A mensagem a ser exibida.
 * @param tempo O tempo de espera em segundos.
 */
void aviso(char *mesg, int tempo)
{
    while (tempo > 0) // Enquanto o tempo não tiver esgotado
    {
        sleep(1); // Dorme por 1 segundo
        tempo--; // Decrementa o tempo
    }
    fprintf(stderr, "Aviso : %s\n", mesg); // Imprime a mensagem
}




/**
 * @brief Função wrapper para a função aviso que permite que ela seja usada como uma função de thread.
 * @param args Um ponteiro para uma estrutura aviso_t que contém a mensagem e o tempo.
 * @return NULL
 */
void *avisowrapper(void *args)
{
    aviso_t *ptr = (aviso_t *)args; // Converte o argumento para o tipo aviso_t
    aviso(ptr->msg, ptr->tempo); // Chama a função aviso
    free(ptr); // Libera a memória alocada para a estrutura
    return NULL; // Retorna NULL
}




/**
 * @brief Função wrapper para a função socpthread que permite que ela seja usada como uma função de thread.
 * @param args Um ponteiro para uma estrutura copiar_t que contém os nomes dos arquivos de origem e destino.
 * @return NULL
 */
void *socpwrapper(void *args)
{
    copiar_t *ptr = (copiar_t *)args; // Converte o argumento para o tipo copiar_t, fica igual que antes do cast para o phtread create
    socpthread(ptr->fonte, ptr->destino); // Chama a função socpthread, so invoca o IoCopy normal
    free(ptr); // Libera a memória alocada para a estrutura
    return NULL; // Retorna NULL
}





/**
 * @brief Função que registra uma cópia de arquivo.
 * @param fileName O nome do arquivo que foi copiado.
 */
void register_copy(const char *fileName)
{
    time_t mytime; // Declara uma variável para armazenar a hora atual
    time(&mytime); // Obtém a hora atual
    char *t = ctime(&mytime); // Converte a hora atual para uma string
    if ('\n' == t[strlen(t) - 1]) // Se a string termina com um caractere de nova linha
        t[strlen(t) - 1] = '\0'; // Substitui o caractere de nova linha por um caractere nulo

    pthread_mutex_lock(&fecho); // Bloqueia o mutex
    sprintf(strings[k], "%s %s", t, fileName); // Formata a string e a armazena no array de strings, Guarda  array para fazer a lista de copias, guarda por linha
    k++; // Incrementa o contador para escrever no array de strings
    pthread_mutex_unlock(&fecho); // Desbloqueia o mutex
}



/**
 * @brief Função que lista todas as cópias de arquivos registradas.
 */
void list_copies()
{
    for (int i = 0; i < MAX; i++) // Para cada string no array de strings
    {
        if (strings[i][0] != '\0') // Se a string não está vazia, vazia comeca com \0 apos substiuicaono primeiro elmento
        {
            printf("%s\n", strings[i]); // Imprime a string por linha
        }
    }
}