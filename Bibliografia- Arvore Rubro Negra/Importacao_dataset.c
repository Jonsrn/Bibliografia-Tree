#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bibliografia.h"

#define MAX_PALAVRAS 1000
#define MAX_LEN 100

// Estrutura para armazenar palavras
typedef struct {
    char palavra_ingles[MAX_LEN];
    char palavras_portugues[MAX_PALAVRAS][MAX_LEN];
    int num_traducoes;
    int unidade;
} PalavraInfo;

PalavraInfo palavras_importadas[MAX_PALAVRAS];
int contador_palavras = 0;

// Função para adicionar a bibliografia em um vetor a partir de um arquivo
void adicionar_bibliografia(const char *filename, ArvRNPort *Raiz) {
    if(Raiz == NULL){    
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
            char *traducao = strtok(NULL, ";");

            if (palavra_ingles && traducao) {
                // Remove espaços em branco na palavra em inglês
                while (isspace((unsigned char)*palavra_ingles)) palavra_ingles++;
                char *end_ingles = palavra_ingles + strlen(palavra_ingles) - 1;
                while (end_ingles > palavra_ingles && isspace((unsigned char)*end_ingles)) end_ingles--;
                *(end_ingles + 1) = '\0';

                // Armazena a palavra em inglês no vetor
                strncpy(palavras_importadas[contador_palavras].palavra_ingles, palavra_ingles, MAX_LEN - 1);
                palavras_importadas[contador_palavras].palavra_ingles[MAX_LEN - 1] = '\0';
                palavras_importadas[contador_palavras].unidade = unidade_atual;

                // Faz uma cópia de 'traducao' antes de usar strtok
                char traducao_copia[512];
                strncpy(traducao_copia, traducao, sizeof(traducao_copia) - 1);
                traducao_copia[sizeof(traducao_copia) - 1] = '\0';

                // Divide as traduções em português por vírgula e processa cada uma
                char *palavra_portugues = strtok(traducao_copia, ",");
                palavras_importadas[contador_palavras].num_traducoes = 0;

                while (palavra_portugues) {
                    // Remove espaços em branco da palavra em português
                    while (isspace((unsigned char)*palavra_portugues)) palavra_portugues++;
                    char *end_pt = palavra_portugues + strlen(palavra_portugues) - 1;
                    while (end_pt > palavra_portugues && isspace((unsigned char)*end_pt)) end_pt--;
                    *(end_pt + 1) = '\0';

                    // Armazena a tradução em português no vetor
                    strncpy(palavras_importadas[contador_palavras].palavras_portugues[palavras_importadas[contador_palavras].num_traducoes], palavra_portugues, MAX_LEN - 1);
                    palavras_importadas[contador_palavras].palavras_portugues[palavras_importadas[contador_palavras].num_traducoes][MAX_LEN - 1] = '\0';

                    palavras_importadas[contador_palavras].num_traducoes++;
                    palavra_portugues = strtok(NULL, ",");
                }

                contador_palavras++;
            }
        }
        fclose(file);
    }else{
        printf("Dataset já preenchido\n"); 
    }    
}

//aqui ficará a função de inserção na lista. 

int inserir_lista_automatico(list_unid **Raiz, int unidade){
    int operacao; 
    operacao = 1; //1 significa que deu certo

    operacao =  inserir_na_Lista(Raiz, unidade); 

    imprimirLista(*Raiz); 

    if(operacao == 0){
       printf("Unidade já presente na lista\n");   
    }else if(operacao == 2){
        printf("A alocação do Nó na Lista falhou\n"); 
    }
   
   return operacao; //0 significa que o numero já existe na lista, 1 significa que deu certo e 2 que a alocação falhou
}

