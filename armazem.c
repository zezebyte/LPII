#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "queue.h"
#include "stack.h"
#include "linkedList.h"
#include "armazem.h"

void InitArm(ApArmazem armaz) {
	NewL(&(armaz->rolos));
	NewL(&(armaz->packs));
	NewL(&(armaz->expds));
	NewL(&(armaz->guias));
}

int ProcuraCodRolo(ApArmazem armaz, char* codigo) {
	int pos = 0, lim = SizeL(&(armaz->rolos));
	ApNo pNR = armaz->rolos.head;

	while(pos < lim && strcmp(pNR->elem.rolo.codigo, codigo)) {
		pNR = pNR->next;
		++pos;
	}
	if(pos == lim) return -1;
	return pos;
}

int ProcuraCodRoloPacks(ApArmazem armaz, char* codigo) {
	ApNo pNP = armaz->packs.head;

	while(!pNP) {
		if(SearchCodS(&(pNP->elem.pack.pilharolos), codigo)) return 1;
		pNP = pNP->next;
	}
	return 0;
}

int ProcuraCodRoloExpds(ApArmazem armaz, char* codigo) {
	ApNo tpack, texpd = armaz->guias.head;

	while(!texpd) {
		tpack = texpd->elem.guia.expds.head;
		while(!tpack) {
			if(SearchCodS(&(tpack->elem.pack.pilharolos), codigo)) return 1;
			tpack = tpack->next;
		}
		texpd = texpd->next;
	}
	return 0;
}

int ProcuraCodRoloGuias(ApArmazem armaz, char* codigo) {
	ApNo tpack, texpd, tguia = armaz->guias.head;

	while(!tguia) {
		if(tguia->elem.guia.open) {
			texpd = tguia->elem.guia.expds.head;
			while(!texpd) {
				tpack = texpd->elem.expd.packs.head;
				while(!tpack) {
					if(SearchCodS(&(tpack->elem.pack.pilharolos), codigo)) return 1;
					tpack = tpack->next;
				}
				texpd = texpd->next;
			}
		}
		tguia = tguia->next;
	}
	return 0;
}

int ProcuraCodPack(ApArmazem armaz, int codigo) {
	int pos = 0, lim = SizeL(&(armaz->packs));
	ApNo pNP = armaz->packs.head;

	while(pos < lim && pNP->elem.pack.codigo != codigo) {
		pNP = pNP->next;
		++pos;
	}
	if(pos == lim) return -1;
	return pos;
}

int ProcuraCodPackExpd(ApLista expd, int codigo) {
	int pos = 0, lim = SizeL(expd);
	ApNo pNP = expd->head;

	while(pos < lim && pNP->elem.pack.codigo != codigo) {
		pNP = pNP->next;
		++pos;
	}
	if(pos == lim) return -1;
	return pos;
}

int ProcuraCodPackExpds(ApArmazem armaz, int codigo) {
	ApNo texpd = armaz->expds.head;

	while(!texpd) {
		if(ProcuraCodPackExpd((ApLista) &(texpd->elem.expd), codigo) != -1) return 1;
		texpd = texpd->next;
	}
	return 0;
}

int ProcuraCodPackGuias(ApArmazem armaz, int codigo) {
	ApNo texpd, tguia = armaz->guias.head;

	while(!tguia) {
		if(tguia->elem.guia.open) {
			texpd = tguia->elem.guia.expds.head;
			while(!texpd) {
				if(ProcuraCodPackExpd((ApLista) &(texpd->elem.expd), codigo) != -1) return 1;
				texpd = texpd->next;
			}
		}
		tguia = tguia->next;
	}
	return 0;
}

