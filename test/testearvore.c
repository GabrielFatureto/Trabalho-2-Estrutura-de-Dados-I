#include "unity.h"
#include "arvore.h"
#include "forma.h"

static int contador_visita;
static int ids_esperados[4];

void setUp(void) {
    contador_visita = 0;
}

void tearDown(void) {
    /* Executado apos cada teste */
}

/* Funcao de callback para validar a ordem dos elementos no percurso */
static void checar_ordem_visita(Forma f, void* aux) {
    (void)aux;

    int id = forma_get_id(f);
    TEST_ASSERT_EQUAL_INT(ids_esperados[contador_visita], id);
    contador_visita++;
}

void teste_insercao_e_ordenacao_arvore(void) {
    Arvore a = criar_arvore();
    TEST_ASSERT_NOT_NULL(a);

    /* Elementos criados estrategicamente para validar os criterios de desempate */
    Forma f1 = criar_retangulo(10, 0.0, 50.0, 10.0, 10.0, "black", "white"); /* Raiz: Y = 50 */
    Forma f2 = criar_retangulo(20, 0.0, 10.0, 10.0, 10.0, "black", "white"); /* Y = 10, X = 0 */
    Forma f3 = criar_retangulo(30, 5.0, 10.0, 10.0, 10.0, "black", "white"); /* Y = 10, X = 5 */
    Forma f4 = criar_retangulo(40, 5.0, 10.0, 5.0, 5.0, "black", "white");   /* Y = 10, X = 5, Area menor */

    /* Insere na arvore */
    arvore_inserir(a, f1);
    arvore_inserir(a, f2);
    arvore_inserir(a, f3);
    arvore_inserir(a, f4);

    /* * Ordem crescente real dos criterios do edital (Y -> X -> Area):
     * 1. ID 20 (Y=10.0, X=0.0, Area=100.0)
     * 2. ID 40 (Y=10.0, X=5.0, Area=25.0)
     * 3. ID 30 (Y=10.0, X=5.0, Area=100.0)
     * 4. ID 10 (Y=50.0, X=0.0, Area=100.0)
     */
    ids_esperados[0] = 20;
    ids_esperados[1] = 40;
    ids_esperados[2] = 30;
    ids_esperados[3] = 10;

    arvore_percorrer_em_ordem(a, checar_ordem_visita, NULL);
    TEST_ASSERT_EQUAL_INT(4, contador_visita);

    /* Libera a memoria */
    liberar_arvore(a, 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_insercao_e_ordenacao_arvore);
    return UNITY_END();
}