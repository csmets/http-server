#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "utils.h"

char *create_response(Header h, Content c) {
    char *status_response = "\0";
    status_response = malloc(sizeof(char) * HEADER_SIZE);

    // eg: HTTP/1.1 200 OK
    strcpy(status_response, h.version);
    strcat(status_response, " \0");
    strcat(status_response, intToStr(h.status_code));
    strcat(status_response, " \0");
    strcat(status_response, h.status);
    strcat(status_response, "\r\n\0");

    char *cache_control = "\0";
    cache_control = malloc(sizeof(char) * HEADER_SIZE);
    strcpy(cache_control, "Cache-Control: \0");
    strcat(cache_control, h.cache_control);
    strcat(cache_control, "\r\n\0");

    char *pragma = "\0";
    pragma = malloc(sizeof(char) * HEADER_SIZE);
    strcpy(pragma, "Pragma: ");
    strcat(pragma, h.pragma);
    strcat(pragma, "\r\n\0");

    char *expires = "\0";
    expires = malloc(sizeof(char) * HEADER_SIZE);
    strcpy(expires, "Expires: \0");
    strcat(expires, intToStr(h.expires));
    strcat(expires, "\r\n\0");

    char *content_length = "\0";
    content_length = malloc(sizeof(char) * HEADER_SIZE);
    strcpy(content_length, "Content-Length: \0");
    strcat(content_length, intToStr(h.content_length));
    strcat(content_length, "\r\n\0");

    char *content_type = "\0";
    content_type = malloc(sizeof(char) * HEADER_SIZE);
    strcpy(content_type, "Content-Type: \0");
    strcat(content_type, h.content_type);

    char *http_resp = "\0";
    http_resp = malloc(sizeof(char) * RESP_SIZE);
    strcpy(http_resp, status_response);
    strcat(http_resp, cache_control);
    strcat(http_resp, pragma);
    strcat(http_resp, expires);
    strcat(http_resp, content_length);
    strcat(http_resp, content_type);
    strcat(http_resp, "\r\n\n\0");
    strcat(http_resp, c.body);

    free(status_response);
    free(cache_control);
    free(pragma);
    free(expires);
    free(content_length);
    free(content_type);

    return http_resp;
}
