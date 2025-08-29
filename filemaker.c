#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint16_t program[0x01000000];
char text[sizeof(program)];

#include "instruction_names.c"

int main(){
	FILE *flie = fopen("cartridge.cart", "w");
	#include "output.txt"
	memcpy(text, program, sizeof(program));
	fwrite(text, 1, sizeof(text), flie);
	return 0;
}
