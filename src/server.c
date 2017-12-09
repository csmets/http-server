#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include "utils.h"
#include "header.h"

#define FILE_SIZE 900000
#define RESP_SIZE 910000

int main() {
    FILE *html_data;
    html_data = fopen("index.html", "r");

    char response_data[FILE_SIZE];
    fgets(response_data, FILE_SIZE, html_data);

    // Response header
    char *http_header = header();

    strcat(http_header, "Content-Length:");
    int content_length = strlen(response_data);
    strcat(http_header, intToStr(content_length));
    strcat(http_header, "\r\n\n");

    strcat(http_header, response_data);

    char http_response[RESP_SIZE];
    strcpy(http_response, http_header);

    // Create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8090);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;

    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_response, sizeof(http_response), 0);
        close(client_socket);
    }

    return 0;
}
