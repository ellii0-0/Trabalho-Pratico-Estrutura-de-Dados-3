#include <stdio.h>

#include "registros.h"

<<<<<<< HEAD
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
=======
char *tabelaNomeCampo[] = {
        "idPoPs",
        "idPoPsConectado",
        "velocidade",
        "unidadeMedida"
};
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b

// escreve o registro campo a campo
void escrever_registro(FILE *bin, RegDados *registro)
{
<<<<<<< HEAD
        if (bin == NULL || registro == NULL)
                return;

=======
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b
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

<<<<<<< HEAD
// escreve o cabeçalho no arquivo binário campo a campo
void escrever_cabecalho(FILE *bin, RegCab *cabecalho)
{
        if (bin == NULL || cabecalho == NULL)
                return;
=======
// escreve o cabeçalho no início do arquivo, campo a campo
void escrever_cabecalho(FILE *bin, RegCab *cabecalho)
{
        fseek(bin, 0, SEEK_SET);        // retorna ao começo do arquivo
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b

        fwrite(&cabecalho->status,      sizeof(cabecalho->status),      1,      bin);
        fwrite(&cabecalho->topoPilha,   sizeof(cabecalho->topoPilha),   1,      bin);
        fwrite(&cabecalho->proxRRN,     sizeof(cabecalho->proxRRN),     1,      bin);
        fwrite(&cabecalho->nroRegRem,   sizeof(cabecalho->nroRegRem),   1,      bin);
        fwrite(&cabecalho->nroPares,    sizeof(cabecalho->nroPares),    1,      bin);
<<<<<<< HEAD
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
=======
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b
}