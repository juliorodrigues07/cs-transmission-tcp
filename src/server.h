#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

// ACUSAÇÃO DE ERROS E CRIAÇÃO DAS CONEXÕES (SOCKETS)
void error(const char *msg);
int socket_creation(int port_number, int n_connections);
