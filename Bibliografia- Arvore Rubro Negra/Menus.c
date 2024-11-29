#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"

void menu_principal(){
    printf("Bem vindo a Bibliografia\n"); 
    printf("[1]-Importar Bibliografia\n"); 
    printf("[2]-Realizar Atividades\n"); 
    printf("[3]-Sobre\n"); 
    printf("[0]-Sair\n"); 
} 

void sobre(){
    printf("Trabalho realizado por:\nJonathan dos Santos Barbosa\nClistenes Rodger\n"); 
}

void realizar_atividades(){
    printf("[1]-Imprimir todas as palavras em português seguida das suas equivalentes em inglês, de uma unidade específica\n"); 
    printf("[2]-Imprimir todas as palavras em ingles, correspondentes a palavra em português digitada\n"); 
    printf("[3]-Remover palavra em inglês, informando a palavra em inglês e a unidade na qual ela pertence\n"); 
    printf("[4]-Remover palavras em inglês, de uma palavra em português e unidade especifica\n"); 
    printf("[0]-Sair\n"); 
}

