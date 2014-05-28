#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int NewL(pLinkedList pLL) {
	pLL->head = NULL;
	pLL->cont = 0;
	return 1;
}

int FullL(pLinkedList pLL) {
	if(MAXLIST == 0) return 0;
	if(SizeL(pLL) < MAXLIST) return 0;
	return 1;
}

int SizeL(pLinkedList pLL) {
	return pLL->cont;
}

int EmptyL(pLinkedList pLL) {
	if(pLL->head == NULL) return 1;
	return 0;
}

void ClearL(pLinkedList pLL) {
	while(!EmptyL(pLL)) {
		free(DeleteL(pLL, 0));
	}
}

pNo DeleteL(pLinkedList pLL, int pos) {
	pNo ApN = NULL, prev;
	if(pos >= 0 && pos < SizeL(pLL)) {
		ApN = SetPositionL(pLL, pos);
		if(pos != 0) {
			prev = SetPositionL(pLL, pos - 1);
			prev->next = ApN->next;
		}else {
			pLL->head = ApN->next;
		}
		--(pLL->cont);
	}
	return ApN;
}

pNo SetPositionL(pLinkedList pLL, int pos) {
	pNo ApN = NULL;
	int i;
	if(pos >= 0 && pos < SizeL(pLL)) {
		ApN = pLL->head;
		for(i = 0; i < pos; ++i) {
			ApN = ApN->next;
		}
	}
	return ApN;
}

int InsertL(pLinkedList pLL, pNo ApN, int pos) {
	pNo aux;
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

int ReplaceL(pLinkedList pLL, pNo ApN, int pos) {
	if(pos >= 0 && pos < SizeL(pLL)) {
		InsertL(pLL, ApN, pos);
		free(DeleteL(pLL, pos + 1));
		return 1;
	}
	return 0;
}

void PrintL(pLinkedList pLL) {
	int i = 0;
	pNo aux = SetPositionL(pLL, i);
	printf("Lista:\n");

	while(aux != NULL) {
		printf("%d ", aux->elem);
		aux = SetPositionL(pLL, ++i);
	}
}

void SortL(pLinkedList pLL) {
	pNo cmp, prev;
	int i, j, n = SizeL(pLL);

	for(i = 0; i < n - 1; ++i) {
		for(j = 0; j < n - i - 1; ++j) {
			cmp = SetPositionL(pLL, j);
			if(cmp->elem > cmp->next->elem) {
				if(j != 0) {
					prev = SetPositionL(pLL, j - 1);
					prev->next = cmp->next;
					cmp->next = cmp->next->next;
					prev->next->next = cmp;
				}else {
					pLL->head = cmp->next;
					cmp->next = cmp->next->next;
					pLL->head->next = cmp;
				}
			}
		}
	}
}
