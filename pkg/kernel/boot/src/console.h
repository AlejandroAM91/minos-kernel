#ifndef _KERNEL_BOOT_CONSOLE
#define _KERNEL_BOOT_CONSOLE

void boot_console_init();
void boot_console_putchar(char c);
void boot_console_puts(const char* data);

#endif