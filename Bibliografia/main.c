#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"

int main(){
   Arv23Port *palavras_portugues; 
   palavras_portugues = NULL; 

   int op1, op2; 

   do{
      menu_principal(); 
      scanf("%d", &op1); 
      switch(op1){
        case 0: 
           printf("Encerrando o programa\n"); 
           break;
        case 1: 
            //essa função importará a bibliografia do arquivo. 
            break; 
        case 2: 
            do{
                realizar_atividades();    
                scanf("%d", &op2);

                switch(op2){
                    case 0: 
                       break; 
                    
                    case 1: 
                        // Imprimir todas as palavras em português seguida das suas equivalentes em inglês, de uma unidade específica
                        break; 
                    case 2: 
                        //Imprimir todas as palavras em ingles, correspondentes a palavra em português digitada
                        break; 
                    case 3: 
                        // Remover palavra em inglês, informando a palavra em inglês e a unidade na qual ela pertence
                        break; 
                    case 4:    
                        //Adicionar a descrição posteriormente.          
                        break; 
                    default: 
                        printf("Digite uma opção válida\n");
                        break; 
                }            
            }while(op2 !=0); 

        case 3: 
             sobre(); 
             break; 

        default: 
            printf("Opção inválida\n"); 
      }
    }while(op1 !=0); 

    return 0; 
}