#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "content.h"

Content load_file_contents(char *file_path) {
    FILE *html_data;
    char *response_data = NULL;
    response_data = malloc(sizeof(char) * RESP_SIZE);
    Content content;
    content.file_path = file_path;

    if (fexists(file_path) == 1) {

        html_data = fopen(file_path, "rb");

        char line[MAX_READ_LINES];
        while(fgets(line, sizeof(html_data), html_data)) {
            strcat(response_data, line);
        };

        content.status_code = 200;
        content.content_type = get_content_type(get_file_extension(file_path));
        content.length = strlen(response_data);
    } else {
        content.status_code = 404;
        content.length = 0;
    }

    content.body = response_data;

    return content;
}

char *get_file_extension(char *file_path) {
    char *dot = strrchr(file_path, '.');
    if(!dot || dot == file_path) return "";
    return dot + 1;
}

char *get_content_type(char *extension) {
    printf("%s", extension);
    char *mime;
    if (strcmp(extension, "json") == 0) {
        mime = "application/json";
        return mime;
    } else if (strcmp(extension, "html") == 0) {
        mime = "text/html";
        return mime;
    } else if (strcmp(extension, "css") == 0) {
        mime = "text/css";
        return mime;
    } else {
        mime = "text/plain";
        return mime;
    }
}
