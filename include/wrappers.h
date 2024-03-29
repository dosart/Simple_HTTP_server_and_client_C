#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol);

int Connect(int clientfd, const struct sockaddr *addr, socklen_t addrlen);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int listenfd, struct sockaddr *addr, socklen_t *addrlen);

int Getaddrinfo(const char *host, const char *service,
                const struct addrinfo *hints, struct addrinfo **result);

void Freeaddrinfo(struct addrinfo *result);

int Setsockopt(int s, int level, int optname, const void *optval,
               socklen_t optlen);

int Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host,
                socklen_t hostlen, char *serv, socklen_t servlen, int flags);

ssize_t Send(int sockfd, const void *msg, size_t len, int flags);

ssize_t Recv(int sockfd, void *buf, size_t len, int flags);

int Open_listen_fd(const char *port, int listen_size);

int open_listen_fd(const char *port, int listen_size);

int Open_client_fd(char *hostname, char *port);

int open_client_fd(char *hostname, char *port);

#endif
