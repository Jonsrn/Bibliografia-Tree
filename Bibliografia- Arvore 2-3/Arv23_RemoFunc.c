#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliografia.h"


//Aqui nesse arquivo vão ficar as funcionalidades de remoção da Arv23 




int contar_descendentes(Arv23Port *Raiz){
    int qtd; 
    qtd = 0;
    if(Raiz != NULL){
        qtd += contar_descendentes(Raiz->esq); 

        if(Raiz->n_infos >= 1 && Raiz->n_infos <= 2) {
            qtd += Raiz->n_infos;
       }

        qtd += contar_descendentes(Raiz->cen); 
        qtd += contar_descendentes(Raiz->dir); 
    }
    return qtd; 
}


InfArv23 Pegar_Maior(Arv23Port *Raiz, int *operacao) {
    // Itera até encontrar o maior elemento
    *operacao = 0; //não deu certo
    InfArv23 Info;
    if(Raiz != NULL){
        while (Raiz->dir != NULL || (Raiz->n_infos == 1 && Raiz->cen != NULL)) {
            if (Raiz->dir != NULL) {
                Raiz = Raiz->dir; // Vai para o filho direito se existir
            } else {
                Raiz = Raiz->cen; // Caso contrário, vai para o filho central
            }
        }

        Info = (Raiz->n_infos == 2) ? Raiz->info2 : Raiz->info1;
        *operacao = 1; //sucesso

    }    

    // Se o nó tem 2 informações, retorna a maior (info2), senão retorna a única (info1)
    return Info;
}

InfArv23 Pegar_Menor(Arv23Port *Raiz, int *operacao) {
    // Itera até encontrar o menor elemento
    *operacao = 0; //Não deu certo
    InfArv23 Info; 
   
    if(Raiz != NULL){
        while (Raiz->esq != NULL) { // Vai sempre para o filho esquerdo
            Raiz = Raiz->esq;
        }

       
        Info = Raiz->info1; 
        *operacao = 1; //deu certo
        

    }

    // Retorna o status
    return Info;
}

int RemoverInfo1Folha(Arv23Port **Raiz, Arv23Port **Pai){
    int operacao; 
    operacao = 0; //não manipulou
    if(*Raiz != NULL){
        //Primeiro, temos que saber onde estamos, se estamos na esquerda do Pai, no Centro dele ou na direita
        if((*Pai)->esq == *Raiz){
            //estou na esquerda do meu pai
            if((*Pai)->cen->n_infos == 2){
                //se o filho do centro do pai, tem dois filhos, eu consigo puxar. 
                (*Raiz)->info1 = (*Pai)->info1; //Minha Raiz atual vai receber a Info 1 do meu pai; 
                (*Pai)->info1 = (*Pai)->cen->info1; //A info1 do filho do centro, sobe. 
                (*Pai)->cen->info1 = (*Pai)->cen->info2; //A info2 do filho do centro, passa a ser Info1
                (*Pai)->cen->n_infos = 1; //Numero de Infos do Filho do Centro é atualizado;
                operacao = 1; //remoção bem sucedida
            }else{
                //O filho do Centro do Pai não tem duas Infos que pena :( 
                //dá pra manipular ainda (talvez)

                //Se o Pai tiver Duas Infos, dá pra manipular 
                if((*Pai)->n_infos == 2){
                     //Se o Pai tem duas Infos, temos duas situações, 1 O filho da direita tem duas Infos, o Filho da direita tem uma Info

                     if((*Pai)->dir->n_infos == 2){
                        //O primeiro caso, o Filho da Direita tem duas Infos; 
                        //Nesse caso, faremos o movimento de Onda
                        
                        (*Raiz)->info1 = (*Pai)->info1; // Minha Info Atual vai receber a Info1 do Pai
                        (*Pai)->info1 = (*Pai)->cen->info1; //O pai, vai receber a Info1 do Filho do centro
                        (*Pai)->cen->info1 = (*Pai)->info2; //A Info1 do filho do Centro do Pai, vai receber a Info2 do Pai
                        (*Pai)->info2 = (*Pai)->dir->info1; //A Info2 do Pai, vai receber a Info1 do Filho da Direita do Pai
                        (*Pai)->dir->info1 = (*Pai)->dir->info2; //A info1 do Filho da Direita do Pai, vai receber a Info2 do Filho da direita do Pai
                        (*Pai)->dir->n_infos = 1; //Numero de Infos do Filho da Direita do Pai atualizado
                        operacao = 1; 
                     }else{
                        //O segundo caso, O filho da Direita tem Uma Info
                        //Nesse caso, faremos agrupamento

                        (*Raiz)->info1 = (*Pai)->info1; // Minha Info Atual vai receber a Info1 do Pai
                        (*Pai)->info1 = (*Pai)->cen->info1; //O pai, vai receber a Info1 do Filho do centro
                        (*Pai)->cen->info1 = (*Pai)->info2; //A Info1 do filho do Centro do Pai, vai receber a Info2 do Pai
                        (*Pai)->cen->info2 = (*Pai)->dir->info1; //Agrupamos, a Info1 do Filho da direita passa a ser a Info2 do Filho do Centro
                        (*Pai)->cen->n_infos = 2; //numero de infos do filho do centro é atualizado; 
                        (*Pai)->n_infos = 1; //Numero de Infos do Pai é atualizada; 
                        free((*Pai)->dir); //Libera a antiga direita
                        (*Pai)->dir = NULL; //Direita do Pai agora é NULA;            
                        operacao = 1;   



                     }


                     
                    

                }else{
                    //O Pai não possui duas Infos, e também o filho do Centro só possui uma Info, por aqui não dá pra fazer mais nada
                    
                    //Isso vai ficar pra outra função; 

                     operacao = 2; //caso não coberto



                }

            }


        }else if((*Pai)->cen == *Raiz){
            //estou no centro do meu pai
            
            //primeiro, eu verifico se meu Pai tem duas Infos

            if((*Pai)->n_infos == 2){
                //Como o Pai tem duas Infos, é melhor pra manipular por onda, mas antes é preciso ver se a direita possui uma ou duas Infos
                if((*Pai)->dir->n_infos == 2){
                   //O filho da Direita Possui Duas Infos
                   (*Raiz)->info1 = (*Pai)->info2; //Minha Raiz Atual vai receber a Info2 do Pai
                   (*Pai)->info2 = (*Pai)->dir->info1; //A info2 do Pai recebe a Info1 do Filho da Direita
                   (*Pai)->dir->info1 = (*Pai)->dir->info2; //A Info1 do Filho da Direita do Pai vai receber a Info2 da Direita do Pai
                   (*Pai)->dir->n_infos = 1; //Numero de Infos da Direita do Pai é atualizado pra 1
                   operacao = 1; // sucesso
                }else{
                    //O filho da Direita do Pai não possui duas Infos, agruparemos então
                    
                    (*Raiz)->info1 = (*Pai)->info2; //Minha Info1 da raiz atual recebe a Info2 do Pai
                    (*Raiz)->info2 = (*Pai)->dir->info1; //Minha Info2 da Raiz Atual recebe a Info1 do Filho da Direita; 
                    (*Raiz)->n_infos = 2; //Numero de Infos da Raiz atual atualizado
                    (*Pai)->n_infos = 1; //Numero de Infos do Pai Atualizado
                    free((*Pai)->dir); //Liberado o Nó da Direita
                    (*Pai)->dir = NULL; // O filho da direita do Pai agore é NULO; 
                    operacao = 1; //sucesso

                }

            }else{
                //O pai não possui duas Infos, olharemos então pra esquerda, veremos se é possivel fazer a onda. 
                if((*Pai)->esq->n_infos == 2){
                    //O filho da esquerda possui duas Infos, então dá pra manipular; 
                    (*Raiz)->info1 = (*Pai)->info1; //A Raiz atual recebe A Info1 do Pai
                    (*Pai)->info1 = (*Pai)->esq->info2; //A info1 do Pai, recebe a Info2 do Filho da Esquerda do Pai
                    (*Pai)->esq->n_infos = 1; //O numero de Infos do Filho da Esquerda é atualizado para 1
                    operacao = 1; //sucesso;
                }else{
                    //Há apenas Uma Info na Esquerda, aqui nessa sub-árvore não é possivel manipular daqui. 

                    operacao = 2; //caso não coberto
                }


            }




        }else if((*Pai)->n_infos == 2 && (*Pai)->dir == *Raiz){
            //estou na direita do meu pai
            // como estou na direita, já temos a certeza de que temos como manipular

            //Se o Filho do Centro possuir duas Infos
            if((*Pai)->cen->n_infos == 2){
                //Nesse caso, faremos a onda
                (*Raiz)->info1 = (*Pai)->info2; //A Info1 da minha raiz atual recebe a Info 2 do Pai
                (*Pai)->info2 = (*Pai)->cen->info2; //A Info2 do Pai recebe a Info2 do Filho do Centro
                (*Pai)->cen->n_infos = 1; //Atualiza o numero de Infos do Filho do centro 
                operacao = 1; //sucesso
            }else{
                //O filho do Centro não possui duas Infos, então olharemos se o Filho da Esquerda do Pai possui duas Infos
 
                if((*Pai)->esq->n_infos == 2){
                    //O filho da esquerda do Pai possui duas Infos, dá pra fazer a Onda
                    (*Raiz)->info1 = (*Pai)->info2; 
                    (*Pai)->info2 = (*Pai)->cen->info1; //A info1 do Filho do Centro sobe para ser a Info2 do Pai
                    (*Pai)->cen->info1 = (*Pai)->info1; //A Info1 do Pai desce pra ser a Info1 do Filho do Centro
                    (*Pai)->info1 = (*Pai)->esq->info2; //A Info2 do Filho da Esquerda do Pai sobe para se Tornar a Info1 do Pai
                    (*Pai)->esq->n_infos = 1; //Numero de Infos do Filho da Esquerda é atualizado
                    operacao = 1; //sucesso
                }else{
                    //O filho da Esquerda não tem duas Infos, então nos livraremos do nó atual, e desceremos a Info2 do Pai pro Info2 do Centro
                    (*Pai)->cen->info2 = (*Pai)->info2; //A Info2 do Pai, desce para se tornar a Info2 do Filho do Centro
                    (*Pai)->n_infos = 1; //Numero de Infos do Pai é atualizado
                    (*Pai)->cen->n_infos = 2; //Numero de Infos do Filho do centro é atualizado pra 2  
                    operacao = 1; //sucesso   //O ideal seria dar um free lá fora   
                    free(*Raiz); //Liberado o Nó atual      
                    (*Pai)->dir = NULL; //Direita do Pai se torna Nula

                }  

            }


        } 



    }

    return operacao;
}


