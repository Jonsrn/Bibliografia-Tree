#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"

/*
typedef struct Lista_Unidades list_unid; 
typedef struct {
    int valor; // Usaremos este campo para armazenar o inteiro
    // Remova ou comente o campo palavra_portugues
    // char palavra_portugues[256];
} InfArv23;

typedef struct Arv23Port {
    InfArv23 info1;
    InfArv23 info2;
    int n_infos;
    struct Arv23Port *esq;
    struct Arv23Port *cen;
    struct Arv23Port *dir;
} Arv23Port;

typedef struct {
    int valor_equivalente; // Campo para armazenar o inteiro
    // Remova ou comente o campo palavra_ingles
    // char palavra_ingles[256];
} InfoBB;

typedef struct ArvBB_ing {
    InfoBB info;
    struct list_unid *unidades;
    struct ArvBB_ing *esq;
    struct ArvBB_ing *dir;
} ArvBB_ing;


typedef struct Lista_Unidades{
    int unidade;
    list_unid *prox; 
}list_unid;



Arv23Port *criarNoArv23(InfArv23 Info, Arv23Port *Filho_Esq, Arv23Port *Filho_Cent) {
    Arv23Port *Novo_no = (Arv23Port *)malloc(sizeof(Arv23Port));
    if (Novo_no == NULL) {
        printf("Falha na alocação\n");
        exit(1); // Encerra o programa em caso de falha na alocação
    } else {
        Novo_no->info1 = Info;
        Novo_no->esq = Filho_Esq;
        Novo_no->cen = Filho_Cent;
        Novo_no->dir = NULL;
        Novo_no->n_infos = 1;
    }
    return Novo_no;
}


int ehfolha(Arv23Port *no) {
    // Verifica se o nó é folha (não tem filhos)
    int operacao; 
    operacao = 0;

    if (no == NULL) {
        operacao = 1; // Considera nó nulo como folha
    }
    return operacao;
}


Arv23Port *adicionaChave(Arv23Port *no, InfArv23 Info, Arv23Port *MaiorNo) {
    // Adiciona uma chave ao nó e ajusta os ponteiros dos filhos
    if (Info.valor < no->info1.valor) {
        // Info é menor que info1, desloca info1 para info2
        no->info2 = no->info1;
        no->info1 = Info;
        if (MaiorNo != NULL) {
            no->dir = no->cen;
            no->cen = MaiorNo;
        }
    } else {
        no->info2 = Info;
        if (MaiorNo != NULL) {
            no->dir = MaiorNo;
        }
    }
    no->n_infos = 2;
    return no;
}


Arv23Port *quebraNo(Arv23Port **No, InfArv23 Info, InfArv23 *promove, Arv23Port *Filho) {
    Arv23Port *Maior;
    if (Info.valor > (*No)->info2.valor) {
        // Info é maior que info2
        *promove = (*No)->info2;
        Maior = criarNoArv23(Info, (*No)->dir, Filho);
        (*No)->n_infos = 1;
        (*No)->dir = NULL;
    } else if (Info.valor > (*No)->info1.valor) {
        // Info está entre info1 e info2
        *promove = Info;
        Maior = criarNoArv23((*No)->info2, Filho, (*No)->dir);
        (*No)->n_infos = 1;
        (*No)->dir = NULL;
    } else {
        // Info é menor que info1
        *promove = (*No)->info1;
        Maior = criarNoArv23((*No)->info2, (*No)->cen, (*No)->dir);
        (*No)->info1 = Info;
        (*No)->n_infos = 1;
        (*No)->cen = Filho;
        (*No)->dir = NULL;
    }
    return Maior;
}



Arv23Port *insereArv23(Arv23Port **no, InfArv23 Info, InfArv23 *promove, Arv23Port **Pai, int *situacao, int *info_posicao, Arv23Port **no_referencia) {
    Arv23Port *MaiorNo = NULL;
    int verificacao = 0;
    InfArv23 promove1;

    if (*no == NULL) {
        // Árvore vazia, cria o primeiro nó
        *no = criarNoArv23(Info, NULL, NULL);
        if (*no == NULL) {
            *situacao = 0; // Falha na alocação
        } else {
            *situacao = 1;       // Inserção bem-sucedida
            *no_referencia = *no; // Retorna o endereço do novo nó
            *info_posicao = 1;
        }
    } else {
        if (Info.valor == (*no)->info1.valor) {
            *situacao = 2; // Chave duplicada
            *info_posicao = 1;
            *no_referencia = *no;
            verificacao = 1;
        }

        if ((*no)->n_infos == 2 && verificacao == 0) {
            if (Info.valor == (*no)->info2.valor) {
                *situacao = 2; // Chave duplicada
                *info_posicao = 2;
                *no_referencia = *no;
                verificacao = 1;
            }
        }

        if (verificacao != 1) {
            if (ehfolha(*no) == 1) {
                if ((*no)->n_infos == 1) {
                    *no = adicionaChave(*no, Info, NULL);
                    *situacao = 1;
                    *no_referencia = *no;
                    *info_posicao = 2;
                } else {
                    MaiorNo = quebraNo(no, Info, promove, NULL);
                    if (*Pai == NULL) {
                        *no = criarNoArv23(*promove, *no, MaiorNo);
                        MaiorNo = NULL;
                    }
                    *situacao = 1;
                    *no_referencia = *no;
                    *info_posicao = 1;
                }
            } else {
                if (Info.valor < (*no)->info1.valor) {
                    MaiorNo = insereArv23(&((*no)->esq), Info, promove, no, situacao, info_posicao, no_referencia);
                } else if (((*no)->n_infos == 1) || (Info.valor < (*no)->info2.valor)) {
                    MaiorNo = insereArv23(&((*no)->cen), Info, promove, no, situacao, info_posicao, no_referencia);
                } else {
                    MaiorNo = insereArv23(&((*no)->dir), Info, promove, no, situacao, info_posicao, no_referencia);
                }
            }
        }
    }

    // Tratamento de pendências
    if (MaiorNo != NULL) {
        if ((*no)->n_infos == 1) {
            *no = adicionaChave(*no, *promove, MaiorNo);
            *situacao = 1;
            *no_referencia = *no;
            *info_posicao = 2;
        } else {
            MaiorNo = quebraNo(no, *promove, &promove1, MaiorNo);
            if (*Pai == NULL) {
                *no = criarNoArv23(promove1, *no, MaiorNo);
                MaiorNo = NULL;
            } else {
                *promove = promove1;
            }
            *situacao = 1;
            *no_referencia = *no;
            *info_posicao = 1;
        }
    }

    return MaiorNo;
}


//Binária

ArvBB_ing* criar_no_ArvBB(InfoBB info) {
    ArvBB_ing *novo_no = (ArvBB_ing *)malloc(sizeof(ArvBB_ing));
    if (novo_no == NULL) {
        printf("Falha na alocação\n");
        exit(1); // Encerra o programa em caso de falha na alocação
    }
    novo_no->info = info;
    novo_no->unidades = NULL;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
}


int inserir_ArvBB_Ingles(ArvBB_ing **Raiz, InfoBB info, ArvBB_ing **no_existente) {
    int operacao = 1; // 1 significa que deu certo
    if (*Raiz == NULL) {
        ArvBB_ing *novo_no = criar_no_ArvBB(info);
        *Raiz = novo_no;
        *no_existente = *Raiz; // Retorna o endereço do novo nó
    } else {
        if (info.valor_equivalente < (*Raiz)->info.valor_equivalente) {
            operacao = inserir_ArvBB_Ingles(&((*Raiz)->esq), info, no_existente);
        } else if (info.valor_equivalente > (*Raiz)->info.valor_equivalente) {
            operacao = inserir_ArvBB_Ingles(&((*Raiz)->dir), info, no_existente);
        } else {
            // O nó já está alocado
            *no_existente = *Raiz;
            operacao = 2; // 2 significa que o nó já existe
        }
    }
    return operacao;
}


void imprimirArvBB(ArvBB_ing *no, int nivel) {
    if (no != NULL) {
        imprimirArvBB(no->esq, nivel + 1);
        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("%d\n", no->info.valor_equivalente);
        imprimirArvBB(no->dir, nivel + 1);
    }
}



void testeArvBB() {
    ArvBB_ing *raiz = NULL;
    ArvBB_ing *no_existente = NULL;
    InfoBB info;
    int numeros[] = {50, 20, 70, 10, 30, 60, 80, 25, 35, 65, 85, 50, 70, 10};
    int n_numeros = sizeof(numeros) / sizeof(numeros[0]);

    for (int i = 0; i < n_numeros; i++) {
        info.valor_equivalente = numeros[i];
        inserir_ArvBB_Ingles(&raiz, info, &no_existente);
    }

    // Imprimir a árvore binária de busca
    printf("Árvore Binária de Busca após inserções:\n");
    imprimirArvBB(raiz, 0);
}


*/



















