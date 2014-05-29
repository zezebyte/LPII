#ifndef QUEUE_H_
#define QUEUE_H_
#include "types.h"

int EmptyQ(ApQueue);
int FullQ(ApQueue);
void ClearQ(ApQueue);
int SizeQ(ApQueue);
ApNo FrontQ(ApQueue);
int NewQ(ApQueue);
ApNo Dequeue(ApQueue);
int Enqueue(ApQueue, ApNo);

#endif /* QUEUE_H_ */
