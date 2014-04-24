/* 
 * File:   armazem.h
 * Author: sos
 *
 * Created on 23 de Abril de 2014, 14:02
 */
#ifndef _ARMAZEMH_
#define _ARMAZEMH_
#include "types.h"

void InitArm(ApArmazem);
int ProcuraCodRolo(char, ApArmazem);
int ProcuraCodPack(int, ApArmazem);
int ProcuraCodigoRoloEmPacks(ApArmazem, char);
void ReceberRolo(pQueue, ApArmazem);
void AdRoloArm(pQueue, ApArmazem);
void RemoverRolo(ApArmazem);
void AlterarRolos(ApArmazem);
void ListarRolos(ApArmazem);
void CriarPack(ApArmazem);
void AdicionarRoloPack(ApArmazem);
void ListarPacks(ApArmazem);
void EliminarPack(ApArmazem);
void FecharPack(ApArmazem);




#endif
