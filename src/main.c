// Thales Mendonça Soares       --      NUSP 14608869
// Victor Soares Vasconcelos    --      NUSP 16903560

#include <stdio.h>
<<<<<<< HEAD
<<<<<<< Updated upstream

int main()
{
        printf("Olá, mundo!\n");
=======
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
=======
#include <string.h>
#include <stdlib.h>

#include "fornecidas.h"
#include "comandos.h"

#define MAIN_BUF_LEN 1024

int main()
{
        // recebe o comando

        char buffer[MAIN_BUF_LEN];
        fgets(buffer, MAIN_BUF_LEN, stdin);
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b

        // leitura do índice da funcionalidade

        char *token = strtok(buffer, " ");
        int indice_func = atoi(token);

        // executa a funcionalidade especificada

        switch (indice_func) {
        case 1:
<<<<<<< HEAD
                comando_create(buffer, BUF_LEN);
=======
                comando_create();
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b
                break;
        case 2:
                break;
        case 3:
<<<<<<< HEAD
                comando_where(buffer, BUF_LEN);
=======
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b
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

<<<<<<< HEAD
>>>>>>> Stashed changes
=======
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b
        return 0;
}