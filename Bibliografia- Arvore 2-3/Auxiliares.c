#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliografia.h"



//Funções dos Itens agr

//Item (I)  informar uma unidade e então imprima todas as palavras da unidade em português seguida das equivalentes em inglês;

void imprimir_palavras_pela_unidade(Arv23Port *Raiz){
    int situacao; 
    if(Raiz != NULL){
        int confirmacao, unidade; 
        confirmacao = 0; 
        //primeiro passo é digitar a unidade, como o dataset é fixo (50), vamos limitar por essa quantidade
        do {
            printf("Digite a unidade: ");
            
            if (scanf("%d", &unidade) == 1) { // Valida se a entrada é um número
                if (unidade > 0 && unidade <= 50) {
                    confirmacao = 1;
                } else {
                    printf("Digite uma unidade válida (Entre 1 e 50).\n");
                }
            } else {
                printf("Entrada inválida. Digite um número válido (Entre 1 e 50).\n");
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida
            }
        } while (confirmacao == 0); 

         
        

       situacao = imprimir_infos_23_por_unidade(Raiz, unidade);  //consertar o retorno dessa função

       if(situacao != 1){
           situacao = 2; //nenhuma palavra encontrada 
       }

               
        

    }else{
        //arvore vazia
        situacao = 0;
    }

    mensagem_status_impressao_unidade(situacao); 
}

//Item (II) informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em português dada, independente da unidade; 
void imprimir_todos_significados_palavra_especifica(Arv23Port *Raiz){
    int situacao; 
    if(Raiz != NULL){
       inf_op Informacao; 
       int operacao = 0; //0, significa que não deu certo

       Arv23Port *No_recuperado; 
       No_recuperado = NULL; 

       while (getchar() != '\n');
       
       printf("Digite a palavra em português que deseja imprimir seus significados: ");
       fgets(Informacao.palavra_utilizada, 100, stdin);
       Informacao.palavra_utilizada[strcspn(Informacao.palavra_utilizada, "\n")] = '\0';  

       operacao =  armazenar_No_ARV23(Raiz, Informacao, &No_recuperado); 

    

       
       if(operacao != 0){
            if(operacao == 1){  
               //está na info1  
               imprimiArvBB(No_recuperado->info1.significados_ingles);
               situacao = 1; //deu certo 
            }else if(operacao == 2){
               //está na info2
               imprimiArvBB(No_recuperado->info2.significados_ingles);
               situacao = 1; //deu certo 
            }

       }else{
           //A palavra pesquisada não foi encontrada
           situacao = 2; 
        }
    
    }else{
        //A árvore está vazia
        situacao = 0; 
    }

    mensagem_status_impressao_palavra_especifica(situacao); 
} 


/*
Item (III) Excluir palavra em ingles, de determinada unidade
Como vai funcionar, temos a palavra em inglês e sua respectiva unidade (ou seja, ambas tem que corresponder, pra que a exclusão seja feita)
uma palavra em inglês pode estar em mais de uma unidade(baseado no meu dataset), então partiremos de uma lógica de reversão em cascata
como não sabemos onde exatamente essa palavra em ingles está, devemos percorrer todas as infos da arvore RN
Em cada Info da RN, vamos percorrer todos os nós da árvore binária, ao encontrar a palavra correspondente
vamos mandar remover a unidade da lista, caso a unidade removida seja a única naquela lista, tornando-a nula
faremos a remoção definitiva do nome do dataset, com a remoção do Nó, caso a subárvore então fique NULA
faremos a exclusão da palavra em português da RN

*/

void excluir_palavra_ingles_unidade(Arv23Port **Raiz) {
   int situacao; 
   if (*Raiz != NULL) {
       inf_op Informacao;  
       int operacao;   
       int confirmacao = 0;

       
       while (getchar() != '\n');
       
       printf("Digite a palavra em inglês que deseja excluir: ");
       fgets(Informacao.palavra_utilizada, 100, stdin);
       Informacao.palavra_utilizada[strcspn(Informacao.palavra_utilizada, "\n")] = '\0';

      
       do {
            printf("Digite a unidade: ");
            
            if (scanf("%d", &Informacao.unidade) == 1) { // Valida se a entrada é um número
                if (Informacao.unidade > 0 && Informacao.unidade <= 50) {
                    confirmacao = 1;
                } else {
                    printf("Digite uma unidade válida (Entre 1 e 50).\n");
                }
            } else {
                printf("Entrada inválida. Digite um número válido (Entre 1 e 50).\n");
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida
            }
        } while (confirmacao == 0);

       operacao = remover_palavra_ingles_pela_unidade(Raiz, *Raiz, Informacao); 

       if(operacao == 1){
           //Operação concluida com sucesso
           situacao = 1;
       }else{
           //Nenhuma palavra com a unidade pesquisada foi encontrada. 
           situacao = 2; 
       }


   } else {
       //A raiz está vazia
       situacao = 0; 
   }

   mensagem_status_exclusao_ingles_unidade(situacao); 
}



