#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#define ALPHA 26

typedef struct TrieNode trie; 

struct TrieNode{
	
	bool is_it;  // end of string
	trie *child[ALPHA];
};

static int 
char_to_index(char cha)
{
    return cha - 'A';
}

trie
* insert(trie * root, const char * key)
{
    if('\0' == *key) // if first character is NULL, then turn on the is_it flag
    {
        root->is_it = true;
        return root;
    }
    else
    {
        for(int i = 0; i < 26; i++)
        {
            root->child[i] = NULL;
        }
        int idx = char_to_index(*key); // first character index - 26
        
        if(0 == root->child[idx])
        {
            trie * new = malloc(sizeof(trie));
            if (NULL == new)
            {
                return NULL;
            }
            root->child[idx] = new;
            new = insert(root, key + 1);     
            
        }
    }
    return root;
}


int main()
{
    trie * root = calloc(1, sizeof(trie));
    root = insert(root, "temp");
	root = insert(root, "The");
	root = insert(root, "Quick");

}
