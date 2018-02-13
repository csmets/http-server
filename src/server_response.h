#ifndef SERVER_RESPONSE_H
#define SERVER_RESPONSE_H

#include "header.h"
#include "content.h"

char *create_response(Header h, Content c);

#endif
