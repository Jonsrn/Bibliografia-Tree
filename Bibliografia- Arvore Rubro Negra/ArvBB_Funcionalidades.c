#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"



// funcionalidade de criação de Nó

ArvBB_ing* criar_no_ArvBB(InfoBB info){
     ArvBB_ing *novo_no; 
     novo_no = NULL; 

     novo_no = (ArvBB_ing*)malloc(sizeof(ArvBB_ing)); 
     if(novo_no == NULL){
          printf("Falha na alocação\n"); 
     }else{
        memset(novo_no, 0, sizeof(ArvBB_ing));  //zera o lixo da memória
        strcpy(novo_no->info.palavra_ingles, info.palavra_ingles); // Copia a string 
        novo_no->info.unidades = NULL; 
        novo_no->esq = NULL; 
        novo_no->dir = NULL;
     }

     return novo_no; 

}

int inserir_ArvBB_Ingles(ArvBB_ing **Raiz, InfoBB info, ArvBB_ing **no_existente){
     int operacao; 
     operacao = 1; //1 significa que deu certo.
     int comparacao;
      

     if(*Raiz == NULL){
          ArvBB_ing *novo_no;
          novo_no = NULL; 

          novo_no = criar_no_ArvBB(info);
          if (novo_no == NULL) {
             operacao = 0; // Indica falha na alocação
          } else {
             *Raiz = novo_no;
             *no_existente = *Raiz; // Retorna o endereço do novo nó
        } 

     }else{
           
          comparacao = strcmp(info.palavra_ingles, (*Raiz)->info.palavra_ingles);

          if(comparacao < 0){
               operacao = inserir_ArvBB_Ingles(&(*Raiz)->esq, info, no_existente); 
          }else if(comparacao > 0){
               operacao = inserir_ArvBB_Ingles(&(*Raiz)->dir, info, no_existente); 
          }else{
               //O nó já está alocado 
               //Devemos então recuperar o Nó atual
               *no_existente = *Raiz;
            
               operacao = 2; //2 significa que o Nó já existe, recuperamos o endereço dele
          }
     }

     return operacao; 

     //operacao = 1, indica sucesso nominal, inserindo o Nó novo, operacao = 2 indica sucesso, mas o Nó já existe


}


//Essa função percorre a ArvBB, e recupera os Nós de acordo com um dos critérios, 0 recupera tudo, !=0 recupera valores especificos 

int Armazenar_No_ARVBB(ArvBB_ing *Raiz, int unidade, ArvBB_ing ***vetor_ingles, int *tam_vetor){
    int resultado; 
    resultado = 1;
    if(Raiz != NULL){
        resultado = Armazenar_No_ARVBB(Raiz->esq, unidade, vetor_ingles, tam_vetor);

        // Se houve erro na subárvore esquerda, interrompe a operação 
        if (resultado == 1) {
            if (unidade == 0 || buscando_unidade(Raiz->info.unidades, unidade) == 1) {
                // Realoca o vetor dinâmico
                ArvBB_ing **temp = (ArvBB_ing **)realloc(*vetor_ingles, (*tam_vetor + 1) * sizeof(ArvBB_ing *));
                if (temp == NULL) {
                    printf("\nErro na realocação do vetor\n");
                    resultado = 0; // Indica falha na realocação
                } else {
                    *vetor_ingles = temp;
                    (*vetor_ingles)[*tam_vetor] = Raiz;
                    (*tam_vetor)++;
                }
            }
        }

        if(resultado == 1){
          resultado = Armazenar_No_ARVBB(Raiz->dir, unidade, vetor_ingles, tam_vetor);
        } 
     }
    
    return resultado; 
    
}

void imprimiArvBB(ArvBB_ing *no) {
    if (no != NULL) {
        imprimiArvBB(no->esq);


        printf("\nPalavra em inglês: %s, Unidades que ela está presente: \n", no->info.palavra_ingles);
        imprimirLista(no->info.unidades);

        imprimiArvBB(no->dir);
    }
}

//Função de remover Nó da Árvore 

int menor_filho(ArvBB_ing *Raiz, ArvBB_ing **menor){
     //Vou assumir que não encontrei 
     int operacao; 
     operacao = 0; 

     if(Raiz != NULL){
          //percorre até encontrar o Nó mais à esquerda
          while(Raiz->esq != NULL){
               Raiz = Raiz->esq; 
          }

          *menor = Raiz; 
          operacao = 1; 
     }

     return operacao; 

}

