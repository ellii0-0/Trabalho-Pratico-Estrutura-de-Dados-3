#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#include "comandos.h"
#include "fornecidas.h"
#include "registros.h"
#include "input.h"

void comando_rrn()
{
        // busca registro binario em RRN

        char *caminho = strtok(NULL, " ");
        char *rrn_str = strtok(NULL, " ");
 
        if (caminho == NULL || rrn_str == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        int32_t RRN = atoi(rrn_str);
 
        RegCab cabecalho;
        FILE *bin = abrir_binario(caminho, &cabecalho, false);
 
        if (bin == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }
 
        if (RRN < 0 || RRN >= cabecalho.proxRRN) {
                fechar_binario(bin, &cabecalho, false);
                printf("Registro inexistente.\n");
                return;
        }

        // busca facilitada por RRN

        fseek(bin, CAB_TAMANHO + RRN * REG_TAMANHO, SEEK_SET);
 
        RegDados registro;
        ler_registro(bin, &registro);
 
        fechar_binario(bin, &cabecalho, false);
        
        if (registro.removido == REG_REMOVIDO)
                printf("Registro inexistente.\n");
        else
                printa_registro(&registro);
}

void comando_inserir(char *buffer, size_t length)
{
        // insere um novo registro no arquivo
        
        char *caminho_bin = strdup(strtok(NULL, " "));
        RegCab cabecalho;                       // lê o cabeçalho do arquivo binário

        FILE *bin = abrir_binario(caminho_bin, &cabecalho, true);

        if (bin == NULL) {
                printf("Falha no processamento do arquivo.\n");

                free(caminho_bin);
                return;
        }

        char *n_str = strtok(NULL, " ");        // número de iterações
        int n = atoi(n_str);

        for (int i = 0; i < n; i++) {
                fgets_limpo(buffer, length, stdin);

                RegDados registro;

                char *campo = strtok(buffer, " ");
                registro.idPoPs = ler_valor_inteiro(campo);

                campo = strtok(NULL, " ");
                registro.idPoPsConectado = ler_valor_inteiro(campo);

                campo = strtok(NULL, " ");
                registro.velocidade = ler_valor_inteiro(campo);

                campo = strtok(NULL, " ");
                ler_valor_str(campo, &registro.unidadeMedida, 1);

                inserir_registro(bin, &cabecalho, &registro);
        }

        // escreve o cabeçalho na memória e fecha o arquivo

        fechar_binario(bin, &cabecalho, true);

        BinarioNaTela(caminho_bin);

        free(caminho_bin);
}


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