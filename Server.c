// Heder files, Standard library of C
#include <stdio.h> // input/ output functions
#include <winsock2.h> // It is Microsoft's implementation of the Berkeley Sockets API

// Linking winsock library with the ws2_32.lib
// This library contains the implementations of the socket(), bind(), listen(), accept(),  recv(), send()
// without this it gives the linking error
#pragma comment(lib, "ws2_32.lib")

int main()
{
    // WSDATA : it is a structure that stores: winsock version, description, system update
    WSADATA wsa;
    // creating the two sockets server_fd: main server socket, client_fd: client connection socket
    SOCKET server_fd, client_fd; // server_fd: waits for the connecion, client_fd: talks to the client
    // it is a structure that stores: sin_faimly: IPV4 or IPV6
    //                                sin_port: Port number
    //                                sin_address: IP address
    // It say the where should the server exists in the network
    struct sockaddr_in address;
    // It stores the client's http request
    char buffer[1024];

    // Initialize Winsock
    // MAKEWORD(2,2): request winsock version-2.2
    // &wsa: Store info in structure(WSADATA)
    // Wihtout this all of the socket functions will not work
    // IT boots the networking system before using it
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create socket
    // AF_INET: IPV4 (AF_INET6: IPV6)
    // SOCK_STREAM: type of communication(TCP) (SOCK_DGRAM: UDP)
    // 0: protocol (automatically chooses the TCP for the SOCK_STREAM)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Intiatializing the address structure variable (defined above)
    address.sin_family = AF_INET;         // IPV4
    address.sin_port = htons(8080);       // port number
    address.sin_addr.s_addr = INADDR_ANY; // Accept the connection from any ip address from this machine

    // Bind: attach socket to the any IP + PORT
    // server_fd: The socket descriptor created earlier
    // (struct sockaddr *)&address: Pointer to the address structure containing IP and Port
    // sizeof(address): Size of the address structure
    // This links the socket to the IP and Port configured in 'address'
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen: put the socket in to the passive mode & waits for the connection
    // server_fd: The socket to listen on
    // 3: backlog (max no of pending connection in the queue)
    // This prepares the server to accept incoming client requests
    listen(server_fd, 3);

    // prints the statement when the server is running (browser, terminal)
    printf("Server running on port 8080...\n");

    // Accept: connecting a client
    // server_fd: The listening socket
    // NULL, NULL: We are not storing the client's address information
    // Returns a new socket (client_fd) specifically for this client connection
    // The program waits here until a client connects
    client_fd = accept(server_fd, NULL, NULL);

    // Read request: HTTP request from the browser
    // client_fd: The socket to read from
    // buffer: Where to store the data
    // 1024: Max bytes to read
    // 0: Flags
    recv(client_fd, buffer, 1024, 0);
    printf("%s\n", buffer);

    // Send response
    // HTTP/1.1 200 OK: The status line (protocol version and success code)
    // Content-Type: text/plain: The MIME type of the content
    // \r\n\r\n: The blank line that separates headers from the body
    // "Hello from C server": The body of the response
    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "Hello from C server";

    // Send the response back to the client
    // client_fd: The socket to send to
    // response: The buffer containing the data
    // strlen(response): The amount of data to send
    // 0: Flags
    send(client_fd, response, strlen(response), 0);

    // Close the client connection
    closesocket(client_fd);
    // Close the server socket
    closesocket(server_fd);

    // Cleanup Winsock resources
    WSACleanup();

    return 0;
}