/**
 * patriciaTree.c
 * 
 * Create on: 12/05/2018
 *    Author: Rafael da Costa Silva 
 */

#include "patriciaTree.h"

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