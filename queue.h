#ifndef QUEUE_H_
#define QUEUE_H_
#include "No.h"

typedef struct queue* pQueue;

typedef struct queue {
	ApNo head;
	ApNo tail;
} Queue;

int EmptyQ(pQueue);
int FullQ(pQueue);
void ClearQ(pQueue);
int SizeQ(pQueue);
ApNo FrontQ(pQueue);
int NewQ(pQueue);
ApNo Dequeue(pQueue);
int Enqueue(pQueue, ApNo);

#endif /* QUEUE_H_ */
