#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* ESTE PROCESO SE PROGRAMA UN TEMPORIZADOR PARA  DENTRO DE 50 SEGUNDOS Y SE BLOQUEA A ESPERAR QUE LLEGUE */
/* LA ACCION POR DEFECTO DEL SIGALRM ES ACABAR EL PROCESO */
int main (int argc,char * argv[])
{
	alarm(5);
	pause();
	exit(1);
}
