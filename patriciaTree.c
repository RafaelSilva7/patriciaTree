/**
 * patriciaTree.c
 * 
 * Create on: 12/05/2018
 *    Author: Rafael da Costa Silva 
 */

#include "patriciaTree.h"


bool insert_controller(Node** p_tree, char* key)
{
    int posit = 0;

    // Caso a raiz seja nula
    if (*p_tree == NULL)
    {
        // Aloco a raiz da arvore
        (*p_tree) = (Node*) malloc(sizeof(Node));
        (*p_tree)->label = 0;
        (*p_tree)->prefix = NULL;
        (*p_tree)->left = (*p_tree)->right = NULL;
    }

    // Realiza a busca e insercao da nova chave
    return find_insert(p_tree, p_tree, key, &posit);
}


bool find_insert(Node** p_tree, Node** root, char* key, int* posit)
{
    if ((*root) == NULL) return 0;

    // Caso nao esteja na raiz procuro o local a ser inserido
    if ((*p_tree) != (*root))
    {
        int size = (int) strlen((*root)->prefix);
        int size_key = (int) strlen(key);

        for (int cont = 0; cont < size; cont++)
        {
            // percorri toda a chave (uma chave n pode estar contida dentro de outra)
            if (*posit == size_key)
                return 0;
            // encontrei a posicao a ser inserida
            if ((*root)->prefix[cont] != key[*posit])
                return insert(p_tree, root, key, posit, cont);

            (*posit)++;
        }

        // chave invalida (iguais) ou a chave atual esta contida na nova chave
        if (size == size_key || (size < size_key && (*root)->right == NULL && (*root)->left == NULL))
            return 0;
    }

    bool resp;

    // insercao ou busca a direita
    if (key[*posit] == '1')
    {
        if ((*root)->right == NULL)
            resp = insert(p_tree, &(*root)->right, key, posit, 0);
        else
            resp = find_insert(p_tree, &(*root)->right, key, posit);
    }
        // insercao ou busca a esquerda
    else
    {
        if ((*root)->left == NULL)
            resp = insert(p_tree, &(*root)->left, key, posit, 0);
        else
            resp = find_insert(p_tree, &(*root)->left, key, posit);
    }

    return resp;
}


bool insert(Node** p_tree, Node** root, char* key, int* posit, int posit_root)
{
    int size_key = (int) strlen(key);

    // Aloca o node que recebera o restante da chave a ser inserida
    Node* new = (Node*) malloc(sizeof(Node));
    new->prefix = (char*) calloc((size_t) (size_key - (*posit)), sizeof(char));
    new->left = new->right = NULL;

    // Somente insere um novo node
    if ((*root) == NULL)
    {
        for(int i = *posit; i < size_key; i++)
        {
            new->prefix[i] = key[*posit];
            (*posit)++;
        }
        (*root) = new;
    }
    else
    {
        char* str_parent = (char*) calloc((size_t) (posit_root - 1), sizeof(char));
        int size = (int) strlen((*root)->prefix);
        int cont;

        // Aloca o node que recebera o restante da chave do node atual
        Node* sister = (Node*) malloc(sizeof(Node));
        sister->left = sister->right = NULL;
        sister->prefix = (char*) calloc((size_t) (size - posit_root), sizeof(char));

        // Armazeno o valor de prefixo
        for (int i = 0; i < posit_root; i++)
            str_parent[i] = (*root)->prefix[i];

        cont = 0;
        // O restante da chavo do node
        for (int i = posit_root; i < size; i++)
        {
            sister->prefix[cont] = (*root)->prefix[i];
            cont++;
        }

        cont = 0;
        // O restante da nova chave
        for (int i = *posit; i < size_key; i++)
        {
            new->prefix[cont] = key[i];
            cont++;
        }

        (*root)->prefix = str_parent;

        // Caso new deva ser inserido a direita
        if (new->prefix[0] == '1')
        {
            (*root)->left = sister;
            (*root)->right = new;
        }
        else
        {
            (*root)->left = new;
            (*root)->right = sister;
        }
    }

    // Numero de palavras armazenadas
    (*p_tree)->label++;

    return 1;
}