int inserir_ArvBB_Automatico(ArvBB_ing **Raiz, InfoBB Info, int unidade){
    int operacao; 
    operacao = 1; //1 indica sucesso 
    
    ArvBB_ing *no_existente; 
    no_existente = NULL; //Isso daqui serve para após inserir, ter acesso ao endereço do Nó, pra inserções subsequentes em sua sublista

    operacao = inserir_ArvBB_Ingles(Raiz, Info, &no_existente); 
    
    imprimiArvBB(*Raiz); 
    
    printf("Imprimindo lista da palavra: %s\n", (*Raiz)->info.palavra_ingles); 
    //Nos retornos, 0 significa falhou totalmente (alocação), 1 significa que deu certo criar um novo nó e inseri-lo, e 2 significa que o Nó já existe. 
    //Independente se o Nó é novo ou antigo, o recuperamos, para poder fazer a inserção em sua lista

    if(operacao != 0){
        operacao = inserir_lista_automatico(&(no_existente->info.unidades), unidade); 
        //Nos retornos aqui, 0 significa que a alocação falhou, 1 que deu certo, e 2 que o número já existe nessa lista
    }else{
        printf("Falha na alocação do Nó da Arvore Binária\n"); 
    }
    

    return operacao; 

}






int inserir_ArvRN_Automatico(ArvRNPort **Raiz, InfArvRN Info, int unidade, InfoBB Info_ingles){
    int operacao; 
    operacao = 1; //1 significa sucesso 
    int situacao; 
    situacao = 1; 
    
    ArvRNPort *no_referencia; 

    no_referencia = NULL; 

    situacao = inserir_ArvRN_Portugues(Raiz, Info, &no_referencia);
    atualizar_Raiz_ARVRN(Raiz); 
    //situacao, se for 0, é falha na alocação, se for 1 o novo nó foi criado e preenchido, se for 2

    if(situacao != 0){
        //Como inserimos com sucesso na árvore Rubro Negra, precisamos agr inserir a palavra 
        //precisamos saber em qual das infos está a palavra

        
        //A palavra em portugues está na info1 daquele Nó
        printf("Imprimindo a árvore Binária da palavra: %s\n", no_referencia->info.palavra_portugues); 
        operacao = inserir_ArvBB_Automatico((&(no_referencia)->info.significados_ingles), Info_ingles, unidade);
        //Nos retornos aqui, 0 significa que a alocação falhou, 1 que deu certo, e 2 que o número já existe nessa lista

        if(operacao == 0){
            //A inserção na árvore Binária falhou
            printf("Houve uma falha na inserção da palavra em inglês na Arvore BB\n"); 
        }

    }else{
        if(no_referencia == NULL){
            printf("A alocação do Nó da 2-3 falhou\n"); 
        }        
    }

    return operacao; 

} 


// Função para inserir as palavras do vetor na árvore 2-3 e nas subestruturas associadas
void inserir_palavras_no_dicionario(ArvRNPort **Raiz) {
    if (*Raiz == NULL) {
        for (int i = 0; i < contador_palavras; i++) {
            int unidade = palavras_importadas[i].unidade; // Unidade atual associada

            for (int j = 0; j < palavras_importadas[i].num_traducoes; j++) {
                // Obtém a palavra em inglês e suas traduções
                InfoBB info_ing;
                strncpy(info_ing.palavra_ingles, palavras_importadas[i].palavra_ingles, sizeof(info_ing.palavra_ingles) - 1);
                info_ing.palavra_ingles[sizeof(info_ing.palavra_ingles) - 1] = '\0';
                info_ing.unidades = NULL; // Inicializa a lista de unidades

                // Define a palavra em português
                InfArvRN info_port;
                strncpy(info_port.palavra_portugues, palavras_importadas[i].palavras_portugues[j], sizeof(info_port.palavra_portugues) - 1);
                info_port.palavra_portugues[sizeof(info_port.palavra_portugues) - 1] = '\0';
                info_port.significados_ingles = NULL; // Inicializa a árvore binária para significados em inglês

                // Insere a palavra em português com seu significado em inglês e unidade na árvore 2-3
                int resultado = inserir_ArvRN_Automatico(Raiz, info_port, unidade, info_ing);

                if (resultado == 0) {
                    printf("Erro ao inserir a palavra '%s' (significado em inglês: '%s') na árvore 2-3.\n",
                           info_port.palavra_portugues, info_ing.palavra_ingles);
                }
            }
        }
    } else {
        printf("Dataset já preenchido\n");
    }
}




