#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bibliografia.h"

unsigned long long calcular_valor_equivalente(const char *palavra) {
    unsigned long long valor = 0;
    unsigned long long fator = 1;  // Fator inicial para o peso do caractere

    for (int i = 0; palavra[i] != '\0'; i++) {
        valor += (unsigned char)palavra[i] * fator;
        fator *= 256;  // Multiplica o fator por 256 para aumentar o peso dos próximos caracteres
    }

    printf("calcular_valor_equivalente: Palavra '%s', valor equivalente %llu\n", palavra, valor);
    return valor;
}


void adicionar_bibliografia(Arv23Port **Raiz, const char *filename) {
    /*
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
            info_ing.valor_equivalente = calcular_valor_equivalente(info_ing.palavra_ingles); // Aplica a função para valor equivalente
            printf("Valor equivalente da palavra em inglês '%s' é %llu\n", info_ing.palavra_ingles, info_ing.valor_equivalente);

            // Variável para capturar o nó da palavra em inglês
            ArvBB_ing *no_ing_existente = NULL;

            // Divide as traduções em português por vírgula e processa cada uma
            char *palavra_portugues = strtok(traducao, ",");
            while (palavra_portugues) {
                printf("Processando tradução para o português: '%s'\n", palavra_portugues);
                // Remove espaços em branco no início e no final
                while (isspace((unsigned char)*palavra_portugues)) palavra_portugues++;
                char *end_pt = palavra_portugues + strlen(palavra_portugues) - 1;
                while (end_pt > palavra_portugues && isspace((unsigned char)*end_pt)) end_pt--;
                *(end_pt + 1) = '\0';

                // Configura estrutura para a palavra em português
                InfArv23 info_port;
                strncpy(info_port.palavra_portugues, palavra_portugues, sizeof(info_port.palavra_portugues) - 1);
                info_port.palavra_portugues[sizeof(info_port.palavra_portugues) - 1] = '\0';
                info_port.valor_equivalente = calcular_valor_equivalente(info_port.palavra_portugues);
                printf("Valor equivalente da palavra em português '%s' é %llu\n", info_port.palavra_portugues, info_port.valor_equivalente);
                // Variáveis para capturar o nó e posição na árvore 2-3
                int situacao_arv23 = 0, info_posicao = 0;
                Arv23Port *no_port_existente = NULL;
                InfArv23 promove; // Variável necessária para a função de inserção

                // Insere na árvore 2-3 usando o valor equivalente
                insereArv23(Raiz, info_port, &promove, NULL, &situacao_arv23, &info_posicao, &no_port_existente);

                if (situacao_arv23 == 1 || situacao_arv23 == 2) {
                    // Insere ou encontra a palavra em inglês na árvore binária associada
                    int operacao_arvbb = 0;

                    if (info_posicao == 1) {
                        // A palavra está na Info1 da Arv2-3
                        operacao_arvbb = inserir_ArvBB_Ingles(&(no_port_existente->info1.significados_ingles), info_ing, &no_ing_existente);
                    } else {
                        // A palavra está na Info2 da Arv2-3
                        operacao_arvbb = inserir_ArvBB_Ingles(&(no_port_existente->info2.significados_ingles), info_ing, &no_ing_existente);
                    }

                    if (operacao_arvbb == 1 || operacao_arvbb == 2) {
                        // Insere a unidade na lista encadeada dentro do nó da palavra em inglês
                        int operacao_lista = inserir_na_Lista(&no_ing_existente->unidades, unidade_atual);
                        if (operacao_lista == 0) {
                            // Unidade já existe, não é necessário fazer nada
                        }
                    }
                }

                // Próxima tradução
                palavra_portugues = strtok(NULL, ",");
            }
        }
    }

    fclose(file);
    */
}

