#include <ctype.h>
#include <string.h>

#include "input.h"

// chama fgets num arquivo de texto e elimina caracteres como \r e \n
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

// implementação da função não-padronizada "strdup()" que duplica uma string
// EXIGE QUE SE CHAME free() APÓS USO
char *meu_strdup(char *str)
{
        size_t len = strlen(str);

        char *dup = malloc(sizeof(*str) * (len + 1));

        if (dup == NULL)
                return NULL;

        strncpy(dup, str, len);
        dup[len] = '\0';

        return dup;
}