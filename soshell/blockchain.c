/**
 * @file blockchain.c
 * @brief Implementação de uma simulação de blockchain utilizando processos e memória compartilhada.
 */

#include "shell.h"  // Inclui os cabeçalhos necessários

#include <openssl/sha.h>  // Inclui a biblioteca OpenSSL para cálculo de hash SHA-256

/**
 * @brief Calcula o hash SHA-256 para uma string de entrada.
 * 
 * @param string A string de entrada para calcular o hash.
 * @param outputBuffer O buffer de saída para armazenar o hash calculado.
 */
void sha256(char* string, char outputBuffer[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256); // Inicialização do contexto
    SHA256_Update(&sha256, string, strlen(string)); // Atualização com os dados
    SHA256_Final(hash, &sha256); // Finalização e obtenção do hash

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]); // Conversão para hexadecimal
    }
    outputBuffer[64] = 0; // Terminação da string
}

/**
 * @brief Cria um novo bloco na blockchain.
 * 
 * @param block Ponteiro para o bloco a ser criado.
 * @param index O índice do bloco na blockchain.
 * @param data Os dados a serem armazenados no bloco.
 * @param prev_hash O hash do bloco anterior.
 */
void create_block(Block* block, int index, const char* data, const char* prev_hash) {
    block->index = index;
    block->timestamp = time(NULL);//tempo atual
    strcpy(block->data, data);
    strcpy(block->prev_hash, prev_hash);

    char block_string[1024];
    sprintf(block_string, "%d%ld%s%s", block->index, block->timestamp, block->data, block->prev_hash);
    sha256(block_string, block->hash);//calcula a hash consoante a string que recebe, aquie ele tem uma sequencia de bytes que, por isso uso o Sprintf, e meto la na string 
    //de proprio bloco ele recebe a string com index,tiemstamp, data, prev_hash.->representacao hexadeciaml da string tam de 256 bits, ou seja 64 bytes

}

/**
 * @brief Adiciona um novo bloco à blockchain.
 * 
 * @param blockchain Ponteiro para a blockchain.
 * @param new_block Ponteiro para o novo bloco a ser adicionado.
 */
void add_block(Blockchain* blockchain, Block* new_block) {
    if (blockchain->size < NUM_BLOCKS) {
        blockchain->blocks[blockchain->size++] = *new_block;
    }
}

/**
 * @brief Exibe os blocos da blockchain.
 * 
 * @param blockchain Ponteiro para a blockchain.
 */
void display_blockchain(Blockchain* blockchain) {
    for (int i = 0; i < blockchain->size; i++) {
        Block* block = &blockchain->blocks[i];
        printf("Index: %d\n", block->index);
        printf("Timestamp: %ld\n", block->timestamp);
        printf("Data: %s\n", block->data);
        printf("Previous Hash: %s\n", block->prev_hash);
        printf("Hash: %s\n", block->hash);
        printf("\n");
    }
}

/**
 * @brief Processo filho para adicionar blocos à blockchain.
 * 
 * @param blockchain Ponteiro para a blockchain.
 * @param sem Ponteiro para o semáforo.
 * @param index O índice do bloco a ser adicionado.
 */
void child_process(Blockchain* blockchain, sem_t* sem, int index) {
    char data[256];
    sprintf(data, "Block #%d data", index);

    sem_wait(sem);

    char* prev_hash = (index == 0) ? "0" : blockchain->blocks[index - 1].hash;
    Block new_block;
    create_block(&new_block, index, data, prev_hash);
    add_block(blockchain, &new_block);

    sem_post(sem);

    exit(0);
}

/**
 * @brief Simula a blockchain usando processos e memória compartilhada.
 */
void simulate_blockchain() {
    // Criação da memória compartilhada para a blockchain
    int fd = shm_open("/blockchain_shm", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(fd, sizeof(Blockchain)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    Blockchain* blockchain = mmap(NULL, sizeof(Blockchain), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (blockchain == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    blockchain->size = 0;

    // Criação do semáforo para sincronização
    sem_t* sem = sem_open("/blockchain_sem", O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Criação dos processos filhos para adicionar blocos à blockchain
    for (int i = 0; i < NUM_BLOCKS; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            child_process(blockchain, sem, i);
        }
    }

    // Espera pelos processos filhos
    for (int i = 0; i < NUM_BLOCKS; ++i) {
        wait(NULL);
    }

    // Exibe a blockchain
    display_blockchain(blockchain);

    // Libera os recursos alocados
    munmap(blockchain, sizeof(Blockchain));
    shm_unlink("/blockchain_shm");
    sem_close(sem);
    sem_unlink("/blockchain_sem");
}
