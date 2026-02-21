#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {

    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[1024];

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // Listen
    listen(server_fd, 3);

    printf("Server running on port 8080...\n");

    // Accept
    client_fd = accept(server_fd, NULL, NULL);

    // Read request
    recv(client_fd, buffer, 1024, 0);
    printf("%s\n", buffer);

    // Send response
    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "Hello from C server";

    send(client_fd, response, strlen(response), 0);

    closesocket(client_fd);
    closesocket(server_fd);

    WSACleanup();

    return 0;
}