void imprimirArv23(Arv23Port *no, int nivel) {
    if (no != NULL) {
        imprimirArv23(no->esq, nivel + 1);

        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("[%s]", no->info1.palavra_portugues);
        if (no->n_infos == 2) {
            printf(", [%s]", no->info2.palavra_portugues);
        }
        printf("\n");

        imprimirArv23(no->cen, nivel + 1);

        if (no->n_infos == 2) {
            imprimirArv23(no->dir, nivel + 1);
        }
    }
}

void testeArv23() {
    Arv23Port *raiz = NULL;
    InfArv23 promove;
    int situacao = 0, info_posicao = 0;
    Arv23Port *no_referencia = NULL;

    // Inserir palavras de teste
    char *palavras[] = {"casa", "arvore", "bola", "dado", "elefante", "faca", "gato", "gato", "bobla"};
    int n_palavras = sizeof(palavras) / sizeof(palavras[0]);

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
    char *palavras[] = {"house", "tree", "ball", "dice", "elephant", "knife", "cat"};
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
    while (atual != NULL) {
        printf("%d -> ", atual->unidade);
        atual = atual->prox;
    }
    printf("NULL\n");
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

void testeIntegrado() {
    Arv23Port *raiz_arv23 = NULL;
    InfArv23 promove;
    int situacao, info_posicao;
    Arv23Port *no_referencia;

    // Inserir palavras em português na árvore 2-3
    char *palavras_portugues[] = {"casa", "arvore", "bola", "frajola"};
    int n_palavras_portugues = sizeof(palavras_portugues) / sizeof(palavras_portugues[0]);

    for (int i = 0; i < n_palavras_portugues; i++) {
        InfArv23 info_port;
        memset(&info_port, 0, sizeof(InfArv23)); // Zera a estrutura para evitar lixo
        strcpy(info_port.palavra_portugues, palavras_portugues[i]);
        info_port.significados_ingles = NULL;  // Inicializa a subárvore como NULL

        // Inserção na árvore 2-3
        insereArv23(&raiz_arv23, info_port, &promove, NULL, &situacao, &info_posicao, &no_referencia);

        // Debugging para verificar se `no_referencia` e `info_posicao` foram corretamente atualizados
        if (situacao == 1 || situacao == 2) {
            if (info_posicao == 1) {
                printf("Palavra '%s' inserida na árvore 2-3 no nó %s, posição info1\n", 
                       info_port.palavra_portugues, no_referencia->info1.palavra_portugues);
            } else if (info_posicao == 2) {
                printf("Palavra '%s' inserida na árvore 2-3 no nó %s, posição info2\n", 
                       info_port.palavra_portugues, no_referencia->info2.palavra_portugues);
            } else {
                printf("Erro: posição inválida para a palavra '%s' em português\n", info_port.palavra_portugues);
            }
        } else {
            printf("Erro ao inserir '%s' na árvore 2-3\n", info_port.palavra_portugues);
            continue;
        }

        // Agora inserir palavras em inglês na árvore binária dentro do nó da árvore 2-3
        char *palavras_ingles[] = {"house", "tree", "ball", "Kripto"};
        ArvBB_ing *no_ing_existente = NULL;

        for (int j = 0; j < 3; j++) {
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
                inserir_na_Lista(&no_ing_existente->info.unidades, 1);
                inserir_na_Lista(&no_ing_existente->info.unidades, 2);
            }
        }
    }

    // Função para imprimir a estrutura completa
    printf("Estrutura completa após inserções:\n");
    imprimirArv23Completa(raiz_arv23);
}



/*

int main(){

    testeArv23();
    testeArvBB(); 


    return 0;
}*/