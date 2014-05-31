#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int EmptyS(ApStack pS) {
	if(pS->top == NULL) return 1;
	return 0;
}

int FullS(ApStack pS) {
	if(MAXSTACK == 0)
		return 0;
	else if(SizeS(pS) < MAXSTACK) return 0;
	return 1;
}

void ClearS(ApStack pS) {
	while(!EmptyS(pS)) {
		free(Pop(pS));
	}
}

int SizeS(ApStack pS) {
	int i = 0;
	ApNo pN = pS->top;
	while(pN != NULL) {
		pN = pN->next;
		++i;
	}
	return i;
}

ApNo TopS(ApStack pS) {
	return pS->top;
}

int NewS(ApStack pS) {
	pS->top = NULL;
	return 1;
}

ApNo Pop(ApStack pS) {
	ApNo pN = pS->top;
	if(!EmptyS(pS)) pS->top = pN->next;
	return pN;
}

int Push(ApStack pS, ApNo ch) {
	if(FullS(pS)) {
		return 0;
	}else {
		ch->next = pS->top;
		pS->top = ch;
		return 1;
	}
}

int SearchCodS(ApStack pS, char* cod) {
	ApNo aux = pS->top;

	while(aux != NULL) {
		if(strcmp(cod, aux->elem.rolo.codigo) == 0) return 1;       //encontrou um codigo igual
		aux = aux->next;
	}
	return 0;       //nao encontrou
}

void PrintStack(ApStack pS) {
	ApNo ApN = pS->top;

	while(ApN) {
		printf("    Rolo %s\n", ApN->elem.rolo.codigo);
		printf("    Descricao: %s\n", ApN->elem.rolo.descr);
		printf("    Comprimento: %.2f\n", ApN->elem.rolo.comp);
		printf("    Qualidade: %d\n", ApN->elem.rolo.qualid);
		printf("    Encomenda: %d\n\n", ApN->elem.rolo.enc);
		ApN = ApN->next;
	}
}
