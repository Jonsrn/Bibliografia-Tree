#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"

// Funções de Inserção

// Função para criar um novo nó
Arv23Port *criarNoArv23(InfArv23 Info, Arv23Port *Filho_Esq, Arv23Port *Filho_Cent) {
    Arv23Port *Novo_no = (Arv23Port *)malloc(sizeof(Arv23Port));
    if (Novo_no == NULL) {
        printf("Falha na alocação\n");
        exit(1); // Encerra o programa em caso de falha na alocação
    }
    memset(Novo_no, 0, sizeof(Arv23Port)); // Zera para evitar lixo

    Novo_no->info1 = Info;
    Novo_no->esq = Filho_Esq;
    Novo_no->cen = Filho_Cent;
    Novo_no->dir = NULL;
    Novo_no->n_infos = 1;
    return Novo_no;
}

// Função para verificar se o nó é folha
int ehfolha(Arv23Port *no) {
    // Um nó é folha se não tem filho esquerdo
    return (no != NULL && no->esq == NULL);
}

// Função para adicionar uma chave ao nó
Arv23Port *adicionaChave(Arv23Port *no, InfArv23 Info, Arv23Port *MaiorNo) {
    int comparacao = strcmp(Info.palavra_portugues, no->info1.palavra_portugues);
    if (comparacao < 0) {
        // Nova info é menor que info1
        no->info2 = no->info1;
        no->info1 = Info;
        if (MaiorNo != NULL) {
            no->dir = no->cen;
            no->cen = MaiorNo;
        }
        no->n_infos = 2;
    } else {
        // Nova info é maior ou igual a info1
        no->info2 = Info;
        if (MaiorNo != NULL) {
            no->dir = MaiorNo;
        }
        no->n_infos = 2;
    }
    return no; // Retorna o nó atualizado em vez de um inteiro
}
// Função para quebrar o nó com indicação de raiz




// Função para quebrar o nó
Arv23Port *quebraNo(Arv23Port **No, InfArv23 Info, InfArv23 *promove, Arv23Port *Filho, Arv23Port **no_referencia) {
    int comparacao1 = strcmp(Info.palavra_portugues, (*No)->info2.palavra_portugues);
    int comparacao2 = strcmp(Info.palavra_portugues, (*No)->info1.palavra_portugues);
    Arv23Port *Maior;

    if (comparacao1 > 0) {
        // Caso 1: Info > info2
        *promove = (*No)->info2;
        Maior = criarNoArv23(Info, (*No)->dir, Filho);
        *no_referencia = Maior; 
    } else if (comparacao2 > 0) {
        // Caso 2: info1 < Info < info2
        *promove = Info;
        Maior = criarNoArv23((*No)->info2, Filho, (*No)->dir);
        *no_referencia = Maior;
    } else {
        // Caso 3: Info < info1
        *promove = (*No)->info1;
        Maior = criarNoArv23((*No)->info2, (*No)->cen, (*No)->dir);
        (*No)->info1 = Info;
        (*No)->cen = Filho;
        *no_referencia = *No; 
    }

    // Atualiza o nó atual
    (*No)->n_infos = 1;
    memset(&(*No)->info2, 0, sizeof(InfArv23)); // Limpa info2
    (*No)->dir = NULL;

    return Maior;
}




