#define TEST_MODE
#include "localtimes.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_get_color_type() {
    const char *current = "Asia/Tokyo";
    const char *important[] = {"America/Los_Angeles", "Europe/London"};
    int num_important = 2;

    assert(get_color_type("Asia/Tokyo", current, important, num_important) == COLOR_CURRENT);
    assert(get_color_type("America/Los_Angeles", current, important, num_important) == COLOR_IMPORTANT);
    assert(get_color_type("Europe/London", current, important, num_important) == COLOR_IMPORTANT);
    assert(get_color_type("UTC", current, important, num_important) == COLOR_NONE);
    printf("test_get_color_type passed\n");
}

void test_format_time_string() {
    struct tm tm = {0};
    tm.tm_year = 126; // 2026 (years since 1900)
    tm.tm_mon = 3;   // April (0-11)
    tm.tm_mday = 17;
    tm.tm_wday = 5;  // Friday (0-6)
    tm.tm_hour = 10;
    tm.tm_min = 30;
    tm.tm_sec = 15;
    tm.tm_isdst = 0;

    char buf[128];
    format_time_string(buf, sizeof(buf), &tm);
    // Note: format_time_string uses "%... %s" which adds a space before DST marker.
    // If DST is 0, it appends "" so there is a trailing space.
    assert(strcmp(buf, "2026/04/17 (Fri) 10:30:15 ") == 0);

    tm.tm_isdst = 1;
    format_time_string(buf, sizeof(buf), &tm);
    assert(strcmp(buf, "2026/04/17 (Fri) 10:30:15 *") == 0);

    printf("test_format_time_string passed\n");
}

int main() {
    test_get_color_type();
    test_format_time_string();
    printf("All unit tests passed!\n");
    return 0;
}
