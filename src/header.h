#ifndef HEADER_H
#define HEADER_H

#include "content.h"

#define HEADER_SIZE 500

typedef struct Header {
    char *version;
    short int status_code;
    char *status;
    int content_length;
    char *cache_control;
    char *pragma;
    int expires;
    char *content_type;
} Header;

Header create_header(Content content);

#endif
