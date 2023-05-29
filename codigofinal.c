#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void preencherLista(Node** head, int tamanho) {
    srand(time(NULL));
    Node* current = *head;
    for (int i = 0; i < tamanho; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = rand() % 100;
        newNode->next = NULL;

        if (*head == NULL) {
            *head = newNode;
            current = *head;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }
}

void exibirLista(Node* head) {
    printf("Lista atual: ");
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int verificarOrdem(Node* head) {
    Node* current = head;
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void selectionSort(Node* head, int passo) {
    Node* current = head;
    for (int i = 0; i <= passo && current->next != NULL; i++) {
        Node* minNode = current;
        Node* innerCurrent = current->next;
        while (innerCurrent != NULL) {
            if (innerCurrent->data < minNode->data) {
                minNode = innerCurrent;
            }
            innerCurrent = innerCurrent->next;
        }
        if (minNode != current) {
            int temp = current->data;
            current->data = minNode->data;
            minNode->data = temp;
        }
        current = current->next;
    }
}

void bubbleSort(Node* head, int passo) {
    Node* current;
    Node* innerCurrent;
    for (int i = 0; i <= passo && current->next != NULL; i++) {
        current = head;
        while (current->next != NULL) {
            innerCurrent = head;
            while (innerCurrent->next != NULL) {
                if (innerCurrent->data > innerCurrent->next->data) {
                    int temp = innerCurrent->data;
                    innerCurrent->data = innerCurrent->next->data;
                    innerCurrent->next->data = temp;
                }
                innerCurrent = innerCurrent->next;
            }
            current = current->next;
        }
    }
}

void insertionSort(Node* head, int passo) {
    if (head == NULL || head->next == NULL)
        return;

    Node* sorted = NULL;
    Node* current = head;
    for (int i = 0; i <= passo && current != NULL; i++) {
        Node* nextNode = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = nextNode;
    }

    head = sorted;
}

void receberConfiguracao(Node* head) {
    printf("Digite a lista após a troca:\n");
    Node* current = head;
    while (current != NULL) {
        scanf("%d", &(current->data));
        current = current->next;
    }
}

int verificarConfiguracao(Node* head, Node* listaInicial, void (*sortFunction)(Node*, int), int passo) {
    Node* current = head;
    Node* correto = listaInicial;

    sortFunction(correto, passo);

    while (current != NULL && correto != NULL) {
        if (current->data != correto->data) {
            return 0;
        }
        current = current->next;
        correto = correto->next;
    }

    return 1;
}

void exibirSolucaoCorreta(Node* head, Node* listaInicial, void (*sortFunction)(Node*, int), int passo) {
    printf("Solução correta: ");
    sortFunction(listaInicial, passo);
    Node* current = listaInicial;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void liberarLista(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Node* head = NULL;
    int tamanho;
    printf("Escolha a dificuldade (tamanho da lista): ");
    scanf("%d", &tamanho);

    preencherLista(&head, tamanho);
    Node* listaInicial = NULL;
    Node* current = head;
    while (current != NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = current->data;
        newNode->next = NULL;

        if (listaInicial == NULL) {
            listaInicial = newNode;
        } else {
            Node* temp = listaInicial;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        current = current->next;
    }

    int opcao;
    int passo = 0;
    void (*sortFunction)(Node*, int) = NULL;
    do {
        printf("\n-----------------------\n");
        printf("1. Exibir lista\n");
        printf("2. Ordenar lista (Selection Sort)\n");
        printf("3. Ordenar lista (Bubble Sort)\n");
        printf("4. Ordenar lista (Insertion Sort)\n");
        printf("5. Sair\n");
        printf("-----------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirLista(head);
                break;
            case 2:
                sortFunction = selectionSort;
                break;
            case 3:
                sortFunction = bubbleSort;
                break;
            case 4:
                sortFunction = insertionSort;
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

        if (sortFunction != NULL) {
            while (!verificarOrdem(head)) {
                exibirLista(head);
                receberConfiguracao(head);
                if (verificarConfiguracao(head, listaInicial, sortFunction, passo)) {
                    printf("A configuração está correta!\n");
                    passo++;
                } else {
                    printf("Configuração incorreta!\n");
                    exibirSolucaoCorreta(head, listaInicial, sortFunction, passo);
                    break;
                }
            }
        }
    } while (opcao != 5);

    liberarLista(head);
    liberarLista(listaInicial);
    return 0;
}
