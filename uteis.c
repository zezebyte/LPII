#ifdef _WIN32
#define CLEAR "cmd /c cls"
#else
#define CLEAR "clear"
#endif
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define STRG 80
#define MAX 100

void limparEcra() {       //funcao para limpar o ecra
	system(CLEAR);
}

void Prima() {       //funcao de espera
	printf("\nPrima ENTER para continuar...\n");
	getchar();
}

void sleep(long m) {
	clock_t limit, cl = clock();
	limit = cl + m;
	while(limit > cl)
		cl = clock();
}
