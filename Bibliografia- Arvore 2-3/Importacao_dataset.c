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
void adicionar_bibliografia(const char *filename, Arv23Port **Raiz) {
    int situacao; 

    if(*Raiz == NULL){    
        FILE *file = fopen(filename, "r");
        if (!file) {
            //Erro ao abrir o arquivo.
            situacao = 7;
        }else{

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

            situacao = inserir_palavras_no_dicionario(Raiz); 
        
        }    

        
    }else{
        //Dataset já preenchido 
        situacao = 6; 
    }  

    /* 
    legenda dos retornos 1 (deu certo), 2 (falhou porque a alocação do nó da lista falhou), 3 (Unidade já está presente na lista de uma palavra em Ingles especifica, quer dizer que a palavra em ptbr, a palavra em ingles e a unidade já estavam presentes), 
    4 (Falha na Alocação da Árvore BB), 5 (Alocação do Nó da 2-3 falhou), 6 (Dataset já preenchido), 7 (falha na abertura do arquivo)
    */

     mensagem_status_montagem_dataset(situacao);   
}

// Função para inserir as palavras do vetor na árvore RN e nas subestruturas associadas
int inserir_palavras_no_dicionario(Arv23Port **Raiz) {
    int situacao; 

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
                InfArv23 info_port;
                strncpy(info_port.palavra_portugues, palavras_importadas[i].palavras_portugues[j], sizeof(info_port.palavra_portugues) - 1);
                info_port.palavra_portugues[sizeof(info_port.palavra_portugues) - 1] = '\0';
                info_port.significados_ingles = NULL; // Inicializa a árvore binária para significados em inglês

                // Insere a palavra em português com seu significado em inglês e unidade na árvore 2-3
                situacao = inserir_Arv23_Automatico(Raiz, info_port, unidade, info_ing); 

                if (situacao == 0 || situacao == 2 || situacao == 4 || situacao == 5) {
                    //algo deu errado
                    break;
                }
            }
        }
    }

   return situacao;     

}

int inserir_Arv23_Automatico(Arv23Port **Raiz, InfArv23 Info, int unidade, InfoBB Info_ingles){
    int operacao; 
    operacao = 1; //1 significa sucesso 
    int situacao; 
    situacao = 1;  


    insereArv23(Raiz, Info, NULL, NULL, &situacao); 

    //situacao, se for 0, é falha na alocação, se for 1 o novo nó foi criado e preenchido, se for 2

    if(situacao != 0){
        //Como inserimos com sucesso na árvore 2-3, precisamos agr inserir a palavra 
        //precisamos recuperar o nó e saber em qual das infos está a palavra 
        inf_op palavra_desejada;
        strncpy(palavra_desejada.palavra_utilizada, Info.palavra_portugues, sizeof(palavra_desejada.palavra_utilizada) - 1);
        palavra_desejada.palavra_utilizada[sizeof(palavra_desejada.palavra_utilizada) - 1] = '\0';

        Arv23Port *no_encontrado = NULL;
        int posicao = armazenar_No_ARV23(*Raiz, palavra_desejada, &no_encontrado);

        if (posicao == 1) {
            situacao = inserir_ArvBB_Automatico(&(no_encontrado->info1.significados_ingles), Info_ingles, unidade);
        } else if (posicao == 2) {
            situacao = inserir_ArvBB_Automatico(&(no_encontrado->info2.significados_ingles), Info_ingles, unidade);
        } 

    }else{
            //A alocação do Nó da 2-3 falhou
            situacao = 5;    
    }

    return operacao; 

} 

int inserir_ArvBB_Automatico(ArvBB_ing **Raiz, InfoBB Info, int unidade){
    int operacao, situacao; 
    situacao = 1; //1 indica sucesso 
    
    ArvBB_ing *no_existente; 
    no_existente = NULL; //Isso daqui serve para após inserir, ter acesso ao endereço do Nó, pra inserções subsequentes em sua sublista

    operacao = inserir_ArvBB_Ingles(Raiz, Info, &no_existente); 
    
    //Nos retornos, 0 significa falhou totalmente (alocação), 1 significa que deu certo criar um novo nó e inseri-lo, e 2 significa que o Nó já existe. 
    //Independente se o Nó é novo ou antigo, o recuperamos, para poder fazer a inserção em sua lista

    if(operacao != 0){
        situacao = inserir_lista_automatico(&(no_existente->info.unidades), unidade); 
        //Nos retornos aqui, 2 significa que a alocação falhou, 1 que deu certo, e 3 que o número já existe nessa lista
    }else{
        //Falha na alocação do Nó da Arvore Binária
        situacao = 4; 
       
    }

    return situacao; 

}


//aqui ficará a função de inserção na lista. 

int inserir_lista_automatico(list_unid **Raiz, int unidade){
    int operacao, situacao; 
    situacao = 1; //1 significa que deu certo

    operacao =  inserir_na_Lista(Raiz, unidade); 

    if(operacao == 0){
       //Unidade já presente na lista
       situacao = 3;  
    }else if(operacao == 2){
       //A alocação do Nó na Lista falhou
       situacao = 2;  
    }

   return situacao; //3 significa que o numero já existe na lista, 1 significa que deu certo e 2 que a alocação falhou
}






 