int agregar_infos(Arv23Port **Raiz, int posicao){
   int operacao; 
   operacao = 0; //Não deu certo

   if(*Raiz != NULL){
      //se a posição for 2, significa que a info está na Info2, e que a agregação vai ocorrer no Centro e na direita
      //Se a posição for 1, significa que só temos uma Info, e que a agregação vai ocorrer entre esquerda e Centro

      if(posicao == 2){
          //Primeiro, ajustamos as Infos que já estão no Centro
          (*Raiz)->cen->esq->info2 = (*Raiz)->cen->info1; //A Info1 do Filho do Centro desce para se tornar a Info2 da sua esquerda
          (*Raiz)->cen->esq->n_infos = 2; //Numero de Infos da Esquerda do Centro é atualizado pra 2
          (*Raiz)->cen->info1 = (*Raiz)->cen->cen->info1; //O filho do filho do Centro sobe para se tornar a Info1 do Centro
          (*Raiz)->n_infos = 1; //Numero de Infos da Raiz é atualizado
          //Com isso, o proximo passo, é agregar
          (*Raiz)->cen->info2 = (*Raiz)->dir->info1; //A Info1 da Direita, agrega, e se torna a Info2 do Centro
          
          //mudei para usar o endereço do nó diretamente
          (*Raiz)->cen->cen = (*Raiz)->dir->esq; //A Info1 do Filho da Esquerda do Filho da Direita, se torna a Info1 do Filho do Filho do Centro
          (*Raiz)->cen->dir = (*Raiz)->dir->cen; //O nó do Filho do Centro do Filho da Direita, se torna a Info1 do Filho da Direita do Filho do Centro
          
          (*Raiz)->cen->n_infos = 2; //Numero de Infos do Filho do Centro é atualizado
          //free((*Raiz)->dir->esq); //Liberado o Nó do Filho da Esquerda da Direita
          free((*Raiz)->dir); //Liberado o Nó da Direita da Raiz
          (*Raiz)->dir = NULL; 

          operacao = 1; //sucesso, agregado




      }else if(posicao == 1){
         //O valor a ser removido está na posição 1, mas temos duas situações, a primeira, é se a info é unica no nó, e a segunda é se temos duas Infos
         if((*Raiz)->n_infos == 1){
            Arv23Port *aux; 
            //Só temos uma Info no Nó, isso significa que a agregação vai ocorrer na Esquerda e no Centro
            //Primeiro passo, é ajustar as Infos na Esquerda
            (*Raiz)->esq->esq->info2 = (*Raiz)->esq->info1; //A Info1 do Filho da Esquerda desce e passa a ser a Info2 do Filho da Esquerda Esquerda
            (*Raiz)->esq->esq->n_infos = 2; //Numero de Infos é atualizado pra 2
            (*Raiz)->esq->info1 = (*Raiz)->esq->cen->info1; //Info1 do Filho do Centro do Filho da Esquerda sobe para se tornar a Info1 da Esquerda
            //Com a composição inicial feita, proximo passo, é pegar as Infos que estão no Centro
            (*Raiz)->esq->info2 = (*Raiz)->cen->info1; //Info1 do Filho do Centro se torna a Info2 do Filho da Esquerda
            (*Raiz)->esq->n_infos = 2; //Numero de Infos da Esquerda é atualizado pra 2
            (*Raiz)->esq->cen = (*Raiz)->cen->esq; //A info1 filho da esquerda do Filho do Centro, se torna a Info1 do filho do Centro da Esquerda
            (*Raiz)->esq->dir = (*Raiz)->cen->cen; //O Nó do centro do Do centro, se torna o Nó da Direita da Esquerda
            free((*Raiz)->cen); //Libera o Filho do Centro
            aux = *Raiz; //Raiz original vai pro auxiliar
            *Raiz = (*Raiz)->esq; //A nova Raiz local passa a ser esquerda
            free(aux);

            operacao = 1; 

         }


      }
   }

   return operacao; 
}


