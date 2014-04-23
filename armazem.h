/* 
 * File:   armazem.h
 * Author: sos
 *
 * Created on 23 de Abril de 2014, 14:02
 */
#include "No.h"
#include "pack.h"
#define MAX 100

typedef struct armazem *ApArmazem;

typedef struct armazem{
    Rolo rolosarmazem[MAX];
    Pack packsarmazem[MAX];
    int cont_rolos;
    int cont_packs;
}Armazem;


void InitArm(ApArmazem);
int ProcuraCodPack(char, ApArmazem);
