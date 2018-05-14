/**
 * patriciaTree.h
 * 
 * Create on: 12/05/2018
 *    Author: Rafael da Costa Silva 
 */

#ifndef PATRICIA_TREE_H
#define PATRICIA_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int bool;

typedef struct patriciaTree
{
    char* prefix;
    int label;
    struct patriciaTree* left;
    struct patriciaTree* right;
} Node;

/**
 * Realiza a insercao de uma nova chave a arvore patricia
 * Node**, raiz da arvore a ter a chave inserida
 * char*, chave a ser inserida na arvore
 * @return Retorna 1 caso seja inserido e 0 caso contrario
 */
bool insert(Node** root, char* key);

#endif