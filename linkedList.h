#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "types.h"

int NewL(ApLista);
int FullL(ApLista);
int SizeL(ApLista);
int EmptyL(ApLista);
void ClearL(ApLista);
ApNo DeleteL(ApLista, int);
ApNo SetPositionL(ApLista, int);
int InsertL(ApLista, ApNo, int);
int ReplaceL(ApLista, ApNo, int);

#endif /* LINKEDLIST_H_ */
