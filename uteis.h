/*
 Este Vai ser o principal HeaderFile
 
 */
#include <stdio.h>
#include <stdlib.h>
#define STRG 80
#define MAX 100



void limparEcra(){ //funcao para limpar o ecra
    system(" cmd /c cls ");
}

void Prima(){ //funcao de espera
    printf("Prima ENTER para continuar...\n");
    getchar();
}
