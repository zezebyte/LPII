#ifndef ARMAZEM_H_
#define ARMAZEM_H_
#include "types.h"

void InitArm(ApArmazem);
int ProcuraCodRolo(ApArmazem, char*);
int ProcuraCodPack(ApArmazem, int);
int ProcuraCodigoRoloEmPacks(ApArmazem, char*);
void ReceberRolo(ApArmazem, ApQueue);
void AdRoloArm(ApArmazem, ApQueue);
void RemoverRolo(ApArmazem);
void AlterarRolos(ApArmazem);
void ListarRolos(ApArmazem);
void CriarPack(ApArmazem);
void AdicionarRoloPack(ApArmazem);
void ListarPacks(ApArmazem);
void RemoverPack(ApArmazem);
void FecharPack(ApArmazem);
int daysinmonth(int, int);
int validDate(int, int, int);

#endif	/* ARMAZEM_H_ */
