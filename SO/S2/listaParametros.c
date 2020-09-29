#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

void usage(int args) {
	char b[127];
	if (args == 1) {
		sprintf(b,"Este programa escribe los argumentos que recibe. Por favor, introduce algún parámetro.\n");
		write(1,b,strlen(b));
	}
	exit(0);
}

int main(int argc,char *argv[]) {
	char buf[80];
	usage(argc);	
	int i;
	for (i=0;i<argc;i++){
		if (i==0){
			sprintf(buf,"El argumento %d es %s (es el nombre del ejecutable)\n",i,argv[i]);
		}else{
			sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
		}
		write(1, buf, strlen(buf));
	}
	return 0;
}
