#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "gettftp.h"
#include "puttftp.h"
#include "adress.h"

#define BUFFER_SIZE 516
#define Welcome "$ ./enseash \nBienvenue dans le Shell enseash. \nTapez 'exit' pour quitter.\n"
#define enseash "enseash"
#define pourcentage " % "
#define end "Au revoir !\n"

int main(int argc, char *argv[]) {
    char input[BUFFER_SIZE];

    // print welcome message
    write(STDOUT_FILENO, Welcome, strlen(Welcome));

    const char *host = NULL;
    const char *file = NULL;

    // verify argument
    if (argc == 3) {
        host = argv[1];
        file = argv[2];
        dprintf(STDOUT_FILENO, "Serveur : %s\n", host);
        dprintf(STDOUT_FILENO, "Fichier : %s\n", file);
    } else if (argc > 1) {
        dprintf(STDERR_FILENO, "Usage : %s <host> <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    while (1) {

        write(STDOUT_FILENO, enseash, strlen(enseash));
        write(STDOUT_FILENO, pourcentage, strlen(pourcentage));
        ssize_t bytes_read = read(STDIN_FILENO, input, BUFFER_SIZE - 1);
        if (bytes_read <= 0) {
            continue;
        }
        input[bytes_read - 1] = '\0'; // Remplacer '\n' par '\0'

        // quit if "exit" is entering
        if (strcmp(input, "exit") == 0) {
            write(STDOUT_FILENO, end, strlen(end));
            exit(EXIT_SUCCESS);
        }

        if (strcmp(input, "gettftp") == 0 && host != NULL && file != NULL) {
            gettftp(host, file);
        } else if (strcmp(input, "puttftp") == 0 && host != NULL && file != NULL) {
            puttftp(host, file);
        }
    }
    return 0;
}

