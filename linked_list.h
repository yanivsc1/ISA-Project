#ifndef ISA_LINKED_LIST_H
#define ISA_LINKED_LIST_H

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef struct node {
    struct node* next;
    char* key;
    unsigned int value;
} Node;

typedef struct linked_list {
    struct node* head;
    size_t size;
} List;


List* create_list();

Node* create_node(char* key, unsigned int value);

int find_node(List* list, char* key);

void insert_node(List* list, char* key, unsigned int value);

void free_list(List* list);

#endif //ISA_LINKED_LIST_H
