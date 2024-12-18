#ifndef ADRESS_H

#define ADRESS_H

#define BUFFER_SIZE 516
#define TFTP_PORT 69

int resolve_address(const char *host, struct sockaddr_storage *server_addr);

#endif //ADRESS_H
