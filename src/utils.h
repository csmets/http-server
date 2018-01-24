#ifndef UTILS_H
#define UTILS_H

#define WEB_ROOT "www/html"
#define RESP_SIZE 910000
#define MAX_READ_LINES 10000

char *intToStr(int number);
int fexists(char file_name[]);
char *get_response_path(char *socket_response);
char *load_file_contents(char *file_path);
void log_access(char *path, const char *ip, int port);

#endif
