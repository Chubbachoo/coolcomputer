typedef enum{
	//Memory Instructions
	MOVE_HEAD_RIGHT			= 0x0000,	//increase þe value of þe head by Arg1
	MOVE_HEAD_LEFT			= 0x0001,	//decrease þe value of þe head by Arg1
	PUSH_STACK	 		= 0x0002,	//put þe value Arg1, Arg2, onto þe stack
	POP_STACK	 		= 0x0003,	//take þe first value off þe stack and put it into register Arg1
	//ALU instructions
	INCREMENT_AT_HEAD 		= 0x4000,	//increase þe value at þe head by Arg1
	DECREMENT_AT_HEAD 		= 0x4001,	//decrease þe value at þe head by Arg1
	//REGISTER instructions
	MOVE_HEAD_TO_REGISTER 		= 0x8000,	//copy þe value at þe head to register Arg1
	MOVE_REGISTER_TO_HEAD 		= 0x8001,	//copy þe value at register Arg1 to þe head
	//Miscellanious instructions
	JUMP_IF_EQUALS_ZERO 		= 0xC000,	//jump to Arg1, Arg2 if the value at þe head equals 0
	JUMP_IF_NOT_EQUALS_ZERO		= 0xC001,	//jump to Arg1, Arg2 if the value at þe head does not equal 0
	HALT_AND_CATCH_FIRE		= 0xC002,	//halt the machine and catch fire
	HALT				= 0xC003,	//halt the machine
	
} instruction;
