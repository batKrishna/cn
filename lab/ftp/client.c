#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    FILE *fp;
    int csd, n, cport;
    char name[100], rcvg[100], fname[100];
    struct sockaddr_in servaddr;

    printf("Enter the port: ");
    scanf("%d", &cport);

    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd < 0) {
        printf("Error creating socket\n");
        return 1;
    }
    printf("Socket is created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);

    if (connect(csd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        printf("Error in connection\n");
        return 1;
    }
    printf("Connected\n");


    printf("Enter the existing file name: ");
    scanf("%s", name);
    printf("Enter the new file name: ");
    scanf("%s", fname);

    fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }

    send(csd, name, strlen(name), 0);

    while (1) {
        n = recv(csd, rcvg, sizeof(rcvg) - 1, 0);
        if (n <= 0) break;
        rcvg[n] = '\0';

        if (strcmp(rcvg, "error") == 0) {
            printf("File is not available\n");
            fclose(fp);
            close(csd);
            return 1;
        }

        if (strcmp(rcvg, "completed") == 0) {
            printf("File is transferred successfully.\n");
            break;
        }

        fprintf(fp, "%s", rcvg);
        printf("%s", rcvg);
    }

    fclose(fp);
    close(csd);
    return 0;
}
