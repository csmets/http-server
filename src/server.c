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
#define WEB_ROOT "www/html"

#define PORT 8090

int main() {

    // Create a socket

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    ///////////////////////////////////////////////////////////////////////////

    // Define the address

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    ///////////////////////////////////////////////////////////////////////////

    bind(
        server_socket,
        (struct sockaddr*) &server_address,
        sizeof(server_address)
    );

    listen(server_socket, 5);

    int client_socket;
    char socket_response[1024];
    char *separated_resp;

    while(1) {
        client_socket = accept(server_socket, (struct sockaddr*) NULL, NULL);

        // Read the returned response from the socket

        read(client_socket, socket_response, 1024);

        ///////////////////////////////////////////////////////////////////////

        // Get the path from the response returned
        //
        // TODO
        // Separate this into it's own function as well as other sections below
        // and set some abstraction to allow better usage of the socket
        // response.

        short int count = 0;
        char *path;
        separated_resp = strtok(socket_response, " ");
        while (separated_resp != NULL) {
            if (count == 1) {
                path = separated_resp;
                break;
            }
            separated_resp = strtok(NULL, " ");
            count++;
        }

        char open_path[512] = WEB_ROOT;
        char* absolute_path = "/";
        if (strcmp(path, absolute_path) == 0) {
            path = "/index.html";
            strcat(open_path, path);
        } else {
            strcat(open_path, path);
        }

        ///////////////////////////////////////////////////////////////////////

        // Load file from given path
        //
        // TODO
        // Check if path given exists and if not return a 404 to prevent server
        // from crashing.

        FILE *html_data;
        html_data = fopen(open_path, "r");

        char response_data[FILE_SIZE];
        char line[1000];
        while(fgets(line, FILE_SIZE, html_data)) {
            strcat(response_data, line);
        };

        ///////////////////////////////////////////////////////////////////////

        // Response header

        char *http_header = header();

        strcat(http_header, "Content-Length:");
        int content_length = strlen(response_data);
        strcat(http_header, intToStr(content_length));
        strcat(http_header, "\r\n\n");

        strcat(http_header, response_data);

        char http_response[RESP_SIZE];
        strcpy(http_response, http_header);

        ///////////////////////////////////////////////////////////////////////

        // Send reponse to client

        send(client_socket, http_response, sizeof(http_response), 0);

        ///////////////////////////////////////////////////////////////////////

        close(client_socket);
    }

    return 0;
}