int Remover_Info_Nao_Folha(Arv23Port **Raiz, int Localizacao){
   int operacao = 1; //Deu certo
   InfArv23 Aux;
   

   if(*Raiz != NULL){
       int qtd_descendentes; 

       if((*Raiz)->n_infos == 2){
                    //Temos duas Infos aqui
                    //Então temos Uma direita pra olhar/manipular
                    
                    if(Localizacao == 2){
                        //Minha Info a ser eliminada está na Info2 do Nó. 
                        
                        //olhando minha direita. 
                        if((*Raiz)->dir != NULL && (*Raiz)->dir->n_infos == 2){
                            //O filho da Direita possui duas Infos, dá pra manipular
                            if(ehfolha((*Raiz)->dir)){
                                //A direita é folha, ou seja, podemos manipular sem se preocupar com reajuste de filhos
                                (*Raiz)->info2 = (*Raiz)->dir->info1; //A Info2 da minha raiz atual recebe a Info1 da Minha Direita
                                (*Raiz)->dir->info1 = (*Raiz)->dir->info2; //A info1 do Filho da Direita recebe a Info2 do seu mesmo nó
                                (*Raiz)->dir->n_infos = 1; //Numero de Infos do Filho da Direita é atualizado
                        
                            }else{
                                //A minha direita não é folha, então temos uma sub-árvore, vamos então contar quantos descendentes tem aqui
                                qtd_descendentes = contar_descendentes((*Raiz)->dir); 

                                if(qtd_descendentes >3){
                                    //Possuindo mais do que 3 Descendentes dá pra manipular 
                                    
                                    Aux = Pegar_Menor((*Raiz)->dir, &operacao);                                                                    
                                    
                                    
                                     if(operacao == 1){
                                        (*Raiz)->info2 = Aux;
                                        operacao = Remover_Arv23(&((*Raiz)->dir), NULL, (*Raiz)->info2);
                                     }
                                
                                    

                                }else{ 
                                    operacao = agregar_infos(Raiz, 2); //2 significa que a Info está na posição 2
                                    //Não temos como manipular com descendentes, então o jeito vai ser agregar
                                }

                            }
                            
                            
                        }else{
                            //Minha direita não possui duas Infos, olharemos então pro Centro
                            
                            if(ehfolha((*Raiz)->cen)){
                                if((*Raiz)->cen->n_infos == 2){
                                    //O Centro possui duas Infos, dá pra manipular
                                    (*Raiz)->info2 = (*Raiz)->cen->info2; //A info2 do Filho do Centro sobe para ser a Nova Info2 da Raiz Atual
                                    (*Raiz)->cen->n_infos = 1; //Numero de Infos do Filho do Centro é atualizado
                                    operacao = 1; //sucesso
                                }else{
                                    //Como a direita e o Centro não possuem duas Infos, Vamos Agrupar
                                    (*Raiz)->cen->info2 = (*Raiz)->dir->info1; //A Info2 do Filho do Centro recebe a Info1 do Filho da Direita
                                    (*Raiz)->cen->n_infos = 2; //O numero de Infos do Filho do Centro é atualizado pra 2
                                    (*Raiz)->n_infos = 1; //O numero de Infos da Raiz atual é atualizado pra 1
                                    free((*Raiz)->dir); //O nó da direita é liberado
                                    (*Raiz)->dir = NULL; //direita NULA agora
                                    operacao = 1; //sucesso
                                }
                            }else{
                                // O centro não é folha, contaremos os descendentes
                                qtd_descendentes = contar_descendentes((*Raiz)->cen); 

                                if(qtd_descendentes > 3){
                                    //Temos mais do que 3 Infos, dá pra manipular
                                    Aux = Pegar_Maior((*Raiz)->cen, &operacao); //Pega o menor da sub-arvore do centro
                                    
                                                                       
                                    if(operacao == 1){
                                        (*Raiz)->info2 = Aux;
                                        operacao = Remover_Arv23(&((*Raiz)->cen), NULL, (*Raiz)->info2); 
                                    }
                                    
                                    
                                }else{
                                    //Não temos descendentes suficientes no Centro, pra Manipular dessa forma
                                    operacao = agregar_infos(Raiz, 2); //2 Significa que a informação está na Info2
                                }
                            }    
                        }  

                    }else if(Localizacao == 1){
                        //A Info encontrada está na Info1 do Nó
                        
                        //primeiro verificamos se temos duas Infos no Nó. (vai facilitar a manipulação)

                        if(ehfolha((*Raiz)->esq)){ 
                            //Se a esquerda for Folha, sabemos por consequencia que o centro e a direita (se existir) também são folhas
                            
                            if(((*Raiz)->cen) != NULL && (*Raiz)->cen->n_infos == 2){
                                //como temos duas Infos no filho do centro, Info1 pode subir
                                (*Raiz)->info1 = (*Raiz)->cen->info1; //A Info1 do Filho do Centro subiu para ser a nova Info1 da Raiz atual
                                (*Raiz)->cen->info1 = (*Raiz)->cen->info2; //A antiga Info2 do Filho do Centro, se torna a nova Info1 do Centro
                                (*Raiz)->cen->n_infos = 1; //Numero de Infos da Raiz do Filho do Centro é atualizada pra 1;
                                operacao = 1; //sucesso
                            }else{
                                //O filho do Centro não possui dois Filhos, olhamos na direita então
                                if((*Raiz)->dir != NULL && (*Raiz)->dir->n_infos == 2){
                                    //A direita possui duas Infos, facilita a manipulação
                                    //Movimento de Onda agora
                                    (*Raiz)->info1 = (*Raiz)->cen->info1; //A info1 do Filho do Centro Sobe
                                    (*Raiz)->cen->info1 = (*Raiz)->info2; //Info2 da Raiz desce para o Centro
                                    (*Raiz)->info2 = (*Raiz)->dir->info1; //Info1 da direita sobe para ser a Nova Info2 da Raiz Atual
                                    (*Raiz)->dir->info1 = (*Raiz)->dir->info2; //Info2 da Direita passa a ser a Info1
                                    (*Raiz)->dir->n_infos = 1; //Numero de Infos da Direita é atualizado
                                    operacao = 1; // sucesso

                                }else{
                                    //O Filho da direita não possui duas Infos, agrupamos
                                    (*Raiz)->info1 = (*Raiz)->cen->info1; //Info1 do Filho do Centro, sobe pra ser a nova Info1 da Raiz
                                    (*Raiz)->cen->info1 = (*Raiz)->info2; //A Info2 da Raiz Desce pra ser a Nova Info1 do Centro
                                    (*Raiz)->cen->info2 = (*Raiz)->dir->info1; //A Info1 da Direita agrupa e se torna a Info2 do Centro
                                    (*Raiz)->n_infos = 1; //A Raiz atual é atualizada para 1 Info
                                    (*Raiz)->cen->n_infos = 2; //A Raiz do Filho do Centro é atualizada para Duas Infos
                                    free((*Raiz)->dir); //O nó da Direita é liberado
                                    (*Raiz)->dir = NULL; //A direita se torna NULA
                                    operacao = 1; // sucesso
                                }

                            }
                        }else{
                            //A esquerda não é folha, então é sub-árvore

                            //primeiro conto os descendentes do Centro
                            
                            qtd_descendentes = contar_descendentes((*Raiz)->cen); 

                            if(qtd_descendentes > 3){
                                //Temos mais de 3 descendentes no Centro, então podemos manipular
                                Aux = Pegar_Menor((*Raiz)->cen, &operacao);                                
                                
                                if(operacao == 1){
                                    (*Raiz)->info1 = Aux; //Caso a operação tenha sido bem sucedida, será atribuido o novo valor
                                     operacao = Remover_Arv23(&((*Raiz)->cen), NULL, (*Raiz)->info1); 
                                }
                                
                                
                            }else{
                                //Não temos o suficiente no Centro, olhamos na esquerda então 
                                qtd_descendentes = contar_descendentes((*Raiz)->esq); 

                                if(qtd_descendentes > 3){

                                    Aux = Pegar_Maior((*Raiz)->esq, &operacao); //Pega o maior da sub-arvore da esquerda                                

                                    
                                    if(operacao == 1){
                                        //Se o movimento deu certo, o novo valor é atribuido
                                        (*Raiz)->info1 = Aux;
                                        operacao = Remover_Arv23(&((*Raiz)->esq), NULL, (*Raiz)->info1); 
                                     } 

                                     

                                }else{
                                    //Não há descendentes suficientes aqui, então, o jeito vai ser agregar
                                    operacao = agregar_infos(Raiz, 1);

                                }
                                
                            }

                        }    

                        


                    }

                }else{
                    //Não temos duas Infos, isso significa que o valor encontrado está na Info1, e que só temos o centro e a esquerda para olhar
                    
                    if(ehfolha((*Raiz)->esq)){
                        if((*Raiz)->cen != NULL && (*Raiz)->cen->n_infos == 2){
                            //O centro possui duas Infos, significa que dá pra manipular

                            (*Raiz)->info1 = (*Raiz)->cen->info1; //A Info1 do Centro, sobe para ser a Nova Info1 da Raiz Atual
                            (*Raiz)->cen->info1 = (*Raiz)->cen->info2; //A Info2 do Centro se torna a Nova Info1
                            (*Raiz)->cen->n_infos = 1; //Numero de Infos do Filho do Centro é atualizado pra 1
                            operacao = 1; //sucesso

                            
                        }else{
                            //O centro não possui Duas Infos
                            if((*Raiz)->esq != NULL  && (*Raiz)->esq->n_infos == 2){
                                //A esquerda possui duas Infos, dá pra manipualar
                                (*Raiz)->info1 = (*Raiz)->esq->info2; //Info2 da esquerda sobe para ser a nova Info1 da Raiz
                                (*Raiz)->esq->n_infos = 1; //Numero de Infos da Esquerda é atualizado
                                operacao = 1; //sucesso
                            }else{
                                //Como a Raiz atual não possui duas Infos, e seus dois filhos não possuem duas Infos, não dá pra fazer por manipulação simples
                               
                                
                                //Aqui, se o pai for NULO, significa que estamos em um caso com apenas 3 Infos, é possivel agrupar. 

                                //if(Pai == NULL || *Pai == NULL){
                                //Como só temos 3 Infos ao todo, e uma vai ser eliminada, só vai restar duas Infos, agrupa, e elimina os dois nós debaixo
                                (*Raiz)->info1 = (*Raiz)->esq->info1; //Info1 da Esquerda sobe para ser a Nova Info1 da Raiz
                                (*Raiz)->info2 = (*Raiz)->cen->info1; //Info1 do Centro sobe para se tornar a Info2 da Raiz
                                (*Raiz)->n_infos = 2; //Numero de Infos é atualizada
                                free((*Raiz)->esq); //Liberada a Esquerda
                                free((*Raiz)->cen); //Liberado o Nó do Centro
                                (*Raiz)->esq = NULL; //Esquerda se torna NULA
                                (*Raiz)->cen = NULL; //Centro se Torna Nulo
                                operacao = 1; //sucesso
                               
                                
                            }

                        }
                    }else{
                       //A esquerda não é folha

                       //Contamos os descendentes do Centro

                       qtd_descendentes = contar_descendentes((*Raiz)->cen); 

                       if(qtd_descendentes > 3){
                           // Tem mais de 3 descendentes, dá pra manipular
                           
                           Aux = Pegar_Menor((*Raiz)->cen, &operacao); //Pega o menor da sub-árvore central
                                                      
                           if(operacao == 1){
                              (*Raiz)->info1 = Aux;
                               operacao = Remover_Arv23(&((*Raiz)->cen), NULL, (*Raiz)->info1); 
                           }
                           

                       }else{
                           //O centro não possui duas Infos
                           //Olharemos então na esquerda

                           qtd_descendentes = contar_descendentes((*Raiz)->esq); 

                           if(qtd_descendentes > 3){
                               Aux = Pegar_Maior((*Raiz)->esq, &operacao); //Pega o maior da sub-arvore esquerda
                               
                                                            
                               if(operacao == 1){
                                  (*Raiz)->info1 = Aux; 
                                   operacao = Remover_Arv23(&((*Raiz)->esq), NULL, (*Raiz)->info1); 
                               } 
                               
                               
                           }else{
                               operacao = agregar_infos(Raiz, 1); //1 significa que o valor está na Info1
                           }
                       }


                    }    


                }


    }

   return operacao; 

}

