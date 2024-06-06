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
#include <time.h>
#include <dirent.h>
#include <limits.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <openssl/sha.h>



#define MAX 100
#define BUFFSIZE 1024
#define FILE_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
//atribuicao de definicao apos verificacao de indefinicao
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif



#define NUM_PASSWORDS 10
#define PASSWORD_LENGTH 8

#define NUM_BLOCKS 5


typedef struct
    { char msg[100] ;
    int tempo;} aviso_t;

typedef struct {
    char fonte[100];
    char destino[100];
    //int buffsize;
} copiar_t;

typedef struct {
    int index;
    time_t timestamp;
    char data[256];
    char prev_hash[65];
    char hash[65];
} Block;

typedef struct {
    Block blocks[NUM_BLOCKS];
    int size;
} Blockchain;


int parse(char *buf, char **args);

void execute(int numargs, char **args);

int redirects(int numargs, char *args[]);

int builtin (char **args);

void socp(char *fonte, char *destino) ;

void ioCopy(int IN,int OUT);

bool justsee(int entrada1, int entrada2);

bool compare2txt(char *INONE, char *INTWO);

void calc(char *value1,char *op, char*value2);

void bits(char op1, char *op, char *op2);

int dupAndClose(int oldFd, int newFd, int argc, char **argv);

int redir(int numargs, char *args[]);

int count_args(char **args);

void aviso (char *mesg, int tempo);

void *avisowrapper(void *args);


void socpthread(char *dest, char *src);

void *socpwrapper(void *args);

//void ioCopythread(int IN, int OUT, int buffsize);

void register_copy(const char *fileName);

void list_copies();

void getFileType(const char* filename);
/* constantes que podem tornar uteis*/

int maiortamanho(char* filename1, char* filename2);

void sext(const char* filename);

void removerleitura(const char* filename);

void sols(const char* directory_name);

int isjpg ( int fileDescriptor );





//***************************** */

void add_to_history(const char *command);
void print_history();
void execute_command_from_history(int n);
void process_command(char *command);


void execute_pipe(char **args1, char **args2);

//--------------------music------------------
void gerapassharmonia(const char* file);

void gerapass12(const char *file, const char *password);

void descodificar12(const char *file);

void decode_nota(char *nota, char *notas[]);

//---------------------BLOCKCHAIN-----------------------

void sha256(char* string, char outputBuffer[65]);

void create_block(Block* block, int index, const char* data, const char* prev_hash);

void add_block(Blockchain* blockchain, Block* new_block);

void display_blockchain(Blockchain* blockchain);

void child_process(Blockchain* blockchain, sem_t* sem, int index);

void simulate_blockchain();

#define BG 0
#define FG 1
