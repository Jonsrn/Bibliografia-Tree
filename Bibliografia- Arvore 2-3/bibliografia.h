#ifndef _BIBLIOGRAFIA_H
#define _BIBLIOGRAFIA_H

//Prototipos das estruturas

#define MAX_CAMINHO 100  // Tamanho máximo do vetor de mensagens

typedef struct Lista_Unidades list_unid; //prototipo da lista encadeada das unidades
typedef struct Infos_op inf_op; //Essa estrutura aqui é pra armazenar as variaveis de exclusao
typedef struct InfoArvBB InfoBB; //Essa struct é as infos da ArvBB    
typedef struct ArvBB_ingles ArvBB_ing; //prototipo da arvore BB, pra colocar as palavras em ingles
typedef struct Info_Arv_23 InfArv23;  //prototipo da informação da arvore 2-3
typedef struct ARV_23_Portugues Arv23Port; //prototipo da arvore 2-3

typedef struct Lista_Unidades{
    int unidade;
    list_unid *prox; 
}list_unid;

typedef struct Infos_op{
    char palavra_utilizada[100]; 
    int unidade; 
}inf_op;

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


//Protótipo das funções de diagnóstico

void mensagem_status_montagem_dataset(int situacao); //função de diagnostico da importação do dataset
void mensagem_status_impressao_unidade(int situacao); //Função de diagnostico do Item (I)
void mensagem_status_impressao_palavra_especifica(int situacao); //Função de diagnóstico do Item II
void mensagem_status_exclusao_ingles_unidade(int situacao); //Função de diagnóstico do Item III
void mensagem_status_exclusao_correspondente_ingles(int situacao); //Função de diagnóstico do Item IV
void mensagem_status_teste(int situacao); //Função de diagnóstico dos testes



//Protótipo das Funções auxiliares
void adicionar_bibliografia(const char *filename, Arv23Port **Raiz);  //Função para importar o txt e preencher a árvore 2-3 e suas subsidiarias 
int inserir_palavras_no_dicionario(Arv23Port **Raiz); 
void imprimir_palavras_pela_unidade(Arv23Port *Raiz); //Função auxiliar da unidade I
void imprimir_todos_significados_palavra_especifica(Arv23Port *Raiz); //Função do Item II
void excluir_palavra_ingles_unidade(Arv23Port **Raiz); //Função referente ao Item III
int percorrer_remover_palavras_pela_unidade(ArvBB_ing *Raiz_percorrendo, ArvBB_ing **Raiz_original, inf_op Info); //Função do Item IV
void excluir_palavras_correspondentes_ingles(Arv23Port **Raiz); //Item IV
int imprimir_infos_23_por_unidade(Arv23Port *Raiz, int unidade); //Função pra imprimir todos as infos em ptbr e suas subárvores em ingles que correspondam a unidade
void testar_caminho_palavras(Arv23Port *Raiz); //Função auxiliar dos testes de medição
int remover_palavra_ingles_pela_unidade(Arv23Port **Raiz_original, Arv23Port *Raiz_percorrendo, inf_op Info); 

//Protótipos das funções da árvore 2-3


Arv23Port *criarNoArv23(InfArv23 Info, Arv23Port *Filho_Esq, Arv23Port *Filho_Cent); //Função de Criação do Nó da Árvore 2-3
int ehfolha(Arv23Port *no); // Função pra verificar se é folha, 0 para não, 1 para sim
Arv23Port *adicionaChave(Arv23Port *no, InfArv23 Info, Arv23Port *MaiorNo); 
Arv23Port *insereArv23(Arv23Port **no, InfArv23 Info, InfArv23 *promove, Arv23Port **Pai, int *situacao); //Função de Inserção na Árvore 2-3 de palavra em portugues 
Arv23Port *quebraNo(Arv23Port **No, InfArv23 Info, InfArv23 *promove, Arv23Port *Filho); 
int armazenar_No_ARV23(Arv23Port *Raiz, inf_op Info, Arv23Port **No_recuperado); //Essa função percorre a árvore 2-3 e recupera seu Nó
int buscar_documentar_caminho(Arv23Port *Raiz, inf_op Info, inf_op Infos_percurso[MAX_CAMINHO], int *tam_vetor); 
int buscar_sem_documentar(Arv23Port *Raiz, inf_op Info); 

