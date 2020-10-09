#include <minos/core/services/console.h>

#include <stdarg.h>
#include <minos/core/hwitf/console.h>

#define MAX_INT_BUFFER 11

static inline void _itoa(int, char*, size_t);

static inline void _print_char(va_list params);
static inline int  _print_int(va_list params);
static inline int  _print_param(char, va_list);
static inline int  _print_str(va_list);

void putchar(char c) {
    console.putchar(c);
}

size_t puts(const char *str){
    size_t len;
    for (len = 0; str[len]; len++)
		  console.putchar(str[len]);
    return len;
}

size_t printf(const char *fmt, ...) {
    int nchars = 0;
    va_list params;
	va_start(params, fmt);

    while (*fmt != '\0') {
        switch(*fmt) {
        case '%':
            fmt++;
            nchars += _print_param(*fmt, params);
            fmt++;
            break;
        case '\\':
            fmt++;
            console.putchar(*fmt);
            fmt++;
            nchars++;
            break;
        default:
            console.putchar(*fmt);
            fmt++;
            nchars++;
        }
    }

    va_end(params);
    return nchars;
}

void _print_char(va_list params) {
    int c = va_arg(params, int);
    console.putchar(c);
}

int _print_int(va_list params) {
    int value = va_arg(params, int);
    char buffer[MAX_INT_BUFFER];
    _itoa(value, buffer, MAX_INT_BUFFER);
    return puts(buffer);
}

int _print_param(char type, va_list params) {
    int nchars = 0;
    switch (type){
    case 'c':
        _print_char(params);
        nchars++;
        break;
    case 'd':
        nchars += _print_int(params);
        break;
    case 's':
        nchars += _print_str(params);
        break;
    }
    return nchars;
}

int _print_str(va_list params) {
    return puts(va_arg(params, const char*));
}

void _itoa(int value, char *buffer, size_t buffer_size) {
    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    size_t i = 0;
    while (value != 0 && i < buffer_size - 1)
    {
        buffer[i++] = value % 10 + '0';
        value /= 10;
    }
    buffer[i] = '\0';

    for (size_t t = 0; t < i / 2; t++)
    {
        char tmp = buffer[i - t - 1];
        buffer[i - t - 1] = buffer[t];
        buffer[t] = tmp;
    }
}
