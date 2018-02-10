#include "header.c"
#include "utils.c"

char *build_response(char *path) {
    char *ext = get_file_extension(path);
    char *mime = get_mime_type(ext);
}
