/*
 Este Vai ser o principal HeaderFile
 
 */
#include <stdio.h>
#include <stdlib.h>
#define STRG 80

void limparEcra(){						//funcao para limpar o ecra
    system(" cmd /c cls ");
}

void Prima(){
    printf("Prima ENTER para continuar...\n");
    getchar();
}
