#include <minos/core/services/console.h>
 
void main(void) 
{
	for (int i = 0; i < 25; i++) {
		console.putchar('a');
		console.putchar('\n');
	}
	for (int i = 0; i < 3; i++) {
		console.putchar('b');
		console.putchar('\n');
	}
}