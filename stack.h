#ifndef STACK_H_
#define STACK_H_
#include "types.h"

int EmptyS(ApStack);
int FullS(ApStack);
void ClearS(ApStack);
int SizeS(ApStack);
ApNo TopS(ApStack);
int NewS(ApStack);
ApNo Pop(ApStack);
int Push(ApStack, ApNo);
int SearchCodS(ApStack, char*);
void PrintStack(ApStack);

#endif /* STACK_H_ */
