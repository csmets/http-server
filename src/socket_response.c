#include <string.h>
#include <stdlib.h>

#include "server_config.h"
#include "utils.h"
#include "socket_response.h"

char *split_socket_response (char *socket_response) {
    char *separated_resp = NULL;
    separated_resp = strtok(socket_response, " ");
    return separated_resp;
}

char *get_response_path(char *path) {
    char *open_path = NULL;
    open_path = malloc(
                    sizeof(char) *
                        (
                            strlen(WEB_ROOT) +
                            strlen(path) +
                            strlen(DEFAULT_FILE) + 1
                        )
                    );

    strcpy(open_path, WEB_ROOT);

    char *absolute_path = "/";
    if (strcmp(path, absolute_path) == 0) {
        strcat(open_path, DEFAULT_FILE); // load root file
    } else {
        strcat(open_path, path);
        if (isDirectory(open_path) != 0) {
            strcat(open_path, DEFAULT_FILE);
        }
    }

    return open_path;
}

socket_resp socket_response_object(char *socket_response) {
    short int count = 0;
    char *separated_resp = NULL;
    socket_resp socket_obj;
    socket_obj.path = "\0";
    socket_obj.method = "\0";
    separated_resp = split_socket_response(socket_response);

    while (separated_resp != NULL) {
        if (count == 0) {
            socket_obj.method = strdup(separated_resp);
        } else if (count == 1) {
            socket_obj.path = get_response_path(separated_resp);
            break;
        }
        separated_resp = strtok(NULL, " ");
        count++;
    }

    return socket_obj;
}
