#include "transmission.h"

int main (int argc, char **argv) {

    if (argc != 3)
        error("Usage: ./server <port_number> <buffer_size>\n");

    unsigned int port_number = atoi(argv[1]);
    unsigned int buffer_size = atoi(argv[2]);

    char *buffer = (char *) malloc(buffer_size * sizeof(char));

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket < 0)
        error("ERROR: Opening socket!\n");

    struct timeval start_time, finish_time;

    free(buffer);
    return 0;
}
