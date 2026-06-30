#include "svg.h"
#include <string.h>

FILE* svg_abrir(const char* caminho) {
    FILE* f = fopen(caminho, "w");
    if (f) {
        fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"2000\" height=\"2000\">\n");
    }
    return f;
}

void svg_desenhar_forma(FILE* svg, Forma f) {
    if (!svg || !f) return;

    TipoForma tipo = forma_get_tipo(f);
    int id = forma_get_id(f);
    double x = forma_get_x(f);
    double y = forma_get_y(f);
    const char* corb = forma_get_cor_borda(f);
    const char* corp = forma_get_cor_preenchimento(f);

    if (tipo == TIPO_CIRCULO) {
        double r = forma_get_raio(f);
        fprintf(svg, "  <circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"2\" />\n", id, x, y, r, corb, corp);
    } 
    else if (tipo == TIPO_RETANGULO) {
        double w = forma_get_largura(f);
        double h = forma_get_altura(f);
        fprintf(svg, "  <rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"2\" />\n", id, x, y, w, h, corb, corp);
    } 
    else if (tipo == TIPO_LINHA) {
        double x2 = forma_get_x2(f);
        double y2 = forma_get_y2(f);
        fprintf(svg, "  <line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n", id, x, y, x2, y2, corb);
    } 
    else if (tipo == TIPO_TEXTO) {
        const char* txt = forma_get_texto(f);
        const char* ff = forma_get_font_family(f);
        const char* fw = forma_get_font_weight(f);
        const char* fs = forma_get_font_size(f);
        fprintf(svg, "  <text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\">%s</text>\n", id, x, y, corb, corp, ff, fw, fs, txt);
    }
}

void svg_desenhar_retangulo_selecao(FILE* svg, double x, double y, double w, double h) {
    if (!svg) return;
    fprintf(svg, "  <rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill=\"none\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n", x, y, w, h);
}

void svg_fechar(FILE* svg) {
    if (svg) {
        fprintf(svg, "</svg>\n");
        fclose(svg);
    }
}