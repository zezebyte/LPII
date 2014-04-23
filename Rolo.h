/* 
 * File:   Rolo.h
 * Author: sos
 *
 * Created on 23 de Abril de 2014, 14:35
 */

#define STRG 80

typedef struct{
    char codigo[10], descr[STRG];
    int enc, qualid;
    float comp;
}Rolo;
