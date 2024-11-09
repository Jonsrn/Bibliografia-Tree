#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"

void menu_principal(){
    printf("Bem vindo a Bibliografia\n"); 
    printf("[1]-Importar Bibliografia\n"); 
    printf("[2]-Realizar Atividades\n"); 
    printf("[3]-Testes de Funcionalidades Base\n"); 
    printf("[4]-Sobre\n"); 
    printf("[0]-Sair\n"); 
} 

void testes_menu(){
    printf("[1]-Testar Arvore 2-3 Individual\n"); 
    printf("[2]-Testar Arvore BB Individual\n"); 
    printf("[3]-Teste da Lista Encadeada Individual\n"); 
    printf("[4]-Teste das 3 estruturas de maneira Integrada\n"); 
}

void sobre(){
    printf("Trabalho realizado por: Jonathan dos Santos Barbosa\n"); 
}

void realizar_atividades(){
    printf("[1]-Imprimir todas as palavras em português seguida das suas equivalentes em inglês, de uma unidade específica\n"); 
    printf("[2]-Imprimir todas as palavras em ingles, correspondentes a palavra em português digitada\n"); 
    printf("[3]-Remover palavra em inglês, informando a palavra em inglês e a unidade na qual ela pertence\n"); 
    printf("[4]-Remover pa\n"); 
    printf("[0]-Sair\n"); 
}

/*
informar uma palavra em português e a unidade a qual a mesma pertence e então remove-la, para isto 
deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma 
unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da 
árvore 2-3. 

*/
