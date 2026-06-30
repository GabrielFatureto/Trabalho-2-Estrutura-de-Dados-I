# =========================================================
# Makefile - Projeto Completo (Estrutura de Dados 1)
# =========================================================

CC = gcc

# Nome do executável final do programa (mude se o edital pedir outro nome)
EXEC = siguel

# CFLAGS atualizado com as pastas de inclusão e a flag de proteção de pilha do edital
CFLAGS = -std=c99 -Wall -Wextra -g -fstack-protector-all -I./include -I./unity -DUNITY_INCLUDE_DOUBLE
LDFLAGS = -lm

OBJ_DIR = obj

# Lista de todos os objetos necessários para o programa final
PRINCIPAIS_OBJS = $(OBJ_DIR)/main.o \
                  $(OBJ_DIR)/arvore.o \
                  $(OBJ_DIR)/forma.o \
                  $(OBJ_DIR)/geo.o \
                  $(OBJ_DIR)/ordenacao.o \
                  $(OBJ_DIR)/qry.o \
                  $(OBJ_DIR)/svg.o

# =========================================================
# ALVOS PRINCIPAIS
# =========================================================

# O comando "make" sozinho agora vai compilar o programa final
all: cria_pastas $(EXEC)

cria_pastas:
	@mkdir -p $(OBJ_DIR)

# Alvo que linka todos os objetos e gera o executável final
$(EXEC): $(PRINCIPAIS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# =========================================================
# COMPILAÇÃO DOS OBJETOS (.o)
# =========================================================

$(OBJ_DIR)/unity.o: unity/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/forma.o: src/forma.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/arvore.o: src/arvore.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/ordenacao.o: src/ordenacao.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/geo.o: src/geo.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/qry.o: src/qry.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/svg.o: src/svg.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================================================
# TESTES UNITÁRIOS (Framework Unity)
# =========================================================

test_forma: cria_pastas $(OBJ_DIR)/unity.o $(OBJ_DIR)/forma.o
	$(CC) $(CFLAGS) test/testeforma.c $(OBJ_DIR)/forma.o $(OBJ_DIR)/unity.o -o $(OBJ_DIR)/testeforma $(LDFLAGS)
	./$(OBJ_DIR)/testeforma

test_arvore: cria_pastas $(OBJ_DIR)/unity.o $(OBJ_DIR)/forma.o $(OBJ_DIR)/arvore.o
	$(CC) $(CFLAGS) test/testearvore.c $(OBJ_DIR)/arvore.o $(OBJ_DIR)/forma.o $(OBJ_DIR)/unity.o -o $(OBJ_DIR)/testearvore $(LDFLAGS)
	./$(OBJ_DIR)/testearvore

test_ordenacao: cria_pastas $(OBJ_DIR)/unity.o $(OBJ_DIR)/forma.o $(OBJ_DIR)/ordenacao.o
	$(CC) $(CFLAGS) test/testeordenacao.c $(OBJ_DIR)/ordenacao.o $(OBJ_DIR)/forma.o $(OBJ_DIR)/unity.o -o $(OBJ_DIR)/testeordenacao $(LDFLAGS)
	./$(OBJ_DIR)/testeordenacao

testes: test_forma test_arvore test_ordenacao

# =========================================================
# UTILITÁRIOS
# =========================================================

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all cria_pastas test_forma test_arvore test_ordenacao testes clean