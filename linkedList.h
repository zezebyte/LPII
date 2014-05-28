#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "types.h"

int NewL(pLinkedList);
int FullL(pLinkedList);
int SizeL(pLinkedList);
int EmptyL(pLinkedList);
void ClearL(pLinkedList);
pNo DeleteL(pLinkedList, int);
pNo SetPositionL(pLinkedList, int);
int InsertL(pLinkedList, pNo, int);
int ReplaceL(pLinkedList, pNo, int);
void SortL(pLinkedList);
void PrintL(pLinkedList);

#endif /* LINKEDLIST_H_ */
