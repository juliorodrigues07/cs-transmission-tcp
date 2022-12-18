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
    char *file_name = argv[3];
    unsigned int buffer_size = atoi(argv[4]);

    char *buffer = (char *) malloc(buffer_size * sizeof(char));

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    inet_aton(server_host, &server_address.sin_addr);

    // Abre o socket do cliente
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket < 0)
        error("ERROR: Opening socket! (Client)\n");

    printf("Connecting...\n");

    // Realiza a conexão com o servidor
    int server_socket = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (server_socket < 0)
        error("ERROR: Connecting to server socket! (Client)\n");

    printf("Connection Successful!\n");

    // Envia o nome do arquivo para o servidor byte a byte
    long int sending;
    for (int i = 0; i < strlen(file_name); i++) {

        sending = send(client_socket, &file_name[i], 1, 0);
        if (sending < 0)
            error("ERROR: Sending file name! (Client)\n");
    }

    // Sinaliza o final do nome do arquivo enviado
    sending = send(client_socket, "\0", 1, 0);
    if (sending < 0)
        error("ERROR: Sending EOF! (Client)\n");

    long int receiving;
    unsigned int bytes_received = 0;

    // Arquivo de saída para gravação
    FILE *file = fopen("output.txt", "w");

    // Começa a contagem do tempo de transmissão
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    // Enquanto houver conteúdo no arquivo (bytes), recebe do servidor respeitando o tamanho do buffer
    while (true) {

        receiving = recv(client_socket, buffer, buffer_size, 0);
        if (receiving < 0)
            error("ERROR: Receiving file via buffer! (Client)\n");

        // Sinalização se os dados do arquivo sendo recebido terminaram
        if (!strcmp(buffer, "\0"))
            break;

        // Escreve os dados recebidos no arquivo de saída
        fprintf(file, "%s", buffer);

        // Acumula o total de bytes recebidos
        bytes_received += receiving;
    }

    // Fecha o arquivo e os sockets de comunicação
    fclose(file);
    close(client_socket);
    close(server_socket);

    // Finaliza a contagem do tempo de transmissão
    struct timeval finish_time;
    gettimeofday(&finish_time, NULL);

    // Obtém o tempo total para geração do relatório de transmissão com as estatísticas
    unsigned int start = start_time.tv_sec * 1000000 + start_time.tv_usec;
    unsigned int finish = finish_time.tv_sec * 1000000 + finish_time.tv_usec;
    double total_time = (finish - start) / 1000000.0;
    double bit_rate = (((bytes_received / 1000.0) * 8) / total_time);

    printf("Buffer: %5u Byte(s) \nTaxa: %10.2lf Kbps (%u Bytes em %0.3lf s)\n", buffer_size,
                                                                                bit_rate,
                                                                                bytes_received,
                                                                                total_time);

    free(buffer);
    return 0;
}
