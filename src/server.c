#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#include "utils.h"
#include "header.h"
#include "content.h"
#include "server_response.h"

#define PORT 8080

int main() {

    char buff[RESP_SIZE];

    // Create a socket

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    socklen_t slen;
    char socket_response[1024];
    int client_socket;

    ///////////////////////////////////////////////////////////////////////////

    // Define the address

    struct sockaddr_in server_address, client_addr;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    ///////////////////////////////////////////////////////////////////////////

    bind(
        server_socket,
        (struct sockaddr*)&server_address,
        sizeof(server_address)
    );

    listen(server_socket, 5);

    while(1) {
        slen = sizeof(client_addr);

        client_socket = accept(
                            server_socket,
                            (struct sockaddr*)&client_addr,
                            &slen
                        );

        // Read the returned response from the socket

        read(client_socket, socket_response, 1024);

        ///////////////////////////////////////////////////////////////////////

        // Get the path from the response returned

        char *open_path = get_response_path(socket_response);

        ///////////////////////////////////////////////////////////////////////

        // Load file from given path

        Content response_content = load_file_contents(open_path);

        ///////////////////////////////////////////////////////////////////////

        // Create header
        Header header = create_header(response_content);

        printf("%d", header.content_length);

        ///////////////////////////////////////////////////////////////////////

        // Create http response

        char *http_response = create_response(header, response_content);

        ///////////////////////////////////////////////////////////////////////

        // Send reponse to client

        char http_response_array[RESP_SIZE];
        strcpy(http_response_array, http_response);

        send(
            client_socket,
            http_response_array,
            sizeof(http_response_array),
            0
        );

        ///////////////////////////////////////////////////////////////////////

        // Memory clean up

        memset(&http_response_array[0], 0, sizeof(http_response_array));
        memset(&socket_response[0], 0, sizeof(socket_response));
        open_path = NULL;

        ///////////////////////////////////////////////////////////////////////

        // Log the client request

        log_access(
            open_path,
            inet_ntop(AF_INET, &client_addr.sin_addr, buff, sizeof(buff)),
            ntohs(client_addr.sin_port)
        );

        ///////////////////////////////////////////////////////////////////////

        close(client_socket);
    }

    return 0;
}
