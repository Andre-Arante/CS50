#include <stdio.h>
#include <stdlib.h>

// create a node data type
typedef struct node {
    int number;
    struct node *next;
}
node;

int main(void) {

    // list of size
    node *list = NULL;

    // add a number to list
    node *n = malloc(sizeof(node));

    // safety check before adding node
    if (n == NULL) {
        return 1;
    }
    // set n.number to 1 and n.next to NULL
    n->number = 1;
    n->next = NULL;

    // update list with new node
    list = n;

    // add another number
    n = malloc(sizeof(node));
    if (n == NULL) {
        free(list);
        return 1;
    }
    // set values for second node
    n->number = 2;
    n->next = NULL;
    // set first node.next to point at current node n
    list->next = n;

    // add another number to llist
    n = malloc(sizeof(node));
    if(n == NULL) {
        free(list->next); // free in reverse order to avoid touching memory you
        free(list);       // shouldn't touch
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;

    // print numbers
    for (node *tmp = list; tmp != NULL; tmp = tmp->next) {
        printf("%i", tmp->number);
    }

    // free list
    while (list != NULL) {
        // save the number 2 node
        node *tmp = list->next;
        // free address of number 1 node
        free(list);
        // point at address saved above
        list = tmp;
    }

    return 0;
}