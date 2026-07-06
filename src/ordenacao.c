#include "ordenacao.h"
#include "forma.h"
#include "svg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// SISTEMA DE ANIMAÇÃO (FRAMES SVG)
// ==========================================
static int anim_ativo = 0;
static int anim_frame = 0;
static char anim_bsd[512];
static char anim_base[512];
static Forma* anim_todas = NULL;
static int anim_n_todas = 0;
static double anim_sel_x, anim_sel_y, anim_sel_w, anim_sel_h;
static int anim_tem_sel = 0;

static Forma* anim_selecionados = NULL;
static int anim_n_selecionados = 0;
static double anim_start_x, anim_start_y, anim_dw;

// Estrutura para fazer backup das posições originais
typedef struct {
    Forma f;
    double original_x;
    double original_y;
} BackupPosicao;
static BackupPosicao* backup_coords = NULL;

void init_animacao(const char* bsd, const char* base, 
                   Forma* todas, int n_todas, 
                   double rx, double ry, double rw, double rh, int tem_sel,
                   Forma* sel, int n_sel, double sx, double sy, double dw) {
    strcpy(anim_bsd, bsd);
    strcpy(anim_base, base);
    anim_todas = todas;
    anim_n_todas = n_todas;
    anim_sel_x = rx; anim_sel_y = ry; anim_sel_w = rw; anim_sel_h = rh;
    anim_tem_sel = tem_sel;
    
    anim_selecionados = sel;
    anim_n_selecionados = n_sel;
    anim_start_x = sx;
    anim_start_y = sy;
    anim_dw = dw;
    
    // Fazemos backup de onde cada forma selecionada estava antes de mexer
    backup_coords = (BackupPosicao*)malloc(n_sel * sizeof(BackupPosicao));
    for (int i = 0; i < n_sel; i++) {
        backup_coords[i].f = sel[i];
        backup_coords[i].original_x = forma_get_x(sel[i]);
        backup_coords[i].original_y = forma_get_y(sel[i]);
    }
    
    anim_frame = 0;
    anim_ativo = 1;
}

void finalizar_animacao() {
    if (!anim_ativo) return;
    anim_ativo = 0;
    
    // Devolve cada forma exatamente para sua coordenada de origem
    for (int i = 0; i < anim_n_selecionados; i++) {
        forma_set_x(backup_coords[i].f, backup_coords[i].original_x);
        forma_set_y(backup_coords[i].f, backup_coords[i].original_y);
    }
    free(backup_coords);
}

static void gerar_frame() {
    if (!anim_ativo) return;
    
    // Alinha temporariamente o vetor atual na tela para a foto
    for (int i = 0; i < anim_n_selecionados; i++) {
        forma_set_x(anim_selecionados[i], anim_start_x + (i * anim_dw));
        forma_set_y(anim_selecionados[i], anim_start_y);
    }

    char caminho[2048];
    snprintf(caminho, sizeof(caminho), "%s/%s-%03d.svg", anim_bsd, anim_base, anim_frame++);
    
    FILE* svg = svg_abrir(caminho);
    if (svg) {
        // Desenha todas as formas da árvore
        for (int i = 0; i < anim_n_todas; i++) {
            svg_desenhar_forma(svg, anim_todas[i]);
        }
        if (anim_tem_sel) {
            svg_desenhar_retangulo_selecao(svg, anim_sel_x, anim_sel_y, anim_sel_w, anim_sel_h);
        }
        svg_fechar(svg);
    }
}

// ==========================================
// FUNÇÕES DE ORDENAÇÃO
// ==========================================

// Função auxiliar para trocar duas formas de posição no vetor
static void trocar(Forma* a, Forma* b) {
    Forma temp = *a;
    *a = *b;
    *b = temp;
    gerar_frame();
}

// BUBBLE SORT
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

// SELECTION SORT
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

// INSERTION SORT
void insertion_sort(Forma vetor[], int n, ComparaForma cmp) {
    for (int i = 1; i < n; i++) {
        Forma chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && cmp(vetor[j], chave) > 0) {
            vetor[j + 1] = vetor[j];
            vetor[j] = chave; 
            gerar_frame();
            j--;
        }
        vetor[j + 1] = chave;
    }
}

// SHELL SORT
void shell_sort(Forma vetor[], int n, ComparaForma cmp) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Forma temp = vetor[i];
            int j;
            for (j = i; j >= gap && cmp(vetor[j - gap], temp) > 0; j -= gap) {
                vetor[j] = vetor[j - gap];
                vetor[j - gap] = temp;
                gerar_frame();
            }
            vetor[j] = temp;
        }
    }
}

// QUICK SORT
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

// MERGE SORT
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
        gerar_frame();
    }
    while (i < n1) { vetor[k++] = L[i++]; gerar_frame(); }
    while (j < n2) { vetor[k++] = R[j++]; gerar_frame(); }
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