#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "input.h"


char *fgets_limpo(char *buffer, size_t length, FILE *stream)
{
        char *p = fgets(buffer, length, stream);        // chama fgets normalmente

        if (p == NULL)                                  // se for nulo, retorna erro
                return NULL;

        while (isprint(*p))                             // avança até o primeiro caractere
                p++;                                    // não-imprimível

        *p = '\0';                                      // marca o fim da string

        return buffer;                                  // retorno padrão do fgets bem-sucedido
}

char *meu_strdup(char *str)
{
        if (str == NULL)
                return NULL;
        size_t len = strlen(str) + 1;

        char *dup = malloc(sizeof(*str) * len);

        if (dup == NULL)
                return NULL;

        strncpy(dup, str, len);

        return dup;
}

int32_t ler_valor_inteiro(char *buffer)
{
        if (token_nulo(buffer) || !isdigit(*buffer))    // se o valor for marcado como nulo,
                return NIL_INT;                         // ou não for numérico, retorna nulo

        return atoi(buffer);                    // senão, retorna o valor inteiro da string
}

char *ler_valor_str(char *buffer, char *dest, size_t dest_length)
{
        if (buffer == NULL || dest == NULL)
                return NULL;

        memset(dest, LIXO_STR, dest_length);
        char *p = buffer;

        while (*p != '\0' && isspace(*p))       // percorre o buffer até o primeiro caractere
                p++;                            // não-espaço ou até o seu fim

        if (token_nulo(p)) {                            // se o valor for marcado como nulo,
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

                while (*p != '\0' && n < dest_length) { // avança até o fim das aspas
                        p++;                            // ou o fim do buffer
                        n++;
                }

                strncpy(dest, begin, n);        // copia a string

        } else {                                        // string vazia: copia NULO
                strncpy(dest, NIL_STR, dest_length);
        }
        
        return dest;
}

bool token_nulo(char *token)
{
        if (token == NULL)
                return true;

        char *nulo = "NULO";

        for (size_t i = 0; i < 5; i++) {
                if (toupper(token[i]) != nulo[i])
                        return false;
        }

        return true;
}