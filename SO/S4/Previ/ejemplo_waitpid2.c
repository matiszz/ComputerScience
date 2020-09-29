#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define FIN_BUCLE 50000000ULL


void hago_algo_util()
{
unsigned long long  i;


	for (i = 0; i < FIN_BUCLE; i++);


}


void trata_alarma(int s) 
{

}


int main(int argc,char *argv[])
{
	int pid,res;
	char buff[256];		
	int hijos=0;

	for (hijos=0;hijos<10;hijos++)
	{
		sprintf(buff, "Creando el hijo numero %d\n", hijos);
		write(1, buff, strlen(buff)); 
		
		pid=fork();
		if (pid==0) /* Esta linea la ejecutan tanto el padre como el hijo */
		{
			signal (SIGALRM, trata_alarma);
			/* Escribe aqui el codigo del proceso hijo */
			sprintf(buff,"Hola, soy %d\n",getpid());
			write(1, buff, strlen(buff)); 

			alarm(1); 
			pause();

			/* Termina su ejecución */
			exit(0);
		}else if (pid<0)	
		{
			/* Se ha producido un error */
			perror("Error en el fork");
		}
	}

	hago_algo_util();


	/* Esperamos que acaben el resto de  hijos */
	while ((pid=waitpid(-1,&res,0)) > 0) 
	{
		sprintf(buff,"Waitpid bloqueante. Termina %d\n",pid);
		write(1, buff, strlen(buff)); 
	}
	return 0;
}
