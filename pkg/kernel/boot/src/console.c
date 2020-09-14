#include "console.h"

#include <stddef.h>
#include <stdint.h>

#define BOOT_CONSOLE_BUFFER 0xB8000 // vga buffer
#define BOOT_CONSOLE_COLOR  0x0700 // bg = black, fg = light grey
#define BOOT_CONSOLE_HEIGHT 25
#define BOOT_CONSOLE_WIDTH  80

struct console_pos {
    size_t row;
    size_t col;
} boot_console_pos;

 
uint16_t* boot_console_buffer;

static inline uint16_t boot_console_entry(unsigned char uc) {
	return (uint16_t) BOOT_CONSOLE_COLOR | (uint16_t) uc;
}

void boot_console_init() {
    boot_console_pos.row = 0;
	boot_console_pos.col = 0;
    boot_console_buffer = (uint16_t*) BOOT_CONSOLE_BUFFER;
	for (size_t i = 0; i < BOOT_CONSOLE_HEIGHT * BOOT_CONSOLE_WIDTH; i++) {
		boot_console_buffer[i] = boot_console_entry(' ');
	}

}

void boot_console_putchar(char c) {
	const size_t index = boot_console_pos.row * BOOT_CONSOLE_WIDTH + boot_console_pos.col;
	boot_console_buffer[index] = boot_console_entry(c);
	boot_console_pos.col += 1;
	if (boot_console_pos.col == BOOT_CONSOLE_WIDTH) {
		boot_console_pos.col = 0;
		boot_console_pos.row += 1;
		if (boot_console_pos.row == BOOT_CONSOLE_HEIGHT) {
			boot_console_pos.row = 0;
		}
	}
}

void boot_console_puts(const char* data) {
	for (size_t i = 0; data[i]; i++) {
		boot_console_putchar(data[i]);
	}
}
