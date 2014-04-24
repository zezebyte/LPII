#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "armazem.h"

void InitArm(ApArmazem armaz){
    armaz->cont_packs=0;
    armaz->cont_rolos=0;
}

int ProcuraCodRolo(char codigo[], ApArmazem armaz){
    int pos=0;
    
    while(pos<armaz->cont_rolos && (strcmp(codigo,armaz->rolosarmazem[pos].codigo))!=0)
        pos++;
    if(pos!=armaz->cont_rolos)
        return pos;
    else
        return -1;
    
}

int ProcuraCodPack(int codigo, ApArmazem armaz){
    int pos=0;
    
    while(pos<armaz->cont_packs && codigo!=armaz->packsarmazem[pos].codigo)
        pos++;
    if(pos!=armaz->cont_packs)
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
        printf("Buffer da seccao de acabamentos cheio!\n");
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
    fgets(cod, sizeof(cod), stdin);
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
void ListarRolos(ApArmazem armaz){
    int i;
    
    printf("Listar Rolos no armazem\n");
    for(i=0; i<armaz->cont_rolos; i++){
        printf("Codigo do Rolo: %s\n", armaz->rolosarmazem[i].codigo);
        printf("Descricao: %s\n", armaz->rolosarmazem[i].descr);
        printf("Comprimento: %.2f\n", armaz->rolosarmazem[i].comp);
        printf("Qualidade: %d\n", armaz->rolosarmazem[i].qualid);
        printf("Encomenda: %d\n", armaz->rolosarmazem[i].enc);  
    }
    for(i=0; i<armaz->cont_packs-1; i++){
        if(SizeS(&(armaz->packsarmazem[i].pilharolos))>0){
            PrintStack(&&(armaz->packsarmazem[i].pilharolos));
        }
    }
}

void CriarPack(ApArmazem armaz){
    int aux;
    char str[STRG], cd;
    
    printf("Inserir Pack\n");
    printf("Insira o codigo do pack: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &aux);
    if(aux>999999 && aux<=9999999){
        if(ProcuraCodPack(aux, armaz)==-1){
            armaz->packsarmazem[armaz->cont_packs].codigo=aux;
            printf("Introduza a data: (2014/04/25): ");
            fgets(str, sizeof(str), stdin);
            sscanf(str, "%d%c%d%c%d", &(armaz->packsarmazem[armaz->cont_packs].data.ano), &cd,&(armaz->packsarmazem[armaz->cont_packs].data.mes),&cd, &(armaz->packsarmazem[armaz->cont_packs].data.dia));
            printf("Pack Inserido com sucesso\n");
            NewS(&armaz->packsarmazem[armaz->cont_packs].pilharolos);
            armaz->packsarmazem[armaz->cont_packs].open=1;
            armaz->cont_packs=armaz->cont_packs+1;
            
        }else{
            printf("Esse codigo ja foi atribuido a outro pack\n");
        }
    }else{
        printf("O codigo digitado é invalido\n");
    }
}
void AdicionarRoloPack(ApArmazem armaz){
    ApNo aux, auxtop;
    int codpack, pospack, posrolo, i;
    char codrolo[10], str[STRG];
    
    printf("Empilhar rolo num pack\n");
    printf("Digite o codigo do pack: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &codpack);
    if(codpack>999999 && codpack<=9999999){
        pospack=(ProcuraCodPack(codpack,armaz));
        if(pospack!=-1){
            printf("Introduza o codigo do rolo que pretende adicionar: ");
            fgets(codrolo, sizeof(codrolo), stdin);
            if(strlen(codrolo)<11){
                posrolo=ProcuraCodRolo(codrolo, armaz);
                if(posrolo!=-1){
                    if(armaz->packsarmazem[codpack].open==1){
                        if(EmptyS(&armaz->packsarmazem[pospack].pilharolos)==1){
                            Push(&armaz->rolosarmazem[codrolo], &armaz->packsarmazem[pospack].pilharolos);
                            armaz->cont_rolos=armaz->cont_packs-1;
                            for(i=posrolo;i<armaz->cont_rolos-1; i++){
                                armaz->rolosarmazem[i]=armaz->rolosarmazem[i+1];
                            }
                        }else{
                            auxtop=TopS(&armaz->packsarmazem[armaz->cont_packs].pilharolos);
                            if(armaz->rolosarmazem[posrolo].qualid==auxtop->elem.qualid && armaz->rolosarmazem[posrolo].enc==auxtop->elem.enc){
                                 Push(&armaz->rolosarmazem[codrolo], &armaz->packsarmazem[pospack].pilharolos);
                                for(i=posrolo;i<armaz->cont_rolos-1; i++){
                                    armaz->rolosarmazem[i]=armaz->rolosarmazem[i+1];
                                }
                            }else{
                                printf("O rolo nao pode ser empilhado neste pack!\n");
                            }
                            
                        }
                    }else{
                        printf("Nao pode inserir mais rolos o pack ja esta fechado!\n");
                    }
                }else{
                    printf("O rolo que pretende empilhar nao existe!\n");
                }
            }else{
                printf("O codigo enserido esta incorreto!\n");
            }
        }else{
            printf("Esse pack nao existe!\n");
        }
    }else{
        printf("O codigo inserido esta incorreto!\n");
    }
}
