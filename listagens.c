#include "listagens.h"
#include "linkedList.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ListarRoloCod(ApArmazem armaz) {
	char codrolo[80];
	int encontrou = 0;
	ApNo pNR = armaz->rolos.head;
	ApNo pNP = armaz->packs.head;
	ApNo pNE = armaz->expds.head;
	ApNo pNG = armaz->expds.head;

	printf("Introduza o codigo do rolo\n");
	fgets(codrolo, sizeof(codrolo), stdin);
	codrolo[strlen(codrolo)-1] = '\0';
	if(strlen(codrolo) < 11) {
		while(pNR && strcmp(pNR->elem.rolo.codigo, codrolo)) {       //procura o codigo na lista de rolos
			pNR = pNR->next;
		}
		if(pNR) {
			printf("O rolo encontra-se na lista de rolos\n\n");
			printf("Rolo %s\n", codrolo);
			printf("Conteudo do Rolo\n\n");
			printf("Descricao: %s\n", pNR->elem.rolo.descr);
			printf("Comprimento: %.2f\n", pNR->elem.rolo.comp);
			printf("Encomenda: %d\n\n", pNR->elem.rolo.qualid);

		}else {
			while(pNP && !encontrou) {
				pNR = pNP->elem.pack.pilharolos.top;       //primeiro no da stack
				while(pNR && !encontrou) {       //procura o codigo na lista de rolos
					if(strcmp(pNR->elem.rolo.codigo, codrolo)) {
						encontrou = 1; //se encontrou coloca a flag a 1, para sair
					}else {
						pNR = pNR->next;
					}
				}
				pNP = pNP->next;
			}
			if(pNR) {
				printf("O rolo encontra-se na lista de packs\n\n");
				printf("Rolo %s\n", codrolo);
				printf("Conteudo do Rolo\n\n");
				printf("Descricao: %s", pNR->elem.rolo.descr);
				printf("Comprimento: %.2f", pNR->elem.rolo.comp);
				printf("Encomenda: %d\n\n", pNR->elem.rolo.qualid);
			}else {
				while(pNE && !encontrou){ //lista de expedicoes
					pNP=pNE->elem.expd.packs.head;
					while(pNP && !encontrou){
						pNR=pNP->elem.pack.pilharolos.top;
						while(pNR && !encontrou) {
							if(strcmp(pNR->elem.rolo.codigo, codrolo)) {
								encontrou = 1;
							}else{
								pNR = pNR->next;
							}
						}
						pNP = pNP->next;
					}
					pNE = pNE->next;
				}
				if(pNR){
					printf("O rolo encontra-se na lista de expedicoes\n\n");
					printf("Rolo %s\n", codrolo);
					printf("Conteudo do Rolo\n\n");
					printf("Descricao: %s", pNR->elem.rolo.descr);
					printf("Comprimento: %.2f", pNR->elem.rolo.comp);
					printf("Encomenda: %d\n\n", pNR->elem.rolo.qualid);
				}else{
					while(pNG && !encontrou){
						if(pNG->elem.guia.open){
							pNE = pNG->elem.guia.expds.head;
							while(pNE && !encontrou){
								pNP = pNE->elem.expd.packs.head;
								while(pNP && !encontrou){
									pNR = pNP->elem.pack.pilharolos.top;
									while(pNR && !encontrou){
										if(strcmp(pNR->elem.rolo.codigo, codrolo)){
											encontrou = 1;
										}else{
											pNR = pNR->next;
										}
									}
									pNP = pNP->next;
								}
								pNE = pNE->next;
							}

						}
						pNG = pNG->next;
					}
					if(pNR){
						printf("O rolo encontra-se na lista de guias\n\n");
						printf("Rolo %s\n", codrolo);
						printf("Conteudo do Rolo\n\n");
						printf("Descricao: %s", pNR->elem.rolo.descr);
						printf("Comprimento: %.2f", pNR->elem.rolo.comp);
						printf("Encomenda: %d\n\n", pNR->elem.rolo.qualid);
					}else{
						printf("O rolo digitado nao existe\n");
					}
				}
			}
		}
	}else {
		printf("Codigo de Rolo invalido, tem mais de 10 caracteres\n");
	}
}

void ListarContPack(ApArmazem armaz){
	char str[80];
	int codpack;
	ApNo pNR;
	ApNo pNP = armaz->packs.head;

	printf("Introduza o codigo do Pack");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &codpack);
	if(codpack>999999 && codpack<=9999999){
		while(pNP && pNP->elem.pack.codigo != codpack) {
			pNP = pNP->next;
		}
		if(pNP){
			printf("Pack %d:\n", codpack);
			if(EmptyS(&(pNP->elem.pack.pilharolos))){
				printf("O pack esta vazio\n");
			}else{
				pNR = pNP->elem.pack.pilharolos.top;
				printf("Qualidade: %d\n", pNR->elem.rolo.qualid);
				printf("Encomenda: %d\n", pNR->elem.rolo.enc);
				while(pNP){
					printf("Rolo %s\n", pNR->elem.rolo.codigo);
					printf("Conteudo do Rolo\n\n");
					printf("Descricao: %s", pNR->elem.rolo.descr);
					printf("Comprimento: %.2f", pNR->elem.rolo.comp);
					printf("Encomenda: %d\n\n", pNR->elem.rolo.qualid);
				}
			}
		}
	}else{
		printf("Codigo do Pack incorreto\n");
	}
}
