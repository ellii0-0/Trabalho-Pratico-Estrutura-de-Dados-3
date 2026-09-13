#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "comandos.h"
#include "filtro.h"
#include "input.h"
#include "fornecidas.h"

// funções auxiliares

void loop_busca(int codigo, FILE *bin, RegCab *cabecalho, Filtro *filtro);
void operacao_busca(int codigo, FILE *bin, RegCab *cabecalho, RegDados *registro, int32_t RRN);



void comando_busca(int codigo, char *buffer, size_t length)
{
        char *caminho_bin = strdup(strtok(NULL, " "));

        FILE *bin = fopen(caminho_bin, "rb+");

        if (bin == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }

        RegCab cabecalho;                       // lê o cabeçalho do arquivo binário
        ler_cabecalho(bin, &cabecalho);

        cabecalho.status = CAB_INCONSISTENTE;   // marca o cabeçalho enquanto inconsistente
        fseek(bin, 0, SEEK_SET);
        escrever_cabecalho(bin, &cabecalho);

        char *n_str = strtok(NULL, " ");        // número de iterações
        int n = atoi(n_str);

        for (int i = 0; i < n; i++) {
                Filtro filtro;                          // recebe o i-ésimo filtro da entrada

                fgets_limpo(buffer, length, stdin);
                parse_filtro(&filtro, buffer, length);

                // debug_filtro(&filtro);

                loop_busca(codigo, bin, &cabecalho, &filtro);

                if (codigo == 3)
                        // quebra de linha entre prints da func 3
                        printf("\n");

                if (i + 1 < n)
                        // fseek apenas quando necessário
                        fseek(bin, CAB_TAMANHO, SEEK_SET);
        }

        cabecalho.status = CAB_CONSISTENTE;

        fseek(bin, 0, SEEK_SET);
        escrever_cabecalho(bin, &cabecalho);

        fclose(bin);

        if (codigo == 5 || codigo == 6 || codigo == 7)
                BinarioNaTela(caminho_bin);

        free(caminho_bin);
}

// loop que percorre todo os registros
void loop_busca(int codigo, FILE *bin, RegCab *cabecalho, Filtro *filtro)
{
        for (int32_t RRN = 0; RRN < cabecalho->proxRRN; RRN++) {
                RegDados registro;              // lê do disco o registro no RRN
                ler_registro(bin, &registro);

                if (registro.removido == REG_REMOVIDO)
                        // ignora o registro removido
                        continue;
                else if (comparar_filtro(filtro, &registro))
                        operacao_busca(codigo, bin, cabecalho, &registro, RRN);
        }
}

// realiza uma operação definida pelo código no registro que satisfaz o filtro
void operacao_busca(int codigo, FILE *bin, RegCab *cabecalho, RegDados *registro, int32_t RRN)
{
        switch (codigo) {
        case 3:                                 // imprimir
                printa_registro(registro);
                break;
        case 5:                                 // remoção do registro
                remover_registro(bin, cabecalho, RRN);
                break;
        }
}