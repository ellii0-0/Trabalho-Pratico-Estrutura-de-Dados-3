#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "registros.h"

// chama fgets num arquivo de texto e elimina caracteres como \r e \n
char *fgets_limpo(char *buffer, size_t length, FILE *stream);

// implementação da função não-padronizada "strdup()" que duplica uma string
// EXIGE QUE SE CHAME free() APÓS USO
char *meu_strdup(char *str);

// lê um valor inteiro (checa nulo)
int32_t ler_valor_inteiro(char *buffer);

// lê uma string (checa nulo)
char *ler_valor_str(char *buffer, char *dest, size_t dest_length);

// verifica se um token é "NULO" (case-insensitive)
bool token_nulo(char *token);