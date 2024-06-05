/**
 * @file ficheirosinfo.c
 * @brief A program to get the type of a file.
 */

#include "shell.h"

/**
 * @brief Gets the type of a file.
 * 
 * This function uses the stat() system call to get information about the file. 
 * It then checks the st_mode field of the struct stat to determine the type of the file. 
 * It prints the type of the file to the standard output.
 * 
 * @param filename The name of the file.
 */
// A função getFileType recebe um nome de arquivo como argumento
void getFileType(const char* filename) {
    // Declara uma variável do tipo struct stat para armazenar as informações do arquivo
    struct stat fileStat;

    // Tenta obter as informações do arquivo
    if (stat(filename, &fileStat) == -1) {
        // Se houver um erro, imprime uma mensagem de erro e termina o programa
        perror("Error opening file, or file does not exist\n");
        exit(0);
    }

    // Verifica o tipo do arquivo e imprime uma mensagem apropriada
    if ((fileStat.st_mode & S_IFREG) == S_IFREG) {
        printf("%s: A regular file\n", filename);
    } else if ((fileStat.st_mode & S_IFDIR) == S_IFDIR) {
        printf("%s: A directory\n", filename);
    } else if ((fileStat.st_mode & S_IFCHR) == S_IFCHR) {
        printf("%s: A character device\n", filename);
    } else if ((fileStat.st_mode & S_IFBLK) == S_IFBLK) {
        printf("%s: A block device\n", filename);
    } else if ((fileStat.st_mode & S_IFLNK) == S_IFLNK) {
        printf("%s: A symbolic link\n", filename);
    } else if ((fileStat.st_mode & S_IFSOCK) == S_IFSOCK) {
        printf("%s: A socket\n", filename);
    } else if ((fileStat.st_mode & S_IFIFO) == S_IFIFO) {
        printf("%s: A FIFO/pipe\n", filename);
    } else {
        printf("%s: Unknown type\n", filename);
    }
}
