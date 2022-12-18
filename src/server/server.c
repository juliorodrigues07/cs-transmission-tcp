#include "server.h"

void error (const char *msg) {
    perror(msg);
    exit(1);
}

int socket_creation (unsigned int port_number) {

    bool check = true;
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Cria o socket do servidor, verificando possíveis erros
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server_socket < 0)
        error("ERROR: Opening socket! (Server)\n");

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &check, sizeof(int)) == -1)
        error("ERROR: Already in use! (Server)\n");

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        error("ERROR: Binding! (Server)\n");

    if (listen(server_socket, 5) < 0)
        error("ERROR: Listening! (Server)\n");

    return server_socket;
}

int main (int argc, char **argv) {

    if (argc != 3)
        error("Usage: ./server <port_number> <buffer_size>\n");

    // Argumentos de entrada do servidor
    unsigned int port_number = atoi(argv[1]);
    unsigned int buffer_size = atoi(argv[2]);

    char *buffer = (char *) malloc(buffer_size * sizeof(char));

    // Criação do socket do servidor
    int server_socket = socket_creation(port_number);

    // Conexão do cliente com o servidor
    printf("Awaiting connection..\n");

    struct sockaddr_in client_address;
    unsigned int client_size = sizeof(client_address);

    // Aceita a conexão de clientes
    int client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_size);
    if (client_socket < 0)
        error("ERROR: Accept! (Server)\n");

    printf("Connection Successful!\n");

    int i;
    char message[100];

    // Contadores de bytes recebidos e enviados
    long int receiving, sending;

    // Obtém o nome do arquivo byte a byte
    for (i = 0; ; i++) {

        receiving = recv(client_socket, &message[i], 1, 0);
        if (receiving < 0)
            error("ERROR: Receiving file name! (Server)\n");

        if (message[i] == '\0')
            break;
    }

    // Volta dois diretórios no caminho (server e src)
    chdir("..");
    chdir("..");

    // Obtém o diretório corrente concatenado ao diretório de arquivos cwd + /files/
    char cwd[PATH_MAX];
    char path[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    strcpy(path, strcat(cwd, "/files/"));

    // Começa a contagem do tempo de transmissão
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    // Abre o arquivo em modo leitura (se existir) para enviar ao cliente
    unsigned int bytes_sended = 0;
    FILE *file = fopen(strcat(path, message), "r");
    if (file == NULL)
        error("ERROR: Opening file! (Server)\n");

    // Enquanto houver conteúdo no arquivo (bytes) envia ao cliente respeitando o tamanho do buffer
    while (fgets(buffer, (int) buffer_size, file) != NULL) {

        sending = send(client_socket, buffer, buffer_size, 0);
        if (sending < 0)
            error("ERROR: Sending file via buffer! (Server)\n");

        // Acumula o total de bytes enviados
        bytes_sended += sending;
    }

    // Sinaliza a finalização da transmissão
    sending = send(client_socket, "\0", 1, 0);
    if (sending < 0)
        error("ERROR: Sending EOF! (Server)\n");

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
    double bit_rate = (((bytes_sended / 1000.0) * 8) / total_time);

    printf("Buffer: %5u Byte(s) \nTaxa: %10.2lf Kbps (%u Bytes em %0.3lf s)\n", buffer_size,
                                                                                bit_rate,
                                                                                bytes_sended,
                                                                                total_time);

    free(buffer);
    return 0;
}
