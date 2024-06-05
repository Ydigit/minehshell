#include "shell.h"

/**
 * @brief Conta o número de argumentos numa lista de argumentos.
 * 
 * @param args A lista de argumentos.
 * 
 * Esta função percorre a lista de argumentos e conta o número de argumentos até encontrar um NULL.
 * 
 * @return O número de argumentos na lista.
 */
int count_args(char **args) {
    int count = 0; // Inicializa o contador de argumentos
    while(args[count] != NULL) { // Enquanto o argumento atual não for NULL
        count++; // Incrementa o contador de argumentos
    }
    return count; // Retorna o número de argumentos
}




/**
 * @brief Duplica um descritor de ficheiro e fecha o antigo.
 * 
 * @param oldFd O descritor de ficheiro antigo.
 * @param newFd O novo descritor de ficheiro.
 * @param argc O número de argumentos.
 * @param argv A lista de argumentos.
 * 
 * Esta função verifica se o descritor de ficheiro antigo é válido. Se não for, termina o programa.
 * Em seguida, duplica o descritor de ficheiro antigo para o novo descritor de ficheiro e fecha o antigo.
 * Também remove os dois últimos argumentos da lista de argumentos e atualiza o número de argumentos.
 * 
 * @return O número atualizado de argumentos.
 */
int dupAndClose(int oldFd, int newFd, int argc, char **argv){
    if(oldFd < 0){ // Se o descritor de ficheiro antigo não é válido
        exit(1); // Termina o programa
    }
    dup2(oldFd,newFd); // Duplica o descritor de ficheiro
    close(oldFd); // Fecha o descritor de ficheiro antigo
    argv[argc-2] = NULL; // Remove os dois últimos argumentos
    return (argc - 2); // Retorna o número atualizado de argumentos
}




/**
 * @brief Redireciona a entrada/saída com base nos argumentos fornecidos.
 * 
 * @param argc O número de argumentos.
 * @param args A lista de argumentos.
 * 
 * Esta função verifica se o penúltimo argumento é um operador de redirecionamento ("2>", ">", ">>" ou "<").
 * Se for, ela abre ou cria o ficheiro especificado no último argumento e redireciona a saída de erro, a saída padrão ou a entrada padrão para esse ficheiro, conforme especificado pelo operador de redirecionamento.
 * Em seguida, ela remove o operador de redirecionamento e o nome do ficheiro dos argumentos e atualiza o número de argumentos.
 * 
 * @return O número atualizado de argumentos.
 */
int redir(int argc, char **args){
    int fd; // Descritor de ficheiro
    if(argc < 3){ // Se o número de argumentos é menor que 3
        perror("Invalid Arguments"); // Imprime uma mensagem de erro
        exit(1); // Termina o programa
    }

    if(strcmp(args[argc-2],"2>") == 0 ){ // Se o penúltimo argumento é "2>"
        fd = creat(args[argc-1], FILE_MODE); // Cria o ficheiro especificado no último argumento
        argc = dupAndClose(fd,STDERR_FILENO,argc,args); // Redireciona a saída de erro para o ficheiro e atualiza o número de argumentos
    }
    else if(strcmp(args[argc-2],">") == 0 ){ // Se o penúltimo argumento é ">"
        fd = open(args[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE); // Abre o ficheiro especificado no último argumento para escrita, criando-o se não existir e truncando-o se existir
        argc = dupAndClose(fd,STDOUT_FILENO,argc,args); // Redireciona a saída padrão para o ficheiro e atualiza o número de argumentos
    }
    else if (strcmp(args[argc - 2], ">>") == 0){ // Se o penúltimo argumento é ">>"
        fd = open(args[argc - 1], O_WRONLY | O_CREAT | O_APPEND, FILE_MODE); // Abre o ficheiro especificado no último argumento para escrita, criando-o se não existir e anexando-o se existir
        argc = dupAndClose(fd,STDOUT_FILENO,argc,args); // Redireciona a saída padrão para o ficheiro e atualiza o número de argumentos
    }
    else if(strcmp(args[argc - 2], "<") == 0){ // Se o penúltimo argumento é "<"
        fd = open(args[argc - 1], FILE_MODE | O_RDONLY); // Abre o ficheiro especificado no último argumento para leitura
        argc = dupAndClose(fd,STDIN_FILENO,argc,args); // Redireciona a entrada padrão para o ficheiro e atualiza o número de argumentos
    }
    return argc; // Retorna o número atualizado de argumentos
}

