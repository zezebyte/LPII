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

void AdRoloArm(pQueue ap_queue, ApArmazem armaz){
    ApNo aux;
    char str[STRG];
    
    if(EmptyQ(ap_queue)==0){
        aux=Dequeue(ap_queue);
        printf("Introduza o codigo do Rolo: ");
        fgets(str, sizeof(str), stdin);
        if(strlen(str)<11){
            if(ProcuraCodRolo(str,armaz)==-1 && ProcuraCodigoRoloEmPacks(armaz, str)==0){
                strcpy(aux->elem.codigo, str);
                printf("Introduza o comprimento do rolo: ");
                fgets(str, sizeof(str), stdin);
                sscanf(str, "%f", aux->elem.comp);
                if(aux->elem.comp>0.0){
                    printf("Introduza a qualidade do rolo: ");
                    fgets(str, sizeof(str), stdin);
                    sscanf(str, "%d", &(aux->elem.enc));
                    armaz->rolosarmazem[armaz->cont_rolos]=aux->elem;
                    free(aux);
                    armaz->cont_rolos= armaz->cont_rolos+1;
                    printf("Rolo adicionado ao armazem com sucesso\n"); 
                }else{
                    Enqueue(aux, ap_queue);
                    printf("Os rolos tem que ter o comprimento positivo!\n");
                }
            }else{
                Enqueue(aux, ap_queue);
                printf("Já existe um rolo com esse codigo!\n");
            }
        }else{
            Enqueue(aux, ap_queue);
            printf("O codigo so pode ter ate 10 caracteres!\n");
        }
    }else{
        Enqueue(aux, ap_queue);
        printf("Nao ha rolos para adicionar!\n");
    }
}

void RemoverRolo(ApArmazem armaz){
    char cod[10];
    int pos, i;
    
    printf("Inttroduza o codigo do rolo que pretende remover: ");
    fgets(str, sizeof(str), stdin);
    pos=ProcuraCodRolo(cod, armaz);
    if(pos!=-1){
        armaz->cont_rolos=armaz->cont_rolos-1;
        for(i=pos; i<armaz->cont_rolos-1; i++){
            armaz->rolosarmazem[i]=armaz->rolosarmazem[i+1];
        }
        printf("Rolo apagado com sucesso!\n");
    }else{
        printf("Nao existe um rolo com esse codigo para apagar!\n");
    }
}

void AlterarRolos(ApArmazem armaz){
    int ind;
    float aux;
    char str[STRG];
    
    if(armaz->cont_rolos!=0){
        printf("Alteracao de rolos\n");
        printf("Introduza o codigo do rolo a alterar: ");
        fgets(str, sizeof(str), stdin);
        if(strlen(str)<11){
            ind=ProcuraCodRolo(str, armaz);
            if(ind!=-1){
                printf("Introduza o comprimento do rolo: ");
                fgets(str, sizeof(str), stdin);
                sscanf(str, "%f", &aux);
                if(aux>0.0){
                    armaz->rolosarmazem[ind].comp=aux;
                    printf("Introduza a qualidade do rolo: ");
                    fgets(str, sizeof(str), stdin);
                    scanf(str, "%d", &(armaz->rolosarmazem[ind].qualid));
                    printf("Introduza a descricao do produto: ");
                    fgets(armaz->rolosarmazem[ind].descr, sizeof(armaz->rolosarmazem[ind].descr), stdin);
                    printf("Introduza a encomenda do produto: ");
                    fgets(str, sizeof(str), stdin);
                    scanf(str, "%d", &(armaz->rolosarmazem[ind].enc));
                    printf("Rolo editado com sucesso!\n");
                }else{
                    printf("Os rolos tem de ter comprimento positivo!\n");
                }
            }else{
                printf("Nao existe um rolo com esse codigo!\n");
            }
        }else{
           printf("O codigo so pode ter ate 10 caracteres!\n"); 
        }
    }else{
        printf("Nao há rolos para alterar!\n");
    }
}
