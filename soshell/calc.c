#include "shell.h"

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

        resultado = powf(valor1,valor2); //operacao de exponenecial
        
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

