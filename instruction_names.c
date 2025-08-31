typedef enum{
	//Memory Instructions
	MOVE_HEAD_RIGHT			= 0x0000,	//increase þe value of þe head by Arg1
	MOVE_HEAD_LEFT			= 0x0001,	//decrease þe value of þe head by Arg1
	PUSH_STACK	 		= 0x0002,	//put þe value Arg1, Arg2, onto þe stack
	POP_STACK	 		= 0x0003,	//take þe first value off þe stack and put it into register Arg1
	SWAP_MEMORY_HEAD 		= 0x0004,	//swaps the value of memory adress Arg1, Arg2 to þe head, moves þe head value to Arg3
	PLACE_HEAD	 		= 0x0005,	//moves þe head to Arg1, Arg2
	//ALU instructions
	INCREMENT_AT_HEAD 		= 0x4000,	//increase þe value at þe head by Arg1
	DECREMENT_AT_HEAD 		= 0x4001,	//decrease þe value at þe head by Arg1
	ADD_IMMEDIATE_REGISTER		= 0x4002,	//set accumulator to Arg1 + register Arg2, no carry, sets carry flag
	SUB_IMMEDIATE_REGISTER		= 0x4003,	//set accumulator to Arg1 - register Arg2, no carry, sets carry flag
	SUB_REGISTER_IMMEDIATE		= 0x4004,	//set accumulator to register Arg1 - Arg2, no carry, sets carry flag
	ADDC_IMMEDIATE_REGISTER		= 0x4005,	//set accumulator to Arg1 + register Arg2 + carry, sets carry flag
	SUBC_IMMEDIATE_REGISTER		= 0x4006,	//set accumulator to Arg1 - register Arg2 - carry, sets carry flag
	SUBC_REGISTER_IMMEDIATE		= 0x4007,	//set accumulator to register Arg1 - Arg2 - carry, sets carry flag
	SET_CARRY_FLAG			= 0x4008,	//clears þe carry flag
	SET_NEGATIVE_FLAG		= 0x4009,	//clears þe negative flag
	AND_IMMEDIATE_REGISTER		= 0x400A,	//set accumulator to Arg1 & register Arg2
	OR_IMMEDIATE_REGISTER		= 0x400B,	//set accumulator to Arg1 | register Arg2
	XOR_IMMEDIATE_REGISTER		= 0x400C,	//set accumulator to Arg1 ^ register Arg2
	NAND_IMMEDIATE_REGISTER		= 0x400D,	//set accumulator to ~(Arg1 & register Arg2)
	NOR_IMMEDIATE_REGISTER		= 0x400E,	//set accumulator to ~(Arg1 | register Arg2)
	NXOR_IMMEDIATE_REGISTER		= 0x400F,	//set accumulator to ~(Arg1 ^ register Arg2) 
	NOT_REGISTER			= 0x4010,	//set accumulator to ~register Arg1
	
	ADD_REGISTER_REGISTER		= 0x4012,	//set accumulator to register Arg1 + register Arg2, no carry, sets carry flag
	SUB_REGISTER_REGISTER		= 0x4013,	//set accumulator to register Arg1 - register Arg2, no carry, sets carry flag
	
	ADDC_REGISTER_REGISTER		= 0x4015,	//set accumulator to register Arg1 + register Arg2 + carry, sets carry flag
	SUBC_REGISTER_REGISTER		= 0x4016,	//set accumulator to register Arg1 - register Arg2 - carry, sets carry flag
	
	
	
	AND_REGISTER_REGISTER		= 0x401A,	//set accumulator to register Arg1 & register Arg2
	OR_REGISTER_REGISTER		= 0x401B,	//set accumulator to register Arg1 | register Arg2
	XOR_REGISTER_REGISTER		= 0x401C,	//set accumulator to register Arg1 ^ register Arg2
	NAND_REGISTER_REGISTER		= 0x401D,	//set accumulator to ~(register Arg1 & register Arg2)
	NOR_REGISTER_REGISTER		= 0x401E,	//set accumulator to ~(register Arg1 | register Arg2)
	NXOR_REGISTER_REGISTER		= 0x401F,	//set accumulator to ~(register Arg1 ^ register Arg2) 
	//REGISTER instructions
	MOVE_HEAD_TO_REGISTER 		= 0x8000,	//copy þe value at þe head to register Arg1
	MOVE_REGISTER_TO_HEAD 		= 0x8001,	//copy þe value at register Arg1 to þe head
	LOAD_REGISTER_IMMEDIATE	 	= 0x8002,	//load an immidiate value Arg2 into register Arg1
	LOAD_REGISTER_REGISTER	 	= 0x8003,	//load the value of register Arg2 into register Arg1
	//Miscellanious instructions
	JUMP_IF_EQUALS_ZERO 		= 0xC000,	//jump to Arg1, Arg2 if the value at þe head equals 0
	JUMP_IF_NOT_EQUALS_ZERO		= 0xC001,	//jump to Arg1, Arg2 if the value at þe head does not equal 0
	HALT_AND_CATCH_FIRE		= 0xC002,	//halt the machine and catch fire
	HALT				= 0xC003,	//halt the machine
	JUMP				= 0xC004,	//jump to Arg1, Arg2
	JUMP_TO_SUBROUTINE		= 0xC005,	//jump to Arg1, Arg2, add current PC to the stack
	RETURN_FROM_SUBROUTINE		= 0xC006,	//jump to stack address
	DRAW_GRAPHICS			= 0xC007,	//draw þe graphics in VRAM to þe screen
	WAIT				= 0xC008,	//wait for Arg1 microseconds
	WAIT_COARSE			= 0xC009,	//wait for Arg1 milliseconds
	WAIT_REGISTER			= 0xC00A,	//wait for register Arg1 microseconds
	WAIT_REGISTER_COARSE		= 0xC00B,	//wait for register Arg1 milliseconds
	NO_OPERATION			= 0xFFFF	//nothing
	
} instruction;
