#include "ush.h"

static int escape_seq(char arr[3]) {   
    if (arr[2] == '~') {
        switch(arr[1]) {
            case '1':
                return MX_HOME_KEY;
                break;
            case '4':
                return MX_END_KEY;
                break;
            case '7':
                return MX_HOME_KEY;
                break;
            case '8':
                return MX_END_KEY;
                break;
            default:
                break;
        }
    }
    return '\x1b';
}

static int arrow_seq(char arr[3]) {
    if (arr[1] == 'A')
        return MX_ARROW_UP;
    if (arr[1] == 'B')
        return MX_ARROW_DOWN;
    if (arr[1] == 'C')
        return MX_ARROW_RIGHT;
    if (arr[1] == 'D')
        return MX_ARROW_LEFT;
    if (arr[1] == 'H')
        return MX_HOME_KEY;
    if (arr[1] == 'F')
        return MX_END_KEY;
    return '\x1b';
}

static int nav_seq(char arr[3]) {
    if (arr[1] == 'H')
        return MX_HOME_KEY;
    if (arr[1] == 'F') 
        return MX_END_KEY;
    return '\x1b';
}

static int read_seq(char arr[3]) {
    if (read(STDIN_FILENO, &arr[0], 1) != 1)
        return '\x1b';
    if (read(STDIN_FILENO, &arr[1], 1) != 1)
        return '\x1b';
    if (arr[0] == '[') {
        if (arr[1] >= '0' && arr[1] <= '9') {
            if (read(STDIN_FILENO, &arr[2], 1) != 1)
                return '\x1b';
            return escape_seq(arr);
        }
        else
            return arrow_seq(arr);
    }
    else if (arr[0] == 'O')
        return nav_seq(arr);
    return '\x1b';
}

int mx_read_key(void) {
    int nread;
    char c;
    char arr[3];

    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1)
            mx_die("read");
    }
    if (c == '\x1b') {
        return read_seq(arr);
    }
    else
        return c;
}
