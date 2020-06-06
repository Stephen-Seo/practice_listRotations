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

Node** n_get_rotations(Node *list) {
    unsigned int length = 0;
    Node *current = list;
    while(current) {
        ++length;
        current = current->next;
    }
    if(length == 0) {
        return NULL;
    }

    Node **array_of_lists = (Node**)malloc((length + 1) * sizeof(Node*));
    memset(array_of_lists, 0, (length + 1) * sizeof(Node*));

    current = list;
    Node *temp, *head;
    unsigned int i = 0;
    while(current) {
        head = current;
        temp = current;
        while(temp) {
            n_push(array_of_lists + i, temp->value);
            temp = temp->next;
        }
        temp = list;
        while(temp && temp != head) {
            n_push(array_of_lists + i, temp->value);
            temp = temp->next;
        }
        ++i;
        current = current->next;
    }

    return array_of_lists;
}

void na_cleanup(Node **array_of_lists) {
    Node **current = array_of_lists;
    while(*current) {
        cleanup_list(*current);
        ++current;
    }
    free(array_of_lists);
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

    printf("Getting lists of rotations...\n");
    Node **array_of_lists = n_get_rotations(list);
    Node **current = array_of_lists;
    while(*current) {
        printf("  ");
        n_print(*current);
        printf("\n");
        ++current;
    }

    na_cleanup(array_of_lists);
    cleanup_list(list);
    return 0;
}
