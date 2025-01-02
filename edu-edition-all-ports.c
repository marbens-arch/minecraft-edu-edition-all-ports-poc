#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/udp.h>

#define BUFFER_SIZE 512
#define STRING "Hello from Minecraft Education Edition All Ports PoC"

int main(void)
{
    ssize_t bytes_received, bytes_sent;
    char received_message[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof client_addr;
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock < 0) {
        perror("Unable to create socket");
        return EXIT_FAILURE;
    }

    // POSIX requires zeroing of sockaddr_in
    memset(&server_addr, 0, sizeof server_addr);
    memset(&client_addr, 0, sizeof client_addr);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(6666);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*)&server_addr, sizeof server_addr) < 0) {
        close(sock);
        perror("Unable to bind to socket");
        return EXIT_FAILURE;
    }

    while (1) {
        bytes_received = recvfrom(sock, received_message, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_len);

        if (bytes_received < 0) {
            perror("Unable to receive bytes");
            continue;
        }

        fwrite(received_message, 1, bytes_received, stdout);

        bytes_sent = sendto(sock, STRING, strlen(STRING), 0, (struct sockaddr*)&client_addr, client_addr_len);

        // This error is not fatal
        if (bytes_sent < 0)
            perror("Unable to send bytes");
    }

    close(sock);

    return EXIT_SUCCESS;
}