// Função de inserção na árvore 2-3
Arv23Port *insereArv23(Arv23Port **no, InfArv23 Info, InfArv23 *promove, Arv23Port **Pai, int *situacao, int *info_posicao, Arv23Port **no_referencia) {
    Arv23Port *MaiorNo = NULL;
    InfArv23 promove_local; // Variável local para promoção
    int comparacao1, comparacao2;
    int verificacao = 0; // 0 significa que não tem palavra igual na árvore

    if (*no == NULL) {
        // Se a árvore for nula, criaremos o primeiro nó
        *no = criarNoArv23(Info, NULL, NULL);
        if (*no == NULL) {
            *situacao = 0; // Falha total devido à falha de alocação
        } else {
            *situacao = 1;       // Sucesso com nova inserção
            *no_referencia = *no; // Retorna o endereço do novo nó
            *info_posicao = 1;    // A palavra está em info1
        }
    } else {
        comparacao1 = strcmp(Info.palavra_portugues, (*no)->info1.palavra_portugues);

        if (comparacao1 == 0) {
            *situacao = 2;        // A palavra já existe em info1
            *info_posicao = 1;
            *no_referencia = *no;
            verificacao = 1;
        }

        if ((*no)->n_infos == 2) {
            comparacao2 = strcmp(Info.palavra_portugues, (*no)->info2.palavra_portugues);
            if (comparacao2 == 0) {
                *situacao = 2;    // A palavra já existe em info2
                *info_posicao = 2;
                *no_referencia = *no;
                verificacao = 1;
            }
        }

        if (verificacao != 1) {
            if (ehfolha(*no)) { // Se for folha
                if ((*no)->n_infos == 1) {
                    // Nó tem apenas uma informação
                    printf("Adicionando segunda chave '%s' no nó com info1='%s'\n", Info.palavra_portugues, (*no)->info1.palavra_portugues);
                    *no = adicionaChave(*no, Info, NULL); // Retorna o nó atualizado
                    *situacao = 1; // Indica que a palavra foi adicionada com sucesso
                    *no_referencia = *no; // Recupera o endereço
                    *info_posicao = 1; // Atualiza a posição correta
                    MaiorNo = NULL;
                } else {
                    // Nó tem duas informações, precisa quebrar
                    printf("Quebrando o nó. Antes da quebra, info1='%s' e info2='%s', nova info='%s'\n", (*no)->info1.palavra_portugues, (*no)->info2.palavra_portugues, Info.palavra_portugues);
                    MaiorNo = quebraNo(no, Info, &promove_local, NULL, no_referencia);
                    if (Pai == NULL || *Pai == NULL) {
                        // Criação de uma nova raiz
                        *no = criarNoArv23(promove_local, *no, MaiorNo);
                        MaiorNo = NULL;
                        *info_posicao = 1;
                        *no_referencia = *no;
                        printf("Novo nó raiz criado com promoção de '%s'\n", promove_local.palavra_portugues);
                    } else {
                        *promove = promove_local;
                        *no_referencia = *no;
                        *info_posicao = 1;
                    }
                }
            } else {
                // Nó não é folha, precisa descer na árvore
                if (comparacao1 < 0) {
                    printf("Descendo para a esquerda do nó com info1='%s'\n", (*no)->info1.palavra_portugues);
                    MaiorNo = insereArv23(&((*no)->esq), Info, &promove_local, no, situacao, info_posicao, no_referencia);
                } else {
                    if ((*no)->n_infos == 2) {
                        comparacao2 = strcmp(Info.palavra_portugues, (*no)->info2.palavra_portugues);
                    }
                    if (((*no)->n_infos == 1) || (comparacao2 < 0)) {
                        printf("Descendo para o centro do nó com info1='%s'\n", (*no)->info1.palavra_portugues);
                        MaiorNo = insereArv23(&((*no)->cen), Info, &promove_local, no, situacao, info_posicao, no_referencia);
                    } else {
                        printf("Descendo para a direita do nó com info2='%s'\n", (*no)->info2.palavra_portugues);
                        MaiorNo = insereArv23(&((*no)->dir), Info, &promove_local, no, situacao, info_posicao, no_referencia);
                    }
                }

                // Tratamento das pendências após as chamadas recursivas
                if (MaiorNo != NULL) {
                    if ((*no)->n_infos == 1) {
                        // Adiciona o valor promovido ao nó
                        *no = adicionaChave(*no, promove_local, MaiorNo); // Retorna o nó atualizado
                        *situacao = 1;
                        *no_referencia = *no;
                        *info_posicao = 1;
                        MaiorNo = NULL;
                    } else {
                        // Quebra o nó atual e promove o valor
                        InfArv23 promove1;
                        MaiorNo = quebraNo(no, promove_local, &promove1, MaiorNo, no_referencia);
                        if (Pai == NULL || *Pai == NULL) {
                            // Criação de uma nova raiz
                            *no = criarNoArv23(promove1, *no, MaiorNo);
                            MaiorNo = NULL;
                            *info_posicao = 1;
                            *no_referencia = *no;
                        } else {
                            *promove = promove1;
                            *info_posicao = 1;
                        }
                        *situacao = 1;
                        *no_referencia = *no;
                    }
                }
            }
        }
    }

    return MaiorNo;
}


