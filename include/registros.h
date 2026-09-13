// header que define as structs do cabeçalho, do registro de dados e valores nulos

#pragma once

#include <inttypes.h>

// valores nulos e lixo

#define NIL_INT         -1
<<<<<<< HEAD
#define NIL_STR         ""

#define LIXO_STR        '$'

// registro de cabeçalho do arquivo conectaPoPs (17 bytes)
=======
#define LIXO_STR        '$'

// registro de cabeçalho do arquivo conectaPoPs (17 bytes)

>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b
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

<<<<<<< HEAD
// índices de remoção
=======
// índice de remoção
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b

#define REG_REMOVIDO    '1'
#define REG_EM_USO      '0'

<<<<<<< HEAD
// printa registro na tela conforme especificado
void printa_registro(RegDados *registro);

// funções de escrita do arquivo binário

void escrever_registro(FILE *bin, RegDados *registro);
void escrever_cabecalho(FILE *bin, RegCab *cabecalho);

// funções de leitura do arquivo binário

void ler_registro(FILE *bin, RegDados *registro);
void ler_cabecalho(FILE *bin, RegCab *cabecalho);
=======
// nomes dos campos do registro de dados
extern char *tabelaNomeCampo[];

// funções auxiliares

void escrever_registro(FILE *bin, RegDados *registro);
void escrever_cabecalho(FILE *bin, RegCab *cabecalho);
>>>>>>> fd6c626a55b425953831a1291fe3de674d3ff41b
