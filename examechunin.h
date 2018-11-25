/**
*@file examechunin.h
*@author Carolina Estrella Machado
*@date 20 november 2018
*@brief assinaturas das funcoes que serao implementadas no arquivo examechunin.c
*/

#ifndef __EXAMECHUNIN_H__
#define __EXAMECHUNIN_H__
#include "queue.h"

typedef struct{
	int atributo;
	Ninja* ninja1;
	Ninja* ninja2;
}batalhas;

void telainicial();

void criaexame(t_node* root);

Ninja* escolhepersonagem(t_list* list);

void inicializaarvorecomninjas(t_node* root, t_list* list);

Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute);

void resultado(t_node* root, t_list* list, Ninja* vencedor, Ninja* perdedor, int etapa, int derrotado, int atributo, batalhas* battles);

void derrota(int etapa, batalhas* battles);

void achapai(t_node* root, t_list* list, Ninja* personagem, Ninja* adversario, int atributo, int etapa, int* batalha, batalhas* battles);

int filhos_ninja(t_node *root);

Ninja* procuraadversario(t_node *root, Ninja *personagem);

int supremaciaelemental(Ninja* personagem, Ninja* adversario);

void displaypersonagem(t_node* raiz, Ninja* personagem, Ninja* adversario, int etapa, int atributo, int* flag);

int escolheatributo();

void continua();

void iniciaexame();


#endif