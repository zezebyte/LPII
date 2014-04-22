/* 
 * File:   uteis.h
 * Author: ATP
 *
 * Created on 22 de Abril de 2014, 18:08
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
