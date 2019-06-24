#include "server.h"

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include "dstring.h"
#include "max.h"
#include "hashmap.h"
#include "indexer.h"
#include "serializer.h"
#include "server.h"

// TODO: extract to config file?
#define MAX_PHRASE_LENGTH 10
#define READ_MAX 1024
#define SO_BACKLOG 10

#define BYE "Bye\n"
#define INDEXED "Text has been indexed\n"
#define INVALID_COMMAND "Invalid command\n"
#define NOT_FOUND "[]\n"
#define TOO_FEW_ARGUMENTS "Too few arguments\n"

#define EXIT "EXIT"
#define INDEX "INDEX"
#define SEARCH "SEARCH"

static const int YES = 1;

static int process_command(hashmap *hm, int fd, char *buf, size_t nbytes) {
  dstringa commands;
  dstring req;
  dstring trimmed;

  req = dappend(dempty(), buf);
  trimmed = dtrim(req);
  commands = dsplit(trimmed, ' ');
  printf("%d '%s'\n", req.length, dtext(trimmed));

  // TODO: don't allocate new dstrings all the time
  if (dequals(trimmed, dcreate(EXIT))) {
    // TODO: don't calculate strlen all the time
    send(fd, BYE, strlen(BYE), 0);
    return 1;
  }
  if (dequals(commands.values[0], dcreate(INDEX))) {
    printf("INDEX\n");
    if (commands.length < 3) {
      send(fd, TOO_FEW_ARGUMENTS, strlen(TOO_FEW_ARGUMENTS), 0);
    } else {
      dstring document = commands.values[1];
      dstring text = djoin(drange(commands, 2, commands.length), ' ');
      printf("TEXT: '%s'\n", dtext(text));
      dstringa index = indexer(text, MAX_PHRASE_LENGTH);
      printf("INDEX SIZE: %d\n", index.length);
      for (int i = 0; i < index.length; i++) {
	dstring on = index.values[i];
	hm = hset(hm, on, document);
      }
      send(fd, INDEXED, strlen(INDEXED), 0);
    }
  } else if (dequals(commands.values[0], dcreate(SEARCH))) {
    printf("SEARCH\n");
    if (commands.length < 2) {
      send(fd, TOO_FEW_ARGUMENTS, strlen(TOO_FEW_ARGUMENTS), 0);
    } else {
      dstring text = djoin(drange(commands, 1, commands.length), ' ');
      printf("SEARCH STRING: '%s'\n", dtext(text));
      dstringa value = hget(hm, text);
      printf("SEARCH RESULTS SIZE: %d\n", value.length);
      if(!value.length) {
	send(fd, NOT_FOUND, strlen(NOT_FOUND), 0);
      } else {
	dstring output = dcreate("[");
	for(int i = 0; i < value.length; i++) { // This builds the JSON array output
	  dstring on = value.values[i];
	  output = dappendc(output, '"');
	  output = dappendd(output, on);
	  output = dappendc(output, '"');
	  if(i != value.length - 1)
	    output = dappendc(output, ',');
	}
	output = dappendc(output, ']');
	output = dappendc(output, '\n');
	send(fd, dtext(output), output.length, 0);
      }
    }
  } else {
    send(fd, INVALID_COMMAND, strlen(INVALID_COMMAND), 0);
  }

  return 0;
}

int start_server(char *host, int port) {
  char buf[READ_MAX];
  struct sockaddr_in client_addr;
  int fd_max;
  hashmap *hm;
  fd_set master_fds;
  fd_set copy_fds;
  struct sockaddr_in server_addr;
  int server_fd;

  hm = sload(); // Loads database file if it exists, otherwise returns an empty hash map

  FD_ZERO(&copy_fds);
  FD_ZERO(&master_fds);
  memset(buf, 0, READ_MAX);
  memset(&client_addr, 0, sizeof(struct sockaddr_in));
  memset(&server_addr, 0, sizeof(struct sockaddr_in));

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    return -1;
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &YES, sizeof(int)) == -1) {
    perror("setsockopt");
    return -1;
  }

  // TODO: respect host parameter
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);
  if (bind(server_fd, (struct sockaddr *) &server_addr,
	   sizeof(struct sockaddr_in)) == -1) {
    perror("bind");
    return -1;
  }

  if (listen(server_fd, SO_BACKLOG) == -1) {
    perror("listen");
    return -1;
  }

  printf("Fist started at localhost:%d\n", port);

  FD_SET(server_fd, &master_fds);
  fd_max = server_fd;

  // TODO: while (running)
  // TODO: signal handler to set running
  while (1) {
    char buf[READ_MAX];
    int i;

    copy_fds = master_fds;

    if (select(fd_max + 1, &copy_fds, NULL, NULL, NULL) == -1) {
      perror("select");
      // TODO: check errno?
      continue;
    }

    for (i = 0; i <= fd_max; i++) {
      if (FD_ISSET(i, &copy_fds)) {
	if (i == server_fd) {
	  socklen_t addrlen = sizeof(struct sockaddr_in);
	  int new_fd = accept(server_fd,(struct sockaddr *) &client_addr,
			      &addrlen);
	  if (new_fd == -1) {
	    perror("accept");
	    continue;
	  }
	  FD_SET(new_fd, &master_fds);
	  fd_max = MAX(new_fd, fd_max);
	} else {
	  // -1 to preserve final NULL
	  int nbytes = recv(i, buf, READ_MAX - 1, 0);
	  buf[nbytes] = '\0';
	  if (nbytes <= 0) {
	    if (nbytes < 0) {
	      perror("recv");
	    }
	    close(i);
	    FD_CLR(i, &master_fds);
	  } else {
	    int should_close = process_command(hm, i, buf, nbytes);
	    if (should_close) {
	      close(i);
	      FD_CLR(i, &master_fds);
	    }
	  }
	}
      }
    }
  }
}
