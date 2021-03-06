#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "MensajeError.c"

#define TAMBUFER 2000

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	if (argc < 3|| argc >4)
		mensajeFinalError("Uso: EcoTCPCliente <Direcci�n del servidor> <Palabra de eco> [<Puerto>]");
	char *servIP = argv[1];
	char *cadenaEco = argv[2];
	int puerto = (argc == 4) ? argv[3] : 7;
	
	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s < 0){
		mensajeFinalError("Error de apertura de puerto");
	}
	struct sockaddr_in dirServ;
	memset(&dirServ,0,sizeof(dirServ));
	dirServ.sin_family = AF_INET;
	int valRet = inet_pton(AF_INET, servIP,&dirServ.sin_addr.s_addr);
	if(valRet == 0)
		mensajeFinalError("Direcci�n del servidor erronea");
	else if(valRet < 0)
		mensajeFinalError("Error en el inet_pton()");
	dirServ.sin_port = htons(puerto);
	
	//Establecemos la comunicaci�n con el servidor de eco
	if(connect(s, (struct sockaddr*) &dirServ,sizeof(dirServ))<0)
		mensajeFinalError("Error en la conexi�n");
	size_t longCadenaEco = strlen(cadenaEco);
	
	//Envia el mensaje al servidor
	ssize_t numBytes = send(s,cadenaEco,longCadenaEco, 0);
	if(numBytes< 0)
		mensajeFinalError("Fallo el envio");
	else if(numBytes != longCadenaEco)
		mensajeFinalError("N�mero de bytes enviados erroneo");
	
	//Recibimos de vuelta la cadena desde el servidor
	unsigned int totalBytesRec = 0;
	fputs("Recibido: ",stdout);
	while(totalBytesRec < longCadenaEco){
		char buffer[TAMBUFER];
		numBytes = recv(s,buffer,TAMBUFER - 1, 0);
		if(numBytes<0)
			mensajeFinalError("Recepci�n fallida");
		else if(numBytes==0)
			mensajeFinalError("Conexi�n cerrada prematuramente");
		totalBytesRec += numBytes;
		buffer[numBytes] = '\0';
		fputs(buffer,stdout);
	}
	fputs((const char*)'\0',stdout);
	
	close(s);
	return 0;
}
