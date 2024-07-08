#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    time_t t = time(NULL);
    if (t == (time_t)(-1)) {
        return 2;
    }
    printf("Current time is %ld\n", t);
    struct tm date;
    if (gmtime_r(&t, &date) == NULL) {
        return 1;
    }
    printf("Current date is %d-%02d-%02d %02d:%02d\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);
    printf("Timezone is %s (%ld)\n", date.tm_zone, date.tm_gmtoff);
    return 0;
}