int tratando_pendencias(Arv23Port **Raiz, Arv23Port **Pai, InfArv23 Info, int posicao){
    int operacao, qtd_descendentes; 
    operacao = 0; //Tratamos que não deu certo
    Arv23Port *Aux; 
    Aux = NULL; 
    InfArv23 Valor;   
    
    if(*Raiz != NULL){
      

        //Temos duas situações aqui, se temos ao todo 3 Infos, quando o Pai é Nulo, Ou seja, 3 Infos, no total, precisando de uma agregação

        if(Pai == NULL || *Pai == NULL){
            //Caso mais simples
            
            if(posicao == 3 || posicao == 4){
            //verificar se há 3 descendentes
                qtd_descendentes = contar_descendentes(*Raiz); 

                if(qtd_descendentes == 3){
                    if(posicao == 3){
                        //está no centro, então agrega a esquerda com a raiz
                        (*Raiz)->info2 = (*Raiz)->info1; //Info1 da Raiz passa a ser a Info2
                        (*Raiz)->info1 = (*Raiz)->esq->info1; //Info1 da Esquerda passa a ser Info1 da Raiz
                        (*Raiz)->n_infos = 2; //Numero de Infos é atualizado pra 2
                        free((*Raiz)->cen); //Libera o Centro
                        free((*Raiz)->esq); //Libera a esquerda
                        (*Raiz)->esq = NULL; //Esquerda passa a ser NULA
                        (*Raiz)->cen = NULL; //Centro passa a ser NULO
                        operacao = 1;
                    }else if(posicao == 4){
                        //Está na esquerda o Valor a ser eliminado, então agregamos a Raiz com o centro
                        (*Raiz)->info2 = (*Raiz)->cen->info1; //Info1 do Centro sobe e se torna a Nova Info2
                        (*Raiz)->n_infos = 2; //Numero de Infos é atualizado
                        free((*Raiz)->esq); //Libera a Esquerda da raiz
                        free((*Raiz)->cen); //Libera o Centro da Raiz
                        (*Raiz)->esq = NULL; //Esquerda passa a ser NULO
                        (*Raiz)->cen = NULL; //Centro passa a ser NULO
                        operacao = 1; 

                    }
                }
            }
    }else{
      
        //O Pai da recursão não é NULO, significa que estamos em uma subárvore. 
        //Primeiro, preciso saber, onde estou em relação ao PAI. 

        if((*Pai)->esq == *Raiz){
            //Estou na esquerda do Pai
            //Precisamos contar quantas Infos temos
            //Se no Centro também tiver 3 Infos, vamos agregar, se tiver mais de 3, podemos pegar o Maior, e descer 
            if((*Pai)->n_infos == 1){
                
                 //O pai só tem uma Info, então há duas sub-arvores apenas, dá pra agregar. 
                qtd_descendentes =  contar_descendentes((*Pai)->cen);
                if(qtd_descendentes == 3){
                  
                    //O centro também só tem 3 Infos, dá pra agregar
                    (*Raiz)->esq->info2 = (*Raiz)->info1; //A Info1 da minha raiz desce e se torna a Info2 da Esquerda
                    (*Raiz)->esq->n_infos = 2; //Atualiza o Numero de Infos pra 2  
                    (*Raiz)->info1 = (*Raiz)->cen->info1; //A Info1 do Centro sobe e se torna a Info1 daa Raiz
                    (*Raiz)->info2 = (*Pai)->cen->info1; //A Info1 do Centro se torna a Info2 da Raiz
                    (*Raiz)->n_infos = 2; //Numero de Infos da Raiz é atualizado
                    (*Raiz)->cen->info1 = (*Pai)->info1; //A info1 do Pai desce, e se torna a Info1 do Filho do Centro da Raiz
                    (*Raiz)->cen->info2 = (*Pai)->cen->esq->info1; //O filho da Esquerda do Centro do Pai, se torna a Info2 do Filho do Centro da Raiz
                    (*Raiz)->cen->n_infos = 2; //Numero de Infos é atualizado
                    (*Raiz)->dir = (*Pai)->cen->cen; //O nó do Centro, do filho do Centro do Pai se tornar o novo Nó Direito da Raiz
                    free((*Pai)->cen->esq); //Liberado o filho da esquerda do Centro do Pai
                    free((*Pai)->cen); //Liberado o filho do centro do Pai
                    Aux = *Pai; //O endereço do Pai vai pro auxiliar
                    *Pai = *Raiz; //endereço da raiz sobe e passa a ser o Pai. 
                    free(Aux); //Pai é liberado; 
                    
                    //Após agregar, é possivel remover

                    operacao = Remover_Arv23(Pai, NULL, Info); 


                }else if(qtd_descendentes > 3){
                  
                    //se o centro possui mais do que 3, precisamos apenas do menor valor
                    Valor = Pegar_Menor((*Raiz)->cen, &operacao); //Pega o menor da sub-arvore central
                    
                    if(operacao == 1){
                    //Significa que conseguimos o menor valor de lá, então dá pra manipular
                    (*Raiz)->cen->info2 = (*Pai)->info1; //A Info1 do Pai desce e se torna a Info2 do Centro da Raiz
                    (*Raiz)->cen->n_infos = 2; //Numero de Infos do Filho do Centro é atualizado pra 2; 
                    (*Pai)->info1 = Valor; //O menor valor, se torna a nova Info1 do Pai; 
                    operacao = Remover_Arv23(Raiz, NULL, Info); //Mando a função de remover, pra retirar o valor que eu queria antes; 

                   }

                    

                }



            }else{
               

                //Se temos duas Infos, muito possivelmente vai dar pra manipular diretamente
                //primeiro verificamos se o centro possui mais de três Infos
                qtd_descendentes = contar_descendentes((*Pai)->cen); 
                if(qtd_descendentes > 3){
                    
                    //Temos mais de 3 Infos no Centro, então podemos pegar o Menor
                    Valor = Pegar_Menor((*Raiz)->cen, &operacao); //Pega o menor da sub-arvore central

                   if(operacao == 1){
                    //Significa que conseguimos o menor valor de lá, então dá pra manipular
                    (*Raiz)->cen->info2 = (*Pai)->info1; //A Info1 do Pai desce e se torna a Info2 do Centro da Raiz
                    (*Raiz)->cen->n_infos = 2; //Numero de Infos do Filho do Centro é atualizado pra 2; 
                    (*Pai)->info1 = Valor; //O menor valor, se torna a nova Info1 do Pai; 
                    operacao = Remover_Arv23(Raiz, NULL, Info); //Mando a função de remover, pra retirar o valor que eu queria antes; 

                   }

                }else{
                    //O centro não possui mais do que 3 Infos, olhamos na direita

                    qtd_descendentes = contar_descendentes((*Pai)->dir); 
                    if(qtd_descendentes > 3){
                       
                        //temos mais do que 3 Infos na direita, precisamos da Menor
                        Valor = Pegar_Menor((*Raiz)->dir, &operacao); //Pega o menor da sub-arvore direita

                       if(operacao == 1){
                            //Conseguimos o menor valor da direita, agora, precisamos operar algumas coisas antes
                            //Precisamos Inserir a Info2 do Pai na sub-arvore central
                            insereArv23(&((*Pai)->cen), (*Pai)->info2, NULL, NULL, &operacao); 
                            if(operacao == 1){
                                //A inserção na sub-arvore foi bem sucedida, então, podemos colocar o Menor valor encontrado, na Info2 do Pai
                                (*Pai)->info2 = Valor; 
                                //Proximo passo, é retirar o menor valor do Centro, agora que ele possui 4 Infos, é possivel
                                
                                Valor = Pegar_Menor((*Raiz)->cen, &operacao); //Pega o menor na sub-arvore central

                                if(operacao == 1){
                                    //Deu certo pegar o menor valor, então fazemos outra inserção, na Esquerda, dessa vez, mandando Info1 do Pai

                                    insereArv23(&((*Pai)->esq), (*Pai)->info1, NULL, NULL, &operacao); 

                                    if(operacao == 1){
                                        //Deu certo inserir na sub-arvore da esquerda
                                        //agora, atribuimos o novo valor menor para a Info1 do Pai
                                        (*Pai)->info1 = Valor; 
                                        //Proximo passo, é remover o valor que queriamos
                                        operacao = Remover_Arv23(&((*Pai)->esq), NULL, Info); 
                                    }
                                    

                                 } 

                            }

                    } 

                    }else if(qtd_descendentes == 3){
                       
                        //Temos 3 Descendentes na direita, dá pra agregar aqui e balancear depois
                        
                        Valor = (*Pai)->dir->esq->info1; //A info1 da esquerda da Direita é o Valor Menor a ser recuperado
                        (*Pai)->dir->info2 = (*Pai)->dir->cen->info1; //Info1 do Centro da Direita sobe e se torna a Info2 da direita
                        (*Pai)->dir->n_infos = 2; 
                        free((*Pai)->dir->esq); //Esquerda da Direita do Pai é liberada
                        free((*Pai)->dir->cen); //Centro da Direita do Pai é liberada
                        (*Pai)->dir->esq = NULL;//Esquerda da Direita se torna NULA 
                        (*Pai)->dir->cen = NULL; //Centro da Direita se torna NULA
                        
                        //Proximo passo é inserir a Info2 do Pai, na sub-arvore do Centro
                        
                        insereArv23(&((*Pai)->cen), (*Pai)->info2, NULL, NULL, &operacao); 

                        if(operacao == 1){
                            //Inserção na sub-arvore foi bem sucedida
                            (*Pai)->info2 = Valor; //A nova Info2 do Pai é o valor recuperado

                            //Proximo passo é conseguir o menor do Centro 
                            Valor = Pegar_Menor((*Raiz)->cen, &operacao); 
                           

                            if(operacao == 1){
                                //Deu certo pegar o menor, agora, inserimos Info1 do Pai na sub-arvore à esquerda 
                                insereArv23(&((*Pai)->esq), (*Pai)->info1, NULL, NULL, &operacao); 

                                if(operacao == 1){
                                    //Com a inserção bem sucedida, substituimos a Info1 do Pai pelo Valor
                                    (*Pai)->info1 = Valor; //A nova Info1 do Pai é o menor valor recuperado do Centro
                                    operacao = Remover_Arv23(&((*Pai)->esq), NULL, Info); //manda a remoção pra cuidar do caso
                                }

                           }
                        }

                    }


                    
                }

                //Temos duas Infos no Pai
            }    


        }else if((*Pai)->cen == *Raiz){
           
            //Estou no Centro do Pai
            
            //Verifico se tenho uma direita no Pai (ou seja, se tem duas Infos)

            if((*Pai)->n_infos == 2){
                
                //O pai tem duas Infos, isso significa que temos uma direita para olhar
                qtd_descendentes = contar_descendentes((*Pai)->dir); 

                if(qtd_descendentes > 3){
                    //Temos mais do que 3 Infos, dá pra pegar o menor valor
                    Valor = Pegar_Menor((*Raiz)->dir, &operacao); 

                   if(operacao == 1){
                        //Deu certo pegar o menor, então podemos prosseguir
                        //Inserindo o Info2 no Centro, onde estou
                        insereArv23(&((*Pai)->cen), (*Pai)->info2, NULL, NULL, &operacao); 

                        if(operacao == 1){
                            //Com a Inserção bem sucedida, Info2 do Pai recebe o valor e na sequencia a remoção é chamada
                            (*Pai)->info2 = Valor; 
                            operacao = Remover_Arv23(&((*Pai)->cen), NULL, Info); //Remoção é chamada pra cuidar do caso simples
                        }
                   }

                }else if(qtd_descendentes == 3){
                   
                    //Temos 3 descendentes na direita, dá pra agregar e balancear mais tarde
                    Valor = (*Pai)->dir->esq->info1; // O menor valor da sub-arvore vai pra variavel
                    (*Pai)->dir->info2 = (*Pai)->dir->cen->info1; //A info1 do Centro da Direita sobe e se torna a Info2 da direita
                    (*Pai)->dir->n_infos = 2; //A direita do Pai tem o numero de Infos atualizado
                    free((*Pai)->dir->esq); //A esquerda da Direita do Pai é liberada
                    free((*Pai)->dir->cen); //O centro da Direita do Pai é liberada
                    (*Pai)->dir->esq = NULL; //A esquerda da Direita se torna NULO
                    (*Pai)->dir->cen = NULL; //O centro da Direita se torna NULO

                    //Proximo passo, é inserir Info2 no Centro do Pai
                    insereArv23(&((*Pai)->cen), (*Pai)->info2, NULL, NULL, &operacao); 

                    if(operacao == 1){
                        //deu certo a inserção, então a Info2 do Pai recebe o novo valor
                        (*Pai)->info2 = Valor; 
                        //com 4 valores, podemos realizar a remoção agora
                        operacao = Remover_Arv23(&((*Pai)->cen), NULL, Info); 

                    }

                }
            }else{
        
                //O pai não possui duas Infos, só temos a esquerda pra olhar

                qtd_descendentes = contar_descendentes((*Pai)->esq); 

                if(qtd_descendentes > 3){
                    //temos mais do que 3 descendentes na esquerda

                    Valor = Pegar_Maior((*Raiz)->esq, &operacao); 

                    if(operacao == 1){
                    //Deu certo pegar o Maior valor, agora inserimos Info1 do Pai na sub-arvore do centro

                        insereArv23(&((*Pai)->cen), (*Pai)->info1, NULL, NULL, &operacao); 

                        if(operacao == 1){
                            //Deu certo a Inserção, atribuimos o novo valor a Info1 do Pai e mandamos a remoção
                            (*Pai)->info1 = Valor; 
                            operacao = Remover_Arv23(&((*Pai)->cen), NULL, Info); //Manda a remoção pra cuidar de um caso mais simples
                        }
                 }
                }else if(qtd_descendentes == 3){
                   
                    //temos apenas 3 descendentes, agrega e depois balanceia 
                    Valor = (*Pai)->esq->cen->info1; //Info1 do Centro da Esquerda sobe
                    (*Pai)->esq->info2 = (*Pai)->esq->info1; //Info1 se torna a Info2 da esquerda do Pai
                    (*Pai)->esq->info1 = (*Pai)->esq->esq->info1; //Info1 da Esquerda da Esquerda sobe e se torna a Info1 da Esquerda
                    (*Pai)->esq->n_infos = 2; //Numero de Infos da Esquerda é atualizado
                    free((*Pai)->esq->esq); //Esquerda da Esquerda é liberada
                    free((*Pai)->esq->cen); //Centro da Esquerda é liberado
                    (*Pai)->esq->esq = NULL; //Esquerda da Esquerda se torna NULA
                    (*Pai)->esq->cen = NULL; //Centro da Esquerda se torna NULO

                    //Manipulação feita, proximo passo, é inserir a Info1 do Pai no Centro
                    insereArv23(&((*Pai)->cen), (*Pai)->info1, NULL, NULL, &operacao); 
                    if(operacao == 1){
                        //Deu certo a inserção, reatribuimos o Valor pra Info1 do Pai, e passamos a remoção
                        (*Pai)->info1 = Valor; 
                        operacao = Remover_Arv23(&((*Pai)->cen), NULL, Info); 
                    }

                }
            }




        }else if((*Pai)->dir == *Raiz){
            //Estou na direita do Pai
            
            //Precisamos contar quantas Infos temos
            //Se no Centro também tiver 3 Infos, vamos agregar, se tiver mais de 3, podemos pegar o Maior, e descer

            //Como somos a direita, sabemos que o pai tem duas Infos

            //primeiro passo, é verificar se o Centro possui mais de 3 Infos

            qtd_descendentes = contar_descendentes((*Pai)->cen); 

            if(qtd_descendentes > 3){
               
                //Temos mais do que 3 descendentes na sub-arvore do centro, dá pra manipular
                Valor = Pegar_Maior((*Raiz)->cen, &operacao);

                if(operacao == 1){
                    //deu certo pegar o maior valor
                    //inserimos então a Info2 do Pai, na sub-arvore à direita
                    insereArv23(&((*Pai)->dir), (*Pai)->info2, NULL, NULL, &operacao); 

                    if(operacao == 1){
                        // A inserção na sub-arvore deu certo, proximo passo é atribuir o novo valor a info2 do Pai, e realizar a remoção
                        (*Pai)->info2 = Valor; 

                        operacao = Remover_Arv23(&((*Pai)->dir), NULL, Info); 
                    }
                }
            }else if(qtd_descendentes == 3){
              
                //temos 3 descendentes no Centro, dá pra agregar e balancear depois
                Valor = (*Pai)->cen->cen->info1; //Pegamos o maior valor da sub-arvore do centro, no caso a Info1 do Centro do Centro
                (*Pai)->cen->info2 = (*Pai)->cen->info1; //A info1 do Centro se torna a Info2
                (*Pai)->cen->info1 = (*Pai)->cen->esq->info1; //Info1 da esquerda do Centro sobe e se torna a nova Info1 do Centro
                (*Pai)->cen->n_infos = 2; //numero de Infos do Centro é atualizado pra 2
                free((*Pai)->cen->esq); //Esquerda do Centro é liberada
                free((*Pai)->cen->cen); //Centro do Centro é liberada
                (*Pai)->cen->esq = NULL; //Esquerda do Centro passa a ser NULA
                (*Pai)->cen->cen = NULL; //Centro do Centro passa a ser NULA; 

                //Proximo passo é inserir a Info2 do Pai na Sub-arvore da direita

                insereArv23(&((*Pai)->dir), (*Pai)->info2, NULL, NULL, &operacao); 

                if(operacao == 1){
                    //deu certo a inserção na subarvore
                    //proximo passo é atribuir o novo Valor na Info2 do Pai
                    (*Pai)->info2 = Valor; 
                    //depois, aplicar a remoção na direita
                    operacao = Remover_Arv23(&((*Pai)->dir), NULL, Info); //chamada a função de remoção 
                }

            }
            



        }



    }
    
}
    return operacao; 
}


