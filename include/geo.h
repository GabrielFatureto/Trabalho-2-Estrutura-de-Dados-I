#ifndef GEO_H
#define GEO_H

#include "arvore.h"

/* * Lê o arquivo .geo especificado, processa os comandos de criação de formas
 * (c, r, l, t, ts) e insere todas as figuras criadas na árvore fornecida.
 * Retorna 1 em caso de sucesso ou 0 se houver erro ao abrir o arquivo.
 */
int ler_arquivo_geo(const char* caminho_geo, Arvore arvore);

#endif