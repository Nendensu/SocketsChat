#include "serv_lib.h"

void raise_error(const char *msg)
{
    fprintf(stderr, "\033[0;31m==> ERROR: %s \033[0m\n", msg);
    fflush(stderr);

    exit(1);
}

void disconnect(const char *name)
{
    fprintf(stdout, "\033[0;33m---> User %s was disconnected \033[0m\n", name);
    fflush(stdout);
}

int response(int newsockfd, const char *name)
{
    int check; // Var for check functions return

    const char *response = "I've got your message"; // response from server
    
    check = write(newsockfd, response, strlen(response));
    if(check < 0) 
    { 
        disconnect(name);

        return -1;
    }

    return 0;
}

void chat(int newsockfd, const char *name)
{
    char buffer[BUFFER_SIZE];

    int check; // Var for check functions return

    while(1) 
    {
        memset(buffer, 0, BUFFER_SIZE);
     	check = read(newsockfd, buffer, BUFFER_SIZE - 1);
     	if(check < 1) 
        { 
            disconnect(name);

            break;
     	}

     	fprintf(stdout, "Here is the message from %s: %s\n", name, buffer);
        fflush(stdout);

        check = response(newsockfd, name);
        if(check < 0)
        {
            break;
        }
    }
    
    pthread_exit(0);
    close(newsockfd);
}

void *set_name(void *sockfd)
{
    const char *hello = "Hello, "; // Part of hello string from server
   
    char *name;
    int *newsockfd;

    int check; // Var for check functions return

    newsockfd = (int *) sockfd;

    name = (char *) malloc(NAME_SIZE);
    memset(name, 0, NAME_SIZE);
    check = read(*newsockfd, name, NAME_SIZE - 1);
    if(check < 0) 
    { 
	    raise_error("Reading from socket");
    }

    char *hello_string = (char *) malloc(strlen(hello) + strlen(name) + 1);
    strncpy(hello_string, hello, strlen(hello));
    strncat(hello_string, name, strlen(name));

    check = write(*newsockfd, hello_string, strlen(hello_string));
    if(check < 0) 
    { 
	    raise_error("Writing to socket");
    }
    free(hello_string);

    fprintf(stdout, "\033[0;32m---> User login as %s\033[0m\n", name);
    fflush(stdout);

    chat(*newsockfd, name);
}

void new_connection(int sockfd)
{
    int newsockfd;
    struct sockaddr_in cli_addr;
    pthread_t tid;

    socklen_t cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if(newsockfd < 0) 
    { 
        raise_error("On accept");
    }

    fprintf(stdout, "\033[0;32m---> Accepting connecting from %s\033[0m\n", inet_ntoa(cli_addr.sin_addr));
    fflush(stdout);

    pthread_create(&tid, NULL, set_name, (void *)&newsockfd); 
    pthread_detach(tid);
}
