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


	int error_message;
	error_message = ::bind(sock, (SOCKADDR*)&InfoServer, sizeof(InfoServer));

	char buffer[1500];
	memset(buffer, '\0', 1500);
	sockaddr_in _from;
	socklen_t fromlen = sizeof(_from);
	error_message = recvfrom(sock, buffer, 1500, 0,
		reinterpret_cast<sockaddr*>(&_from), &fromlen);
	if (error_message < 1) {
		fprintf(stderr, "socket() message: %s\n", strerror(errno));
	}
	else {
		printf(" IP : %s ", inet_ntoa(_from.sin_addr));
		printf(" Port : %d ", ntohs(_from.sin_port));
		printf("Reçu : %s ", buffer);
	}

		return 0;
	}
