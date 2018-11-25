/**
*@file doublylinkedlist.h
*@author Carolina Estrella Machado
*@date 20 november 2018
*@brief assinaturas das funcoes que serao implementadas no arquivo doublylinkedlist.c
*/

#ifndef __DOUBLYLINKEDLIST_H__
#define __DOUBLYLINKEDLIST_H__

/**
*@brief estrutura do tipo ninja
*/

typedef struct{
	char* nome;
	char* elemento;
	int ninjutsu;
	int genjutsu;
	int taijutsu;
	int defesa;
} Ninja;

/**
*@brief estrutura do tipo t_element
*/

typedef struct element{
	Ninja* ninja;
	struct element* prev;
	struct element* next;
}t_element;

/**
*@brief estrutura do tipo t_list
*/

typedef struct list{
	t_element* first;
	t_element* last;
}t_list;

t_list* createlist();

Ninja* ninja_create(char* _nome, char* _elemento, int _ninjutsu, int _genjutsu, int _taijutsu, int _defesa);

t_element* alloc_element(char* nome, char* elemento, int ninjutsu, int genjutsu, int taijutsu, int defesa);

int emptylist(t_list* list);

void insert(char* nome, char* elemento, int ninjutsu, int genjutsu, int taijutsu, int defesa, t_list* list);

void endlist(t_list* list);

void ninja_free(Ninja* ninja);

t_list* randomlist();

#endif