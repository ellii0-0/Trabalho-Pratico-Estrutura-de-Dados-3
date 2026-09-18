#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#include "comandos.h"
#include "fornecidas.h"
#include "registros.h"

//busca registro binario em rrn
void comando_rrn(void)
{
        char *caminho = strtok(NULL, " ");
 
        if (caminho == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        char *rrn_str = strtok(NULL, " ");
 
        if (rrn_str == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        int32_t RRN = atoi(rrn_str);
 
        RegCab cabecalho;
        FILE *arquivo = abrir_binario(caminho, &cabecalho, false);
 
        if (arquivo == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        if (cabecalho.status != CAB_CONSISTENTE) {
                fclose(arquivo);
                printf("Falha no processamento do arquivo.\n");
                return;
        }

 
        if (RRN < 0 || RRN >= cabecalho.proxRRN) {
                fclose(arquivo);
                printf("Registro inexistente.\n");
                return;
        }

 
        fseek(arquivo, CAB_TAMANHO + RRN * REG_TAMANHO, SEEK_SET);
 
        RegDados registro;
        ler_registro(arquivo, &registro);
 
        fclose(arquivo);
 
        if (registro.removido == REG_REMOVIDO)
                printf("Registro inexistente.\n");
        else
                printa_registro(&registro);
}

 
// lê e imprime os registros do arquivo binário 
void comando_listar(int codigo, char *buffer, int length)
{       
        (void)buffer;
        (void)length;
        char *caminho = strtok(NULL, " ");
 
        if (caminho == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        // abre para leitura (marcar = false: não altera o status do cabeçalho, fclose basta)
 
        RegCab cabecalho;
        FILE *arquivo = abrir_binario(caminho, &cabecalho, false);
 
        if (arquivo == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        if (cabecalho.status != CAB_CONSISTENTE) {
                fclose(arquivo);
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        int imprimiu = 0;        // marca se pelo menos um registro foi exibido
 
        for (int32_t RRN = 0; RRN < cabecalho.proxRRN; RRN++) {
                RegDados registro;
                ler_registro(arquivo, &registro);
 
                if (codigo == 2 && registro.removido == REG_EM_USO) {
                        printa_registro(&registro);
                        imprimiu = 1;
                }
        }
 
        fclose(arquivo);
 
        if (!imprimiu)
                printf("Registro inexistente.\n");
}
