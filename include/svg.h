#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "forma.h"

/* Abre um arquivo .svg pronto para escrita e adiciona a tag inicial */
FILE* svg_abrir(const char* caminho);

/* Traduz uma Forma opaca para a sua respectiva tag XML (<circle>, <rect>, etc.) */
void svg_desenhar_forma(FILE* svg, Forma f);

/* Desenha um retângulo vermelho tracejado para indicar a área do comando 'sel' */
void svg_desenhar_retangulo_selecao(FILE* svg, double x, double y, double w, double h);

/* Fecha a tag do arquivo e finaliza o ponteiro de escrita */
void svg_fechar(FILE* svg);

#endif