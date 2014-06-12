#include "listagens.h"
#include "linkedList.h"
#include "armazem.h"
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
	ApNo pNG = armaz->guias.head;

	printf("Introduza o codigo do rolo: ");
	fgets(codrolo, sizeof(codrolo), stdin);
	codrolo[strlen(codrolo) - 1] = '\0';
	if(strlen(codrolo) < 11) {
		while(pNR && strcmp(pNR->elem.rolo.codigo, codrolo)) {       //procura o codigo na lista de rolos
			pNR = pNR->next;
		}
		if(pNR) {
			printf("O rolo encontra-se na lista de rolos\n\n");
			printf("Rolo %s\n", codrolo);
			printf("  Descricao: %s\n", pNR->elem.rolo.descr);
			printf("  Comprimento: %.2f\n", pNR->elem.rolo.comp);
			printf("  Encomenda: %d\n\n", pNR->elem.rolo.qualid);

		}else {
			while(pNP && !encontrou) {
				pNR = pNP->elem.pack.pilharolos.top;       //primeiro no da stack
				while(pNR && !encontrou) {       //procura o codigo na lista de rolos
					if(strcmp(pNR->elem.rolo.codigo, codrolo) == 0)
						encontrou = 1;       //se encontrou coloca a flag a 1, para sair
					else pNR = pNR->next;
				}
				pNP = pNP->next;
			}
			if(pNR) {
				printf("O rolo encontra-se na lista de packs\n\n");
				printf("Rolo %s\n", codrolo);
				printf("  Descricao: %s\n", pNR->elem.rolo.descr);
				printf("  Comprimento: %.2f\n", pNR->elem.rolo.comp);
				printf("  Encomenda: %d\n\n", pNR->elem.rolo.qualid);
			}else {
				while(pNE && !encontrou) {       //lista de expedicoes
					pNP = pNE->elem.expd.packs.head;
					while(pNP && !encontrou) {
						pNR = pNP->elem.pack.pilharolos.top;
						while(pNR && !encontrou) {
							if(strcmp(pNR->elem.rolo.codigo, codrolo) == 0)
								encontrou = 1;
							else pNR = pNR->next;
						}
						pNP = pNP->next;
					}
					pNE = pNE->next;
				}
				if(pNR) {
					printf("O rolo encontra-se na lista de expedicoes\n\n");
					printf("Rolo %s\n", codrolo);
					printf("  Descricao: %s\n", pNR->elem.rolo.descr);
					printf("  Comprimento: %.2f\n", pNR->elem.rolo.comp);
					printf("  Encomenda: %d\n\n", pNR->elem.rolo.qualid);
				}else {
					while(pNG && !encontrou) {
						if(pNG->elem.guia.open) {
							pNE = pNG->elem.guia.expds.head;
							while(pNE && !encontrou) {
								pNP = pNE->elem.expd.packs.head;
								while(pNP && !encontrou) {
									pNR = pNP->elem.pack.pilharolos.top;
									while(pNR && !encontrou) {
										if(strcmp(pNR->elem.rolo.codigo, codrolo) == 0)
											encontrou = 1;
										else pNR = pNR->next;
									}
									pNP = pNP->next;
								}
								pNE = pNE->next;
							}
						}
						pNG = pNG->next;
					}
					if(pNR) {
						printf("O rolo encontra-se na lista de guias\n\n");
						printf("Rolo %s:\n", codrolo);
						printf("  Descricao: %s\n", pNR->elem.rolo.descr);
						printf("  Comprimento: %.2f\n", pNR->elem.rolo.comp);
						printf("  Encomenda: %d\n\n", pNR->elem.rolo.qualid);
					}else {
						printf("O rolo digitado nao existe\n");
					}
				}
			}
		}
	}else {
		printf("Codigo de Rolo invalido, tem mais de 10 caracteres\n");
	}
}

