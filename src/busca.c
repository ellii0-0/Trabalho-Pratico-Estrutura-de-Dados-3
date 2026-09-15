#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "comandos.h"
#include "filtro.h"
#include "input.h"
#include "fornecidas.h"

// funções auxiliares

static void loop_printar(FILE *bin, RegCab *cabecalho, Filtro *filtro);
static void loop_remover(FILE *bin, RegCab *cabecalho, Filtro *filtro);
static void loop_atualizar(FILE *bin, RegCab *cabecalho, Filtro *filtro, Filtro *mudancas);

void comando_busca(int codigo, char *buffer, size_t length)
{
        char *caminho_bin = strdup(strtok(NULL, " "));

        FILE *bin;
        
        if (codigo == 3)
                bin = fopen(caminho_bin, "rb");
        else
                bin = fopen(caminho_bin, "rb+");

        if (bin == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }

        RegCab cabecalho;                       // lê o cabeçalho do arquivo binário
        ler_cabecalho(bin, &cabecalho);

        if (codigo != 3) {
                cabecalho.status = CAB_INCONSISTENTE;   // marca o cabeçalho enquanto inconsistente
                fseek(bin, 0, SEEK_SET);
                escrever_cabecalho(bin, &cabecalho);
        }

        char *n_str = strtok(NULL, " ");        // número de iterações
        int n = atoi(n_str);

        for (int i = 0; i < n; i++) {
                Filtro filtro;                          // recebe o i-ésimo filtro da entrada

                fgets_limpo(buffer, length, stdin);
                parse_filtro(&filtro, buffer, length);

                // debug_filtro(&filtro);

                switch (codigo) {
                case 3:
                        loop_printar(bin, &cabecalho, &filtro);
                        break;

                case 5:
                        loop_remover(bin, &cabecalho, &filtro);
                        break;
                        
                case 6:
                        break;

                case 7:
                        Filtro mudancas;

                        fgets_limpo(buffer, length, stdin);
                        parse_filtro(&mudancas, buffer, length);

                        loop_atualizar(bin, &cabecalho, &filtro, &mudancas);
                        break;
                }
        
                if (i + 1 < n)
                        // fseek apenas quando necessário
                        fseek(bin, CAB_TAMANHO, SEEK_SET);
        }

        // escreve o cabeçalho na memória e fecha o arquivo

        if (codigo != 3) {
                cabecalho.status = CAB_CONSISTENTE;

                fseek(bin, 0, SEEK_SET);
                escrever_cabecalho(bin, &cabecalho);
        }

        fclose(bin);

        if (codigo != 3)
                BinarioNaTela(caminho_bin);

        free(caminho_bin);
}

void loop_printar(FILE *bin, RegCab *cabecalho, Filtro *filtro)
{
        for (int32_t RRN = 0; RRN < cabecalho->proxRRN; RRN++) {
                RegDados registro;              // lê do disco o registro no RRN
                ler_registro(bin, &registro);

                if (registro.removido == REG_REMOVIDO)
                        // ignora o registro removido
                        continue;
                else if (filtrar_registro(filtro, &registro))
                        printa_registro(&registro);
        }
        
        printf("\n");
}

void loop_remover(FILE *bin, RegCab *cabecalho, Filtro *filtro)
{
        for (int32_t RRN = 0; RRN < cabecalho->proxRRN; RRN++) {
                RegDados registro;              // lê do disco o registro no RRN
                ler_registro(bin, &registro);

                if (registro.removido == REG_REMOVIDO)
                        // ignora o registro removido
                        continue;
                else if (filtrar_registro(filtro, &registro))
                        remover_registro(bin, cabecalho, RRN);
        }
}

void loop_atualizar(FILE *bin, RegCab *cabecalho, Filtro *filtro, Filtro *mudancas)
{
        for (int32_t RRN = 0; RRN < cabecalho->proxRRN; RRN++) {
                RegDados registro;              // lê do disco o registro no RRN
                ler_registro(bin, &registro);

                if (registro.removido == REG_REMOVIDO)
                        // ignora o registro removido
                        continue;
                else if (filtrar_registro(filtro, &registro))
                        atualizar_registro(&registro, mudancas);
        }
}