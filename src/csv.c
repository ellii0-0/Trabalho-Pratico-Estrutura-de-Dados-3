#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "comandos.h"
#include "fornecidas.h"
#include "registros.h"
#include "input.h"

// funções auxiliares

void cabecalho_vazio(RegCab *cabecalho);
int ler_linha_csv(char *buffer, RegDados *registro);

// funcionalidade 1 da especificação
void comando_create(char *buffer, size_t length)
{
        char *caminho_csv = strtok(NULL, " ");

        FILE *csv = fopen(caminho_csv, "rt");

        if (csv == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }

        char *caminho_bin = meu_strdup(strtok(NULL, " "));

        FILE *bin = fopen(caminho_bin, "wb");

        if (bin == NULL) {
                fclose(csv);
                printf("Falha no processamento do arquivo.\n");
                return;
        }

        // lendo o csv linha a linha

        RegCab cabecalho;
        cabecalho_vazio(&cabecalho);
        escrever_cabecalho(bin, &cabecalho);    // escreve o cabeçalho (inconsistente)

        fgets(buffer, length, csv);         // pula o cabeçalho do csv

        while (fgets_limpo(buffer, length, csv) != NULL) {
                // lê uma linha do csv e a escreve no arquivo binário

                RegDados registro;
                
                int erro = ler_linha_csv(buffer, &registro);
                escrever_registro(bin, &registro);

                cabecalho.proxRRN++;
                cabecalho.nroPares++;
        }

        // escreve o cabeçalho e chama BinarioNaTela()

        cabecalho.status = CAB_CONSISTENTE;

        fseek(bin, 0, SEEK_SET);
        escrever_cabecalho(bin, &cabecalho);

        fclose(csv);
        fclose(bin);

        BinarioNaTela(caminho_bin);

        free(caminho_bin);
}

// cria um cabeçalho vazio
void cabecalho_vazio(RegCab *cabecalho)
{
        *cabecalho = (RegCab){
                .status = CAB_INCONSISTENTE,
                .topoPilha = NIL_INT,
                .proxRRN = 0,
                .nroRegRem = 0,
                .nroPares = 0
        };
}

// lê uma linha do arquivo csv padronizado e armazena em um registro
int ler_linha_csv(char *buffer, RegDados *registro)
{
        registro->removido = REG_EM_USO;
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