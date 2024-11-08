#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "bibliografia.h"

char *remover_acentos(char *str) {
    int i, j = 0;
    char temp[256]; // buffer temporário para a string processada

    for (i = 0; str[i]; i++) {
        char ch = tolower((unsigned char)str[i]); // Converte para minúscula
        
        // Remover acentos e caracteres especiais
        switch (ch) {
            case 'á': case 'à': case 'ã': case 'â': ch = 'a'; break;
            case 'é': case 'è': case 'ê': ch = 'e'; break;
            case 'í': case 'ì': case 'î': ch = 'i'; break;
            case 'ó': case 'ò': case 'õ': case 'ô': ch = 'o'; break;
            case 'ú': case 'ù': case 'û': ch = 'u'; break;
            case 'ç': ch = 'c'; break;
            // Adicione mais casos conforme necessário para remover outros acentos
            default:
                break;
        }
        
        if (isalpha(ch) || isspace(ch) || ch == ',' || ch == ':') { // Permite apenas letras, espaço, vírgulas e dois-pontos
            temp[j++] = ch;
        }
    }
    temp[j] = '\0'; // Termina a string
    strcpy(str, temp); // Copia a string processada de volta
    return str;
}


void adicionar_bibliografia(Arv23Port **Raiz, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int unidade_atual = 0;

    while (fgets(linha, sizeof(linha), file)) {
        // Remove o newline e espaços no final da linha
        linha[strcspn(linha, "\n")] = 0;

        // Detecta uma nova unidade
        if (linha[0] == '%') {
            sscanf(linha, "%% Unidade %d", &unidade_atual); // Captura o número da unidade
            continue;
        }

        // Processa a linha no formato: PalavraIngles: Traducoes
        char *palavra_ingles = strtok(linha, ":");
        char *traducao = strtok(NULL, ":");

        if (palavra_ingles && traducao) {
            // Remove acentos e converte para minúsculas
            remover_acentos(palavra_ingles);

            // Configura a estrutura para a palavra em inglês
            InfoBB info_ing;
            strcpy(info_ing.palavra_ingles, palavra_ingles);

            ArvBB_ing *no_ing_existente = NULL;
            int operacao_arvbb = 0;

            // Divide as traduções em português por vírgula e processa cada uma
            char *palavra_portugues = strtok(traducao, ",");
            while (palavra_portugues) {
                remover_acentos(palavra_portugues);

                // Configura estrutura para a palavra em português
                InfArv23 info_port;
                strcpy(info_port.palavra_portugues, palavra_portugues);

                // Variáveis para capturar o nó e posição na árvore 2-3
                int situacao_arv23 = 0, info_posicao = 0;
                Arv23Port *no_port_existente = NULL;

                // Insere na árvore 2-3
                insereArv23(Raiz, info_port, NULL, NULL, &situacao_arv23, &info_posicao, &no_port_existente);

                if (situacao_arv23 == 1 || situacao_arv23 == 2) {
                    // Insere ou encontra a palavra em inglês na árvore binária associada
                    if(info_posicao == 1){
                        // A palavra está na Info1 da Arv2-3
                           operacao_arvbb = inserir_ArvBB_Ingles(&(no_port_existente->info1.significados_ingles), info_ing, &no_ing_existente);
                    }else{
                        //A palavra está na Info2 da Arv 2-3
                        operacao_arvbb = inserir_ArvBB_Ingles(&(no_port_existente->info2.significados_ingles), info_ing, &no_ing_existente); 
                    }       
                    
                    if (operacao_arvbb == 1 || operacao_arvbb == 2) {
                        // Insere a unidade na lista encadeada dentro do nó da palavra em inglês
                        int operacao_lista = inserir_na_Lista(&no_ing_existente->unidades, unidade_atual);
                        if (operacao_lista == 0) {
                            printf("Unidade %d já está presente para a palavra '%s' em inglês.\n", unidade_atual, palavra_ingles);
                        }
                    }
                }
                
                // Próxima tradução
                palavra_portugues = strtok(NULL, ",");
            }
        }
    }

    fclose(file);
}
