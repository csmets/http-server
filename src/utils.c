#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *intToStr(int number) {
    int length = snprintf(NULL, 0, "%d", number);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", number);
    return str;
}

int fexists(char file_name[]) {
    FILE *file;
    if ((file = fopen(file_name, "r"))) {
       fclose(file);
       return 1;
    }
    return 0;
}

char *get_response_path(char *socket_response) {
    short int count = 0;
    char *path;
    char *separated_resp;

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
    open_path = malloc(sizeof(char) * (strlen(WEB_ROOT) + strlen(path)));
    strcpy(open_path, WEB_ROOT);

    char* absolute_path = "/";
    if (strcmp(path, absolute_path) == 0) {
        path = "/index.html";
        strcat(open_path, path);
    } else {
        strcat(open_path, path);
    }

    return open_path;
}

char *load_file_contents(char *file_path) {
    FILE *html_data;
    char *response_data = "\0";

    if (fexists(file_path) == 1) {
        response_data = malloc(sizeof(char) * RESP_SIZE);

        html_data = fopen(file_path, "r");

        char line[MAX_READ_LINES];
        while(fgets(line, sizeof(html_data), html_data)) {
            strcat(response_data, line);
        };
    }

    return response_data;
}
