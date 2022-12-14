#include "server.h"

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int socket_creation(int port_number, int n_connections){

    bool check = true;
    struct sockaddr_in serv_addr;
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
        error("ERROR: Opening!\n");

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &check, sizeof(int)) == -1)
        error("ERROR: Already in use!\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port_number);

    if (bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        close(socket_fd);
        error("ERROR: Binding!\n");
    }

    if (listen(socket_fd, n_connections) < 0)
        error("ERROR: Listening!\n");

    return socket_fd;
}
