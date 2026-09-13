#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "comandos.h"
#include "filtro.h"
#include "input.h"

// funcionalidade 3 da especificação
void comando_where(char *buffer, size_t length)
{
        char *caminho_bin = strtok(NULL, " ");

        FILE *bin = fopen(caminho_bin, "rb");

        if (bin == NULL) {
                printf("Falha no processamento do arquivo.\n");
                return;
        }

        RegCab cabecalho;                       // lê o cabeçalho do arquivo binário
        ler_cabecalho(bin, &cabecalho);

        int32_t proxRRN = cabecalho.proxRRN;    // número total de registros a serem percorridos
                                                // durante cada busca

        char *n_str = strtok(NULL, " ");
        int n = atoi(n_str);

        for (int i = 0; i < n; i++) {
                Filtro filtro;                          // recebe o i-ésimo filtro da entrada

                fgets_limpo(buffer, length, stdin);
                parse_filtro(&filtro, buffer, length);

                // debug_filtro(filtro);

                for (int32_t j = 0; j < proxRRN; j++) {
                        RegDados registro;              // lê do disco o registro no RRN j
                        ler_registro(bin, &registro);

                        if (registro.removido == REG_REMOVIDO)
                                // ignora o registro removido
                                continue;
                        else if (registro.removido == REG_EM_USO
                                 && comparar_filtro(&filtro, &registro))
                                printa_registro(&registro);
                }

                printf("\n");

                if (i + 1 < n)
                        fseek(bin, CAB_TAMANHO, SEEK_SET);
        }

        fclose(bin);
}