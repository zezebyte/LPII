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
	while(!EmptyQ(pQ)) {
		free(Dequeue(pQ));
	}
}

int SizeQ(ApQueue pQ) {
	int i = 0;
	ApNo pQN = pQ->head;
	while(pQN) {
		++i;
		pQN = pQN->next;
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

	if(!EmptyQ(pQ)) {
		pQ->head = pQ->head->next;
		if(EmptyQ(pQ)) {
			pQ->tail = NULL;
		}
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
		x->next = NULL;
		return 1;
	}
}
