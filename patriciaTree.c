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
        int size = strlen((*root)->prefix);
        int size_key = strlen(key);

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
    int size_key = strlen(key);

    // Aloca o node que recebera o restante da chave a ser inserida
    Node* new = (Node*) malloc(sizeof(Node));
    new->prefix = (char*) calloc(size_key - (*posit), sizeof(char));
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
        char* str_parent = (char*) calloc(posit_root-1, sizeof(char));
        int size = strlen((*root)->prefix);
        int cont;

        // Aloca o node que recebera o restante da chave do node atual
        Node* sister = (Node*) malloc(sizeof(Node));
        sister->left = sister->right = NULL;
        sister->prefix = (char*) calloc(size - posit_root, sizeof(char));

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

/**
bool insert(Node** root, char* key)
{
    // Verifica se a raiz é nula
    if (!(*root))
    {
        Node* new = (Node*) calloc(1,sizeof(Node));
        new->prefix = (char*) malloc(strlen(key)* sizeof(char));
        strcpy(new->prefix, key);
        new->label = 0;
        new->left = new->right = NULL;
        (*root) = new;
    }
    else
    {
        int i = (*root)->label, cont_p = 0;
        // Encontra a posicao de intercecao das chaves
        for (cont_p = 0; i < strlen((*root)->prefix); cont_p++)
        {
            if (key[i] == '\0' || key[i] != (*root)->prefix[cont_p])
                break;
            i++;
        }

        // Caso a chave a ser inserida seja menor
        if (i <= strlen((*root)->prefix))
        {
            // Caso a mesma seja invalida
            if (key[i] == '\0')
            {
                printf("error 01!\n\t Chave invalida: Uma chave nao pode estar contida dentro de outra.");
                return 0;
            }
                // Adiciona um novo node e ajusta a arvore para receber a nova chave
            else
            {
                Node* temp;
                char* char_temp = (char*) calloc(strlen((*root)->prefix)-cont_p, sizeof(char));
                int cont;

                Node* parent = (Node*) malloc(sizeof(Node));
                parent->prefix = (char*) calloc(cont_p, sizeof(char));

                Node* sister = (Node*) malloc(sizeof(Node));
                sister->prefix = (char*) calloc(strlen(key)-i, sizeof(char));

                strncpy(parent->prefix, (*root)->prefix, cont_p);
                parent->label = (*root)->label;

                cont = 0;
                for (int j = i; j < strlen(key); j++)
                {
                    sister->prefix[cont] = key[j];
                    cont++;
                }
                cont = 0;
                for (int j = cont_p; j < strlen((*root)->prefix); j++)
                {
                    char_temp[cont] = (*root)->prefix[j];
                    cont++;
                }

                strcpy((*root)->prefix, char_temp);
                (*root)->label = sister->label = i;

                temp = (*root);
                (*root) = parent;
                parent->left = temp;
                parent->right = sister;
            }
        }
            // Caso possuam o mesmo tamanho
        else
        {
            // Verifica se as chaves são iguais ou menor
            if (key[i] == '\0')
            {
                printf("error 01!\n\t Chave invalida: Uma chave nao pode estar contida dentro de outra.");
                return 0;
            }

                // Caso a insercao seja a esquerda
            if ((*root)->left && (*root)->left->prefix[0] == key[i])
            {
                insert(&(*root)->left, key);
            }
                // Caso a insercao seja a direita
            else if ((*root)->right && (*root)->right->prefix[0] == key[i])
            {
                insert(&(*root)->right, key);
            }
            else
            {
                // Verifica se os dois filhor são diferentes de null
                if (!(*root)->left && (*root)->right)
                {
                    printf("error 03!\n\t Chave invalida: Chavo com alfabeto invalido.");
                    return 0;
                }

                int cont;
                Node* new = (Node*) malloc(sizeof(Node));
                new->prefix = (char*) calloc(strlen(key)-i, sizeof(char));
                new->label = i;

                cont = 0;
                for (int j = i; j < strlen(key); ++j) {
                    new->prefix[cont] = key[j];
                    cont++;
                }

                (*root)->left = new;
            }
        }

    }
    return 1;
}
*/