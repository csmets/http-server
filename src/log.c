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

    fprintf(
            logf,
            "%s %d %s %s %d\r\n",
            l.method,
            l.status_code,
            l.path,
            l.ip,
            l.port);

    fclose(logf);
}
