/**
 * @file compare2txt.c
 * @brief A program to compare two text files.
 */

#include "shell.h"

/**
 * @brief A function that reads two file descriptors and compares their content.
 * 
 * This function reads from two file descriptors in chunks of BUFFSIZE. If the size of the chunks or the content differs, it returns false.
 * 
 * @param entrada1 The first file descriptor.
 * @param entrada2 The second file descriptor.
 * 
 * @return true if the content of the files is identical, false otherwise.
 */
bool justsee(int entrada1, int entrada2) {
    int n, m;
    char buf[BUFFSIZE], buf2[BUFFSIZE];

    while ((n = read(entrada1, buf, BUFFSIZE)) > 0 && (m = read(entrada2, buf2, BUFFSIZE)) > 0) {
        if (n != m || memcmp(buf, buf2, n) != 0) { //memory byte compare
            return false;
        }
    }

    if (n < 0 || m < 0) {
        perror("Read error");
        return false;
    }

    return true;
}

/**
 * @brief A function that opens two files and compares their content.
 * 
 * This function opens two files and uses the justsee function to compare their content.
 * 
 * @param INONE The path to the first file.
 * @param INTWO The path to the second file.
 * 
 * @return true if the content of the files is identical, false otherwise.
 */
bool compare2txt(char * INONE, char *INTWO){
    int fd1;
    int fd2;
    bool estadof;

    fd1=open(INONE, FILE_MODE);
    fd2=open(INTWO, FILE_MODE);
    
    if(fd1<0){
        perror(INONE);
        return false;
    }
    if(fd2<0){
        perror(INTWO);
        return false;
    }
    estadof=justsee(fd1,fd2);
    if(estadof == true){
        printf("yesir they are a copy\n");
        return true;
    }
    else{
        printf("You are having a laugh..\n");
        return false;
    }
}