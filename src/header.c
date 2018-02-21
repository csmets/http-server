#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

Header create_header(Content content) {
    Header h;
    h.version = "HTTP/1.1\0";
    h.status = " OK\0";
    h.status_code = content.status_code;
    h.cache_control = "no-cache, no-store, must-revalidate\0";
    h.pragma = "no-cache\0";
    h.expires = 0;
    h.content_type = content.content_type;
    h.content_length = content.length;
    return h;
}
