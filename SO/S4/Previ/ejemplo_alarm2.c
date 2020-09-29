#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>


/* ESTA VARIABLE SE ACCEDE DESDE LA FUNCION DE ATENCION AL SIGNAL Y DESDE EL MAIN */
int segundos=0;
/* FUNCION DE ATENCION AL SIGNAL SIGALRM */
void funcion_alarma(int s)
{
char buff[256];
	segundos=segundos+10;
	sprintf(buff, "ALARMA pid=%d: %d segundos\n",getpid(),segundos);
	write(1, buff, strlen(buff)); 
}
int main (int argc,char * argv[])
{
	/* REPROGRAMAMOS EL SIGNAL SIGALRM */
	signal(SIGALRM,funcion_alarma);
	while (segundos<100)
	{
		alarm(10); 	/* Programamos la alarma para dentro de 10 segundos */
		pause();  	/* Nos bloqueamos a esperar que nos llegue un evento */
	}
	exit(1);
}
