#include "console.h"
 
void main(void) 
{
	boot_console_puts("MinOS v0.0.0\n");
	for (int i = 0; i < 23; i++) {
		boot_console_puts("No Scroll Line\n");
	}

	for (int i = 0; i < 10; i++) {
		boot_console_puts("Scroll Line\n");
	}
}