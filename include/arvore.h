#ifndef ARVORE_H
#define ARVORE_H

#include "forma.h"

/* Tipo opaco para garantir o encapsulamento da árvore e dos nós */
typedef void* Arvore;

/* Aloca e inicializa uma árvore binária de busca vazia */
Arvore criar_arvore(void);

/* Insere uma forma na árvore utilizando os critérios: Y -> X -> Área */
void arvore_inserir(Arvore a, Forma f);

/* Percorre a árvore em-ordem e aplica a função 'visitar' em cada elemento */
void arvore_percorrer_em_ordem(Arvore a, void (*visitar)(Forma f, void* aux), void* aux);

/* Desaloca a memória da árvore. Se 'liberar_formas' for 1, desaloca também os elementos */
void liberar_arvore(Arvore a, int liberar_formas);

#endif /* ARVORE_H */