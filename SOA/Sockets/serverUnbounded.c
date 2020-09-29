#include <stdlib.h>
#include <string.h>
#include <stdio.h>

doServiceFork(int fd) {
	int pid = fork();
	if (pid < 0) {
		perror("Error al hacer fork");
		exit(1);
	} else if (pid == 0) {
		doService(fd);
		exit(0);
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

	if (argc != 2) {
		strcpy (buffer, "Uso: serverUnbounded numeroDePuerto\n");
		write (2, buffer, strlen (buffer));
		exit (1);
	}

	port = atoi(argv[1]);
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
