#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "comandos.h"
#include "fornecidas.h"
#include "registros.h"

// funções auxiliares

RegCab cabecalho_vazio();
int ler_linha_csv(char *buffer, RegDados *registro);
void escrever_registro(FILE *bin, RegDados *registro);
void escrever_cabecalho(FILE *bin, RegCab *cabecalho);

#define BUFFER_LEN 1024

void comando_create()
{
        // abrindo o csv e o binário

        char *caminho_csv = strtok(NULL, " ");

        FILE *csv = fopen(caminho_csv, "rt");

        if (csv == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }

        char *caminho_bin = strtok(NULL, " ");

        FILE *bin = fopen(caminho_bin, "wb");

        if (bin == NULL) {
                fclose(bin);

                printf("Falha no processamento do arquivo.\n");

                return;
        }

        // lendo o csv linha a linha

        RegCab cabecalho = cabecalho_vazio();

        fseek(bin, SEEK_SET, CAB_OFFSET);       // pula os bytes do cabeçalho

        char buffer[BUFFER_LEN];

        fgets(buffer, BUFFER_LEN, csv);         // pula o cabeçalho

        while (fgets(buffer, BUFFER_LEN, csv) != NULL) {
                // lê uma linha do csv e a escreve no arquivo binário

                RegDados registro;
                
                int erro = ler_linha_csv(buffer, &registro);
                escrever_registro(bin, &registro);

                cabecalho.proxRRN++;
                cabecalho.nroPares++;
        }

        // escreve o cabeçalho e escreve na tela

        escrever_cabecalho(bin, &cabecalho);

        fclose(csv);
        fclose(bin);

        BinarioNaTela(caminho_bin);
}

// cria um cabeçalho vazio
RegCab cabecalho_vazio()
{
        RegCab cabecalho = {
                .status = CAB_CONSISTENTE,
                .topoPilha = NIL_INT,
                .proxRRN = 0,
                .nroRegRem = 0,
                .nroPares = 0
        };

        return cabecalho;
}

// lê uma linha do arquivo csv padronizado e armazena em um registro
int ler_linha_csv(char *buffer, RegDados *registro)
{
        registro->removido = REG_MARCADO;
        registro->encadeamentoPilha = NIL_INT;          // valor nulo padrão

        // lê o idPoPs

        char *token = strtok(buffer, ",");

        if (token == NULL)
                return 1;

        registro->idPoPs = atoi(token);

        // idPoPsConectado

        token = strtok(NULL, ",");

        if (token == NULL)
                return 1;

        registro->idPoPsConectado = atoi(token);

        // velocidade

        token = strtok(NULL, ",");

        if (token == NULL)
                return 1;

        registro->velocidade = atoi(token);

        // unidadeMedida

        token = strtok(NULL, ",");

        if (token == NULL)
                return 1;

        registro->unidadeMedida = *token;

        return 0;
}

// escreve o registro campo a campo
void escrever_registro(FILE *bin, RegDados *registro)
{
        fwrite(
                &registro->removido,
                sizeof(registro->removido),
                1,
                bin
        );
        
        fwrite(
                &registro->encadeamentoPilha,
                sizeof(registro->encadeamentoPilha),
                1,
                bin
        );

        fwrite(
                &registro->idPoPs,
                sizeof(registro->idPoPs),
                1,
                bin
        );

        fwrite(
                &registro->idPoPsConectado,
                sizeof(registro->idPoPsConectado),
                1,
                bin
        );

        fwrite(
                &registro->unidadeMedida,
                sizeof(registro->unidadeMedida),
                1,
                bin
        );
}

// escreve o cabeçalho no início do arquivo, campo a campo
void escrever_cabecalho(FILE *bin, RegCab *cabecalho)
{
        fseek(bin, SEEK_SET, 0);        // retorna ao começo do arquivo

        fwrite(&cabecalho->status,      sizeof(cabecalho->status),      1,      bin);
        fwrite(&cabecalho->topoPilha,   sizeof(cabecalho->topoPilha),   1,      bin);
        fwrite(&cabecalho->proxRRN,     sizeof(cabecalho->proxRRN),     1,      bin);
        fwrite(&cabecalho->nroRegRem,   sizeof(cabecalho->nroRegRem),   1,      bin);
        fwrite(&cabecalho->nroPares,    sizeof(cabecalho->nroPares),    1,      bin);
}
