#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define HEADER_SIZE 500

char *header(int status_code) {
    char *status_response = NULL;
    status_response = malloc(sizeof(char) * HEADER_SIZE);
    char *http_version = "HTTP/1.1 \0";
    char *status = " OK\r\n\0";
    strcpy(status_response, http_version);
    strcat(status_response, intToStr(status_code));
    strcat(status_response, status);

    char *cache_control = "Cache-Control: no-cache, no-store, must-revalidate\r\n\0";
    char *pragma = "Pragma: no-cache\r\n\0";
    char *expires = "Expires: 0\r\n\0";

    char *http_header = NULL;
    http_header = malloc(sizeof(char) * HEADER_SIZE);
    strcpy(http_header, status_response);
    strcat(http_header, cache_control);
    strcat(http_header, pragma);
    strcat(http_header, expires);

    free(status_response);

    return http_header;
}
