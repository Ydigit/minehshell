/**
 * @file calc.c
 * @brief A simple calculator program.
 */

#include "shell.h"

/**
 * @brief A function that performs basic arithmetic operations.
 * 
 * This function takes two values and an operator as input, performs the specified operation, and prints the result.
 * 
 * @param value1 The first operand in string format.
 * @param op The operator in string format. It can be "+", "-", "*", "^", or "/".
 * @param value2 The second operand in string format.
 * 
 * @return void
 */
void calc(char *value1,char *op, char*value2){
    float valor1 = atof(value1);
    float valor2 = atof(value2);
    float resultado;

    if (strncmp(op, "+", 1)==0) {
        resultado = valor1 + valor2;
    } else if (strncmp(op, "-",1)==0) {
        resultado = valor1 - valor2;
    } else if (strncmp(op, "*",1)==0) {
        resultado =valor1 * valor2;
    }else if (strncmp(op, "^",1)==0){
        resultado = powf(valor1,valor2); // Exponential operation
    } else if (strncmp(op, "/",1)==0) {
        if (valor2 == 0) {
            printf("\nErro! segundo elemento da divisao nao pode ser 0!\n\n");
            return;
        } else {
            resultado = valor1 / valor2;
        }
    }else{
        printf("\n\n!!!Operacao ilegal, chamem a gnr!\n\n");
    }
    printf("Resultado da operacao = %.6f\n", resultado);
}