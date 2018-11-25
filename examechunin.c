/**
*@file examechunin.c
*@author Carolina Estrella Machado
*@date 20 november 2018
*@brief implementacao das funcoes contidas no arquivo examechunin.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "examechunin.h"

#ifdef _WIN32
  #define CLEAR "cls"
#else
  #define CLEAR "clear"
#endif

/**
*@brief a funcao criaexame inicia uma arvore com altura 4 criando os nós e folhas
*@param root
*@return void
*/

void criaexame(t_node* root){ //inicializa arvore
	int h=0;
	while(h <= 4){
		cria(root);
		h = height(root);
	}
}

/**
*@brief a funcao escolhepersonagem imprime os ninjas colocados na lista duplamente encadeada para que o usuario possa escolher seu personagem
*@param list
*@return ptr->ninja
*/

Ninja* escolhepersonagem(t_list* list){
	system(CLEAR);
	int atributo, escolha , i=1, j;
	t_element* ptr = list->first;
	printf("Escolha de personagem\n");
	while(ptr != NULL){
		printf("Personagem %d:\n", i);
		atributo = rand()%4 + 1; //coloca um numero aleatorio para decidir atributo que sera mostrado

		if(atributo == 1){
			printf("Ninjutsu: %d ", ptr->ninja->ninjutsu);
		} else printf("Ninjutsu: ?? ");

		if(atributo == 2){
			printf("Genjutsu: %d ", ptr->ninja->genjutsu);
		} else printf("Genjutsu: ?? ");

		if(atributo == 3){
			printf("Taijutsu: %d ", ptr->ninja->taijutsu);
		} else printf("Taijutsu: ?? ");

		if(atributo == 4){
			printf("Defesa: %d\n", ptr->ninja->defesa);
		} else printf("Defesa: ??\n");

		printf("\n");
		ptr = ptr->next;
		i++;
	}

	printf("Escolha seu personagem:\n");
	scanf("%d", &escolha);

	while(escolha < 1 || escolha > 16){
		scanf("%d", &escolha);
	}

	ptr = list->first;
	for(j = 0; j < (escolha - 1); j++){ //encontra o personagem escolhido na lista
		ptr = ptr->next;
	}
	return ptr->ninja;
}

/**
*@brief a funcao inicializa o ultimo nivel da arvore com os 16 primeiros ninjas que foram colocados na lista duplamente encadeada
*@param1 root @param2 list
*@return void
*/

void inicializaarvorecomninjas(t_node* root, t_list* list){
	int level=0;
	t_queue* queue = create_queue();
	t_element* ptr = list->first;
	t_node* node;

	if(root == NULL)
		return;

	toqueue(root, queue); //enfileira

	while(!emptyqueue(queue)){
		node = removefromqueue(queue);

		if(node->left != NULL)
			toqueue(node->left, queue);
		if(node->right != NULL)
			toqueue(node->right, queue);
		if(level >= 15){ //se estiver no ultimo nivel da arvore coloca os primeiros personagens
			node->ninja = ptr->ninja;
			ptr = ptr->next;
		}

		level++;
	}
	free(queue);
}

/**
*@brief a funcao recebe o personagem e seu adversario na arvore para ver quem possui o maior valor do atributo escolhido
*@param1 ninja_one @param2 ninja_two @param3 attribute
*@return ptr
*/

Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute){
	double x = 1.0; 
	//se tiver supremacia elemental multiplica o atributo
	if(attribute > 4){
		x = 1.2;
		attribute -= 5;
	}
	else if(attribute < 1){
		x = 0.8;
		attribute += 5;
	}

	if(attribute == 1){
		if(ninja_one->ninjutsu * x >= ninja_two->ninjutsu)
			return ninja_one;
		else
			return ninja_two;
	}
	if(attribute == 2){
		if(ninja_one->genjutsu * x >= ninja_two->genjutsu)
			return ninja_one;
		else
			return ninja_two;
	}
	if(attribute == 3){
		if(ninja_one->taijutsu * x >= ninja_two->taijutsu)
			return ninja_one;
		else
			return ninja_two;
	}
	if(attribute == 4){
		if(ninja_one->defesa * x >= ninja_two->defesa)
			return ninja_one;
		else
			return ninja_two;
	}

	return NULL;
}

