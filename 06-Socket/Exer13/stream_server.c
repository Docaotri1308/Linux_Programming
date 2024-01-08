#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>             // Contains the necessary structure for the socket
#include <netinet/in.h>             // The library contains constants and structures when using addresses on the internet
#include <arpa/inet.h>
#include <unistd.h>
#include <asm-generic/socket.h>

void chat_func(int socket_fd) {
    char receive_buff[256];
    char send_buff[256];

    while(1) {
        // Read data from socket
        // The read function will block until the data is read
        read(socket_fd, receive_buff, 256);

        if (strncmp(receive_buff, "exit", 4) == 0) {
            system("clear");
            break;
        }
        printf("\nMessage from Client: %s", receive_buff);

        // Enter responses from the keyboard
        // Write data to the client through the write function
        printf("\nMessage to Client: ");
        fgets(send_buff, 256, stdin);
        write(socket_fd, send_buff, 256);

        if (strncmp(send_buff, "exit", 4) == 0) {
            system("clear");
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    int port_num, option, len;
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;

    // Read the portnumber on the command line
    if (argc < 2) {
        printf("No port provided\ncommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    } else {
        port_num = atoi(argv[1]);
    }

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Prevent error: “address already in use”
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));

    // Initialize the address for the server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Listen to up to 5 connections in the queue
    listen(server_fd, 5) == -1;

    // Get client information
    len = sizeof(client_addr);

    while(1) {
        printf("Server is listening at port: %d\n.....\n", port_num);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
        if (client_fd == -1) {
            system("clear");
        }

        printf("Server is got connection \n");
        chat_func(client_fd);
    }

    close(server_fd);
    close(client_fd);

    return 0;
}