#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node {
    struct Node* next;
    char value;
} Node;

void n_push(Node **node, char value) {
    if(*node) {
        Node *current = *node;
        if(current->next) {
            n_push(&current->next, value);
        } else {
            current->next = (Node*)malloc(sizeof(Node));
            memset(current->next, 0, sizeof(Node));
            current->next->value = value;
        }
    } else {
        *node = (Node*)malloc(sizeof(Node));
        memset(*node, 0, sizeof(Node));
        (*node)->value = value;
    }
}

Node* list_from_input(int argc, char **argv) {
    Node *head = NULL;

    --argc; ++argv;
    while(argc > 0) {
        n_push(&head, argv[0][0]);
        --argc; ++argv;
    }

    return head;
}

void cleanup_list(Node *node) {
    if(node) {
        if(node->next) {
            cleanup_list(node->next);
        }
        free(node);
    }
}

void n_print(Node *node) {
    printf("%c ", node->value);
    if(node->next) {
        n_print(node->next);
    }
}

void n_print_until(Node *current, Node *end) {
    printf("%c ", current->value);
    if(current->next && current->next != end) {
        n_print_until(current->next, end);
    }
}

void n_print_rotations(Node *node) {
    Node *start = node;
    while(node) {
        printf("  ");
        n_print(node);
        if(start != node) {
            n_print_until(start, node);
        }
        printf("\n");
        node = node->next;
    }
    printf("\n");
}

int main(int argc, char **argv) {
    Node *list = list_from_input(argc, argv);

    if(!list) {
        printf("List is empty\n");
        cleanup_list(list);
        return 1;
    }

    printf("Got list: ");
    n_print(list);

    printf("\nRotations:\n");
    n_print_rotations(list);

    cleanup_list(list);
    return 0;
}