int armazenar_No_ARV23(Arv23Port *Raiz, inf_ex Info, Arv23Port **No_recuperado){
   int resultado, comparacao1, comparacao2; 
   resultado = 0; //0 significa que não encontrou

   if(Raiz != NULL){
       resultado = armazenar_No_ARV23(Raiz->esq, Info, No_recuperado); 
       comparacao1 = strcmp(Info.palavra_ser_excluida, Raiz->info1.palavra_portugues); 

       if(resultado == 0){

            if(Raiz->n_infos == 1){
                if(comparacao1 == 0){
                        //encontrou, então recuperamos o Nó e recebe 1 (pq está na info1)
                        resultado= 1; 
                        *No_recuperado = Raiz; 
                } 

                if(resultado != 1){
                    // como não encontrou, vamos pro centro
                    resultado = armazenar_No_ARV23(Raiz->cen, Info, No_recuperado);   

                }
                //tem que comparar a info1 
                // caso não encontre, mandar pro centro

            }else{
                //tem que comparar a info e a info 2
                //caso não encontre, mandar pro centro e pra direita
                comparacao2 = strcmp(Info.palavra_ser_excluida, Raiz->info2.palavra_portugues); 

                if(comparacao1 == 0 || comparacao2 == 0){
                    //encontramos, resta saber em qual das infos
                    if(comparacao1 == 0){
                            //recupera o nó e recebe 1 (está na info1)
                            resultado = 1; 
                            *No_recuperado = Raiz; 
                    }else{
                            //recupera o Nó e recebe 2 (está na info2)
                            resultado = 2; 
                            *No_recuperado = Raiz; 
                    }
                    

                }else{
                    //não encontrou, devemos percorrer
                    resultado = armazenar_No_ARV23(Raiz->cen, Info, No_recuperado); 

                    //caso não encontre no centro, deve buscar na direita

                    if(resultado == 0){
                        //Como não foi encontrado nem na esquerda, no atual, e nem no centro, resta ir pra direita
                        resultado = armazenar_No_ARV23(Raiz->dir, Info, No_recuperado); 
                
                    } 

                }


         }
    }   
}

   return resultado;  
}

void imprimir_infos_23_por_unidade(Arv23Port *Raiz, int unidade){
    
    if(Raiz !=NULL){
        ArvBB_ing **vetor_inglesInfo1, **vetor_inglesInfo2; 
        int tamanho_vetor1, tamanho_vetor2, resultado; 
        vetor_inglesInfo1 = NULL; 
        vetor_inglesInfo2 = NULL; 
        tamanho_vetor1 = 0; 
        tamanho_vetor2 = 0; 
        imprimir_infos_23_por_unidade(Raiz->esq, unidade); //manda pra esquerda
        
        //como temos info1, mandaremos agr pra imprimir a ArvBB interna

        resultado = Armazenar_No_ARVBB(Raiz->info1.significados_ingles, unidade, &vetor_inglesInfo1, &tamanho_vetor1); 

        if(resultado == 1){
            if(tamanho_vetor1 != 0){
                printf("A palavra em português '%s' possui as seguintes palavras correspondentes na unidade '%d':\n", Raiz->info1.palavra_portugues, unidade);
                for(int i = 0; i < tamanho_vetor1; i++){
                    printf("Palavra: %s\n", vetor_inglesInfo1[i]->info.palavra_ingles); 
                }
            }    
        }

        //após imprimir, libera a linkagem linear 
        free(vetor_inglesInfo1);


        if(Raiz->n_infos == 2){
            //Nesse caso, como há Info2, precisamos repetir o processo e percorrer sua subárvore
            resultado = Armazenar_No_ARVBB(Raiz->info2.significados_ingles, unidade, &vetor_inglesInfo2, &tamanho_vetor2); 

            if(resultado == 1){
                if(tamanho_vetor2 != 0){
                    printf("A palavra em português '%s' possui as seguintes palavras correspondentes na unidade '%d':\n", Raiz->info2.palavra_portugues, unidade);
                    for(int i = 0; i < tamanho_vetor2; i++){
                        printf("Palavra: %s\n", vetor_inglesInfo2[i]->info.palavra_ingles); 
                    }
                }    
            }

            //após imprimir a info2, liberamos a linkagem linear
            free(vetor_inglesInfo2); 
        } 
        
        
        
        imprimir_infos_23_por_unidade(Raiz->cen, unidade); 

        if(Raiz->n_infos == 2){
            imprimir_infos_23_por_unidade(Raiz->dir, unidade); 
        }

    }
}


