#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para o getopt
#include "arvore.h"
#include "geo.h"
#include "qry.h"    // <-- Adicionado para o compilador conhecer o processar_arquivo_qry

int main(int argc, char* argv[]) {
    char* bed = NULL; // Diretório base de entrada 
    char* bsd = NULL; // Diretório base de saída 
    char* arq_geo = NULL; // Arquivo .geo 
    char* arq_qry = NULL; // Arquivo .qry (opcional) 
    
    int opt;
    // Processa os argumentos de linha de comando 
    while ((opt = getopt(argc, argv, "e:f:o:q:")) != -1) {
        switch (opt) {
            case 'e': bed = optarg; break;
            case 'f': arq_geo = optarg; break;
            case 'o': bsd = optarg; break;
            case 'q': arq_qry = optarg; break;
            default:
                fprintf(stderr, "Uso: %s -f arq.geo -o path [-e path] [-q arqcons.qry]\n", argv[0]);
                return 1;
        }
    }

    // Validação dos parâmetros obrigatórios 
    if (!arq_geo || !bsd) {
        fprintf(stderr, "Erro: Os parâmetros -f e -o são obrigatórios.\n");
        return 1;
    }

    // Monta o caminho completo do arquivo .geo (BED + arq_geo) 
    char caminho_geo[512] = "";
    if (bed) {
        sprintf(caminho_geo, "%s/%s", bed, arq_geo);
    } else {
        strcpy(caminho_geo, arq_geo);
    }

    // Inicializa nossa árvore binária de busca
    Arvore minha_arvore = criar_arvore();

    // Executa a leitura do arquivo .geo e popula a árvore
    if (!ler_arquivo_geo(caminho_geo, minha_arvore)) {
        liberar_arvore(minha_arvore, 1);
        return 1;
    }

    printf("Arquivo .geo processado com sucesso! Árvore populada.\n");

    // Se o usuário passou o parâmetro -q, processa as consultas do arquivo .qry
    if (arq_qry) {
        char caminho_qry[512] = "";
        if (bed) {
            sprintf(caminho_qry, "%s/%s", bed, arq_qry);
        } else {
            strcpy(caminho_qry, arq_qry);
        }
        
        // Executa a inteligência de ordenação, relatórios em texto e imagens .svg
        processar_arquivo_qry(caminho_qry, minha_arvore, bsd, arq_geo);
    }

    // Finalização segura limpando a memória das formas e da árvore
    liberar_arvore(minha_arvore, 1);
    return 0;
}