#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "bibliografia.h"

// Funções de Inserção

// Função para criar um novo nó
Arv23Port *criarNoArv23(InfArv23 Info, Arv23Port *Filho_Esq, Arv23Port *Filho_Cent) {
    Arv23Port *Novo_no = (Arv23Port *)malloc(sizeof(Arv23Port));
    if (Novo_no == NULL) {
        printf("Falha na alocação\n");
        exit(1); // Encerra o programa em caso de falha na alocação
    }
    memset(Novo_no, 0, sizeof(Arv23Port)); // Zera para evitar lixo

    Novo_no->info1 = Info;
    Novo_no->esq = Filho_Esq;
    Novo_no->cen = Filho_Cent;
    Novo_no->dir = NULL;
    Novo_no->n_infos = 1;
    return Novo_no;
}

// Função para verificar se o nó é folha
int ehfolha(Arv23Port *no) {
    // Um nó é folha se não tem filho esquerdo
    return (no != NULL && no->esq == NULL);
}

// Função para adicionar uma chave ao nó
Arv23Port *adicionaChave(Arv23Port *no, InfArv23 Info, Arv23Port *MaiorNo) {
    // Compara a nova informação com a info1 do nó
    int comparacao = strcmp(Info.palavra_portugues, no->info1.palavra_portugues);
    if (comparacao < 0) {
        // Nova info é menor que info1
        no->info2 = no->info1;
        no->info1 = Info;
        if (MaiorNo != NULL) {
            no->dir = no->cen;
            no->cen = MaiorNo;
        }
    } else {
        // Nova info é maior ou igual a info1
        no->info2 = Info;
        if (MaiorNo != NULL) {
            no->dir = MaiorNo;
        }
    }
    no->n_infos = 2;
    return no;
}

// Função para quebrar o nó
Arv23Port *quebraNo(Arv23Port **No, InfArv23 Info, InfArv23 *promove, Arv23Port *Filho) {
    int comparacao1 = strcmp(Info.palavra_portugues, (*No)->info2.palavra_portugues);
    int comparacao2 = strcmp(Info.palavra_portugues, (*No)->info1.palavra_portugues);
    Arv23Port *Maior;

    if (comparacao1 > 0) {
        // Caso 1: Info > info2
        *promove = (*No)->info2;
        Maior = criarNoArv23(Info, (*No)->dir, Filho);
    } else if (comparacao2 > 0) {
        // Caso 2: info1 < Info < info2
        *promove = Info;
        Maior = criarNoArv23((*No)->info2, Filho, (*No)->dir);
    } else {
        // Caso 3: Info < info1
        *promove = (*No)->info1;
        Maior = criarNoArv23((*No)->info2, (*No)->cen, (*No)->dir);
        (*No)->info1 = Info;
        (*No)->cen = Filho;
    }

    // Atualiza o nó atual
    (*No)->n_infos = 1;
    memset(&(*No)->info2, 0, sizeof(InfArv23)); // Limpa info2
    (*No)->dir = NULL;

    return Maior;
}

