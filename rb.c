#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rb.h"

/**
 * Red and black tree
 */

#define BLACK 1
#define RED 0

typedef struct node_{
    node_t * par;
	node_t * left;
	node_t * right;
	int color;
	int val;
} node_t;

typedef struct tree_{
	node_t * root;
	node_t * NIL;
} tree_t;


/**
 * @brief create a tree - root
 * @param none
 * @return new tree
 */
tree_t
* tree_create(void)
{
    // memory allocation
	tree_t * tree = malloc(sizeof(tree_t));
    if (NULL == tree)
    {
        return NULL;
    }
    // NIL is a empty node
	node_t * NIL = malloc(sizeof(node_t));
    if (NULL == NIL)
    {
        return NULL;
    }

    // Tree is a top. It will be black.
	NIL->color = BLACK;
	tree->NIL = NIL;
	tree->root= tree->NIL;

	return tree;
}

/**
 * @brief create a node
 * @param root newly created tree
 * @param val a value to insert
 * @return new node
 */
node_t
* create_node(tree_t * root, int val)
{
    // memory allocation
	node_t * node = malloc(sizeof(node));
    if (NULL == node)
    {
        return NULL;
    }

    // Node color will be red
	node->color = RED;
	// NIL will be assigned as child of new node
    node->left = root->NIL;
	node->right = root->NIL;
    // value assignment
	node->val = val;

	return node;
}


/**
 * @brief insert a node
 * @param tree a tree - top
 * @param node a node to insert into the tree
 * @return none
 */
void 
insert_node(tree_t * tree, node_t * node)
{
    // if the first node of the tree is NIL(NULL- empty node), then assign 
	if (tree->root == tree->NIL)
    {
		tree->root = node;
		node->par = NULL;
		node->color = BLACK;
		return;
	}

    // assgin the root as current node and temp
	node_t * cur = tree->root;
	node_t * temp = cur;

    // iteratively compare the value to insert
    while (cur != tree->NIL)
    {
        temp = cur;

        // current ID is bigger than the user input node ID
        if (cur->val > node->val)
        {
            cur = temp->left;
        }
        else
        {
            cur = temp->right;
        }
    }

    // set the parent node and current node
    node->par = temp;
    if (temp->val > node->val)
    {
        temp->left = node;
    }
    else
    {
        temp->right = node;
    }

    // to balance the tree
	tree_fix(tree, node);
	return;
}

/**
 * @brief to balance the tree after inserting
 * @param tree a tree - top
 * @param node a node 
 * @return none
 */
void 
tree_fix(tree_t * tree, node_t * node)
{
    // set parent, uncle, grand parent
	node_t * par = node->par;
	node_t * uncle = get_uncle(node);
	node_t * gp = get_gp(node);

    // if the node is root, then return
	if (node == tree->root)
	{
		node->color = BLACK;
		return;
    }
    // if the parent color is black, then it's good
	else if (BLACK == par->color)
	{
		return;
	}

    // if the current and parent colors are red
	else if (node->color == RED && par->color == RED)
	{
        // if the uncle is black
		if (uncle->color == BLACK)
		{
            /**
             * the node is parent left and the parent is grand parent right
             * case 3 
             * Reference from
             * https://web.cse.ohio-state.edu/~lai.1/6331/0.Red-Black%20Trees.pdf
             */
			if (node == par->left && par == gp->right)
			{
                // rotate right
				rotate_right(tree, node);
				node = par;
			}
            // the node is parent right and the parent is grand parent left
			else if (node == par->right && par == gp->left)
			{
                // rotate left
				rotate_left(tree, node);
				node = par;
			} 

            // same value to ret
			par = node->par;
			uncle = get_uncle(node); // get the node uncle
			gp = get_gp(node); // get the the node grandparent

            // parent color's supposed to black, since the current is red
			par->color = BLACK;
			gp->color = RED;

            // if the parent is the grand parent left
			if (par == gp->left)
			{
				rotate_right(tree, par);
			}
            // the node is parent right and the parent is grand parent left
			else if (par == gp->right)
			{
                // rotate left
				rotate_left(tree, par);
			}
		}

        // if the uncle is RED, we need to fix the parent line
		else
		{
			par->color = BLACK;
			uncle->color = BLACK;
			gp->color = RED;
			tree_fix(tree, gp);
		}

	return;
}


/**
 * @brief to get the grandparent node
 * @param node the node
 * @return the grandparent node
 */
node_t
* get_gp(node_t * node)
{
	if ((node != NULL) && (node->par != NULL))
    {
		return node->par->par;
    }
	else
    {
		return NULL;
    }
}


/**
 * @brief to get the uncle node
 * @param node the node
 * @return the uncle node
 */
node_t
* get_uncle(node_t *node)
{
	node_t * gp = get_gp(node);

    // if NULL, then return
	if (NULL == gp)
    {
		return NULL;
    }
    // if the node parent is placed on left side of the grand parent, then return other side
	if (node->par == gp->left)
    {
		return gp->right;
    }
	else
    {
		return gp->left;
    }

    return NULL;
}

/**
 * @brief to get the sibling node
 * @param node the node
 * @return the sibling node
 */
node_t 
* get_sib(node_t *node)
{
	node_t * par = node->par;

	if (NULL == par)
	{
		return NULL;
	}
    // the node is parent right and the parent is grand parent left
	if (node == par->left)
	{
		return par->right;
	}
	else
	{
		return par->left;
	}
    
    return NULL;
}


/**
 * @brief to rotate to the left
 * @param tree a tree - top
 * @param node a node 
 * @return none
 */
void 
rotate_left(tree_t * tree, node_t * node)
{
    // set the nodes for local
    node_t * temp = node->left;
	node_t * par = node->par;
	node_t * gp = get_gp(node);          

	if (gp == NULL)
	{
		rbt->root = node;
	}
	else
        // if the parent is placed on left side of grand parent
		if (par == gp->left)
        {
			gp->left = node;
        }
		else
        {
			gp->right = node;
        }  
	}

	node->par = gp;
	node->left= par;
	par->par = node;
	par->right = temp;
	temp->par = par;
}

/**
 * @brief to rotate to the right
 * @param tree a tree - top
 * @param node a node 
 * @return none
 */
void 
rotate_right(tree_t *tree, node_t *node)
{
    // set the nodes for local
    node_t * temp = node->right;
	node_t * par = node->par;
	node_t * gp = get_gp(node);
	
	if (NULL = gp)
	{
		tree->root = node;
	}
	else
	{
		if (gp->left == par)
        {
			gp->left = node;
        }
		else
        {
			gp->right = node;
        }
	}

	node->par = gp;
	node->right = par;
	par->par = node;
	par->left = temp;
	temp->par = par;
}


