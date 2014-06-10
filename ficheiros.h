#ifndef FICHEIROS_H_
#define FICHEIROS_H_
#include "types.h"

ApLista ProcurarListaExpds(ApArmazem, int);
ApLista ProcurarListaPacks(ApArmazem, int);
ApStack ProcurarStack(ApArmazem, int);
void GravarArmaz(ApArmazem, ApQueue);
void LerArmaz(ApArmazem, ApQueue);

#endif /* FICHEIROS_H_ */
