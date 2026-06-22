#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

/* Estrutura interna de cada nó da árvore */
typedef struct No {
    Forma forma;
    struct No* esquerda;
    struct No* direita;
} No;

/* Estrutura interna que serve como o descritor da árvore */
typedef struct {
    No* raiz;
} ArvoreStruct;

/* Função interna para comparar duas formas com base nos critérios do edital */
static int comparar_formas(Forma f1, Forma f2) {
    double y1 = forma_get_y(f1);
    double y2 = forma_get_y(f2);
    if (y1 != y2) {
        return (y1 < y2) ? -1 : 1;
    }

    /* Primeiro desempate: Coordenada X */
    double x1 = forma_get_x(f1);
    double x2 = forma_get_x(f2);
    if (x1 != x2) {
        return (x1 < x2) ? -1 : 1;
    }

    /* Segundo desempate: Área da figura */
    double a1 = forma_get_area(f1);
    double a2 = forma_get_area(f2);
    if (a1 != a2) {
        return (a1 < a2) ? -1 : 1;
    }

    return 0;
}

Arvore criar_arvore(void) {
    ArvoreStruct* a = (ArvoreStruct*)malloc(sizeof(ArvoreStruct));
    if (a) {
        a->raiz = NULL;
    }
    return (Arvore)a;
}

/* Função auxiliar recursiva para inserção de nós */
static No* inserir_recursivo(No* no, Forma f) {
    if (no == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        if (novo) {
            novo->forma = f;
            novo->esquerda = NULL;
            novo->direita = NULL;
        }
        return novo;
    }

    int comp = comparar_formas(f, no->forma);
    if (comp < 0) {
        no->esquerda = inserir_recursivo(no->esquerda, f);
    } else {
        no->direita = inserir_recursivo(no->direita, f);
    }

    return no;
}

void arvore_inserir(Arvore a, Forma f) {
    if (!a || !f) return;
    ArvoreStruct* as = (ArvoreStruct*)a;
    as->raiz = inserir_recursivo(as->raiz, f);
}

/* Função auxiliar recursiva para percurso em-ordem com callback */
static void percorrer_em_ordem_recursivo(No* no, void (*visitar)(Forma f, void* aux), void* aux) {
    if (no == NULL) return;
    percorrer_em_ordem_recursivo(no->esquerda, visitar, aux);
    visitar(no->forma, aux);
    percorrer_em_ordem_recursivo(no->direita, visitar, aux);
}

void arvore_percorrer_em_ordem(Arvore a, void (*visitar)(Forma f, void* aux), void* aux) {
    if (!a || !visitar) return;
    ArvoreStruct* as = (ArvoreStruct*)a;
    percorrer_em_ordem_recursivo(as->raiz, visitar, aux);
}

/* Função auxiliar recursiva para desalocação de memória */
static void liberar_no_recursivo(No* no, int liberar_formas) {
    if (no == NULL) return;
    liberar_no_recursivo(no->esquerda, liberar_formas);
    liberar_no_recursivo(no->direita, liberar_formas);
    if (liberar_formas) {
        liberar_forma(no->forma);
    }
    free(no);
}

void liberar_arvore(Arvore a, int liberar_formas) {
    if (!a) return;
    ArvoreStruct* as = (ArvoreStruct*)a;
    liberar_no_recursivo(as->raiz, liberar_formas);
    free(as);
}