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

/* Função auxiliar interna para contar quantos nós existem na árvore */
static int contar_nos(No* no) {
    if (no == NULL) return 0;
    return 1 + contar_nos(no->esquerda) + contar_nos(no->direita);
}

/* Função auxiliar interna que viaja pela árvore preenchendo o vetor */
static void preencher_vetor_recursivo(No* no, Forma vetor[], int* indice_atual) {
    if (no == NULL) return;

    // Caminhamento em-ordem (Esquerda, Raiz, Direita)
    preencher_vetor_recursivo(no->esquerda, vetor, indice_atual);

    // Copia o ponteiro da forma para o vetor e avança o índice
    vetor[*indice_atual] = no->forma; 
    (*indice_atual)++;

    preencher_vetor_recursivo(no->direita, vetor, indice_atual);
}

/* Função pública que extrai os dados para um vetor dinâmico */
Forma* arvore_para_vetor(Arvore a, int* total_elementos) {
    if (a == NULL) {
        *total_elementos = 0;
        return NULL;
    }

    // Faz o cast (conversão) para acessar os dados internos da árvore
    ArvoreStruct* as = (ArvoreStruct*)a;
    
    // Descobre o tamanho exato necessário para o vetor
    *total_elementos = contar_nos(as->raiz); 
    
    if (*total_elementos == 0) return NULL;

    // Aloca o vetor dinâmico de ponteiros
    Forma* vetor = (Forma*) malloc((*total_elementos) * sizeof(Forma));
    if (vetor == NULL) {
        return NULL; // Prevenção em caso de falta de memória
    }

    int indice = 0;
    preencher_vetor_recursivo(as->raiz, vetor, &indice);

    return vetor;
}