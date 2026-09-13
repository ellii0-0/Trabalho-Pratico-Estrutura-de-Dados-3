// header que define as structs do cabeçalho, do registro de dados e valores nulos

#pragma once

#include <inttypes.h>

// valores nulos e lixo

#define NIL_INT         -1
#define NIL_STR         ""

#define LIXO_STR        '$'

// registro de cabeçalho do arquivo conectaPoPs (17 bytes)
typedef struct RegCab {
        char status;
        int32_t topoPilha;
        int32_t proxRRN;
        int32_t nroRegRem;
        int32_t nroPares;
} RegCab;

#define CAB_TAMANHO     17

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
        char unidadeMedida;
} RegDados;

#define REG_TAMANHO     18

// índices de remoção

#define REG_REMOVIDO    '1'
#define REG_EM_USO      '0'

// printa registro na tela conforme especificado
void printa_registro(RegDados *registro);

// funções de escrita do arquivo binário

void escrever_registro(FILE *bin, RegDados *registro);
void escrever_cabecalho(FILE *bin, RegCab *cabecalho);

void remover_registro(FILE *bin, RegCab *cabecalho, RegDados *registro, int32_t RRN);

// funções de leitura do arquivo binário

void ler_registro(FILE *bin, RegDados *registro);
void ler_cabecalho(FILE *bin, RegCab *cabecalho);
