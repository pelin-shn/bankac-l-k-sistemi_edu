#include "loglama.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *timestamp_olustur()
{
    time_t now = time(NULL);
    struct tm *zaman = localtime(&now);

    static char zaman_damgasi[20];
    strftime(zaman_damgasi, sizeof(zaman_damgasi), "%Y-%m-%d %H:%M:%S", zaman);
    return zaman_damgasi;
}

void loglama(const char *msg)
{
    FILE *fp = fopen("log.txt", "a");
    if (!fp)
        return;

    fprintf(fp, "[%s] %s\n", timestamp_olustur(), msg);
    fclose(fp);
}
