#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void trat_sigusr1(int s) {
char buf[80];

sprintf(buf, "Ready for dead.... \n");
write(1, buf,strlen(buf));
}

void trat_sigalrm(int s) {
char buf[80];

sprintf(buf, "Voy a mandar sigusr1 \n");
write(1, buf,strlen(buf));
}

main(int argc, char *argv[]) {
int i,pid_h;
char buf [80];
int alarma;


if (argc !=2) {
	sprintf(buf, "Usage: %s retardoPadre \n retardoPadre: 0|1\n",argv[0]);
	write(2,buf,strlen(buf));
	exit(1);
}

alarma = atoi(argv[1]);
signal (SIGUSR1, trat_sigusr1);
signal (SIGALRM, trat_sigalrm);

pid_h = fork ();

if (pid_h == 0) {
	sprintf(buf, "Hijo entrando al pause\n");
	write(1,buf,strlen(buf));
	pause();
	sprintf(buf, "Hijo saliendo del pause\n");
	write(1,buf,strlen(buf));

} else {
	if (alarma) {
		alarm(5);
		pause();
	}
	sprintf(buf, "Padre mandando signal\n");
	write(1,buf,strlen(buf));
	kill (pid_h, SIGUSR1);
	waitpid(-1, NULL, 0);
	sprintf(buf, "Padre saliendo del wait\n");
	write(1,buf,strlen(buf));
} 


}

