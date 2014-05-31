#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int NewL(ApLista pLL) {
	pLL->head = NULL;
	pLL->cont = 0;
	return 1;
}

int FullL(ApLista pLL) {
	if(MAXLLIST == 0)
		return 0;
	else if(SizeL(pLL) < MAXLLIST) return 0;
	return 1;
}

int SizeL(ApLista pLL) {
	return pLL->cont;
}

int EmptyL(ApLista pLL) {
	if(pLL->head == NULL) return 1;
	return 0;
}

void ClearL(ApLista pLL) {
	while(!EmptyL(pLL)) {
		free(DeleteL(pLL, 0));
	}
}

ApNo DeleteL(ApLista pLL, int pos) {
	ApNo ApN, del = NULL;
	if(pos >= 0 && pos < SizeL(pLL)) {
		if(pos == 0){
			del = pLL->head;
			pLL->head = del->next;
		}else {
			ApN = SetPositionL(pLL, pos - 1);
			del = ApN->next;
			ApN->next = del->next;
		}
		--(pLL->cont);
	}
	return del;
}

ApNo SetPositionL(ApLista pLL, int pos) {
	ApNo ApN = NULL;
	int i;
	if(pos >= 0 && pos < SizeL(pLL)) {
		ApN = pLL->head;
		for(i = 0; i < pos; ++i) {
			ApN = ApN->next;
		}
	}
	return ApN;
}

int InsertL(ApLista pLL, ApNo ApN, int pos) {
	ApNo aux;
	if(pos >= 0 && pos <= SizeL(pLL)) {
		if(pos != 0) {
			aux = SetPositionL(pLL, pos - 1);
			ApN->next = aux->next;
			aux->next = ApN;
		}else {
			ApN->next = pLL->head;
			pLL->head = ApN;
		}
		++(pLL->cont);
		return 1;
	}
	return 0;
}

int ReplaceL(ApLista pLL, ApNo ApN, int pos) {
	if(pos >= 0 && pos < SizeL(pLL)) {
		InsertL(pLL, ApN, pos);
		free(DeleteL(pLL, pos + 1));
		return 1;
	}
	return 0;
}

