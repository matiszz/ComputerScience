#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int segundos=0;
void funcion_alarma(int signal)
{
	char buff[256];
	segundos=segundos+10;
	sprintf(buff,"ALARMA pid=%d: %d segundos\n",getpid(),segundos);
	write(1, buff, strlen(buff) );
}
int main (int argc,char * argv[])
{
	signal(SIGALRM,funcion_alarma);
	fork();
	while (segundos<100)
	{
		alarm(10);
		pause();
	}
	exit(1);
}
