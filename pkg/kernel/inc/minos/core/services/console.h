#ifndef _KERNEL_CORE_SERVICES_CONSOLE
#define _KERNEL_CORE_SERVICES_CONSOLE

#include <minos/shared/glo.h>

EXTERN struct console {
    void (*putchar)(char);
} console;

// void putchar(char);

#endif