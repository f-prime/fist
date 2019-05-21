#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "indexer.h"
#include "hashmap.h"
#include "server.h"
#include "dstring.h"

// Commands

#define INDEX "INDEX"
#define SEARCH "SEARCH"

// Responses

#define INDEXED "INDEXED"
#define NOT_FOUND "[]"

hashmap * handle_connection(int new_socket, hashmap *hm) {  
    while(1) {
        dstring req = dempty();
        while(dindexof(req, '\n') == -1 || dindexof(req, '\r') == -1) {
            char buffer[1025]; // Need to preserve the last character being a null character
            memset(buffer, 0, 1025);
            recv(new_socket, buffer, 1024, 0); // Only fill 1024 of the 1025 bytes
            req = dappend(req, buffer);
        }
        
        dstring trimmed = dtrim(req);
        dstringa commands = dsplit(trimmed, ' ');
        printf("%d %s\n", req.length, trimmed.text); 
        if(dequals(req, dcreate("exit")))
            break;
    }
    close(new_socket);
    return hm;
}

void start_server(char *host, int port) {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == 0) {
        printf("Could not create socket\n");
        exit(1);
    }
    int opt = 1;

    if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
       perror("Problem setting sockopts");
       exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if(bind(socket_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Couldn't bind");
        exit(EXIT_FAILURE);
    }

    if(listen(socket_fd, 5) < 0) {
        perror("Couldn't listen");
        exit(EXIT_FAILURE);
    }

    printf("Spear started at localhost:%d\n", port); 

    hashmap *hm = hcreate();

    while(1) {
        int new_socket = accept(socket_fd, (struct sockaddr *) &address, (socklen_t*)&addrlen);
        if(new_socket < 0) {
            perror("Couldn't accept");
            exit(EXIT_FAILURE);
        }
        printf("New connection\n");
        hm = handle_connection(new_socket, hm);
    }
}
