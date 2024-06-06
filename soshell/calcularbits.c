#include "shell.h"
void bits(char op1, char *op, char *op2)
{
    int num1 = atoi(&op1);
    int num2 = atoi(op2);
    int resultado;

    if (strcmp(op, "&") == 0)
    {
        resultado = num1 & num2;
    }
    else if (strcmp(op, "^") == 0)
    {
        resultado = num1 ^ num2;
    }
    else if (strcmp(op, "|") == 0)
    {
        resultado = num1 | num2;
    }
    else if (strcmp(op, "~") == 0)
    {
        resultado = ~num1;
    }
    else if (strcmp(op, "<<") == 0)
    {
        resultado = num1 << atoi(op2);
    }
    else if (strcmp(op, ">>") == 0)
    {
        resultado = num1 >> atoi(op2);
    }
    else
    {
        printf("Operação inv.\n");
        return;
    }
    printf("Resultado: %d\n", resultado);
}