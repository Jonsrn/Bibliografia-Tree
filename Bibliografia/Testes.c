#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"




void imprimirArv23(Arv23Port *no, int nivel) {
    if (no != NULL) {
        

        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("[%s]", no->info1.palavra_portugues);
        if (no->n_infos == 2) {
            printf(", [%s]", no->info2.palavra_portugues);
        }
        printf("\n");

        imprimirArv23(no->esq, nivel + 1);

        imprimirArv23(no->cen, nivel + 1);

        if (no->n_infos == 2) {
            imprimirArv23(no->dir, nivel + 1);
        }
    }
}

/*
void testeArv23(Arv23Port **Raiz) {
    InfArv23 promove;
    int situacao = 0, info_posicao = 0;
    Arv23Port *no_referencia = NULL;
    InfArv23 Informacao;

    while (getchar() != '\n');

    while (1) {  // Loop para permitir inserções contínuas
        printf("Digite a palavra em português (ou 'sair' para finalizar): ");
        fgets(Informacao.palavra_portugues, 100, stdin);
        Informacao.palavra_portugues[strcspn(Informacao.palavra_portugues, "\n")] = '\0';

        if (strcmp(Informacao.palavra_portugues, "sair") == 0) {
            break;
        }

        // Inserir a palavra na árvore
        insereArv23(Raiz, Informacao, &promove, NULL, &situacao, &info_posicao, &no_referencia);

        // Exibir situação da inserção
        if (situacao == 1) {
            printf("Palavra '%s' inserida com sucesso.\n", Informacao.palavra_portugues);
        } else if (situacao == 2) {
            printf("Palavra '%s' já existe na árvore.\n", Informacao.palavra_portugues);
        } else {
            printf("Falha ao inserir a palavra '%s'.\n", Informacao.palavra_portugues);
        }

        // Imprimir a árvore após cada inserção
        printf("Árvore 2-3 após a inserção:\n");
        imprimirArv23(*Raiz, 0);
    }
}
*/



void testeArv23() {
    Arv23Port *raiz = NULL;
    InfArv23 promove;
    int situacao = 0, info_posicao = 0;
    Arv23Port *no_referencia = NULL;

    // Inserir palavras de teste
    char *palavras[] = {"casa", "arvore", "bola", "dado", "elefante", "faca", "gato", "habito", 
                        "janela", "livro", "montanha", "navio", "olho", "papel", "quadro",
                        "rio", "sol", "teatro", "universidade"};
    int n_palavras = sizeof(palavras) / sizeof(palavras[0]);

    // Imprimir o vetor de palavras antes da inserção
    printf("Vetor de palavras a serem inseridas:\n");
    for (int i = 0; i < n_palavras; i++) {
        printf("%s ", palavras[i]);
    }
    printf("\n");

    // Inserir cada palavra na árvore 2-3
    for (int i = 0; i < n_palavras; i++) {
        printf("\ntesteArv23: Inserindo %s\n", palavras[i]);
        InfArv23 info_port;
        strcpy(info_port.palavra_portugues, palavras[i]);
        insereArv23(&raiz, info_port, &promove, NULL, &situacao, &info_posicao, &no_referencia); 
    }

    // Imprimir a árvore 2-3
    printf("\nÁrvore 2-3 após inserções:\n");
    imprimirArv23(raiz, 0);
}






void imprimirArvBB(ArvBB_ing *no, int nivel) {
    if (no != NULL) {
        imprimirArvBB(no->esq, nivel + 1);

        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }

        printf("%s\n", no->info.palavra_ingles);

        imprimirArvBB(no->dir, nivel + 1);
    }
}

