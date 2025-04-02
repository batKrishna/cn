#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8001 
#define BUFFER_SIZE 1000 


int main(){
int sockfd ;
char buffer[BUFFER_SIZE];
struct sockaddr_in server_addr, client_addr ;
socklen_t addr_len = sizeof(client_addr);

if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
	exit(EXIT_FAILURE);

	}

server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
        }
        
        printf("server is waiting for a msg\n");
    int n = recvfrom(sockfd, (char *)buffer,BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
    buffer[n] = '\0'; 
     printf("Received message: %s\n", buffer);   
     close(sockfd);
    return 0;

} 