
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024


/**
 * @brief priority queue structure
 */
typedef struct priortyqueue
{
  int heap[MAX_SIZE];   // heap size with 1024
  int count;    // heap counts (index)
} priortyqueue;

/**
 * @brief node location change
 * @param first frist node
 * @param second second node
 */
void
node_exchange(int * first, int * second)
{
  int temp = *first;
  *first = *second;
  *second = temp;
}

/**
 * @brief push function for priority queue
 * @param root priority queue root pointer
 * @param data data to insert into the queue
 * @return none
 */
void 
push(priortyqueue *root, int data) 
{
    if( MAX_SIZE <= root->count) return;   // boundary check (to block heap overflow)
    
    root->heap[root->count] = data;   // index location 
    int cur = root->count;  
    int par = (root->count - 1) / 2;

    while
    (cur > 0 && root->heap[cur] > root->heap[par]) 
    {
        node_exchange(&root->heap[cur], &root->heap[par]);
        cur = par;
        par = (par - 1) / 2;	
    }
    root->count++;
}

/**
 * @brief pop function for priority queue
 * @param root priority queue root pointer
 * @return -1 : error, top value : success
 */
int 
pop(priortyqueue *root) {
  
    if (0 >= root->count) return -1;  // if there is no count, return -1
  
    int ret = root->heap[0];  // to pop value (first value to pop)
    root->count--;    // decrease by one
    root->heap[0] = root->heap[root->count];  // move the last node to the first node
    
    int cur = 0;
    // next is to move the index location
    int next = 0;
    int left = 1; 
    int right = 2;

    // top down exchagne
    while (left < root->count)
    {
        // if the top node is larger than the left child node
        if (root->heap[next] < root->heap[left])
        {
            // move the index to compare and exchange
            next = left;
        }
        // if the top node is larger than the right child node;
        if (root->heap[next] < root->heap[right]) 
        {
            // out of the index location 
            if (right < root->count)
            {
                //node_exchange(&root->heap[next], &root->heap[right]);
                next = right;
            }
        }
        if (next == cur) break;
        else
        {   
            node_exchange(&root->heap[next], &root->heap[cur]);
            // index jump after exchanging
            cur = next;
            // i * n + j
            left = cur * 2 + 1;
            right = cur * 2 + 2;   
        }

    }
    return ret;
}

int main(void) 
{
    int n = 12;
    priortyqueue * root = malloc(sizeof(*root));
    //printf("sizeof %ld", sizeof( root*));

    push(root, 14);
    push(root, 22);
    push(root, 36);
    push(root, 65);
    push(root, 44);
    push(root, 53);
    push(root, 46);
    push(root, 57);
    push(root, 86);
    push(root, 97);
    push(root, 99);
    push(root, 25);

    for(int i = 0; i < n; i++) 
    {
        int data = pop(root);
        printf("%d\n", data);
    }
    
    free(root);
    return 0;
}