void testeArvBB() {
    ArvBB_ing *raiz = NULL;
    ArvBB_ing *no_existente;

    // Inserir palavras de teste
    char *palavras[] = {"house", "tree", "ball", "dice", "elephant", "knife", "cat", "habit", 
        "church", "window", "book", "mountain", "ship", "eye", "paper", 
        "painting", "river", "sun", "theater", "university", "apple", "bridge", 
        "flower", "garden", "hill", "ice", "jungle", "kite", "lamp", "moon", 
        "nest", "ocean", "piano", "queen", "robot", "stone", "train", "umbrella", 
        "vase", "whale", "xylophone", "zebra", "balloon", "cloud", "desert", 
        "earth", "forest", "guitar", "heart", "island", "jacket", "kangaroo", 
        "lemon", "mirror", "necklace", "orange", "parrot", "quilt", "ring", 
        "snow", "tiger", "unicorn", "violin", "waterfall", "yarn", "ant", 
        "bridge", "candle", "drum", "feather", "grape", "honey", "ink", 
        "jewel", "key", "leaf", "mango", "nut", "olive", "pearl", "quicksand", 
        "rope", "star", "tower", "volcano", "wizard", "yogurt", "anchor", 
        "butterfly", "clock", "dolphin", "egg", "fan", "gate", "hammer", 
        "iron", "jigsaw", "kite", "ladder", "mask"
    };;
    int n_palavras = sizeof(palavras) / sizeof(palavras[0]);

    for (int i = 0; i < n_palavras; i++) {
        InfoBB info_ing;
        strcpy(info_ing.palavra_ingles, palavras[i]);
        inserir_ArvBB_Ingles(&raiz, info_ing, &no_existente);
    }

    // Imprimir a árvore binária de busca
    printf("Árvore binária de busca após inserções:\n");
    imprimirArvBB(raiz, 0);
}

void imprimirLista(list_unid *lista) {
    list_unid *atual = lista;
    printf("Unidade: "); 
    while (atual != NULL) {
        if(atual->prox != NULL){
        printf("%d, ", atual->unidade);
        }else{
            printf("%d.\n", atual->unidade); 
        }
        atual = atual->prox;
    }
    
}


void testeLista() {
    list_unid *lista = NULL;

    // Inserir unidades de teste
    int unidades[] = {3, 1, 4, 2, 5};
    int n_unidades = sizeof(unidades) / sizeof(unidades[0]);

    for (int i = 0; i < n_unidades; i++) {
        inserir_na_Lista(&lista, unidades[i]);
    }

    // Imprimir a lista
    printf("Lista após inserções:\n");
    imprimirLista(lista);
}
void imprimirArvBBComListas(ArvBB_ing *no, int nivel) {
    if (no != NULL) {
        imprimirArvBBComListas(no->esq, nivel + 1);

        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("Palavra Inglês: %s\n", no->info.palavra_ingles);

        // Imprimir lista de unidades
        for (int i = 0; i < nivel + 1; i++) {
            printf("   ");
        }
        printf("Unidades: ");
        imprimirLista(no->info.unidades);

        imprimirArvBBComListas(no->dir, nivel + 1);
    }
}

void imprimirArv23Completa(Arv23Port *no) {
    if (no != NULL) {
        imprimirArv23Completa(no->esq);

        // Imprime info1
        printf("Palavra Português: %s\n", no->info1.palavra_portugues);
        printf("  Traduções em Inglês (ArvBB):\n");
        if (no->info1.significados_ingles) {
            imprimirArvBBComListas(no->info1.significados_ingles, 2);
        } else {
            printf("   Nenhuma tradução encontrada.\n");
        }

        if (no->n_infos == 2) {
            // Imprime info2
            printf("Palavra Português: %s\n", no->info2.palavra_portugues);
            printf("  Traduções em Inglês (ArvBB):\n");
            if (no->info2.significados_ingles) {
                imprimirArvBBComListas(no->info2.significados_ingles, 2);
            } else {
                printf("   Nenhuma tradução encontrada.\n");
            }
        }

        imprimirArv23Completa(no->cen);

        if (no->n_infos == 2) {
            imprimirArv23Completa(no->dir);
        }
    }
}

