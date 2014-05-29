#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int EmptyQ(ApQueue pQ) {
	if(pQ->head == NULL) return 1;
	return 0;
}

int FullQ(ApQueue pQ) {
	if(MAXQUEUE == 0)
		return 0;
	else if(SizeQ(pQ) < MAXQUEUE) return 0;
	return 1;
}

void ClearQ(ApQueue pQ) {
	if(!EmptyQ(pQ)) {
		free(Dequeue(pQ));
	}
}

int SizeQ(ApQueue pQ) {
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

ApNo FrontQ(ApQueue pQ) {
	return pQ->head;
}

int NewQ(ApQueue pQ) {
	pQ->head = NULL;
	pQ->tail = NULL;
	return 1;
}

ApNo Dequeue(ApQueue pQ) {
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

int Enqueue(ApQueue pQ, ApNo x) {
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
