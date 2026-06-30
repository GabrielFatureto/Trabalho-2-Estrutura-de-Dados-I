#ifndef QRY_H
#define QRY_H

#include "arvore.h"

/* * Lê e processa o arquivo .qry.
 * Executa os comandos de seleção, ordenação (find/findrm) e modificação.
 * Gera os relatórios textuais (.txt) e visuais (.svg) conforme exigido.
 */
void processar_arquivo_qry(const char* caminho_qry, Arvore arvore, const char* bsd, const char* nome_base);

#endif