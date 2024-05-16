/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"
#include <sys/wait.h>

void execute(int numargs, char **args)
{
  int pid, status;

  if ((pid = fork()) < 0)
  {                  /* cria um processo progenito */
    perror("forks"); /* NOTE: perror() produz uma pequema mensagem de erro para o stream */
    exit(1);         /* estandardizado de erros que descreve o ultimo erro encontrado */
                     /* durante uma chamada ao sistema ou funcao duma biblioteca */
  }

  if (pid == 0)
  {
    //numargs = redir(numargs, args);
    //if(numargs<-1)
      //exit(1);

    execvp(*args, args); /* NOTE: as versoes execv() e
                          * execvp() de execl() sao uteis quando */
    perror(*args);       /* o numero de argumentos nao e. conhecido.
                          * Os argumentos de  */
    exit(1);             /* execv() e execvp() sao o nome do ficheiro
                          * a ser executado e um */
  }                      /* vector de strings que contem os
                          * argumentos. O ultimo argument */

  while (wait(&status) != pid)
    /*spin fazer nada */;

  return;
}

void checkfd(int fd)
{
  if (fd < 0)
  {
    perror("fd invalido");
    exit(0);
  }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//em caso de execute
/*
int redirects(int numargs, char *args[])
{

  // i tratar do redirect do 2>
  if (numargs < 3)
    return numargs; // Guard the following section
  else if (strcmp(args[numargs - 2], "2>") == 0)
  {
    int fd = creat(args[numargs - 1], FILE_MODE);
    if (fd < 0)
    {
      perror(NULL);
      exit(1);
    }
    dup2(fd, STDERR_FILENO);
    close(fd);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;

    return numargs;
  }
  else if (strcmp(args[numargs - 2], ">") == 0)
  {
    int fd = creat(args[numargs - 1], FILE_MODE); // create way out
    dup2(fd, STDOUT_FILENO);                      // espeta la
    close(fd);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
  }
  else if (strcmp(args[numargs - 2], ">>") == 0)
  {
    int fd = open(args[numargs - 1], O_CREAT | O_APPEND | O_WRONLY, FILE_MODE); // modo com permissoes
    dup2(fd, STDOUT_FILENO);                                                    // Redirect stdout to the file
    close(fd);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
  }
  else if (strcmp(args[numargs - 2], "<") == 0)
  {
    int fd = open(args[numargs - 1], O_RDONLY); // le do ultimo
    dup2(fd, STDIN_FILENO);                     // pega no stdin do lido  em fd
    close(fd);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
  }

  return numargs;
}
*/

// dup pega o file descirptor mais baixo do sistema
// com o dup2 garanto que  o que quero vai ser o novo file descriptor
//

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
