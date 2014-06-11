#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include "queue.h"
#include "stack.h"
#include "linkedList.h"
#include "armazem.h"

void InitArm(ApArmazem armaz) {
	NewL(&(armaz->rolos));
	NewL(&(armaz->packs));
	NewL(&(armaz->expds));
	NewL((ApLista) &(armaz->guias));
	armaz->guias.proxguia = 1;
}

int ProcuraCodRolo(ApArmazem armaz, char* codigo) {
	int pos = 0;
	ApNo pNR = armaz->rolos.head;

	while(pNR && strcmp(pNR->elem.rolo.codigo, codigo)) {
		pNR = pNR->next;
		++pos;
	}
	if(!pNR) return -1;
	return pos;
}

int ProcuraCodRoloPacks(ApArmazem armaz, char* codigo) {
	ApNo pNP = armaz->packs.head;

	while(pNP) {
		if(SearchCodS(&(pNP->elem.pack.pilharolos), codigo)) return 1;
		pNP = pNP->next;
	}
	return 0;
}

int ProcuraCodRoloExpds(ApArmazem armaz, char* codigo) {
	ApNo tpack, texpd = armaz->guias.head;

	while(texpd) {
		tpack = texpd->elem.guia.expds.head;
		while(tpack) {
			if(SearchCodS(&(tpack->elem.pack.pilharolos), codigo)) return 1;
			tpack = tpack->next;
		}
		texpd = texpd->next;
	}
	return 0;
}

