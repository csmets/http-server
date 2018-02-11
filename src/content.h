#ifndef CONTENT_H
#define CONTENT_H

typedef struct Content {
    char *file_path;
    char *body;
    short int status_code;
    char *mime_type;
    char length;
} Content;

Content load_file_contents(char *file_path);
char *get_file_extension(char *file_path);
char *get_mime_type(char *extension);

#endif
