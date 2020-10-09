#ifndef _KERNEL_CORE_SERVICES_CONSOLE
#define _KERNEL_CORE_SERVICES_CONSOLE

#include <stddef.h>

size_t printf(const char *fmt, ...);
void   putchar(char c);
size_t puts(const char *str);

#endif