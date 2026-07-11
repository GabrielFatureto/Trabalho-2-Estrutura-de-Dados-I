CC = gcc

# O executável agora se chama "ted" e será gerado dentro da pasta src/
EXEC = ted

# Ajuste dos diretórios de include (agora usamos ../ para voltar para a raiz)
CFLAGS = -std=c99 -Wall -Wextra -g -fstack-protector-all -I../include -I../unity -DUNITY_INCLUDE_DOUBLE
LDFLAGS = -lm

# A pasta obj vai continuar sendo criada na raiz do projeto
OBJ_DIR = ../obj

PRINCIPAIS_OBJS = $(OBJ_DIR)/main.o \
                  $(OBJ_DIR)/arvore.o \
                  $(OBJ_DIR)/forma.o \
                  $(OBJ_DIR)/geo.o \
                  $(OBJ_DIR)/ordenacao.o \
                  $(OBJ_DIR)/qry.o \
                  $(OBJ_DIR)/svg.o

# O comando 'all' também garantirá que tudo funcione caso você só digite 'make'
all: cria_pastas $(EXEC)

cria_pastas:
	@mkdir -p $(OBJ_DIR)

# Como a variável EXEC se chama 'ted', esta regra resolve o "make ted" do professor!
$(EXEC): cria_pastas $(PRINCIPAIS_OBJS)
	$(CC) $(CFLAGS) $(PRINCIPAIS_OBJS) -o $@ $(LDFLAGS)

# ==========================================
# REGRAS DE COMPILAÇÃO (.c -> .o)
# Removido o "src/" da frente pois já estamos nele
# ==========================================

$(OBJ_DIR)/unity.o: ../unity/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/forma.o: forma.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/arvore.o: arvore.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/ordenacao.o: ordenacao.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/geo.o: geo.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/qry.o: qry.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/svg.o: svg.c
	$(CC) $(CFLAGS) -c $< -o $@

# ==========================================
# REGRAS DE TESTE
# Adicionado "../test/" nos caminhos e mantida a execução correta
# ==========================================

test_forma: cria_pastas $(OBJ_DIR)/unity.o $(OBJ_DIR)/forma.o
	$(CC) $(CFLAGS) ../test/testeforma.c $(OBJ_DIR)/forma.o $(OBJ_DIR)/unity.o -o $(OBJ_DIR)/testeforma $(LDFLAGS)
	$(OBJ_DIR)/testeforma

test_arvore: cria_pastas $(OBJ_DIR)/unity.o $(OBJ_DIR)/forma.o $(OBJ_DIR)/arvore.o
	$(CC) $(CFLAGS) ../test/testearvore.c $(OBJ_DIR)/arvore.o $(OBJ_DIR)/forma.o $(OBJ_DIR)/unity.o -o $(OBJ_DIR)/testearvore $(LDFLAGS)
	$(OBJ_DIR)/testearvore

test_ordenacao: cria_pastas $(OBJ_DIR)/unity.o $(OBJ_DIR)/forma.o $(OBJ_DIR)/ordenacao.o
	$(CC) $(CFLAGS) ../test/testeordenacao.c $(OBJ_DIR)/ordenacao.o $(OBJ_DIR)/forma.o $(OBJ_DIR)/unity.o -o $(OBJ_DIR)/testeordenacao $(LDFLAGS)
	$(OBJ_DIR)/testeordenacao

testes: test_forma test_arvore test_ordenacao

# ==========================================
# LIMPEZA
# ==========================================

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all cria_pastas test_forma test_arvore test_ordenacao testes clean