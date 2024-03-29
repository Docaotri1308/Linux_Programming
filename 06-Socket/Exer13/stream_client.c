#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>             // Contains the necessary structure for the socket
#include <netinet/in.h>             // The library contains constants and structures when using addresses on the internet
#include <arpa/inet.h>
#include <unistd.h>

void chat_func(int server_fd) {
    char receive_buff[256];
    char send_buff[256];

    while(1) {
        // Send a message to the server using the write function
        printf("\nMessage to Server: ");
        fgets(send_buff, 256, stdin);
        write(server_fd, send_buff, 256);

        if (strncmp(send_buff, "exit", 4) == 0) {
            printf("Client exit ...\n");
            break;
        }

        // Receive messages from the server using the read function
        read(server_fd, receive_buff, 256);
        
        if (strncmp(receive_buff, "exit", 4) == 0) {
            printf("Server exit ...\n");
            break;
        }
        printf("\nMessage from Server: %s", receive_buff);
    }
}

int main(int argc, char *argv[]) {
    int port_num;
    int server_fd;
    struct sockaddr_in server_addr;

    // Read the portnumber on the command line
    if (argc < 3) {
        printf("command : ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    } 
    else {
        port_num = atoi(argv[2]);
    }

    // Initialize server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Connect to the server
    connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    chat_func(server_fd);

    close(server_fd);
    return 0;
}