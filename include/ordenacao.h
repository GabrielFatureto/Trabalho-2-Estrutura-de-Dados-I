#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "forma.h"

/**
 * Ponteiro de função que define a nossa regra de comparação.
 * Em vez de engessar o código, passamos essa função para que o algoritmo 
 * saiba quem deve vir primeiro no vetor com base no critério escolhido (área, altura, etc).
 * * Retorna:
 * < 0 : Se 'a' deve vir antes de 'b'
 * 0 : Se 'a' e 'b' são equivalentes para a ordenação
 * > 0 : Se 'a' deve vir depois de 'b'
 */
typedef int (*ComparaForma)(Forma a, Forma b);


/* =========================================================================
 * ALGORITMOS QUADRÁTICOS O(n²)
 * Ideais para vetores pequenos, simples de entender, mas sofrem com muitos dados.
 * ========================================================================= */

/**
 * Compara vizinho com vizinho e vai empurrando o maior elemento para o final,
 * como se fosse uma bolha subindo até a superfície.
 */
void bubble_sort(Forma vetor[], int n, ComparaForma cmp);

/**
 * Passa pelo vetor procurando o menor elemento de todos e o coloca na primeira posição.
 * Depois, procura o segundo menor e coloca na segunda posição, e assim por diante.
 */
void selection_sort(Forma vetor[], int n, ComparaForma cmp);

/**
 * Funciona como se você estivesse organizando cartas de baralho na mão:
 * pega uma forma por vez e a insere na posição correta comparando com as que já organizou.
 */
void insertion_sort(Forma vetor[], int n, ComparaForma cmp);


/* =========================================================================
 * ALGORITMOS AVANÇADOS / INTERMEDIÁRIOS
 * Estruturas focadas em performance para quando o volume de dados é gigante.
 * ========================================================================= */

/**
 * Uma evolução do Insertion Sort que quebra o vetor em "subvetores" menores
 * usando saltos (gaps), deixando o vetor quase ordenado antes do passe final.
 */
void shell_sort(Forma vetor[], int n, ComparaForma cmp);

/**
 * Escolhe um elemento como "pivô" e joga todo mundo que é menor que ele para a esquerda,
 * e quem é maior para a direita. Depois, faz o mesmo processo recursivamente nas duas metades.
 */
void quick_sort(Forma vetor[], int inicio, int fim, ComparaForma cmp);

/**
 * Divide o vetor ao meio repetidamente até ficarem blocos de 1 único elemento.
 * Depois, vai juntando (intercalando) esses blocos de forma ordenada usando memória extra.
 */
void merge_sort(Forma vetor[], int inicio, int fim, ComparaForma cmp);

#endif /* ORDENACAO_H */