#include <stdio.h>
#include <stdlib.h>

#include "armazem.h"
#include "uteis.h"
#include "ficheiros.h"
#include "queue.h"
#include "stack.h"
#include "listagens.h"

void menuconsultas(ApArmazem armaz) {
	int op;
	char str[STRG];

	do {
		op = -1;
		limparEcra();
		printf("Menu de operacoes em packs\n\n"
			"  1 - Listar Rolos por codigo\n"
			"  2 - Listar Conteudo de um Pack\n"
			"  3 - Metragem de uma Expedicao\n"
			"  4 - Quantidade de Rolos e Packs dentro de uma Guia\n"
			"  0 - Voltar para o menu anterior\n"
			"Opcao: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &op);
		limparEcra();
		switch(op) {
		case 1:
			ListarRoloCod(armaz);
			break;
		case 2:
			ListarContPack(armaz);
			break;
		case 3:
			MetragemExpd(armaz);
			break;
		case 4:
			QuantRolosPacksGuia(armaz);
			break;
		case 0:
			printf("Voltar ao menu anterior...");
			break;
		default:
			printf("Erro! Opcao invalida\n");
		}
		Prima();
	}while(op != 0);
}

void menurolos(ApArmazem armaz, ApQueue filaEspera) {
	int op;
	ApNo aux;
	char str[STRG];

	do {
		aux = filaEspera->head;
		op = -1;
		limparEcra();
		printf("Menu de operacoes em rolos\n");
		if(!aux) {
			printf("Nao existem rolos na fila de espera\n");
		}else {
			printf("|");
			while(aux) {
				printf("%s|", aux->elem.rolo.descr);
				aux = aux->next;
			}
			printf("\n");
		}
		printf("  1 - Adicionar rolo ao armazem\n"
			"  2 - Remover rolo do armazem\n"
			"  3 - Alterar informacao de rolo\n"
			"  4 - Listar os rolos no armazem\n"
			"  0 - Voltar para o menu anterior\n"
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
			printf("Voltar ao menu anterior...");
			break;
		default:
			printf("Erro! Opcao invalida\n");
		}
		Prima();
	}while(op != 0);
}

void menupacks(ApArmazem armaz) {
	int op;
	char str[STRG];

	do {
		op = -1;
		limparEcra();
		printf("Menu de operacoes em packs\n\n"
			"  1 - Criar pack\n"
			"  2 - Empilhar rolos num pack\n"
			"  3 - Anular pack\n"
			"  4 - Listar packs\n"
			"  5 - Fechar pack\n"
			"  0 - Voltar para o menu anterior\n"
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
			printf("Voltar ao menu anterior...");
			break;
		default:
			printf("Erro! Opcao invalida\n");
		}
		Prima();
	}while(op != 0);
}

void menuexpds(ApArmazem armaz) {
	int op;
	char str[STRG];

	do {
		op = -1;
		limparEcra();
		printf("Menu de operacoes em expedicoes\n\n"
			"  1 - Criar expedicao\n"
			"  2 - Associar packs a uma expedicao\n"
			"  3 - Remover pack de uma expedicao\n"
			"  4 - Listar expedicoes\n"
			"  5 - Anular expedicao\n"
			"  6 - Fechar expedicao\n"
			"  0 - Voltar para o menu anterior\n"
			"Opcao: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &op);
		limparEcra();
		switch(op) {
		case 1:
			CriarExpedicao(armaz);
			break;
		case 2:
			AdicionarPackExpd(armaz);
			break;
		case 3:
			RemoverPackExpds(armaz);
			break;
		case 4:
			ListarExpedicoes(armaz);
			break;
		case 5:
			RemoverExpedicao(armaz);
			break;
		case 6:
			FecharExpedicao(armaz);
			break;
		case 0:
			printf("Voltar ao menu anterior...");
			break;
		default:
			printf("Erro! Opcao invalida\n");
		}
		Prima();
	}while(op != 0);
}

void menuguias(ApArmazem armaz) {
	int op;
	char str[STRG];

	do {
		op = -1;
		limparEcra();
		printf("Menu de operacoes em guias\n\n"
			"  1 - Criar guia\n"
			"  2 - Associar expedicoes a guia de remessa\n"
			"  3 - Anular guia de remessa\n"
			"  4 - Listar guias de remessa\n"
			"  5 - Finalizar guia de remessa\n"
			"  0 - Voltar para o menu anterior\n"
			"Opcao: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &op);
		limparEcra();
		switch(op) {
		case 1:
			CriarGuia(armaz);
			break;
		case 2:
			AdicionarExpdGuia(armaz);
			break;
		case 3:
			RemoverGuia(armaz);
			break;
		case 4:
			ListarGuias(armaz);
			break;
		case 5:
			FecharGuia(armaz);
			break;
		case 0:
			printf("Voltar ao menu anterior...");
			break;
		default:
			printf("Erro! Opcao invalida\n");
		}
		Prima();
	}while(op != 0);
}

void menu(ApArmazem armaz, ApQueue filaEspera) {
	int op;
	char str[STRG];

	do {
		op = -1;
		limparEcra();
		printf("Programa de Gestao de Empresa de Tecidos\n\n"
			"  1 - Chegada de rolo ao armazem\n"
			"  2 - Operacoes em rolos\n"
			"  3 - Operacoes em packs\n"
			"  4 - Operacoes em expds\n"
			"  5 - Operacoes em guias\n"
			"  6 - Consultas de armazem\n"
			"  7 - Gravar base de dados\n"
			"  8 - Carregar base de dados\n"
			"  9 - CLEAR TEST\n"
			"  0 - Sair do programa\n"
			"Opcao: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &op);
		limparEcra();
		switch(op) {
		case 1:
			ReceberRolo(armaz, filaEspera);
			Prima();
			break;
		case 2:
			menurolos(armaz, filaEspera);
			break;
		case 3:
			menupacks(armaz);
			break;
		case 4:
			menuexpds(armaz);
			break;
		case 5:
			menuguias(armaz);
			break;
		case 6:
			menuconsultas(armaz);
			break;
		case 7:
			GravarArmaz(armaz, filaEspera);
			Prima();
			break;
		case 8:
			LerArmaz(armaz, filaEspera);
			Prima();
			break;
		case 9:
			Limpa(armaz, filaEspera);
			printf("Armazem reiniciado.\n");
			Prima();
			break;
		case 0:
			limparEcra();
			printf("A sair do programa.");
			sleep(500);
			printf(".");
			sleep(500);
			printf(".");
			sleep(500);
			break;
		default:
			printf("Erro! Opcao invalida\n");
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

	menu(armaz, ap_rolos);
	return EXIT_SUCCESS;
}
