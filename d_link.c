#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    node_t *next;
    node_t *prev;
    int data;
} node_t;

typedef struct llist
{
    node_t *head;
    node_t *tail;
    int count;
} llist_t;

/**
 * Comparison between nodes
 * @return 1 for right > left, 0 for equal, -1 for left > right
 * @return -2 for error
 */
int node_compare(node_t *left, node_t *right)
{
    if (NULL == left || NULL == right)
    {
        return -2;
    }

    if (left->data > right->data)
    {
        return -1;
    }

    else if (left->data == right->data)
    {
        return 0;
    }

    return 1;
}

llist_t *create_list()
{
    llist_t *new_list = malloc(sizeof(llist_t));
    if (NULL == new_list)
    {
        return NULL;
    }

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->count = 0;

    return new_list;
}

int add_list(llist_t *list, int data)
{
    if (NULL == list)
    {
        return -1;
    }

    // Generate New Node
    node_t *new_node = malloc(sizeof(node_t));
    if (NULL == new_node)
    {
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    // List is empty
    if (NULL == list->head)
    {
        list->head = new_node;
        list->tail = new_node;
        list->count += 1;
        return 0;
    }

    // List is not empty
    node_t *current = list->head;
    node_t *temp;
    int flag = 0;

    while (current->next != NULL)
    {
        if (node_compare(current, new_node) >= 0)
        {
            current = current->next;
        }
        else
        {
            temp = current->prev;

            temp->next = new_node;
            new_node->prev = temp;
            new_node->next = current;
            current->prev = new_node;

            return 0;

        }
    }

    if (node_compare(current, new_node) >= 0)
    {
        current->next = new_node;
        new_node->prev = current;
        list->tail = current;
        
        return 0;
    }

    temp = current->prev;

    temp->next = new_node;
    new_node->prev = temp;
    new_node->next = current;
    current->prev = new_node;

    return 0;
}