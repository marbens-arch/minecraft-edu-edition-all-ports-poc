#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/udp.h>

#include "datainfo.h"
#define RETRANS_TIMEOUT_MS 200

int main(int argc, char **argv)
{
    int sock;
    struct sockaddr_in server_addr;
    ssize_t bytes_received, bytes_sent;
    char received_message[BUFFER_SIZE];
    socklen_t server_addr_len = sizeof server_addr;
    struct timeval timeout = {
        .tv_sec = 0,
        .tv_usec = RETRANS_TIMEOUT_MS * 1000
    };

    if (argc < 2) {
        fputs("Usage: <program name> <server IP address>\n", stderr);
        return EXIT_FAILURE;
    }

    // POSIX requires zeroing of sockaddr_in
    memset(&server_addr, 0, sizeof server_addr);

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) < 1) {
        fputs("Invalid IP address specified\n", stderr);
        return EXIT_FAILURE;
    }

    server_addr.sin_port = htons(6666);

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        perror("Unable to create socket");
        return EXIT_FAILURE;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout) < 0) {
        close(sock);
        perror("Unable to set timeout");
        return EXIT_FAILURE;
    }

    while (1) {
        bytes_sent = sendto(sock, STRING, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, server_addr_len);
        if (bytes_sent < 0) {
            perror("Unable to send data");
            continue;
        }

        bytes_received = recvfrom(sock, received_message, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, &server_addr_len);
        if (bytes_received < 0) {
            if (errno == EAGAIN)
                printf("Data not acknowledged in %d ms. Retransmitting.\n", RETRANS_TIMEOUT_MS);
            else
                perror("Unable to receive data");
            continue;
        }

        if (memcmp(received_message, STRING, BUFFER_SIZE) == 0) {
            puts("Successfully received message from Minecraft Education Edition All Ports PoC. System is vulnerable.");
        } else {
            puts("Port 6666 is open but it's not our server program. The server replied with:");
            fwrite(received_message, 1, bytes_received, stdout);
        }

        close(sock);

        return EXIT_SUCCESS;
    }

    close(sock);

    return EXIT_SUCCESS;
}
