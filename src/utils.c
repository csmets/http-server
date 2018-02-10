#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char *intToStr(int number) {
    int length = snprintf(NULL, 0, "%d", number);
    char *str = NULL;
    str = malloc(length + 1);
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

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

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

char *load_file_contents(char *file_path) {
    FILE *html_data;
    char *response_data = NULL;
    response_data = malloc(sizeof(char) * RESP_SIZE);

    if (fexists(file_path) == 1) {

        html_data = fopen(file_path, "rb");

        char line[MAX_READ_LINES];
        while(fgets(line, sizeof(html_data), html_data)) {
            strcat(response_data, line);
        };
    }

    return response_data;
}

char *get_file_extension(char *file_path) {
    char *dot = strrchr(file_path, '.');
    if(!dot || dot == file_path) return "";
    return dot + 1;
}

char *get_mime_type(char *extension) {
    char *mime;
    if (strcmp(extension, "json") == 0) {
        mime = "application/json";
        return mime;
    } else if (strcmp(extension, "css") == 0) {
        mime = "text/css";
        return mime;
    } else {
        mime = "text/plain";
        return mime;
    }
}

void log_access(char *path, const char *ip, int port) {
    FILE *logf = fopen("http_access.log", "a");
    if (logf == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(logf, "Requested: %s IP: %s Port: %d\r\n", path, ip, port);

    fclose(logf);
}
