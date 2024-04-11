#include "shell.h"


bool justsee(int entrada1, int entrada2) {
    int n, m;
    char buf[BUFFSIZE], buf2[BUFFSIZE];

    while ((n = read(entrada1, buf, BUFFSIZE)) > 0 && (m = read(entrada2, buf2, BUFFSIZE)) > 0) {
        if (n != m || memcmp(buf, buf2, n) != 0) {
            return false;
        }
    }

    if (n < 0 || m < 0) {
        perror("Read error");
        return false;
    }

    return true;
}

 bool compare2txt(char * INONE, char *INTWO){//devo ter 
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