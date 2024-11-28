#include <stdio.h>
#include "bibliografia.h"


//função de diagnostico da importação do dataset




//Função de diagnostico do Item (I)

void mensagem_status_impressao_unidade(int situacao){

    if(situacao == 0){
        printf("A operação falhou, porque a árvore está vazia\n"); 
    }
    if(situacao == 1){
        printf("A operacao foi realizada com sucesso\n"); 

    }
    if(situacao == 2){
        printf("Nenhum correspondente foi encontrado com o valor pesquisado\n"); 
    }
}

void mensagem_status_impressao_palavra_especifica(int situacao){

    if(situacao == 0){
        printf("A operação falhou, por que a árvore está vazia\n");
    }
    if(situacao == 1){
        printf("A operação foi realizada com sucesso \n");
    }
    if(situacao == 2){
        printf("A operação falhou, porque a palavra pesquisada não foi encontrada\n"); 
    }
}


//Item III

void mensagem_status_exclusao_ingles_unidade(int situacao){
    if(situacao == 0){
         printf("A operação falhou, por que a árvore está vazia\n");
    }
    if(situacao == 1){
        printf("A operação foi realizada com sucesso \n");
    }
    if(situacao == 2){

    }
}



//Item IV 

void mensagem_status_exclusao_correspondente_ingles(int situacao){

    if(situacao == 0){
         printf("A operação falhou, por que a árvore está vazia\n");
    }
    if(situacao == 1){
         printf("A operação foi realizada com sucesso \n");
    }
    if(situacao == 2){
        printf("Nenhuma palavra com a unidade pesquisada foi encontrada.\n"); 
    }
}