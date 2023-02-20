#include <proto/bsdsocket.h>
#include <stdio.h>

int main()
{
	int socket = ISocket->socket(domain, type, protocol);
    if(socket < 0) {
        printf("socket creation failed\n");
        return 0;
    }

    struct sockaddr_in sa;

	// port = 2121;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(80);
	//sa.sin_addr.s_addr = INADDR_LOOPBACK;

    //bool success = true;

    struct hostent *he;

    he = gethostbyname("google.com");
    if(he == 0) {
        perror("gethostbyname");
        return 0;
    }
    char *address = (char *)&sa.sin_addr;
    address[0] = he->h_addr_list[0][0];
    address[1] = he->h_addr_list[0][1];
    address[2] = he->h_addr_list[0][2];
    address[3] = he->h_addr_list[0][3];

    int connectResult = ISocket->connect (socket, (struct sockaddr *)&sa, sizeof(sa));
    if(connectResult < 0) {
        printf("connect failed\n");
    }

    close(socket);

    return 0;
}