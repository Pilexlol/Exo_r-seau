#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

int main()
{

	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;

	SOCKADDR_IN InfoServer;
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	InfoServer.sin_addr.s_addr = htonl(INADDR_ANY);
	InfoServer.sin_family = AF_INET;
	InfoServer.sin_port = htons(9012);
	printf("Listage du port %d...\n", 9012);

	int resultat;
	int error_message;
	error_message = ::bind(sock, (SOCKADDR*)&InfoServer, sizeof(InfoServer));
	int i;
	int j,a,b,c;
	char buffer[1500];
	memset(buffer, '\0', 1500);
	sockaddr_in _from;
	socklen_t fromlen = sizeof(_from);
	error_message = recvfrom(sock, buffer, 1500, 0,reinterpret_cast<sockaddr*>(&_from), &fromlen);

	if (error_message < 1) {
		fprintf(stderr, "socket() message: %s\n", strerror(errno));
	}
	else {

		for (i = 0; i < strlen(buffer) ; i++)
		{
			printf("Valeur Recu : %d \n ", buffer[i] -48);
			i++;
		}	
	 
		for (i = 0; i < strlen(buffer); i++)
		{
			for (j = 0; j < strlen(buffer); j++)
			{
					
					a = buffer[j++]-48;
					b = buffer[i]-48;
					c = a + b;
					resultat = c;
				j++;
		}
			
		}
		printf("Resultat %d \n", resultat);
	}



		return 0;
	}
