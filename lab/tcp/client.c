#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8001
#define BUFFER_SIZE 100

int main() {
  int sock = 0;
  struct sockaddr_in serv_addr;
  char buffer[BUFFER_SIZE] = {0};
  const char *message = "hello server is listening  ";

 if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket creation error");
    exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    perror(" ");
    close(sock);
    exit(EXIT_FAILURE);
    }
    
 if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
     perror("Connection failed");
     close(sock);
     exit(EXIT_FAILURE);
    }
    send(sock, message, strlen(message), 0);
    printf("msg sent to server: %s\n", message);

  
    read(sock, buffer, BUFFER_SIZE);
    printf("Server: %s\n", buffer);


    close(sock);

    return 0;
}
