#ifndef _KERNEL_CORE_HWITF_CONSOLE
#define _KERNEL_CORE_HWITF_CONSOLE

#include <minos/shared/glo.h>

struct console {
    void (*putchar)(char);
};

EXTERN struct console console;

#endif