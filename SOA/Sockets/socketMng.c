#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Create a socket and initialize it to be able to accept
// connections.
// It returns the virtual device associated to the socket that should be used
// in the accept system call, to get the virtual device associated to
// the connection

int createServerSocket(int port) {
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in sckt;
	sckt.sin_family = PF_INET;
	sckt.sin_addr.s_addr = INADDR_ANY;
	sckt.sin_port = htons(port);
	
	int b = bind(fd, (const struct sockaddr *)&sckt, sizeof(sckt));
	if (b < 0) {
		perror("Error en el listen\n");
		exit (0);
	}
	int l = listen(fd, 5);

	return fd;
}

// Returns the file descriptor associated to the connection.
// accept system call will fill the socketAddr parameter
// with the address of the socket for the client which is requesting the
// connection, and the addrSize parameter with the size of that address.

int acceptNewConnections(int fdSocket) {
	struct sockaddr_in cliente;
	unsigned int length = sizeof(cliente);
	int fdAccept = accept(fdSocket, (struct sockaddr *) &cliente, &length);
	return fdAccept;
}

// Returns the socket virtual device that the client should use to access
// the socket, if the connection is successfully established
// and -1 in case of error
//
// Connect system call requires the address of the
// server socket to request the connection and the size of that address.

int clientConnection(char *hostName, int port) {
	struct sockaddr_in serv_addr;
	struct hostent *hent;
	int fdSocket;
	int ret;

	//creates the virtual device for accessing the socket
	fdSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (fdSocket < 0)
		return fdSocket;

	memset((char *)&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	hent = gethostbyname(hostName);

	if (hent == NULL) {
		close(fdSocket);
		return -1;
	}
	
	memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)hent->h_addr, hent->h_length);
	serv_addr.sin_port = htons(port);
	serv_addr.sin_family = PF_INET;

	ret = connect(fdSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (ret < 0) {
		close(fdSocket);
		return (ret);
	}

	return fdSocket;
}

int deleteSocket(int fdSocket) {
	close(fdSocket);
}