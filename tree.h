/**
*@file tree.h
*@author Carolina Estrella Machado
*@date 20 november 2018
*@brief assinaturas das funcoes que serao implementadas no arquivo tree.c
*/

#ifndef __TREE_H__
#define __TREE_H__
#include "doublylinkedlist.h"

/**
*@brief estrutura do tipo t_node
*/

typedef struct node{
	Ninja* ninja;
	struct node* left;
	struct node* right;
}t_node;

t_node* node_create();

t_node* tree_create();

int height(t_node* root);

t_node* cria(t_node* root);

void tree_free(t_node* tree);

int emptytree(t_node* node);

void tree_print_preorder(t_node* root);

#endif