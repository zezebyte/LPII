#include <stdio.h>
#include <stdlib.h>

#include "uteis.h"
#include "armazem.h"
#include "queue.h"
#include "stack.h"

void MenuPacks(ApArmazem armaz) {
	int op;
	char str[STRG];

	do {
		op = -1; 				//reset da opcao
		limparEcra();
		printf("Menu Packs\n"
			"\n"
			"Escolha por favor uma das seguintes opcoes:\n"
			"1-Criar Pack\n"
			"2-Empilhar Rolos num Pack\n"
			"3-Anular Packs\n"
			"4-Listar Packs\n"
			"5-Fechar Pack\n"
			"0-Voltar ao menu anterior\n"
			"Opcao: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &op);
		limparEcra();
		switch(op) {
		case 1:
			CriarPack(armaz);
			break;
		case 2:
			AdicionarRoloPack(armaz);
			break;
		case 3:
			RemoverPack(armaz);
			break;
		case 4:
			ListarPacks(armaz);
			break;
		case 5:
			FecharPack(armaz);
			break;
		case 0:
			printf("Voltar ao menu anterior\n");
			break;
		default:
			printf("Erro! Opcao Invalida!\n");
		}
		Prima();
	}while(op != 0);
}
void MenuRolos(ApArmazem armaz, ApQueue filaEspera) {
	int op;
	char str[STRG];

	do {
		op = -1; 				//reset da opcao
		limparEcra();
		printf("Menu Rolos\n"
			"\n"
			"Escolha por favor uma das seguintes opcoes:\n"
			"1-Passar rolo para o Armazem\n"
			"2-Remover Rolo do Armazem\n"
			"3-Alterar informacao de rolo\n"
			"4-Listar Rolos no Armazem\n"
			"0-Voltar ao menu anterior\n"
			"Opcao: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &op);
		limparEcra();
		switch(op) {
		case 1:
			AdRoloArm(armaz, filaEspera);
			break;
		case 2:
			RemoverRolo(armaz);
			break;
		case 3:
			AlterarRolos(armaz);
			break;
		case 4:
			ListarRolos(armaz);
			break;
		case 0:
			printf("Voltar ao menu anterior\n");
			break;
		default:
			printf("Erro! Opcao Invalida!\n");
		}
		Prima();
	}while(op != 0);
}
void Menu(ApArmazem armaz, ApQueue filaEspera) {
	int op;
	char str[STRG];

	do {
		op = -1; 				//reset da opcao
		limparEcra();
		printf("Programa de Gestao de Empresa de Tecidos\n"
			"\n"
			"Escolha por favor uma das seguintes opcoes:\n"
			"1-Receber Rolos\n"
			"2-Operacoes com Rolos\n"
			"3-Operacoes com Packs\n"
			"0-Sair\n"
			"Opcao: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &op);
		limparEcra();
		switch(op) {
		case 1:
			ReceberRolo(armaz, filaEspera);
			break;
		case 2:
			MenuRolos(armaz, filaEspera);
			break;
		case 3:
			MenuPacks(armaz);
			break;
		case 0:
			printf("A sair do programa.");
			sleep(500);
			printf(".");
			sleep(500);
			printf(".");
			sleep(500);
			Prima();
			break;
		default:
			printf("Erro! Opcao Invalida!\n");
			Prima();
		}
	}while(op != 0);
}

int main(int argc, char** argv) {
	Armazem armazem;
	ApArmazem armaz = &armazem;
	Queue rolos;
	ApQueue ap_rolos = &rolos;

	InitArm(armaz);
	NewQ(ap_rolos);

	Menu(armaz, ap_rolos);
	return EXIT_SUCCESS;
}
