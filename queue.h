/**
*@file queue.h
*@author Carolina Estrella Machado
*@date 20 november 2018
*@brief assinaturas das funcoes que serao implementadas no arquivo queue.c
*/

#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "tree.h"

/**
*@brief estrutura do tipo t_qelement
*/

typedef struct qelement{
	t_node* data;
	struct qelement* next;
} t_qelement;

/**
*@brief estrutura do tipo t_queue
*/

typedef struct queue{
	t_qelement* first;
	t_qelement* last;
}t_queue;

t_qelement* alloc_qelement(t_node* data);

t_queue* create_queue();

void toqueue(t_node* data, t_queue* queue);

t_node* removefromqueue(t_queue* queue);

int emptyqueue(t_queue* queue);

#endif