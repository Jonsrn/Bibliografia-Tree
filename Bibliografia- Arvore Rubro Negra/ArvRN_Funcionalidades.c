#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"


//Funções de inserção, balanceamento e rotação

ArvRNPort *criar_no_ArvRN(InfArvRN Info){
    ArvRNPort *novo_no; 
    novo_no = NULL; 

    novo_no = (ArvRNPort*)malloc(sizeof(ArvRNPort));
    if(novo_no != NULL){
        memset(novo_no, 0, sizeof(ArvRNPort));  //zera o lixo da memória
        strcpy(novo_no->info.palavra_portugues, Info.palavra_portugues); // Copia a string 
        novo_no->cor = VERMELHO; 
        novo_no->info.significados_ingles = NULL; 
        novo_no->esq = NULL; 
        novo_no->dir = NULL;
     }
     
     return novo_no; 
}

int qual_cor(ArvRNPort *Raiz){
    int cor; 
    if(Raiz == NULL){
        cor = PRETO;
    }else{
        if(Raiz->cor == VERMELHO){
            cor = VERMELHO;
        }else{
            cor = PRETO; 
        }
    }
    return cor; 
}

void trocar_cor(ArvRNPort **Raiz){
    if((*Raiz)->cor == VERMELHO){
        (*Raiz)->cor = PRETO;
    }else{
        (*Raiz)->cor = VERMELHO; 
    }
    
    if((*Raiz)->esq != NULL){

        if((*Raiz)->esq->cor == VERMELHO){
            (*Raiz)->esq->cor = PRETO;
        }else{
            (*Raiz)->esq->cor = VERMELHO;
        }
    }    
    
    if((*Raiz)->dir != NULL){

        if((*Raiz)->dir->cor == VERMELHO){
            (*Raiz)->dir->cor = PRETO;
        }else{
            (*Raiz)->dir->cor = VERMELHO;
        }
    }    
}

//Função Rotação Direita

void rotacaoDir_RN(ArvRNPort **Raiz) {
    ArvRNPort *novo_R = (*Raiz)->esq; // Filho esquerdo de Raiz sobe como nova raiz

    (*Raiz)->esq = novo_R->dir; // Filho direito de novo_R se torna filho esquerdo de Raiz
    novo_R->dir = *Raiz; // Raiz original desce como filho direito de novo_R

    // Ajuste das cores para manter as propriedades da árvore rubro-negra
    novo_R->cor = (*Raiz)->cor; // novo_R herda a cor da raiz original
    (*Raiz)->cor = VERMELHO; // Raiz original se torna vermelha após a rotação

    // Atualizar o ponteiro para apontar para a nova raiz
    *Raiz = novo_R;
}



//Função Rotação Esquerda

void rotacaoEsq_RN(ArvRNPort **Raiz) {
    // O filho direito da raiz se torna a nova raiz da subárvore
    ArvRNPort *novo_R = (*Raiz)->dir;

    // O filho esquerdo de novo_R se torna o filho direito de Raiz
    (*Raiz)->dir = novo_R->esq;

    // Raiz desce e se torna o filho esquerdo de novo_R
    novo_R->esq = *Raiz;

    // Ajuste das cores para manter as propriedades da árvore rubro-negra
    novo_R->cor = (*Raiz)->cor; // novo_R herda a cor da raiz original
    (*Raiz)->cor = VERMELHO;   // Raiz original se torna vermelha após a rotação

    // Atualizar o ponteiro para apontar para a nova raiz
    *Raiz = novo_R;
}

void balancear_ArvRN(ArvRNPort **Raiz) {
    if (*Raiz != NULL) { // Verifica se a raiz não é nula
        // Rotação à esquerda
        if (qual_cor((*Raiz)->esq) == PRETO && qual_cor((*Raiz)->dir) == VERMELHO) {
            rotacaoEsq_RN(Raiz);
        }

        // Rotação à direita
        if ((*Raiz)->esq != NULL && qual_cor((*Raiz)->esq) == VERMELHO && qual_cor((*Raiz)->esq->esq) == VERMELHO) {
            rotacaoDir_RN(Raiz);
        }

        // Troca de cores
        if (qual_cor((*Raiz)->esq) == VERMELHO && qual_cor((*Raiz)->dir) == VERMELHO) {
            trocar_cor(Raiz);
        }
    }
}