/**
*@brief a funcao imprime a batalhas que acabou de ocorrer
*@param1 atributo @param2 vencedor @param3 vitoria
*@return void
*/

void imprimebatalha(int atributo, Ninja* vencedor, Ninja* perdedor, int vitoria){
	double x = 1.0;
	//se tiver supremacia elemental multiplica o atributo
	if(atributo > 4){
		x = 1.2;
		atributo -= 5;
	}
	else if(atributo < 1){
		x = 0.8;
		atributo += 5;
	}
    //imprime resultado da batalha
	switch(atributo){
		case 1:
			if(vitoria){ //se o personagem for o vencedor, multiplica apenas seus atributos pelo valor x
				printf("%s (Ninjutsu %.0lf) x %s (Ninjutsu %d) ", vencedor->nome, vencedor->ninjutsu * x, perdedor->nome, perdedor->ninjutsu);
				if(x == 1.2)
					printf("[x1.2]");
				if(x == 0.8)
					printf("[x0.8]");
			}
			else if(vitoria == 0){ //se nao multiplica atributos do perdedor pelo valor x
				printf("%s (Ninjutsu %d) x %s (Ninjutsu %.0lf) ", vencedor->nome, vencedor->ninjutsu, perdedor->nome, perdedor->ninjutsu * x);
				if(x == 1.2)
					printf("[x1.2]");
				if(x == 0.8)
					printf("[x0.8]");
			}
			break;
		case 2:
			if(vitoria){
				printf("%s (Genjutsu %.0lf) x %s (Genjutsu %d) ", vencedor->nome, vencedor->genjutsu * x, perdedor->nome, perdedor->genjutsu);
				if(x == 1.2)
					printf("[x1.2]");
				if(x == 0.8)
					printf("[x0.8]");
			}
			else if(vitoria == 0){
				printf("%s (Genjutsu %d) x %s (Genjutsu %.0lf) ", vencedor->nome, vencedor->genjutsu, perdedor->nome, perdedor->genjutsu * x);
				if(x == 1.2)
					printf("[x1.2]");
				if(x == 0.8)
					printf("[x0.8]");
			}
			break;
		case 3:
			if(vitoria){
				printf("%s (Taijutsu %.0lf) x %s (Taijutsu %d) ", vencedor->nome, vencedor->taijutsu * x, perdedor->nome, perdedor->taijutsu);
				if(x == 1.2)
					printf("[x1.2]");
				if(x == 0.8)
					printf("[x0.8]");
			}
			else if(vitoria == 0){
				printf("%s (Taijutsu %d) x %s (Taijutsu %.0lf) ", vencedor->nome, vencedor->taijutsu, perdedor->nome, perdedor->taijutsu * x);
				if(x == 1.2)
					printf("[x1.2]");
				if(x == 0.8)
					printf("[x0.8]");
			}
			break;
		case 4:
			if(vitoria){
				printf("%s (Defesa %.0lf) x %s (Defesa %d) ", vencedor->nome, vencedor->defesa * x, perdedor->nome, perdedor->defesa);
				if(x == 1.2)
					printf("[x1.2]");
				if(x == 0.8)
					printf("[x0.8]");
			}
			else if(vitoria == 0){
				printf("%s (Defesa %d) x %s (Defesa %.0lf) ", vencedor->nome, vencedor->defesa, perdedor->nome, perdedor->defesa * x);
				if(x == 1.2)
					printf("[x1.2]");
				if(x == 0.8)
					printf("[x0.8]");
			}
			break;
	}
}

/**
*@brief a funcao imprime as batalhas que ocorreram na 1 etapa
*@param battles
*@return void
*/

