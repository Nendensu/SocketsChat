#ifndef SERV_LIB_H
#define SERV_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define NAME_SIZE 256
#define MAX_CONNECTIONS 10

void raise_error(const char *); 

void disconnect(const char *);

int response(int, const char *);

void chat(int, const char *);

void *set_name(void *);

void new_connection(int);

#endif
