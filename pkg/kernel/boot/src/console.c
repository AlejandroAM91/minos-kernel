#include "console.h"

#include <stddef.h>
#include <stdint.h>

#define BOOT_CONSOLE_BUFFER 	0xB8000 // vga buffer
#define BOOT_CONSOLE_COLOR  	0x0700 // bg = black, fg = light grey
#define BOOT_CONSOLE_HEIGHT 	25
#define BOOT_CONSOLE_WIDTH  	80
#define BOOT_CONSOLE_LAST_LINE	(BOOT_CONSOLE_HEIGHT - 1) * BOOT_CONSOLE_WIDTH

struct console_pos {
    size_t row;
    size_t col;
} boot_console_pos;

 
uint16_t* boot_console_buffer;

static inline uint16_t _boot_console_entry(unsigned char uc);
static inline void _boot_console_newline();
static inline void _boot_console_putchar(char c);
static inline void _boot_console_scroll();

void boot_console_init() {
    boot_console_pos.row = 0;
	boot_console_pos.col = 0;
    boot_console_buffer = (uint16_t*) BOOT_CONSOLE_BUFFER;
	for (size_t i = 0; i < BOOT_CONSOLE_HEIGHT * BOOT_CONSOLE_WIDTH; i++) {
		boot_console_buffer[i] = _boot_console_entry(' ');
	}
}

void boot_console_putc(char c) {
	switch (c)
	{
	case '\n':
		_boot_console_newline();
		break;
	
	default:
		_boot_console_putchar(c);
		break;
	}
}

void boot_console_puts(const char* data) {
	for (size_t i = 0; data[i]; i++) {
		boot_console_putc(data[i]);
	}
}

static inline uint16_t _boot_console_entry(unsigned char uc) {
	return (uint16_t) BOOT_CONSOLE_COLOR | (uint16_t) uc;
}

static inline void _boot_console_newline() {
	boot_console_pos.col = 0;
	boot_console_pos.row += 1;
	if (boot_console_pos.row == BOOT_CONSOLE_HEIGHT) {
		_boot_console_scroll();
	}
}

static inline void _boot_console_putchar(char c) {
	const size_t index = boot_console_pos.row * BOOT_CONSOLE_WIDTH + boot_console_pos.col;
	boot_console_buffer[index] = _boot_console_entry(c);
	boot_console_pos.col += 1;
	if (boot_console_pos.col == BOOT_CONSOLE_WIDTH) {
		_boot_console_newline();
	}
}

static inline void _boot_console_scroll() {
	for (size_t i = 0; i < BOOT_CONSOLE_LAST_LINE; i++) {
		boot_console_buffer[i] = boot_console_buffer[i + BOOT_CONSOLE_WIDTH];
	}

	for (size_t i = 0; i < BOOT_CONSOLE_WIDTH; i++) {
		boot_console_buffer[i + BOOT_CONSOLE_LAST_LINE] = _boot_console_entry(' ');
	}
	boot_console_pos.row -= 1;
}
