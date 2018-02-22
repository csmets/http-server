#ifndef SOCKET_RESP_H
#define SOCKET_RESP_H

typedef struct socket_resp {
    char *method;
    char *path;
} socket_resp;

socket_resp socket_response_object(char *socket_response);

#endif
