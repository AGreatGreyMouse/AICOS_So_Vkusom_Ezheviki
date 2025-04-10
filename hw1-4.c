#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// создаём новую ноду по запросу 
Node* add_node(Node *head, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("мда, паршивой ноде не нашлось места!\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = head;
    return new_node;
}

Node* reverse_list(Node *head) {
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;    
        current->next = prev;    
        prev = current;          
        current = next; // голландская чехарда
    }
    return prev;
}

void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// оказывается по человечески всю ноду делистнуть нельзя, надо вручную вычищать эти авгиеевы конюшни
void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    int value;

    printf("пиши сколько хочешь чисел, но особо не наглей (0 = горшочек не вари):\n");
    while (1) {
        scanf("%d", &value);
        if (value == 0)
            break;
        
        // нодим ноду
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            printf("добавляли почку связности, всё сломалось!\n");
            return 1;
        }
        new_node->data = value;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            Node *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }

    head = reverse_list(head); // хлеб всему хэд
    printf("ответчик:\n");
    print_list(head);

    // геноцид скинхэдов
    free_list(head);

    return 0;
}
