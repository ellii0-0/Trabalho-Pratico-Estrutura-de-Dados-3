#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#include "comandos.h"
#include "fornecidas.h"
#include "registros.h"
#include "input.h"

void comando_listar(char *buffer, size_t length)
{
        // lê e imprime os registros do arquivo binário 

        char *caminho = strtok(NULL, " ");
 
        if (caminho == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        // abre para leitura
 
        RegCab cabecalho;
        FILE *bin = abrir_binario(caminho, &cabecalho, false);
 
        if (bin == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        bool imprimiu = false;        // marca se pelo menos um registro foi exibido
 
        for (int32_t RRN = 0; RRN < cabecalho.proxRRN; RRN++) {
                RegDados registro;
                ler_registro(bin, &registro);
 
                if (registro.removido == REG_EM_USO) {
                        printa_registro(&registro);
                        imprimiu = true;
                }
        }
 
        fechar_binario(bin, &cabecalho, false);
 
        if (!imprimiu)
                printf("Registro inexistente.\n");
}