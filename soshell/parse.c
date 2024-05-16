#include "shell.h"

/*
    parse . particiona o comando Unix (armazenado em ptrLinha) em argumentos
*/

int parse (char *ptrLinha, char **args)
{
  
  int count = 0;
  while ('\0' != *ptrLinha)
    {
      /* strip whitespace. Usa um NULL para indicar que o argumento anterior e. o ultimo */
      while (isspace ((unsigned char) *ptrLinha))
        *ptrLinha++ = '\0';

      *args++ = ptrLinha;/* salvaguarda argumento */
      count++;
      while ((*ptrLinha != '\0') && (!isspace ((unsigned char) *ptrLinha)))/* salta sobre o argumento */
        ptrLinha++;
    }
  *args = (char *) NULL;/* o ultimo argumento e. NULL */
  return count;
}
