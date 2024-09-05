#include "shell.h"

/*
    parse . particiona o comando Unix (armazenado em ptrLinha) em argumentos
*/

/**
 * @brief Analisa uma linha de comando e divide-a em argumentos.
 * 
 * @param ptrLinha Um ponteiro para a linha de comando a ser analisada.
 * @param args Um array de ponteiros para onde os argumentos serão salvos.
 * 
 * Esta função percorre a linha de comando e divide-a em argumentos separados por espaços em branco.
 * Cada argumento é salvo no array `args` e um NULL é adicionado ao final do array para indicar o fim dos argumentos.
 * A função também conta o número de argumentos e retorna esse número.
 * 
 * @return O número de argumentos na linha de comando.
 */

int parse (char *ptrLinha, char **args)
{
  

  
  int count = 0; // Inicializa o contador de argumentos
  while ('\0' != *ptrLinha) // Enquanto não chegar ao fim da linha de comando
    {
      /* Remove espaços em branco. Usa um NULL para indicar que o argumento anterior é o último */
      while (isspace ((unsigned char) *ptrLinha))
        *ptrLinha++ = '\0'; // Substitui espaços em branco por NULL e avança para o próximo caractere

      *args++ = ptrLinha; // Guarda o argumento atual e avança para a próxima posição no array de argumentos
      count++; // Incrementa o contador de argumentos
      while ((*ptrLinha != '\0') && (!isspace ((unsigned char) *ptrLinha))) // Enquanto não chegar ao fim do argumento atual
        ptrLinha++; // Avança para o próximo caractere
    }
  *args = (char *) NULL; // O último argumento é NULL
  return count; // Retorna o número de argumentos
}

//ver o ultimo com o & para ver o lat one, para char de bg e fg