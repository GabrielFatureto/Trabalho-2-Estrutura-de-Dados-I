#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "forma.h"

int ler_arquivo_geo(const char* caminho_geo, Arvore arvore) {
    FILE* arquivo = fopen(caminho_geo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo .geo: %s\n", caminho_geo);
        return 0;
    }

    char comando[10];
    
    // Variáveis padrão para fontes de texto caso o comando 'ts' mude o estilo 
    char fFamily[50] = "sans";
    char fWeight[50] = "n";
    char fSize[50] = "12px";

    while (fscanf(arquivo, "%s", comando) != EOF) {
        if (strcmp(comando, "c") == 0) {
            int id; double x, y, r; char corb[50], corp[50];
            fscanf(arquivo, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
            Forma f = criar_circulo(id, x, y, r, corb, corp);
            arvore_inserir(arvore, f);
            
        } else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; char corb[50], corp[50];
            fscanf(arquivo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            Forma f = criar_retangulo(id, x, y, w, h, corb, corp);
            arvore_inserir(arvore, f);
            
        } else if (strcmp(comando, "l") == 0 || strcmp(comando, "1") == 0) { 
            // Tratando 'l' ou '1' devido a possíveis variações de OCR do edital 
            int id; double x1, y1, x2, y2; char cor[50];
            fscanf(arquivo, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);
            Forma f = criar_linha(id, x1, y1, x2, y2, cor);
            arvore_inserir(arvore, f);
            
        } else if (strcmp(comando, "ts") == 0) {
            fscanf(arquivo, "%s %s %s", fFamily, fWeight, fSize);
            
        } else if (strcmp(comando, "t") == 0) {
            int id; double x, y; char corb[50], corp[50], ancora;
            char txto[256];
            
            fscanf(arquivo, "%d %lf %lf %s %s %c", &id, &x, &y, corb, corp, &ancora);
            
            // Lê o resto da linha para pegar o texto completo (que pode ter espaços) 
            fgets(txto, sizeof(txto), arquivo);
            
            // Remove a quebra de linha do final se existir
            txto[strcspn(txto, "\r\n")] = 0;
            
            // Remove espaços extras do começo do texto capturado pelo fgets
            char* txto_limpo = txto;
            while (*txto_limpo == ' ' || *txto_limpo == '\t') txto_limpo++;

            Forma f = criar_texto(id, x, y, corb, corp, ancora, txto_limpo, fFamily, fWeight, fSize);
            arvore_inserir(arvore, f);
        }
    }

    fclose(arquivo);
    return 1;
}