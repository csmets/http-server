#ifndef CONTENT_H
#define CONTENT_H

typedef struct Content {
    char *file_path;
    char *body;
    short int status_code;
    char *content_type;
    int length;
} Content;

Content load_file_contents(char *file_path);
char *get_file_extension(char *file_path);
char *get_content_type(char *extension);

#endif
