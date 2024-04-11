#include "shell.h"

char prompt[100];

int main ()
{
  int len;
  char linha[1024];/* um comando */
  char *args[64];/* com um maximo de 64 argumentos */

  strcpy (prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
  {
    printf ("%s", prompt);
    if (fgets (linha, 1023, stdin) == NULL)
    {
      printf ("\n");
      exit (0);
    }
    len = strlen (linha);
    if (1 == len)
      continue;/* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
    parse (linha, args);/* particiona a string em argumentos */

    if (!builtin (args))
      execute (args);/* executa o comando */
    }
  return 0;
}

  /*           
    * BULD In
  */           

int builtin (char **args)
{
  /* Toda a funcionalidade embutida deverá devolver 1*/
  //get out
  if (strcmp (args[0], "sair") == 0)
  {
    exit (0);
    return 1; /* funcionalidade embutida */
  }

  if (strncmp (args[0], "42", 2) == 0)
  {
    printf("42 is the answer to life the universe and everything\n");
    printf("...\n");
    return 1;/* funcionalidade embutida */
  }

if (strncmp (args[0], "devgit", 6) == 0)
{
    printf("Check more on \n");
    printf("****************************\n");
    printf("* https://github.com/Ydigit*\n");
    printf("****************************\n");
    return 1; /* funcionalidade embutida */
}

  if( 0==strcmp(args[0], "obterinfo") ){
    printf("SoShell 2024 versaõ 1.0\n");
    return 1 ; //comando embutido
  }
  if( 0==strcmp(args[0], "identificacaopessoal") ){
    system("id");
    return 1 ; //comando embutido
  }

  if (0 == strcmp(args[0], "cd")) {
    int err;
    char *guardadir = "~";
    //char *guardadiremtraco[255];

    if(args[1] == NULL || strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME")==0){
      getcwd(guardadir, 255);
      err=chdir( getenv("HOME") ) ;//entra
    }
    else if(strcmp(args[1],"-")==0){//se for vou ter de dar ch em anterior
      //getcwd(guardadiremtraco, 255);
      err=chdir(guardadir);
      }
      else{
      getcwd(guardadir,255);//guarda atual em guardadir
      err = chdir( args[1] );//entra na diretoria do arg1
    }

    if (err<0) perror ( args[1]);//menor que zero e invalid
      return 1 ; //comando embutido
  }


//username
  if( strlen(args[0])>4 && strlen(args[0])<102 && 0==strncmp(args[0], "PS1=",4) ){ //max 102 porcausa dos 98 * os 4
    strcpy(prompt,args[0]+4);
    prompt[strlen(args[0]+4)] = ' ';
    prompt[strlen(args[0]+4)+1] = '\0';
    return 1 ; //comando embutido
  }


//copy com o socp
    if( 0==strcmp(args[0], "socp") ){
    if(args[1]==NULL || args[2]==NULL){
      printf("uso-> socp enrada ->t sadai\n");
    }else{
      socp(args[2], args[1]);// o 2 e o destino e o 1 e a source 
    }
    return 1; //comando embutido
  }

  //check if equals
//check if equals
if(0 == strcmp(args[0],"compare2txt")){
  if(args[1]==NULL || args[2]==NULL){
    perror("no files no equals..\n");
    exit(0);
  }
  else{
    compare2txt(args[1], args[2]);
  }
  return 1;//embutido
}
//linhax e o 
//int numargs = parse();




/*
  int i=0;
  while(args[i]!=NULL){
    i++;
  }
  if ( 0 == strcmp(args[0], "calc")&& i==3) {
      calc(args[1],args[2],args[3]);
 return 1 ; //comando embutido
  }
*/



  //

  /* IMPORTANTE : 
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}
