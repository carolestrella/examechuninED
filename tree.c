/**
*@file tree.c
*@author Carolina Estrella Machado
*@date 20 november 2018
*@brief implementacao das funcoes contidas no arquivo tree.h
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

/**
*@brief aloca memoria para um novo no na arvore
*@param void
*@return ptr
*/

t_node* node_create(){
	t_node* ptr = (t_node*)malloc(sizeof(t_node));
	ptr->ninja = NULL;
	ptr->left = NULL;
	ptr->right = NULL;

	return ptr;
}

/**
*@brief cria uma nova raiz na arvore
*@param void
*@return root
*/

t_node* tree_create(){
	t_node* root = node_create();

	return root;
}

/**
*@brief vrifica altura da arvore
*@param root
*@return altura
*/

int height(t_node* root){
	int right, left;
	if(root == NULL)
		return 0;
	else{
		left = height(root->left);
		right = height(root->right);
		if(right > left)
			return right+1;
		else
			return left+1;
	}
}

/**
*@brief pecorre na arvore recursivamente criando nos que ainda nao foram criados
*@param root
*@return root
*/

t_node* cria(t_node* root){
	if(root == NULL)
		return node_create();
	else{
		root->left = cria(root->left);
		root->right = cria(root->right);
	}

	return root;
}

/**
*@brief libera memoria alocado para arvore
*@param tree
*@return void
*/

void tree_free(t_node* tree){
	if(!emptytree(tree)){
		tree_free(tree->left);
		tree_free(tree->right);
		free(tree);
	}
}

/**
*@brief verifica se a arvore esta vazia
*@param node
*@return bool
*/

int emptytree(t_node* node){
	return node == NULL;
}

/**
*@brief imprime os nos que contem ninjas de forma recursiva
*@param root
*@return void
*/

void tree_print_preorder(t_node* root){
	if(root == NULL)
		return;
	else{
		if(root->ninja != NULL)
			printf("%s\n", root->ninja->nome);
		tree_print_preorder(root->left);
		tree_print_preorder(root->right);
	}
	
}
