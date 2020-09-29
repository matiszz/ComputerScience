#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 8

int esNumero(char *str) {
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

int main (int argc, char *argv[]) {
	int i;
	for (i = 1; i < argc; ++i) {
		int a = esNumero(argv[i]);
		if (a == 0) printf("[X] No és número \n");
		else printf("[V] És un numero \n");
	}
}
