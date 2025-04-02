#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *fp;
    int sd, newsd, n, a, bd, port, clilen;
    char name[100], fileread[100], rcv[100];
    struct sockaddr_in servaddr, cliaddr;

    printf("Enter the port address: ");
    scanf("%d", &port);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        printf("Can't create\n");
        return 1;
    }
    printf("Socket is created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    a = sizeof(servaddr);

    bd = bind(sd, (struct sockaddr *)&servaddr, a);
    if (bd < 0) {
        printf("Can't bind\n");
        return 1;
    }
    printf("Binded\n");

    listen(sd, 5);
    clilen = sizeof(cliaddr);
    newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);
    if (newsd < 0) {
        printf("Can't accept\n");
        return 1;
    }
    printf("Accepted connection\n");

    n = recv(newsd, rcv, sizeof(rcv) - 1, 0);
    if (n <= 0) {
        printf("Error receiving file name\n");
        close(newsd);
        return 1;
    }
    rcv[n] = '\0';

    fp = fopen(rcv, "r");
    if (fp == NULL) {
        send(newsd, "error", strlen("error"), 0);
        close(newsd);
        return 1;
    }

    while (fgets(fileread, sizeof(fileread), fp)) {
        send(newsd, fileread, strlen(fileread), 0);
        usleep(100000); 
    }

    send(newsd, "completed", strlen("completed"), 0);

    fclose(fp);
    close(newsd);
    return 0;
}