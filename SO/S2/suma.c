#include "mis_funciones.h"

#define MAX_SIZE 8

int main (int argc, char *argv[]) {
	int i;
	int sum = 0;
	for (i = 1; i < argc; ++i) {
		int a = esNumero(argv[i]);
		if (a == 0){ 
			printf("%c no és número \n", *argv[i]);
			exit(0);
		} else sum += mi_atoi(argv[i]);
	}
	printf("%d \n", sum);
}
