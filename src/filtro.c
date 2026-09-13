#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "filtro.h"

// funções auxiliares

static int ler_valor_inteiro(char *buffer);
static char *ler_valor_str(char *buffer, char *dest, size_t dest_length);

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

// lê um valor inteiro passado para o filtro e retorna
// checa para o valor NULO (-1)
int ler_valor_inteiro(char *buffer)
{
        if (strcmp(buffer, "NULO") == 0)        // se o valor for marcado como nulo,
                return NIL_INT;                 // então retorna NIL_INT (-1)

        return atoi(buffer);                    // senão, retorna o valor inteiro da string
}

// copia uma string entre aspas de buffer a dest, assim como ScanQuoteString()
// sempre retorna o endereço dest passado
// CUIDADO: ESSA FUNÇÃO NÃO GARANTE QUE O NULO '\0' SEJA COPIADO
// SE FOR NECESSÁRIO, ELE DEVE SER INSERIDO MANUALMENTE
char *ler_valor_str(char *buffer, char *dest, size_t dest_length)
{
        char *p = buffer;

        while (*p != '\0' && isspace(*p))       // percorre o buffer até o primeiro caractere
                p++;                            // não-espaço ou até o seu fim

        if (*p == 'N' || *p == 'n') {                   // se o valor for marcado como nulo,
                strncpy(dest, NIL_STR, dest_length);    // escreve a NIL_STR ("") no destino

        } else if (*p == '\"') {                        // string iniciada em aspas
                p++;

                char *begin = p;        // começo da string a ser copiada
                size_t n = 0;           // número de caracteres

                while (*p != '\"' && *p != '\0' && n < dest_length) {     // avança até o fim das aspas
                        p++;                                            // ou o fim do buffer
                        n++;
                }

                if (*p != '\"')                                  // aspas "quebradas": copia NULO
                        strncpy(dest, NIL_STR, dest_length);
                else                                            // copia a string
                        strncpy(dest, begin, n);
                
        } else if (*p != '\0') {        // sem aspas: apenas copia o conteúdo do buffer
                char *begin = p;        // começo da string a ser copiada
                size_t n = 0;           // número de caracteres

                while (*p != '\0' && n < dest_length) {  // avança até o fim das aspas
                        p++;                            // ou o fim do buffer
                        n++;
                }

                strncpy(dest, begin, n);        // copia a string

        } else {                                        // string vazia: copia NULO
                strncpy(dest, NIL_STR, dest_length);
        }
        
        return dest;
}