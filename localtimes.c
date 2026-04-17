#include "zones.inc"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
	struct timeval	tv;
	struct tm		tm;
    char	*weekday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    char	*dst[] = { "", "*" };
	int		i;

	if (argc > 1 && strcmp(argv[1], "--version") == 0) {
		printf("localtimes version: %s\n", VERSION_STRING);
		return 0;
	}

	gettimeofday(&tv,NULL);

	for (i=0;i<num_embedded_zones;i++) {
		setenv("TZ", embedded_zones[i], 1);
		tzset();
		localtime_r(&tv.tv_sec, &tm);
        if (strcmp(embedded_zones[i], current_zone) == 0) {
            printf("%c[%d;%d;%dm", 0x1B, 1, 32, 40);
        } else {
            int j;
            for (j = 0; j < num_important_zones; j++) {
                if (strcmp(embedded_zones[i], important_zones[j]) == 0) {
                    printf("%c[%d;%d;%dm", 0x1B, 38, 5, 227);
                    break;
                }
            }
        }
		printf("%19s : %04d/%02d/%02d (%s) %02d:%02d:%02d %s",
                embedded_zones[i],
                tm.tm_year + 1900,
                tm.tm_mon + 1,
                tm.tm_mday,
                weekday[tm.tm_wday],
                tm.tm_hour,
                tm.tm_min,
                tm.tm_sec,
                dst[tm.tm_isdst]);
        printf("%c[%dm\n", 0x1B, 0);
	}

	return 0;
}
