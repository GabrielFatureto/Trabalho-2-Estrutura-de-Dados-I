#include "unity.h"
#include "forma.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void setUp(void) {
    /* Executado antes de cada teste */
}

void tearDown(void) {
    /* Executado apos cada teste */
}

void teste_criar_e_obter_dados_circulo(void) {
    Forma c = criar_circulo(1, 10.0, 20.0, 5.0, "red", "blue");
    
    TEST_ASSERT_NOT_NULL(c);
    TEST_ASSERT_EQUAL_INT(1, forma_get_id(c));
    TEST_ASSERT_EQUAL_INT(TIPO_CIRCULO, forma_get_tipo(c));
    TEST_ASSERT_EQUAL_DOUBLE(10.0, forma_get_x(c));
    TEST_ASSERT_EQUAL_DOUBLE(20.0, forma_get_y(c));
    TEST_ASSERT_EQUAL_STRING("red", forma_get_cor_borda(c));
    TEST_ASSERT_EQUAL_STRING("blue", forma_get_cor_preenchimento(c));
    
    TEST_ASSERT_DOUBLE_WITHIN(0.001, M_PI * 25.0, forma_get_area(c));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 10.0, forma_get_largura(c));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 10.0, forma_get_altura(c));

    liberar_forma(c);
}

void teste_criar_e_obter_dados_linha(void) {
    Forma l = criar_linha(2, 0.0, 0.0, 3.0, 4.0, "black");
    
    TEST_ASSERT_NOT_NULL(l);
    TEST_ASSERT_EQUAL_INT(2, forma_get_id(l));
    TEST_ASSERT_EQUAL_INT(TIPO_LINHA, forma_get_tipo(l));
    
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 5.0, forma_get_largura(l));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 1.5, forma_get_altura(l));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 1.5 * 5.0, forma_get_area(l));

    liberar_forma(l);
}

void teste_modificar_posicao_e_cor(void) {
    Forma r = criar_retangulo(3, 0.0, 0.0, 10.0, 10.0, "white", "black");
    
    forma_set_x(r, 15.0);
    forma_set_y(r, 25.0);
    forma_set_cores(r, "green", "yellow");

    TEST_ASSERT_EQUAL_DOUBLE(15.0, forma_get_x(r));
    TEST_ASSERT_EQUAL_DOUBLE(25.0, forma_get_y(r));
    TEST_ASSERT_EQUAL_STRING("green", forma_get_cor_borda(r));
    TEST_ASSERT_EQUAL_STRING("yellow", forma_get_cor_preenchimento(r));

    liberar_forma(r);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_criar_e_obter_dados_circulo);
    RUN_TEST(teste_criar_e_obter_dados_linha);
    RUN_TEST(teste_modificar_posicao_e_cor);
    return UNITY_END();
}