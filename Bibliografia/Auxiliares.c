#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bibliografia.h"

// Função para adicionar a bibliografia a partir de um arquivo
void adicionar_bibliografia(Arv23Port **Raiz, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[512];
    int unidade_atual = 0;

    while (fgets(linha, sizeof(linha), file)) {
        // Remove o newline e espaços no final da linha
        linha[strcspn(linha, "\r\n")] = '\0';

        // Remove espaços em branco no início da linha
        char *linha_ptr = linha;
        while (isspace((unsigned char)*linha_ptr)) {
            linha_ptr++;
        }

        // Detecta uma nova unidade
        if (linha_ptr[0] == '%') {
            sscanf(linha_ptr, "%% Unidade %d", &unidade_atual); // Captura o número da unidade
            continue;
        }

        // Ignora linhas vazias
        if (strlen(linha_ptr) == 0) {
            continue;
        }

        // Processa a linha no formato: palavra_ingles: traducoes;
        char *palavra_ingles = strtok(linha_ptr, ":");
        char *traducao = strtok(NULL, ";"); // Considera ';' como delimitador final

        // Após verificar que 'palavra_ingles' e 'traducao' não são NULL
if (palavra_ingles && traducao) {
    printf("Processando palavra em inglês: '%s'\n", palavra_ingles);

    // Remove espaços em branco no início e no final da palavra em inglês
    while (isspace((unsigned char)*palavra_ingles)) palavra_ingles++;
    char *end_ingles = palavra_ingles + strlen(palavra_ingles) - 1;
    while (end_ingles > palavra_ingles && isspace((unsigned char)*end_ingles)) end_ingles--;
    *(end_ingles + 1) = '\0';

    // Configura a estrutura para a palavra em inglês
    InfoBB info_ing;
    strncpy(info_ing.palavra_ingles, palavra_ingles, sizeof(info_ing.palavra_ingles) - 1);
    info_ing.palavra_ingles[sizeof(info_ing.palavra_ingles) - 1] = '\0';
    info_ing.unidades = NULL; // Inicializa a lista de unidades como vazia

    // Variável para capturar o nó da palavra em inglês
    ArvBB_ing *no_ing_existente = NULL;

    // Faz uma cópia de 'traducao' antes de usar strtok
    char traducao_copia[512];
    strncpy(traducao_copia, traducao, sizeof(traducao_copia) - 1);
    traducao_copia[sizeof(traducao_copia) - 1] = '\0';

    // Divide as traduções em português por vírgula e processa cada uma
    char *palavra_portugues = strtok(traducao_copia, ",");
    while (palavra_portugues) {
        // Remove espaços em branco no início e no final da tradução em português
        while (isspace((unsigned char)*palavra_portugues)) palavra_portugues++;
        char *end_pt = palavra_portugues + strlen(palavra_portugues) - 1;
        while (end_pt > palavra_portugues && isspace((unsigned char)*end_pt)) end_pt--;
        *(end_pt + 1) = '\0';

        printf("Processando tradução para o português: '%s'\n", palavra_portugues);

        // O restante do código permanece o mesmo...

        // Próxima tradução
        palavra_portugues = strtok(NULL, ",");
    }
  }

    }
    fclose(file);
}

