all: serverSocket clientSocket launchClient serverUnbounded serverBounded extraBonusServer

launchClient: launchClient.c
	gcc -o launchClient launchClient.c

serverSocket: serverSocket.c socketMng.o
	gcc -o serverSocket -g serverSocket.c socketMng.o

serverUnbounded: serverUnbounded.c socketMng.o
	gcc -o serverUnbounded -g serverUnbounded.c socketMng.o

serverBounded: serverBounded.c socketMng.o
	gcc -o serverBounded -g serverBounded.c socketMng.o
	
extraBonusServer: extraBonusServer.c socketMng.o
	gcc -pthread -o extraBonusServer -g extraBonusServer.c socketMng.o

clientSocket: clientSocket.c socketMng.o
	gcc -o clientSocket -g clientSocket.c socketMng.o

socketMng.o: socketMng.c
	gcc -c -g socketMng.c

clean: 
	rm -f serverSocket clientSocket socketMng.o launchClient serverUnbounded serverBounded extraBonusServer

cleanLaunch:
	rm -f client_* launch_info
