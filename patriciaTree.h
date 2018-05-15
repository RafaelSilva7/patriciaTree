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

typedef struct patricia_tree
{
    char* prefix;
    int label;
    struct patricia_tree* left;
    struct patricia_tree* right;
} Node;

/**
 * Realiza a insercao propriamente dita na arvore
 * Node**, raiz da arvore patricia
 * Node**, node no qual a chave sera inserida
 * char*, chave a ser inserida na arvore
 * int*, posicao em que a chave sera inserida (em relacao a chave)
 * int, posicao em que a chave sera inserida (em relacao ao node)
 * @return Retorna 1 caso seja inserido e 0 caso contrario
 */
bool insert(Node** p_tree, Node** root, char* key, int* posit, int posit_root);

/**
 * Realiza o controle da insercao de uma nova chave a arvore patricia
 * Node**, raiz da arvore patricia
 * char*, chave a ser inserida na arvore
 * @return Retorna 1 caso seja inserido e 0 caso contrario
 */
bool insert_controller(Node** p_tree, char* key);

/**
 * Realiza a busca do local a ser inserido a nova chave
 * Node**, raiz da arvore patricia
 * Node**, node a ser realizado a pesquisa
 * char*, chave a ser inserida na arvore
 * @return Retorna 1 caso seja inserido e 0 caso contrario
 */
bool find_insert(Node** p_tree, Node** root, char* key, int* posit);

#endif