//Funções de remoção da arv23

int situacao_da_arvore(Arv23Port **Raiz, Arv23Port **Pai, InfArv23 Info); //Intermediaria pra Função de Remoção
int Remover_Arv23(Arv23Port **Raiz, Arv23Port **Pai, InfArv23 Info); //Função principal de remoção da arvore 2-3
int RemoverInfo1Folha(Arv23Port **Raiz, Arv23Port **Pai); //Auxiliar que cuida de remover os casos que envolvem Info1 Folha
int Remover_Info_Nao_Folha(Arv23Port **Raiz, int Localizacao); //Auxiliar que cuida de remover Infos que não estão em folhas
int agregar_infos(Arv23Port **Raiz, int posicao); //Função auxiliar de agregação
InfArv23 movimento_de_sub_arvore(Arv23Port **Raiz, int tipo_movimento, int *operacao); //Trata de fazer o movimento de Onda e recuperar o Menor/Maior valor, dependendo da situação
int tratando_pendencias(Arv23Port **Raiz, Arv23Port **Pai, InfArv23 Info, int posicao); //Trata de tentar resolver situações onde anteriormente não era possivel, através de uma volta na recursão, subindo um nivel
int contar_descendentes(Arv23Port *Raiz); //Contabiliza descendentes, conforme necessidade
int Altura(Arv23Port *Raiz); //Calcula altura de sub-arvores, conforme necessidade
int verificador_consistencia(Arv23Port *Raiz, Arv23Port **Pai); //Função que é chamada após uma remoção bem sucedida para verificar se a estrutura continua balanceada
int auxiliar_reconstrucao(Arv23Port **Raiz); //Função chamada caso a árvore tenha desbalanceado
int reconstruir_Arv(Arv23Port *Raiz, Arv23Port **Nova_Raiz); //Função que percorre a árvore original, reconstruindo uma nova balanceada
void liberarArvore23(Arv23Port **Raiz); //Função que lida de apagar a árvore antiga totalmente




 
 











//Protótipos das funções da árvore Binária

ArvBB_ing* criar_no_ArvBB(InfoBB info); //Função de Criação do Nó. 
int inserir_ArvBB_Ingles(ArvBB_ing **Raiz, InfoBB info, ArvBB_ing **no_existente); //Essa função insere o novo Nó na árvore, e recupera o endereço de seu Nó na árvore, mas se houver o Nó existente na árvore, seu Nó original será recuperado e o novo descartado. 
int Armazenar_No_ARVBB(ArvBB_ing *Raiz, int unidade, ArvBB_ing ***vetor_ingles, int *tam_vetor); // Função que recupera os Nós correspondentes, pra impressão posterior.
int menor_filho(ArvBB_ing *Raiz, ArvBB_ing **menor); //Função que vai recuperar o endereço do menor filho à direita
int remover_No_ArvBB(ArvBB_ing **Raiz, inf_op informacoes); //Função que vai excluir a palavra em ingles da arvore, caso a unidade corresponda E a lista seja nula
void imprimiArvBB(ArvBB_ing *no); 


//Protótipo das funções da Lista Encadeada
int criar_no_Lista(list_unid **novo_elemento, int unidade); //Função pra criar o Nó da Lista
int inserir_na_Lista(list_unid **Raiz, int unidade); //Função para inserir na Lista a Unidade
int buscando_unidade(list_unid *Raiz_Lista, int unidade_buscada); //Função de percorrer a Lista, em busca da unidade pesquisada. 
int remover_unidade_lista(list_unid **Raiz_Lista, int unidade_buscada); // Função para remover a Unidade da Lista. 
void imprimirLista(list_unid *lista); 











#endif
