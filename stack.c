#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int EmptyS(pStack pS) {
	if(pS->top == NULL) return 1;
	return 0;
}

int FullS(pStack pS) {
	return 0;
}

void ClearS(pStack pS) {
	ApNo pN = pS->top;
	if(!EmptyS(pS)){
		while(pN->next != NULL){
			pS->top = pN->next;
			free(pN);
			pN = pS->top;
		}
	}
}

int SizeS(pStack pS) {
	int i = 0;
	ApNo pN = pS->top;
	while(pN->next != NULL) {
		pN = pN->next;
		++i;
	}
	return i;
}

ApNo TopS(pStack pS) {
	return pS->top;
}

int NewS(pStack pS) {
	pS->top = NULL;
	return 1;
}

ApNo Pop(pStack pS) {
	ApNo pN = pS->top;
	if(!EmptyS(pS))
		pS->top = pN->next;
	return pN;
}

int Push(pStack pS, ApNo ch) {
	if(FullS(pS)) {
		return 0;
	}else {
		ch->next = pS->top;
		pS->top = ch;
		return 1;
	}
}

int SearchCod(pStack pS, char cod[]){
	ApNo aux=pS->top;
    
    
}

void PrintStack(pStack pS){
	
}