// Função de inserção na árvore 2-3
Arv23Port *insereArv23(Arv23Port **no, InfArv23 Info, InfArv23 *promove, Arv23Port **Pai, int *situacao, int *info_posicao, Arv23Port **no_referencia) {
    Arv23Port *MaiorNo = NULL;
    InfArv23 promove_local; // Variável local para promoção
    int comparacao1, comparacao2;
    int verificacao = 0; // 0 significa que não tem palavra igual na árvore

    if (*no == NULL) {
        // Se a árvore for Nula, criaremos o primeiro Nó
        *no = criarNoArv23(Info, NULL, NULL);
        if (*no == NULL) {
            *situacao = 0; // Falha total devido à falha de alocação
        } else {
            *situacao = 1;       // Sucesso com nova inserção
            *no_referencia = *no; // Retorna o endereço do novo nó
            *info_posicao = 1;    // A palavra está em info1
        }
    } else {
        comparacao1 = strcmp(Info.palavra_portugues, (*no)->info1.palavra_portugues);

        if (comparacao1 == 0) {
            *situacao = 2;        // A palavra já existe em info1
            *info_posicao = 1;
            *no_referencia = *no;
            verificacao = 1;
        }

        if ((*no)->n_infos == 2) {
            comparacao2 = strcmp(Info.palavra_portugues, (*no)->info2.palavra_portugues);
            if (comparacao2 == 0) {
                *situacao = 2;    // A palavra já existe em info2
                *info_posicao = 2;
                *no_referencia = *no;
                verificacao = 1;
            }
        }

        if (verificacao != 1) {
            if (ehfolha(*no)) { // Se for folha
                if ((*no)->n_infos == 1) {
                    // Nó tem apenas uma informação
                    printf("Adicionando segunda chave '%s' no nó com info1='%s'\n", Info.palavra_portugues, (*no)->info1.palavra_portugues);
                    *no = adicionaChave(*no, Info, NULL);
                    *situacao = 1;
                    *no_referencia = *no;
                    *info_posicao = 2;
                } else {
                    // Nó tem duas informações, precisa quebrar
                    printf("Quebrando o nó. Antes da quebra, info1='%s' e info2='%s', nova info='%s'\n", (*no)->info1.palavra_portugues, (*no)->info2.palavra_portugues, Info.palavra_portugues);
                    MaiorNo = quebraNo(no, Info, &promove_local, NULL);
                    if (Pai == NULL || *Pai == NULL) {
                        *no = criarNoArv23(promove_local, *no, MaiorNo);
                        MaiorNo = NULL;
                        *info_posicao = 1;
                        *no_referencia = *no;
                        printf("Novo nó raiz criado com promoção de '%s'\n", promove_local.palavra_portugues);
                    } else {
                        *promove = promove_local;
                        *no_referencia = *no;
                        *info_posicao = 1;
                    }
                }
            } else {
                // Nó não é folha, precisa descer na árvore
                if (comparacao1 < 0) {
                    printf("Descendo para a esquerda do nó com info1='%s'\n", (*no)->info1.palavra_portugues);
                    MaiorNo = insereArv23(&((*no)->esq), Info, &promove_local, no, situacao, info_posicao, no_referencia);
                } else {
                    if ((*no)->n_infos == 2) {
                        comparacao2 = strcmp(Info.palavra_portugues, (*no)->info2.palavra_portugues);
                    }
                    if (((*no)->n_infos == 1) || (comparacao2 < 0)) {
                        printf("Descendo para o centro do nó com info1='%s'\n", (*no)->info1.palavra_portugues);
                        MaiorNo = insereArv23(&((*no)->cen), Info, &promove_local, no, situacao, info_posicao, no_referencia);
                    } else {
                        printf("Descendo para a direita do nó com info2='%s'\n", (*no)->info2.palavra_portugues);
                        MaiorNo = insereArv23(&((*no)->dir), Info, &promove_local, no, situacao, info_posicao, no_referencia);
                    }
                }

                // Tratamento das pendências após as chamadas recursivas
                if (MaiorNo != NULL) {
                    if ((*no)->n_infos == 1) {
                        *no = adicionaChave(*no, promove_local, MaiorNo);
                        *situacao = 1;
                        *no_referencia = *no;
                        *info_posicao = 2;
                    } else {
                        InfArv23 promove1;
                        MaiorNo = quebraNo(no, promove_local, &promove1, MaiorNo);
                        if (Pai == NULL || *Pai == NULL) {
                            *no = criarNoArv23(promove1, *no, MaiorNo);
                            MaiorNo = NULL;
                            *info_posicao = 1;
                            *no_referencia = *no;
                        } else {
                            *promove = promove1;
                            *info_posicao = 1;
                        }
                        *situacao = 1;
                        *no_referencia = *no;
                    }
                }
            }
        }
    }

    return MaiorNo;
}
