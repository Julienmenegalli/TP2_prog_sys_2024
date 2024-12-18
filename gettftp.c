#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "gettftp.h"
#include "adress.h"

void gettftp(const char *host, const char *file) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    dprintf(STDOUT_FILENO, "Téléchargement du fichier %s depuis le serveur %s...\n", file, host);

    if (resolve_address(host, &server_addr) < 0) {
        return;
    }

    // create a UDP socket
    sockfd = socket(server_addr.ss_family, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Erreur lors de la création du socket");
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TFTP_PORT);

    snprintf(buffer, BUFFER_SIZE, "Requête fictive pour GET %s", file);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    ssize_t len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
    if (len > 0) {
        buffer[len] = '\0';
        dprintf(STDOUT_FILENO, "Réponse reçue : %s\n", buffer);
    }
    close(sockfd);
}
