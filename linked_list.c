#include "linked_list.h"


List* create_list(){
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL){
        perror("malloc() error");
        return NULL;
    }
    list->size = 0;
    list->head = NULL;
    return list;
}

Node* create_node(char* key, unsigned int value){
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL){
        perror("malloc() error");
        return NULL;
    }
    node->value = value;
    node->key = key;
    return node;
}

int find(List* list, char* key){
    if (list == NULL){
        return -1;
    }
    Node* node = list->head;
    while(node){
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

void insert_node(List* list, char* key, unsigned int value){
    if (list == NULL) {
        return;
    }
    Node* node = create_node(key, value);
    if (node == NULL){
        return;
    }
    if (list->head == NULL){
        list->head = node;
        list->size++;
        return;
    }
    node->next = list->head;
    list->head = node;
}

void free_list(List* list){
    if (list == NULL){
        return;
    }
    Node* temp = list->head;
    while (temp){
        list->head = temp->next;
        free(temp);
        temp = list->head;
    }
    free(list);
}