void ListarContPack(ApArmazem armaz) {
	char str[80];
	int codpack, encontrou = 0;
	ApNo pNR;
	ApNo pNP = armaz->packs.head;
	ApNo pNE = armaz->expds.head;
	ApNo pNG = armaz->guias.head;

	printf("Introduza o codigo do Pack: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &codpack);
	if(codpack > 999999 && codpack <= 9999999) {
		while(pNP && pNP->elem.pack.codigo != codpack) {
			pNP = pNP->next;
		}
		if(pNP) {
			printf("Pack %d:\n", codpack);
			if(EmptyS(&(pNP->elem.pack.pilharolos))) {       //verifica se o pack tem rolos empilhados
				printf("O pack esta vazio\n");
			}else {
				pNR = pNP->elem.pack.pilharolos.top;
				printf("  Qualidade: %d\n", pNR->elem.rolo.qualid);
				printf("  Encomenda: %d\n", pNR->elem.rolo.enc);
				while(pNR) {
					printf("    Rolo %s\n", pNR->elem.rolo.codigo);
					printf("      Descricao: %s\n", pNR->elem.rolo.descr);
					printf("      Comprimento: %.2f\n", pNR->elem.rolo.comp);
					printf("      Encomenda: %d\n\n", pNR->elem.rolo.qualid);
					pNR = pNR->next;
				}
			}
		}else {
			while(pNE && !encontrou) {
				pNP = pNE->elem.expd.packs.head;
				while(pNP && !encontrou) {
					if(pNP->elem.pack.codigo == codpack) {
						encontrou = 1;
					}else {
						pNP = pNP->next;
					}
				}
				pNE = pNE->next;
			}
			if(pNP) {
				printf("Pack %d:\n", codpack);
				if(EmptyS(&(pNP->elem.pack.pilharolos))) {       //verifica se o pack tem rolos empilhados
					printf("O pack esta vazio\n");
				}else {
					pNR = pNP->elem.pack.pilharolos.top;
					printf("  Qualidade: %d\n", pNR->elem.rolo.qualid);
					printf("  Encomenda: %d\n", pNR->elem.rolo.enc);
					while(pNR) {
						printf("    Rolo %s\n\n", pNR->elem.rolo.codigo);
						printf("      Descricao: %s\n", pNR->elem.rolo.descr);
						printf("      Comprimento: %.2f\n", pNR->elem.rolo.comp);
						printf("      Encomenda: %d\n\n", pNR->elem.rolo.qualid);
						pNR = pNR->next;
					}
				}
			}else {
				while(pNG && !encontrou) {
					if(pNG->elem.guia.open == 1) {
						pNE = pNG->elem.guia.expds.head;
						while(pNE && !encontrou) {
							pNP = pNE->elem.expd.packs.head;
							while(pNP && !encontrou) {
								if(pNP->elem.pack.codigo == codpack) {
									encontrou = 1;
								}else {
									pNP = pNP->next;
								}
							}
							pNE = pNE->next;
						}

					}
					pNG = pNG->next;
				}
				if(pNP) {
					printf("Pack %d:\n", codpack);
					if(EmptyS(&(pNP->elem.pack.pilharolos))) {       //verifica se o pack tem rolos empilhados
						printf("O pack esta vazio\n");
					}else {
						pNR = pNP->elem.pack.pilharolos.top;
						printf("  Qualidade: %d\n", pNR->elem.rolo.qualid);
						printf("  Encomenda: %d\n", pNR->elem.rolo.enc);
						while(pNR) {
							printf("    Rolo %s\n\n", pNR->elem.rolo.codigo);
							printf("      Descricao: %s\n", pNR->elem.rolo.descr);
							printf("      Comprimento: %.2f\n", pNR->elem.rolo.comp);
							printf("      Encomenda: %d\n\n", pNR->elem.rolo.qualid);
							pNR = pNR->next;
						}
					}
				}else {
					printf("O pack digitado nao existe\n");
				}
			}
		}
	}else {
		printf("Codigo do Pack incorreto\n");
	}
}
void MetragemExpd(ApArmazem armaz) {
	char str[80];
	float metragem = 0.0;
	int codexpd, encontrou = 0;
	ApNo pNE = armaz->expds.head;
	ApNo pNP;
	ApNo pNR;
	ApNo pNG = armaz->guias.head;

	printf("Introduza a encomenda: ");
	fgets(str, sizeof(str), stdin);
	sscanf(str, "%d", &codexpd);
	if(codexpd > 0) {
		while(pNE && !encontrou) {
			if(pNE->elem.expd.enc == codexpd) {
				encontrou = 1;
			}else {
				pNE = pNE->next;
			}
		}
		if(pNE) {
			if(EmptyL(&(pNE->elem.expd.packs))) {
				printf("A expedicao esta vazia\n");
			}else {
				pNP = pNE->elem.expd.packs.head;
				while(pNP) {
					pNR = pNP->elem.pack.pilharolos.top;
					while(pNR) {
						metragem += pNR->elem.rolo.comp;
						pNR = pNR->next;
					}
					pNP = pNP->next;
				}
			}
		}else {
			while(pNG) {
				if(pNG->elem.guia.open) {
					pNE = pNG->elem.guia.expds.head;
					while(pNE && !encontrou) {
						if(pNE->elem.expd.enc == codexpd) {
							encontrou = 1;
						}else {
							pNE = pNE->next;
						}
					}
				}
				pNG = pNG->next;
			}
			if(pNE) {
				pNP = pNE->elem.expd.packs.head;
				while(pNP) {
					pNR = pNP->elem.pack.pilharolos.top;
					while(pNR) {
						metragem += pNR->elem.rolo.comp;
						pNR = pNR->next;
					}
					pNP = pNP->next;
				}
			}

		}

		if(encontrou == 0) {
			printf("Essa expedicao nao existe\n");
		}else {
			if(metragem > 0) {
				printf("A metragem da Expedicao : %d e: %.2f", codexpd, metragem);
			}else {
				printf("A expedicao esta vazia\n");
			}
		}
	}else {
		printf("Codigo de encomenda incorreto\n");
	}
}

void QuantRolosPacksGuia(ApArmazem armaz) {
	char str[80];
	int codguia, trolos = 0, tpacks = 0, posguia;
	ApNo ApGuia;
	ApNo ApExp;
	ApNo ApPack;

	if(EmptyL((ApLista) &(armaz->guias)) == 0) {       //verifica se existem guias
		printf("Digite o numero da guia: ");
		fgets(str, sizeof(str), stdin);
		sscanf(str, "%d", &codguia);
		if(codguia > 0) {       //verifica se o codigo da guia é valido
			posguia = ProcuraGuia(armaz, codguia);
			if(posguia != -1) {       //verifica se encontrou a guia
				ApGuia = SetPositionL((ApLista) &(armaz->guias), posguia);       //devolve o apontador da guia
				ApExp = ApGuia->elem.guia.expds.head;       //fica com o primeiro no da lista
				while(ApExp) {       //enquanto tiver nos percorre
					ApPack = ApExp->elem.expd.packs.head;       //primeiro no da lista de packs
					while(ApPack) {
						trolos += SizeS(&(ApPack->elem.pack.pilharolos));
						tpacks++;
						ApPack = ApPack->next;       //passa para o no seguinte
					}
					ApExp = ApExp->next;
				}
				printf("Existem: %d packs e %d rolos na guia\n", tpacks, trolos);
			}else {
				printf("Guia nao encontrada!\n");
			}
		}else {
			printf("Codigo de guia digitado nao e valido\n");
		}

	}else {
		printf("Nao existem guias\n");
	}
}

