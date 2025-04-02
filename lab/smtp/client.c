#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 1024

int main() {
    int client_socket, port;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char from[50], to[50], mail[BUFFER_SIZE], request[BUFFER_SIZE], response[BUFFER_SIZE];

   
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d", &port);
    server_addr.sin_port = htons(port);

    printf("Enter the server address: ");
    char server_name[100];
    scanf("%s", server_name);
    server = gethostbyname(server_name);
    if (!server) {
        fprintf(stderr, "Error: No such host\n");
        exit(EXIT_FAILURE);
    }
    memcpy(&server_addr.sin_addr, server->h_addr, server->h_length);

    
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    recv(client_socket, response, BUFFER_SIZE, 0);
    printf("Server: %s", response);

    
    printf("Enter your email: ");
    scanf("%s", from);

    
    printf("Enter recipient email: ");
    scanf("%s", to);

    
    printf("Enter your message: ");
    getchar(); // Clear newline
    fgets(mail, BUFFER_SIZE, stdin);
    mail[strcspn(mail, "\n")] = '\0'; 

    
    snprintf(request, sizeof(request), "MAIL FROM: %s\n", from);
    send(client_socket, request, strlen(request), 0);
    recv(client_socket, response, BUFFER_SIZE, 0);
    printf("Server: %s", response);

    snprintf(request, sizeof(request), "RCPT TO: %s\n", to);
    send(client_socket, request, strlen(request), 0);
    recv(client_socket, response, BUFFER_SIZE, 0);
    printf("Server: %s", response);

    snprintf(request, sizeof(request), "DATA\n%s\n.\n", mail);
    send(client_socket, request, strlen(request), 0);
    recv(client_socket, response, BUFFER_SIZE, 0);
    printf("Server: %s", response);

    snprintf(request, sizeof(request), "QUIT\n");
    send(client_socket, request, strlen(request), 0);
    recv(client_socket, response, BUFFER_SIZE, 0);
    printf("Server: %s", response);

    printf("Email sent successfully!\n");
    
    printf("\nCLIENT CLOSING DOWN!!!!\n");

    close(client_socket);
    return 0;
}

