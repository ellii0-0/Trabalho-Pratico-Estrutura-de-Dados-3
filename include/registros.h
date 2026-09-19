// header que define as structs do cabeçalho, do registro de dados e valores nulos

#pragma once

#include <inttypes.h>

#include "filtro.h"

#include <stdio.h>

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

// escreve o registro campo a campo
void escrever_registro(FILE *bin, RegDados *registro);

// escreve o cabeçalho no arquivo binário campo a campo
void escrever_cabecalho(FILE *bin, RegCab *cabecalho);

// remove um registro no RRN especificado
// ATENÇÃO: ESSA FUNÇÃO CHAMA FSEEK AO BYTEOFFSET DO RRN
void remover_registro(FILE *bin, RegCab *cabecalho, int32_t RRN);


// arquivo binário

// abrir arquivo binário vazio (wb)
FILE *abrir_binario_novo(char *caminho, RegCab *cabecalho);

// abrir arquivo binário (marcando ou não o cabeçalho, rb ou rb+)
FILE *abrir_binario(char *caminho, RegCab *cabecalho, bool marcar);

// fechar arquivo binário (escrevendo o cabeçalho)
int fechar_binario(FILE *bin, RegCab *cabecalho, bool marcar);

//insere registro no binario
bool inserir_registro(FILE *bin, RegCab *cabecalho, RegDados *registro);

// funções de leitura do arquivo binário

// lê do disco um registro campo a campo
void ler_registro(FILE *bin, RegDados *registro);

// lê do disco o cabeçalho campo a campo
void ler_cabecalho(FILE *bin, RegCab *cabecalho);

// funções de filtro

// atualiza um registro conforme um filtro
void atualizar_registro(Filtro *mudancas, RegDados *registro);

// compara os campos marcados nas flagos do filtro com um registro de dados
bool filtrar_registro(Filtro *filtro, RegDados *registro);