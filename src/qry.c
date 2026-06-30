#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "ordenacao.h"
#include "forma.h"
#include "svg.h"

// --- Funções de Comparação de Critérios ---
static int comparar_por_altura(Forma a, Forma b) {
    double h_a = forma_get_altura(a);
    double h_b = forma_get_altura(b);
    return (h_a < h_b) ? -1 : (h_a > h_b);
}

static int comparar_por_largura(Forma a, Forma b) {
    double w_a = forma_get_largura(a);
    double w_b = forma_get_largura(b);
    return (w_a < w_b) ? -1 : (w_a > w_b);
}

static int comparar_por_area(Forma a, Forma b) {
    double area_a = forma_get_area(a);
    double area_b = forma_get_area(b);
    return (area_a < area_b) ? -1 : (area_a > area_b);
}

static int comparar_por_cor(Forma a, Forma b) {
    return strcmp(forma_get_cor_borda(a), forma_get_cor_borda(b));
}

// Mapeia a sigla do algoritmo para a função correta
static void executar_ordenacao(const char* alg, Forma vetor[], int n, ComparaForma cmp) {
    if (strcmp(alg, "bs") == 0) bubble_sort(vetor, n, cmp);
    else if (strcmp(alg, "ss") == 0) selection_sort(vetor, n, cmp);
    else if (strcmp(alg, "is") == 0) insertion_sort(vetor, n, cmp);
    else if (strcmp(alg, "shs") == 0) shell_sort(vetor, n, cmp);
    else if (strcmp(alg, "qs") == 0) quick_sort(vetor, 0, n - 1, cmp);
    else if (strcmp(alg, "ms") == 0) merge_sort(vetor, 0, n - 1, cmp);
}

// Mapeia a sigla do critério para a função correta
static ComparaForma selecionar_criterio(const char* crit) {
    if (strcmp(crit, "h") == 0) return comparar_por_altura;
    if (strcmp(crit, "w") == 0) return comparar_por_largura;
    if (strcmp(crit, "a") == 0) return comparar_por_area;
    if (strcmp(crit, "c") == 0) return comparar_por_cor;
    return comparar_por_area; // Fallback seguro
}

// Verifica se o ponto de referência da forma está dentro do retângulo do 'sel'
static int ponto_dentro_retangulo(Forma f, double rx, double ry, double rw, double rh) {
    double fx = forma_get_x(f);
    double fy = forma_get_y(f);
    return (fx >= rx && fx <= rx + rw && fy >= ry && fy <= ry + rh);
}

void processar_arquivo_qry(const char* caminho_qry, Arvore arvore, const char* bsd, const char* nome_base) {
    FILE* qry = fopen(caminho_qry, "r");
    if (!qry) return;

    // Monta os caminhos dos relatórios de saída globais do qry
    char caminho_txt[512], caminho_svg[512];
    sprintf(caminho_txt, "%s/%s.txt", bsd, nome_base);
    sprintf(caminho_svg, "%s/%s.svg", bsd, nome_base);

    FILE* txt_relatorio = fopen(caminho_txt, "w");
    FILE* svg_final = svg_abrir(caminho_svg);

    // =========================================================
    // TRAVA DE SEGURANÇA CONTRA FALHA DE SEGMENTAÇÃO
    // =========================================================
    if (!txt_relatorio || !svg_final) {
        printf("\n[ERRO CRÍTICO] Não foi possível criar os arquivos de saída em: '%s'\n", bsd);
        printf("Verifique se o diretório existe ou se você tem permissão de escrita.\n\n");
        
        if (txt_relatorio) fclose(txt_relatorio);
        if (svg_final) svg_fechar(svg_final);
        fclose(qry);
        return;
    }

    // Primeiro, desenha o estado inicial completo da árvore no SVG final
    int total_nos_arvore = 0;
    Forma* todas_formas = arvore_para_vetor(arvore, &total_nos_arvore);
    if (todas_formas) {
        for (int i = 0; i < total_nos_arvore; i++) {
            svg_desenhar_forma(svg_final, todas_formas[i]);
        }
    }

    char comando[20];
    Forma* selecionados = NULL;
    int total_selecionados = 0;
    
    // Variáveis para guardar a última área de seleção desenhada
    double sel_x = 0, sel_y = 0, sel_w = 0, sel_h = 0;
    int tem_selecao = 0;

    while (fscanf(qry, "%s", comando) != EOF) {
        if (strcmp(comando, "sel") == 0) {
            fscanf(qry, "%lf %lf %lf %lf", &sel_x, &sel_y, &sel_w, &sel_h);
            tem_selecao = 1;

            if (selecionados) { free(selecionados); selecionados = NULL; }
            total_selecionados = 0;

            // Filtra os elementos da árvore que estão dentro da caixa de seleção
            if (total_nos_arvore > 0 && todas_formas) {
                selecionados = (Forma*)malloc(total_nos_arvore * sizeof(Forma));
                for (int i = 0; i < total_nos_arvore; i++) {
                    if (ponto_dentro_retangulo(todas_formas[i], sel_x, sel_y, sel_w, sel_h)) {
                        selecionados[total_selecionados++] = todas_formas[i];
                    }
                }
            }
            fprintf(txt_relatorio, "/* Comando sel: %d formas selecionadas dentro de (%lf, %lf) */\n", total_selecionados, sel_x, sel_y);
        } 
        else if (strcmp(comando, "find") == 0) {
            int k; char alg[10], crit[10]; double x, y, dw;
            fscanf(qry, "%d %s %s %lf %lf %lf", &k, alg, crit, &x, &y, &dw);

            fprintf(txt_relatorio, "Comando find %d %s %s:\n", k, alg, crit);

            if (total_selecionados > 0 && selecionados) {
                ComparaForma cmp = selecionar_criterio(crit);
                
                // Ordena o vetor de ponteiros selecionados usando o algoritmo lido
                executar_ordenacao(alg, selecionados, total_selecionados, cmp);

                // Modifica as posições das k primeiras formas ordenadas
                int limite = (k < total_selecionados) ? k : total_selecionados;
                for (int i = 0; i < limite; i++) {
                    double novo_x = x + (i * dw);
                    double novo_y = y;
                    
                    fprintf(txt_relatorio, "  - Forma ID %d antiga pos (%lf, %lf) -> Nova pos (%lf, %lf)\n", 
                            forma_get_id(selecionados[i]), forma_get_x(selecionados[i]), forma_get_y(selecionados[i]), novo_x, novo_y);
                    
                    // Altera fisicamente as coordenadas da forma na memória
                    forma_set_x(selecionados[i], novo_x);
                    forma_set_y(selecionados[i], novo_y);
                }
            } else {
                fprintf(txt_relatorio, "  Nenhuma forma estava selecionada para ordenacao.\n");
            }
        }
    }

    // Se houve comando 'sel', desenha o retângulo pontilhado no SVG final para documentação
    if (tem_selecao) {
        svg_desenhar_retangulo_selecao(svg_final, sel_x, sel_y, sel_w, sel_h);
    }

    // Redesenha as formas modificadas por cima para garantir a atualização visual
    if (todas_formas) {
        for (int i = 0; i < total_nos_arvore; i++) {
            svg_desenhar_forma(svg_final, todas_formas[i]);
        }
    }

    // Limpeza de memória local
    if (todas_formas) free(todas_formas);
    if (selecionados) free(selecionados);

    fclose(qry);
    fclose(txt_relatorio);
    svg_fechar(svg_final);
}