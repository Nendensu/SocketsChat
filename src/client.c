#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void raise_error(const char *msg);

int main(int argc, char *argv[])
{
    int sockfd, portnum;
    char buffer[1024];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    int check; // Var for check functions return

    if(argc < 3) 
    {
        raise_error("No port or hostname provided");
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) 
    {
        raise_error("Opening socket");
    }

    portnum = atoi(argv[2]);
    if(portnum < 1 || portnum > 65535)
    {
        raise_error("Incorrect port number");
    }
    
    server = gethostbyname(argv[1]);
    if(server == NULL) 
    {
        raise_error("No such host");
    }
    
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portnum);
    
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    {
        raise_error("Can't connection to the destanation host");
    }

    printf("\033[0;32m---> Successfully connect to the %s on port %d\033[0m\n", argv[1], portnum);
    fflush(stdout);
    
    printf("Please enter your name: ");
    fflush(stdout);

    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    strtok(buffer, "\n");
    
    check = write(sockfd, buffer, strlen(buffer));
    if(check < 0)
    {
        raise_error("Writing to socket");
    }
    
    bzero(buffer, 1024);

    check = read(sockfd, buffer, 1023);
    if (check < 0) 
    {
        raise_error("Reading from socket");
    }
        
    printf("\033[0;33m%s\033[0m\n", buffer);
    fflush(stdout);

    while(1) 
    {
        printf("Please enter the message: ");
        fflush(stdout);
        
        bzero(buffer, 1024);
        fgets(buffer, 1023, stdin);
        strtok(buffer, "\n");
        
        check = write(sockfd, buffer, strlen(buffer));
        if (check < 0) 
        {
            raise_error("Writing to socket");
        }
        
        bzero(buffer, 1024);

        check = read(sockfd, buffer, 1023);
        if (check < 0) 
        {
            raise_error("Reading from socket");
        }
        
        printf("%s\n", buffer);
        fflush(stdout);
    }

    close(sockfd);

    return 0;
}

void raise_error(const char *msg) 
{
    fprintf(stderr, "\033[0;31m==> ERROR: %s \033[0m\n", msg);
    fflush(stderr);
    
    exit(1);
}