int inserir_ArvRN_Portugues(ArvRNPort **Raiz, InfArvRN Info, ArvRNPort **No_existente){
    int operacao, comparacao; 
    operacao = 0; //0, significa que não deu certo

    if(*Raiz == NULL){
          ArvRNPort *novo_no;
          novo_no = NULL; 

          novo_no = criar_no_ArvRN(Info);
          if (novo_no == NULL) {
             operacao = 0; // Indica falha na alocação
          } else {
             *Raiz = novo_no;
             *No_existente = *Raiz; // Retorna o endereço do novo nó
             operacao = 1; 
        } 
    }else{
        comparacao = strcmp(Info.palavra_portugues, (*Raiz)->info.palavra_portugues); 

        if(comparacao < 0){
            operacao = inserir_ArvRN_Portugues(&((*Raiz)->esq), Info, No_existente); 
        }else if(comparacao > 0){
            operacao = inserir_ArvRN_Portugues(&((*Raiz)->dir), Info, No_existente); 
        }else{
            //O nó já está alocado 
            //Devemos então recuperar o Nó atual
            *No_existente = *Raiz;
            
            operacao = 2; //2 significa que o Nó já existe, recuperamos o endereço dele
        }

        balancear_ArvRN(Raiz); 

    }
   

   return operacao; 


}

void atualizar_Raiz_ARVRN(ArvRNPort **Raiz){
    if((*Raiz) != NULL){
        (*Raiz)->cor = PRETO; 
    }
}


//Funções de consulta e impressão

int consultar_ArvRN(ArvRNPort *Raiz, InfArvRN Info){
    int operacao, comparacao;
    operacao = 0; //Não existe essa valor na árvore
    if(Raiz != NULL){
        comparacao = strcmp(Info.palavra_portugues, Raiz->info.palavra_portugues);
        if(comparacao < 0){
            operacao = consultar_ArvRN(Raiz->esq, Info); 
        }else if(comparacao > 0){
            operacao = consultar_ArvRN(Raiz->dir, Info); 
        }else{
            operacao = 1; //encontrou o elemento, então retorna 1

        }
        
    }
    return operacao; 
}

void imprimir_ArvRN(ArvRNPort *Raiz){
    if(Raiz != NULL){
        imprimir_ArvRN(Raiz->esq); 

        printf("Palavra em português: %s\n", Raiz->info.palavra_portugues); 

        imprimir_ArvRN(Raiz->dir); 
    }
} 

int armazenar_NO_ArvRN(ArvRNPort *Raiz, inf_op Info, ArvRNPort **No_recuperado){
    int operacao, comparacao; 
    operacao = 0; //0 significa que não encontrou
    if(Raiz != NULL){
        comparacao = strcmp(Info.palavra_utilizada, Raiz->info.palavra_portugues);

        if(comparacao < 0){
            operacao = armazenar_NO_ArvRN(Raiz->esq, Info, No_recuperado); 
        }else if(comparacao > 0){
            operacao = armazenar_NO_ArvRN(Raiz->dir, Info, No_recuperado); 
        }else if(comparacao == 0){
            //encontrou
            *No_recuperado = Raiz; 
            operacao = 1; 
       }
    }   

    return operacao; 
}

