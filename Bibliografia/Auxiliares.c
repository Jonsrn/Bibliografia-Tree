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



void imprimiArvBB(ArvBB_ing *no) {
    if (no != NULL) {
        imprimiArvBB(no->esq);


        printf("%s\n", no->info.palavra_ingles);

        imprimiArvBB(no->dir);
    }
}
// Função para imprimir o vetor de palavras importadas
void imprimir_palavras_importadas() {
    for (int i = 0; i < contador_palavras; i++) {
        printf("Palavra em inglês: %s\n", palavras_importadas[i].palavra_ingles);
        printf("Traduções para o português:");
        printf("Numero de unidades: ");
        for (int j = 0; j < palavras_importadas[i].num_traducoes; j++) {
            printf(" %s", palavras_importadas[i].palavras_portugues[j]);
            if (j < palavras_importadas[i].num_traducoes - 1) {
                printf(",");
            }
        }
        printf("\n");
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






int inserir_Arv23_Automatico(Arv23Port **Raiz, InfArv23 Info, int unidade, InfoBB Info_ingles){
    int operacao; 
    operacao = 1; //1 significa sucesso 
    int situacao, info_posicao; 
    situacao = 1; 
    info_posicao = 0; 
    Arv23Port *no_referencia; 

    no_referencia = NULL; 

    insereArv23(Raiz, Info, NULL, NULL, &situacao, &info_posicao, &no_referencia); 

    //situacao, se for 0, é falha na alocação, se for 1 o novo nó foi criado e preenchido, se for 2

    if(situacao != 0){
        //Como inserimos com sucesso na árvore 2-3, precisamos agr inserir a palavra 
        //precisamos saber em qual das infos está a palavra

        if(info_posicao == 1){
            //A palavra em portugues está na info1 daquele Nó
            printf("Imprimindo a árvore Binária da palavra: %s\n", no_referencia->info1.palavra_portugues); 
             operacao = inserir_ArvBB_Automatico((&(no_referencia)->info1.significados_ingles), Info_ingles, unidade);
            //Nos retornos aqui, 0 significa que a alocação falhou, 1 que deu certo, e 2 que o número já existe nessa lista
        }
        if(info_posicao == 2){
            printf("Imprimindo a árvore Binária da palavra: %s\n", no_referencia->info2.palavra_portugues); 
            operacao = inserir_ArvBB_Automatico((&(no_referencia)->info2.significados_ingles), Info_ingles, unidade); 
            //Nos retornos aqui, 0 significa que a alocação falhou, 1 que deu certo, e 2 que o número já existe nessa lista
        }

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



void inserir_palavra_teste(Arv23Port **Raiz) {
    InfArv23 info_port;
    InfoBB info_ing;
    int unidade = 1; // Definindo uma unidade fixa para o teste

    // Define a palavra em português
    strncpy(info_port.palavra_portugues, "casa", MAX_LEN - 1);
    info_port.palavra_portugues[MAX_LEN - 1] = '\0';

    // Define um array de palavras em inglês para associar a "casa"
    char *traduzido_ingles[] = {"house", "home", "abode", "dwelling", "residence", "domicile", "habitat", "mansion", "hut", "lodge"};
    int num_traducoes = 10; // Definindo o número de traduções para o teste

    // Insere cada tradução em inglês associada à palavra em português "casa"
    for (int i = 0; i < num_traducoes; i++) {
        // Define a palavra em inglês atual
        strncpy(info_ing.palavra_ingles, traduzido_ingles[i], MAX_LEN - 1);
        info_ing.palavra_ingles[MAX_LEN - 1] = '\0';

        // Chama a função de inserção automática na árvore 2-3
        int resultado = inserir_Arv23_Automatico(Raiz, info_port, unidade, info_ing);
        if (resultado == 1) {
            printf("Inserção bem-sucedida para a palavra em inglês: '%s'\n", info_ing.palavra_ingles);
        } else if (resultado == 2) {
            printf("Palavra em inglês '%s' já existe.\n", info_ing.palavra_ingles);
        } else {
            printf("Falha ao inserir a palavra '%s' na árvore 2-3.\n", info_ing.palavra_ingles);
        }
    }
    imprimiArvBB((*Raiz)->info1.significados_ingles); 

}


// Função para inserir as palavras do vetor na árvore 2-3 e nas subestruturas associadas
void inserir_palavras_no_dicionario(Arv23Port **Raiz) {
    if(*Raiz == NULL){
    
        for (int i = 0; i < contador_palavras; i++) {
            // Obtém a palavra em inglês e suas traduções
            InfoBB info_ing;
            strncpy(info_ing.palavra_ingles, palavras_importadas[i].palavra_ingles, sizeof(info_ing.palavra_ingles) - 1);
            info_ing.palavra_ingles[sizeof(info_ing.palavra_ingles) - 1] = '\0';
            info_ing.unidades = NULL; // Inicializa a lista de unidades

            int unidade = palavras_importadas[i].unidade; // Unidade atual associada

            // Para cada tradução, insere na árvore 2-3
            for (int j = 0; j < palavras_importadas[i].num_traducoes; j++) {
                InfArv23 info_port;
                strncpy(info_port.palavra_portugues, palavras_importadas[i].palavras_portugues[j], sizeof(info_port.palavra_portugues) - 1);
                info_port.palavra_portugues[sizeof(info_port.palavra_portugues) - 1] = '\0';
                info_port.significados_ingles = NULL; // Inicializa a árvore binária para significados em inglês

                // Insere a palavra em português com seu significado em inglês e unidade na árvore 2-3
                int resultado = inserir_Arv23_Automatico(Raiz, info_port, unidade, info_ing);

                if (resultado == 0) {
                    printf("Erro ao inserir a palavra '%s' (significado em inglês: '%s') na árvore 2-3.\n",
                        info_port.palavra_portugues, info_ing.palavra_ingles);
                }
            }
        }
    }else{
        printf("Dataset já preenchido\n"); 
    }    

    
}


//Funções dos Itens agr

//Item (I)  informar uma unidade e então imprima todas as palavras da unidade em português seguida das equivalentes em inglês;

//Item (II) informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em português dada, independente da unidade; 


void imprimir_todos_significados_palavra_especifica(Arv23Port *Raiz){
    if(Raiz != NULL){
       InfArv23 Informacao; 
       int situacao; 

       Arv23Port *No_recuperado; 
       No_recuperado = NULL; 

       while (getchar() != '\n');
       
       printf("Digite a palavra em português que deseja imprimir seus significados: ");
       fgets(Informacao.palavra_portugues, 100, stdin);
       Informacao.palavra_portugues[strcspn(Informacao.palavra_portugues, "\n")] = '\0';  

       situacao = armazenar_No_ARV23(Raiz, Informacao, &No_recuperado); 

       
       if(situacao != 0){
          if(situacao == 1){
              //A palavra está na info1
              imprimiArvBB(No_recuperado->info1.significados_ingles);

          }else if(situacao == 2){
              imprimiArvBB(No_recuperado->info2.significados_ingles); 
          }
           

       }else{
           printf("A palavra pesquisada não foi encontrada\n");
       }
    
    }else{
        printf("A árvore está vazia\n"); 
    }
} 


























// Função para adicionar a bibliografia em um vetor a partir de um arquivo
void adicionar_bibliografia(const char *filename, Arv23Port *Raiz) {
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









