/* 
 * File:   main.c
 * Author: ATP
 *
 * Created on 22 de Abril de 2014, 17:57
 */

#include "uteis.h"
#include "armazem.h"
#include "queue.h"
#include "stack.h"
/*
 * 
 */

void MenuPacks(){
    int op;
    char str[STRG];
    
    do{
    	op = -1;
        limparEcra();
        printf("Menu Packs\n"
                "\n"
               "Escolha por favor uma das seguintes opcoes:\n"
               "1-Criar Pack\n"
               "2-Empilhar Rolos num Pack\n"
               "3-Anular Packs\n"
               "4-Listar Packs\n"
               "5-Fechar Pack\n"
               "0-Voltar ao menu anterior\n"
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
                printf("Voltar ao menu anterior\n");
                break;
            default:
                printf("Erro! Opcao Invalida!\n");
        }
    }while(op!=0);
}
void MenuRolos(){
    int op;
    char str[STRG];
    
    do{
    	op = -1;
        limparEcra();
        printf("Menu Rolos\n"
                "\n"
               "Escolha por favor uma das seguintes opcoes:\n"
               "1-Remover Rolo do Armazem\n"
               "2-Alterar informacao de rolo\n"
               "3-Listar Rolos no Armazem\n"
               "0-Voltar ao menu anterior\n"
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
                printf("Voltar ao menu anterior\n");
                break;
            default:
                printf("Erro! Opcao Invalida!\n");
        }
    }while(op!=0);
}
void Menu(){
    int op;
    char str[STRG];
    
    do{
    	op = -1;
        limparEcra();
        printf("Programa de Gestao de Empresa de Tecidos\n"
                "\n"
               "Escolha por favor uma das seguintes opcoes:\n"
               "1-Receber Rolos\n"
               "2-Operacoes com Rolos\n"
               "3-Operacoes com Packs\n"
               "0-Sair\n"
               "Opcao: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &op);
        switch(op){
            case 1:
                break;
            case 2:
                MenuRolos();
                Prima();
                break;
            case 3:
                break;
            case 0:
                printf("Saiu do Programa\n");
                break;
            default:
                printf("Erro! Opcao Invalida!\n");
                Prima();
        }
    }while(op!=0);
}


int main(int argc, char** argv) {
    Armazem armazem;
    ApArmazem armaz=&armazem;
    Queue rolos;
    pQueue ap_rolos=&rolos;
    
    InitArm(armaz);
    NewQ(ap_rolos);
    
    Menu();
    Prima();
    return EXIT_SUCCESS;
}
