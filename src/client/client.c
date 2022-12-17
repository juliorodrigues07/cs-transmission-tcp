#include "client.h"

void error (const char *msg) {
    perror(msg);
    exit(1);
}

int main (int argc, char **argv) {

    if (argc != 5)
        error("Usage: ./client <server_host> <port_number> <file_name> <buffer_size>");

    // Argumentos da linha de comando
    char *server_host = argv[1];
    unsigned int port_number = atoi(argv[2]);
    char *file_name = atoi(argv[3]);
    unsigned int buffer_size = atoi(argv[4]);

    char *buffer = (char *) malloc(buffer_size * sizeof(char));

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    inet_aton(server_host, &server_address.sin_addr);

    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket < 0)
        error("ERROR: Opening socket!\n");

    struct timeval start_time, finish_time;

    free(buffer);
    return 0;
}
