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
            adicionar_bibliografia("bibliografia_database.txt", &palavras_portugues);           
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
                        imprimir_palavras_pela_unidade(palavras_portugues);
                        break; 
                    case 2: 
                         //Imprimir todas as palavras em ingles, correspondentes a palavra em português digitada
                         imprimir_todos_significados_palavra_especifica(palavras_portugues);                        
                         break; 
                    case 3: 
                        // Remover palavra em inglês, informando a palavra em inglês e a unidade na qual ela pertence
                        excluir_palavra_ingles_unidade(&palavras_portugues); 
                        break; 
                    case 4: 
                        //Remover todas as palavras em ingles com unidade especifica, de uma palavra em português especifica   
                        excluir_palavras_correspondentes_ingles(&palavras_portugues);    
                        break; 
                    default: 
                        printf("Digite uma opção válida\n");
                        break; 
                }            
            }while(op2 !=0); 

            break; 
        case 3: 
          //testar o caminho de busca de 30 palavras em português, guardar o caminho e os tempos
          testar_caminho_palavras(palavras_portugues);
          break;           

        case 4: 
             sobre(); 
             break; 

        default: 
            printf("Opção inválida\n"); 
      }
    }while(op1 !=0); 

    return 0; 
}