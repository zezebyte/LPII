/* 
 * File:   armazem.h
 * Author: sos
 *
 * Created on 23 de Abril de 2014, 14:02
 */
#ifndef ARMAZEM_H_
#define ARMAZEM_H_
#include "types.h"

void InitArm(ApArmazem);
int ProcuraCodRolo(ApArmazem, char*);
int ProcuraCodPack(ApArmazem, int);
int ProcuraCodigoRoloEmPacks(ApArmazem, char*);
void ReceberRolo(ApArmazem, pQueue);
void AdRoloArm(ApArmazem, pQueue);
void RemoverRolo(ApArmazem);
void AlterarRolos(ApArmazem);
void ListarRolos(ApArmazem);
void CriarPack(ApArmazem);
void AdicionarRoloPack(ApArmazem);
void ListarPacks(ApArmazem);
void EliminarPack(ApArmazem);
void FecharPack(ApArmazem);

#endif