int imprimir_infos_RN_por_unidade(ArvRNPort *Raiz, int unidade){
    int situacao = 2; //não encontrou 
    if(Raiz != NULL){
        ArvBB_ing **vetor_ingles; 
        int tamanho_vetor, resultado; 
        vetor_ingles = NULL;
        tamanho_vetor = 0;  

        situacao |= imprimir_infos_RN_por_unidade(Raiz->esq, unidade); 

        resultado = Armazenar_No_ARVBB(Raiz->info.significados_ingles, unidade, &vetor_ingles, &tamanho_vetor); 

        if(resultado == 1 && tamanho_vetor != 0){
           
            printf("A palavra em português '%s' possui as seguintes palavras correspondentes na unidade '%d':\n", Raiz->info.palavra_portugues, unidade);
            
            for(int i = 0; i < tamanho_vetor; i++){
                printf("Palavra: %s\n", vetor_ingles[i]->info.palavra_ingles); 
            }
            situacao = 1; //pelo menos uma correspondencia foi encontrada


           
        }
        //após imprimir, libera a linkagem linear 
        free(vetor_ingles);

        situacao |= imprimir_infos_RN_por_unidade(Raiz->dir, unidade); 

    }

    return situacao; 
}






//Funções de remoção



ArvRNPort *Remover_Menor(ArvRNPort *Raiz){
    ArvRNPort *nova_raiz = Raiz;
    if(Raiz != NULL){
        if(Raiz->esq == NULL){
            free(Raiz); 
            nova_raiz = NULL; 
        }else{
            if(qual_cor(Raiz->esq) == PRETO && qual_cor(Raiz->esq->esq) == PRETO){
                Raiz = mover2EsqVermelho(&Raiz); 
            }

            Raiz->esq = Remover_Menor(Raiz->esq); 

            balancear_ArvRN(&Raiz); 

            nova_raiz = Raiz; 
        }
    }    

    return nova_raiz; 
    
}

ArvRNPort *Procurando_Menor(ArvRNPort *Raiz){
    ArvRNPort *atual, *prox;
    atual = NULL; 
    prox = NULL; 
    
    if(Raiz != NULL){
        atual = Raiz; 
        prox = Raiz->esq; 

        while(prox != NULL){
            atual = prox; 
            prox = prox->esq; 
        } 
    }    

    return atual;
}

ArvRNPort *mover2EsqVermelho(ArvRNPort **Raiz){
    if((*Raiz) != NULL){
        trocar_cor((Raiz)); 

        if((*Raiz)->dir != NULL && qual_cor((*Raiz)->dir->esq) == VERMELHO){
            
            rotacaoDir_RN(&((*Raiz)->dir)); 
            rotacaoEsq_RN(Raiz); 
            trocar_cor(Raiz); 

        }
    }    

    return *Raiz; 
}

ArvRNPort *mover2DirVermelho(ArvRNPort **Raiz) {
    if (*Raiz != NULL) {
        // Troca as cores do nó atual e seus filhos
        trocar_cor(Raiz);

        // Verifica se o filho esquerdo do nó esquerdo é vermelho
        if ((*Raiz)->esq != NULL && qual_cor((*Raiz)->esq->esq) == VERMELHO) {
            // Realiza a rotação à direita para balancear a subárvore
            rotacaoDir_RN(Raiz);

            // Troca as cores novamente após a rotação
            trocar_cor(Raiz);
        }
    }

    return *Raiz; // Retorna a nova raiz
}

int remover_No_ArvRN(ArvRNPort **Raiz, InfArvRN Info) {
    int operacao = 0; // 0 significa que não foi removido ou não encontrado

    if (*Raiz != NULL) {
        int comparacao = strcmp(Info.palavra_portugues, (*Raiz)->info.palavra_portugues);

        if (comparacao < 0) {
            // Ajusta a subárvore esquerda se necessário
            if (qual_cor((*Raiz)->esq) == PRETO && qual_cor((*Raiz)->esq->esq) == PRETO) {
                mover2EsqVermelho(Raiz);
            }
            operacao = remover_No_ArvRN(&((*Raiz)->esq), Info);
        } else {
            // Ajusta a subárvore direita se necessário
            if (qual_cor((*Raiz)->esq) == VERMELHO) {
                rotacaoDir_RN(Raiz);
            }

            if (comparacao == 0 && (*Raiz)->dir == NULL) {
                // Caso base: nó encontrado e não possui subárvore direita
                free(*Raiz);
                *Raiz = NULL;
                operacao = 1; // Nó removido
            } else {
                // Verifica e ajusta a subárvore direita se necessário
                if (qual_cor((*Raiz)->dir) == PRETO && qual_cor((*Raiz)->dir->esq) == PRETO) {
                    mover2DirVermelho(Raiz);
                }

                if (comparacao == 0) {
                    // Substitui pelo menor da subárvore direita
                    ArvRNPort *Menor = Procurando_Menor((*Raiz)->dir);
                    (*Raiz)->info = Menor->info; // Substitui a informação
                    (*Raiz)->dir = Remover_Menor((*Raiz)->dir); // Remove o menor nó
                    operacao = 1; // Nó removido
                } else {
                    operacao = remover_No_ArvRN(&((*Raiz)->dir), Info);
                }
            }
        }

        // Rebalanceia a árvore após a remoção
        balancear_ArvRN(Raiz);
    }

    return operacao; // Retorna o status da operação
}






