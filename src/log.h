#ifndef LOG_H
#define LOG_H

typedef struct log {
    char *method;
    short status_code;
    char *path;
    const char *ip;
    short port;
} log;

void log_access(log obj);

#endif