void ReceberRolo(ApArmazem armaz, ApQueue Rolo) {
	ApNo aux;
	char str[STRG];

	if(FullQ(Rolo) == 0) {
		aux = malloc(sizeof(No));
		printf("Adicionar Rolo\n");
		printf("Introduza a descricao do produto: ");
		fgets(aux->elem.rolo.descr, sizeof(aux->elem.rolo.descr), stdin);
		aux->elem.rolo.descr[strlen(aux->elem.rolo.descr) - 1] = '\0';
		printf("Introduza a encomenda do produto: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &(aux->elem.rolo.enc));
		Enqueue(Rolo, aux);
		printf("Rolo introduzido com sucesso!\n");
	}else {
		printf("Buffer da seccao de acabamentos cheio!\n");
	}
}

void AdRoloArm(ApArmazem armaz, ApQueue ap_queue) {
	ApNo aux;
	float tmpf;
	int tmpi;
	char str[STRG];

	if(EmptyQ(ap_queue) == 0) {
		aux = Dequeue(ap_queue);
		printf("Descricao do rolo: %s ", aux->elem.rolo.descr);
		printf("Encomenda do rolo: %d ", aux->elem.rolo.enc);
		printf("Introduza o codigo do Rolo: ");
		fgets(str, sizeof(str), stdin);
		str[strlen(str) - 1] = '\0';
		if(strlen(str) < 11) {
			if(ProcuraCodRolo(armaz, str) == -1 && ProcuraCodigoRoloEmPacks(armaz, str) == 0 && ProcuraCodRoloGuias(armaz,str)==0) {
				strcpy(aux->elem.rolo.codigo, str);
				printf("Introduza o comprimento do rolo: ");
				fgets(str, sizeof(str), stdin);
				sscanf(str, "%f", &tmpf);
				if(tmpf > 0.0) {
					aux->elem.rolo.comp = tmpf;

					printf("Introduza a qualidade do rolo: ");
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d", &tmpi);
					aux->elem.rolo.qualid = tmpi;
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
	int ind;
	float aux;
	ApNo ApRolos;
	char str[STRG];

	if(EmptyL(&(armaz->rolos)) == 0) {
		printf("Alteracao de rolos\t\t*(valor actual)\n\n");
		printf("Introduza o codigo do rolo a alterar: ");
		fgets(str, sizeof(str), stdin);
		str[strlen(str) - 1] = '\0';
		if(strlen(str) < 11) {
			ind = ProcuraCodRolo(armaz, str);
			if(ind != -1) {
				ApRolos=SetPositionL(&(armaz->rolos),ind);
				printf("Introduza o comprimento do rolo: ");
				fgets(str, sizeof(str), stdin);
				sscanf(str, "%f", &aux);
				if(aux > 0.0) {
					ApRolos->elem.rolo.comp=aux;

					printf("Introduza a qualidade do rolo: ");
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d", &(ApRolos->elem.rolo.qualid));

					printf("Introduza a descricao do produto: ");
					fgets(ApRolos->elem.rolo.descr, sizeof(ApRolos->elem.rolo.descr), stdin);
					ApRolos->elem.rolo.descr[strlen(ApRolos->elem.rolo.descr)-1]='\0';
					printf("Introduza a encomenda do produto:");
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d", &(ApRolos->elem.rolo.enc));
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
	ApNo pNoLR = armaz->rolos.head;
	ApNo pNoLP = armaz->packs.head;

	if(!EmptyL(&(armaz->rolos))) {
		printf("Listar rolos do armazem:\n\n");
		for(i = 0; i < SizeL(&(armaz->rolos)); ++i) {
			printf("Rolo: %s\n"
				"Descricao: %s\n"
				"Comprimento: %f\n"
				"Qualidade: %d\n"
				"Emcomenda: %d\n", pNoLR->elem.rolo.codigo, pNoLR->elem.rolo.descr,
				pNoLR->elem.rolo.comp, pNoLR->elem.rolo.qualid, pNoLR->elem.rolo.enc);
			pNoLR = pNoLR->next;
		}
	}else {
		printf("Nao existem rolos no armazem.\n");
	}

	if(!EmptyL(&(armaz->packs))) {
		printf("Listar rolos empilhados\n");
		for(i = 0; i < SizeL(&(armaz->packs)); ++i) {
			if(!EmptyS(&(pNoLP->elem.pack.pilharolos))) {
				PrintStack(&(pNoLP->elem.pack.pilharolos));
			}
			pNoLP = pNoLP->next;
		}
	}else {
		printf("Nao existem rolos empilhados.\n");
	}
}

void CriarPack(ApArmazem armaz) {
	int aux, verif, day, month, year;
	char str[STRG], cd;
	ApNo tpack;
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	printf("Inserir Pack\n");
	printf("Insira o codigo do pack: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &aux);
	if(aux > 999999 && aux <= 9999999) {
		if(ProcuraCodPack(armaz, aux) == -1 && ProcuraCodPackExpds(armaz, aux) == -1 && ProcuraCodPackGuias(
			armaz, aux) == -1) {
			tpack = malloc(sizeof(No));

			printf("Data (A)utomatica ou (M)anual: ");
			fgets(str, sizeof(str), stdin);
			sscanf(str, "%c", &cd);
			cd = toupper(cd);
			switch(cd) {
			default:
				printf("Opcao invalida, a introduzir a data automaticamente\n");
				tpack->elem.pack.data.dia = str_t.wDay;
				tpack->elem.pack.data.mes = str_t.wMonth;
				tpack->elem.pack.data.ano = str_t.wYear;
				break;
			case 'A':
				tpack->elem.pack.data.dia = str_t.wDay;
				tpack->elem.pack.data.mes = str_t.wMonth;
				tpack->elem.pack.data.ano = str_t.wYear;
				break;
			case 'M':
				do {
					printf("Data do pacote [dd/mm/yyyy]: ");
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d%c%d%c%d", &day, &cd, &month, &cd, &year);
					verif = validDate(day, month, year);
					if(!verif) printf("Data invalida!\n");
				}while(!verif);

				tpack->elem.pack.data.dia = day;
				tpack->elem.pack.data.mes = month;
				tpack->elem.pack.data.ano = year;
			}
			NewS(&(tpack->elem.pack.pilharolos));
			tpack->elem.pack.open = 1;
			InsertL(&(armaz->packs), tpack, SizeL(&(armaz->packs)));
			printf("Pack Inserido com sucesso\n");
		}else {
			printf("Esse codigo ja foi atribuido a outro pack\n");
		}
	}else {
		printf("O codigo digitado e invalido\n");
	}
}
void AdicionarRoloPack(ApArmazem armaz) {
	ApNo auxtop, pNR, pNP;
	int codpack, pospack, posrolo;
	char codrolo[10], str[STRG];

	if(!EmptyL(&(armaz->rolos))) {
		if(!EmptyL(&(armaz->packs))) {
			printf("Empilhar rolo num pack\n");
			printf("Digite o codigo do pack: ");
			fgets(str, sizeof(str), stdin);
			sscanf(str, "%d", &codpack);
			if(codpack > 999999 && codpack <= 9999999) {
				pospack = (ProcuraCodPack(armaz, codpack));
				if(pospack != -1) {
					pNP = SetPositionL(&(armaz->packs), pospack);
					if(pNP->elem.pack.open == 1) {
						printf("Introduza o codigo do rolo que pretende adicionar: ");
						fgets(codrolo, sizeof(codrolo), stdin);
						codrolo[strlen(codrolo) - 1] = '\0';
						if(strlen(codrolo) < 11) {
							posrolo = ProcuraCodRolo(armaz, codrolo);
							if(posrolo != -1) {
								pNR = DeleteL(&(armaz->rolos), posrolo);
								if(EmptyS(&(pNP->elem.pack.pilharolos))) {
									Push(&(pNP->elem.pack.pilharolos), pNR);
									printf("Rolo empilhado no pack com sucesso!\n");
								}else {
									auxtop = TopS(&(pNP->elem.pack.pilharolos));
									if(pNR->elem.rolo.enc == auxtop->elem.rolo.enc) {
										if(pNR->elem.rolo.qualid == auxtop->elem.rolo.qualid) {
											Push(&(pNP->elem.pack.pilharolos), pNR);
											printf("Rolo empilhado no pack com sucesso!\n");
										}else {
											printf("O rolo nao tem a mesma qualidade!\n");
										}
									}else {
										printf("O rolo nao tem a mesma encomenda!\n");
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
		}else {
			printf("Nao ha packs criados!\n");
		}
	}else {
		printf("Nao ha rolos para empacotar!\n");
	}
}

void ListarPacks(ApArmazem armaz) {
	ApNo pNP = armaz->packs.head;

	if(!EmptyL(&(armaz->packs))) {
		printf("Listar Packs no armazem:\n\n");
		while(!pNP) {
			printf("Codigo do pack: %d", pNP->elem.pack.codigo);
			printf("Data de criacao: %d/%d/%d", pNP->elem.pack.data.dia, pNP->elem.pack.data.mes,
				pNP->elem.pack.data.ano);
			pNP = pNP->next;
		}
	}else {
		printf("Nao existem packs no armazem!\n");
	}
}

void ListarPacksExpd(ApLista expd) {
	ApNo pNE = expd->head;
	ApNo pNP = pNE->elem.expd.packs.head;


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
