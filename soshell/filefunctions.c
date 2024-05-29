#include "shell.h"


int maiortamanho(char* filename1, char* filename2) {

    struct stat file1_stat, file2_stat;


    if (stat(filename1, &file1_stat) == -1) {
        perror("Error getting file1 information");
        return 1;
    }

    if (stat(filename2, &file2_stat) == -1) {
        perror("Error getting file2 information");
        return 1;
    }

    if (file1_stat.st_size > file2_stat.st_size) {
        printf("O ficheiro %s e maior que %s\n", filename1, filename2);
        printf("Tamanho: %lld KB\n", (long long)(file1_stat.st_size / 1024)); // passagem para KB
    } else if (file1_stat.st_size < file2_stat.st_size) {
        printf("To ficheiro %s e maior que %s\n", filename2, filename1);
        printf("Size: %lld KB\n", (long long)(file2_stat.st_size / 1024));
    } else {
        printf("Ambos tem o mesmo tamanho\n");
        printf("Tamanho: %lld KB\n", (long long)(file1_stat.st_size / 1024));
    }

    return 0;
}


void sext(const char* filename){
    struct stat file_stat;

    if(stat(filename, &file_stat)==-1){
        perror("stat");
        exit(EXIT_FAILURE);
    }

    mode_t new_mode = file_stat.st_mode | S_IXUSR;

    if(chmod(filename, new_mode) == -1){
        perror("chmod");
        exit(EXIT_FAILURE);
    }
}

void removerleitura(const char* filename){
    struct stat file_stat;

    if(stat(filename, &file_stat)==-1){
        perror("stat");
        exit(EXIT_FAILURE);
    }

    mode_t new_mode = file_stat.st_mode & ~(S_IRGRP | S_IROTH);

    if(chmod(filename, new_mode) == -1){
        perror("chmod");
        exit(EXIT_FAILURE);
    }
}



void sols(const char* directory_name){
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory_name);
    if(dir == NULL){
        perror("open dir");
        return;
    }

    printf("%-20s %-10s %-10s %-10s\n", "Name", "Inode", "Size", "Modification Time");
    printf("-----------------------------------------------------------------------\n");

    while((entry = readdir(dir)) != NULL) {
        struct stat file_stat;
        char file_path[PATH_MAX];

        snprintf(file_path, sizeof(file_path), "%s/%s", directory_name, entry->d_name);
        if(stat(file_path, &file_stat)==-1){
            perror("stat");
            continue;
        }

        printf("%-20s %-10lu %-10ld %s", 
        entry->d_name,
        file_stat.st_ino,
        file_stat.st_size,
        ctime(&file_stat.st_mtime));
    }
    closedir(dir);
}