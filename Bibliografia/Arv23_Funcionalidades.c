#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"



//Funções de Inserção

//Criar Nó vai ficar aqui
Arv23Port *criarNoArv23(InfArv23 Info, Arv23Port *Filho_Esq, Arv23Port *Filho_Cent){
    //vou deixar só o protótipo, por enquanto
    Arv23Port *Novo_no; 
    Novo_no = NULL; 

    Novo_no = (Arv23Port*)malloc(sizeof(Arv23Port)); 
    if(Novo_no == NULL){
        printf("Falha na alocação\n"); 
    }else{
        Novo_no->info1 = Info; 
        Novo_no->esq = Filho_Esq; 
        Novo_no->cen = Filho_Cent; 
        Novo_no->dir = NULL; 
        Novo_no->n_infos = 1; 
    }

    return Novo_no; 
}

int ehfolha(Arv23Port *no){
    int situacao; 
    situacao = 0; //Inicio do pressuposto que não é folha
    
    if(no->esq == NULL){
        situacao = 1; //Se não existe um esquerdo, é folha.  
    }

    return situacao; 
}

Arv23Port *adicionaChave(Arv23Port *no, InfArv23 Info, Arv23Port *MaiorNo){
    //Função pra adicionar uma info no Nó e manipular seus ponteiros de filhos, caso necessário
    int comparacao; 
    comparacao = strcmp(Info.palavra_portugues, no->info1.palavra_portugues); 
    if(comparacao < 0){
        //Se a informação adicionada for menor do que a Info 1, Info1, passa a ser Info2
        no->info2 = no->info1; 
        no->info1 = Info;

        if(MaiorNo != NULL){
            no->dir = no->cen; //vai colocar o filho que tava no centro, pra direita
            no->cen = MaiorNo; // e vai colocar o Filho direito da Info que entrou, no Centro, à direita dele
        }


    }else{
        no->info2 = Info; 
        if(MaiorNo != NULL){
            no->dir = MaiorNo; 
        }
    }

    no->n_infos = 2; 

    return no; 
    
}    

Arv23Port *quebraNo(Arv23Port **No, InfArv23 Info, InfArv23 *promove, Arv23Port *Filho){
     int comparacao1, comparacao2; 
     Arv23Port *Maior; 
     
     comparacao1 = strcmp(Info.palavra_portugues, (*No)->info2.palavra_portugues); // verifica se a nova info é maior que info2
     comparacao2 = strcmp(Info.palavra_portugues, (*No)->info1.palavra_portugues); //verifica se a info nova é maior que a info1  
     if(comparacao1 > 0){
        //Se a informação a ser inserida, é maior do que a Info 2, A informação nova se torna o Maior, Info2 vai subir, Info1 permanece inalterado
        *promove = (*No)->info2; 
        Maior = criarNoArv23(Info, (*No)->dir, Filho); 
        (*No)->n_infos = 1;

       }else if(comparacao2 > 0){
            //Se a informação a ser inserida é maior do que Info1, mas menor do que Info2, então o valor a ser inserido é quem vai subir
            *promove = Info;
            Maior = criarNoArv23((*No)->info2, Filho, (*No)->dir); 
            (*No)->n_infos = 1;           

    }else{
        //Se a informação a ser inserida, é menor do que a Info1, a Informação se torna a menor, Info1 sobe, e Info2 é a maior
        *promove = (*No)->info1; 
        Maior = criarNoArv23((*No)->info2, (*No)->cen, (*No)->dir); 
        (*No)->info1 = Info; 
        (*No)->n_infos = 1; 
        (*No)->cen = Filho; 
    }

    return Maior; 

}



//Função de inserção ficará aqui. 

