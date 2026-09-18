#pragma once

// funcionalidade 1 da especificação
void comando_create(char *buffer, size_t length);

// funcionalidade 2 da especificação
void comando_ler(int codigo, char *buffer, int BUF_LEN);

//funcionalidade 4 da especificação
void comando_rrn(void);

// funcionalidade 3. 5 e 7 da especificação
void comando_busca(int codigo, char *buffer, size_t length);
