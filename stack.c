#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int SearchCodS(pStack pS, char cod[]){
    ApNo aux=pS->top;
    
    
    while(aux!=NULL){
        if(strcmp(codigo,aux->elem.codigo)==0)
            return 1; //verdadeiro
        aux=aux->next;
    }
    return 0; //devolve zero se nao encontrar    
}

void PrintStack(pStack pS){
    ApNo ApN=pS->top;
    
    if(EmptyS(ApS)==0){
        while(ApN->next!=NULL){
            printf("Codigo do Rolo: %s\n", armaz->rolosarmazem[i].codigo);
            printf("Descricao: %s\n", armaz->rolosarmazem[i].descr);
            printf("Comprimento: %.2f\n", armaz->rolosarmazem[i].comp);
            printf("Qualidade: %d\n", armaz->rolosarmazem[i].qualid);
            printf("Encomenda: %d\n", armaz->rolosarmazem[i].enc); 
            ApN=ApN->next;
        }
    }
}
