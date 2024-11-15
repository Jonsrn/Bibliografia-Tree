#ifndef _BIBLIOGRAFIA_H
#define _BIBLIOGRAFIA_H

//Prototipos das estruturas

typedef struct Lista_Unidades list_unid; //prototipo da lista encadeada das unidades
typedef struct Infos_exclusao inf_ex; //Essa estrutura aqui é pra armazenar as variaveis de exclusao
typedef struct InfoArvBB InfoBB; //Essa struct é as infos da ArvBB    
typedef struct ArvBB_ingles ArvBB_ing; //prototipo da arvore BB, pra colocar as palavras em ingles
typedef struct Info_Arv_23 InfArv23;  //prototipo da informação da arvore 2-3
typedef struct ARV_23_Portugues Arv23Port; //prototipo da arvore 2-3

typedef struct Lista_Unidades{
    int unidade;
    list_unid *prox; 
}list_unid;

typedef struct Infos_exclusao{
    char palavra_ser_excluida[100]; 
    int unidade; 
}inf_ex;

typedef struct InfoArvBB{
    char palavra_ingles[100]; 
    list_unid *unidades; 
}InfoBB; 

typedef struct ArvBB_ingles{
    InfoBB info;  
    ArvBB_ing *esq, *dir; 
}ArvBB_ing;


typedef struct Info_Arv_23{
    char palavra_portugues[100]; 
    ArvBB_ing *significados_ingles; 
}InfArv23; 


typedef struct ARV_23_Portugues{
    InfArv23 info1, info2;
    int n_infos; 
    Arv23Port *esq, *cen, *dir; 
}Arv23Port;



//Protótipos dos Menus 


void menu_principal(); 
void sobre(); 
void realizar_atividades(); 
void testes_menu(); 

//Protótipo das Funções auxiliares
void adicionar_bibliografia(const char *filename, Arv23Port *Raiz);  //Função para importar o txt e preencher a árvore 2-3 e suas subsidiarias 
void inserir_palavras_no_dicionario(Arv23Port **Raiz); 
void imprimirArv23(Arv23Port *no, int nivel); 
void inserir_palavra_teste(Arv23Port **Raiz);  
void imprimir_palavras_pela_unidade(Arv23Port *Raiz); //Função auxiliar da unidade I
void imprimir_todos_significados_palavra_especifica(Arv23Port *Raiz); //Função do Item II





//Protótipos das funções da árvore 2-3


Arv23Port *criarNoArv23(InfArv23 Info, Arv23Port *Filho_Esq, Arv23Port *Filho_Cent); //Função de Criação do Nó da Árvore 2-3
int ehfolha(Arv23Port *no); // Função pra verificar se é folha, 0 para não, 1 para sim
Arv23Port *adicionaChave(Arv23Port *no, InfArv23 Info, Arv23Port *MaiorNo); 
Arv23Port *insereArv23(Arv23Port **no, InfArv23 Info, InfArv23 *promove, Arv23Port **Pai, int *situacao, int *info_posicao, Arv23Port **no_referencia); //Função de Inserção na Árvore 2-3 de palavra em portugues 
Arv23Port *quebraNo(Arv23Port **No, InfArv23 Info, InfArv23 *promove, Arv23Port *Filho, Arv23Port **no_referencia); 
int armazenar_No_ARV23(Arv23Port *Raiz, InfArv23 Info, Arv23Port **No_recuperado); //Essa função percorre a árvore 2-3 e recupera seu Nó
void imprimir_infos_23_por_unidade(Arv23Port *Raiz, int unidade); //Função pra imprimir todos as infos em ptbr e suas subárvores em ingles que correspondam a unidade


void imprimirArv23(Arv23Port *no, int nivel); //função de impressão, temporaria 



//Funções de remoção da arv23
int remove_arv23(Arv23Port **Pai, Arv23Port **raiz, InfArv23 info); 
void menor_info_esquerda(Arv23Port *no, Arv23Port **no_resultado, Arv23Port **pai_no); 
void menor_info_direita(Arv23Port *no, Arv23Port **no_resultado, Arv23Port **pai_no); 
int situacao_da_arvore(Arv23Port **Pai, Arv23Port **Raiz, InfArv23 Info); 



//Protótipos das funções da árvore Binária

ArvBB_ing* criar_no_ArvBB(InfoBB info); //Função de Criação do Nó. 
int inserir_ArvBB_Ingles(ArvBB_ing **Raiz, InfoBB info, ArvBB_ing **no_existente); //Essa função insere o novo Nó na árvore, e recupera o endereço de seu Nó na árvore, mas se houver o Nó existente na árvore, seu Nó original será recuperado e o novo descartado. 
int Armazenar_No_ARVBB(ArvBB_ing *Raiz, int unidade, ArvBB_ing ***vetor_ingles, int *tam_vetor); // Função que recupera os Nós correspondentes, pra impressão posterior.
int menor_filho(ArvBB_ing *Raiz, ArvBB_ing **menor); //Função que vai recuperar o endereço do menor filho à direita
int remover_No_ArvBB(ArvBB_ing **Raiz, inf_ex informacoes); //Função que vai excluir a palavra em ingles da arvore, caso a unidade corresponda E a lista seja nula

void imprimiArvBB(ArvBB_ing *no); 


//Protótipo das funções da Lista Encadeada
int criar_no_Lista(list_unid **novo_elemento, int unidade); //Função pra criar o Nó da Lista
int inserir_na_Lista(list_unid **Raiz, int unidade); //Função para inserir na Lista a Unidade
int buscando_unidade(list_unid *Raiz_Lista, int unidade_buscada); //Função de percorrer a Lista, em busca da unidade pesquisada. 
int remover_unidade_lista(list_unid **Raiz_Lista, int unidade_buscada); // Função para remover a Unidade da Lista. 




//Funcionalidades de Teste de Software



void imprimirArv23(Arv23Port *no, int nivel); 
void testeArv23(); 
void imprimirArvBB(ArvBB_ing *no, int nivel); 
void testeArvBB(); 
void imprimirLista(list_unid *lista); 
void testeLista(); 


void imprimirArv23Completa(Arv23Port *no); 
void imprimirArvBBComListas(ArvBB_ing *no, int nivel); 
void testeIntegrado(Arv23Port **raiz_arv23); 



















#endif
