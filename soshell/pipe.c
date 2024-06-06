#include "shell.h"

//ls -l | grep "a"

void execute_pipe(char **args1, char **args2) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {  // Child 1
        close(pipefd[0]);  
        dup2(pipefd[1], STDOUT_FILENO);  
        close(pipefd[1]); 

        if (execvp(args1[0], args1) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {  // Child 2
        close(pipefd[1]);  
        dup2(pipefd[0], STDIN_FILENO);  
        close(pipefd[0]);  

        if (execvp(args2[0], args2) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }


    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);  
    waitpid(pid2, NULL, 0); 
}
