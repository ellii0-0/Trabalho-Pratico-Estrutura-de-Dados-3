#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "registros.h"
#include "fornecidas.h"
#include "func.h"

// funções auxiliares
static RegCab cabecalho_vazio();

// funcionalidade [1] especificada: geração de arquivo binário a partir de csv
void func_1()
{
        // leitura do caminho conforme a sintaxe
        // 1 arquivoEntrada.csv arquivoSaida.csv

        char *caminho_csv = strtok(NULL, " ");
        char *caminho_bin = strtok(NULL, " ");

        FILE *arquivo_csv = fopen(caminho_csv, "rt");
        FILE *arquivo_bin = foepn(caminho_bin, "wb");
        
        // teste de validação

        if (arquivo_csv == NULL || arquivo_bin == NULL) {

                fclose(arquivo_csv);
                fclose(arquivo_bin);

                printf("Falha no processamento do arquivo.\n");

                return;
        }

        RegCab cabecalho = cabecalho_vazio();
        
        // fgets no cabeçalho do csv + laço de repetição até o csv acabar

        fclose(arquivo_csv);
        fclose(arquivo_bin);

        BinarioNaTela(caminho_bin);
}

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