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
        error("ERROR: Opening socket! (Client)\n");

    printf("Connecting...\n");

    int server_socket = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (server_socket < 0)
        error("ERROR: Connecting to server socket! (Client)\n");

    printf("Connection Successful!\n");

    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    long int sending = send(client_socket, "Handshake", 10, 0);
    if (sending < 0)
        error("ERROR: Handshake! (Client)\n");

    char message[100];
    long int receiving = recv(client_socket, message, 100, 0);
    if (!strcmp("ACK", message) || receiving < 0)
        error("ERROR: ACK! (Client)\n");

    for (int i = 0; i < strlen(file_name); i++) {

        sending = send(client_socket, &file_name[i], 1, 0);
        if (sending < 0)
            error("ERROR: Sending file via buffer! (Client)\n");
    }

    sending = send(client_socket, "\0", 1, 0);
    if (sending < 0)
        error("ERROR: Sending EOF! (Client)\n");

    receiving = recv(client_socket, message, 100, 0);
    if (!strcmp("ACK", message) || receiving < 0)
        error("ERROR: File ACK! (Client)\n");

    unsigned int bytes_received = 0;
    FILE *file = fopen("output.txt", "w");

    while (true)
        break;

    fclose(file);
    close(client_socket);
    close(server_socket);

    struct timeval finish_time;
    gettimeofday(&finish_time, NULL);

    unsigned int start = start_time.tv_sec * 1000000 + start_time.tv_usec;
    unsigned int finish = finish_time.tv_sec * 1000000 + finish_time.tv_usec;
    double total_time = (finish - start) / 1000000.0;

    printf("Buffer: %5u Byte(s) \nTaxa: %10.2lf kbps (%u Bytes em %0.3lf s)\n", buffer_size,
           ((bytes_received / 1000.0) / total_time),
           bytes_received,
           total_time);

    free(buffer);
    return 0;
}
