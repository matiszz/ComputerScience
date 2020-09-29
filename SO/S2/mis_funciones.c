#include "mis_funciones.h"

int mi_atoi(char *s) {
	int i, negatiu;
	int num = 0; //// FALTA PER QUAN SIGUI NEGATIU
	
	if (s[0] == '-') i = negatiu = 1;
	else i = negatiu = 0;
	
	while (s[i] != '\0') {
		num = num*10 + char2int(s[i]);
		++i;
	}
	if (negatiu) num = num * (-1);
	
	return num;
}

unsigned int char2int(char c) { // Converteix c a int
	int num;
	num = c - '0';
	return num;
}

int esNumero(char *str) { // Diu si és número.
	if (str != NULL) {
		if (str[0] != '-' && strlen(str) <= MAX_SIZE) {
			int i;
			for (i = 0; i < strlen(str); ++i) {
				if (str[i] < '0' || str[i] > '9') return 0;
			}
			return 1;
		} else {
			if (strlen(str) > MAX_SIZE+1) return 0;
			int i;
			for (i = 1; i < strlen(str); ++i) {
				if (str[i] < '0' || str[i] > '9') return 0;
			}
			return 1;
		}
	}
	return 0;
}
