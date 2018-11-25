/**
*@file queue.c
*@author Carolina Estrella Machado
*@date 20 november 2018
*@brief implementacao das funcoes contidas no arquivo queue.h
*/

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
*@brief a funcao aloca um elemento na fila
*@param data
*@return ptr
*/

t_qelement* alloc_qelement(t_node* data){
	t_qelement* ptr = (t_qelement*)malloc(sizeof(t_qelement));
	ptr->data = data;
	ptr->next = NULL;

	return ptr;
}

/**
*@brief a funcao cria uma fila
*@param void
*@return ptr
*/

t_queue* create_queue(){
	t_queue* ptr = (t_queue*)malloc(sizeof(t_queue));
	ptr->first = NULL;
	ptr->last = NULL;

	return ptr;
}

/**
*@brief a funcao aloca um novo elemento na fila
*@param1 data @param2 queue
*@return ptr
*/

void toqueue(t_node* data, t_queue* queue){
	t_qelement* ptr = alloc_qelement(data);

	if(queue->first == NULL && queue->last == NULL)
		queue->first = ptr;

	else
		queue->last->next = ptr;

	queue->last = ptr;
}

/**
*@brief remove o primeiro elemento da fila
*@param queue
*@return ptr
*/

t_node* removefromqueue(t_queue* queue){
	if(emptyqueue(queue)){
		free(queue);
		exit(-1);
	}
	t_qelement* ptr = queue->first;
	t_node* result;
	result = ptr->data;
	if(queue->first == queue->last)
		queue->last = NULL;
	queue->first = queue->first->next;
	free(ptr);

	return result;
}

/**
*@brief verifica se a fila esta vazia
*@param queue
*@return bool
*/

int emptyqueue(t_queue* queue){
	return(queue->first == NULL && queue->last == NULL);
}
