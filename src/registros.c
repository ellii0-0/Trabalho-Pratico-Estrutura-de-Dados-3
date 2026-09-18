#include <stdio.h>

#include <string.h>

#include "registros.h"

void printa_registro(RegDados *registro)
{
    if (registro == NULL)
        return;

    printf("%d %d ",
           registro->idPoPs,
           registro->idPoPsConectado);

    if (registro->velocidade == NIL_INT)
        printf("NULO ");
    else
        printf("%d ", registro->velocidade);

    if (registro->unidadeMedida == LIXO_STR)
        printf("NULO\n");
    else
        printf("\"%c\"\n", registro->unidadeMedida);
}

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

void remover_registro(FILE *bin, RegCab *cabecalho, int32_t RRN)
{
        RegDados registro;

        registro.removido = REG_REMOVIDO;
        registro.encadeamentoPilha = cabecalho->topoPilha;
                
        cabecalho->topoPilha = RRN;
        cabecalho->nroRegRem++;
        // cabecalho->nroPares--;

        // preenche os demais bytes do registro com lixo

        memset(
                &registro.idPoPs,
                LIXO_STR,
                sizeof(registro.idPoPs)
        );

        memset(
                &registro.idPoPsConectado,
                LIXO_STR,
                sizeof(registro.idPoPsConectado)
        );
                
        memset(
                &registro.velocidade,
                LIXO_STR,
                sizeof(registro.velocidade)
        );

        memset(
                &registro.unidadeMedida,
                LIXO_STR,
                sizeof(registro.unidadeMedida)
        );

        // escreve o registro em disco

        fseek(bin, CAB_TAMANHO + RRN * REG_TAMANHO, SEEK_SET);
        escrever_registro(bin, &registro);

}

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

void atualizar_registro(Filtro *mudancas, RegDados *registro)
{
        // os campos correspondentes a uma flag são alterados

        FlagsBusca flags = mudancas->flags;

        if (flags & FLAG_IDPOPS)
                registro->idPoPs = mudancas->idPoPs;

        if (flags & FLAG_IDPOPSCONECTADO)
                registro->idPoPsConectado = mudancas->idPoPsConectado;

        if (flags & FLAG_VELOCIDADE)
                registro->velocidade = mudancas->velocidade;

        if (flags & FLAG_UNIDADEMEDIDA)
                registro->unidadeMedida = mudancas->unidadeMedida; 
}

FILE *abrir_binario_novo(char *caminho, RegCab *cabecalho)
{
        FILE *bin = fopen(caminho, "wb");

        if (bin == NULL)
                return NULL;

        *cabecalho = (RegCab){
                .status = CAB_INCONSISTENTE,
                .topoPilha = NIL_INT,
                .proxRRN = 0,
                .nroRegRem = 0,
                .nroPares = 0
        };

        escrever_cabecalho(bin, cabecalho);

        return bin;
}

bool inserir_registro(FILE *bin, RegCab *cabecalho, RegDados *registro)
{
        int32_t RRN;

        if (cabecalho->topoPilha != NIL_INT) {
                RRN = cabecalho->topoPilha;

                if (fseek(bin, CAB_TAMANHO + RRN * REG_TAMANHO, SEEK_SET) != 0) 
                                                             // 67 ^  :D
                        return false;

                RegDados removido;
                ler_registro(bin, &removido);


                cabecalho->topoPilha = removido.encadeamentoPilha;
                cabecalho->nroRegRem--;
        } else {

                RRN = cabecalho->proxRRN;
                cabecalho->proxRRN++;
        }

        registro->removido = REG_EM_USO;
        registro->encadeamentoPilha = NIL_INT;

        if (fseek(bin, CAB_TAMANHO + (long)RRN * REG_TAMANHO,
                  SEEK_SET) != 0)
                return false;

        escrever_registro(bin, registro);

        return true;
}

bool filtrar_registro(Filtro *filtro, RegDados *registro)
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

FILE *abrir_binario(char *caminho, RegCab *cabecalho, bool marcar)
{
        FILE *bin = fopen(caminho, marcar ? "rb+" : "rb");

        if (bin == NULL)
                return NULL;

        *cabecalho = (RegCab){0};
        ler_cabecalho(bin, cabecalho);

        if (cabecalho->status != CAB_CONSISTENTE) {
                fclose(bin);
                return NULL;
        }

        if (marcar) {
                cabecalho->status = CAB_INCONSISTENTE;

                fseek(bin, 0, SEEK_SET);
                escrever_cabecalho(bin, cabecalho);

        }

        return bin;
}
int fechar_binario(FILE *bin, RegCab *cabecalho, bool marcar)
{
        if (marcar) {
                cabecalho->status = CAB_CONSISTENTE;

                fseek(bin, 0, SEEK_SET);
                escrever_cabecalho(bin, cabecalho);
        }

        return fclose(bin);
}