bool remove_controller(Node **p_tree, char *key) {
    if (*p_tree == NULL) return 0;

    int posit = 0;

    // Procura a chave e o remove
    if ((*p_tree)->label != 0)
        find_remove(p_tree, p_tree, key, &posit);

    return 1;
}

bool find_remove(Node **p_tree, Node** root, char *key, int* posit) {

    // Caso esteja na raiz
    if ((*root) == (*p_tree))
    {
        if (key[*posit] == '1')
        {
            // Verifico se o node a direita deve ser removido
            if (find_remove(p_tree, &(*root)->right, key, posit))
            {
                free((*root)->right);
                (*root)->right = NULL;

            }
        }
        else
        {
            // Verifico se o node a esquerda deve ser removido
            if (find_remove(p_tree, &(*root)->left, key,posit))
            {
                free((*root)->left);
                (*root)->left = NULL;
            }
        }

        // Diminuo o numero de chaves armazenadas
        (*p_tree)->label--;
    }
    else
    {
        int size = (int) strlen((*root)->prefix);
        int size_key = (int) strlen(key);

        // Verfica se este sera o node a ser removido
        for (int i = 0; i < size; i++)
        {
            // Chave a seja menor que a chave ja inserida
            if (*posit == size_key || key[*posit] != (*root)->prefix[i])
                return 0;
            (*posit)++;
        }

        // Encontrei a chave a ser removida
        if (*posit == size_key)
            return 1;
        else
        {
            if (key[*posit] == '1' && (*root)->right != NULL)
            {
                // Verifico a chave a direita
                if (find_remove(p_tree, &(*root)->right, key, posit))
                    remove_right(p_tree, root);
            }
            else
            {
                // Verifico a chave a esquerda
                if (find_remove(p_tree, &(*root)->left, key, posit))
                    remove_left(p_tree, root);
            }
        }
    }

    return 0;
}

void remove_right(Node **p_tree, Node **root) {
    // Remove o node a direita
    free((*root)->right);

    Node* node_aux = (*root)->left;
    int new_size = (int) (strlen((*root)->prefix) + strlen(node_aux->prefix));
    char* str_temp = (char*) malloc(new_size * sizeof(char));

    // prepara a nova string para o node atual
    strcpy(str_temp, (*root)->prefix);
    strcat(str_temp, node_aux->prefix);

    // Mantem a arvore estritamente binaria
    (*root)->right = node_aux->right;
    (*root)->left = node_aux;
    (*root)->prefix = str_temp;
}


void remove_left(Node **p_tree, Node **root) {
    // Remove o node a esquerda
    free((*root)->left);

    Node* node_aux = (*root)->right;
    int new_size = (int) (strlen((*root)->prefix) + strlen(node_aux->prefix));
    char* str_temp = (char*) malloc(new_size * sizeof(char));

    // prepara a nova string para o node atual
    strcpy(str_temp, (*root)->prefix);
    strcat(str_temp, node_aux->prefix);

    // Mantem a arvore estritamente binaria
    (*root)->right = node_aux;
    (*root)->prefix = str_temp;
}

bool find_controller(Node** p_tree, char* key)
{
    if (*p_tree == NULL || key == NULL) return 0;

    int posit = 0;
    return find(p_tree, p_tree, key, &posit);
}

bool find(Node** p_tree, Node** root, char* key, int* posit)
{
    // Caso seja diferente da raiz
    if (*p_tree != *root)
    {
        int size = (int) strlen((*root)->prefix);
        int size_key = (int) strlen(key);

        // Analisa este node da chave
        for (int i = 0; i < size; i++)
        {
            // Caso a chave seja invalida (menor ou diferente)
            if (size_key == *posit || key[*posit] != (*root)->prefix[i])
                return 0;
            (*posit)++;
        }

        // Chave valida
        if (*posit == size_key && (*root)->right == NULL && (*root)->left == NULL)
            return 1;
    }

    // Realiza a procura no node a direita
    if (key[0] == '1' && (*root)->right != NULL)
        return find(p_tree, &(*root)->right, key, posit);
        // Realiza a procura no node a esquerda
    else if (key[0] == '0' && (*root)->left != NULL)
        return find(p_tree, &(*root)->left, key, posit);

    return 0;
}