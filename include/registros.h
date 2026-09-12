// header que define as structs do cabeçalho, do registro de dados e valores nulos

#pragma once

#include <inttypes.h>

// valores nulos e lixo

#define NIL_INT         -1
#define LIXO_STR        '$'

// registro de cabeçalho do arquivo conectaPoPs (17 bytes)
typedef struct RegCab {
        char status;
        int32_t topoPilha;
        int32_t proxRRN;
        int32_t nroRegRem;
        int32_t nroPares;
} RegCab;

// índices do status

#define CAB_INCONSISTENTE       '0'
#define CAB_CONSISTENTE         '1'

// registro de dados (18 bytes)
typedef struct RegDados {
        char removido;
        int32_t encadeamentoPilha;
        int32_t idPoPs;
        int32_t idPoPsConectado;
        int32_t velocidade;
        int32_t unidadeMedida;
} RegDados;

// índice de remoção

#define REG_REMOVIDO    '0'
#define REG_MARCADO     '1'

// nomes dos campos do registro de dados
char *tabelaNomeCampo[] = {
        "idPoPs",
        "idPoPsConectado",
        "velocidade",
        "unidadeMedida"
};