#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[]) {
	
	int pid=fork();
	
	switch (pid) {
		case 0: 
			printf("HIJO: Soy el proceso %d. El parámetro es %s\n", getpid(), argv[1]);
			break;
		case -1:
			printf("Ha surgido un error\n");
			break;
		default:
			printf("PADRE: Soy el proceso %d\n", getpid());
			break;
	}
	
	while(1);
	
	return 0;
}
