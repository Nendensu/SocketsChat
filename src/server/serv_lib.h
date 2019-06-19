#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h> 

#define BUFFER_SIZE 1024
#define NAME_SIZE 256

struct arg_struct
{
    int *arg1;
    char* arg2;
};

void raise_error(const char *msg) 
{
    fprintf(stderr, "\033[0;31m==> ERROR: %s \033[0m\n", msg);
    fflush(stderr);

    exit(1);
}

void responce(const int *newsockfd)
{
    int check; // Var for check functions return

    const char *responce = "I've got your message"; // Responce from server
    
    check = write(*newsockfd, responce, strlen(responce));
    printf("%d", check);
    if(check < 0) 
    { 
	    raise_error("Writing to socket");
    }
}

void *chat(void *arg)
{
    char buffer[BUFFER_SIZE];

    struct arg_struct *args = (struct arg_struct *) arg;
    const int *newsockfd = (int *) args->arg1;
    char *name = (char *) malloc(sizeof(args->arg2));
    strcpy(name, args->arg2);

    int check; // Var for check functions return

    while(1) 
    {
        bzero(buffer, BUFFER_SIZE);
     	check = read(*newsockfd, buffer, BUFFER_SIZE - 1);
     	if(check < 0) 
        { 
	        raise_error("Reading from socket");
     	}

     	printf("Here is the message from %s: %s\n", name, buffer);

        responce(newsockfd);
    }
    
    close(*newsockfd);
}

void new_connection(const int *sockfd)
{
    const char *hello = "Hello, "; // Part of hello string from server
   
    int newsockfd;
    char name[NAME_SIZE];
    struct sockaddr_in cli_addr;
    pthread_t tid;
    struct arg_struct args;

    int check; // Var for check functions return

    socklen_t cli_len = sizeof(cli_addr);
    newsockfd = accept(*sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if(newsockfd < 0) 
    { 
        raise_error("On accept");
    }

    printf("\033[0;32m---> Accepting connecting from %s\033[0m\n", inet_ntoa(cli_addr.sin_addr));
    fflush(stdout);

    bzero(name, NAME_SIZE);
    check = read(newsockfd, name, NAME_SIZE - 1);
    if(check < 0) 
    { 
	    raise_error("Reading from socket");
    }

    char *hello_string = (char *) malloc(strlen(hello) + strlen(name) + 1);
    strcpy(hello_string, hello);
    strcat(hello_string, name);

    check = write(newsockfd, hello_string, strlen(hello_string));
    if(check < 0) 
    { 
	    raise_error("Writing to socket");
    }

    printf("\033[0;32m---> User login as %s\033[0m\n", name);

    args.arg1 = &newsockfd;
    args.arg2 = name;

    pthread_create(&tid, NULL, chat, (void *)&args); 
    pthread_detach(tid);
}
