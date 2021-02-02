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
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main()
{
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif

    SOCKET sock;
    SOCKADDR_IN sin;
    SOCKET csock;
    SOCKADDR_IN csin;
    char buffer[32] = "Ping du client!";
    char bufferClient[50] = { 0 };
    int sockBind_err;
    int sockSend_err;
    int sockRecv_err;
    int PORT = 9012;
	socklen_t size = sizeof(csin);

    if (!erreur)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock != INVALID_SOCKET)
        {
            printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

            sin.sin_addr.s_addr = htonl(INADDR_ANY);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(PORT);

            sockBind_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));

            if (sockBind_err != SOCKET_ERROR)
            {
                printf("Attendez que le client se connecte %d...\n", PORT);
                listen(sock, 6);
                csock = accept(sock, (SOCKADDR*)&csin, &size);
                printf("Le client est connecter sur le port a l'adresse : %d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

                sockRecv_err = recv(csock, &bufferClient, sizeof(bufferClient), 0);

                if (sockRecv_err == -1)
                {
                    printf("erreur lors de la reception du message client");
                }
                else
                {
                    printf("Chaine reçu : %s\n", bufferClient);
                }

                sockSend_err = send(csock, buffer, 32, 0);

                if (sockSend_err != SOCKET_ERROR)
                {
                    printf("Donnes envoye : %s\n", buffer);
                }
                else
                {
                    printf("Erreur de transmission\n");
 
                    shutdown(csock, 2);
                }
            }
            else
            {
                
            }

            printf("Fermeture de la socket...\n");
            close(sock);
            printf("Serveur eteinds\n");
        }
        else
        {
            printf("Impossible de créer la socket");
        }

         #if defined (WIN32)
            WSACleanup();
        #endif
    }
}
