#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node * next;
    int data;
} node_t;

typedef struct llist
{
    node_t * head;
    int count;
} llist_t;


llist_t 
* create_list()
{
    llist_t * new_list = malloc(sizeof(llist_t));
    if (NULL == new_list)
    {
        return NULL;
    }

    new_list->head = NULL;
    new_list->count = 0;

    return new_list;
}

int 
add_node(llist_t * list, int data)
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

    // List is empty
    if (NULL == list->head)
    {
        list->head = new_node;
        list->count += 1;
        return 0;
    }

    // Find the tail of single linked list
    node_t *current = list->head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = new_node;

    list->count += 1;
    return 0;
}

int 
remove_list(llist_t * list)
{
    if (NULL == list)
    {
        return -1;
    }

    if (NULL != list->head)
    {
        node_t * current = list->head;
        node_t * temp;
        while (NULL != current)
        {
            temp = current->next;
            free(current);
            current = NULL;
            current = temp;
        }
    }

    free(list);
    list = NULL;
    return 0;
}

node_t 
* search_node(llist_t * list, int data)
{
    if (NULL == list)
    {
        return NULL;
    }

    node_t *current = list->head;

    while (NULL != current)
    {
        if (current->data == data)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

int main()
{
    node_t * temp;

   llist_t * new_list = create_list();
   add_node(new_list, 14545);
   add_node(new_list, 24544);
   add_node(new_list, 33434);
   add_node(new_list, 4443);
   add_node(new_list, 25454);
   add_node(new_list, 33434);
   add_node(new_list, 41233);
   add_node(new_list, 55545);

   // print function
   node_t * current = new_list->head;
   
   for (int idx = 0; idx < new_list->count; ++idx)
   {
       temp = current->next;
       printf("Data %d\n", current->data);
       current = temp;
   }

   temp = search_node(new_list, 4443);
   printf("search node next %d\n", temp->data);
   printf("length count %d\n", new_list->count);

   remove_list(new_list);

}