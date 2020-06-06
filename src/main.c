#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct SimpleVector {
    char *data;
    unsigned int capacity;
    unsigned int size;
} SimpleVector;

SimpleVector sv_init(unsigned int capacity) {
    SimpleVector sv;
    memset(&sv, 0, sizeof(SimpleVector));

    sv.data = (char*)malloc(capacity * sizeof(char));
    sv.capacity = capacity;

    return sv;
}

void sv_push(SimpleVector *sv, char value) {
    if(!sv->data || sv->capacity == 0) {
        return;
    } else if(sv->size == sv->capacity) {
        char *new_data = (char*)malloc(sv->capacity * 2 * sizeof(char));
        memcpy(new_data, sv->data, sizeof(char) * sv->size);
        free(sv->data);
        sv->data = new_data;
        sv->capacity *= 2;
    }

    sv->data[sv->size++] = value;
}

void sv_cleanup(SimpleVector sv) {
    if(sv.data) {
        free(sv.data);
    }
}

void sv_print(SimpleVector sv) {
    for(unsigned int i = 0; i < sv.size; ++i) {
        printf("%c ", sv.data[i]);
    }
    printf("\n");
}

void sv_print_rotations(SimpleVector sv) {
    for(unsigned int i = 0; i < sv.size; ++i) {
        printf("  ");
        for(unsigned int j = i; j < i + sv.size; ++j) {
            printf("%c ", sv.data[j % sv.size]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    SimpleVector sv = sv_init(32);

    --argc; ++argv;
    while(argc > 0) {
        sv_push(&sv, argv[0][0]);
        --argc; ++argv;
    }
    printf("Got vector: ");
    sv_print(sv);
    printf("Rotations:\n");
    sv_print_rotations(sv);

    sv_cleanup(sv);
    return 0;
}