//função auxiliar de remoção do Item III

int remover_palavra_ingles_pela_unidade(ArvRNPort **Raiz, ArvRNPort *Raiz_percorrer, inf_op Info) {
    int situacao = 0; //Nenhuma palavra foi removida

    if (Raiz_percorrer != NULL) {
        int operacao;
        // Percorre a subárvore esquerda
        
        situacao |= remover_palavra_ingles_pela_unidade(Raiz, Raiz_percorrer->esq, Info);
        

        // Percorre a subárvore direita
        
        situacao |= remover_palavra_ingles_pela_unidade(Raiz, Raiz_percorrer->dir, Info);
        

        // Remove a palavra em inglês da lista de significados
        operacao = remover_No_ArvBB(&(Raiz_percorrer->info.significados_ingles), Info);

        if (operacao == 2) {
            printf("Palavra em inglês: %s excluída com sucesso da palavra: %s\n", Info.palavra_utilizada, Raiz_percorrer->info.palavra_portugues);
            situacao = 1; //sucesso
        }

        // Se a lista de significados em inglês ficou vazia
        if (Raiz_percorrer->info.significados_ingles == NULL) {
            printf("Como a Palavra em português: %s não possui mais correspondentes em inglês, a mesma foi excluída\n", Raiz_percorrer->info.palavra_portugues);

            // Remove o nó rubro-negro usando a raiz original
            operacao = remover_No_ArvRN(Raiz, Raiz_percorrer->info);
            atualizar_Raiz_ARVRN(Raiz); 

            if (operacao == 1) {
                printf("Palavra em português: %s removida com sucesso da árvore!\n", Raiz_percorrer->info.palavra_portugues);
            } else {
                printf("Erro ao tentar remover a palavra: %s\n", Raiz_percorrer->info.palavra_portugues);
            }
        }
    }

    return situacao; //0 se não apagou nada, 1 se apagou
}



int buscar_documentar_caminho(ArvRNPort *Raiz, inf_op Info, inf_op Infos_percurso[MAX_CAMINHO], int *tam_vetor){
    int encontrou, comparacao;
    encontrou = 0; //não encontrou 
    if(Raiz != NULL){
        comparacao = strcmp(Info.palavra_utilizada, Raiz->info.palavra_portugues); 

        if(comparacao < 0){
            //percorre pra esquerda
            snprintf(Infos_percurso[*tam_vetor].palavra_utilizada, 100,"Estou percorrendo à esquerda de %s", Raiz->info.palavra_portugues);
            (*tam_vetor)++;
            encontrou = buscar_documentar_caminho(Raiz->esq, Info, Infos_percurso, tam_vetor); 
            

        }else if(comparacao > 0){
            //percorre pra direita
            snprintf(Infos_percurso[*tam_vetor].palavra_utilizada, 100,"Estou percorrendo à direita de %s", Raiz->info.palavra_portugues);
            (*tam_vetor)++;  
            encontrou = buscar_documentar_caminho(Raiz->dir, Info, Infos_percurso, tam_vetor);                       

        }else if(comparacao == 0){

            encontrou = 1; //palavra encontrada com sucesso 
        }

    }

    return encontrou; 
}
