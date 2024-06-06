/**
 * @file execute.c
 * @brief A program to create a child process and execute a program.
 */

#include "shell.h"
#include <sys/wait.h>

/**
 * @brief Executes a command with or without pipes and handles background execution.
 *
 * This function processes the given command arguments to determine if the command should
 * run in the background or foreground and checks for the presence of pipes. If a pipe is
 * detected, it splits the arguments into two parts and calls execute_pipe() to handle the
 * pipe execution. If no pipe is found, it proceeds to create a child process using fork().
 * In the child process, it attempts to execute the command using execvp(). If execvp() fails,
 * an error message is printed. The parent process waits for the child process to finish if
 * the command is to run in the foreground. For background execution, it does not wait.
 *
 * @param numargs The number of arguments in the command.
 * @param args The command arguments, including the command itself and its parameters.
 */

int last(int *argc, char **args)
{
  if (args[*argc - 1][0] == '&')
  {
    (*argc)--;
    args[*argc] = NULL;
    return BG;
  }
  return FG;
}

void execute(int numargs, char **args)
{
  int pid, status;
  int code = last(&numargs, args);
  // VERIFICAR PIPES NOS ARGS
  // ls -l | grep "a"
  for (int i = 0; i < numargs; ++i)
  {
    if (strcmp(args[i], "|") == 0)
    {
      args[i] = NULL;
      char **args1 = args;
      char **args2 = &args[i + 1];
      execute_pipe(args1, args2);
      return;
    }
  }

  if ((pid = fork()) < 0)
  {
    perror("forks");
    exit(1);
  }

  if (pid == 0)
  {
    // neste
    numargs = redirects(numargs, args);
    execvp(*args, args);
    perror(*args);
    exit(1);
  }
  if (code == FG)
    while (wait(&status) != pid)
      ;

  return;
}

/**
 * @brief Checks if a file descriptor is valid.
 *
 * This function checks if a file descriptor is valid (i.e., not negative).
 * If the file descriptor is invalid, it prints an error message and exits.
 *
 * @param fd The file descriptor to check.
 */
void checkfd(int fd)
{
  if (fd < 0)
  {
    perror("fd invalido");
    exit(0);
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Trata dos redirecionamentos de entrada e saída em um comando.
 *
 * @param numargs O número de argumentos no comando.
 * @param args Os argumentos do comando.
 *
 * Esta função verifica se o penúltimo argumento do comando é um operador de redirecionamento ("2>", ">", ">>" ou "<").
 * Se for, ela abre ou cria o arquivo especificado no último argumento e redireciona a saída de erro, a saída padrão ou a entrada padrão para esse arquivo, conforme especificado pelo operador de redirecionamento.
 * Em seguida, ela remove o operador de redirecionamento e o nome do arquivo dos argumentos do comando e atualiza o número de argumentos.
 *
 * @return O número atualizado de argumentos no comando.
 */

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

// dup pega o file descirptor mais baixo do sistema
// com o dup2 garanto que  o que quero vai ser o novo file descriptor
//

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
