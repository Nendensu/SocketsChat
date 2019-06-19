#include "serv_lib.h"

int main(int argc, char *argv[]) 
{
    int sockfd;
    int portnum;
    struct sockaddr_in serv_addr;
    
    int check; // Var for check functinos return

    if(argc < 2) 
    {
        raise_error("No port provided");
    }
     
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) 
    {
        raise_error("Opening socket");
    }
     
    memset(&serv_addr, 0, sizeof(serv_addr));
    portnum = (int) strtol(argv[1], NULL, 10);
    if(portnum < 1 || portnum > 65535)
    {
        raise_error("Incorrect port number");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portnum);
     
    check = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if(check < 0) 
    { 
        raise_error("On binding");
    }

    printf("\033[0;32m---> Starting server at port %d\033[0m\n", portnum);
    fflush(stdout);

    while(1)
    {
        check = listen(sockfd, MAX_CONNECTIONS);
        if(check < 0)
        {
            raise_error("While listening socket");
        }

        new_connection(sockfd);
    }

    // Add exit command
    //close(sockfd);
     
    return 0; 
}
