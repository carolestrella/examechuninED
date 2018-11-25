/**
*@file doublylinkedlist.c
*@author Carolina Estrella Machado
*@date 20 november 2018
*@brief implementacao das funcoes contidas no arquivo doublylinkedlist.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublylinkedlist.h"

/**
*@brief a funcao cria um ponteiro para o primeiro e ultimo da lista
*@param void
*@return ptr
*/


t_list* createlist(){
	t_list* ptr = (t_list*)malloc(sizeof(t_list));
	ptr->first = NULL;
	ptr->last = NULL;

	return ptr;
}

/**
*@brief a funcao cria um ninja e copia para o ponteiro todas as caracteristicas recebidas
*@param1 _nome @param2 _elemento @param3 _ninjutsu @param4 _genjutsu @param5 _taijutsu @param6 _defesa
*@return ptr
*/

Ninja* ninja_create(char* _nome, char* _elemento, int _ninjutsu, int _genjutsu, int _taijutsu, int _defesa){
	Ninja* ptr = (Ninja*)malloc(sizeof(Ninja));
	ptr->nome = (char*) malloc(sizeof(char)*strlen(_nome)+1);
	ptr->elemento = (char*) malloc(sizeof(char)*strlen(_elemento)+1);
	strcpy(ptr->nome, _nome);
	strcpy(ptr->elemento, _elemento);
	ptr->ninjutsu = _ninjutsu;
	ptr->genjutsu = _genjutsu;
	ptr->taijutsu = _taijutsu;
	ptr->defesa = _defesa;

	return ptr;
}

/**
*@brief a funcao cria um elemento que sera inserido na lista que contem tambem um ponteiro para ninja
*@param1 _nome @param2 _elemento @param3 _ninjutsu @param4 _genjutsu @param5 _taijutsu @param6 _defesa
*@return ptr
*/

t_element* alloc_element(char* nome, char* elemento, int ninjutsu, int genjutsu, int taijutsu, int defesa){
	t_element* ptr = (t_element*)malloc(sizeof(t_element));
	ptr->ninja = ninja_create(nome, elemento, ninjutsu, genjutsu, taijutsu, defesa);
	ptr->prev = NULL;
	ptr->next = NULL;

	return ptr;
}

/**
*@brief a funcao verifica se a lista esta vazia
*@param list
*@return bool
*/

int emptylist(t_list* list){
	return list->first == NULL;
}

/**
*@brief a funcao insere na lista um novo elemento
*@param1 _nome @param2 _elemento @param3 _ninjutsu @param4 _genjutsu @param5 _taijutsu @param6 _defesa @param7 list
*@return void
*/

void insert(char* nome, char* elemento, int ninjutsu, int genjutsu, int taijutsu, int defesa, t_list* list){
	t_element* element = alloc_element(nome, elemento, ninjutsu, genjutsu, taijutsu, defesa);
	if(emptylist(list)){
		list->first = element;
	}
	else{
		list->last->next = element;
		element->prev = list->last;
	}
	list->last = element;
}

/**
*@brief a funcao libera a memoria alocada para a lista
*@param list
*@return void
*/

void endlist(t_list* list){
	t_element* element;
	while(list->first != NULL){
		element = list->first;
		list->first = element->next;
		ninja_free(element->ninja);
		free(element);
	}
	free(list);
}

/**
*@brief a funcao libera memoria alocada para o ponteiro do tipo ninja
*@param ninja
*@return void
*/

void ninja_free(Ninja* ninja){
	free(ninja->nome);
	free(ninja->elemento);
	free(ninja);
}

/**
*@brief a funcao cria uma lista aleatoria a partir do arquivo ninjas.txt e insere na lista duplamente encadeada
*@param void
*@return list
*/

t_list* randomlist(){
	char nome[25], elemento[15];
	int ninj, genj, taij, def, i, j=0, num, flag;
	int randomnumbers[16];
	FILE* ninjas = fopen("ninjas.txt", "r");
	t_list* list = createlist();
	if(ninjas == NULL){
		printf("Arquivo inexistente!\n");
	}
	while(j < 16){
		num = rand()%32 + 1;
		for(i=0; i < 16; i++){
			if(randomnumbers[i] == num)
				flag = 1;
		}
		if(flag != 1){
			randomnumbers[j] = num;
			j++;
		}
		flag = 0;
	}
	j=0;
	while(j < 16){
		for(i=0; i < randomnumbers[j]; i++){
			fscanf(ninjas, "%[^,]s", nome);
			fgetc(ninjas);
			fscanf(ninjas, "%[^,]s", elemento);
			fgetc(ninjas);
			fscanf(ninjas, "%d, %d, %d, %d", &ninj, &genj, &taij, &def);
			fgetc(ninjas);
		}
		insert(nome, elemento, ninj, genj, taij, def, list);
		rewind(ninjas);
		j++;
	}
	fclose(ninjas);

	return list;
}