int ProcuraCodRoloGuias(ApArmazem armaz, char* codigo) {
	ApNo tpack, texpd, tguia = armaz->guias.head;

	while(tguia) {
		if(tguia->elem.guia.open) {
			texpd = tguia->elem.guia.expds.head;
			while(texpd) {
				tpack = texpd->elem.expd.packs.head;
				while(tpack) {
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
	int pos = 0;
	ApNo pNP = armaz->packs.head;

	while(pNP && pNP->elem.pack.codigo != codigo) {
		pNP = pNP->next;
		++pos;
	}
	if(!pNP) return -1;
	return pos;
}

int ProcuraCodPackExpd(ApLista packs, int codigo) {
	int pos = 0;
	ApNo pNP = packs->head;

	while(pNP && pNP->elem.pack.codigo != codigo) {
		pNP = pNP->next;
		++pos;
	}
	if(!pNP) return -1;
	return pos;
}

int ProcuraCodPackExpds(ApArmazem armaz, int codigo) {
	ApNo texpd = armaz->expds.head;

	while(texpd) {
		if(ProcuraCodPackExpd(&(texpd->elem.expd.packs), codigo) != -1) return 1;
		texpd = texpd->next;
	}
	return 0;
}

int ProcuraCodPackGuias(ApArmazem armaz, int codigo) {
	ApNo texpd, tguia = armaz->guias.head;

	while(tguia) {
		if(tguia->elem.guia.open) {
			texpd = tguia->elem.guia.expds.head;
			while(texpd) {
				if(ProcuraCodPackExpd(&(texpd->elem.expd.packs), codigo) != -1) return 1;
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
		printf("Descricao do rolo: %s\n", aux->elem.rolo.descr);
		printf("Encomenda do rolo: %d\n", aux->elem.rolo.enc);
		printf("Introduza o codigo do Rolo: ");
		fgets(str, sizeof(str), stdin);
		str[strlen(str) - 1] = '\0';
		if(strlen(str) < 11) {
			if(ProcuraCodRolo(armaz, str) == -1 && ProcuraCodRoloPacks(armaz, str) == 0 && ProcuraCodRoloExpds(
				armaz, str) == 0 && ProcuraCodRoloGuias(armaz, str) == 0) {
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
					InsertL(&(armaz->rolos), aux, SizeL(&(armaz->rolos)));
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
	char cod[STRG];
	int pos;

	if(EmptyL(&(armaz->rolos)) == 0) {
		printf("Introduza o codigo do rolo que pretende remover: ");
		fgets(cod, sizeof(cod), stdin);
		cod[strlen(cod) - 1] = '\0';
		if(strlen(cod) < 11) {
			pos = ProcuraCodRolo(armaz, cod);
			if(pos != -1) {
				free(DeleteL(&(armaz->rolos), pos));
				printf("Rolo apagado com sucesso!\n");
			}else {
				printf("Nao existe um rolo com esse codigo para apagar!\n");
			}
		}else {
			printf("O codigo nao pode ter mais de 10 caracteres!\n");
		}
	}else {
		printf("Nao existem rolos para remover!\n");
	}
}

void AlterarRolos(ApArmazem armaz) {
	int ind;
	float aux;
	ApNo ApRolos;
	char str[STRG];

	if(EmptyL(&(armaz->rolos)) == 0) {
		printf("Alteracao de rolos    *(valor actual)\n\n");
		printf("Introduza o codigo do rolo a alterar: ");
		fgets(str, sizeof(str), stdin);
		str[strlen(str) - 1] = '\0';
		if(strlen(str) < 11) {
			ind = ProcuraCodRolo(armaz, str);
			if(ind != -1) {
				ApRolos = SetPositionL(&(armaz->rolos), ind);
				printf("Introduza o comprimento do rolo (%.2f): ", ApRolos->elem.rolo.comp);
				fgets(str, sizeof(str), stdin);
				sscanf(str, "%f", &aux);
				if(aux > 0.0) {
					ApRolos->elem.rolo.comp = aux;

					printf("Introduza a qualidade do rolo (%d): ", ApRolos->elem.rolo.qualid);
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d", &(ApRolos->elem.rolo.qualid));

					printf("Introduza a descricao do produto (%s): ", ApRolos->elem.rolo.descr);
					fgets(ApRolos->elem.rolo.descr, sizeof(ApRolos->elem.rolo.descr), stdin);
					ApRolos->elem.rolo.descr[strlen(ApRolos->elem.rolo.descr) - 1] = '\0';

					printf("Introduza a encomenda do produto (%d): ", ApRolos->elem.rolo.enc);
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
	int flag = 0;
	ApNo pNoLR = armaz->rolos.head;
	ApNo pNoLP = armaz->packs.head;
	ApNo pNoLE = armaz->expds.head;
	ApNo pNoLG = armaz->guias.head;

	printf("Listar rolos no armazem:\n\n");
	if(pNoLR) {
		flag = 1;
		while(pNoLR) {
			printf("Rolo %s\n"
				"  Descricao: %s\n"
				"  Comprimento: %.2f\n"
				"  Qualidade: %d\n"
				"  Emcomenda: %d\n\n", pNoLR->elem.rolo.codigo, pNoLR->elem.rolo.descr,
				pNoLR->elem.rolo.comp, pNoLR->elem.rolo.qualid, pNoLR->elem.rolo.enc);
			pNoLR = pNoLR->next;
		}
	}

	while(pNoLP) {
		if(!EmptyS(&(pNoLP->elem.pack.pilharolos))) {
			flag = 1;
			printf("Pack %d:\n", pNoLP->elem.pack.codigo);
			PrintStack(&(pNoLP->elem.pack.pilharolos), 0);
		}
		pNoLP = pNoLP->next;
	}

	while(pNoLE) {
		pNoLP = pNoLE->elem.expd.packs.head;
		while(pNoLP) {
			if(!EmptyS(&(pNoLP->elem.pack.pilharolos))) {
				flag = 1;
				printf("Expedicao %d:\n", pNoLE->elem.expd.enc);
				printf("  Pack %d:\n", pNoLP->elem.pack.codigo);
				PrintStack(&(pNoLP->elem.pack.pilharolos), 1);
			}
			pNoLP = pNoLP->next;
		}
		pNoLE = pNoLE->next;
	}

	while(pNoLG) {
		if(pNoLG->elem.guia.open) {
			pNoLE = pNoLG->elem.guia.expds.head;
			while(pNoLE) {
				pNoLP = pNoLE->elem.expd.packs.head;
				while(pNoLP) {
					if(!EmptyS(&(pNoLP->elem.pack.pilharolos))) {
						flag = 1;
						printf("Guia %d:\n", pNoLG->elem.guia.num);
						printf("  Expedicao %d:\n", pNoLE->elem.expd.enc);
						printf("    Pack %d:\n", pNoLP->elem.pack.codigo);
						PrintStack(&(pNoLP->elem.pack.pilharolos), 2);
					}
					pNoLP = pNoLP->next;
				}
				pNoLE = pNoLE->next;
			}
		}
		pNoLG = pNoLG->next;
	}

	if(!flag) printf("Nao existem rolos para listar.\n");
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
		if(ProcuraCodPack(armaz, aux) == -1 && ProcuraCodPackExpds(armaz, aux) == 0 && ProcuraCodPackGuias(
			armaz, aux) == 0) {
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
			tpack->elem.pack.codigo = aux;
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
								pNR = SetPositionL(&(armaz->rolos), posrolo);
								if(EmptyS(&(pNP->elem.pack.pilharolos))) {
									pNR = DeleteL(&(armaz->rolos), posrolo);
									Push(&(pNP->elem.pack.pilharolos), pNR);
									printf("Rolo empilhado no pack com sucesso!\n");
								}else {
									auxtop = TopS(&(pNP->elem.pack.pilharolos));
									if(pNR->elem.rolo.enc == auxtop->elem.rolo.enc) {
										if(pNR->elem.rolo.qualid == auxtop->elem.rolo.qualid) {
											pNR = DeleteL(&(armaz->rolos), posrolo);
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
	ApNo pNE = armaz->expds.head;
	ApNo pNG = armaz->guias.head;
	int flag = 0;

	printf("Listar packs no armazem:\n\n");
	if(pNP) {
		flag = 1;
		while(pNP) {
			printf("Pack: %d\n", pNP->elem.pack.codigo);
			printf("  Data de criacao: %d/%d/%d\n", pNP->elem.pack.data.dia,
				pNP->elem.pack.data.mes, pNP->elem.pack.data.ano);
			printf("  Contem %d rolos\n\n", SizeS(&(pNP->elem.pack.pilharolos)));
			pNP = pNP->next;
		}
	}

	while(pNE) {
		pNP = pNE->elem.expd.packs.head;
		if(pNP) {
			flag = 1;
			printf("Expedicao %d:", pNE->elem.expd.enc);
			while(pNP) {
				printf("  Pack: %d\n", pNP->elem.pack.codigo);
				printf("    Data de criacao: %d/%d/%d\n", pNP->elem.pack.data.dia,
					pNP->elem.pack.data.mes, pNP->elem.pack.data.ano);
				printf("    Contem %d rolos\n\n", SizeS(&(pNP->elem.pack.pilharolos)));
				pNP = pNP->next;
			}
		}
		pNE = pNE->next;
	}

	while(pNG) {
		if(pNG->elem.guia.open) {
			pNE = pNG->elem.guia.expds.head;
			while(pNE) {
				pNP = pNE->elem.expd.packs.head;
				if(pNP) {
					flag = 1;
					printf("Guia %d", pNG->elem.guia.num);
					printf("  Expedicao %d: \n", pNE->elem.expd.enc);
					while(pNP) {
						printf("    Pack: %d\n", pNP->elem.pack.codigo);
						printf("      Data de criacao: %d/%d/%d\n", pNP->elem.pack.data.dia,
							pNP->elem.pack.data.mes, pNP->elem.pack.data.ano);
						printf("      Contem %d rolos\n\n", SizeS(&(pNP->elem.pack.pilharolos)));
						pNP = pNP->next;
					}
				}
				pNE = pNE->next;
			}
		}
		pNG = pNG->next;
	}

	if(!flag) printf("Nao existem packs para listar.\n");
}

void RemoverPack(ApArmazem armaz) {
	int codpack, pospack;
	char str[STRG];
	ApNo ApNoLP;

	if(EmptyL(&(armaz->packs)) == 0) {
		printf("Apagar um pack\n");
		printf("Digite o codigo do pack a remover: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &codpack);
		if(codpack > 999999 && codpack <= 9999999) {
			pospack = ProcuraCodPack(armaz, codpack);
			if(pospack != -1) {
				ApNoLP = DeleteL(&(armaz->packs), pospack);
				while(EmptyS(&(ApNoLP->elem.pack.pilharolos)) != 0) {
					InsertL(&(armaz->rolos), Pop(&(ApNoLP->elem.pack.pilharolos)),
						SizeL(&(armaz->packs)));
				}
				free(ApNoLP);
				printf("Pack eliminado com sucesso!\n");
			}else {
				printf("Esse pack nao existe!\n");
			}
		}else {
			printf("O codigo inserido esta incorreto!\n");
		}
	}else {
		printf("Nao existem pack para remover!\n");
	}
}

void FecharPack(ApArmazem armaz) {
	int codpack, pospack;
	char str[STRG];
	ApNo pNP;

	if(!EmptyL(&(armaz->packs))) {
		printf("Fechar um pack\n");
		printf("Digite o codigo do pack: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &codpack);
		if(codpack > 999999 && codpack <= 9999999) {
			pospack = ProcuraCodPack(armaz, codpack);
			if(pospack != -1) {
				pNP = SetPositionL(&(armaz->packs), pospack);
				if(!EmptyS(&(pNP->elem.pack.pilharolos))) {
					if(pNP->elem.pack.open == 1) {
						pNP->elem.pack.open = 0;
						printf("Pack Fechado com sucesso.\n");
					}else {
						printf("O pack ja se encontra fechado!\n");
					}
				}else {
					printf("O pack nao tem rolos empilhados, nao pode ser fechado.\n");
				}
			}else {
				printf("O pack nao existe!\n");
			}
		}else {
			printf("O codigo digitado nao esta correto!\n");
		}
	}else {
		printf("Nao ha packs para fechar.\n");
	}
}

int ProcuraEncomenda(ApArmazem armaz, int enc) {
	int pos = 0;
	ApNo pNE = armaz->expds.head;

	while(pNE && enc != pNE->elem.expd.enc) {
		++pos;
		pNE = pNE->next;
	}
	if(pNE) {
		return pos;
	}else {
		return -1;
	}
}

int ProcuraEncomendaGuias(ApArmazem armaz, int enc) {
	ApNo pNG = armaz->guias.head, pNE;

	while(pNG) {
		pNE = pNG->elem.guia.expds.head;
		while(pNE) {
			if(enc == pNE->elem.expd.enc) return 1;
			pNE = pNE->next;
		}
		pNG = pNG->next;
	}
	return 0;
}

void CriarExpedicao(ApArmazem armaz) {
	int enc;
	ApNo pNE;
	char str[80];

	printf("Criar expedicao\n");
	printf("Digite o nro da encomenda: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &enc);
	if(enc > 0) {
		if(ProcuraEncomenda(armaz, enc) == -1 && ProcuraEncomendaGuias(armaz, enc) == 0) {
			pNE = malloc(sizeof(No));
			pNE->elem.expd.enc = enc;
			pNE->elem.expd.open = 1;
			NewL(&(pNE->elem.expd.packs));
			InsertL(&(armaz->expds), pNE, SizeL(&(armaz->expds)));
			printf("Expedicao criada com sucesso.\n");
		}else {
			printf("Ja existe uma expedicao para essa encomenda!\n");
		}
	}else {
		printf("Encomenda invalida, tem que ser num nro positivo!\n");
	}
}

void AdicionarPackExpd(ApArmazem armaz) {
	int enc, posexpd, pospack, codpack;
	ApNo pExpd, pPack;
	char str[80];

	if(!EmptyL(&(armaz->packs))) {
		if(!EmptyL(&(armaz->expds))) {
			printf("Empilhar pack numa expedicao\n");
			printf("A que encomenda se destina o pack: ");
			fgets(str, sizeof(str), stdin);
			sscanf(str, "%d", &enc);
			if(enc > 0) {
				posexpd = ProcuraEncomenda(armaz, enc);
				if(posexpd != -1) {
					pExpd = SetPositionL(&(armaz->expds), posexpd);
					if(pExpd->elem.expd.open) {
						printf("Pack a empilhar: ");
						fgets(str, sizeof(str), stdin);
						sscanf(str, "%d", &codpack);
						if(codpack > 999999 && codpack <= 9999999) {
							pospack = ProcuraCodPack(armaz, codpack);
							pPack = SetPositionL(&(armaz->packs), pospack);
							if(!pPack->elem.pack.open) {
								if(pExpd->elem.expd.enc == (TopS(&(pPack->elem.pack.pilharolos))->elem.rolo.enc)) {
									InsertL(&(pExpd->elem.expd.packs),
										DeleteL(&(armaz->packs), pospack),
										SizeL(&(pExpd->elem.expd.packs)));
									printf("Pack inserido com sucesso!\n");
								}else {
									printf("O pack nao tem a mesma encomenda que a expedicao!\n");
								}
							}else {
								printf("O pack ainda nao esta fechado!\n");
							}
						}else {
							printf("O codigo do pacote e invalido!\n");
						}
					}else {
						printf("A expedicao esta fechada.\n");
					}
				}else {
					printf("Nao existe uma expedicao com essa encomenda.\n");
				}
			}else {
				printf("Encomenda invalida, tem que ser num nro maior que 0.\n");
			}
		}else {
			printf("Nao ha expedicoes criadas!\n");
		}
	}else {
		printf("Nao ha packs para inserir em expedicoes!\n");
	}
}

void RemoverPackExpds(ApArmazem armaz) {
	int encomenda, posexpd, codpack, pospack;
	ApNo ApExp;
	char str[STRG];

	if(!EmptyL(&(armaz->expds))) {
		printf("Remover pack da expedicao:\n");
		printf("Remover de que encomenda: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &encomenda);
		if(encomenda > 0) {
			posexpd = ProcuraEncomenda(armaz, encomenda);
			if(posexpd != -1) {
				ApExp = SetPositionL(&(armaz->expds), posexpd);
				if(!EmptyL(&(ApExp->elem.expd.packs))) {
					printf("Codigo do pack a remover: ");
					fgets(str, sizeof(str), stdin);
					sscanf(str, "%d", &codpack);
					if(codpack > 999999 && codpack <= 9999999) {
						pospack = ProcuraCodPackExpd(&(ApExp->elem.expd.packs), codpack);
						if(pospack != -1) {
							InsertL(&(armaz->packs), DeleteL(&(ApExp->elem.expd.packs), pospack),
								SizeL(&(armaz->packs)));
							printf("Pack removido com sucesso\n");
						}else {
							printf("Esse pack nao existe\n");
						}
					}else {
						printf("Codigo do pack Incorrecto!\n");
					}
				}else {
					printf("Nao foram inseridos pack nesta expedicao.\n");
				}
			}else {
				printf("Essa encomenda nao existe.\n");
			}
		}else {
			printf("Encomenda digitada nao esta correta.\n");
		}
	}else {
		printf("Nao existem expedicoes de onde remover.\n");
	}
}

void ListarExpedicoes(ApArmazem armaz) {
	ApNo pExpd = armaz->expds.head;
	ApNo pGuia = armaz->guias.head;
	int flag = 0;

	printf("A listar expedicoes no armazem:\n\n");
	if(pExpd) {
		flag = 1;
		while(pExpd) {
			printf("Expedicao para encomenda %d\n", pExpd->elem.expd.enc);
			printf("  Contem %d packs\n\n", SizeL(&(pExpd->elem.expd.packs)));
			pExpd = pExpd->next;
		}
	}

	if(pGuia) {
		while(pGuia) {
			pExpd = pGuia->elem.guia.expds.head;
			if(pExpd) {
				flag = 1;
				printf("Guia %d:\n", pGuia->elem.guia.num);
				while(pExpd) {
					printf("  Expedicao para encomenda %d\n", pExpd->elem.expd.enc);
					printf("    Contem %d packs\n\n", SizeL(&(pExpd->elem.expd.packs)));
					pExpd = pExpd->next;
				}
			}
			pGuia = pGuia->next;
		}
	}
	if(!flag) printf("Nao existem expedicoes para listar.\n");
}

void RemoverExpedicao(ApArmazem armaz) {
	int codenc, posenc;
	char str[STRG];
	ApNo pNE;

	if(!EmptyL(&(armaz->expds))) {
		printf("Remover expedicao\n");
		printf("Encomenda da expedicao a remover: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &codenc);
		if(codenc > 0) {
			posenc = ProcuraEncomenda(armaz, codenc);
			if(posenc != -1) {
				pNE = DeleteL(&(armaz->expds), posenc);
				while(!EmptyL(&(pNE->elem.expd.packs))) {
					InsertL(&(armaz->packs), DeleteL(&(pNE->elem.expd.packs), 0),
						SizeL(&(armaz->packs)));
				}
				free(pNE);
				printf("Expedicao removida com sucesso.\n");
			}else {
				printf("A expedicao nao existe.\n");
			}
		}else {
			printf("O nro da encomenda da expedicao tem que ser maior que 0!\n");
		}
	}else {
		printf("Nao ha expedicoes para remover.\n");
	}
}

void FecharExpedicao(ApArmazem armaz) {
	int enc, posexpd;
	char str[STRG];
	ApNo pNE;

	if(!EmptyL(&(armaz->expds))) {
		printf("Fechar uma expedicao\n");
		printf("Digite a encomenda da expedicao: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &enc);
		if(enc > 0) {
			posexpd = ProcuraEncomenda(armaz, enc);
			if(posexpd != -1) {
				pNE = SetPositionL(&(armaz->expds), posexpd);
				if(!EmptyL(&(pNE->elem.expd.packs))) {
					;
					if(pNE->elem.expd.open == 1) {
						pNE->elem.expd.open = 0;
						printf("Expedicao Fechada com sucesso!\n");
					}else {
						printf("A expedicao ja se encontra fechado!\n");
					}
				}else {
					printf("A expedicao nao contem packs, nao pode ser fechada.\n");
				}
			}else {
				printf("A expedicao nao existe!\n");
			}
		}else {
			printf("A encomenda tem de positiva!\n");
		}
	}else {
		printf("Nao existem expedicoes para fechar!\n");
	}
}

int ProcuraGuia(ApArmazem armaz, int nguia) {
	int pos = 0;
	ApNo pNG = armaz->guias.head;

	while(pNG && nguia != pNG->elem.guia.num) {
		++pos;
		pNG = pNG->next;
	}
	if(pNG) {
		return pos;
	}else {
		return -1;
	}
}

void CriarGuia(ApArmazem armaz) {
	ApNo Apguia;
	char str[STRG];

	printf("Criar Guia\n");
	Apguia = malloc(sizeof(No));
	Apguia->elem.guia.num = (armaz->guias.proxguia)++;
	Apguia->elem.guia.open = 1;
	NewL(&(Apguia->elem.guia.expds));
	printf("Introduza o cliente: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &(Apguia->elem.guia.cliente));

	InsertL((ApLista) &(armaz->guias), Apguia, SizeL((ApLista) &(armaz->guias)));
	printf("Guia criada com sucesso\n");
}

void AdicionarExpdGuia(ApArmazem armaz) {
	int codguia, posguia, encomenda, posexpd;
	ApNo ApGuia, ApExp;
	char str[STRG];

	if(!EmptyL((ApLista) &(armaz->guias))) {
		if(!EmptyL(&armaz->expds)) {
			printf("Adicionar expedicao\n");
			printf("Digite o codigo da Guia: ");
			fgets(str, sizeof(str), stdin);
			sscanf(str, "%d", &codguia);
			if(codguia > 0) {
				posguia = ProcuraGuia(armaz, codguia);
				if(posguia != -1) {
					ApGuia = SetPositionL((ApLista) &(armaz->guias), posguia);
					if(ApGuia->elem.guia.open == 1) {
						printf("Digite a Encomenda: ");
						fgets(str, sizeof(str), stdin);
						sscanf(str, "%d", &encomenda);
						if(encomenda > 0) {
							posexpd = ProcuraEncomenda(armaz, encomenda);
							if(posexpd != -1) {
								ApExp = SetPositionL(&(armaz->expds), posexpd);
								if(ApExp->elem.expd.open == 0) {
									InsertL(&(ApGuia->elem.guia.expds),
										DeleteL(&(armaz->expds), posexpd),
										SizeL(&(ApGuia->elem.guia.expds)));
									printf("Expedicao adicionada com sucesso\n");
								}else {
									printf(
										"Nao e possivel adicionar, a expedicao nao esta fechada\n");
								}
							}else {
								printf("Expedicao nao encontrada\n");
							}
						}else {
							printf("Encomenda Invalida!");
						}
					}else {
						printf("A guia esta fechada, nao e possivel modifica-la\n");
					}
				}else {
					printf("Guia nao encontrada\n");
				}
			}else {
				printf("Guia Invalida\n");
			}
		}else {
			printf("Ainda nao foram adicionadas expedicoes\n");
		}
	}else {
		printf("Nao existem para adicionar expedicoes\n");
	}
}

void FecharGuia(ApArmazem armaz) {
	int codguia, posguia, day, month, year, verif;
	char str[STRG], cd;
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);
	ApNo pNG;

	if(!EmptyL((ApLista) &(armaz->guias))) {
		printf("Fechar guia\n");
		printf("Numero da guia a fechar: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &codguia);
		if(codguia > 0) {
			posguia = ProcuraGuia(armaz, codguia);
			if(posguia != -1) {
				pNG = SetPositionL((ApLista) &(armaz->guias), posguia);
				if(!EmptyL(&(pNG->elem.guia.expds))) {
					if(pNG->elem.guia.open) {
						pNG->elem.guia.open = 0;
						printf("Data (A)utomatica ou (M)anual: ");
						fgets(str, sizeof(str), stdin);
						sscanf(str, "%c", &cd);
						cd = toupper(cd);
						switch(cd) {
						default:
							printf("Opcao invalida, a introduzir a data automaticamente\n");
							/* no break */
						case 'A':
							pNG->elem.guia.data.dia = str_t.wDay;
							pNG->elem.guia.data.mes = str_t.wMonth;
							pNG->elem.guia.data.ano = str_t.wYear;
							break;
						case 'M':
							do {
								printf("Data do pacote [dd/mm/yyyy]: ");
								fgets(str, sizeof(str), stdin);
								sscanf(str, "%d%c%d%c%d", &day, &cd, &month, &cd, &year);
								verif = validDate(day, month, year);
								if(!verif) printf("Data invalida!\n");
							}while(!verif);

							pNG->elem.guia.data.dia = day;
							pNG->elem.guia.data.mes = month;
							pNG->elem.guia.data.ano = year;
						}
						printf("Guia fechada com sucesso.\n");
					}else {
						printf("A guia ja se encontra fechada.\n");
					}
				}else {
					printf("Guia nao tem expedicoes, nao pode ser fechada.\n");
				}
			}else {
				printf("A guia nao existe.\n");
			}
		}else {
			printf("O nro da guia tem que ser maior que 0!\n");
		}
	}else {
		printf("Nao ha guias para fechar.\n");
	}
}

void RemoverGuia(ApArmazem armaz) {
	int codguia, posguia;
	char str[STRG];
	ApNo pNG;

	if(!EmptyL((ApLista) &(armaz->guias))) {
		printf("Fechar guia\n");
		printf("Numero da guia a remover: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &codguia);
		if(codguia > 0) {
			posguia = ProcuraGuia(armaz, codguia);
			if(posguia != -1) {
				pNG = SetPositionL((ApLista) &(armaz->guias), posguia);
				if(pNG->elem.guia.open) {
					while(!EmptyL(&(pNG->elem.guia.expds))) {
						InsertL(&(armaz->expds), DeleteL(&(pNG->elem.guia.expds), 0),
							SizeL(&(armaz->expds)));
					}
					free(DeleteL((ApLista) &(armaz->guias), posguia));
					printf("Guia removida com sucesso.\n");
				}else {
					printf("A guia ja foi lancada nao e possivel modifica-la.\n");
				}
			}else {
				printf("A guia nao existe.\n");
			}
		}else {
			printf("O nro da guia tem que ser maior que 0!\n");
		}
	}else {
		printf("Nao ha guias para remover.\n");
	}
}

void ListarGuias(ApArmazem armaz) {
	ApNo pNG = armaz->guias.head;

	if(pNG) {
		printf("Listar guias:\n\n");
		while(pNG) {
			printf("Guia nro: %d\n"
				"Cliente destino: %d\n", pNG->elem.guia.num, pNG->elem.guia.cliente);
			printf("Contem %d expedicoes\n", SizeL(&(pNG->elem.guia.expds)));
			if(!pNG->elem.guia.open) {
				printf("Data de emicao: %d/%d/%d\n", pNG->elem.guia.data.dia,
					pNG->elem.guia.data.mes, pNG->elem.guia.data.ano);
			}else {
				printf("A guia nao emitida.\n");
			}
			printf("\n");
			pNG = pNG->next;
		}
	}else {
		printf("Nao ha guias para listar.\n");
	}
}

void Limpa(ApArmazem armaz, ApQueue filaRolos) {
	ApNo pPack = armaz->packs.head;
	ApNo pExpd = armaz->expds.head;
	ApNo pGuia = armaz->guias.head;

	while(pPack) {
		ClearS(&(pPack->elem.pack.pilharolos));
		pPack = pPack->next;
	}

	while(pExpd) {
		pPack = pExpd->elem.expd.packs.head;
		while(pPack) {
			ClearS(&(pPack->elem.pack.pilharolos));
			pPack = pPack->next;
		}
		pExpd = pExpd->next;
	}

	while(pGuia) {
		pExpd = pGuia->elem.guia.expds.head;
		while(pExpd) {
			pPack = pExpd->elem.expd.packs.head;
			while(pPack) {
				ClearS(&(pPack->elem.pack.pilharolos));
				pPack = pPack->next;
			}
			pExpd = pExpd->next;
		}
		pGuia = pGuia->next;
	}

	ClearQ(filaRolos);
	ClearL(&(armaz->rolos));
	ClearL(&(armaz->packs));
	ClearL(&(armaz->expds));
	ClearL((ApLista) &(armaz->guias));
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
