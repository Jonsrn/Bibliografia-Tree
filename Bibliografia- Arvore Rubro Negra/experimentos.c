#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>



//Funções de Remoção 
/*
Arv23Port *LocalizarMaiorNo(Arv23Port *Raiz){
    //vai e obtém o maior nó
    Arv23Port *MaiorNo; 
    MaiorNo = NULL; 

    MaiorNo = Raiz;

    if(Raiz->dir != NULL){
        MaiorNo = LocalizarMaiorNo(Raiz->dir); //percorre pra direita até ser NULO
    }else{
        if(Raiz->cen != NULL){
            MaiorNo = LocalizarMaiorNo(Raiz->cen); //após chegar no máximo da direita, vai percorrer até chegar ao máximo do centro (se não for uma folha aqui, claro)
        }
    }
    return MaiorNo;  //Retorna o Maior Nó
}


int remover_info1_NaoFolha(Arv23Port *Raiz){
  //função auxiliar pra remover info1 de um nó que não é folha
  int operacao = 0; //significa que a remoção falhou 
  Arv23Port *NoComMaiorInfoEsq; 
  NoComMaiorInfoEsq = NULL; 

  NoComMaiorInfoEsq = LocalizarMaiorNo(Raiz->esq); //função pra obter o maior nó lá da esquerda 

  if(NoComMaiorInfoEsq->n_infos == 2){// se o maior nó possui duas infos, podemos operar
      Raiz->info1 = NoComMaiorInfoEsq->info2; //minha info1 da raiz atual recebe a info2 do maior nó da subárvore à esquerda
      operacao = removerArv23(&(Raiz->esq), &Raiz, NoComMaiorInfoEsq->info2);
  }else{ //Não tem duas infos
      Raiz->info1 = NoComMaiorInfoEsq->info1; // caso não tivermos 2 infos, vamos usar a info1 do maior nó da subárvore à esquerda e mandar remover o Nó na subárvore (onde lá ocorrerá novas operações)
      operacao = removerArv23(&(Raiz->esq), &Raiz, NoComMaiorInfoEsq->info1); 
  }

  return operacao; 
}

int contarQtdInfos(Arv23Port *Raiz){
    int contador; 
    contador = 0; 

    if(Raiz != NULL){
        contador += 1;

        if(Raiz->n_infos == 2){
            contador += 1;
        } 
        contador += contarQtdInfos(Raiz->esq); 
        contador += contarQtdInfos(Raiz->cen); 
        contador += contarQtdInfos(Raiz->dir); 
    }
    return contador; 
}

int remover_info2_NaoFolha(Arv23Port *Raiz){
    int operacao; 
    operacao = 0; //0 significa que não deu certo

    Arv23Port *MaiorNoCentro; 
    MaiorNoCentro = NULL; //inicia como NULO o nó buscado

    MaiorNoCentro = LocalizarMaiorNo(Raiz->cen); //chama a função pra obter o maior nó do centro.
    
    if(MaiorNoCentro->n_infos == 2){//caso o nó recuperado tenha duas infos, pegaremos a info 2 do nó
        Raiz->info2 = MaiorNoCentro->info2; //passamos a info2 do Maior nó para a Info2 do nosso nó original
        operacao = removerArv23(&(Raiz->cen), &Raiz, MaiorNoCentro->info2); // mandamos remover esse valor da sua subárvore
    }else{//caso só tenha uma info no nó recuperado, utilizaremos ela pra substituir na info2 do nó original
       Raiz->info2 = MaiorNoCentro->info1; //o nó original recebe a info1 do maior nó do centro
       operacao = removerArv23(&(Raiz->cen), &Raiz, MaiorNoCentro->info1); // mandamos remover esse valor da sua subárvore
    }

    return operacao; //0 falha, 1 sucesso
}

Arv23Port *LocalizarMenorNo(Arv23Port *Raiz){
    Arv23Port *MenorNo; 
    MenorNo = NULL; 

    MenorNo = Raiz; 

    if(Raiz->esq != NULL){
        MenorNo = LocalizarMenorNo(Raiz->esq); 
    }

    return MenorNo; 
}

int remover_info2_Folha(Arv23Port *Raiz){
    //caso mais simples, pra remover o  caso da info 2 na folha
    int operacao; 
    operacao = 1; 
    memset(&(Raiz->info2), 0, sizeof(InfArv23)); // Limpa info2
    Raiz->n_infos = 1; //atualizamos o número de infos

    return operacao; 
}

int remover_info2_Direita_SendoFolha(Arv23Port *Raiz, Arv23Port *Pai){
    //A raiz aqui é o filho da direita lá da principal vem (raiz->Dir)
    //o caso onde vai remover uma info de um nó que não é folha, mas que o seu filho da direita é folha

    int operacao; 
    operacao = 0; //0 indica que não deu certo

    if(Raiz->n_infos == 2){//meu nó folha da direita possui duas infos 
       Pai->info2 = Raiz->info1; //A info2 do pai recebe a info1 do meu nó atual (o filho folha da direita)
       Raiz->info1 = Raiz->info2; //A info1 do meu nó folha atual recebe a info2 do meu próprio nó
       memset(&(Raiz->info2), 0, sizeof(InfArv23)); // Limpa info2
       Raiz->n_infos = 1; //atualizamos o número de Infos
       operacao = 1; //Confirmada a remoção
    
    }else{
        //caso a direita do pai que é folha não possua duas infos em seu nó
        if(Pai->cen->n_infos == 2){//verifica se o filho do centro do pai tem duas infos
            Pai->info2 = Pai->cen->info2; //a info2 do pai recebe a info2 do filho do centro do pai
            memset(&(Pai->cen->info2), 0, sizeof(InfArv23)); // Limpa info2 do filho do centro do Pai
            Pai->cen->n_infos = 1; //o numero de infos do filho do centro é atualizado
            operacao = 1; //confirmada a remoção
        
        }else{//O centro não possui duas infos (realizar operação de junção)
           Pai->cen->info2 = Raiz->info1; //o filho do centro do pai recebe na info2 a info1 do filho da direita (junção)
           Pai->cen->n_infos = 2; //o numero de infos do filho do centro do Pai é atualizada
           memset(&(Pai->info2), 0, sizeof(InfArv23));//zeramos a info2 do pai
           Pai->n_infos = 1; //atualizamos o número de infos do pai
           free(Raiz); //liberamos o filho da direita do pai
           Pai->dir = NULL; //o filho da direita do pai se torna NULO
           operacao = 1; // Confirmada a remoção
        }

    }

    return operacao; //0 operação falhou, 1 deu certo

}

int removerArv23(Arv23Port **Raiz, Arv23Port **Pai, InfArv23 Info){ //talvez tenha de trocar o retorno disso aqui 
    int operacao, comparacao1, comparacao2; 
    operacao = 0; //0 significa que a remoção não aconteceu. 

    Arv23Port *MenorNoDireita; 
    MenorNoDireita = NULL; 

    if(*Raiz != NULL){
        comparacao1 = strcmp(Info.palavra_portugues, (*Raiz)->info1.palavra_portugues); //compara o valor buscado com a Info1
        if((*Raiz)->n_infos == 2){//temos duas infos
           comparacao2 = strcmp(Info.palavra_portugues, (*Raiz)->info2.palavra_portugues); //Compara o valor buscado com Info2
           
           if(comparacao1 == 0 || comparacao2 == 0){ //está em uma das duas infos a palavra
              
              if(comparacao2 == 0){//caso onde a palavra está no Info2
                 
                 if(ehfolha(*Raiz)){//Verifica se a info que eu quero remover está em uma folha
                    operacao = remover_info2_Folha(*Raiz); //caso seja folha e a info2 vai ser removida.
                 
                 }else if(ehfolha((*Raiz)->dir)){//Não estamos em uma folha, verificamos se o filho da direita é folha
                    operacao = remover_info2_Direita_SendoFolha((*Raiz)->dir, *Raiz); //Fará as operações de remoção usando o filho direito que é folha

                    
                 }else{
                    //pra situação onde a direita do Nó tbm não é folha

                    if(contarQtdInfos((*Raiz)->dir) > 3){
                        //Há mais de 3 infos naquela subárvore, então dá pra manipular
                        MenorNoDireita = LocalizarMenorNo((*Raiz)->dir); // caso tenha mais do que 3, podemos obter o menor nó na direita e substituir
                        (*Raiz)->info2 = MenorNoDireita->info1; // recebe a info1 do menor nó e substitui onde está a atual info2
                        operacao = removerArv23(&((*Raiz)->dir), Raiz, MenorNoDireita->info1);//manda remover na subárvore o valor que recuperei (o menor)

                    }else{
                        //caso não tenha mais de 3 infos na direita, percorre o centro. 
                        operacao = remover_info2_NaoFolha(*Raiz); //percorrerá o centro, para buscar o maior. 
                    }  
                    




                 }

          }else{
             //caso seja a info1 a ser removida

             if(comparacao1 == 0){
                if(ehfolha(*Raiz)){//Verifica se a Info está em um nó folha
                   operacao = remover_info1_Folha(*Raiz, *Pai); 
                   
                   if(operacao == 3){
                     //caso não tenha info 2, e o nó atual não tenha pai, a raiz da árvore é liberada.
                     free(*Raiz); 
                     *Raiz = NULL;                        
                   }
                }else{
                    //Não é folha

                    operacao = remover_info1_NaoFolha((*Raiz)); //função que cuida de eliminar uma info1 que está em um nó não folha

                  }

               }

              }
           }


        }else{
            //não temos duas infos
            if(comparacao1 == 0){
              //A informação buscada está na info1 desse Nó
              if(ehfolha(*Raiz)){//Verifica se a Info está em um nó folha
                   operacao = remover_info1_Folha(*Raiz, *Pai); //faltou essa função de remover Folha no Info1
                   
                   if(operacao == 3){
                     //caso não tenha info 2, e o nó atual não tenha pai, a raiz da árvore é liberada.
                     free(*Raiz); 
                     *Raiz = NULL;                        
                   }
                }else{
                    //Não é folha

                    operacao = remover_info1_NaoFolha((*Raiz)); //função que cuida de eliminar uma info1 que está em um nó não folha

                  }

            }
            
        }

        //percorrer agora

        if(comparacao1 < 0){
            operacao = removerArv23(&(*Raiz)->esq, Raiz, Info); 
        }else if((*Raiz)->n_infos == 1){
            if(comparacao1 > 0){
                operacao = removerArv23(&(*Raiz)->cen, Raiz, Info); 
            }
        }else if((*Raiz)->n_infos == 2){
            comparacao2 = strcmp(Info.palavra_portugues, (*Raiz)->info2.palavra_portugues);
            if(comparacao2 < 0){
                operacao = removerArv23(&(*Raiz)->cen, Raiz, Info); 
            }else{
                operacao = removerArv23(&(*Raiz)->dir, Raiz, Info);
            }
        }

        if(operacao == 2){
            operacao = balancearArv23(&(*Raiz), &(*Pai), operacao);//2 significa caso o centro do meu pai e o pai não possuam duas infos
        }

    }
    return operacao; 
}

int remover_info1_Folha(Arv23Port *Raiz, Arv23Port *Pai){
    int operacao; 
    operacao = 0; //0 significa que a operação não foi concluída
    
    if(Raiz->n_infos == 2){
        Raiz->info1 = Raiz->info2; //A info1 recebe a Info2
        memset(&(Raiz->info2), 0, sizeof(InfArv23)); // Limpa info2
        Raiz->n_infos = 1; //Atualiza o numero de Infos
        operacao = 1; //Finalizado com sucesso
    }else if(Pai == NULL){
        //como não há duas infos, e também não há pai, significa que estamos na raiz, então aqui atualizamos só a variavel, pq pra liberar o nó precisar ser externamente
        operacao = 3; //no caso o 3 foi definido como status de remoção da raiz
    }else{
        //caso não tenha duas infos naquele nó, e o pai não seja nulo, podemos ir no pai e recuperar o valor que precisamos
        if(Pai->esq == Raiz){ //verifica se o meu nó atual está na esquerda do meu pai
            //Estou na esquerda do meu pai
            
            if(Pai->cen->n_infos == 2){//Se o centro do meu pai, tem duas infos
               
               Raiz->info1 = Pai->info1; //a info1 do pai desce e se torna a minha info1
               Pai->info1 = Pai->cen->info1; //a info1 do pai recebe a info1 que sobe do centro do Pai
               Pai->cen->info1 = Pai->cen->info2; //a info1 do centro do pai, recebe antiga info2 do centro do pai (info1 <- info2)
               memset(&(Pai->cen->info2), 0, sizeof(InfArv23)); //zeramos a info2 do centro do Pai
               Pai->cen->n_infos = 1; //Atualizando o numero de Infos do Centro do Pai
               operacao = 1; //confirmada a remoção 
            
            }else if(Pai->n_infos == 2){//O centro do pai não possui duas infos, mas o próprio pai possui duas infos
               
               Raiz->info1 = Pai->info1; //minha raiz atual recebe a info1 do meu pai
               Raiz->info2 = Pai->cen->info1; //meu nó atual(info 2) recebe a info1 do centro do meu pai (juntou)
               Raiz->n_infos = 2; //Atualiza o numero de Infos da Raiz
               free(Pai->cen); //como o nó do centro não tem mais nada a ser utilizados, liberamos ele
               Pai->info1 = Pai->info2; //info2 do pai passa a ser info1
               memset(&(Pai->info2), 0, sizeof(InfArv23));//zeramos a info2 do pai
               Pai->n_infos = 1; //Atualizando o número de Infos do Pai
               Pai->cen = Pai->dir; //o ponteiro do centro do pai recebe o ponteiro da direita do pai
               Pai->dir = NULL; //direita do pai se torna nulo
               operacao = 1; //Confirmada a remoção
            }else{
                //caso o centro do meu pai e o pai não possuam duas infos

                operacao = 2; 

            }

        }else if(Pai->cen == Raiz){
            //Descubro que minha localização é o centro do Nó Pai.

            if(Pai->esq->n_infos == 2){//Se tiver duas Infos na esquerda do pai
              
               Raiz->info1 = Pai->info1; //minha info1 atual recebe a info 1 do pai
               Pai->info1 = Pai->esq->info2; //A info1 do Pai recebe a Info2 da Esquerda (o maior da esquerda)
               memset(&(Pai->esq->info2), 0, sizeof(InfArv23)); //A info2 da esquerda é zerada
               Pai->esq->n_infos = 1; //Atualizado o numero de Infos da Esquerda do Pai
               operacao = 1; //confirmada a remoção

            }else if(Pai->n_infos == 2){//Se a esquerda do pai não há duas infos, verificamos se o pai possui duas infos
               //O pai possui duas infos
               
               if(Pai->dir->n_infos == 2){//Com duas infos no pai, verificamos se a direita do Pai possui duas infos
                   //A direita do Pai possui duas Infos
                  
                   Raiz->info1 = Pai->info2; //minha info1 atual recebe a info2 do pai
                   Pai->info2 = Pai->dir->info1; //A info2 do pai recebe a Info1 do seu filho da direita
                   Pai->dir->info1 = Pai->dir->info2; //A info1 do filho da direita, recebe a info2 do filho da direita 
                   memset(&(Pai->dir->info2), 0, sizeof(InfArv23)); //zeramos a info2 do filho da direita
                   Pai->dir->n_infos = 1; //Atualiza o numero de Infos do filho da direita 
                   operacao = 1; //confirmada a remoção

               }else{ //A direita do pai não possui duas infos
                   Raiz->info1 = Pai->info2; //A info1 do nó atual recebe a info2 do pai
                   Raiz->info2 = Pai->dir->info1; //A info2 do Nó atual, recebe a info1 do filho da direita do pai
                   Raiz->n_infos = 2; //Atualiza o número de infos da Raiz
                   memset(&(Pai->info2), 0, sizeof(InfArv23)); //Zera a info2 do Pai
                   Pai->n_infos = 1; //Atualiza o numero de Infos do Pai
                   free(Pai->dir); //Libera o Filho da direita do Pai
                   Pai->dir = NULL; //O filho da direita recebe NULO
                   operacao = 1; //operação concluida com sucesso



               }

            }else{
                //Se o pai não possui duas infos, entra em outra condição
                
                operacao = 2; 

            }

        }else{
            //Se o meu nó atual não está na esquerda do pai, e nem no centro do pai, ele está na direita

            if(Pai->cen->n_infos == 2){//Verificamos se o filho do centro do Pai tem dois filhos
                
                Raiz->info1 = Pai->info2; //Info1 atual vai receber a info2 do pai
                Pai->info2 = Pai->cen->info2; //info2 do pai vai receber a info2 do filho do centro
                memset(&(Pai->cen->info2), 0, sizeof(InfArv23));//zeramos a info2 do filho do centro
                Pai->cen->n_infos = 1; // atualizamos o número de infos do filho do centro pra 1
                operacao = 1; //Concluido com sucesso

            }else{//caso o filho do centro não tenha 2 infos
               
               Pai->cen->info2 = Pai->info2; //info2 do filho do centro do pai, recebe a info 2 do pai
               Pai->cen->n_infos = 2; //o numero de infos do filho do centro do pai é atualizada
               memset(&(Pai->info2), 0, sizeof(InfArv23)); //Zera a informação de info2 do pai
               Pai->n_infos = 1; //Atualiza o numero de Infos do Pai
               free(Pai->dir); //libera o nó do filho da direita do pai
               Pai->dir = NULL; //O filho da direita é NULO
               operacao = 1; //remoção confirmada


            }

        }
    }

    return operacao; 

}

int balancearArv23(Arv23Port **Raiz, Arv23Port **Pai, int removeu){
    //função responsável por balancear

    if(*Pai == NULL){ //se o pai for nulo, significa que estamos na raiz da árvore
       (*Raiz) = (*Raiz)->esq; //raiz atual recebe a raiz da esquerda
       removeu = 1; //confirmada a remoção

    }else{
        //Caso o pai não seja NULO

        if((*Pai)->esq == (*Raiz)){ // caso eu seja o filho da esquerda do nó pai
           
           if((*Pai)->cen->n_infos == 2){ //caso o filho do centro do meu pai tenha 2 infos
              
               (*Raiz)->info1 = (*Pai)->info1; //minha raiz atual, info1, recebe a info1 do meu pai 
               (*Raiz)->cen = (*Pai)->cen->esq; //a minha raiz atual recebe recebe o filho da esquerda do filho do Centro do Pai (Basicamente o filho do centro do pai, vai ceder seu filho da esquerda, para ser o centro do meu nó atual)
               (*Pai)->info1 = (*Pai)->cen->info1; //Info1 do pai recebe a info1 do seu filho do centro
               (*Pai)->cen->info1 = (*Pai)->cen->info2;  //a info1 do filho do centro do pai recebe a info2 do mesmo nó
               memset(&((*Pai)->cen->info2), 0, sizeof(InfArv23)); //zeramos a info2 do filho do centro do pai
               (*Pai)->cen->n_infos = 1; //atualizamos o numero de infos do centro do pai
               (*Pai)->cen->esq = (*Pai)->cen->cen; //A esquerda do filho do centro do pai, recebe o filho do centro do centro do pai.(confuso ? eu sei)
               (*Pai)->cen->cen = (*Pai)->cen->dir; //filho do centro, do centro do pai, recebe o filho da direita do centro do pai.
               (*Pai)->cen->dir = NULL; //direita do filho do centro do pai se torna NULA
               removeu = 1; //confirmada a remoção
           
           }else{  //o filho do centro do pai não tem duas infos

                if((*Pai)->n_infos == 2){
                    //verifica se o pai possui duas infos

                    (*Raiz)->info1 = (*Pai)->info1; //minha raiz atual recebe na info1 a info1 do meu pai
                    (*Raiz)->info2 = (*Pai)->cen->info1; //minha raiz atual na info2 recebe a info1 do filho do centro do meu pai (junção)
                    (*Raiz)->n_infos = 2; //atualiza o número de infos da minha raiz para 2
                    (*Raiz)->cen = (*Pai)->cen->esq; //Minha raiz do centro recebe o filho da esquerda do filho do Centro do Pai
                    (*Raiz)->dir = (*Pai)->cen->cen; //Minha raiz da direita recebe o filho da direita do filho do centro do pai
                    
                    free((*Pai)->cen);  //o filho do centro do pai é liberado

                    (*Pai)->info1 = (*Pai)->info2; //A info2 do pai se torna a Info1 do pai
                    memset(&((*Pai)->info2), 0, sizeof(InfArv23)); //Info do 2 do pai é zerada
                    (*Pai)->n_infos = 1; //numero de infos do pai é atualzada
                    (*Pai)->cen = (*Pai)->dir; //O filho do centro do pai recebe o filho do centro do pai
                    (*Pai)->dir = NULL; //o filho da direita do pai recebe NULO
                    removeu = 1;

                }else{
                    //O pai não possui duas infos
                    printf("Balanceamento: Linha 428, O pai não possui duas infos, Esquerda da Raiz\n"); 

                    /*

                    /// Ajuste baseado no comportamento funcional da remoção no centro
                    (*Pai)->esq->info2 = (*Pai)->info1;         // info1 do Pai vai para info2 do filho esquerdo
                    (*Pai)->esq->n_infos = 2;                   // Atualizar o número de informações no filho esquerdo
                    (*Pai)->esq->dir = (*Pai)->cen->esq;        // Atribuir corretamente o filho direito do esq
                    if ((*Pai)->cen != NULL) {
                        free((*Pai)->cen);                      // Liberar o nó centro somente se não for NULL
                        (*Pai)->cen = NULL;                     // Atribuir NULL ao centro para evitar duplicação
                    }                        // Centro se torna NULL
                    removeu = 1;
                    

                    
                                    
                    

                    (*Raiz)->info1 = (*Pai)->info1; //A minha info1 atual recebe a info1 do meu pai
                    (*Raiz)->info2 = (*Pai)->cen->info1; //A minha Info2 atual recebe a info1 do filho do centro do Pai
                    (*Raiz)->n_infos = 2; //Atualiza o numero de infos do meu nó atual
                    (*Raiz)->cen = (*Pai)->cen->esq; //Atualiza filho do centro do meu nó, pra receber o filho da esquerda do Centro que é filho do Pai (Confuso ? Muito)
                    (*Raiz)->dir = (*Pai)->cen->cen; //Atualiza meu filho da direita para receber o filho do centro, do filho centro, do meu pai
                    free((*Pai)->cen); //libera o filho do centro do pai
                    (*Pai)->cen = NULL; //filho do centro do pai recebe NULO
                    
                                       


                    
                    
                    
                    removeu = 1; 

                    //Na verdade o segmentation fault é aqui. 

                }

           }
        }else if((*Pai)->cen == (*Raiz)){

            // Eu estou no filho do centro do meu Pai
            if((*Pai)->esq->n_infos == 2){ //o filho da esquerda do meu pai tem dois filhos
                
                (*Raiz)->info1 = (*Pai)->info1; // Minha raiz atual, na info1, recebe a info1 do meu pai
                (*Pai)->info1 = (*Pai)->esq->info2; //A info1 do meu pai, recebe a info2 do filho da esquerda do meu pai
                (*Raiz)->cen = (*Raiz)->esq; //O filho do Centro do meu nó atual, recebe a raiz da esquerda do meu nó atual
                (*Raiz)->esq = (*Pai)->esq->dir; //O filho da esquerda do meu nó recebe o filho da direita, sendo filho da esquerda do meu pai
                (*Pai)->esq->dir = NULL;  //A direita do filho da esquerda do meu pai recebe NULO
                (*Pai)->esq->n_infos = 1; //Atualiza o numero de Infos da esquerda do pai
                memset(&((*Pai)->esq->info2), 0, sizeof(InfArv23)); //zera a info2 da esquerda do meu pai
                removeu = 1; //confirmado


            }else{
                //Não temos dois filhos na esquerda do pai
                
                if((*Pai)->n_infos == 2){//O pai possui duas infos
                    
                    (*Pai)->esq->info2 = (*Pai)->info1; //A info2 do filho da esquerda do pai recebe a info1 do pai
                    (*Pai)->esq->n_infos = 2; //atualiza o numero de infos no filho da esquerda do pai
                    (*Pai)->esq->dir = (*Raiz)->esq; //O filho da direita do filho da esquerda do pai recebe minha raiz esquerda
                    free(*Raiz); //libero minha própria raiz
                    *Raiz = NULL; //Raiz se torna nula
                    free((*Pai)->cen); //Libero o filho do Centro do Pai
                    (*Pai)->cen = NULL; //O filho do Centro do Pai recebe NULO
                    (*Pai)->info1 = (*Pai)->info2; //Info1 do pai recebe info2 do pai
                    memset(&((*Pai)->info2), 0, sizeof(InfArv23)); //Zero a Info2 do Pai
                    (*Pai)->n_infos = 1; //atualizo o numero de infos do pai
                    (*Pai)->cen = (*Pai)->dir; // o filho do centro do pai, recebe o filho da direita do pai
                    (*Pai)->dir = NULL; 
                    removeu = 1;                    

                }else{
                    //o pai não possui duas infos

                    //(*Pai)->esq->info2 = (*Pai)->info1; //A info2 do filho da esquerda do pai, recebe a info1 do pai
                    //(*Pai)->esq->n_infos = 2; //atualiza o numero de infos do filho da esquerda do pai
                    //(*Pai)->esq->dir = (*Pai)->cen->esq; //o filho da direita do filho da esquerda do pai, recebe o filho da esquerda do filho do centro do pai (travalinguas ?)
                    
                    (*Pai)->esq->info2 = (*Pai)->info1; //A info2 do filho da esquerda do pai, recebe a info1 do pai
                    (*Pai)->esq->n_infos = 2;//atualiza o numero de infos do filho da esquerda do pai
                    (*Pai)->esq->dir = (*Pai)->cen->esq;//o filho da direita do filho da esquerda do pai, recebe o filho da esquerda do filho do centro do pai (travalinguas ?)
                    free((*Pai)->cen); //Liberamos o filho do centro do Pai
                    (*Pai)->cen = NULL; //Filho do centro do pai se torna nulo

                    

                    removeu = 1; //aqui 

                }



            }
        }else{
            //Se não estou nem na esquerda, e nem no Centro do pai, estou na direita dele

            if((*Pai)->cen->n_infos == 2){
               //Se o filho do centro do meu pai possuir duas infos
               (*Raiz)->info1 = (*Pai)->info2; //a info1 da minha raiz recebe a info2 do meu pai
               (*Raiz)->cen = (*Raiz)->esq; // o filho do centro da minha raiz recebe o filho da esquerda da minha raiz
               (*Raiz)->esq = (*Pai)->cen->dir; //O filho da esquerda da minha raiz recebe o filho da direita do filho do centro do meu pai
               (*Pai)->info2 = (*Pai)->cen->info2; //A info2 do pai recebe a info2 do filho do centro do pai
               memset(&((*Pai)->cen->info2), 0, sizeof(InfArv23)); //info 2 do filho do centro do pai é zerado
               (*Pai)->cen->n_infos = 1; //numero de infos do filho do centro do pai é atualizado
               (*Pai)->cen->dir = NULL; //filho da direita do filho do centro do pai vira NULO


            }else{//o filho do centro do meu pai não possui duas infos
                (*Pai)->cen->info2 = (*Pai)->info2; //Info2 do filho do centro do pai recebe a Info2 do Pai
                (*Pai)->cen->n_infos = 2; //Atualiza o numero de infos do filho do centro do Pai
                (*Pai)->cen->dir = (*Raiz)->esq; //O filho da direita do filho do centro do pai recebe o filho da esquerda da minha raiz
                free(*Raiz); //libero a raiz atual
                *Raiz = NULL; //raiz se torna NULA
                memset(&((*Pai)->info2), 0, sizeof(InfArv23)); //Zeramos a Info2 do pai
                (*Pai)->n_infos = 1; //Atualizamos o número de Infos do Pai
                free((*Pai)->dir); //Liberamos a direita do Pai
                (*Pai)->dir = NULL; 


            }
            removeu = 1; 

        }
    }

    return removeu; 

}

*/

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
                    //free(*raiz);
                    //*raiz = NULL;
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