int Remover_Arv23(Arv23Port **Raiz, Arv23Port **Pai, InfArv23 Info){
    int operacao; 
    operacao = 0; //não removeu

    if(*Raiz != NULL){
        int comparacao1, comparacao2;
         comparacao1 = strcmp(Info.palavra_portugues, (*Raiz)->info1.palavra_portugues); 
         if((*Raiz)->n_infos == 2){
            comparacao2 = strcmp(Info.palavra_portugues, (*Raiz)->info2.palavra_portugues); //se existir duas infos, compara
         }else{
            comparacao2 = 1; //não existindo Info2, assume que não tem nada aqui. 
         }

         if(comparacao1 == 0 || comparacao2 == 0){
            //encontrou a informação, mas antes, saberemos se estamos em uma folha ou não 
            if(ehfolha(*Raiz)){
                //estamos em uma folha. 
                //verificamos se o pai é NULO, se o Pai é NULO, nos estamos na raiz, sendo folha
               
                if(Pai == NULL || *Pai == NULL){
                    
                    //O pai sendo NULO, temos tres situações
                    //podemos ter: 1 info, 2 infos. Se Info1 tiver de ser removida, Info2 passa a ser Info1
                    //Se Info2 for removido, mantemos apenas Info2
                    //Se houver apenas uma Info, liberamos a árvore
                    
                    if((*Raiz)->n_infos == 1){
                        //Temos só uma Info, ela é folha, e é a Raiz da árvore
                        operacao = 2; //Pendencia pra eliminar a árvore na função externa.
                    }else{
                        
                        if(comparacao2 == 0){
                            // encontramos a informação na Info2, só atualizar o numero de Infos
                            (*Raiz)->n_infos = 1; 
                            operacao = 1; //sucesso
                        }else{
                            //encontramos na Info1, Info2 então passa a ser Info1
                            (*Raiz)->info1 = (*Raiz)->info2;
                            (*Raiz)->n_infos = 1;      
                            operacao = 1; //sucesso                     
                        }
                    }
             

                }else{
                    //estamos em uma folha, mas não somos a raiz da árvore, sinal de que teremos de manipular. (talvez)

                    if((*Raiz)->n_infos == 2){
                        //temos duas Infos, não precisamos manipular externamente
                        if(comparacao2 == 0){
                            //A info a ser eliminada é a segunda, de uma folha, basta atualizar o numero de Infos
                            (*Raiz)->n_infos = 1; 
                            operacao = 1; //sucesso
                        }else{
                            //A informação está na Info1, mas como temos duas, basta mover Info2 pra Info1
                            (*Raiz)->info1 = (*Raiz)->info2; 
                            (*Raiz)->n_infos = 1;
                            operacao = 1; //sucesso; 
                        }



                    }else{
                        //só temos uma Info, nesse caso, mexeremos com o Pai

                        //chamar função de remover Info1 da Folha
                        operacao = RemoverInfo1Folha(Raiz, Pai); 

                        if(operacao == 2){   
                            //Pendencia que não pode ser resolvida naquela função

                          if((*Pai)->cen == *Raiz){
                              operacao = 3; //estou no centro do Pai
                          }else if((*Pai)->esq == *Raiz){
                              operacao = 4; //Estou na esquerda do Pai
                          } 
                        } 
                        
                       


                    }



                }


            }else{
                //Não estamos em uma folha 
                
                //Se não estamos em uma folha, temos diversas situações 
                //Podemos ser Info1 ou Info2
                //Se for Info2, temos filho da direita, melhor ainda
                //se for Info1, temos o Centro ainda pra manipular



                 if(comparacao1 == 0){
                    operacao = Remover_Info_Nao_Folha(Raiz, 1); //Está na Info 1
                 }else if(comparacao2 == 0){
                    operacao = Remover_Info_Nao_Folha(Raiz, 2); //Está na Info 2
                 }

            }      

                


         }else{
            //Não encontramos aqui, vamos percorrer

            if(comparacao1 < 0){
                //vamos para a esquerda de Info1 
                operacao = Remover_Arv23(&((*Raiz)->esq), Raiz, Info); 
            }else if(comparacao1 > 0 && (*Raiz)->n_infos == 1){
                 operacao = Remover_Arv23(&((*Raiz)->cen), Raiz, Info); 

            }else if((*Raiz)->n_infos == 2){
                if(comparacao1 > 0 && comparacao2 < 0){
                    operacao = Remover_Arv23(&((*Raiz)->cen), Raiz, Info);                     
                }else{
                    operacao = Remover_Arv23(&((*Raiz)->dir), Raiz, Info); 
                }
            } 


            //Pendencias 

            if(operacao == 3 || operacao == 4){
                //Significa que não foi possivel finalizar lá atrás, precisamos subir um nivel
                //conto quantos descendentes são, se for 3 em ambos, dá pra agregar, mas se um tiver 4, dá pra manipular 
                //Primeiro, verifico se o Pai não é NULO 

                operacao = tratando_pendencias(Raiz, Pai, Info, operacao);

                

            }



         }

    }

    return operacao; 
}

