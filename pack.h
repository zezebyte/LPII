/* 
 * File:   pack.h
 * Author: sos
 *
 * Created on 23 de Abril de 2014, 14:10
 */

#include "stack.h"

typedef struct{
    int dia, mes, ano;
}Data;

typedef struct{
    char codigo[7];
    Data data;
    Stack pilharolos;
    int open; 
}Pack;
