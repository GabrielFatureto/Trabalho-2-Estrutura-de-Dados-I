#include "unity.h"
#include "ordenacao.h"
#include "forma.h"
#include <stdlib.h>

int comparar_por_id(Forma a, Forma b) {
    int id_a = forma_get_id(a); 
    int id_b = forma_get_id(b);
    
    if (id_a < id_b) return -1;
    if (id_a > id_b) return 1;
    return 0;
}

void setUp(void) {}
void tearDown(void) {}

// =========================================================
// TESTES UNITÁRIOS
// =========================================================

void teste_bubble_sort(void) {
    Forma vetor[3];
    vetor[0] = criar_circulo(3, 10.0, 10.0, 5.0, "black", "red");
    vetor[1] = criar_circulo(1, 20.0, 20.0, 2.0, "black", "blue");
    vetor[2] = criar_circulo(2, 30.0, 30.0, 7.0, "black", "green");

    bubble_sort(vetor, 3, comparar_por_id);

    TEST_ASSERT_EQUAL_INT(1, forma_get_id(vetor[0]));
    TEST_ASSERT_EQUAL_INT(2, forma_get_id(vetor[1]));
    TEST_ASSERT_EQUAL_INT(3, forma_get_id(vetor[2]));

    for(int i = 0; i < 3; i++) liberar_forma(vetor[i]);
}

void teste_selection_sort(void) {
    Forma vetor[3];
    vetor[0] = criar_circulo(3, 10.0, 10.0, 5.0, "black", "red");
    vetor[1] = criar_circulo(1, 20.0, 20.0, 2.0, "black", "blue");
    vetor[2] = criar_circulo(2, 30.0, 30.0, 7.0, "black", "green");

    selection_sort(vetor, 3, comparar_por_id);

    TEST_ASSERT_EQUAL_INT(1, forma_get_id(vetor[0]));
    TEST_ASSERT_EQUAL_INT(2, forma_get_id(vetor[1]));
    TEST_ASSERT_EQUAL_INT(3, forma_get_id(vetor[2]));

    for(int i = 0; i < 3; i++) liberar_forma(vetor[i]);
}

void teste_insertion_sort(void) {
    Forma vetor[3];
    vetor[0] = criar_circulo(3, 10.0, 10.0, 5.0, "black", "red");
    vetor[1] = criar_circulo(1, 20.0, 20.0, 2.0, "black", "blue");
    vetor[2] = criar_circulo(2, 30.0, 30.0, 7.0, "black", "green");

    insertion_sort(vetor, 3, comparar_por_id);

    TEST_ASSERT_EQUAL_INT(1, forma_get_id(vetor[0]));
    TEST_ASSERT_EQUAL_INT(2, forma_get_id(vetor[1]));
    TEST_ASSERT_EQUAL_INT(3, forma_get_id(vetor[2]));

    for(int i = 0; i < 3; i++) liberar_forma(vetor[i]);
}

void teste_shell_sort(void) {
    Forma vetor[4];
    vetor[0] = criar_circulo(4, 10.0, 10.0, 5.0, "black", "red");
    vetor[1] = criar_circulo(2, 20.0, 20.0, 2.0, "black", "blue");
    vetor[2] = criar_circulo(1, 30.0, 30.0, 7.0, "black", "green");
    vetor[3] = criar_circulo(3, 40.0, 40.0, 1.0, "black", "yellow");

    shell_sort(vetor, 4, comparar_por_id);

    TEST_ASSERT_EQUAL_INT(1, forma_get_id(vetor[0]));
    TEST_ASSERT_EQUAL_INT(2, forma_get_id(vetor[1]));
    TEST_ASSERT_EQUAL_INT(3, forma_get_id(vetor[2]));
    TEST_ASSERT_EQUAL_INT(4, forma_get_id(vetor[3]));

    for(int i = 0; i < 4; i++) liberar_forma(vetor[i]);
}

void teste_quick_sort(void) {
    Forma vetor[4];
    vetor[0] = criar_circulo(4, 10.0, 10.0, 5.0, "black", "red");
    vetor[1] = criar_circulo(2, 20.0, 20.0, 2.0, "black", "blue");
    vetor[2] = criar_circulo(1, 30.0, 30.0, 7.0, "black", "green");
    vetor[3] = criar_circulo(3, 40.0, 40.0, 1.0, "black", "yellow");

    quick_sort(vetor, 0, 3, comparar_por_id);

    TEST_ASSERT_EQUAL_INT(1, forma_get_id(vetor[0]));
    TEST_ASSERT_EQUAL_INT(2, forma_get_id(vetor[1]));
    TEST_ASSERT_EQUAL_INT(3, forma_get_id(vetor[2]));
    TEST_ASSERT_EQUAL_INT(4, forma_get_id(vetor[3]));

    for(int i = 0; i < 4; i++) liberar_forma(vetor[i]);
}

void teste_merge_sort(void) {
    Forma vetor[4];
    vetor[0] = criar_circulo(4, 10.0, 10.0, 5.0, "black", "red");
    vetor[1] = criar_circulo(2, 20.0, 20.0, 2.0, "black", "blue");
    vetor[2] = criar_circulo(1, 30.0, 30.0, 7.0, "black", "green");
    vetor[3] = criar_circulo(3, 40.0, 40.0, 1.0, "black", "yellow");

    merge_sort(vetor, 0, 3, comparar_por_id);

    TEST_ASSERT_EQUAL_INT(1, forma_get_id(vetor[0]));
    TEST_ASSERT_EQUAL_INT(2, forma_get_id(vetor[1]));
    TEST_ASSERT_EQUAL_INT(3, forma_get_id(vetor[2]));
    TEST_ASSERT_EQUAL_INT(4, forma_get_id(vetor[3]));

    for(int i = 0; i < 4; i++) liberar_forma(vetor[i]);
}

// =========================================================
// MAIN
// =========================================================
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(teste_bubble_sort);
    RUN_TEST(teste_selection_sort);
    RUN_TEST(teste_insertion_sort);
    RUN_TEST(teste_shell_sort);
    RUN_TEST(teste_quick_sort);
    RUN_TEST(teste_merge_sort);
    
    return UNITY_END();
}