#include <stdio.h>
#include "bibliografia.h"


//função de diagnostico da importação do dataset
void mensagem_status_montagem_dataset(int situacao){
    if(situacao == 1){
        printf("A operação de preenchimento do Dataset realizada com sucesso.\n"); 
    }
    if(situacao == 2){
        printf("A operação falhou porque houve um problema na alocação do nó da lista.\n"); 
    }
    if(situacao == 3){
        printf("A operação falhou porque a palavra em português, seu significado em inglês e assim como sua unidade já estão presentes no dataset.\n"); 
    }
    if(situacao == 4){
        printf("A operação falhou porque houve um problema na alocação do nó da Árvore Binária.\n"); 
    }
    if(situacao == 5){
        printf("A operação falhou porque houve um problema na Alocação do Nó da 2-3.\n"); 
    }
    if(situacao == 6){
        printf("A operação falhou porque o Dataset já foi preenchido.\n"); 
    }
    if(situacao == 7){
        printf("A operação falhou porque não foi possivel abrir o arquivo.\n"); 
    }    
}



//Função de diagnostico do Item (I)

void mensagem_status_impressao_unidade(int situacao){

    if(situacao == 0){
        printf("A operação falhou, porque a árvore está vazia.\n"); 
    }
    if(situacao == 1){
        printf("A operacao foi realizada com sucesso.\n"); 

    }
    if(situacao == 2){
        printf("Nenhuma palavra correspondente foi encontrada com o valor pesquisado.\n"); 
    }
  
}

void mensagem_status_impressao_palavra_especifica(int situacao){

    if(situacao == 0){
        printf("A operação falhou, por que a árvore está vazia.\n");
    }
    if(situacao == 1){
        printf("A operação foi realizada com sucesso.\n");
    }
    if(situacao == 2){
        printf("A operação falhou, porque a palavra pesquisada não foi encontrada.\n"); 
    }
}


//Item III

void mensagem_status_exclusao_ingles_unidade(int situacao){
    if(situacao == 0){
         printf("A operação falhou, por que a árvore está vazia.\n");
    }
    if(situacao == 1){
        printf("A operação foi realizada com sucesso.\n");
    }
    if(situacao == 2){
        printf("A operação falhou, porque nenhuma palavra com a unidade pesquisada foi encontrada.\n");
    }
}



//Item IV 

void mensagem_status_exclusao_correspondente_ingles(int situacao){

    if(situacao == 0){
         printf("A operação falhou, por que a árvore está vazia.\n");
    }
    if(situacao == 1){
         printf("A operação foi realizada com sucesso, palavra em português removida da árvore RN.\n");
    }
    if(situacao == 2){
        printf("A operação falhou porque nenhuma palavra em português correspondente foi encontrada.\n"); 
    }
    if(situacao == 3){
        printf("A operação foi realizada com sucesso, as palavra em inglês correspondentes a unidade foram removidas.\n");
    }
    if(situacao == 4){
        printf("A operação falhou porque a remoção da palavra em português na Rubro Negra não foi bem sucedida.\n");
    }
    if(situacao == 5){
        printf("A operação falhou porque a remoção não encontrou nenhuma palavra em inglês correspondente a unidade solicitada.\n");
    }
}
