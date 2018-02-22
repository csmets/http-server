#include <stdio.h>
#include <stdlib.h>
#include "server_config.h"
#include "log.h"

void log_access(log l) {
    FILE *logf = fopen(LOG_FILE, "a");
    if (logf == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(logf, "Requested: %s IP: %s Port: %d\r\n", l.path, l.ip, l.port);

    fclose(logf);
}
