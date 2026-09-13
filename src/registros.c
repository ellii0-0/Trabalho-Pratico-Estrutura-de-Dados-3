#include <stdio.h>

#include "registros.h"

void printa_registro(RegDados *registro)
{
        if (registro == NULL)
                return;

        printf(
                "%d %d %d \"%c\"\n",
                registro->idPoPs,
                registro->idPoPsConectado,
                registro->velocidade,
                registro->unidadeMedida
        );
}

// escreve o registro campo a campo
void escrever_registro(FILE *bin, RegDados *registro)
{
        if (bin == NULL || registro == NULL)
                return;

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

// escreve o cabeçalho no arquivo binário campo a campo
void escrever_cabecalho(FILE *bin, RegCab *cabecalho)
{
        if (bin == NULL || cabecalho == NULL)
                return;

        fwrite(&cabecalho->status,      sizeof(cabecalho->status),      1,      bin);
        fwrite(&cabecalho->topoPilha,   sizeof(cabecalho->topoPilha),   1,      bin);
        fwrite(&cabecalho->proxRRN,     sizeof(cabecalho->proxRRN),     1,      bin);
        fwrite(&cabecalho->nroRegRem,   sizeof(cabecalho->nroRegRem),   1,      bin);
        fwrite(&cabecalho->nroPares,    sizeof(cabecalho->nroPares),    1,      bin);
}


// lê do disco um registro campo a campo
void ler_registro(FILE *bin, RegDados *registro)
{
        if (bin == NULL || registro == NULL)
                return;
        
        fread(
                &registro->removido,
                sizeof(registro->removido),
                1,
                bin
        );
        
        fread(
                &registro->encadeamentoPilha,
                sizeof(registro->encadeamentoPilha),
                1,
                bin
        );

        fread(
                &registro->idPoPs,
                sizeof(registro->idPoPs),
                1,
                bin
        );

        fread(
                &registro->idPoPsConectado,
                sizeof(registro->idPoPsConectado),
                1,
                bin
        );

        fread(
                &registro->velocidade,
                sizeof(registro->velocidade),
                1,
                bin
        );

        fread(
                &registro->unidadeMedida,
                sizeof(registro->unidadeMedida),
                1,
                bin
        );
}

// lê do disco o cabeçalho campo a campo
void ler_cabecalho(FILE *bin, RegCab *cabecalho)
{
        if (bin == NULL || cabecalho == NULL)
                return;
        
        fread(&cabecalho->status,      sizeof(cabecalho->status),      1,      bin);
        fread(&cabecalho->topoPilha,   sizeof(cabecalho->topoPilha),   1,      bin);
        fread(&cabecalho->proxRRN,     sizeof(cabecalho->proxRRN),     1,      bin);
        fread(&cabecalho->nroRegRem,   sizeof(cabecalho->nroRegRem),   1,      bin);
        fread(&cabecalho->nroPares,    sizeof(cabecalho->nroPares),    1,      bin);
}