#include "puttftp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "gettftp.h"
#include "adress.h"

// Fonction pour téléverser un fichier via TFTP
void puttftp(const char *host, const char *file) {
    struct sockaddr_storage server_addr;
    char buffer[BUFFER_SIZE];

    dprintf(STDOUT_FILENO, "Téléversement du fichier %s vers le serveur %s...\n", file, host);

    // Résoudre l'adresse du serveur
    if (resolve_address(host, &server_addr) < 0) {
        return;
    }

    // Créer un socket UDP
    const int sockfd = socket(server_addr.ss_family, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Erreur lors de la création du socket");
        return;
    }

    // Exemple : Envoyer une requête fictive
    snprintf(buffer, BUFFER_SIZE, "Requête fictive pour PUT %s", file);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Recevoir une réponse
    ssize_t len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
    if (len > 0) {
        buffer[len] = '\0';
        dprintf(STDOUT_FILENO, "Réponse reçue : %s\n", buffer);
    }

    close(sockfd);
}