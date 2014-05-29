/*
 * File:   main.c
 * Author: sos
 *
 * Created on 28 de Maio de 2014, 20:37
 */

#include <stdio.h>
#include <stdlib.h>
#include "armazem.h"
#define STR 80

/*
*
 */
menurolos(ApArmazem armaz){
    int op;
    char str[STR];

    do{
        limparEcra();
        printf("Menu Rolos\n"
               "Escolha por favor uma das seguintes opcoes\n"
               "1-Remover Rolo do Armazem\n"
               "2-Alterar informacao de rolo\n"
               "3-Listar os rolos no armazem\n"
               "0-Voltar para o menu anterior\n"
               "Opcao: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &op);
        switch(op){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 0:
                printf("Voltar ao menu anterior...");
                Prima();
                break;
            default:
                printf("Erro! Opcao invalida\n");
        }
    }while(op!=0);
}

menupacks(ApArmazem armaz){
    int op;
    char str[STR];

    do{
        limparEcra();
        printf("Menu Packs\n"
               "Escolha por favor uma das seguintes opcoes\n"
               "1-Criar Pack\n"
               "2-Empilhar Rolos num Pack\n"
               "3-Anular Pack\n"
               "4-Listar Packs\n"
               "5-Fechar Pack\n"
               "0-Voltar para o menu anterior\n"
               "Opcao: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &op);
        switch(op){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                printf("Voltar ao menu anterior...");
                Prima();
                break;
            default:
                printf("Erro! Opcao invalida\n");
        }
    }while(op!=0);
}
menuexpds(ApArmazem armaz){
    int op;
    char str[STR];

    do{
        limparEcra();
        printf("Menu Expedicoes\n"
               "Escolha por favor uma das seguintes opcoes\n"
               "1-Criar Expedicao\n"
               "2-Associar Packs a uma Expedicao\n"
               "3-Remover Pack de uma Expedicao\n"
               "4-Listar Expedicoes\n"
               "5-Fechar Expedicao\n"
               "0-Voltar para o menu anterior\n"
               "Opcao: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &op);
        switch(op){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                printf("Voltar ao menu anterior...");
                Prima();
                break;
            default:
                printf("Erro! Opcao invalida\n");
        }
    }while(op!=0);
}

menuguias(ApArmazem armaz){
    int op;
    char str[STR];

    do{
        limparEcra();
        printf("Menu Guias\n"
               "Escolha por favor uma das seguintes opcoes\n"
               "1-Criar Guia\n"
               "2-Associar Expedicoes a Guia de Remessa\n"
               "3-Anular Guia de Remessa\n"
               "4-Finalizar Guia de Remessa\n"
               "5-Listar Guias de Remessa" //falta este
               "0-Voltar para o menu anterior\n"
               "Opcao: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &op);
        switch(op){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                printf("Voltar ao menu anterior...");
                Prima();
                break;
            default:
                printf("Erro! Opcao invalida\n");
        }
    }while(op!=0);
}
menu(ApArmazem armaz){
    int op;
    char str[STR];

    do{
        limparEcra();
        printf("Programa de Gestao de Empresa de Tecidos\n"
               "Escolha por favor uma das seguintes opcoes\n"
               "1-Receber Rolos\n"
               "2-Operacoes com Rolos\n"
               "3-Operacoes com Packs\n"
               "4-Expedicoes\n"
               "5-Guias\n"
               "0-Voltar para o menu anterior\n"
               "Opcao: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &op);
        switch(op){
            case 1:

                break;
            case 2:
                menurolos(armaz);
                Prima();
                break;
            case 3:
                menupacks(armaz);
                Prima();
                break;
            case 4:
                menuexpds(armaz);
                Prima();
                break;
            case 5:
                menuguias(armaz);
                Prima();
                break;
            case 0:
                printf("Saiu do Programa...");
                Prima();
                break;
            default:
                printf("Erro! Opcao invalida\n");
        }
    }while(op!=0);
}
int main(int argc, char** argv) {
    Armazem armazem;
    ApArmazem armaz=&armazem;
    menu(armaz);

    return (EXIT_SUCCESS);
}

