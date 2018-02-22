#include <string.h>
#include <stdlib.h>

#include "server_config.h"
#include "utils.h"

char *get_response_path(char *socket_response) {
    short int count = 0;
    char *path = "\0";
    char *separated_resp = NULL;

    separated_resp = strtok(socket_response, " ");

    while (separated_resp != NULL) {
        if (count == 1) {
            path = separated_resp;
            break;
        }
        separated_resp = strtok(NULL, " ");
        count++;
    }

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
