#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
	
	int pid;
	int i;
	
	for (i=0; i<argc; ++i) {
		pid=fork();
		
		if (pid==0) {
			printf("HIJO: Soy el proceso %d. El parámetro es %s\n", getpid(), argv[i]);
			exit(0);
		}
		
		waitpid(pid);
	}
	
	return 0;
}
