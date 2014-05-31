#ifndef ARMAZEM_H_
#define ARMAZEM_H_
#include "types.h"

void InitArm(ApArmazem);
int ProcuraCodRolo(ApArmazem, char*);
int ProcuraCodRoloPacks(ApArmazem, char*);
int ProcuraCodRoloExpds(ApArmazem, char*);
int ProcuraCodRoloGuias(ApArmazem, char*);
int ProcuraCodPack(ApArmazem, int);
int ProcuraCodPackExpd(ApLista, int);
int ProcuraCodPackExpds(ApArmazem, int);
int ProcuraCodPackGuias(ApArmazem, int);
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
int ProcuraEncomenda(ApArmazem,int);
void CriarExpedicao(ApArmazem);
void AdicionarPackExpd(ApArmazem);
void RemoverPackExpds(ApArmazem);
void ListarExpedicoes(ApArmazem);
void FecharExpedicao(ApArmazem);
void CriarGuia(ApArmazem);
void AdicionarExpdGuia(ApArmazem);
void AnularGuia(ApArmazem);
void FecharGuia(ApArmazem);
void ListarGuias(ApArmazem);
int daysinmonth(int, int);
int validDate(int, int, int);


#endif	/* ARMAZEM_H_ */
