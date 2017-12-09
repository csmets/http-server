#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *header() {
    char *status_code = "HTTP/1.1 200 OK\r\n\0";

    char *cache_control = "Cache-Control: no-cache, no-store, must-revalidate\r\n\0";
    char *pragma = "Pragma: no-cache\r\n\0";
    char *expires = "Expires: 0\r\n\0";

    char *http_header;
    strcat(http_header, status_code);
    strcat(http_header, cache_control);
    strcat(http_header, pragma);
    strcat(http_header, expires);

    return http_header+3;
}
