#include "shell.h"

char prompt[100];

// char strings[MAX][5];
// int k = 0;
// pthread_mutex_t fecho;

int main()
{
  int len;
  char linha[1024]; /* um comando */
  char *args[64];   /* com um maximo de 64 argumentos */

  /****SHELNAME*****/

//adicionar coisa em rust
  strcpy(prompt, "SHELL do LEO: Espeta ai um comando : $>");
  while (1)
  {
    printf("%s", prompt);
    if (fgets(linha, 1023, stdin) == NULL)
    {
      printf("\n");
      exit(0);
    }
    len = strlen(linha);
    if (1 == len)
      continue; /* linha é apenas \n */
    if (linha[len - 1] == '\n')
      //linha[len - 1] = '\0';
      if (linha[len - 1] == '\n') linha[len - 1] = '\0';
        add_to_history(linha);


    int numargs = parse(linha, args); /* particiona a string em argumentos */

    if (!builtin(args))
      execute(numargs, args); /* executa o comando */
  } // execucao continua
  return 0;
}

/**************
 * BULD In  ***
 *************/

/**
 * @brief Executes built-in shell commands.
 *
 * This function handles built-in shell commands such as "sair", "42", "devgit", "obterinfo", "identificacaopessoal", and more..
 * For "cd", it handles changing to the home directory, previous directory, and a specified directory.
 *
 * @param args Null-terminated array of arguments. args[0] is the command, args[1] onwards are parameters to the command.
 * @return int Always returns 1 to continue execution.
 */

