#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "registros.h"

// chama fgets num arquivo de texto e elimina caracteres como \r e \n
char *fgets_limpo(char *buffer, size_t length, FILE *stream);

// implementação da função não-padronizada "strdup()" que duplica uma string
// EXIGE QUE SE CHAME free() APÓS USO
char *meu_strdup(char *str);

// lê um valor inteiro passado para o filtro e retorna
// checa para o valor NULO (-1)
int32_t ler_valor_inteiro(char *buffer);

// copia uma string entre aspas de buffer a dest, assim como ScanQuoteString()
// sempre retorna o endereço dest passado
// CUIDADO: ESSA FUNÇÃO NÃO GARANTE QUE O NULO '\0' SEJA COPIADO
// SE FOR NECESSÁRIO, ELE DEVE SER INSERIDO MANUALMENTE
char *ler_valor_str(char *buffer, char *dest, size_t dest_length);

// verifica se um token é "NULO" (case-insensitive)
bool token_nulo(char *token);