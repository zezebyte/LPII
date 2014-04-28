#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


int EmptyQ(pQueue pQ) {
	if(pQ->head == NULL) return 1;
	return 0;
}

int FullQ(pQueue pQ) {
	return 0;
}

void ClearQ(pQueue pQ) {
	if(!EmptyQ(pQ)) {
		free(Dequeue(pQ));
	}
}

int SizeQ(pQueue pQ) {
	int i = 0;
	ApNo pQN = pQ->head;
	if(pQN != NULL) {
		++i;
		while(pQN->next != pQ->head) {
			pQN = pQN->next;
			++i;
		}
	}
	return i;
}

ApNo FrontQ(pQueue pQ) {
	return pQ->head;
}

int NewQ(pQueue pQ) {
	pQ->head = NULL;
	pQ->tail = NULL;
	return 1;
}

ApNo Dequeue(pQueue pQ) {
	ApNo pQN = pQ->head;

	if(pQ->head == pQ->tail) {
		pQ->head = NULL;
		pQ->tail = NULL;
	}else {
		pQ->head = pQ->head->next;
		pQ->tail->next = pQ->head;
	}
	return pQN;
}

int Enqueue(pQueue pQ, ApNo x) {
	if(FullQ(pQ)) {
		return 0;
	}else {
		if(EmptyQ(pQ)) {
			pQ->head = x;
		}else {
			pQ->tail->next = x;
		}
		pQ->tail = x;
		pQ->tail->next = pQ->head;
		return 1;
	}
}
