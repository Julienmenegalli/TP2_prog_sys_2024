#include "adress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

int resolve_address(const char *host, struct sockaddr_storage *server_addr) {
    struct addrinfo hints, *res;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // IPv4 ou IPv6
    hints.ai_socktype = SOCK_DGRAM; // Socket UDP

    status = getaddrinfo(host, NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "Erreur de résolution d'adresse : %s\n", gai_strerror(status));
        return -1;
    }

    memset(server_addr, 0, sizeof(*server_addr));
    memcpy(server_addr, res->ai_addr, res->ai_addrlen);

    // define tftp port
    if (server_addr->ss_family == AF_INET) {
        ((struct sockaddr_in *)server_addr)->sin_port = htons(TFTP_PORT);
    } else if (server_addr->ss_family == AF_INET6) {
        ((struct sockaddr_in6 *)server_addr)->sin6_port = htons(TFTP_PORT);
    }

    freeaddrinfo(res); // save memory of getaddrinfo
    return 0;
}
