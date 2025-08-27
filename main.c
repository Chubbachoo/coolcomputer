#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

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
#define IINPUT_2 registers[0xB]
#define OPCODE registers[0xC]
#define ARG1 registers[0xD]
#define ARG2 registers[0xE]
#define ARG3 registers[0xF]

#include "instruction_names.c"

void loadprogram(){
	memory[0x03000000] = LOAD_REGISTER_IMMEDIATE;
	memory[0x03000001] = 0x0004;
	memory[0x03000002] = 0xFFFF;
	memory[0x03000003] = 0x0000;
	memory[0x03000004] = MOVE_REGISTER_TO_HEAD;
	memory[0x03000005] = 0x0004;
	memory[0x03000006] = 0x0000;
	memory[0x03000007] = 0x0000;
	memory[0x03000008] = JUMP_IF_NOT_EQUALS_ZERO;
	memory[0x03000009] = 0x0300;
	memory[0x0300000A] = 0x0008;
	memory[0x0300000B] = 0x0000;
	
	memory[0x03FFFFFC] = HALT_AND_CATCH_FIRE;
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


int main(){
	powerup();
	while (power == 1){
		printf("pc 0x%X\r", reword(PROGRAM_COUNTER_HIGH, PROGRAM_COUNTER_LOW, 0));
		interpretinstruction(PROGRAM_COUNTER_HIGH, PROGRAM_COUNTER_LOW);
		/*printf("opcode 0x%X\n", OPCODE);
		printf("0x%X\n", ARG1);
		printf("0x%X\n", ARG2);
		printf("0x%X\n", ARG3);
		printf("accumulator 0x%X\n", ACCUMULATOR);
		printf("head 0x%X\n", readmemory(HEAD_HIGH, HEAD_LOW, 0));
		usleep(1000000);*/
	}
	#include "errors.c"
	return power;
}
