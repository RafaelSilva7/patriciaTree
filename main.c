/**
 * main.c
 * 
 * Create on: 12/05/2018
 *    Author: Rafael da Costa Silva 
 */

#include "patriciaTree.h"

int main() {

    Node* patriciaTree = NULL;

    insert_controller(&patriciaTree, "10101");
    insert_controller(&patriciaTree, "10110110");
    insert_controller(&patriciaTree, "101101101");
    insert_controller(&patriciaTree, "01011100");
    insert_controller(&patriciaTree, "01010");

    return 0;
}