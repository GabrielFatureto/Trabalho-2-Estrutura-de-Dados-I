#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "forma.h"

#define M_PI 3.14159265358979323846

typedef struct { double r; } CirculoData;
typedef struct { double w; double h; } RetanguloData;
typedef struct { double x2; double y2; } LinhaData;
typedef struct {
    char ancora; 
    char* txto; 
    char* fFamily; 
    char* fWeight; 
    char* fSize;
} TextoData;

/* Estrutura principal que implementa o ponteiro opaco Forma */
typedef struct {
    int id;
    TipoForma tipo;
    double x; 
    double y; 
    char* corb;
    char* corp;
    union {
        CirculoData circulo;
        RetanguloData retangulo;
        LinhaData linha;
        TextoData texto;
    } dados;
} FormaStruct;

/* Função auxiliar para clonar strings sem usar extensões não-C99 */
static char* duplicar_string(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char* clone = (char*)malloc(len);
    if (clone) memcpy(clone, s, len);
    return clone;
}

/* --- Construtores --- */

Forma criar_circulo(int id, double x, double y, double r, const char* corb, const char* corp) {
    FormaStruct* f = (FormaStruct*)malloc(sizeof(FormaStruct));
    if (!f) return NULL;
    f->id = id; f->tipo = TIPO_CIRCULO; f->x = x; f->y = y;
    f->corb = duplicar_string(corb); f->corp = duplicar_string(corp);
    f->dados.circulo.r = r;
    return (Forma)f;
}

Forma criar_retangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp) {
    FormaStruct* f = (FormaStruct*)malloc(sizeof(FormaStruct));
    if (!f) return NULL;
    f->id = id; f->tipo = TIPO_RETANGULO; f->x = x; f->y = y;
    f->corb = duplicar_string(corb); f->corp = duplicar_string(corp);
    f->dados.retangulo.w = w; f->dados.retangulo.h = h;
    return (Forma)f;
}

Forma criar_linha(int id, double x1, double y1, double x2, double y2, const char* cor) {
    FormaStruct* f = (FormaStruct*)malloc(sizeof(FormaStruct));
    if (!f) return NULL;
    f->id = id; f->tipo = TIPO_LINHA; f->x = x1; f->y = y1;
    f->corb = duplicar_string(cor); f->corp = duplicar_string(cor);
    f->dados.linha.x2 = x2; f->dados.linha.y2 = y2;
    return (Forma)f;
}

Forma criar_texto(int id, double x, double y, const char* corb, const char* corp, char ancora, const char* txto, const char* fFamily, const char* fWeight, const char* fSize) {
    FormaStruct* f = (FormaStruct*)malloc(sizeof(FormaStruct));
    if (!f) return NULL;
    f->id = id; f->tipo = TIPO_TEXTO; f->x = x; f->y = y;
    f->corb = duplicar_string(corb); f->corp = duplicar_string(corp);
    f->dados.texto.ancora = ancora;
    f->dados.texto.txto = duplicar_string(txto);
    f->dados.texto.fFamily = duplicar_string(fFamily);
    f->dados.texto.fWeight = duplicar_string(fWeight);
    f->dados.texto.fSize = duplicar_string(fSize);
    return (Forma)f;
}

/* --- Getters Básicos --- */

int forma_get_id(Forma f) { return ((FormaStruct*)f)->id; }
TipoForma forma_get_tipo(Forma f) { return ((FormaStruct*)f)->tipo; }
double forma_get_x(Forma f) { return ((FormaStruct*)f)->x; }
double forma_get_y(Forma f) { return ((FormaStruct*)f)->y; }
const char* forma_get_cor_preenchimento(Forma f) { return ((FormaStruct*)f)->corp; }
const char* forma_get_cor_borda(Forma f) { return ((FormaStruct*)f)->corb; }

/* --- Getters Calculados --- */

double forma_get_area(Forma f) {
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_CIRCULO) return M_PI * fs->dados.circulo.r * fs->dados.circulo.r;
    if (fs->tipo == TIPO_RETANGULO) return fs->dados.retangulo.w * fs->dados.retangulo.h;
    if (fs->tipo == TIPO_LINHA) return 1.5 * forma_get_largura(f);
    if (fs->tipo == TIPO_TEXTO) return 10.0 * strlen(fs->dados.texto.txto);
    return 0.0;
}

double forma_get_largura(Forma f) {
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_CIRCULO) return 2.0 * fs->dados.circulo.r;
    if (fs->tipo == TIPO_RETANGULO) return fs->dados.retangulo.w;
    if (fs->tipo == TIPO_LINHA) {
        double dx = fs->dados.linha.x2 - fs->x, dy = fs->dados.linha.y2 - fs->y;
        return sqrt(dx*dx + dy*dy);
    }
    if (fs->tipo == TIPO_TEXTO) return 1.0 * strlen(fs->dados.texto.txto);
    return 0.0;
}

double forma_get_altura(Forma f) {
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_CIRCULO) return 2.0 * fs->dados.circulo.r;
    if (fs->tipo == TIPO_RETANGULO) return fs->dados.retangulo.h;
    if (fs->tipo == TIPO_LINHA) return 1.5;
    if (fs->tipo == TIPO_TEXTO) return 10.0;
    return 0.0;
}

/* --- Setters --- */

void forma_set_x(Forma f, double x) {
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_LINHA) fs->dados.linha.x2 = x + (fs->dados.linha.x2 - fs->x);
    fs->x = x;
}

void forma_set_y(Forma f, double y) {
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_LINHA) fs->dados.linha.y2 = y + (fs->dados.linha.y2 - fs->y);
    fs->y = y;
}

void forma_set_cores(Forma f, const char* corb, const char* corp) {
    FormaStruct* fs = (FormaStruct*)f;
    free(fs->corb); free(fs->corp);
    fs->corb = duplicar_string(corb);
    fs->corp = duplicar_string(corp);
}

/* --- Destrutor --- */

void liberar_forma(Forma f) {
    if (!f) return;
    FormaStruct* fs = (FormaStruct*)f;
    free(fs->corb); free(fs->corp);
    if (fs->tipo == TIPO_TEXTO) {
        free(fs->dados.texto.txto); free(fs->dados.texto.fFamily);
        free(fs->dados.texto.fWeight); free(fs->dados.texto.fSize);
    }
    free(fs);
}

double forma_get_raio(Forma f) {
    if (!f) return 0.0;
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_CIRCULO) {
        return fs->dados.circulo.r;
    }
    return 0.0;
}

double forma_get_x2(Forma f) {
    if (!f) return 0.0;
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_LINHA) {
        return fs->dados.linha.x2;
    }
    return 0.0;
}

double forma_get_y2(Forma f) {
    if (!f) return 0.0;
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_LINHA) {
        return fs->dados.linha.y2;
    }
    return 0.0;
}

const char* forma_get_texto(Forma f) {
    if (!f) return "";
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_TEXTO) {
        return fs->dados.texto.txto;
    }
    return "";
}

const char* forma_get_font_family(Forma f) {
    if (!f) return "sans";
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_TEXTO) {
        return fs->dados.texto.fFamily;
    }
    return "sans";
}

const char* forma_get_font_weight(Forma f) {
    if (!f) return "normal";
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_TEXTO) {
        return fs->dados.texto.fWeight;
    }
    return "normal";
}

const char* forma_get_font_size(Forma f) {
    if (!f) return "12px";
    FormaStruct* fs = (FormaStruct*)f;
    if (fs->tipo == TIPO_TEXTO) {
        return fs->dados.texto.fSize;
    }
    return "12px";
}