int situacao_da_arvore(Arv23Port **Pai, Arv23Port **Raiz, InfArv23 Info){
    int resposta;
    resposta = 0;
    

    if((*Raiz)->n_infos == 1 & (*Raiz)->esq == NULL){
       free(Raiz); 
       *Raiz = NULL; 
       resposta = 1;  
    }else{
       resposta  = remove_arv23(Pai, Raiz, Info); 
    }

    

    return resposta; 
    
}


int main() {
    Arv23Port *Raiz = NULL;
    InfArv23 info;
    int situacao, info_posicao;
    Arv23Port *no_referencia = NULL;
    int opcao;

    printf("Árvore 2-3 - Menu de operações:\n");

    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Inserir uma palavra\n");
        printf("2 - Remover uma palavra\n");
        printf("3 - Imprimir a árvore\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Inserir palavra
                printf("Digite a palavra em português para inserir: ");
                scanf("%s", info.palavra_portugues);
                insereArv23(&Raiz, info, NULL, NULL, &situacao, &info_posicao, &no_referencia);
                printf("Palavra '%s' inserida com sucesso!\n", info.palavra_portugues);
                break;

            case 2:
                // Remover palavra
                printf("Digite a palavra em português para remover: ");
                scanf("%s", info.palavra_portugues);
                if (situacao_da_arvore(NULL, &Raiz, info)) {
                    printf("Palavra '%s' removida com sucesso!\n", info.palavra_portugues);
                } else {
                    printf("Falha ao remover: palavra '%s' não encontrada.\n", info.palavra_portugues);
                }
                break;

            case 3:
                // Imprimir a árvore
                printf("Estado atual da árvore:\n");
                imprimirArv23(Raiz, 0);  // Função para exibir a árvore
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}