int Altura(Arv23Port *Raiz) {
    int altura;
    if (Raiz == NULL) {
        altura = -1; // Uma árvore vazia tem altura -1
    } else {
        int altura_esq = Altura(Raiz->esq); // Altura da subárvore esquerda
        int altura_cen = Altura(Raiz->cen); // Altura da subárvore central
        int altura_dir = -1; // Altura da subárvore direita (só relevante para 2 infos)

        if (Raiz->n_infos == 2) {
            // Altura da subárvore direita é relevante apenas para 2 informações no nó
            altura_dir = Altura(Raiz->dir);
        }

        // Calcula a maior altura entre as subárvores
        int maior_altura = altura_esq > altura_cen ? altura_esq : altura_cen;
        if (Raiz->n_infos == 2) {
            maior_altura = maior_altura > altura_dir ? maior_altura : altura_dir;
        }

        altura = 1 + maior_altura; // Incrementa 1 para incluir o nível atual
    }

    return altura;
}


//Após uma remoção bem sucedida, é necessário verificar a consistencia da árvore, para garantir que nenhuma das sub-árvore esteja desnivelada em relação às outras
int verificador_consistencia(Arv23Port *Raiz, Arv23Port **Pai){
    int consistente;                    
    consistente = 1; //1 significa que está correta a árvore
    if(Raiz != NULL){
        int altura_esq, altura_cen, altura_dir;
        consistente = verificador_consistencia(Raiz->esq, &Raiz); 

        //Se encontrar alguma inconsistencia para a recursão e retorna (pq se tem uma, já é o suficiente saber)

        if(consistente != 0){
             if(ehfolha(Raiz)){
                // se a raiz é folha, então o centro e a direita não podem ter filhos
                if(Raiz->cen != NULL || Raiz->dir != NULL){
                    //Significa que não temos um filho na esquerda, mas temos no Centro ou na direita, está inconsistente (ou seja, uma pseudofolha kkk)
                    consistente = 0; 
                }

             }else{
                //Não é folha, então veremos o numero de Infos

                //verificar aqui a altura dessas sub-arvores
                if(Raiz->n_infos == 1){
                    //Temos só uma Info, então temos que ter dois filhos
                    if(Raiz->esq == NULL || Raiz->cen == NULL || Raiz->dir != NULL){
                        //Se não somos folha, e temos uma Info aqui, a situação é
                        //A esquerda não pode ser NULA, o Centro não pode ser NULO
                        //e a Direita tem que ser NULA, se houver qualquer uma dessas anomalias, está inconsistente
                        consistente = 0; //A arvore se degenerou
                    }
                }else if(Raiz->n_infos == 2){
                    //Se temos duas Infos, e não somos folha, precisamos ter 3 filhos
                    if(Raiz->esq == NULL || Raiz->cen == NULL || Raiz->dir == NULL){
                        //Se um dos filhos for NULO, sabendo que não estamos em uma folha, a arvore está degenerada
                        consistente = 0; 
                    }

                }

                if(consistente != 0 && (Pai == NULL || *Pai == NULL)){
                    //Deu ok no primeiro teste, verificação adicional na raiz principal da arvore
                     
                    //Na raiz, comparamos as alturas das sub-árvores
                    altura_esq = Altura(Raiz->esq);
                    altura_cen = Altura(Raiz->cen);
                    altura_dir = Raiz->n_infos == 2 ? Altura(Raiz->dir) : -1;

                    if (Raiz->n_infos == 1) {
                        if (altura_esq != altura_cen) {
                            consistente = 0; // Desbalanceamento com 1 informação
                        }
                    } else if (Raiz->n_infos == 2) {
                        if (altura_esq != altura_cen || altura_cen != altura_dir) {
                            consistente = 0; // Desbalanceamento com 2 informações
                        }
                    }

                    if(consistente != 0){
                        //Ultima verificação, se as sub-árvores estão consistentes
                        //olhando a esquerda
                        
                        altura_esq = Altura(Raiz->esq->esq);
                        altura_cen = Altura(Raiz->esq->cen);
                        altura_dir = Raiz->esq->n_infos == 2 ? Altura(Raiz->esq->dir) : -1;
                        
                        if (Raiz->esq->n_infos == 1) {
                        if (altura_esq != altura_cen) {
                            consistente = 0; // Desbalanceamento com 1 informação
                        }
                        } else if (Raiz->esq->n_infos == 2) {
                          if (altura_esq != altura_cen || altura_cen != altura_dir) {
                            consistente = 0; // Desbalanceamento com 2 informações
                          }
                       }  
                         //Se a sub-arvore da esquerda ficou inconsistente, já pode parar

                        if(consistente != 0){
                            //caso esteja tudo ok, verificar a sub-arvore do Centro 

                            altura_esq = Altura(Raiz->cen->esq);
                            altura_cen = Altura(Raiz->cen->cen);
                            altura_dir = Raiz->cen->n_infos == 2 ? Altura(Raiz->cen->dir) : -1;
                            
                            if (Raiz->cen->n_infos == 1) {
                            if (altura_esq != altura_cen) {
                                consistente = 0; // Desbalanceamento com 1 informação
                            }
                            } else if (Raiz->cen->n_infos == 2) {
                            if (altura_esq != altura_cen || altura_cen != altura_dir) {
                                consistente = 0; // Desbalanceamento com 2 informações
                            }
                           }

                        }

                        if(consistente != 0 && Raiz->n_infos == 2){
                            //Caso tenha duas infos na Raiz e esteja tudo ok nos casos anteriores, verificamos sua direita
                            altura_esq = Altura(Raiz->dir->esq);
                            altura_cen = Altura(Raiz->dir->cen);
                            altura_dir = Raiz->dir->n_infos == 2 ? Altura(Raiz->dir->dir) : -1;
                            
                            if (Raiz->dir->n_infos == 1) {
                            if (altura_esq != altura_cen) {
                                consistente = 0; // Desbalanceamento com 1 informação
                            }
                            } else if (Raiz->dir->n_infos == 2) {
                            if (altura_esq != altura_cen || altura_cen != altura_dir) {
                                consistente = 0; // Desbalanceamento com 2 informações
                            }
                           } 

                         
                            
                        } 


                    }

                     
                }

                
               
 

             }

             if(consistente == 1){
                //como a arvore nesse ponto pode estar degenerada, é necessário mandar sem verificar o numero de Infos
                consistente = verificador_consistencia(Raiz->cen, &Raiz);  //Vai pro Centro

                if(consistente == 1){
                    //Caso não tenha encontrado inconsistencia no Centro, percorre a Direita
                    consistente = verificador_consistencia(Raiz->dir, &Raiz); //Vai pra direita
                }
             }    



        }

    }

    return consistente;
    
}


