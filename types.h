#include "stack.h"
#define STRG 80
#define MAX 100

typedef struct armazem *ApArmazem;
typedef struct no *ApNo;

typedef struct{
    int dia, mes, ano;
}Data;

typedef struct{
    char codigo[7];
    Data data;
    Stack pilharolos;
    int open;
}Pack;

typedef struct{
    char codigo[10], descr[STRG];
    int enc, qualid;
    float comp;
}Rolo;

typedef struct armazem{
    Rolo rolosarmazem[MAX];
    Pack packsarmazem[MAX];
    int cont_rolos;
    int cont_packs;
}Armazem;

typedef struct no {
	comp elem;
	ApNo next;
}No;

typedef Rolo comp;


