#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "examechunin.h"

#ifdef _WIN32
  #define CLEAR "cls"
#else
  #define CLEAR "clear"
#endif

void telainicial(){
	int op, flag = 1;

	while(flag){
		system(CLEAR);
		printf("\n");
	    printf("███████╗██╗  ██╗ █████╗ ███╗   ███╗███████╗     ██████╗██╗  ██╗██╗   ██╗███╗   ██╗██╗███╗   ██╗\n");
	    printf("██╔════╝╚██╗██╔╝██╔══██╗████╗ ████║██╔════╝    ██╔════╝██║  ██║██║   ██║████╗  ██║██║████╗  ██║\n");
	    printf("█████╗   ╚███╔╝ ███████║██╔████╔██║█████╗      ██║     ███████║██║   ██║██╔██╗ ██║██║██╔██╗ ██║\n");
	    printf("██╔══╝   ██╔██╗ ██╔══██║██║╚██╔╝██║██╔══╝      ██║     ██╔══██║██║   ██║██║╚██╗██║██║██║╚██╗██║\n");
	    printf("███████╗██╔╝ ██╗██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╗██║  ██║╚██████╔╝██║ ╚████║██║██║ ╚████║\n");
	    printf("╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝╚═╝  ╚═══╝\n");
	    printf("\n[1] Iniciar Exame\n");
	    printf("[2] Sair\n");
	    printf("Escolha uma opcao: ");
	    scanf("%d", &op);
	    switch(op){
	    	case 1:
	    		iniciaexame();
	    		break;
	    	case 2:
	    		flag = 0;
	    		break;
	    }
	}
}

int main(){
	telainicial();
	return 0;
}