int builtin(char **args)
{
  // int argc=count_args(args);
  /* Toda a funcionalidade embutida deverá devolver 1*/
  // get out
  if (strcmp(args[0], "sair") == 0)
  {
    exit(0);
    return 1; /* funcionalidade embutida */
  }
  // 42 resposta
  if (strncmp(args[0], "42", 2) == 0)
  {
    printf("42 is the answer to life the universe and everything\n");
    printf("...\n");
    return 1; /* funcionalidade embutida */
  }

  if (strncmp(args[0], "devgit", 6) == 0)
  {
    printf("Check more on \n");
    printf("****************************\n");
    printf("* https://github.com/Ydigit*\n");
    printf("****************************\n");
    return 1; /* funcionalidade embutida */
  }

  if (0 == strcmp(args[0], "obterinfo"))
  {
    printf("SoShell 2024 versão 1.0\n");
    return 1; // comando embutido
  }

  //*******PERSONALIDE*******
  if (0 == strcmp(args[0], "identificacaopessoal"))
  {
    system("id");
    return 1; // comando embutido
  }

  if (0 == strcmp(args[0], "cd"))
  {
    int err;
    static char guardadir[255] = ""; // static para que mantenha o seu valor entre chamadas de função
    char currentdir[255];

    getcwd(currentdir, sizeof(currentdir)); // obter o diretório atual

    if (args[1] == NULL || strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME") == 0)
    {
      strcpy(guardadir, currentdir); // copiar currentdir para guardadir
      err = chdir(getenv("HOME"));   // mudar para o diretório home
    }
    else if (strcmp(args[1], "-") == 0)
    {
      if (guardadir[0] != '\0') // se guardadir não estiver vazio
      {
        err = chdir(guardadir);        // mudar para o diretório em guardadir
        strcpy(guardadir, currentdir); // copiar currentdir para guardadir
      }
      else
      { // nao tem elementos de reserva, esta empty
        fprintf(stderr, "cd: OLDPWD not defined well\n");
        return 1;
      }
    }
    else
    {                                // cd normal
      strcpy(guardadir, currentdir); // copiar currentdir para guardadir
      err = chdir(args[1]);          // mudar para o diretório especificado por args[1]
    }

    if (err < 0)
      perror(args[1]); // imprimir mensagem de erro se chdir falhou
    return 1;          // retornar 1 para indicar que um comando interno foi executado
  }

  // ****username******
  if (strlen(args[0]) > 4 && strlen(args[0]) < 102 && 0 == strncmp(args[0], "PS1=", 4))
  { // max 102 porcausa dos 98 * os 4
    strcpy(prompt, args[0] + 4);
    prompt[strlen(args[0] + 4)] = ' ';
    prompt[strlen(args[0] + 4) + 1] = '\0';
    return 1; // comando embutido
  }

  // **** cópia com o socp ****
  if (0 == strcmp(args[0], "socp"))
  {
    // Se não forem fornecidos dois argumentos, imprime uma mensagem de uso
    if (args[1] == NULL || args[2] == NULL)
    {
      printf("uso-> socp entrada saida\n");
      // Exemplo de uso: socp origem.txt destino.txt
      // Neste exemplo, o conteúdo do ficheiro "origem.txt" será copiado para o ficheiro "destino.txt".
    }
    else
    {
      // Chama a função socp com o segundo argumento como destino e o primeiro como origem
      socp(args[2], args[1]);
      // Exemplo de uso: socp origem.txt destino.txt
      // Neste exemplo, o conteúdo do ficheiro "origem.txt" será copiado para o ficheiro "destino.txt".
    }
    return 1; // comando embutido
  }

  // *******verifica se é igual******
  // Exemplo de uso: compare2txt file1.txt file2.txt
  // Neste exemplo, o conteúdo dos ficheiros "file1.txt" e "file2.txt" será comparado.

  if (0 == strcmp(args[0], "compare2txt"))
  {
    if (args[1] == NULL || args[2] == NULL)
    {
      perror("no files no equals..\n"); // saida erro
      exit(0);
    }
    else
    {
      compare2txt(args[1], args[2]); // chamada funcao
    }
    return 1; // embutido
  }

  /*
    *****chamadas de I/O flux na main, mas neste momento as minha estao a ser chamadas no execute.c********

  if( 0==strcmp(args[1], ">") ){

        redir(argc - 1,args);
        return 1;
      }
      if( 0==strcmp(args[1], ">>") ){
        redir(argc - 1,args);
        return 1;
      }

      if( 0==strcmp(args[1], "2>") ){
        redir((argc) - 1,args);
        return 1;
      }
      if( 0==strcmp(args[1], "<") ){
        redir(argc - 1,args);
        return 1;
      }
  */

  // calc
  /*
    int i=1;// indice de array
    int conta=0;
    while(args[i]!=NULL){
      i++;
      conta++;
    }

    if ( 0 == strcmp(args[0], "calc") && conta==3) {
        calc(args[1],args[2],args[3]);
        return 1 ;
    }
      else{
        printf("\n!!!!usage type error != -> <calc><value1> <operando> <value2>!!!!\n\n");
      return 1;
      }
    */

  // *****calcula*****
  /*
   */
  int i = 0;
  // Este loop percorre a lista de argumentos até encontrar um NULL, que indica o fim da lista
  while (args[i] != NULL)
  {
    i++;
  }
  // Se o primeiro argumento for "calc" e o número total de argumentos for 3 (incluindo o comando "calc")
  if (0 == strcmp(args[0], "calc") && i == 4) // 0->1->2(args)
  {
    // A função calc é chamada com os três argumentos
    calc(args[1], args[2], args[3]);
    return 1; // Indica que um comando embutido foi executado
  }

  if (0 == strcmp(args[0], "calcularbits") && i == 4) // 0->1->2(args)
  {
    // A função calcularbits é chamada com os três argumentos
    bits(args[1][0], args[2], args[3]);
    return 1; // Indica que um comando embutido foi executado
  }

  // aviso
  // obj sera passar o meu argumento de args para cada thread para cada funcao

  /*if (strcmp (args[0], "aviso")==0 ) {
    pthread_t onlythread;
    //primeira execucao com thread, e segunda sem thread
    pthread_create(&onlythread, NULL, avisowrapper, (void *)args);
    //aviso( args[1], atoi ( args[2] ) ) ;
    return 1;
  }
  */

  //***AVISO***
  // Exemplo de uso: aviso "Hora do almoço" 3600
  // Neste exemplo, a função aviso será chamada com os argumentos "Hora do almoço" e "3600".
  // Uma mensagem "Hora do almoço" será exibida após 3600 segundos (1 hora).

  if (strcmp(args[0], "aviso") == 0)
  {
    // Cria uma variável para armazenar o ID da thread
    pthread_t th;
    // Aloca memória para uma estrutura aviso_t
    aviso_t *ptr = (aviso_t *)malloc(sizeof(aviso_t));
    // Copia a mensagem do segundo argumento para a estrutura
    strcpy(ptr->msg, args[1]);
    // Converte o terceiro argumento para um inteiro e armazena-o na estrutura
    ptr->tempo = atoi(args[2]);
    // Cria uma nova thread que executa a função avisowrapper com a estrutura como argumento
    pthread_create(&th, NULL, avisowrapper, (void *)ptr);
    return 1; // Indica que um comando embutido foi executado
  }

  // ****SOCTTHREAD****
  // o uso de structs e importante para a
  // Verifica se o primeiro argumento é igual a "socpthread"
  if (0 == strcmp(args[0], "socpthread"))
  {
    // Se o segundo ou terceiro argumento for NULL, imprime uma mensagem de uso
    if (args[1] == NULL || args[2] == NULL)
    {
      printf("uso-> socp entrada -> saida\n");
    }
    else
    {
      pthread_t th;                                         // Declara uma variável para armazenar o ID da thread
      copiar_t *ptr = (copiar_t *)malloc(sizeof(copiar_t)); // Aloca memória para uma estrutura copiar_t
      strcpy(ptr->fonte, args[1]);                          // Copia o segundo argumento para o campo fonte da estrutura
      strcpy(ptr->destino, args[2]);                        // Copia o terceiro argumento para o campo destino da estrutura

      // Cria uma nova thread que executa a função socpwrapper com a estrutura como argumento + cast
      pthread_create(&th, NULL, socpwrapper, (void *)ptr); // Struct para passar os argumentos que preciso para 1 unica thread
      pthread_detach(th);                                  // Desanexa a thread para que seus recursos sejam automaticamente liberados quando ela terminar//termian auitomatico quandoa caba a sua execucaon exito join

      socp(args[2], args[1]); // Chama a função socp com o terceiro argumento como destino e o segundo como origem
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  // ****ListaDeCopias*********
  // Verifica se o primeiro argumento é igual a "listCopies"
  if (strcmp(args[0], "listCopies") == 0)
  {
    list_copies(); // Chama a função list_copies que lista todas as cópias de arquivos registradas
    return 1;      // Retorna 1 para indicar que um comando embutido foi executado
  }

  // Verifica se o primeiro argumento é igual a "ftype"
  if (strcmp(args[0], "ftype") == 0)
  {
    // Se o segundo argumento for NULL, imprime uma mensagem de uso
    if (args[1] == NULL /*|| args[2] == NULL*/)
    {
      printf("uso-> ftype path \n");
    }
    else
    {
      getFileType(args[1]); // Chama a função getFileType com o segundo argumento como o caminho do arquivo
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  //***MAIOR***
  // Verifica se o primeiro argumento é igual a "Maior"
  if (strcmp(args[0], "Maior") == 0)
  {
    // Se o segundo ou terceiro argumento for NULL, imprime uma mensagem de uso
    if (args[1] == NULL || args[2] == NULL)
    {
      printf("uso-> ftype path / path \n");
    }
    else
    {
      maiortamanho(args[1], args[2]); // Chama a função maiortamanho com o segundo e terceiro argumentos como os caminhos dos arquivos
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  //***SETX***
  // Verifica se o primeiro argumento é igual a "Sext"
  if (strcmp(args[0], "Sext") == 0)
  {
    // Se o segundo argumento for NULL, imprime uma mensagem de uso
    if (args[1] == NULL)
    {
      printf("uso-> ftype path\n");
    }
    else
    {
      sext(args[1]); // Chama a função sext com o segundo argumento como o caminho do arquivo
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  //***REMOVERLEITURA***
  // Verifica se o primeiro argumento é igual a "RemoverLeitura"
  if (strcmp(args[0], "RemoverLeitura") == 0)
  {
    // Se o segundo argumento for NULL, imprime uma mensagem de uso
    if (args[1] == NULL)
    {
      printf("uso-> ftype path\n");
    }
    else
    {
      removerleitura(args[1]); // Chama a função removerleitura com o segundo argumento como o caminho do arquivo
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  //***SOLS***
  // Verifica se o primeiro argumento é igual a "sols"
  if (strcmp(args[0], "sols") == 0)
  {
    // Se o segundo argumento for NULL, imprime uma mensagem de uso
    if (args[1] == NULL)
    {
      printf("uso-> ftype path\n");
    }
    else
    {
      sols(args[1]); // Chama a função sols com o segundo argumento como o caminho do diretório
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  if (0 == strcmp(args[0], "isjpg"))
  {
    int fd = open(args[1], O_RDONLY);
    if (isjpg(fd) == 1)
      printf("%s é um JPG\n", args[1]);
    else
      printf("%s não é um JPG\n", args[1]);
    return 1;
  }



  if (strcmp(args[0], "historic") == 0) {
        print_history();
        return 1;
    }
  
  if (strcmp(args[0], "execute_from_historic") == 0) {
        if (args[1] == NULL) {
            printf("usage: execute_from_history <n>\n");
        } else {
            int n = atoi(args[1]);
            execute_command_from_history(n); // chamada com o localizador de índice
        }
        return 1;
    }

  //--------------------------------ENCRY----------------------------------------------------
  //***GERAPASSI***
  // Verifica se o primeiro argumento é igual a "gerapassI"
  if (strcmp(args[0], "gerapassI") == 0)
  {
    // Se o segundo argumento for NULL, imprime uma mensagem de erro
    if (args[1] == NULL)
    {
      printf("sem ficheiro de insercao\n");
    }
    else
    {
      gerapassharmonia(args[1]); // Chama a função gerapassharmonia com o segundo argumento como o caminho do arquivo
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  //***GERSPASS12***
  // Verifica se o primeiro argumento é igual a "gerapass12"
  if (strcmp(args[0], "gerapass12") == 0)
  {
    // Se o segundo ou terceiro argumento for NULL, imprime uma mensagem de erro e termina o programa
    if (args[1] == NULL || args[2] == NULL)
    {
      printf("password / file invalida/nao inserida");
      exit(EXIT_FAILURE);
    }
    else
    {
      gerapass12(args[1], args[2]); // Chama a função gerapass12 com o segundo e terceiro argumentos
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  //***DESCODIFICAR12***
  // Verifica se o primeiro argumento é igual a "descodificar12"
  if (strcmp(args[0], "descodificar12") == 0)
  {
    // Se o segundo argumento for NULL, imprime uma mensagem de erro e termina o programa
    if (args[1] == NULL)
    {
      printf("file invalida/nao inserida");
      exit(EXIT_FAILURE);
    }
    else
    {
      descodificar12(args[1]); // Chama a função descodificar12 com o segundo argumento como o caminho do arquivo
    }
    return 1; // Retorna 1 para indicar que um comando embutido foi executado
  }

  // -----------------------------BLOCKCHAIN------------------------------------------------
  /*
    if (strcmp(args[0], "simularblockchain") == 0) {
        simulate_blockchain();
        return 1;
    }

  */

  /*
  Esses dados são apresentados em sequência para cada bloco na blockchain, começando com o bloco de índice 0 até o último bloco,
   que neste caso é o bloco de índice 4. Cada bloco contém informações sobre si mesmo, o bloco anterior e seu hash. Isso garante a
   integridade e a imutabilidade dos dados na blockchain.
  */

  /* IMPORTANTE :
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}
