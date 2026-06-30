#ifndef FORMA_H
#define FORMA_H

/**
 * Ponteiro genérico (opaco) que representa uma forma geométrica.
 * Esconde a struct real dentro do arquivo .c para garantir o encapsulamento (TAD).
 */
typedef void* Forma;

/**
 * Identificadores para os tipos de formas suportados pelo sistema.
 * Usado internamente para saber com qual estrutura estamos lidando na union.
 */
typedef enum {
    TIPO_CIRCULO,
    TIPO_RETANGULO,
    TIPO_LINHA,
    TIPO_TEXTO
} TipoForma;


/* =========================================================================
 * CONSTRUTORES
 * Alocam a memória necessária e inicializam as propriedades de cada figura.
 * ========================================================================= */

/**
 * Cria um círculo dinamicamente a partir do ID, centro (x, y), raio (r) e cores.
 */
Forma criar_circulo(int id, double x, double y, double r, const char* corb, const char* corp);

/**
 * Cria um retângulo dinamicamente a partir do ID, ponto superior esquerdo (x, y), largura (w), altura (h) e cores.
 */
Forma criar_retangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp);

/**
 * Cria uma linha reta ligando o ponto inicial (x1, y1) ao ponto final (x2, y2) com uma cor definida.
 */
Forma criar_linha(int id, double x1, double y1, double x2, double y2, const char* cor);

/**
 * Cria um elemento de texto dinamicamente contendo a string, configurações de fonte e ponto de ancoragem.
 */
Forma criar_texto(int id, double x, double y, const char* corb, const char* corp, char ancora, const char* txto, const char* fFamily, const char* fWeight, const char* fSize);


/* =========================================================================
 * GETTERS BÁSICOS
 * Recuperam os dados fundamentais compartilhados por praticamente todas as formas.
 * ========================================================================= */

/**
 * Retorna o identificador numérico único da forma.
 */
int forma_get_id(Forma f);

/**
 * Retorna o tipo de figura geométrica (Círculo, Retângulo, Linha ou Texto).
 */
TipoForma forma_get_tipo(Forma f);

/**
 * Retorna a coordenada X de referência da forma (centro, canto superior esquerdo ou início).
 */
double forma_get_x(Forma f);

/**
 * Retorna a coordenada Y de referência da forma (centro, canto superior esquerdo ou início).
 */
double forma_get_y(Forma f);

/**
 * Retorna um ponteiro para a string que guarda a cor de preenchimento da forma.
 */
const char* forma_get_cor_preenchimento(Forma f);

/**
 * Retorna um ponteiro para a string que guarda a cor da borda (ou cor da linha/texto).
 */
const char* forma_get_cor_borda(Forma f);


/* =========================================================================
 * GETTERS CALCULADOS
 * Propriedades abstratas cujos valores dependem da geometria específica de cada tipo.
 * ========================================================================= */

/**
 * Calcula e retorna a área ocupada pela forma com base nas regras do edital.
 */
double forma_get_area(Forma f);

/**
 * Calcula e retorna a largura total delimitadora ou comprimento da forma.
 */
double forma_get_largura(Forma f);

/**
 * Calcula e retorna a altura total delimitadora ou espessura conceitual da forma.
 */
double forma_get_altura(Forma f);


/* =========================================================================
 * GETTERS ESPECÍFICOS
 * Leitura de campos exclusivos de determinados tipos. Retornam zero ou vazio se incompatível.
 * ========================================================================= */

/**
 * Retorna o raio caso a forma seja um círculo.
 */
double forma_get_raio(Forma f);

/**
 * Retorna a coordenada X final caso a forma seja uma linha reta.
 */
double forma_get_x2(Forma f);

/**
 * Retorna a coordenada Y final caso a forma seja uma linha reta.
 */
double forma_get_y2(Forma f);

/**
 * Retorna o conteúdo textual bruto caso a forma seja um elemento de texto.
 */
const char* forma_get_texto(Forma f);

/**
 * Retorna a família tipográfica (ex: Arial, sans-serif) caso a forma seja um texto.
 */
const char* forma_get_font_family(Forma f);

/**
 * Retorna a estilização/peso da fonte (ex: bold, normal) caso a forma seja um texto.
 */
const char* forma_get_font_weight(Forma f);

/**
 * Retorna o tamanho da fonte (ex: 12px, 10pt) caso a forma seja um texto.
 */
const char* forma_get_font_size(Forma f);


/* =========================================================================
 * SETTERS
 * Modificadores para atualizar o estado e a posição dos elementos em memória.
 * ========================================================================= */

/**
 * Altera a coordenada X da forma, deslocando proporcionalmente seus sub-elementos se necessário.
 */
void forma_set_x(Forma f, double x);

/**
 * Altera a coordenada Y da forma, deslocando proporcionalmente seus sub-elementos se necessário.
 */
void forma_set_y(Forma f, double y);

/**
 * Substitui as strings de cor antigas por novos valores, liberando a memória anterior.
 */
void forma_set_cores(Forma f, const char* corb, const char* corp);


/* =========================================================================
 * DESTRUTOR
 * ========================================================================= */

/**
 * Libera recursivamente toda a memória alocada para as strings internas e para a struct da forma.
 */
void liberar_forma(Forma f);

#endif /* FORMA_H */