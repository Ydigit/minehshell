#include "shell.h"

void calc (char *op1,char *op, char*op2){
    float num1 = atof(op1);
    float num2 = atof(op2);
    float result;

    if (strcmp(op, "+")==0) {
        result = num1 + num2;
    } else if (strcmp(op, "-")==0) {
        result = num1 - num2;
    } else if (strcmp(op, "*")==0) {
        result = num1 * num2;
    }else if (strcmp(op, "^")==0){
         powf(num1,num2); 
    } else if (strcmp(op, "/")==0) {
    
        if (num2 != 0) {
            result = num1 / num2;
        } else {
            printf("Erro divisao por 0\n");
            return;
        }
    } else {
        printf("\n");
        return;
    }

    printf("Resulto = %.6f\n", result);
}

