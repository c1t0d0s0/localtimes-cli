#ifndef LOCALTIMES_H
#define LOCALTIMES_H

#include <stddef.h>
#include <time.h>

typedef enum {
    COLOR_NONE,
    COLOR_CURRENT,
    COLOR_IMPORTANT
} color_type_t;

color_type_t get_color_type(const char *zone, const char *current_zone, const char **important_zones, int num_important_zones);
void format_time_string(char *buf, size_t size, const struct tm *tm);

#endif
