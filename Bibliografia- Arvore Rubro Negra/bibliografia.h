#ifndef _BIBLIOGRAFIA_H
#define _BIBLIOGRAFIA_H

#define PRETO 0
#define VERMELHO 1

//Prototipos das estruturas

typedef struct Lista_Unidades list_unid; //prototipo da lista encadeada das unidades
typedef struct Infos_exclusao inf_ex; //Essa estrutura aqui é pra armazenar as variaveis de exclusao
typedef struct InfoArvBB InfoBB; //Essa struct é as infos da ArvBB    
typedef struct ArvBB_ingles ArvBB_ing; //prototipo da arvore BB, pra colocar as palavras em ingles
typedef struct Info_Arv_RN InfArvRN ;  //prototipo da informação da arvore Rubro Negra
typedef struct ARV_Rubro_Negra_Portugues ArvRNPort; //prototipo da arvore Rubro Negra

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


typedef struct Info_Arv_RN{
    char palavra_portugues[100]; 
    ArvBB_ing *significados_ingles; 
}InfArvRN; 


typedef struct ARV_Rubro_Negra_Portugues{
    InfArvRN info;
    int cor; 
    ArvRNPort *esq, *dir; 
}ArvRNPort;



//Protótipos dos Menus 


void menu_principal(); 
void sobre(); 
void realizar_atividades(); 
void testes_menu(); 



//Protótipo das Funções auxiliares
void adicionar_bibliografia(const char *filename, ArvRNPort *Raiz);  //Função para importar o txt e preencher a árvore 2-3 e suas subsidiarias 
void inserir_palavras_no_dicionario(ArvRNPort **Raiz);  
void imprimir_palavras_pela_unidade(ArvRNPort *Raiz); //Função auxiliar da unidade I
void imprimir_todos_significados_palavra_especifica(ArvRNPort *Raiz); //Função do Item II
void excluir_palavra_ingles_unidade(ArvRNPort **Raiz); //Função referente ao Item III
void percorrer_remover_palavras_pela_unidade(ArvBB_ing *Raiz_percorrendo, ArvBB_ing **Raiz_original, inf_ex Info); //Função do Item IV
void excluir_palavras_correspondentes_ingles(ArvRNPort **Raiz); //Item IV



//Protótipos das funções da Árvore Rubro Negra

ArvRNPort *criar_no_ArvRN(InfArvRN Info); //Função de criação do Nó
int qual_cor(ArvRNPort *Raiz); //Função pra descobrir a cor do Nó
void trocar_cor(ArvRNPort **Raiz); //Função que troca a cor do Nó e de seus dois filhos
void rotacaoDir_RN(ArvRNPort **Raiz); //Função de Rotação à direita
void rotacaoEsq_RN(ArvRNPort **Raiz); //Função de Rotação à esquerda
void balancear_ArvRN(ArvRNPort **Raiz); //Função de Balanceamento
int inserir_ArvRN_Portugues(ArvRNPort **Raiz, InfArvRN Info, ArvRNPort **No_existente); //Função de Inserção
void atualizar_Raiz_ARVRN(ArvRNPort **Raiz); //Função auxiliar que atualiza pra Preto a Raiz
int consultar_ArvRN(ArvRNPort *Raiz, InfArvRN Info); 
void imprimir_ArvRN(ArvRNPort *Raiz); 
int armazenar_NO_ArvRN(ArvRNPort *Raiz, inf_ex Info, ArvRNPort **No_recuperado); //Função que busca e recupera o Nó
void imprimir_infos_RN_por_unidade(ArvRNPort *Raiz, int unidade); 

//Funções de remoção da Rubro-Negra
ArvRNPort *Remover_Menor(ArvRNPort *Raiz); //remove o menor valor
ArvRNPort *Procurando_Menor(ArvRNPort *Raiz); //percorre a subárvore em busca do menor nó
ArvRNPort *mover2EsqVermelho(ArvRNPort **Raiz); 
ArvRNPort *mover2DirVermelho(ArvRNPort **Raiz); 
int remover_No_ArvRN(ArvRNPort **Raiz, InfArvRN Info); //Função principal de remoção
void remover_palavra_ingles_pela_unidade(ArvRNPort **Raiz, ArvRNPort *Raiz_percorrer, inf_ex Info); //Função auxiliar do Item III







//Protótipos das funções da árvore Binária de Busca

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
void imprimirLista(list_unid *lista);

//funções de diagnostico e status

void mensagem_status_impressao_unidade(int situacao); //função de diagnostico do Item I
void mensagem_status_impressao_palavra_especifica(int situacao); //Função de diagnóstico do Item II
void mensagem_status_exclusao_ingles_unidade(int situacao);  //Função de diagnóstico do Item III
void mensagem_status_exclusao_correspondente_ingles(int situacao); //Função de diagnóstico do Item IV


//Funcionalidades de Teste de Software

/*

void imprimirArv23(Arv23Port *no, int nivel); 
void testeArv23(); 
void imprimirArvBB(ArvBB_ing *no, int nivel); 
void testeArvBB(); 
void testeLista(); 


void imprimirArv23Completa(Arv23Port *no); 
void imprimirArvBBComListas(ArvBB_ing *no, int nivel); 
void testeIntegrado(Arv23Port **raiz_arv23); 

*/

















#endif
