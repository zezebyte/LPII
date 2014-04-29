#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "queue.h"
#include "stack.h"
#include "armazem.h"

void InitArm(ApArmazem armaz) {
	armaz->cont_packs = 0;
	armaz->cont_rolos = 0;
}

int ProcuraCodRolo(ApArmazem armaz, char* codigo) {
	int pos = 0;

	while(pos < armaz->cont_rolos && (strcmp(codigo, armaz->rolosarmazem[pos].codigo)) != 0)
		pos++;
	if(pos != armaz->cont_rolos)
		return pos;
	else return -1;
}

int ProcuraCodPack(ApArmazem armaz, int codigo) {
	int pos = 0;

	while(pos < armaz->cont_packs && codigo != armaz->packsarmazem[pos].codigo)
		++pos;
	if(pos != armaz->cont_packs)
		return pos;
	else return -1;
}
int ProcuraCodigoRoloEmPacks(ApArmazem armaz, char* codigo) {
	int i;

	for(i = 0; i < armaz->cont_packs; ++i) {
		if(SearchCodS(&(armaz->packsarmazem[i].pilharolos), codigo)) return 1;
	}
	return 0;
}

void ReceberRolo(ApArmazem armaz, pQueue Rolo) {
	ApNo aux;
	char str[STRG];

	if(FullQ(Rolo) == 0) {
		aux = malloc(sizeof(No));
		printf("Adicionar Rolo\n");
		printf("Introduza a descricao do produto: ");
		fgets(aux->elem.descr, sizeof(aux->elem.descr), stdin);
		aux->elem.descr[strlen(aux->elem.descr) - 1] = '\0';
		printf("Introduza a encomenda do produto: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &(aux->elem.enc));
		Enqueue(Rolo, aux);
		printf("Rolo introduzido com sucesso!\n");
	}else {
		printf("Buffer da seccao de acabamentos cheio!\n");
	}
}

void AdRoloArm(ApArmazem armaz, pQueue ap_queue) {
	ApNo aux;
	float tmpf;
	int tmpi;
	char str[STRG];

	if(EmptyQ(ap_queue) == 0) {
		aux = Dequeue(ap_queue);
		printf("Descricao do rolo: %s ", aux->elem.descr);
		printf("Encomenda do rolo: %d ", aux->elem.enc);
		printf("Introduza o codigo do Rolo: ");
		fgets(str, sizeof(str), stdin);
		str[strlen(str) - 1] = '\0';
		if(strlen(str) < 11) {
			if(ProcuraCodRolo(armaz, str) == -1 && ProcuraCodigoRoloEmPacks(armaz, str) == 0) {
				strcpy(aux->elem.codigo, str);
				printf("Introduza o comprimento do rolo: ");
				fgets(str, sizeof(str), stdin);
				sscanf(str, "%f", &tmpf);
				if(tmpf > 0.0) {
					aux->elem.comp = tmpf;

					printf("Introduza a qualidade do rolo: ");
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d", &tmpi);
					aux->elem.qualid = tmpi;

					armaz->rolosarmazem[armaz->cont_rolos] = aux->elem;
					++armaz->cont_rolos;
					free(aux);
					printf("Rolo adicionado ao armazem com sucesso\n");
				}else {
					Enqueue(ap_queue, aux);
					printf("Os rolos tem que ter o comprimento positivo!\n");
				}
			}else {
				Enqueue(ap_queue, aux);
				printf("Ja existe um rolo com esse codigo!\n");
			}
		}else {
			Enqueue(ap_queue, aux);
			printf("O codigo so pode ter ate 10 caracteres!\n");
		}
	}else {
		printf("Nao ha rolos para adicionar!\n");
	}
}

void RemoverRolo(ApArmazem armaz) {
	char cod[10];
	int pos, i;

	printf("Introduza o codigo do rolo que pretende remover: ");
	fgets(cod, sizeof(cod), stdin);
	cod[strlen(cod) - 1] = '\0';
	pos = ProcuraCodRolo(armaz, cod);
	if(pos != -1) {
		--armaz->cont_rolos;
		for(i = pos; i < armaz->cont_rolos; ++i) {
			armaz->rolosarmazem[i] = armaz->rolosarmazem[i + 1];
		}
		printf("Rolo apagado com sucesso!\n");
	}else {
		printf("Nao existe um rolo com esse codigo para apagar!\n");
	}
}

void AlterarRolos(ApArmazem armaz) {
	int ind, tmp;
	float aux;
	char str[STRG];

	if(armaz->cont_rolos != 0) {
		printf("Alteracao de rolos\t\t*(valor actual)\n\n");
		printf("Introduza o codigo do rolo a alterar: ");
		fgets(str, sizeof(str), stdin);
		str[strlen(str) - 1] = '\0';
		if(strlen(str) < 11) {
			ind = ProcuraCodRolo(armaz, str);
			if(ind != -1) {
				printf("Introduza o comprimento do rolo (%.2f): ", armaz->rolosarmazem[ind].comp);
				fgets(str, sizeof(str), stdin);
				sscanf(str, "%f", &aux);
				if(aux > 0.0) {
					armaz->rolosarmazem[ind].comp = aux;

					printf("Introduza a qualidade do rolo (%d): ", armaz->rolosarmazem[ind].qualid);
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d", &tmp);
					armaz->rolosarmazem[ind].qualid = tmp;

					printf("Introduza a descricao do produto (%s): ",
						armaz->rolosarmazem[ind].descr);
					fgets(str, sizeof(str), stdin);
					str[strlen(str) - 1] = '\0';
					strcpy(armaz->rolosarmazem[ind].descr, str);

					printf("Introduza a encomenda do produto (%d): ", armaz->rolosarmazem[ind].enc);
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d", &tmp);
					armaz->rolosarmazem[ind].enc = tmp;

					printf("Rolo editado com sucesso!\n");
				}else {
					printf("Os rolos tem de ter comprimento positivo!\n");
				}
			}else {
				printf("Nao existe um rolo com esse codigo!\n");
			}
		}else {
			printf("O codigo so pode ter ate 10 caracteres!\n");
		}
	}else {
		printf("Nao ha rolos para alterar!\n");
	}
}

void ListarRolos(ApArmazem armaz) {
	int i;

	if(armaz->cont_rolos != 0) {
		printf("Listar rolos no armazem\n\n");
		for(i = 0; i < armaz->cont_rolos; ++i) {
			printf("Rolo %s\n", armaz->rolosarmazem[i].codigo);
			printf("Descricao: %s\n", armaz->rolosarmazem[i].descr);
			printf("Comprimento: %.2f\n", armaz->rolosarmazem[i].comp);
			printf("Qualidade: %d\n", armaz->rolosarmazem[i].qualid);
			printf("Encomenda: %d\n\n", armaz->rolosarmazem[i].enc);
		}
	}else {
		printf("Nao existem rolos no armazem.\n");
	}

	if(armaz->cont_packs != 0) {
		printf("Listar rolos empilhados\n\n");
		for(i = 0; i < armaz->cont_packs; ++i) {
			if(SizeS(&(armaz->packsarmazem[i].pilharolos)) > 0) {
				PrintStack(&(armaz->packsarmazem[i].pilharolos));
			}
		}
	}else {
		printf("\nNao existem rolos empilhados.\n");
	}
}

void CriarPack(ApArmazem armaz) {
	int aux, verif, day, month, year;
	char str[STRG], cd;
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	printf("Inserir Pack\n");
	printf("Insira o codigo do pack: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &aux);
	if(aux > 999999 && aux <= 9999999) {
		if(ProcuraCodPack(armaz, aux) == -1) {
			armaz->packsarmazem[armaz->cont_packs].codigo = aux;

			printf("Data (A)utomatica ou (M)anual: ");
			fgets(str, sizeof(str), stdin);
			sscanf(str, "%c", &cd);
			cd = toupper(cd);
			switch(cd) {
			default:
				printf("Opcao invalida, a introduzir a data automaticamente\n");
				armaz->packsarmazem[armaz->cont_packs].data.dia = str_t.wDay;
				armaz->packsarmazem[armaz->cont_packs].data.mes = str_t.wMonth;
				armaz->packsarmazem[armaz->cont_packs].data.ano = str_t.wYear;
				break;
			case 'A':
				armaz->packsarmazem[armaz->cont_packs].data.dia = str_t.wDay;
				armaz->packsarmazem[armaz->cont_packs].data.mes = str_t.wMonth;
				armaz->packsarmazem[armaz->cont_packs].data.ano = str_t.wYear;
				break;
			case 'M':
				do {
					printf("Data do pacote [dd/mm/yyyy]: ");
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d%c%d%c%d", &day, &cd, &month, &cd, &year);
					verif = validDate(day, month, year);
					if(!verif) printf("Data invalida!\n");
				}while(!verif);

				armaz->packsarmazem[armaz->cont_packs].data.dia = day;
				armaz->packsarmazem[armaz->cont_packs].data.mes = month;
				armaz->packsarmazem[armaz->cont_packs].data.ano = year;
			}

			printf("Pack Inserido com sucesso\n");
			NewS(&armaz->packsarmazem[armaz->cont_packs].pilharolos);
			armaz->packsarmazem[armaz->cont_packs].open = 1;
			++armaz->cont_packs;

		}else {
			printf("Esse codigo ja foi atribuido a outro pack\n");
		}
	}else {
		printf("O codigo digitado e invalido\n");
	}
}
void AdicionarRoloPack(ApArmazem armaz) {
	ApNo aux, auxtop;
	int codpack, pospack, posrolo, i;
	char codrolo[10], str[STRG];

	printf("Empilhar rolo num pack\n");
	printf("Digite o codigo do pack: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &codpack);
	if(codpack > 999999 && codpack <= 9999999) {
		pospack = (ProcuraCodPack(armaz, codpack));
		if(pospack != -1) {
			if(armaz->packsarmazem[pospack].open == 1) {
				printf("Introduza o codigo do rolo que pretende adicionar: ");
				fgets(codrolo, sizeof(codrolo), stdin);
				codrolo[strlen(codrolo) - 1] = '\0';
				if(strlen(codrolo) < 11) {
					posrolo = ProcuraCodRolo(armaz, codrolo);
					if(posrolo != -1) {
						if(EmptyS(&(armaz->packsarmazem[pospack].pilharolos))) {
							aux = malloc(sizeof(No));
							aux->elem = armaz->rolosarmazem[posrolo];
							Push(&(armaz->packsarmazem[pospack].pilharolos), aux);
							--armaz->cont_rolos;
							for(i = posrolo; i < armaz->cont_rolos; ++i) {
								armaz->rolosarmazem[i] = armaz->rolosarmazem[i + 1];
							}
							printf("Rolo empilhado no pack com sucesso!\n");
						}else {
							auxtop = TopS(&(armaz->packsarmazem[pospack].pilharolos));
							if(armaz->rolosarmazem[posrolo].qualid == auxtop->elem.qualid && armaz->rolosarmazem[posrolo].enc == auxtop->elem.enc) {
								aux = malloc(sizeof(No));
								aux->elem = armaz->rolosarmazem[posrolo];
								Push(&(armaz->packsarmazem[pospack].pilharolos), aux);
								for(i = posrolo; i < armaz->cont_rolos - 1; ++i) {
									armaz->rolosarmazem[i] = armaz->rolosarmazem[i + 1];
								}
								printf("Rolo empilhado no pack com sucesso!\n");
							}else {
								printf("O rolo nao pode ser empilhado neste pack!\n");
							}
						}
					}else {
						printf("O rolo que pretende empilhar nao existe!\n");
					}
				}else {
					printf("O codigo enserido esta incorreto!\n");
				}
			}else {
				printf("Nao pode inserir mais rolos o pack ja esta fechado!\n");
			}
		}else {
			printf("Esse pack nao existe!\n");
		}
	}else {
		printf("O codigo inserido esta incorreto!\n");
	}
}

void ListarPacks(ApArmazem armaz) {
	int i;

	if(armaz->cont_packs != 0) {
		printf("Listar packs\n\n");

		for(i = 0; i < armaz->cont_packs; ++i) {
			printf("Pack %d\n", armaz->packsarmazem[i].codigo);
			printf("Data de Criacao: %d/%d/%d\n", armaz->packsarmazem[i].data.ano,
				armaz->packsarmazem[i].data.mes, armaz->packsarmazem[i].data.dia);
		}
	}else {
		printf("Nao existem packs para listar!\n");
	}
}

void RemoverPack(ApArmazem armaz) {
	int codpack, pospack, i;
	char str[STRG];
	ApNo apn;

	printf("Apagar um pack\n");
	printf("Digite o codigo do pack a remover: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &codpack);
	if(codpack > 999999 && codpack <= 9999999) {
		pospack = ProcuraCodPack(armaz, codpack);
		if(pospack != -1) {
			while(!EmptyS(&armaz->packsarmazem[pospack].pilharolos)) {
				apn = Pop(&(armaz->packsarmazem[pospack].pilharolos));
				armaz->rolosarmazem[armaz->cont_rolos] = apn->elem;
				++armaz->cont_rolos;
				free(apn);
			}
			--armaz->cont_packs;
			for(i = pospack; i < armaz->cont_packs; ++i) {
				armaz->packsarmazem[i] = armaz->packsarmazem[i + 1];
			}
			printf("Pack eliminado com sucesso!\n");
		}else {
			printf("Esse pack nao existe!\n");
		}
	}else {
		printf("O codigo enserido esta incorreto!\n");
	}
}

void FecharPack(ApArmazem armaz) {
	int codpack, pospack;
	char str[STRG];

	printf("Fechar um pack\n");
	printf("Digite o codigo do pack: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &codpack);
	if(codpack > 999999 && codpack <= 9999999) {
		pospack = ProcuraCodPack(armaz, codpack);
		if(pospack != -1) {
			if(armaz->packsarmazem[pospack].open == 1) {
				armaz->packsarmazem[pospack].open = 0;
				printf("Pack Fechado com sucesso!\n");
			}else {
				printf("O pack ja se encontra fechado!\n");
			}
		}else {
			printf("O pack nao existe!\n");
		}
	}else {
		printf("O codigo digitado nao esta correto!\n");
	}
}

int daysinmonth(int month, int year) {
	int days[] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	days[1] = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28;
	return days[month - 1];
}

int validDate(int day, int month, int year) {
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);
	if(year >= 2000 && year <= str_t.wYear && month >= 1 && month <= 12 && day >= 1 && day <= daysinmonth(
		month, year)) return 1;
	return 0;
}