int reconstruir_Arv(Arv23Port *Raiz, Arv23Port **Nova_Raiz){
    int operacao;
    operacao = 1; //indica sucesso
    if(Raiz != NULL){
        operacao = reconstruir_Arv(Raiz->esq, Nova_Raiz); 

        if(operacao == 1){
            //A operação está prosseguindo conforme esperado
            insereArv23(Nova_Raiz, Raiz->info1, NULL, NULL, &operacao); 
            if(operacao == 1){
                if(Raiz->n_infos == 2){
                    insereArv23(Nova_Raiz, Raiz->info2, NULL, NULL, &operacao); 
                }
            }
            //Se estiver tudo ok com a inserção na nova arvore das Info1 e Info2(talvez)
            if(operacao == 1){

                operacao = reconstruir_Arv(Raiz->cen, Nova_Raiz); //Manda pro centro

                if(operacao == 1){
                    operacao = reconstruir_Arv(Raiz->dir, Nova_Raiz); //Manda pra direita
                }
            }

        }

    }
    return operacao;
}

void liberarArvore23(Arv23Port **Raiz) {
    if (*Raiz != NULL) {
        // Libera as subárvores recursivamente
        liberarArvore23(&(*Raiz)->esq);
        liberarArvore23(&(*Raiz)->cen);
        liberarArvore23(&(*Raiz)->dir);

        // Libera o próprio nó
        free(*Raiz);
        *Raiz = NULL; 
    }
}



