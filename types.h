#ifndef TYPES_H_
#define TYPES_H_

#define STRG 80
#define MAX 100

typedef struct armazem* ApArmazem;
typedef struct stack* pStack;
typedef struct queue* pQueue;
typedef struct no* ApNo;
typedef struct rolo comp;

typedef struct queue {
	ApNo head;
	ApNo tail;
} Queue;

typedef struct stack {
	ApNo top;
} Stack;

typedef struct data{
    int dia, mes, ano;
}Data;

typedef struct pack{
    int codigo;
    Data data;
    Stack pilharolos;
    int open;
}Pack;

typedef struct rolo{
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

#endif	/* TYPES_H_ */