//Funções de remoção 

void menor_info_direita(Arv23Port *no, Arv23Port **no_resultado, Arv23Port **pai_no) {
    // Vai até o extremo esquerdo da subárvore direita
    *pai_no = no;

    while (no->esq != NULL) {
        *pai_no = no;
        no = no->esq;
    }

    *no_resultado = no;
}

void menor_info_esquerda(Arv23Port *no, Arv23Port **no_resultado, Arv23Port **pai_no) {
    // Vai até o extremo direito da subárvore esquerda
    *pai_no = no;

    while (no->dir != NULL) {
        *pai_no = no;
        no = no->dir;
    }

    *no_resultado = no;
}



int remove_arv23(Arv23Port **Pai, Arv23Port **raiz, InfArv23 info) {
    int removido = 0;
    Arv23Port *no = NULL, *no1, *pai_no = NULL, *pai_no1 = NULL, **aux;
    aux = (Arv23Port **)malloc(sizeof(Arv23Port *));
    no1 = (Arv23Port *)malloc(sizeof(Arv23Port));

    if (*raiz != NULL) {
        if (ehfolha(*raiz)) {
            if ((*raiz)->n_infos == 2) {
                if (strcmp(info.palavra_portugues, (*raiz)->info2.palavra_portugues) == 0) {
                    (*raiz)->n_infos = 1;
                    removido = 1;
                } else if (strcmp(info.palavra_portugues, (*raiz)->info1.palavra_portugues) == 0) {
                    (*raiz)->info1 = (*raiz)->info2;
                    (*raiz)->n_infos = 1;
                    removido = 1;
                }
            } else if (strcmp(info.palavra_portugues, (*raiz)->info1.palavra_portugues) == 0) {
                if (*Pai == NULL) {
                    //isso vai ser feito externamente
                    removido = 4;
                } else if (*raiz == (*Pai)->esq) {
                    (*raiz)->info1 = (*Pai)->info1;
                    pai_no = *Pai;
                    menor_info_direita((*Pai)->cen, &no, &pai_no);
                    (*Pai)->info1 = no->info1;
                    removido = 1;

                    if (no->n_infos == 2) {
                        no->info1 = no->info2;
                        no->n_infos = 1;
                    } else {
                        if (pai_no->n_infos == 1) {
                            (*raiz)->info2 = no->info1;
                            (*raiz)->n_infos = 2;
                            free(no);
                            *Pai = *raiz;
                        } else {
                            no->info1 = pai_no->info2;
                            pai_no1 = pai_no;
                            menor_info_direita(pai_no->dir, &no1, &pai_no1);
                            pai_no->info2 = no1->info1;

                            if (no1->n_infos == 2) {
                                no1->info1 = no1->info2;
                                no1->n_infos = 1;
                            } else {
                                no->info2 = pai_no->info2;
                                no->n_infos = 2;
                                pai_no->n_infos = 1;
                                free(no1);
                                pai_no1->dir = NULL;
                            }
                        }
                    }
                } else if (*raiz == (*Pai)->cen) {
                    removido = 1;
                    if ((*Pai)->n_infos == 1) {
                        if (((*Pai)->esq)->n_infos == 2) {
                            (*raiz)->info1 = (*Pai)->info1;
                            (*Pai)->info1 = ((*Pai)->esq)->info2;
                            ((*Pai)->esq)->n_infos = 1;
                        } else {
                            ((*Pai)->esq)->info2 = (*Pai)->info1;
                            free(*raiz);
                            ((*Pai)->esq)->n_infos = 2;
                            *aux = (*Pai)->esq;
                            free(*Pai);
                            *Pai = *aux;
                        }
                    } else {
                        (*raiz)->info1 = (*Pai)->info2;
                        pai_no = *Pai;
                        menor_info_direita((*Pai)->dir, &no, &pai_no);
                        (*Pai)->info2 = no->info1;

                        if (no->n_infos == 2) {
                            no->info1 = no->info2;
                            no->n_infos = 1;
                        } else {
                            (*raiz)->n_infos = 2;
                            (*raiz)->info2 = (*Pai)->info2;
                            (*Pai)->n_infos = 1;
                            free(no);
                            (*Pai)->dir = NULL;
                        }
                    }
                } else {
                    removido = 1;
                    pai_no = *Pai;
                    menor_info_esquerda((*Pai)->cen, &no, &pai_no);

                    if (no->n_infos == 1) {
                        no->info2 = (*Pai)->info2;
                        (*Pai)->n_infos = 1;
                        no->n_infos = 2;
                        free(*raiz);
                        *raiz = NULL;
                    } else {
                        (*raiz)->info1 = (*Pai)->info2;
                        (*Pai)->info2 = no->info2;
                        no->n_infos = 1;
                    }
                }
            }
        } else {
            if (strcmp(info.palavra_portugues, (*raiz)->info1.palavra_portugues) < 0) {
                removido = remove_arv23(raiz, &(*raiz)->esq, info);
            } else if (strcmp(info.palavra_portugues, (*raiz)->info1.palavra_portugues) == 0) {
                pai_no = *raiz;
                menor_info_direita((*raiz)->cen, &no, &pai_no);
                (*raiz)->info1 = no->info1;
                remove_arv23(raiz, &(*raiz)->cen, (*raiz)->info1);
                removido = 1;
            } else if (((*raiz)->n_infos == 1) || (strcmp(info.palavra_portugues, (*raiz)->info2.palavra_portugues) < 0)) {
                removido = remove_arv23(raiz, &(*raiz)->cen, info);
            } else if (strcmp(info.palavra_portugues, (*raiz)->info2.palavra_portugues) == 0) {
                pai_no = *Pai;
                menor_info_direita((*Pai)->dir, &no, &pai_no);
                (*raiz)->info2 = no->info1;
                remove_arv23(raiz, &(*raiz)->dir, (*raiz)->info2);
                removido = 1;
            } else {
                removido = remove_arv23(raiz, &(*raiz)->dir, info);
            }
        }
    }

    return removido;
}

