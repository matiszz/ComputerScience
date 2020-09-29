#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void lee_y_escribe(int f0, int fd, int toRead) {
	char buf[50];
	while(toRead > 0) {
		int nbytes = read(f0, buf, (toRead < sizeof(buf) ? toRead : sizeof(buf)));
		toRead = toRead - nbytes;
		write(fd, buf, nbytes);
	}
}

// Escribir un caracter en una posicion dada.
int main (int argc, char *argv[]) {
	int f0 = open(argv[1], O_RDONLY);
	int f1 = open("file1.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	int f2 = open("file2.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);

	int size = lseek(f0, 0, SEEK_END); // Me pongo al final, para conseguir el tamaño.
	
	int toRead = ((size%2) ? (size/2)+1 : size/2);
	lseek(f0, 0, SEEK_SET); // Me vuelvo a poner al principio. 
	
	lee_y_escribe(f0, f1, toRead);

	toRead = size/2;
	lee_y_escribe(f0, f2, toRead);

	exit(0);
}