void testeIntegrado(Arv23Port **raiz_arv23){
    InfArv23 promove;
    int situacao, info_posicao;
    Arv23Port *no_referencia;

    // Inserir várias palavras em português na árvore 2-3
    char *palavras_portugues[] = {"casa", "arvore", "bola", "dado", "elefante", "faca", "gato", "habito", 
                                  "igreja", "janela", "livro", "montanha", "navio", "olho", "papel", "quadro",
                                  "rio", "sol", "teatro", "universidade"};
    int n_palavras_portugues = sizeof(palavras_portugues) / sizeof(palavras_portugues[0]);

    for (int i = 0; i < n_palavras_portugues; i++) {
        InfArv23 info_port;
        memset(&info_port, 0, sizeof(InfArv23)); // Zera a estrutura para evitar lixo
        strcpy(info_port.palavra_portugues, palavras_portugues[i]);
        info_port.significados_ingles = NULL;  // Inicializa a subárvore como NULL

        // Inserção na árvore 2-3
        insereArv23(raiz_arv23, info_port, &promove, NULL, &situacao, &info_posicao, &no_referencia);

        // Verificação de retorno da referência de nó e posição de informação
        if (situacao == 1 || situacao == 2) {
            if (info_posicao == 1) {
                
                printf("Palavra '%s' inserida na árvore 2-3 no nó %s, posição info1\n", 
                       info_port.palavra_portugues, no_referencia->info1.palavra_portugues);
            } else if (info_posicao == 2) {
                if(no_referencia->n_infos == 2){ 
                    printf("Palavra '%s' inserida na árvore 2-3 no nó %s, posição info2\n", 
                        info_port.palavra_portugues, no_referencia->info2.palavra_portugues);
                }else{
                    printf("Epa, só tem uma info aqui. \n"); 
                }        
            } else {
                printf("Erro: posição inválida para a palavra '%s' em português\n", info_port.palavra_portugues);
            }
        } else {
            printf("Erro ao inserir '%s' na árvore 2-3\n", info_port.palavra_portugues);
            continue;
        }

        // Inserir várias palavras em inglês na árvore binária para cada palavra em português
        char *palavras_ingles[] = {"house", "tree", "ball", "dice", "elephant", "knife", "cat", "habit", 
                                   "church", "window", "book", "mountain", "ship", "eye", "paper", "painting",
                                   "river", "sun", "theater", "university"};
        int n_palavras_ingles = sizeof(palavras_ingles) / sizeof(palavras_ingles[0]);
        ArvBB_ing *no_ing_existente = NULL;

        for (int j = 0; j < n_palavras_ingles; j++) {
            InfoBB info_ing;
            memset(&info_ing, 0, sizeof(InfoBB)); // Zera a estrutura para evitar lixo
            strcpy(info_ing.palavra_ingles, palavras_ingles[j]);
            info_ing.unidades = NULL; // Inicializa a lista de unidades como NULL

            int operacao;
            if (info_posicao == 1) {
                printf("Inserindo '%s' na ArvBB de '%s' (info1)\n", 
                       info_ing.palavra_ingles, no_referencia->info1.palavra_portugues);
                operacao = inserir_ArvBB_Ingles(&(no_referencia->info1.significados_ingles), info_ing, &no_ing_existente);
            } else if (info_posicao == 2) {
                printf("Inserindo '%s' na ArvBB de '%s' (info2)\n", 
                       info_ing.palavra_ingles, no_referencia->info2.palavra_portugues);
                operacao = inserir_ArvBB_Ingles(&(no_referencia->info2.significados_ingles), info_ing, &no_ing_existente);
            } else {
                printf("Erro: Posição inválida para a palavra '%s' em português\n", info_port.palavra_portugues);
                continue;
            }

            if (operacao == 1 || operacao == 2) {
                // Insere unidades associadas
                inserir_na_Lista(&no_ing_existente->info.unidades, 1);
                inserir_na_Lista(&no_ing_existente->info.unidades, 2);
            }
        }
    }
    
    /*
    // Imprimir a estrutura completa
    printf("Estrutura completa após inserções:\n");
    imprimirArv23Completa(raiz_arv23);

    */
}



/*

int main(){

    testeArv23();
    testeArvBB(); 


    return 0;
}*/
