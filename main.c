#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <math.h>
#include <SDL3/SDL.h>

volatile uint16_t memory[0x04000000];
/*	memory
		0x00000000-0x0000FFFF - 0-page
		0x00000000-0x00FFFFFF - Working RAM
		0x01000000-0x017FFFFF - Video RAM
		0x01800000-0x01FDFFFF - Audio RAM
		0x01FE0000-0x01FEFFFF - High Stack
		0x01FF0000-0x01FFFFFF - Low Stack
		0x02000000-0x0200000F - Cartridge Swap Bank
		0x02000010-0x02FFFFFF - Cartridge Swap
		0x03000000-0x03FFFFFF - Cartridge Static
*/
volatile uint16_t registers[0x10];
/*	registers:
		0 - Program counter high bit
		1 - Program counter low bit
		2 - Head high bit
		3 - Head low bit
		4 - Accumulator
		5 - General purpose X
		6 - General purpose Y
		7 - Zero
		8 - Stack Height
		9 - Flags
		A - Input 1
		B - Input 2
		C - Opcode
		D - Arg1
		E - Arg2
		F - Arg3

*/
/*
	Flags
		1s - Carry
		2s - Negative
		4s - 
		8s - 
		10s - 
		20s - 
		40s - 
		80s - 
		100s - 
		200s - 
		400s - 
		800s - 
		1000s - 
		2000s - 
		4000s - 
		8000s - Draw Screen
*/

int8_t power = 0;

#define PROGRAM_COUNTER_HIGH registers[0x0]
#define PROGRAM_COUNTER_LOW registers[0x1]
#define HEAD_HIGH registers[0x2]
#define HEAD_LOW registers[0x3]
#define ACCUMULATOR registers[0x4]
#define GENERAL_PURPOSE_X registers[0x5]
#define GENERAL_PURPOSE_Y registers[0x6]
#define ZERO registers[0x7]
#define STACK_HEIGHT registers[0x8]
#define FLAGS registers[0x9]
#define INPUT_1 registers[0xA]
#define INPUT_2 registers[0xB]
#define OPCODE registers[0xC]
#define ARG1 registers[0xD]
#define ARG2 registers[0xE]
#define ARG3 registers[0xF]

#define CARRY (registers[0x9] & 1)
#define NEGATIVE ((registers[0x9] & 2) << 1)
#define DRAW_SCREEN ((registers[0x9] & 0x8000) << 15)

#define KEYCODE_UP 0x0001
#define KEYCODE_RIGHT 0x0002
#define KEYCODE_DOWN 0x0004
#define KEYCODE_LEFT 0x0008
#define KEYCODE_A 0x0010
#define KEYCODE_B 0x0020
#define KEYCODE_X 0x0040
#define KEYCODE_Y 0x0080
#define KEYCODE_L 0x0100
#define KEYCODE_R 0x0200
#define KEYCODE_MENU 0x0400
#define KEYCODE_ESCAPE 0x0800
#define KEYCODE_NORÞ 0x1000
#define KEYCODE_SOUÞ 0x2000
#define KEYCODE_EAST 0x4000
#define KEYCODE_WEST 0x8000

#include "instruction_names.c"

void loadprogram(){
	
	memory[0x03FFFFFC] = HALT_AND_CATCH_FIRE;
	#include "file_loading.c"
}

void memory_setup(){
	PROGRAM_COUNTER_HIGH = 0x300;
	PROGRAM_COUNTER_LOW = 0x0;
	HEAD_HIGH = 0x0;
	HEAD_LOW = 0x0;
	ZERO = 0x0;
	STACK_HEIGHT = 0x0;
	loadprogram();
}

void powerup(){
	power = 1;
	memory_setup();
}

