#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um nó da arvore binária
typedef struct Comodo { // Aqui a a escolha de usar "Comodo" em vez de "No" é para ficar mais relacionado ao tema do jogo de detetive, onde cada nó representa um cômodo da casa.
    char nome[50];
    char pista[50]; // Campo para armazenar uma pista, '\0' pode ser usado para indicar que não há pista nesse cômodo
    struct Comodo* esquerdo; // Ponteiro para o filho esquerdo
    struct Comodo* direito; // Ponteiro para o filho direito
} Comodo;

// Estrutura BST para pistas encontradas
typedef struct PistaBST {
    char pista[50];
    struct PistaBST* esquerda;
    struct PistaBST* direita;
} PistaBST;

// Função para criar um novo nó (cômodo)
Comodo* criarSala(const char* nome, const char* pista) {
    Comodo* novo = (Comodo*)malloc(sizeof(Comodo)); // Aloca um comodo(no) dinâmicamente na memória

    if(novo == NULL) { // Verifica se teve algum erro na alocação da memória
        printf("Erro ao alocar memoria");
        exit(1);
    }

    strcpy(novo->nome, nome);
    strcpy(novo->pista, pista); // Copia a pista para o campo do nó, se a pista for '\0' (string vazia), isso indica que não há pista nesse cômodo
    novo->esquerdo = NULL; // Inicicializa o comodo esquerdo como NULL
    novo->direito = NULL; // Inicializa o comodo direito como NULL

    return novo; // Retorna o novo comodo criado
}

// Função para criar um novo nó BST para pistas
PistaBST* criarNoPistaBST(const char* pista) {
    PistaBST* novo = (PistaBST*)malloc(sizeof(PistaBST));
    if(novo == NULL) {
        printf("Erro ao alocar memoria");
        exit(1);
    }
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Função para inserir uma pista na BST de pistas
PistaBST* inserirPista(PistaBST* raiz, const char* pista) {
    if(raiz == NULL) {
        return criarNoPistaBST(pista);
    }

    if(strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if(strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

// Função para exibir as pistas encontradas (percurso em ordem)
void exibirPistas(PistaBST* raiz) {
    if(raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

void liberarPistas(PistaBST* raiz) {
    if(raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
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
void explorarSalas(Comodo* raiz, PistaBST** pistaRaiz) { // O uso de um ponteiro duplo para a raiz da BST de pistas é necessário porque a função pode modificar a raiz da árvore (inserindo novas pistas), e queremos que essa modificação seja refletida fora da função.
    Comodo* atual = raiz;
    char opcao = ' ';

    do {

        printf("\nVoce esta aqui: %s\n\n", atual->nome);
        printf("Para qual direcao deseja ir?\n");
        printf("e. Esquerda\n");
        printf("d. Direita\n");
        printf("s. Sair\n");
        printf("Sua escolha: ");
        scanf("%c", &opcao);
        limparEntrada();

        switch(opcao) {
            case 'e': // Move para o comodo esquerdo
                if(atual->esquerdo == NULL) {
                    printf("\nNao ha caminho nessa direcao\n");
                    break;
                }

                // Atualiza a posição atual do jogador para o comodo escolhido na esquerda
                atual = atual->esquerdo;

                // Verifica se há uma pista nesse comodo, se sim, insere na BST de pistas
                if(atual->pista[0] != '\0') {
                    *pistaRaiz = inserirPista(*pistaRaiz, atual->pista);
                    printf("\nVoce encontrou uma pista: %s\n", atual->pista);
                }

                break;
            
            case 'd': // Move para o comodo direito
                if(atual->direito == NULL) {
                    printf("\nNao ha caminho nessa direcao\n");
                    break;
                }

                // Atualiza a posição atual do jogador para o comodo escolhido na direita
                atual = atual->direito;

                // Verifica se há uma pista nesse comodo, se sim, insere na BST de pistas
                if(atual->pista[0] != '\0') {
                    *pistaRaiz = inserirPista(*pistaRaiz, atual->pista);
                    printf("\nVoce encontrou uma pista: %s\n", atual->pista);
                }

                break;

            case 's': // Sai do jogo
                printf("\nSaindo...\n");
                exibirPistas(*pistaRaiz); // Exibe as pistas encontradas antes de sair
                break;

            default:
                printf("\nERRO: Opcao invalida!\n");
        }

    } while(opcao != 's');

}

// Função principal (main)
int main() {
    Comodo* raiz = criarSala("Hall de Entrada", "\0"); // Criando o nó raiz da árvore, que representa o hall de entrada da casa
    PistaBST* pistaRaiz = NULL; // Raiz da BST de pistas

    raiz->esquerdo = criarSala("Sala de Estar", "\0"); // Criando o nó esquerdo da raiz, que representa a sala de estar
    raiz->esquerdo->direito = criarSala("Cozinha", "Pegadas de lama"); // Criando o nó direito do nó "Sala de Estar", que representa a cozinha
    raiz->esquerdo->esquerdo = criarSala("Quarto", "Lencol de cama com sangue"); // Criando o nó esquerdo do nó "Sala de Estar", que representa o quarto
    raiz->esquerdo->esquerdo->esquerdo = criarSala("Banheiro", "Palavra 'Assassino' escrita na parede"); // Criando o nó esquerdo do nó "Quarto", que representa o banheiro
    raiz->direito = criarSala("Biblioteca", "Livro com pagina arrancada"); // Criando o nó direito da raiz, que representa a biblioteca
    raiz->direito->esquerdo = criarSala("Escritorio", "\0"); // Criando o nó esquerdo do nó "Biblioteca", que representa o escritório
    raiz->direito->direito = criarSala("Jardim", "\0"); // Criando o nó direito do nó "Biblioteca", que representa o jardim
    raiz->direito->direito->esquerdo = criarSala("Garagem", "Chave perdida"); // Criando o nó esquerdo do nó "Jardim", que representa a garagem
    

    printf("Bem-vindo ao Detetive Quest!\n");
    
    explorarSalas(raiz, &pistaRaiz); // Inicia a exploração dos cômodos da casa

    liberar(raiz);
    liberarPistas(pistaRaiz);


    return 0;
}