void batalhas1etapa(batalhas* battles){
	printf("\nEXAME CHUNIN\n");
	printf("1a ETAPA:\n");
	double x = 1.0;
	int atr, i;
	for(i = 1; i <= 8; i++){
		atr = battles[i].atributo;
		if(atr > 4){
			x = 1.2;
			atr -= 5;
		}
		else if(atr < 1){
			x = 0.8;
			atr += 5;
		}
		if(atr == 1)
			printf("%s (Ninjutsu %.0lf) x %s (Ninjutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->ninjutsu * x, battles[i].ninja2->nome, battles[i].ninja2->ninjutsu);
		else if(atr == 2)
			printf("%s (Genjutsu %.0lf) x %s (Genjutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->genjutsu * x, battles[i].ninja2->nome, battles[i].ninja2->genjutsu);
		else if(atr == 3)
			printf("%s (Taijutsu %.0lf) x %s (Taijutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->taijutsu * x, battles[i].ninja2->nome, battles[i].ninja2->taijutsu);
		else if(atr == 4)
			printf("%s (Defesa %.0lf) x %s (Defesa %d)\n", battles[i].ninja1->nome, battles[i].ninja1->defesa * x, battles[i].ninja2->nome, battles[i].ninja2->defesa);
	}
}

/**
*@brief a funcao imprime as batalhas que ocorreram na 2 etapa
*@param battles
*@return void
*/

void batalhas2etapa(batalhas* battles){
	printf("\n2a ETAPA:\n");
	double x = 1.0;
	int atr, i;
	for(i = 9; i <= 12; i++){
		atr = battles[i].atributo;
		if(atr > 4){
			x = 1.2;
			atr -= 5;
		}
		else if(atr < 1){
			x = 0.8;
			atr += 5;
		}
		if(atr == 1)
			printf("%s (Ninjutsu %.0lf) x %s (Ninjutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->ninjutsu * x, battles[i].ninja2->nome, battles[i].ninja2->ninjutsu);
		else if(atr == 2)
			printf("%s (Genjutsu %.0lf) x %s (Genjutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->genjutsu * x, battles[i].ninja2->nome, battles[i].ninja2->genjutsu);
		else if(atr == 3)
			printf("%s (Taijutsu %.0lf) x %s (Taijutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->taijutsu * x, battles[i].ninja2->nome, battles[i].ninja2->taijutsu);
		else if(atr == 4)
			printf("%s (Defesa %.0lf) x %s (Defesa %d)\n", battles[i].ninja1->nome, battles[i].ninja1->defesa * x, battles[i].ninja2->nome, battles[i].ninja2->defesa);
	}
}

/**
*@brief a funcao imprime as batalhas que ocorreram na 3 etapa
*@param battles
*@return void
*/

void batalhas3etapa(batalhas* battles){
	printf("\n3a ETAPA:\n");
	double x = 1.0;
	int atr, i;
	for(i = 13; i <= 14; i++){
		atr = battles[i].atributo;
		if(atr > 4){
			x = 1.2;
			atr -= 5;
		}
		else if(atr < 1){
			x = 0.8;
			atr += 5;
		}
		if(atr == 1)
			printf("%s (Ninjutsu %.0lf) x %s (Ninjutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->ninjutsu * x, battles[i].ninja2->nome, battles[i].ninja2->ninjutsu);
		else if(atr == 2)
			printf("%s (Genjutsu %.0lf) x %s (Genjutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->genjutsu * x, battles[i].ninja2->nome, battles[i].ninja2->genjutsu);
		else if(atr == 3)
			printf("%s (Taijutsu %.0lf) x %s (Taijutsu %d)\n", battles[i].ninja1->nome, battles[i].ninja1->taijutsu * x, battles[i].ninja2->nome, battles[i].ninja2->taijutsu);
		else if(atr == 4)
			printf("%s (Defesa %.0lf) x %s (Defesa %d)\n", battles[i].ninja1->nome, battles[i].ninja1->defesa * x, battles[i].ninja2->nome, battles[i].ninja2->defesa);
	}
}

/**
*@brief a funcao imprime o resultado da batalha
*@param1 root @param2 list @param3 vencedor @param4 perdedor @param5 etapa @param6 derrotado @param7 atributo @param8 battles
*@return void
*/


void resultado(t_node* root, t_list* list, Ninja* vencedor, Ninja* perdedor, int etapa, int derrotado, int atributo, batalhas* battles){
	system(CLEAR);
	int escolha;
	printf("%da ETAPA: Resultado\n\n", etapa);

	if(derrotado == 0){
		printf("██╗   ██╗██╗████████╗ ██████╗ ██████╗ ██╗ █████╗\n");
        printf("██║   ██║██║╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗\n");
        printf("██║   ██║██║   ██║   ██║   ██║██████╔╝██║███████║\n");
        printf("╚██╗ ██╔╝██║   ██║   ██║   ██║██╔══██╗██║██╔══██║\n");
        printf(" ╚████╔╝ ██║   ██║   ╚██████╔╝██║  ██║██║██║  ██║\n");
        printf("  ╚═══╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝\n\n");

        imprimebatalha(atributo, vencedor, perdedor, 1);
        printf("\n%s ganhou a batalha\n", vencedor->nome);
	}

	else if(derrotado == 1){
		printf("██████╗ ███████╗██████╗ ██████╗  ██████╗ ████████╗ █████╗ \n");
        printf("██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗\n");
        printf("██║  ██║█████╗  ██████╔╝██████╔╝██║   ██║   ██║   ███████║\n");
        printf("██║  ██║██╔══╝  ██╔══██╗██╔══██╗██║   ██║   ██║   ██╔══██║\n");
        printf("██████╔╝███████╗██║  ██║██║  ██║╚██████╔╝   ██║   ██║  ██║\n");
        printf("╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝\n\n");

        imprimebatalha(atributo, vencedor, perdedor, 0);
        printf("\n%s ganhou a batalha\n", vencedor->nome);
	}


	if(derrotado == 1){ //se perder a batalha mostra duas opcoes do que fazer
		printf("\n[1] Voltar ao menu principal\n");
		printf("[2] Sair\n");

		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 2)
			scanf("%d", &escolha);

		if(escolha == 1){
			endlist(list);
			tree_free(root);	
			telainicial();
		}
		else if(escolha == 2){
			endlist(list);
			tree_free(root);	
			exit(0);
		}
	}

	if(derrotado == 0 && etapa == 4){ //se ganhou o exame mostra todas as batalhas dos niveis
		batalhas1etapa(battles);
		batalhas2etapa(battles);
		batalhas3etapa(battles);
		printf("\n4a ETAPA:\n");
		imprimebatalha(atributo, vencedor, perdedor, 1);
		printf("\n\n[1] Voltar ao menu principal\n");
		printf("[2] Sair\n");

		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 2)
			scanf("%d", &escolha);

		if(escolha == 1){
			endlist(list);
			tree_free(root);	
			telainicial();
		}
		else if(escolha == 2){
			endlist(list);
			tree_free(root);	
			exit(0);
		}
	}
}

/**
*@brief a funcao acha o personagem e seu adversario na arvore e chama a funcao fight, que vai retornar o ponteiro do vencedor. os demais personagens recebem atributos aleatorios e decidem o vencedor
*@param1 root @param2 list @param3 personagem @param4 adversario @param5 atributo @param6 etapa @param7 batalha @param8 battles
*@return void
*/

void achapai(t_node* root, t_list* list, Ninja* personagem, Ninja* adversario, int atributo, int etapa, int* batalha, batalhas* battles){
	if(root == NULL)
		return;

	if(root->left != NULL && root->right != NULL && root->left->ninja != NULL && root->right->ninja != NULL){
		if((root->left->ninja == personagem && root->right->ninja == adversario) || (root->right->ninja == personagem && root->left->ninja == adversario)){
			battles[++*batalha].atributo = atributo;
			battles[*batalha].ninja1 = personagem;
			battles[*batalha].ninja2 = adversario;

			Ninja* vencedor = fight(personagem, adversario, atributo);

			if(vencedor == personagem){
				resultado(root, list, vencedor, adversario, etapa, 0, atributo, battles);
			}
			else if(vencedor == adversario){
				resultado(root, list, vencedor, personagem, etapa, 1, atributo, battles);
			}
			root->ninja = vencedor;
		}
		else{ //outros ninjas da arvore que nao sejam personagem recebem atributos aleatorios
			int atr = rand()%4 + 1;
			battles[++*batalha].atributo = atr;
			battles[*batalha].ninja1 = root->left->ninja;
			battles[*batalha].ninja2 = root->right->ninja;

			root->ninja = fight(root->left->ninja, root->right->ninja, atr);
		}	
	}
	else{
		achapai(root->left, list, personagem, adversario, atributo, etapa, batalha, battles);
		achapai(root->right, list, personagem, adversario, atributo, etapa, batalha, battles);
	}
}

/**
*@brief a funcao verifica se raiz possui filhos ninja
*@param root 
*@return bool
*/

int filhos_ninja(t_node *root){

	return (root->left->ninja != NULL && root->right->ninja != NULL);
}

/**
*@brief a funcao procura o adversario do personagem na arvore de forma recursiva
*@param1 root @param2 personagem
*@return ptr
*/

Ninja* procuraadversario(t_node *root, Ninja *personagem){

	if(root == NULL)
		return NULL;

	if (filhos_ninja(root)){

		if(root->left->ninja == personagem)
			return root->right->ninja;
		else if(root->right->ninja == personagem)
			return root->left->ninja;
		else
			return NULL;
	}

	else{

		Ninja* esquerda = procuraadversario(root->left, personagem);
		Ninja* direita = procuraadversario(root->right, personagem);

		if(esquerda != NULL)
			return esquerda;
		else if(direita != NULL)
			return direita;
		else
			return NULL;
	}
}

/**
*@brief a funcao verifica se o personagem possui supremacia ou inferioridade elemental em relacao ao seu adversario
*@param1 personagem @param2 adversario 
*@return bool
*/

int supremaciaelemental(Ninja* personagem, Ninja* adversario){
	int flag = 0;

	if((strcmp(personagem->elemento, " Fogo") == 0 && strcmp(adversario->elemento, " Vento") == 0) || 
		(strcmp(personagem->elemento, " Vento") == 0 && strcmp(adversario->elemento, " Relampago") == 0) || 
		(strcmp(personagem->elemento, " Relampago") == 0 && strcmp(adversario->elemento, " Terra") == 0) || 
		(strcmp(personagem->elemento, " Terra") == 0 && strcmp(adversario->elemento, " Agua") == 0) || 
		(strcmp(personagem->elemento, " Agua") == 0 && strcmp(adversario->elemento, " Fogo") == 0)){
		flag = 1; //se supremacia elemental
    }
	else if((strcmp(adversario->elemento, " Fogo") == 0 && strcmp(personagem->elemento, " Vento") == 0) || 
		(strcmp(adversario->elemento, " Vento") == 0 && strcmp(personagem->elemento, " Relampago") == 0) || 
		(strcmp(adversario->elemento, " Relampago") == 0 && strcmp(personagem->elemento, " Terra") == 0) || 
		(strcmp(adversario->elemento, " Terra") == 0 && strcmp(personagem->elemento, " Agua") == 0) || 
		(strcmp(adversario->elemento, " Agua") == 0 && strcmp(personagem->elemento, " Fogo") == 0)){
		flag = -1; //se inferioridade elemental
	}

	return flag;
}

/**
*@brief a funcao imprime personagem escolhido, seus atributos e seu adversario
*@param1 root, @param2 personagem @param3 adversario @param4 etapa @param5 atributo @param6 flag 
*@return void
*/

void displaypersonagem(t_node* raiz, Ninja* personagem, Ninja* adversario, int etapa, int atributo, int* flag){
	system(CLEAR);
	double x = 1.0;

	printf("%da ETAPA\n\n", etapa);
	printf("Seu personagem: %s\n", personagem->nome);
	if(supremaciaelemental(personagem, adversario) == 1){ //se tem supremacia elemental multiplica atributos por 1.2
		printf("SUPREMACIA ELEMENTAL: %s > %s\n", personagem->elemento, adversario->elemento);
		printf("Todos os atributos foram multiplicados por x1.2\n\n");
		x = 1.2;
        *flag = 1;
	} 
	else if(supremaciaelemental(personagem, adversario) == -1){ //se tem inferioridade elemental multiplica atributos por 0.8
		printf("INFERIORIDADE ELEMENTAL: %s < %s\n", personagem->elemento, adversario->elemento);
		printf("Todos os atributos foram multiplicados por x0.8\n\n");
		x = 0.8;
        *flag = -1;
	}
	
	if(atributo == 1){
		printf("X) XX: XX\n");
	} else printf("1) Ninjutsu: %.0lf\n", personagem->ninjutsu * x);
	if(atributo == 2){
		printf("X) XX: XX\n");
	} else printf("2) Genjutsu: %.0lf\n", personagem->genjutsu * x);
	if(atributo == 3){
		printf("X) XX: XX\n");
	} else printf("3) Taijutsu: %.0lf\n", personagem->taijutsu * x);
	if(atributo == 4){
		printf("X) XX: XX\n\n");
	} else printf("4) Defesa: %.0lf\n\n", personagem->defesa * x);

	printf("Seu adversario: %s\n\n", adversario->nome);
}

/**
*@brief a funcao le o atributo escolhido pelo usuario
*@param void
*@return atributo
*/

int escolheatributo(){
	int atributo;
	printf("Selecione um atributo: ");
	scanf("%d", &atributo);

	while(atributo < 1 || atributo > 4)
		scanf("%d", &atributo);

	return atributo;
}

void continua(){
	setbuf(stdin, NULL);
	printf("\nPressione qualquer tecla para prosseguir\n");
	getchar();
}

/**
*@brief a funcao inicia o exame chunin chamando todas as funcoes necessarias 
*@param void
*@return void
*/

void iniciaexame(){
	int i, flag=0, derrotado = 0, batalha = 0;
	srand(time(0));
	t_node* root = NULL;
	root = tree_create();
	criaexame(root);
	t_list* list = randomlist();
	inicializaarvorecomninjas(root, list);
	tree_print_preorder(root);
	Ninja* personagem = escolhepersonagem(list);
	Ninja* adversario = NULL;
	batalhas battles[17];
	for(i=0; i < 4; i++){
		int atributo;
		adversario = procuraadversario(root, personagem);
		if(i==0){
			displaypersonagem(root, personagem, adversario, i+1, 0, &flag); //manda o endereco de flag para saber se tem supremacia ou inferioridade elemental
			atributo = escolheatributo(); //salva em uma variavel o atributo escolhido para na proxima etapa omitir ultimo atributo escolhido
			//se flag for 1, soma 5 no atributo para saber na funcao fight se tem supremacia elemental
			if(flag == 1)
				atributo += 5;
			//se flag for 1, subtrai 5 no atributo para saber na funcao fight se tem inferioridade elemental
			else if(flag == -1)
				atributo -= 5;
			achapai(root, list, personagem, adversario, atributo, i+1, &batalha, battles);
			continua();
			if(flag == 1)
				atributo -= 5;
			else if(flag == -1)
				atributo +=5;
		}
		else{
			displaypersonagem(root, personagem, adversario, i+1, atributo, &flag);
			atributo = escolheatributo();
			//se flag for 1, soma 5 no atributo para saber na funcao fight se tem supremacia elemental
			if(flag == 1)
				atributo += 5;
			//se flag for 1, subtrai 5 no atributo para saber na funcao fight se tem inferioridade elemental
			else if(flag == -1)
				atributo -= 5;
			achapai(root, list, personagem, adversario, atributo, i+1, &batalha, battles);
			continua();
			if(flag == 1)
				atributo -= 5;
			else if(flag == -1)
				atributo +=5;
		}
		flag=0;
	}

	endlist(list);
	tree_free(root);	
}
