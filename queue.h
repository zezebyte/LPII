#ifndef QUEUE_H_
#define QUEUE_H_
#include "types.h"

int EmptyQ(pQueue);
int FullQ(pQueue);
void ClearQ(pQueue);
int SizeQ(pQueue);
ApNo FrontQ(pQueue);
int NewQ(pQueue);
ApNo Dequeue(pQueue);
int Enqueue(pQueue, ApNo);

#endif /* _QUEUEH_ */