Arv23Port *insereArv23(Arv23Port **no, InfArv23 Info, InfArv23 *promove, Arv23Port **Pai, int *situacao, int *info_posicao, Arv23Port **no_referencia){
    Arv23Port *MaiorNo; 
    MaiorNo = NULL; 
    int comparacao1, comparacao2, verificacao; 
    InfArv23 promove1; 
    verificacao = 0; // 0 significa que não tem palavra igual na árvore
    

    if(*no == NULL){
        //Se a árvore for Nula, criaremos o primeiro Nó
        *no = criarNoArv23(Info, NULL, NULL); 
        if (*no == NULL) {
            *situacao = 0; // Falha total devido à falha de alocação
        }else {
            *situacao = 1;       // Sucesso com nova inserção
            *no_referencia = *no; // Retorna o endereço do novo nó
        }

    }else{

        comparacao1 = strcmp(Info.palavra_portugues, (*no)->info1.palavra_portugues);

        if(comparacao1 == 0){
            *situacao = 2; //2 indica que a A info que eu queria inserir já existe em uma das Infos desse Nó
            *info_posicao = 1; //indica qual posicao está a palavra
            *no_referencia = *no; //O nó será recuperado por referencia
            verificacao = 1; //1 indica que tem palavra repetida, portanto, não se deve prosseguir
        } 

        if((*no)->n_infos == 2){
            comparacao2 = strcmp(Info.palavra_portugues, (*no)->info2.palavra_portugues);
            if(comparacao2 == 0){
                *situacao = 2; //2 indica que a A info que eu queria inserir já existe em uma das Infos desse Nó
                *info_posicao = 2; //A palavra está na posição 2 do Nó
                *no_referencia = *no; //recupera o endereço do Nó
                verificacao = 1; 
            }
        }

        if(verificacao != 1){

            if(ehfolha(*no) == 1){//Se for folha, entra aqui
                if((*no)->n_infos == 1){
                    //Se tiver uma única info, entra aqui.
                    *no = adicionaChave(*no, Info, NULL); 
                    *situacao = 1; //1 indica que a palavra não existia e foi adicionada com sucesso
                    *no_referencia = *no; //recupera o endereço
                }else{
                    //Se já tiver duas infos, entra aqui. 
                    MaiorNo = quebraNo(no, Info, promove, NULL); 
                    if(*Pai == NULL){
                        *no = criarNoArv23(*promove, *no, MaiorNo); 
                        MaiorNo = NULL; 
                    }
                    *situacao = 1; 
                    *no_referencia = *no;
                }
            }else{
                comparacao1 = strcmp(Info.palavra_portugues, (*no)->info1.palavra_portugues); //Como lidamos com palavras, é necessário comparar strings
                //Caso não seja folha, é necessário percorrer até chegar na folha. 
                if(comparacao1 < 0){ 
                    MaiorNo = insereArv23(&((*no)->esq), Info, promove, no, situacao, info_posicao, no_referencia); 
                    //A informação é menor do que a Info 1, então obviamente vai pela esquerda
                }else{
                    //Não é menor do que a Info 1, há duas condições de verificação agr
                    if((*no)->n_infos == 2){
                        comparacao2 = strcmp(Info.palavra_portugues, (*no)->info2.palavra_portugues); 
                    }
                    
                    if(((*no)->n_infos == 1) || (comparacao2 < 0)){ 
                        //Verifica se o numero de infos é igual a 1 ou se ele é menor do que a Info 2
                        //Nesse caso, a inserção caminhará para o centro. 

                        MaiorNo = insereArv23(&((*no)->cen), Info, promove, no, situacao, info_posicao, no_referencia);

                    }else{
                        //A info é maior do que a Info 2, o caminho aqui é pela direita
                        MaiorNo = insereArv23(&((*no)->dir), Info, promove, no, situacao, info_posicao, no_referencia);
                    }

                } 
            }
        }    






    } 

        //As pendências agr (quando a função tá voltando na recursão)
    if(MaiorNo != NULL){
        //significa que voltou pendencia aqui
        if((*no)->n_infos == 1){
            //Se o numero de Infos da Chave, for igual a 1, podemos inserir aqui sem quebrar
            *no = adicionaChave(*no, *promove, MaiorNo);
            *situacao = 1; //1 indica nova informação inserida
            *no_referencia = *no; //recupera o endereço do Nó
            *info_posicao = 1;  


        }else{
            //Como há um valor a ser inserido, e já temos duas infos, a unica saída é quebrar o Nó
            MaiorNo = quebraNo(no, *promove, &promove1, MaiorNo); 
            if(*Pai == NULL){
                //Se não houver um pai, pra comportar a subida, um novo pai deve ser criado
                *no = criarNoArv23(promove1, *no, MaiorNo); 
                MaiorNo = NULL; 
            }else{
                // Se há um pai, a promoção continua
                *promove = promove1;
            }
            *situacao = 1;
            *no_referencia = *no; 
            *info_posicao = 1; 
        }
    }

    return MaiorNo;

}


  









