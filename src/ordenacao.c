#include "ordenacao.h"
#include <stdlib.h>

// Função auxiliar para trocar duas formas de posição no vetor
static void trocar(Forma* a, Forma* b) {
    Forma temp = *a;
    *a = *b;
    *b = temp;
}

// ==========================================
// BUBBLE SORT
// ==========================================
void bubble_sort(Forma vetor[], int n, ComparaForma cmp) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (cmp(vetor[j], vetor[j + 1]) > 0) {
                trocar(&vetor[j], &vetor[j + 1]);
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
}

// ==========================================
// SELECTION SORT
// ==========================================
void selection_sort(Forma vetor[], int n, ComparaForma cmp) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (cmp(vetor[j], vetor[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            trocar(&vetor[i], &vetor[min_idx]);
        }
    }
}

// ==========================================
// INSERTION SORT
// ==========================================
void insertion_sort(Forma vetor[], int n, ComparaForma cmp) {
    for (int i = 1; i < n; i++) {
        Forma chave = vetor[i];
        int j = i - 1;
        
        // Desloca os elementos que são maiores que a chave
        while (j >= 0 && cmp(vetor[j], chave) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

// ==========================================
// SHELL SORT
// ==========================================
void shell_sort(Forma vetor[], int n, ComparaForma cmp) {
    // Começa com uma lacuna (gap) grande e vai reduzindo
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Faz um insertion sort para esta lacuna específica
        for (int i = gap; i < n; i++) {
            Forma temp = vetor[i];
            int j;
            for (j = i; j >= gap && cmp(vetor[j - gap], temp) > 0; j -= gap) {
                vetor[j] = vetor[j - gap];
            }
            vetor[j] = temp;
        }
    }
}

// ==========================================
// QUICK SORT
// ==========================================
static int particiona(Forma vetor[], int inicio, int fim, ComparaForma cmp) {
    Forma pivo = vetor[fim];
    int i = (inicio - 1);

    for (int j = inicio; j < fim; j++) {
        if (cmp(vetor[j], pivo) <= 0) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[i + 1], &vetor[fim]);
    return (i + 1);
}

void quick_sort(Forma vetor[], int inicio, int fim, ComparaForma cmp) {
    if (inicio < fim) {
        int pi = particiona(vetor, inicio, fim, cmp);
        quick_sort(vetor, inicio, pi - 1, cmp);
        quick_sort(vetor, pi + 1, fim, cmp);
    }
}

// ==========================================
// MERGE SORT
// ==========================================
static void intercalar(Forma vetor[], int inicio, int meio, int fim, ComparaForma cmp) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Forma* L = (Forma*) malloc(n1 * sizeof(Forma));
    Forma* R = (Forma*) malloc(n2 * sizeof(Forma));

    for (int i = 0; i < n1; i++) L[i] = vetor[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = vetor[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (cmp(L[i], R[j]) <= 0) {
            vetor[k++] = L[i++];
        } else {
            vetor[k++] = R[j++];
        }
    }

    while (i < n1) vetor[k++] = L[i++];
    while (j < n2) vetor[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(Forma vetor[], int inicio, int fim, ComparaForma cmp) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        merge_sort(vetor, inicio, meio, cmp);
        merge_sort(vetor, meio + 1, fim, cmp);
        intercalar(vetor, inicio, meio, fim, cmp);
    }
}