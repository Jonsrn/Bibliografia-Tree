#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "bibliografia.h"


//Essa função visa realizar a busca de 30 palavras em português, demonstrando o caminho e o tempo
void testar_caminho_palavras(ArvRNPort *Raiz){
    int situacao, operacao; 

    if(Raiz != NULL){
        int numero_palavras = 30;
        int tam_vetor;
        long long tempos[30]; // Vetor para armazenar os tempos de cada operação
        situacao = 1; //sucesso

       


        // Vetor fixo de 30 palavras em português utilizando a estrutura inf_op
        inf_op palavras_teste[30] = {{"ventilador", 0},{"protocolo", 0},{"monitor", 0},{"fisico", 0},{"auditoria", 0},{"cliente", 0},
            {"funcionar", 0},{"biblioteca", 0},{"copia", 0},{"bicicleta", 0},{"software", 0},{"celula", 0},{"banco de dados", 0},{"baixar", 0},
            {"servidor", 0},{"falha", 0},{"hardware", 0},{"executar", 0},{"programacao", 0},{"documento", 0},{"recuperar", 0},{"tabela", 0},
            {"aparelho", 0},{"encriptacao", 0},{"computador", 0},{"programa", 0},{"teclado", 0},{"interacao", 0},{"nuvem", 0},{"estrutura", 0}
        };

        inf_op Infos_percurso[MAX_CAMINHO]; //vetor que vai guardar o caminho

        // Preparar arquivo para armazenar resultados
        FILE *arquivo = fopen("tempos_busca.txt", "w");
        if (!arquivo) {
            //Erro ao abrir arquivo
            situacao = 2; 
        }else{ 

            //Como o tempo é afetado pela impressão, a impressão tem de ser feita após a contagem do tempo. (Penso em guardar o caminho em um vetor fixo, depois mandar pra um arquivo txt)
            //Usei um vetor previamente alocado pra evitar operações de realloc, que consomem tempo desnecessário            
            //Vai ter um laço for, pra guardar os tempos em um arquivo e ir procurando com outras palavras (vou guardar em um arquivo)
            
            //dentro do laço a frase vai começar com, "Iniciando busca da palavra xxxx"

            // Obter a frequência do contador de alta resolução
            LARGE_INTEGER freq;
            QueryPerformanceFrequency(&freq);
            
            for(int i = 0; i < numero_palavras; i++){
                operacao = 0; //Não encontrou
                tam_vetor = 0;


                snprintf(Infos_percurso[tam_vetor].palavra_utilizada, 100,"Iniciando busca da palavra %s", palavras_teste[i].palavra_utilizada);
                tam_vetor++; 

                //inicio da medição do tempo aqui
                LARGE_INTEGER inicio, fim;

                QueryPerformanceCounter(&inicio); //inicio

                  operacao = buscar_sem_documentar(Raiz, palavras_teste[i]); 

                 // fim da medição
                QueryPerformanceCounter(&fim); //fim

                //operações envolvendo arquivo e impressão ficam fora da medição, pois consomem tempo

                operacao = buscar_documentar_caminho(Raiz, palavras_teste[i], Infos_percurso, &tam_vetor);

                // Calcula o tempo em nanosegundos
                long long tempo_nano = (fim.QuadPart - inicio.QuadPart) * 1000000000LL / freq.QuadPart;
                tempos[i] = tempo_nano; // Armazena o tempo para a palavra atual

               

                


                //laço for pra guardar 
                fprintf(arquivo, "Palavra: %s | Tempo: %lld nanosegundos\n", palavras_teste[i].palavra_utilizada, tempos[i]);
                for (int j = 0; j < tam_vetor; j++) {
                    fprintf(arquivo, "  Caminho: %s\n", Infos_percurso[j].palavra_utilizada);
                }

                // Adiciona o resultado final
                if (operacao == 1) {
                    fprintf(arquivo, "  Resultado: Encontrada a palavra %s\n\n", palavras_teste[i].palavra_utilizada);
                } else {
                    fprintf(arquivo, "  Resultado: Não encontrada a palavra %s\n\n", palavras_teste[i].palavra_utilizada);
                }

               
                //depois de medir, antes do laço voltar, eu tenho de zerar o vetor, após o armazenamento no arquivo

                memset(Infos_percurso, 0, sizeof(Infos_percurso));

            }

            fclose(arquivo); // Fecha o arquivo após os testes
    
        
        }

        
    
    
    }else{
        //A arvore está vazia
        situacao = 0; 
    }
    
    
    mensagem_status_teste(situacao);

}