#include "shell.h"

char strings[MAX][130];
int k = 0;
pthread_mutex_t fecho;

void socpthread(char *dest, char *src)
{
    int fdIn, fdOut;

    fdIn = open(src, FILE_MODE);
    if (fdIn < 0)
    {
        perror(src);
        return;
    }
    fdOut = creat(dest, FILE_MODE);
    if (fdOut < 0)
    {
        perror(dest);
        return;
    }
    ioCopy(fdIn, fdOut);
    //ioCopythread(fdIn, fdOut, buffsize);
    register_copy(dest);
}

void aviso(char *mesg, int tempo)
{
    while (tempo > 0)
    {
        sleep(1);
        tempo--;
    }
    fprintf(stderr, "Aviso : %s\n", mesg);
}

void *avisowrapper(void *args)
{
    aviso_t *ptr = (aviso_t *)args;
    aviso(ptr->msg, ptr->tempo);
    free(ptr);
    return NULL;
}

void *socpwrapper(void *args)
{
    copiar_t *ptr = (copiar_t *)args;
    socpthread(ptr->fonte, ptr->destino);
    free(ptr);
    return NULL;
}


void register_copy(const char *fileName)
{
    time_t mytime;
    time(&mytime);
    char *t = ctime(&mytime);
    if ('\n' == t[strlen(t) - 1])
        t[strlen(t) - 1] = '\0';

    pthread_mutex_lock(&fecho); // fechamento
    sprintf(strings[k], "%s %s", t, fileName);
    k++;
    pthread_mutex_unlock(&fecho); // abertura
}



void list_copies()
{
    for (int i = 0; i < MAX; i++)
    {
        if (strings[i][0] != '\0')
        { // Only print non-empty strings
            printf("%s\n", strings[i]);
        }
    }
}