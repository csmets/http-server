#ifndef SERVER_RESPONSE_H
#define SERVER_RESPONSE_H

#include "header.h"
#include "content.h"

typedef struct Http_Response {
    char *content;
    int size;
} Http_Response;

Http_Response create_response(Header h, Content c);

#endif
