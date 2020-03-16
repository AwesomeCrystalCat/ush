#include "libmx.h"

static void two_byte_print(wchar_t c) {
    char arr[3] = {0};

    arr[0] = (c >> 6 & 0x1F) | 0xC0;
    arr[1] = (c & 0x3F) | 0x80;
    write(1, arr, mx_strlen(arr));
}

static void three_byte_print(wchar_t c) {
    char arr[4] = {0};

    arr[0] = (c >> 12 & 0x0F) | 0xE0;
    arr[1] = (c >> 6 & 0x3F) | 0x80;
    arr[2] = (c & 0x3F) | 0x80;
    write(1, arr, mx_strlen(arr));
}

static void four_byte_print(wchar_t c) {
    char arr[5] = {0};

    arr[0] = (c >> 18 & 0x07) | 0xF0;
    arr[1] = (c >> 12 & 0x3F) | 0x80;
    arr[2] = (c >> 6 & 0x3F) | 0x80;
    arr[3] = (c & 0x3F) | 0x80;
    write(1, arr, mx_strlen(arr));
}

void mx_print_unicode(wchar_t c) {
    if (c < 0x80)
        write(1, &c, 1);
    else if (c < 0x0800)
        two_byte_print(c);
    else if (c < 0x010000)
        three_byte_print(c);
    else
        four_byte_print(c);
}