int remover_No_ArvBB(ArvBB_ing **Raiz, inf_ex informacoes){
     ArvBB_ing *aux, *end_filho, *endMenorFilho; 
     int operacao, comparacao; 
     operacao = 1; //1 significa sucesso

     if(*Raiz == NULL){
          //Se a arvore estiver vazia, não há nada a ser feito aqui (mas isso vai significar que o Nó lá na 2-3 vai ser excluído)
          operacao = 0; //Não há árvore
     }else{
          comparacao = strcmp(informacoes.palavra_ser_excluida, (*Raiz)->info.palavra_ingles);
          
          if(comparacao < 0){ // se for menor, buscar na subarvore a esquerda
               operacao = remover_No_ArvBB(&((*Raiz)->esq), informacoes); 
          }else if(comparacao > 0){ // se for maior, buscar na subarvore a direita
               operacao = remover_No_ArvBB(&((*Raiz)->dir), informacoes); 
          }else{ 
                //caso 1: O nó não tem filhos
                if((*Raiz)->esq == NULL && (*Raiz)->dir == NULL){
                    //Antes de excluir o Nó, precisamos verificar se a lista ficará vazia. 
                    operacao = remover_unidade_lista(&(*Raiz)->info.unidades, informacoes.unidade); 
                    if(operacao == 1){
                         //Se a operação for 1, significa que o capitulo foi encontrado na lista e excluído de lá
                         if((*Raiz)->info.unidades == NULL){
                              aux = *Raiz; 
                              *Raiz = NULL; //O nó passa a ser nulo
                              free(aux); //A memória é liberada
                         }else{
                              operacao = 2; //significa que só o valor da lista foi excluído, há mais de um capitulo lá
                         }
                   }else{
                        operacao = 0; //Não haverá exclusão, porque o valor da unidade não foi encontrado
                   }     

               }//caso 2: O nó tem apenas um filho
               else if((*Raiz)->esq == NULL || (*Raiz)->dir == NULL){
                    // Se o filho esquerdo é NULL, endFilho aponta para o filho direito e vice-versa 
                    //Mas antes precisamos verificar se há o capitulo na lista e se ele é único. 
                    operacao = remover_unidade_lista(&(*Raiz)->info.unidades, informacoes.unidade); 
                    if(operacao == 1){
                         //Se a operação for 1, significa que o capitulo foi encontrado na lista e excluído de lá
                         if((*Raiz)->info.unidades == NULL){
                              end_filho = (*Raiz)->esq != NULL ? (*Raiz)->esq : (*Raiz)->dir; 
                              aux = *Raiz; 
                              *Raiz = end_filho; // Substitui o nó pelo seu único filho
                              free(aux); // Libera a memória do nó
                         }else{
                              operacao = 2; //significa que só o valor da lista foi excluído, há mais de um capitulo lá

                         }
                    }else{
                         operacao = 0; //Não haverá exclusão, porque o valor da unidade não foi encontrado

                    }
                

               } //caso 3: O nó tem dois filhos
               else{
                    //Antes de realizar o procedimento, vamos verificar na lista se a unidade está lá, e se a mesma ficará vazia
                    operacao = remover_unidade_lista(&(*Raiz)->info.unidades, informacoes.unidade);
                    
                    if(operacao == 1){
                         if((*Raiz)->info.unidades == NULL){
                              if(menor_filho((*Raiz)->dir, &endMenorFilho) == 1){
                                   (*Raiz)->info = endMenorFilho->info;
                                   inf_ex novo_inf_ex;
                                   strcpy(novo_inf_ex.palavra_ser_excluida, endMenorFilho->info.palavra_ingles);
                                   novo_inf_ex.unidade = informacoes.unidade;
                                   operacao = remover_No_ArvBB(&((*Raiz)->dir), novo_inf_ex);
                                   

                              }else{
                                   //falhou em encontrar o menor filho 
                                   printf("Erro ao encontrar o menor filho.\n");
                                   operacao = 0; 
                              }
                         }else{
                              operacao = 2; //significa que só o valor da lista foi excluído, há mais de um capitulo lá
                         }     

                    }else{
                          operacao = 0; //Não haverá exclusão, porque o valor da unidade não foi encontrado

                    }
               }


          }
     }
     return operacao; 

}


void percorrer_remover_palavras_pela_unidade(ArvBB_ing *Raiz_percorrendo, ArvBB_ing **Raiz_original, inf_ex Info){
     if(Raiz_percorrendo != NULL){
        int resultado; 

        percorrer_remover_palavras_pela_unidade(Raiz_percorrendo->esq, Raiz_original, Info);
        
        percorrer_remover_palavras_pela_unidade(Raiz_percorrendo->dir, Raiz_original, Info); 

        inf_ex Informacao;
        Informacao.unidade = Info.unidade; 
        strcpy(Informacao.palavra_ser_excluida, Raiz_percorrendo->info.palavra_ingles);
        
        resultado = buscando_unidade(Raiz_percorrendo->info.unidades, Info.unidade); 

        if(resultado == 1){
          remover_No_ArvBB(Raiz_original, Informacao);

          if(Raiz_percorrendo->info.unidades == NULL){
             printf("Como não há mais unidades utilizando essa palavra, ela foi removida\n");    
            }

        }


        

     }
}






