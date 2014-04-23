/* 
 * File:   No.h
 * Author: ATP
 *
 * Created on 23 de Abril de 2014, 7:58
 */


#include "types.h"

//typedef struct no *ApNo;
typedef struct no *ApNo;

typedef struct no {
	comp elem;
	ApNo next;
}No;
