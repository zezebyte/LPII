/*
 Este Vai ser o principal HeaderFile
 
 */
#include <stdio.h>
#include <stdlib.h>
#include "Stacks.h"
#include "No.h"
#define STRG 80

typedef struct{  //Estrutura data
    int dia, mes, ano;
}Data;

typedef struct{ //Estrutura do Rolo
    char codigo[10], desc[STRG];
    int enc, qualid;
    float comp;
}Rolo;

typedef struct no{
   Rolo elemento;
   ApNo NoSeguinte;
}No;



void limparEcra(){ //funcao para limpar o ecra
    system(" cmd /c cls ");
}

void Prima(){ //funcao de espera
    printf("Prima ENTER para continuar...\n");
    getchar();
}
