#include "console.h"

#include <stddef.h>
#include <stdint.h>

#include <minos/core/services/console.h>


#define BOOT_CONSOLE_BUFFER 	0xB8000 // vga buffer
#define BOOT_CONSOLE_COLOR  	0x0700 // bg = black, fg = light grey
#define BOOT_CONSOLE_HEIGHT 	25
#define BOOT_CONSOLE_WIDTH  	80
#define BOOT_CONSOLE_LAST_LINE	(BOOT_CONSOLE_HEIGHT - 1) * BOOT_CONSOLE_WIDTH

struct boot_console_pos {
    size_t row;
    size_t col;
} _boot_console_pos;

uint16_t* _boot_console_buffer;

static inline void      _boot_console_clear();
static inline uint16_t  _boot_console_entry(unsigned char uc);
static inline void      _boot_console_newline();
static inline void      _boot_console_putchar(char c);
static inline void      _boot_console_scroll();

void boot_console_init()  {
    _boot_console_buffer = (uint16_t*) BOOT_CONSOLE_BUFFER;
    _boot_console_clear();
	console.putchar = &boot_console_putchar;
}

void boot_console_putchar(char c) {
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

void _boot_console_clear() {
    _boot_console_pos.row = 0;
	_boot_console_pos.col = 0;
    for (size_t i = 0; i < BOOT_CONSOLE_HEIGHT * BOOT_CONSOLE_WIDTH; i++) {
		_boot_console_buffer[i] = _boot_console_entry(' ');
	}
}

static inline uint16_t _boot_console_entry(unsigned char uc) {
	return (uint16_t) BOOT_CONSOLE_COLOR | (uint16_t) uc;
}

static inline void _boot_console_newline() {
	_boot_console_pos.col = 0;
	_boot_console_pos.row += 1;
	if (_boot_console_pos.row == BOOT_CONSOLE_HEIGHT) {
		_boot_console_scroll();
	}
}

static inline void _boot_console_putchar(char c) {
	const size_t index = _boot_console_pos.row * BOOT_CONSOLE_WIDTH + _boot_console_pos.col;
	_boot_console_buffer[index] = _boot_console_entry(c);
	_boot_console_pos.col += 1;
	if (_boot_console_pos.col == BOOT_CONSOLE_WIDTH) {
		_boot_console_newline();
	}
}

static inline void _boot_console_scroll() {
	for (size_t i = 0; i < BOOT_CONSOLE_LAST_LINE; i++) {
		_boot_console_buffer[i] = _boot_console_buffer[i + BOOT_CONSOLE_WIDTH];
	}

	for (size_t i = 0; i < BOOT_CONSOLE_WIDTH; i++) {
		_boot_console_buffer[i + BOOT_CONSOLE_LAST_LINE] = _boot_console_entry(' ');
	}
	_boot_console_pos.row -= 1;
}
