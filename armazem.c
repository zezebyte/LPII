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
int ProcuraCodigoRoloEmPacks(ApArmazem armaz, char codigo[]){
    int i;
    
    for(i=0; i<armaz->cont_packs-1; i++){
        if(SearchCodS(&(armaz->packsarmazem[i]), codigo))
            return 1; 
    }
    return 0;
}

void ReceberRolo(pQueue Rolo, ApArmazem armaz){
    ApNo aux;
    char str[STRG];
    
    if(FullQ(Rolo)=0){
        aux=malloc(sizeof(No));
        printf("Adicionar Rolo\n");
        printf("Introduza a descricao do produto: ");
        fgets(aux->elem.descr, sizeof(aux->elem.descr), stdin);
        printf("Introduza a encomenda do porduto: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", aux->elem.enc);
        Enqueue(Rolo, aux);
        printf("Rolo introduzido com sucesso!\n");
    }else{
        printf("Buffer da seccao de acabamentos cheio!\n")
    }
}