uint32_t reword(uint16_t highword, uint16_t lowword, int32_t offset){
	return (((uint32_t)highword << 16) + lowword + offset);
}
uint16_t readmemory(uint16_t highword, uint16_t lowword, int32_t offset){
	if (reword(highword, lowword, offset) >= 0x04000000){
		printf("Log: Invalid memory read.\n");
		return 0;
	}
	return (memory[reword(highword, lowword, offset)]);
}
void writememory(uint16_t highword, uint16_t lowword, int32_t offset, uint16_t value){
	if (reword(highword, lowword, offset) >= 0x03000000){
		power = 2;
		return;
	}
	memory[reword(highword, lowword, offset)] = value;
	return;
}
void increaseprogramcounter(uint16_t offset){
	PROGRAM_COUNTER_HIGH = (reword(PROGRAM_COUNTER_HIGH, PROGRAM_COUNTER_LOW, offset) >> 16);
	PROGRAM_COUNTER_LOW += offset;
}
void increasehead(int32_t offset){
	HEAD_HIGH = (reword(HEAD_HIGH, HEAD_LOW, offset) >> 16);
	HEAD_LOW += offset;
}
uint16_t readfromregister(uint16_t index){
	if (index < 0x10){
		return registers[index];
	} else {
		printf("Log: Invalid Register Read");
		return 0;
	}
}
void writetoregister(uint16_t index, uint16_t value){
	if (index < 0x10 && index != 0x07){
		registers[index] = value;
	} else if (index == 0x07){
		return;
	} else {
		power = 3;
	}
}




int main(){
	powerup();
	#include "video.c"
	void interpretinstruction(uint16_t highword, uint16_t lowword){
		OPCODE = readmemory(highword, lowword, 0);
		ARG1 = readmemory(highword, lowword, 1);
		ARG2 = readmemory(highword, lowword, 2);
		ARG3 = readmemory(highword, lowword, 3);
		if (OPCODE >= 0xC000){
			#include "misc_instructions.c"
		} else if (OPCODE >= 0x8000){
			#include "register_instructions.c"
		} else if (OPCODE >= 0x4000){
			#include "alu_instructions.c"
		} else {
			#include "memory_instructions.c"
		}
	}
	while (power == 1){
		//printf("pc 0x%X\r", reword(PROGRAM_COUNTER_HIGH, PROGRAM_COUNTER_LOW, 0));
		interpretinstruction(PROGRAM_COUNTER_HIGH, PROGRAM_COUNTER_LOW);
		/*printf("opcode 0x%X\n", OPCODE);
		printf("0x%X\n", ARG1);
		printf("0x%X\n", ARG2);
		printf("0x%X\n", ARG3);
		printf("accumulator 0x%X\n", ACCUMULATOR);
		printf("head 0x%X\n", readmemory(HEAD_HIGH, HEAD_LOW, 0));
		usleep(1000000);*/
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_EVENT_TERMINATING:
					power = 0;
					break;
				case SDL_EVENT_LOW_MEMORY:
					power = 0;
					break;
				case SDL_EVENT_QUIT:
					power = 0;
					break;
				case SDL_EVENT_KEY_DOWN:
					switch(event.key.key){
						case SDLK_W:
							INPUT_1 |= KEYCODE_UP;
							break;
						case SDLK_A:
							INPUT_1 |= KEYCODE_LEFT;
							break;
						case SDLK_S:
							INPUT_1 |= KEYCODE_DOWN;
							break;
						case SDLK_D:
							INPUT_1 |= KEYCODE_RIGHT;
							break;
						case SDLK_Z:
							INPUT_1 |= KEYCODE_A;
							break;
						case SDLK_X:
							INPUT_1 |= KEYCODE_B;
							break;
						case SDLK_C:
							INPUT_1 |= KEYCODE_X;
							break;
						case SDLK_V:
							INPUT_1 |= KEYCODE_Y;
							break;
					}
					break;
				case SDL_EVENT_KEY_UP:
					switch(event.key.key){
						case SDLK_W:
							INPUT_1 &= ~KEYCODE_UP;
							break;
						case SDLK_A:
							INPUT_1 &= ~KEYCODE_LEFT;
							break;
						case SDLK_S:
							INPUT_1 &= ~KEYCODE_DOWN;
							break;
						case SDLK_D:
							INPUT_1 &= ~KEYCODE_RIGHT;
							break;
						case SDLK_Z:
							INPUT_1 &= ~KEYCODE_A;
							break;
						case SDLK_X:
							INPUT_1 &= ~KEYCODE_B;
							break;
						case SDLK_C:
							INPUT_1 &= ~KEYCODE_X;
							break;
						case SDLK_V:
							INPUT_1 &= ~KEYCODE_Y;
							break;
					}
					break;
			}
		}
		#include "PPU.c"
	}
	#include "errors.c"
	return power;
}
