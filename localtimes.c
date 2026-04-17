#include "localtimes.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

color_type_t get_color_type(const char *zone, const char *current_zone, const char **important_zones, int num_important_zones) {
    if (strcmp(zone, current_zone) == 0) {
        return COLOR_CURRENT;
    }
    int j;
    for (j = 0; j < num_important_zones; j++) {
        if (strcmp(zone, important_zones[j]) == 0) {
            return COLOR_IMPORTANT;
        }
    }
    return COLOR_NONE;
}

void format_time_string(char *buf, size_t size, const struct tm *tm) {
    char *weekday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    const char *dst = (tm->tm_isdst > 0) ? " *" : "";

    snprintf(buf, size, "%04d/%02d/%02d (%s) %02d:%02d:%02d%s",
            tm->tm_year + 1900,
            tm->tm_mon + 1,
            tm->tm_mday,
            weekday[tm->tm_wday],
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec,
            dst);
}

#ifndef TEST_MODE
#include "zones.inc"
int main(int argc, char **argv) {
	struct timeval	tv;
	struct tm		tm;
	int		i;
    char    time_buf[128];

	if (argc > 1 && strcmp(argv[1], "--version") == 0) {
		printf("%s\n", VERSION_STRING);
		return 0;
	}

	gettimeofday(&tv,NULL);

	for (i=0;i<num_embedded_zones;i++) {
		setenv("TZ", embedded_zones[i], 1);
		tzset();
		localtime_r(&tv.tv_sec, &tm);

        color_type_t color = get_color_type(embedded_zones[i], current_zone, important_zones, num_important_zones);
        
        if (color == COLOR_CURRENT) {
            printf("%c[%d;%d;%dm", 0x1B, 1, 32, 40);
        } else if (color == COLOR_IMPORTANT) {
            /* bold yellow on black — SGR 16-color, not 256-color */
            printf("%c[%d;%d;%dm", 0x1B, 1, 33, 40);
        }

        format_time_string(time_buf, sizeof(time_buf), &tm);
		printf("%19s : %s", embedded_zones[i], time_buf);
        printf("%c[%dm\n", 0x1B, 0);
	}

	return 0;
}
#endif
