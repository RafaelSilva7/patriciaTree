/**
 * main.c
 * 
 * Create on: 12/05/2018
 *    Author: Rafael da Costa Silva 
 */

#include "patriciaTree.h"

int main() {

    Node* patriciaTree = NULL;

    insert(&patriciaTree, "arara");
    insert(&patriciaTree, "arrasara");
    insert(&patriciaTree, "asas");
    insert(&patriciaTree, "assas");
    insert(&patriciaTree, "assara");

    return 0;
}