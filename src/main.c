// Thales Mendonça Soares       --      NUSP 14608869
// Victor Soares Vasconcelos    --      NUSP 16903560

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fornecidas.h"
#include "comandos.h"
#include "input.h"

#define BUF_LEN 65535


int main()
{
        // recebe o comando

        char buffer[BUF_LEN];
        fgets_limpo(buffer, BUF_LEN, stdin);

        // leitura do índice da funcionalidade

        char *token = strtok(buffer, " ");
        int indice_func = atoi(token);

        // executa a funcionalidade especificada

        switch (indice_func) {
        case 1:
                comando_create(buffer, BUF_LEN);
                break;
        case 2:
                break;
        case 3:
                comando_where(buffer, BUF_LEN);
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