int situacao_da_arvore(Arv23Port **Pai, Arv23Port **Raiz, InfArv23 Info) {
    int resposta = 0;

    if ((*Raiz)->n_infos == 1 && (*Raiz)->esq == NULL) { 
       free(*Raiz); 
       *Raiz = NULL; 
       resposta = 1;  
    } else {
       resposta = remove_arv23(Pai, Raiz, Info); 
    }

    return resposta; 
}


void remover_palavra_ingles_pela_unidade(Arv23Port **Raiz, inf_ex Info) {
    int operacao = 0;

    if (*Raiz != NULL) {
        if ((*Raiz)->esq != NULL) {
            remover_palavra_ingles_pela_unidade(&((*Raiz)->esq), Info); // percorre a esquerda
        }
        if ((*Raiz)->cen != NULL) {
            remover_palavra_ingles_pela_unidade(&((*Raiz)->cen), Info); // percorre o centro
        }

        if ((*Raiz)->n_infos == 2 && (*Raiz)->dir != NULL) {
            remover_palavra_ingles_pela_unidade(&((*Raiz)->dir), Info); // percorre a direita, se houver
        }

        // Remoção na árvore binária de busca associada
        operacao = remover_No_ArvBB(&((*Raiz)->info1.significados_ingles), Info);

        if (operacao == 2) {
            printf("Palavra em inglês: %s excluída com sucesso da palavra: %s\n", Info.palavra_ser_excluida, (*Raiz)->info1.palavra_portugues);
        }
        
        if ((*Raiz)->info1.significados_ingles == NULL) {
            printf("Como a Palavra em português: %s não possui mais correspondentes em inglês, a mesma foi excluída\n", (*Raiz)->info1.palavra_portugues);
            situacao_da_arvore(NULL, Raiz, (*Raiz)->info1);
        }

        if ((*Raiz)->n_infos == 2) {
            operacao = remover_No_ArvBB(&((*Raiz)->info2.significados_ingles), Info);

            if (operacao == 2) {
                printf("Palavra em inglês: %s excluída com sucesso da palavra: %s\n", Info.palavra_ser_excluida, (*Raiz)->info2.palavra_portugues);
            }
            
            if ((*Raiz)->info2.significados_ingles == NULL) {
                printf("Como a Palavra em português: %s não possui mais correspondentes em inglês, a mesma foi excluída\n", (*Raiz)->info2.palavra_portugues);
                situacao_da_arvore(NULL, Raiz, (*Raiz)->info2);
            }
        }
    }
}
