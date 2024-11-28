#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"





//Função de Inserir na Lista 

int criar_no_Lista(list_unid **novo_elemento, int unidade){
    int operacao;
    operacao = 1; //1 significa que estamos partindo do pressuposto que a alocação do Nó será feita de maneira bem sucedida

    *novo_elemento = (list_unid*) malloc(sizeof(list_unid)); 
    if(*novo_elemento == NULL){
        operacao = 0; 
    }else{
        (*novo_elemento)->unidade = unidade; 
        (*novo_elemento)->prox = NULL; 
    }
    return operacao; 
}

int inserir_na_Lista(list_unid **Raiz, int unidade) {
    int operacao = 1; // 1 indica sucesso

    list_unid *anterior = NULL;
    list_unid *atual = *Raiz;
    list_unid *novo_elemento; 
    novo_elemento = NULL; 

    // Caso especial: inserção na raiz ou antes do primeiro elemento
    if (*Raiz == NULL || unidade < (*Raiz)->unidade) {        

        operacao = criar_no_Lista(&novo_elemento, unidade);
        if(operacao == 1){
            novo_elemento->prox = *Raiz;
            *Raiz = novo_elemento;
        }else{
            operacao = 0; 
        }    
    } else {
        // Percorre a lista para encontrar a posição correta de inserção
        while (atual != NULL && atual->unidade < unidade) {
            anterior = atual;
            atual = atual->prox;
        }

        // Verifica se a unidade já existe na lista
        if (atual != NULL && atual->unidade == unidade) {
            operacao = 2; // Unidade já existe, não insere
        } else {
            // Insere o novo elemento na posição encontrada
            operacao = criar_no_Lista(&novo_elemento, unidade);
            if(operacao == 1){
                anterior->prox = novo_elemento;
                novo_elemento->prox = atual;
            }    
        }
    }

    return operacao; // Retorna 1 para sucesso, 0 se a unidade já existe
}



//Função de percorrer a Lista


int buscando_unidade(list_unid *Raiz_Lista, int unidade_buscada){
    int operacao; 
    operacao = 0; //0 significa que não foi encontrada

    while(Raiz_Lista != NULL){
        if(Raiz_Lista->unidade == unidade_buscada){
            operacao = 1; //encontrou
            break;
        }

        Raiz_Lista = Raiz_Lista->prox;
    }

    return operacao; 
}

void imprimirLista(list_unid *lista) {
    list_unid *atual = lista;
    printf("Unidade: "); 
    while (atual != NULL) {
        if(atual->prox != NULL){
        printf("%d, ", atual->unidade);
        }else{
            printf("%d.\n", atual->unidade); 
        }
        atual = atual->prox;
    }
    
}


//Função de remover da Lista

int remover_unidade_lista(list_unid **Raiz_Lista, int unidade_buscada){
    int operacao; 
    operacao = 0; //0 significa que não deu certo 

    list_unid *anterior = NULL;
    list_unid *atual = *Raiz_Lista;
    
   while (atual != NULL) {
        if (atual->unidade == unidade_buscada) {
            operacao = 1; // Encontrou o valor na lista
            
            if (anterior == NULL) {
                // Caso especial: o elemento a ser removido é a raiz
                *Raiz_Lista = atual->prox;
            } else {
                // Remover o nó do meio ou do final da lista
                anterior->prox = atual->prox;
            }
            
            free(atual); // Libera o nó da memória
            break;
        }

        anterior = atual; // Move o ponteiro anterior
        atual = atual->prox; // Avança na lista
    }

    return operacao; 

}
