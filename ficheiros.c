#include "ficheiros.h"
#include "armazem.h"
#include "stack.h"
#include "linkedList.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

ApLista ProcurarListaExpds(ApArmazem armaz, int codigo) {
	ApNo pNoG = armaz->guias.head;

	while(pNoG) {
		if(pNoG->elem.guia.num == codigo) {
			return &(pNoG->elem.guia.expds);
		}
		pNoG = pNoG->next;
	}
	return NULL;
}

ApLista ProcurarListaPacks(ApArmazem armaz, int codigo) {
	ApNo pNoG = armaz->guias.head;
	ApNo pNoE = armaz->expds.head;

	while(pNoE) {
		if(pNoE->elem.expd.enc == codigo) {
			return &(pNoE->elem.expd.packs);
		}
		pNoE = pNoE->next;
	}

	while(pNoG) {
		pNoE = pNoG->elem.guia.expds.head;
		while(pNoE) {
			if(pNoE->elem.expd.enc == codigo) return &(pNoE->elem.expd.packs);
			pNoE = pNoE->next;
		}
		pNoG = pNoG->next;
	}

	return NULL;
}

ApStack ProcurarStack(ApArmazem armaz, int codigo) {
	ApNo pNoG = armaz->guias.head;
	ApNo pNoE = armaz->expds.head;
	ApNo pNoP = armaz->packs.head;

	while(pNoP) {
		if(pNoP->elem.pack.codigo == codigo) return &(pNoP->elem.pack.pilharolos);
		pNoP = pNoP->next;
	}

	while(pNoE) {
		pNoP = pNoE->elem.expd.packs.head;
		while(pNoP) {
			if(pNoP->elem.pack.codigo == codigo) return &(pNoP->elem.pack.pilharolos);
			pNoP = pNoP->next;
		}
		pNoE = pNoE->next;
	}

	while(pNoG) {
		pNoE = pNoG->elem.guia.expds.head;
		while(pNoE) {
			pNoP = pNoE->elem.expd.packs.head;
			while(pNoP) {
				if(pNoP->elem.pack.codigo == codigo) return &(pNoP->elem.pack.pilharolos);
				pNoP = pNoP->next;
			}
			pNoE = pNoE->next;
		}
		pNoG = pNoG->next;
	}
	return NULL;
}

void GravarArmaz(ApArmazem armaz, ApQueue pQ) {
	FILE *fq, *fr, *fp, *fe, *fg;
	char *fileQ = "queue.db";
	char *fileR = "rolos.db";
	char *fileP = "packs.db";
	char *fileE = "expds.db";
	char *fileG = "guias.db";
	char *mode = "wb";
	ApNo pNoQ = pQ->head;
	ApNo pNoR = armaz->rolos.head;
	ApNo pNoP = armaz->packs.head;
	ApNo pNoE = armaz->expds.head;
	ApNo pNoG = armaz->guias.head;

	SaveNo save;

	fq = fopen(fileQ, mode);
	if(!fq) {
		fprintf(stderr, "Can't open input file %s!\n", fileQ);
		exit(1);
	}
	fr = fopen(fileR, mode);
	if(!fr) {
		fprintf(stderr, "Can't open input file %s!\n", fileR);
		exit(1);
	}
	fp = fopen(fileP, mode);
	if(!fp) {
		fprintf(stderr, "Can't open input file %s!\n", fileP);
		exit(1);
	}
	fe = fopen(fileE, mode);
	if(!fe) {
		fprintf(stderr, "Can't open input file %s!\n", fileE);
		exit(1);
	}
	fg = fopen(fileG, mode);
	if(!fg) {
		fprintf(stderr, "Can't open input file %s!\n", fileG);
		exit(1);
	}

	while(pNoQ) {
		fwrite(&(pNoQ->elem.rolo), sizeof(Rolo), 1, fq);
		pNoQ = pNoQ->next;
	}

	while(pNoR) {
		save.no.rolo = pNoR->elem.rolo;
		save.code = -1;
		fwrite(&(save), sizeof(SaveNo), 1, fr);
		pNoR = pNoR->next;
	}

	while(pNoP) {
		pNoR = pNoP->elem.pack.pilharolos.top;
		while(pNoR) {
			save.no.rolo = pNoR->elem.rolo;
			save.code = pNoP->elem.pack.codigo;
			fwrite(&(save), sizeof(SaveNo), 1, fr);
			pNoR = pNoR->next;
		}
		save.no.pack = pNoP->elem.pack;
		save.code = -1;
		fwrite(&(save), sizeof(SaveNo), 1, fp);
		pNoP = pNoP->next;
	}
	while(pNoE) {
		pNoP = pNoE->elem.expd.packs.head;
		while(pNoP) {
			pNoR = pNoP->elem.pack.pilharolos.top;
			while(pNoR) {
				save.no.rolo = pNoR->elem.rolo;
				save.code = pNoP->elem.pack.codigo;
				fwrite(&(save), sizeof(SaveNo), 1, fr);
				pNoR = pNoR->next;
			}
			save.no.pack = pNoP->elem.pack;
			save.code = pNoE->elem.expd.enc;
			fwrite(&(save), sizeof(SaveNo), 1, fp);
			pNoP = pNoP->next;
		}
		save.no.expd = pNoE->elem.expd;
		save.code = -1;
		fwrite(&(save), sizeof(SaveNo), 1, fe);
		pNoE = pNoE->next;
	}

	while(pNoG) {
		pNoE = pNoG->elem.guia.expds.head;
		while(pNoE) {
			pNoP = pNoE->elem.expd.packs.head;
			while(pNoP) {
				pNoR = pNoP->elem.pack.pilharolos.top;
				while(pNoR) {
					save.no.rolo = pNoR->elem.rolo;
					save.code = pNoP->elem.pack.codigo;
					fwrite(&(save), sizeof(SaveNo), 1, fr);
					pNoR = pNoR->next;
				}
				save.no.pack = pNoP->elem.pack;
				save.code = pNoE->elem.expd.enc;
				fwrite(&(save), sizeof(SaveNo), 1, fp);
				pNoP = pNoP->next;
			}
			save.no.expd = pNoE->elem.expd;
			save.code = pNoG->elem.guia.num;
			fwrite(&(save), sizeof(SaveNo), 1, fe);
			pNoE = pNoE->next;
		}
		fwrite(&(pNoG->elem.guia), sizeof(Guia), 1, fg);
		pNoG = pNoG->next;
	}

	fclose(fq);
	fclose(fr);
	fclose(fp);
	fclose(fe);
	fclose(fg);
}

