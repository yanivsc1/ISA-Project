#ifndef ISA_LINKED_LIST_H
#define ISA_LINKED_LIST_H

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

/**
 * A struct to represent a single node in the linked list, with a string key and an unsigned int value
 */
typedef struct node {
    struct node* next;
    char* key;
    unsigned int value;
} Node;

/**
 * A struct to represent a singly linked list of nodes
 */
typedef struct linked_list {
    struct node* head;
    size_t size;
} List;

/**
 * This function creates a new empty list.
 * @return - A pointer to the new list created
 */
List* create_list();

/**
 * This function creates a new node with a given key and value.
 * @param key - The key to be given to the new node
 * @param value - The value to be given to the new node
 * @return - A pointer to the new node created
 */
Node* create_node(char* key, unsigned int value);

/**
 * This function iterates over the linked list to find the value of a node given a key
 * @param list - The list to find the node in
 * @param key - The key of the node to look for
 * @return value - If a node with the given key is found on the list
 * -1 - If list = NULL or if the list doesn't contain a node with the given key
 */
int find_node(List* list, char* key);

/**
 * This function creates a new node from the given key and value, and inserts it to the head of the list
 * @param list - The list to insert the new node to
 * @param key - The key for the new node
 * @param value - The value for the new node
 */
void insert_node(List* list, char* key, unsigned int value);

/**
 * This function frees all resources associated with the list
 * @param list - The source list
 */
void free_list(List* list);

#endif //ISA_LINKED_LIST_H
