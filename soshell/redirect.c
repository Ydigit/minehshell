#include "shell.h"

int dupAndClose(int oldFd, int newFd, int argc, char **argv){
    if(oldFd < 0){
        exit(1);
    }
    dup2(oldFd,newFd);
    close(oldFd);
    argv[argc-2] = NULL;
    return (argc - 2);
}

int redir(int argc, char **args){
    int fd;
    if(argc < 3){
        perror("Invalid Arguments");
        exit(1);
    }

    if(strcmp(args[argc-2],"2>") == 0 ){
        fd = creat(args[argc-1], FILE_MODE);
        argc = dupAndClose(fd,STDERR_FILENO,argc,args);
        //apartir daqui ele so me da dupe fecha e da o return do -2
    }
    else if(strcmp(args[argc-2],">") == 0 ){
        fd = open(args[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
        argc = dupAndClose(fd,STDOUT_FILENO,argc,args);
    }
    else if (strcmp(args[argc - 2], ">>") == 0){
        fd = open(args[argc - 1], O_WRONLY | O_CREAT | O_APPEND, FILE_MODE);
        argc = dupAndClose(fd,STDOUT_FILENO,argc,args);
    }
    else if(strcmp(args[argc - 2], "<") == 0){
        fd = open(args[argc - 1], FILE_MODE | O_RDONLY);
        argc = dupAndClose(fd,STDIN_FILENO,argc,args);
    }
    return argc;
}

