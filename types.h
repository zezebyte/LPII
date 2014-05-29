#ifndef TYPES_H_
#define TYPES_H_

#define STRG 80
#define MAXSTACK 0
#define MAXQUEUE 20
#define MAXLLIST 0

typedef struct linkedlist* ApLista;
typedef struct armazem* ApArmazem;
typedef struct stack* ApStack;
typedef struct queue* ApQueue;
typedef struct no* ApNo;

typedef struct queue {
	ApNo head;
	ApNo tail;
} Queue;

typedef struct stack {
	ApNo top;
} Stack;

typedef struct linkedlist {
	ApNo head;
	int cont;
} LinkedList;

typedef struct data {
	int dia, mes, ano;
} Data;

typedef struct guia {
	int num, cliente;
	LinkedList expds;
} Guia;

typedef struct expedicao {
	int enc, open;
	LinkedList packs;
} Expd;

typedef struct pack {
	int codigo;
	Data data;
	Stack pilharolos;
	int open;
} Pack;

typedef struct rolo {
	char codigo[10], descr[STRG];
	int enc, qualid;
	float comp;
} Rolo;

typedef struct armazem {
	LinkedList rolos;
	LinkedList packs;
	LinkedList expds;
	LinkedList guias;
} Armazem;

typedef union componente {
	Rolo rolo;
	Pack pack;
	Expd expd;
	Guia guia;
} comp;

typedef struct no {
	comp elem;
	ApNo next;
} No;

#endif	/* TYPES_H_ */
