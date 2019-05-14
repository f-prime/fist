#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "indexer.h"
#include "hashmap.h"
#include "server.h"
#include "utils.h"

// Commands

#define INDEX "INDEX"
#define SEARCH "SEARCH"

// Responses

#define INDEXED "INDEXED"
#define NOT_FOUND "[]"

l_item *handle_connection(int new_socket, l_item *hm) {
    printf("Handled\n");
    char *buffer = malloc(sizeof(char) * 1024);
    
    while(1) { 
        memset(buffer, 0, 1024);
        int size = recv(new_socket, buffer, 1024, 0);
        if(size == 0) {
            close(new_socket);
            break;
        }
        printf("%s\n", buffer);
        
        t_split token = split(stripend(buffer));
        if(token.length > 0) {
            char *cmd = token.word_array[0];
            char *value = token.word_array[1];
            int length = token.length;
            if(!strncmp(cmd, INDEX, strlen(INDEX))) {
                memset(buffer, 0, 1024);
                for(int i = 2; i < length; i++) {
                    char *word = token.word_array[i];
                    strncat(buffer, word, strlen(word));
                    if(i != token.length - 1)
                        strcat(buffer, " ");
                }
                char *cleaned_words = stripend(buffer);
                t_index index = indexer(cleaned_words, 10);
                for(int i = 0; i < index.length; i++) {
                    hm = h_add(hm, index.index[i], value);
                }

                for(int i = 0; i < index.length; i++) {
                    printf("INDEXED %s\n", index.index[i]);
                }

                send(new_socket, INDEXED, strlen(INDEXED), 0);

            } else if(!strncmp(cmd, SEARCH, strlen(SEARCH))) {
                char *search = malloc(sizeof(buffer));
                memset(search, 0, sizeof(buffer));
                for(int i = 1; i < token.length; i++) {
                    char *word = token.word_array[i];
                    int size = strlen(word);
                    strncat(search, word, size);
                    if(i != token.length - 1)
                        strcat(search, " ");
                }
                printf("SEARCH '%s'\n", search); 
                l_item key = h_get(hm, search);
                if(key == NULL)
                    send(new_socket, NOT_FOUND, strlen(NOT_FOUND), 0);
                else {
                    char *values = malloc(sizeof(char*));
                    values[0] = '[';
                    for(int i = 0; i < key->num_vals; i++) {
                        values = realloc(values, sizeof(char) * strlen(key->values[i]) + 3);
                        strcat(values, "\"");
                        strncat(values, key->values[i], strlen(key->values[i]));
                        if(i != key->num_vals - 1) {
                            strcat(values, "\"");
                            strcat(values, ",");
                        } else {
                            strcat(values, "\"");
                            strcat(values, "]");
                        }
                    }
                    send(new_socket, values, strlen(values), 0);
                }
            }
        }
    }
    free(buffer);
    printf("DISCONNECTED\n");
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

    l_item *hm = h_create();

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
