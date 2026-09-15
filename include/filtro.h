#pragma once

#include <inttypes.h>
#include <stdbool.h>

// flags de busca, cada bit representa um campo de comparação
typedef enum FlagsBusca {
        FLAG_VAZIO              = 0,
        FLAG_IDPOPS             = 1,
        FLAG_IDPOPSCONECTADO    = 2,
        FLAG_VELOCIDADE         = 4,
        FLAG_UNIDADEMEDIDA      = 8
} FlagsBusca;

// estrutura de filtro para buscas
typedef struct Filtro {
        FlagsBusca flags;

        int32_t idPoPs;
        int32_t idPoPsConectado;
        int32_t velocidade;
        char unidadeMedida;
} Filtro;

// lê os caracteres de entrada no formato especificado:
// m nomeCampo_1 valorCampo_1 nomeCampo_2 valorCampo_2 ... nomeCampo_m valorCampo_m
void parse_filtro(Filtro *filtro, char *buffer, size_t length);

// printa o filtro
void debug_filtro(Filtro *filtro);