void LerArmaz(ApArmazem armaz, ApQueue pQ) {
	FILE *fq, *fr, *fp, *fe, *fg;
	char *fileQ = "queue.db";
	char *fileR = "rolos.db";
	char *fileP = "packs.db";
	char *fileE = "expds.db";
	char *fileG = "guias.db";
	char *mode = "rb";
	ApLista pLista;
	ApStack pStack;
	ApNo aux;
	Rolo tmpr;
	Guia tmpg;

	SaveNo load;

	Limpa(armaz, pQ);
	armaz->guias.proxguia = 1;

	fq = fopen(fileQ, mode);
	if(!fq) {
		fprintf(stderr, "Can't open input file %s!\n", fileQ);
		exit(1);
	}
	fr = fopen(fileR, mode);
	if(!fr) {
		fprintf(stderr, "Can't open input file %s!\n", fileR);
		exit(1);
	}
	fp = fopen(fileP, mode);
	if(!fp) {
		fprintf(stderr, "Can't open input file %s!\n", fileP);
		exit(1);
	}
	fe = fopen(fileE, mode);
	if(!fe) {
		fprintf(stderr, "Can't open input file %s!\n", fileE);
		exit(1);
	}
	fg = fopen(fileG, mode);
	if(!fg) {
		fprintf(stderr, "Can't open input file %s!\n", fileG);
		exit(1);
	}

	while(!feof(fq) && fread(&tmpr, sizeof(Rolo), 1, fq) == 1) {
		aux = malloc(sizeof(No));
		aux->elem.rolo = tmpr;
		Enqueue(pQ, aux);
	}

	while(!feof(fg) && fread(&tmpg, sizeof(Guia), 1, fg) == 1) {
		aux = malloc(sizeof(No));
		aux->elem.guia = tmpg;
		NewL(&(aux->elem.guia.expds));
		InsertL((ApLista) &(armaz->guias), aux, SizeL((ApLista) &(armaz->guias)));
	}
	if(!EmptyL((ApLista) &(armaz->guias))) armaz->guias.proxguia = aux->elem.guia.num + 1;

	while(!feof(fe) && fread(&load, sizeof(SaveNo), 1, fe) == 1) {
		aux = malloc(sizeof(No));
		aux->elem.expd = load.no.expd;
		NewL(&(aux->elem.expd.packs));
		if(load.code == -1) {
			InsertL(&(armaz->expds), aux, SizeL(&(armaz->expds)));
		}else {
			pLista = ProcurarListaExpds(armaz, load.code);
			if(pLista) {
				InsertL(pLista, aux, SizeL(pLista));
			}
		}
	}

	while(!feof(fp) && fread(&load, sizeof(SaveNo), 1, fp) == 1) {
		aux = malloc(sizeof(No));
		aux->elem.pack = load.no.pack;
		NewS(&(aux->elem.pack.pilharolos));
		if(load.code == -1) {
			InsertL(&(armaz->packs), aux, SizeL(&(armaz->packs)));
		}else {
			pLista = ProcurarListaPacks(armaz, load.code);
			if(pLista) {
				InsertL(pLista, aux, SizeL(pLista));
			}
		}
	}

	while(!feof(fr) && fread(&load, sizeof(SaveNo), 1, fr) == 1) {
		aux = malloc(sizeof(No));
		aux->elem.rolo = load.no.rolo;
		if(load.code == -1) {
			InsertL(&(armaz->rolos), aux, SizeL(&(armaz->rolos)));
		}else {
			pStack = ProcurarStack(armaz, load.code);
			if(pStack) {
				Push(pStack, aux);
			}
		}
	}

	fclose(fq);
	fclose(fr);
	fclose(fp);
	fclose(fe);
	fclose(fg);
}
