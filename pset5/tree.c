// Implements a list of numbers as a binary search tree

#include <stdio.h>
#include <stdlib.h>

// Create a node datastruct
typedef struct node {
    int number;
    struct node *left;
    struct node *right;
}
node;

void free_tree(node *root);
void print_tree(node *root);
bool search(node *tree, int number);

int main(void) {

    // initial tree of size 0
    node *tree = NULL;

    // add a number to list
    node *n = malloc(sizeof(node));
    if(n == NULL) {
        return 1;
    }
    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

    // add another number
    // this number is less than the root, therefore it will become a left child
    node *n = malloc(sizeof(node));
    if(n == NULL) {
        return 1;
    }
    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    // add another number
    // this time a right child (greater than root value)
    node *n = malloc(sizeof(node));
    if(n == NULL) {
        return 1;
    }
    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    print_tree(tree);
    free_tree(tree);
}

// recursively iterates through tree and free each node
void free_tree(node *root) {

    // base case
    if (root == NULL) {
        return;
    }

    // recursive case
    free_tree(root->left);  // free child (and recursively all of its desendents)
    free_tree(root->right);
    free(root); // free self last once all childs have been succesfully freed
}


// recursively iterates through tree and prints the root
void print_tree(node *root) {

    // base case
    if(root == NULL) {
        // if reached end of tree, job is finished
        return;
    }

    // recursive case
    print_tree(root->left);     // calls print tree to print left child
    printf("%i\n", root->number);   // prints self
    print_tree(root->right);    // calls print tree to print right child
}

// implements binary search on a tree
// requires that tree is sorted
bool search(node *tree, int number) {
    // make sure tree is not empty
    if (tree = NULL) {
        return false;
    }
    // check if value is on left branch
    else if (number < tree->number) {
        return search(tree->left, number);
    }
    // check the right branch
    else if (number > tree->number) {
        return search(tree->right, number);
    }
    // else we have already found the value
    else {
        return tree;
    }
}