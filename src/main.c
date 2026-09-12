// Thales Mendonça Soares       --      NUSP 14608869
// Victor Soares Vasconcelos    --      NUSP 16903560

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fornecidas.h"

#include "func.h"

#define BUF_LEN 1024

int main()
{
        // recebe o comando

        char buffer[BUF_LEN];
        fgets(buffer, buffer, stdin);

        // leitura do índice da funcionalidade

        char *token = strtok(buffer, " ");
        int func = atoi(token);

        // executa a funcionalidade especificada

        switch (func) {
        case 1:
                func_1();
                break;
        case 2:
                break;
        case 3:
                break;
        case 4:
                break;
        case 5:
                break;
        case 6:
                break;
        case 7:
                break;
        default:
                // saída de erro não-especificada
                printf("Funcionalidade inválida.\n");
                return 1;
        }

        return 0;
}