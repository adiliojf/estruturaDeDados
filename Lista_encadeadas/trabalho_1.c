#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* prox;
} Node;

// Função de busca recursiva
char* busca_recursiva(Node* lista, int num) {
    if (lista == NULL) {
        return "O valor nao esta na lista.";
    }
    if (lista->val == num) {
        return "O valor esta na lista.";
    } else {
        return busca_recursiva(lista->prox, num);
    }
}

// Função para inserir no início da lista
void inserir_no_inicio(Node** lista, int num) {
    Node* novo = malloc(sizeof(Node));
    if (novo) {
        novo->val = num;
        novo->prox = *lista;
        *lista = novo;
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

// Função para inserir no final da lista
void inserir_no_final(Node** lista, int num) {
    Node* novo = malloc(sizeof(Node));
    if (novo) {
        novo->val = num;
        novo->prox = NULL;
        if (*lista == NULL) {
            *lista = novo;
        } else {
            Node* aux = *lista;
            while (aux->prox) {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

// Função para inserir no meio da lista
void inserir_no_meio(Node** lista, int num, int ant) {
    Node* novo = malloc(sizeof(Node));
    if (novo) {
        novo->val = num;
        if (*lista == NULL) {
            novo->prox = NULL;
            *lista = novo;
        } else {
            Node* aux = *lista;
            while (aux->prox && aux->val != ant) {
                aux = aux->prox;
            }
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

// Função para remover um elemento da lista
Node* remover_elemento(Node** lista, int num) {
    Node* aux = *lista;
    Node* anterior = NULL;

    while (aux != NULL && aux->val != num) {
        anterior = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        return NULL; // Elemento não encontrado
    }

    if (anterior == NULL) {
        *lista = aux->prox; // O elemento a ser removido é o primeiro
    } else {
        anterior->prox = aux->prox;
    }

    return aux;
}

// Função para imprimir a lista
void imprimir(Node* lista) {
    printf("\nLista: ");
    while (lista) {
        printf("%d ", lista->val);
        lista = lista->prox;
    }
    printf("\n\n");
}

int main() {
    int opcao, valor, anterior;
    Node* removido = NULL;
    Node* lista = NULL;
    char* elemento_achado;

    do {
        printf("\n0 - Sair\n1 - Inserir no inicio\n2 - Inserir no meio\n3 - Inserir no final\n4 - Remover elemento\n5 - Imprimir lista\n6 - Buscar elemento\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_no_inicio(&lista, valor);
            break;
        case 2:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            printf("Digite um valor de referencia: ");
            scanf("%d", &anterior);
            inserir_no_meio(&lista, valor, anterior);
            break;
        case 3:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_no_final(&lista, valor);
            break;
        case 4:
            printf("Digite o valor a ser removido: ");
            scanf("%d", &valor);
            removido = remover_elemento(&lista, valor);
            if (removido) {
                printf("O elemento removido foi %d.\n", removido->val);
                free(removido);
            }
            break;
        case 5:
            imprimir(lista);
            break;
        case 6:
            printf("Digite o valor: ");
            scanf("%d", &valor);
            elemento_achado = busca_recursiva(lista, valor);
            printf("%s\n", elemento_achado);
            break;
        default:
            if (opcao != 0) {
                printf("Opção Invalida!\n");
            }
        }
    } while (opcao != 0);

    // Libere a memória alocada para os nós restantes na lista
    while (lista) {
        Node* temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}
