#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char buf[256];
	
	int fdr = open("file.txt", O_RDONLY);
	int fdw = open("file.txt", O_WRONLY);
	int size = lseek(fdr, 0, SEEK_SET);
	lseek(fdw, 0, SEEK_END);
	
	int i = 0;
	while (i < size) {
		int leido = read(fdr, buf, sizeof(buf));
		write(fdw, buf, strlen(buf));
		i = lseek(fdr, leido, SEEK_SET);
	}
}
