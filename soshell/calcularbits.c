#include "shell.h"

/**
 * @file calcularbits.c
 * @brief Realiza operações bit a bit entre dois números.
 *
 * Este arquivo contém a função bits, que é responsável por realizar operações bit a bit
 * entre dois números inteiros. As operações suportadas incluem AND (&), OR (|), XOR (^),
 * NOT (~), deslocamento à esquerda (<<) e deslocamento à direita (>>). A função converte
 * os operandos de string para inteiro, realiza a operação especificada e imprime o resultado.
 *
 * @param op1 O primeiro operando como caractere. Será convertido para inteiro.
 * @param op O operador como string. Define a operação bit a bit a ser realizada.
 * @param op2 O segundo operando como string. Será convertido para inteiro.
 */

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