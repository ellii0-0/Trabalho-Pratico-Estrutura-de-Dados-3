#include <stdio.h>

#include "registros.h"

char *tabelaNomeCampo[] = {
        "idPoPs",
        "idPoPsConectado",
        "velocidade",
        "unidadeMedida"
};

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
                &registro->velocidade,
                sizeof(registro->velocidade),
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
        fseek(bin, 0, SEEK_SET);        // retorna ao começo do arquivo

        fwrite(&cabecalho->status,      sizeof(cabecalho->status),      1,      bin);
        fwrite(&cabecalho->topoPilha,   sizeof(cabecalho->topoPilha),   1,      bin);
        fwrite(&cabecalho->proxRRN,     sizeof(cabecalho->proxRRN),     1,      bin);
        fwrite(&cabecalho->nroRegRem,   sizeof(cabecalho->nroRegRem),   1,      bin);
        fwrite(&cabecalho->nroPares,    sizeof(cabecalho->nroPares),    1,      bin);
}