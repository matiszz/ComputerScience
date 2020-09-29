#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int MAX_FORKS;
int forksActual;

doServiceFork(int fd) {
	if (forksActual > MAX_FORKS)
		printf("Server no pot acceptar més connexions\n");
	else {
		forksActual++;
		printf("-> He fet %d fork\n", forksActual);
		int pid = fork();

		if (pid < 0) {
			perror("Error al hacer fork");
			exit(1);
		} else if (pid == 0) {
			doService(fd);
			exit(0);
		}
		waitpid(pid);
		forksActual--;
		printf("-> He matat al servidor, hi ha %d forks\n", forksActual);
	}
}

doService(int fd) {
	int i = 0;
	char buff[80];
	char buff2[80];
	int ret;
	int fdSocket = (int) fd;

	ret = read(fdSocket, buff, sizeof(buff));

	while (ret > 0) {
		buff[ret] = '\0';
		sprintf(buff2, "El servidor [%d] ha recibido: %s\n", getpid(), buff);
		write(1, buff2, strlen(buff2));
		ret = write(fd, "caracola ", 8);

		if (ret < 0) {
			perror ("Error escribiendo en el socket");
			exit(1);
		}

		ret = read(fdSocket, buff, sizeof(buff));
	}

	if (ret < 0) perror ("Error leyendo del socket");

	sprintf(buff2, "El servidor [%d] finaliza el servicio\n", getpid());
	write(1, buff2, strlen(buff2));
}


main (int argc, char *argv[]) {
	int socketFD;
	int connectionFD;
	char buffer[80];
	int ret;
	int port;

	if (argc != 3) {
		strcpy (buffer, "Uso: serverUnbounded numeroDePuerto MAX_FORKS\n");
		write (2, buffer, strlen (buffer));
		exit (1);
	}

	port = atoi(argv[1]);
	MAX_FORKS = atoi(argv[2]);
	forksActual = 0;
	socketFD = createServerSocket (port);

	if (socketFD < 0) {
		perror ("Error al crear el socket\n");
		exit (1);
	}

	while (1) {
		connectionFD = acceptNewConnections (socketFD);

		if (connectionFD < 0) {
			perror ("Error estableciendo la conexión\n");
			deleteSocket(socketFD);
			exit (1);
		}
		doServiceFork(connectionFD);
	}

}
