#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um nó da arvore binária
typedef struct Comodo { // Aqui a a escolha de usar "Comodo" em vez de "No" é para ficar mais relacionado ao tema do jogo de detetive, onde cada nó representa um cômodo da casa.
    char nome[50];
    struct Comodo* esquerdo; // Ponteiro para o filho esquerdo
    struct Comodo* direito; // Ponteiro para o filho direito
} Comodo;

// Função para criar um novo nó (cômodo)
Comodo* criarSala(const char* nome) {
    Comodo* novo = (Comodo*)malloc(sizeof(Comodo)); // Aloca um comodo(no) dinâmicamente na memória

    if(novo == NULL) { // Verifica se teve algum erro na alocação da memória
        printf("Erro ao alocar memoria");
        exit(1);
    }

    strcpy(novo->nome, nome);
    novo->esquerdo = NULL; // Inicicializa o comodo esquerdo como NULL
    novo->direito = NULL; // Inicializa o comodo direito como NULL

    return novo; // Retorna o novo comodo criado
}

void liberar(Comodo* raiz) {
    if(raiz != NULL) {
        liberar(raiz->esquerdo);
        liberar(raiz->direito);
        free(raiz);
    }
}

// Função para limpar o buffer de entrada
void limparEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// Função de explorar os comodos
void explorarSalas(Comodo* raiz) {
    Comodo* atual = raiz;
    char opcao = ' ';

    do {
        // Verifica a cada volta do loop se o jogador chegou em um nó-folha (ultimo comodo), se sim, interrompe o loop e dá fim de jogo.
        if(atual->esquerdo == NULL && atual->direito == NULL) {
            printf("\nVoce chegou ao ultimo comodo (%s), Fim de jogo!\n", atual->nome);
            break;
        }

        printf("\nVoce esta aqui: %s\n\n", atual->nome);
        printf("Para qual direcao desaja ir?\n");
        printf("e. Esquerda\n");
        printf("d. Direita\n");
        printf("s. Sair\n");
        printf("Sua escolha: ");
        scanf("%c", &opcao);
        limparEntrada();

        switch(opcao) {
            case 'e':
                if(atual->esquerdo == NULL) {
                    printf("\nNao ha caminho nessa direcao\n");
                    break;
                }

                // Atualiza a posição atual do jogador para o comodo escolhido na esquerda
                atual = atual->esquerdo;
                break;
            
            case 'd':
                if(atual->direito == NULL) {
                    printf("\nNao ha caminho nessa direcao\n");
                    break;
                }
                // Atualiza a posição atual do jogador para o comodo escolhido na direita
                atual = atual->direito;
                break;

            case 's':
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nERRO: Opcao invalida!\n");
        }

    } while(opcao != 's');

}

// Função principal (main)
int main() {
    Comodo* raiz = criarSala("Hall de Entrada"); // Criando o nó raiz da árvore, que representa o hall de entrada da casa

    raiz->esquerdo = criarSala("Sala de Estar"); // Criando o nó esquerdo da raiz, que representa a sala de estar
    raiz->direito = criarSala("Biblioteca"); // Criando o nó direito da raiz, que representa a biblioteca
    raiz->esquerdo->esquerdo = criarSala("Quarto"); // Criando o nó esquerdo do nó "Sala de Estar", que representa o quarto



    printf("Bem-vindo ao Detetive Quest!\n");
    
    explorarSalas(raiz);

    liberar(raiz);


    return 0;
}