#ifndef UTILS_H
#define UTILS_H

char *intToStr(int number);
int fexists(char file_name[]);
int isDirectory(const char *path);
char *get_response_path(char *socket_response);
void log_access(char *path, const char *ip, int port);

#endif
