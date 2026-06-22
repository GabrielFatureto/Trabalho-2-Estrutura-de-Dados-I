#ifndef FORMA_H
#define FORMA_H

/* Tipo opaco para garantir que as estruturas internas fiquem ocultas no .c */
typedef void* Forma;

typedef enum {
    TIPO_CIRCULO,
    TIPO_RETANGULO,
    TIPO_LINHA,
    TIPO_TEXTO
} TipoForma;

/* --- Construtores --- */
Forma criar_circulo(int id, double x, double y, double r, const char* corb, const char* corp);
Forma criar_retangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp);
Forma criar_linha(int id, double x1, double y1, double x2, double y2, const char* cor);
Forma criar_texto(int id, double x, double y, const char* corb, const char* corp, char ancora, const char* txto, const char* fFamily, const char* fWeight, const char* fSize);

/* --- Getters Básicos --- */
int forma_get_id(Forma f);
TipoForma forma_get_tipo(Forma f);
double forma_get_x(Forma f);
double forma_get_y(Forma f);
const char* forma_get_cor_preenchimento(Forma f);
const char* forma_get_cor_borda(Forma f);

/* --- Getters Calculados (Regras do edital) --- */
double forma_get_area(Forma f);
double forma_get_largura(Forma f);
double forma_get_altura(Forma f);

/* --- Setters --- */
void forma_set_x(Forma f, double x);
void forma_set_y(Forma f, double y);
void forma_set_cores(Forma f, const char* corb, const char* corp);

/* --- Destrutor --- */
void liberar_forma(Forma f);

#endif /* FORMA_H */