//Item (IV) Informar palavra em portugues e unidade, e excluir as palavras em ingles correspondente daquela palavra, que estejam naquela unidade

void excluir_palavras_correspondentes_ingles(Arv23Port **Raiz) {
    int situacao; 

    if (*Raiz != NULL) {
        inf_op Informacao;
        Arv23Port *No_encontrado = NULL;
        int confirmacao = 0, resultado;

        // Limpar o buffer de entrada para evitar problemas com `fgets`
        while (getchar() != '\n');

        printf("Digite a palavra em português que deseja excluir: ");
        fgets(Informacao.palavra_utilizada, 100, stdin);
        Informacao.palavra_utilizada[strcspn(Informacao.palavra_utilizada, "\n")] = '\0';

        // Loop para garantir que a unidade seja válida
        do {
            printf("Digite a unidade: ");
            
            if (scanf("%d", &Informacao.unidade) == 1) { // Valida se a entrada é um número
                if (Informacao.unidade > 0 && Informacao.unidade <= 50) {
                    confirmacao = 1;
                } else {
                    printf("Digite uma unidade válida (Entre 1 e 50).\n");
                }
            } else {
                printf("Entrada inválida. Digite um número válido (Entre 1 e 50).\n");
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida
            }
        } while (confirmacao == 0);

        // Buscar a palavra em português na árvore 2-3
       
        resultado = armazenar_No_ARV23(*Raiz, Informacao, &No_encontrado);

        if (resultado == 0) {
            //A palavra pesquisada não foi encontrada
            situacao = 2; 
        } else{
            int localizacao; 
            //a sub-árvore está na info1
            
            // Remover correspondentes em inglês da árvore associadas
            if(resultado == 1){
                 //está na info1
                 localizacao = 1;
                 resultado = percorrer_remover_palavras_pela_unidade(No_encontrado->info1.significados_ingles, &(No_encontrado->info1.significados_ingles), Informacao);
            }else if(resultado == 2){
                //está na info2
                localizacao = 2; 
                resultado = percorrer_remover_palavras_pela_unidade(No_encontrado->info2.significados_ingles, &(No_encontrado->info2.significados_ingles), Informacao);
            }



            if(resultado == 1){
                //Remoção da arvore binária efetuada com sucesso

                if(localizacao == 1){
                    //como operei com info1, verificar agr se a sub-árvore ficou NULA
                    if (No_encontrado->info1.significados_ingles == NULL) {
                        resultado = remove_arv23(NULL, Raiz, No_encontrado->info1);
                    
                    }

                    if(resultado != 1){
                        //Falha na remoção na árvore 2-3
                        situacao = 4; 
                    }else{
                        //sucesso na remoção da 2-3
                        situacao = 1; 
                    }

                }else if(localizacao == 2){
                    //como operei com info2, verificar agr se a sub-árvore ficou NULA
                    if (No_encontrado->info2.significados_ingles == NULL) {
                        resultado = remove_arv23(NULL, Raiz, No_encontrado->info2); //verificar esse retorno aqui
                    
                    }

                    if(resultado != 1){
                        //Falha na remoção na árvore 2-3
                        situacao = 4; 
                    }else{
                        //sucesso na remoção da 2-3
                        situacao = 1; 
                    }

                }else{
                    //Não precisa remover da 2-3 (operação efetuada com sucesso)
                    situacao = 3; 
                }            
            
            
            }else{
                //Nenhuma palavra removida (pois nenhuma na ArvBB correspondeu a unidade solicitada)
                situacao = 5; 
            }          
            

            
        } 
        
    } else {
        situacao = 0;
        //A árvore está vazia 
    }

    mensagem_status_exclusao_correspondente_ingles(situacao); 
}








