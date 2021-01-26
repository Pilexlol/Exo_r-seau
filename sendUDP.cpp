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

int main ()
{
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

SOCKET sock;

sock = socket(AF_INET,SOCK_DGRAM,0);

fprintf(stderr,"socket() message :%s\n", strerror(errno));

SOCKADDR_IN destAddrUdp;
	destAddrUdp.sin_addr.s_addr = inet_addr("192.168.65.23");
	destAddrUdp.sin_family = AF_INET;
	destAddrUdp.sin_port = htons(9012);

char buffer[3];
buffer[0] ='O';
buffer[1] ='U';
buffer[2] ='I';

socklen_t tailleudp = sizeof(destAddrUdp);
int octet_message;
octet_message = sendto(sock,buffer,sizeof(buffer),0,(SOCKADDR*)&destAddrUdp,sizeof(destAddrUdp));

if(octet_message == 0){
fprintf(stderr,"sendto message erreur : %s\n", strerror(errno));
}
close(sock);

return 0;
}
