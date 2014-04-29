#ifndef STACK_H_
#define STACK_H_
#include "types.h"

int EmptyS(pStack);
int FullS(pStack);
void ClearS(pStack);
int SizeS(pStack);
ApNo TopS(pStack);
int NewS(pStack);
ApNo Pop(pStack);
int Push(pStack, ApNo);
int SearchCodS(pStack, char*);
void PrintStack(pStack);

#endif /* STACK_H_ */
