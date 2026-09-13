#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "filtro.h"
#include "input.h"

bool comparar_filtro(Filtro *filtro, RegDados *registro)
{
        // se é encontrada uma flag ativa cujo valor correspondente
        // é diferente do contido no registro, então retorna falso
        // do contrário, retorna verdadeiro

        FlagsBusca flags = filtro->flags;

        if (flags & FLAG_IDPOPS
            && filtro->idPoPs != registro->idPoPs)
                return false;

        if (flags & FLAG_IDPOPSCONECTADO
            && filtro->idPoPsConectado != registro->idPoPsConectado)
                return false;

        if (flags & FLAG_VELOCIDADE
            && filtro->velocidade != registro->velocidade)
                return false;

        if (flags & FLAG_UNIDADEMEDIDA
            && filtro->unidadeMedida != registro->unidadeMedida)
                return false;

        return true;
}

void parse_filtro(Filtro *filtro, char *buffer, size_t length)
{
        *filtro = (Filtro){
                .flags                  = FLAG_VAZIO,   // as flags são ativadas uma a uma no laço
                .idPoPs                 = NIL_INT,
                .idPoPsConectado        = NIL_INT,
                .velocidade             = NIL_INT
        };

        strncpy(&filtro->unidadeMedida, NIL_STR, 1);

        char *m_str = strtok(buffer, " ");
        int m = atoi(m_str);

        for (int i = 0; i < m; i++) {
                char *nomeCampo  = strtok(NULL, " ");
                char *valorCampo = strtok(NULL, " ");

                // compara o nome do campo com cada nome respectivo
                // e guarda a flag e o valor correspondente no filtro  

                if (strcmp(nomeCampo, "idPoPs") == 0) {
                        filtro->flags |= FLAG_IDPOPS;
                        filtro->idPoPs = ler_valor_inteiro(valorCampo);
                } else if (strcmp(nomeCampo, "idPoPsConectado") == 0) {
                        filtro->flags |= FLAG_IDPOPSCONECTADO;
                        filtro->idPoPsConectado = ler_valor_inteiro(valorCampo);
                } else if (strcmp(nomeCampo, "velocidade") == 0) {
                        filtro->flags |= FLAG_VELOCIDADE;
                        filtro->velocidade = ler_valor_inteiro(valorCampo);
                } else if (strcmp(nomeCampo, "unidadeMedida") == 0) {
                        filtro->flags |= FLAG_UNIDADEMEDIDA;
                        ler_valor_str(valorCampo, &filtro->unidadeMedida, 1);
                }
        }
}

void debug_filtro(Filtro *filtro)
{
        printf("=== FILTRO ===\n");
        printf("flags: %d\n", filtro->flags);
        printf("idPoPs: %" PRId32 "\n", filtro->idPoPs);
        printf("idPoPsConectado: %" PRId32 "\n", filtro->idPoPsConectado);
        printf("velocidade: %" PRId32 "\n", filtro->velocidade);
        printf("unidadeMedida: '%c'\n", filtro->unidadeMedida);
        printf("=============\n");
}