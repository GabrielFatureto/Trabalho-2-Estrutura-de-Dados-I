#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "forma.h"

/* * Ponteiro de função para comparar duas formas.
 * Deve retornar:
 * < 0 se a deve vir antes de b
 * 0 se forem iguais
 * > 0 se a deve vir depois de b
 */
typedef int (*ComparaForma)(Forma a, Forma b);

/* Algoritmos de ordenação O(n^2) */
void bubble_sort(Forma vetor[], int n, ComparaForma cmp);
void selection_sort(Forma vetor[], int n, ComparaForma cmp);

/* Algoritmos de ordenação O(n log n) */
void quick_sort(Forma vetor[], int inicio, int fim, ComparaForma cmp);
void merge_sort(Forma vetor[], int inicio, int fim, ComparaForma cmp);

#endif /* ORDENACAO_H */