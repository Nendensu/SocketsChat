#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void raise_error(const char *msg);

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    char name[256], buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    
    int check; // Var for check functinos return

    if(argc < 2) {
        raise_error("No port provided");
    }
     
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        raise_error("Opening socket");
    }
     
    bzero(&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    if(portno < 1 || portno > 65535)
    {
        raise_error("Incorrect port number");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
     
    check = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if(check < 0) { 
        raise_error("On binding");
    }

    printf("\033[0;32m---> Starting server at port %d\033[0m\n", portno);
    fflush(stdout);

    listen(sockfd, 5);

    socklen_t cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if(newsockfd < 0) { 
        raise_error("On accept");
    }

    printf("\033[0;32m---> Accepting connecting from %s\033[0m\n", inet_ntoa(cli_addr.sin_addr));
    fflush(stdout);

    bzero(name, 256);
    check = read(newsockfd, name, 255);
    if(check < 0) { 
	    raise_error("Reading from socket");
    }


    check = write(newsockfd, "I got your name", 15);
    if(check < 0) { 
	    raise_error("Writing to socket");
    }
    
    while(1) {
        bzero(buffer, 1024);
     	check = read(newsockfd, buffer, 1023);
     	if(check < 0) { 
	        raise_error("Reading from socket");
     	}

     	printf("Here is the message from %s: %s\n", name, buffer);
     	
        check = write(newsockfd, "I got your message", 18);
     	if(check < 0) { 
	        raise_error("Writing to socket");
     	}
     }
     
     close(newsockfd);
     close(sockfd);
     
     return 0; 
}

void raise_error(const char *msg) {
    fprintf(stderr, "\033[0;31m==> ERROR: %s \033[0m\n", msg);

    exit(1);
}
