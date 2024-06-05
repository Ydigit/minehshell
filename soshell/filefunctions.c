/**
 * @file filefunctions.c
 * @brief A program to perform various operations on files.
 */

#include "shell.h"

/**
 * @brief Compares the sizes of two files.
 * 
 * This function uses the stat() system call to get information about the two files. 
 * It then compares the sizes of the files and prints which file is larger or if they are the same size.
 * 
 * @param filename1 The name of the first file.
 * @param filename2 The name of the second file.
 * @return 0 if successful, 1 if an error occurred.
 */


// A função maiortamanho recebe dois nomes de arquivos como argumentos
int maiortamanho(char* filename1, char* filename2) {
    // Declara duas variáveis do tipo struct stat para armazenar as informações dos arquivos
    struct stat file1_stat, file2_stat;

    // Tenta obter as informações do primeiro arquivo
    if (stat(filename1, &file1_stat) == -1) {
        // Se houver um erro, imprime uma mensagem de erro e retorna 1
        perror("Error getting file1 information");
        return 1;
    }

    // Tenta obter as informações do segundo arquivo
    if (stat(filename2, &file2_stat) == -1) {
        // Se houver um erro, imprime uma mensagem de erro e retorna 1
        perror("Error getting file2 information");
        return 1;
    }

    // Compara os tamanhos dos dois arquivos
    if (file1_stat.st_size > file2_stat.st_size) {
        // Se o primeiro arquivo for maior, imprime uma mensagem indicando isso
        printf("O ficheiro %s e maior que %s\n", filename1, filename2);
        printf("Tamanho: %lld KB\n", (long long)(file1_stat.st_size / 1024)); // passagem para KB
    } else if (file1_stat.st_size < file2_stat.st_size) {
        // Se o segundo arquivo for maior, imprime uma mensagem indicando isso
        printf("To ficheiro %s e maior que %s\n", filename2, filename1);
        printf("Size: %lld KB\n", (long long)(file2_stat.st_size / 1024));
    } else {
        // Se ambos os arquivos tiverem o mesmo tamanho, imprime uma mensagem indicando isso
        printf("Ambos tem o mesmo tamanho\n");
        printf("Tamanho: %lld KB\n", (long long)(file1_stat.st_size / 1024));
    }

    // Retorna 0 para indicar que a função foi executada com sucesso
    return 0;
}

/**
 * @brief Adds execute permission for the user to a file.
 * 
 * This function uses the stat() system call to get the current permissions of the file. 
 * It then uses the chmod() system call to add the execute permission for the user.
 * 
 * @param filename The name of the file.
 */
// A função sext recebe um nome de arquivo como argumento
void sext(const char* filename){
    // Declara uma variável do tipo struct stat para armazenar as informações do arquivo
    struct stat file_stat;

    // Tenta obter as informações do arquivo
    if(stat(filename, &file_stat)==-1){
        // Se houver um erro, imprime uma mensagem de erro e termina o programa
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Cria um novo modo que é o modo atual do arquivo com a permissão de execução do usuário adicionada
    mode_t new_mode = file_stat.st_mode | S_IXUSR;

    // Tenta alterar as permissões do arquivo para o novo modo
    if(chmod(filename, new_mode) == -1){
        // Se houver um erro, imprime uma mensagem de erro e termina o programa
        perror("chmod");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Removes read permission for the group and others from a file.
 * 
 * This function uses the stat() system call to get the current permissions of the file. 
 * It then uses the chmod() system call to remove the read permission for the group and others.
 * 
 * @param filename The name of the file.
 */

// A função removerleitura recebe um nome de arquivo como argumento
void removerleitura(const char* filename){
    // Declara uma variável do tipo struct stat para armazenar as informações do arquivo
    struct stat file_stat;

    // Tenta obter as informações do arquivo
    if(stat(filename, &file_stat)==-1){
        // Se houver um erro, imprime uma mensagem de erro e termina o programa
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Cria um novo modo que é o modo atual do arquivo com as permissões de leitura do grupo e de outros removidas
    mode_t new_mode = file_stat.st_mode & ~(S_IRGRP | S_IROTH);

    // Tenta alterar as permissões do arquivo para o novo modo
    if(chmod(filename, new_mode) == -1){
        // Se houver um erro, imprime uma mensagem de erro e termina o programa
        perror("chmod");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Lists the files in a directory.
 * 
 * This function uses the opendir() and readdir() functions to read the files in a directory. 
 * It then uses the stat() system call to get information about each file. 
 * It prints the name, inode number, size, and modification time of each file.
 * 
 * @param directory_name The name of the directory.
 */
// A função sols recebe um nome de diretório como argumento
void sols(const char* directory_name){
    // Declara um ponteiro para um diretório e uma entrada de diretório
    DIR *dir;
    struct dirent *entry;

    // Tenta abrir o diretório
    dir = opendir(directory_name);
    if(dir == NULL){
        // Se houver um erro, imprime uma mensagem de erro e retorna
        perror("open dir");
        return;
    }

    // Imprime os cabeçalhos da tabela
    printf("%-20s %-10s %-10s %-10s\n", "Name", "Inode", "Size", "Modification Time");
    printf("-----------------------------------------------------------------------\n");

    // Lê cada entrada no diretório
    while((entry = readdir(dir)) != NULL) {
        // Declara uma variável do tipo struct stat para armazenar as informações do arquivo e uma string para o caminho do arquivo
        struct stat file_stat;
        char file_path[PATH_MAX];

        // Constrói o caminho do arquivo
        snprintf(file_path, sizeof(file_path), "%s/%s", directory_name, entry->d_name);
        // Tenta obter as informações do arquivo
        if(stat(file_path, &file_stat)==-1){
            // Se houver um erro, imprime uma mensagem de erro e continua com a próxima entrada
            perror("stat");
            continue;
        }

        // Imprime as propriedades do arquivo
        printf("%-20s %-10lu %-10ld %s", 
        entry->d_name,
        file_stat.st_ino,
        file_stat.st_size,
        ctime(&file_stat.st_mtime));
    }
    // Fecha o diretório
    closedir(dir);
}