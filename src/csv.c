#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "comandos.h"
#include "fornecidas.h"
#include "registros.h"
#include "input.h"

// funções auxiliares

// lê uma linha do arquivo csv padronizado e armazena em um registro
int ler_linha_csv(char *buffer, RegDados *registro);

void comando_create(char *buffer, size_t length)
{
        char *caminho_csv = strtok(NULL, " ");

        FILE *csv = fopen(caminho_csv, "rt");

        if (csv == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }

        char *caminho_bin = strdup(strtok(NULL, " "));

        // cria o arquivo binário

        RegCab cabecalho;
        FILE *bin = abrir_binario_novo(caminho_bin, &cabecalho);

        if (bin == NULL) {
                free(caminho_bin);
                fclose(csv);
                printf("Falha no processamento do arquivo.\n");
                return;
        }

        fgets(buffer, length, csv);             // pula o cabeçalho do csv

        while (fgets_limpo(buffer, length, csv) != NULL) {
                // laço: lê uma linha do csv e a escreve no arquivo binário

                RegDados registro;
                ler_linha_csv(buffer, &registro);
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

int ler_linha_csv(char *buffer, RegDados *registro)
{
        registro->removido = REG_EM_USO;
        registro->encadeamentoPilha = NIL_INT;          // valor nulo padrão

        char *next = buffer;

        // AVISO: a função strsep não existe no windows
        // lê campo a campo o arquivo csv. usa-se strsep
        // para tratar campos nulos

        char *token = strsep(&next, ",");
        registro->idPoPs = ler_valor_inteiro(token);

        token = strsep(&next, ",");
        registro->idPoPsConectado = ler_valor_inteiro(token);

        token = strsep(&next, ",");
        registro->velocidade = ler_valor_inteiro(token);

        token = strsep(&next, ",");
        ler_valor_str(token, &registro->unidadeMedida, sizeof(registro->unidadeMedida));

        return 0;
}