#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void error(int number);
void* dialog(void *sockfd);

/**
 * Error codes:
 * 0 - no port provided
 * 1 - error opening socket
 * 2 - error on binding
 * 3 - error creating thread
 * */

int main(int argc, char** argv) {
    int sockfd, newsockfd, portno, thread_number;
    socklen_t *clilen;
    struct sockaddr_in serv_addr, *cli_addr;
    pthread_t threads[100];

    if(argc < 2) {
        error(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    thread_number = 0;

    if(sockfd < 0) {
        error(1)
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error(2);
    }

    while(1) {
        listen(sockfd, 5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (pthread_create(&threads[thread_number], NULL, dialog, &newsockfd)) {
            error(3);
        }
    }

    return 0;
}

void error(int error_code) {
    switch(error_code) {
        case 0:
            fprintf(stderr, "ERROR: no port provided\n");
            break;
        case 1:
            fprintf(stderr, "ERROR: error opening socket\n");
            break;
        case 2:
            fprintf(stderr, "ERROR: error on binding\n");
            break;
        case 3:fprintf(stderr, "ERROR: error creating thread\n");
            break;
        case 4:
            fprintf(stderr, "ERROR: \n");
            break;
        case 5:
            fprintf(stderr, "ERROR: \n");
            break;
        case 6:
            fprintf(stderr, "ERROR: \n");
            break;
        default:
            fprintf(stderr, "ERROR: unexpected error\n");
            break;
    }
    exit(1);
}

void* dialog(void *sockfd) {
    int n;
    int *newsockfd = (int *)sockfd;
    char bufer[256];


    while(1) {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);

        if (n < 0) {
            error("ERROR reading from socket");
        }

        printf("Here is the message: %s", buffer);
        n = write(newsockfd, "I got your message", 18);

        if (n < 0) {
            error("ERROR writing to socket");
        }
    }
}