int auxiliar_reconstrucao(Arv23Port **Raiz){
    int operacao;
    operacao = 1; //1 indica sucesso
    if(*Raiz != NULL){
        //Primeiro passo é criar uma nova Raiz temporaria
        Arv23Port *Nova_Raiz; 
        Nova_Raiz = NULL; 

        operacao = reconstruir_Arv(*Raiz, &Nova_Raiz);

        if(operacao == 1){
            //Arvore reconstruida com sucesso, agora precisamos eliminar a antiga
            liberarArvore23(Raiz); 

            if(*Raiz == NULL){
                //Arvore eliminada, então atribuiremos a nova
                *Raiz = Nova_Raiz;

            }else{
                operacao = 0; //arvore antiga não foi eliminada corretamente
            }
        }else{
            //Falhou na reconstrução da nova árvore
            operacao = 0; 
        }


    }

    return operacao;
}


int situacao_da_arvore(Arv23Port **Raiz, Arv23Port **Pai, InfArv23 Info){
   int operacao; 
   operacao = 0; // não deu certo 
   if(*Raiz != NULL){
     operacao = Remover_Arv23(Raiz, Pai, Info);

       
     if(operacao == 1){
        //significa sucesso na remoção, verificamos então a consistencia da arvore 
        operacao = verificador_consistencia(*Raiz, NULL); 
        if(operacao == 0){
            //A Arvore ficou inconsistente, é necessário reconstruir
            operacao = auxiliar_reconstrucao(Raiz); 
        }

      }
      

     if(operacao == 2){
         //eliminamos a arvore 
         free(*Raiz); 
         *Raiz = NULL; 
         operacao = 1; 
     }
     
       
   }
   
   return operacao;
}


