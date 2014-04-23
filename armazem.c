#include <stdio.h>
#include <stdlib.h>
#include "armazem.h"

void InitArm(ApArmazem armaz){
    armaz->cont_packs=0;
    armaz->cont_rolos=0;
}

int ProcuraCodRolo(char codigo[], ApArmazem armaz){
    int pos=0;
    
    while(pos<armaz->cont_rolos && (strcmp(codigo,armaz->rolosarmazem[pos].codigo))!=0)
        pos++;
    if(pos!=armaz->cont_rolo)s
        return pos;
    else
        return -1;
    
}

int ProcuraCodPack(char codigo[], ApArmazem armaz){
    int pos=0;
    
    while(pos<armaz->cont_packs && (strcmp(codigo,armaz->packsarmazem[pos].codigo))!=0)
        pos++;
    if(pos!=armaz->cont_packs)s
        return pos;
    else
        return -1;
}
