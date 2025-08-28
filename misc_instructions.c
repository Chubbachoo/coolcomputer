switch (OPCODE){
	case JUMP_IF_EQUALS_ZERO:
		if(readmemory(HEAD_HIGH, HEAD_LOW, 0) == 0){
			PROGRAM_COUNTER_HIGH = ARG1;
			PROGRAM_COUNTER_LOW = ARG2;
			break;
		}
		increaseprogramcounter(4);
		break;
	case JUMP_IF_NOT_EQUALS_ZERO:
		if(readmemory(HEAD_HIGH, HEAD_LOW, 0) != 0){
			PROGRAM_COUNTER_HIGH = ARG1;
			PROGRAM_COUNTER_LOW = ARG2;
			break;
		}
		increaseprogramcounter(4);
		break;
	case HALT_AND_CATCH_FIRE:
		power = -1;
		break;
	case HALT:
		power = 0;
		break;
	case JUMP:
		PROGRAM_COUNTER_HIGH = ARG1;
		PROGRAM_COUNTER_LOW = ARG2;
		break;
	case JUMP_TO_SUBROUTINE:
		writememory(0x01FE, STACK_HEIGHT, 0, PROGRAM_COUNTER_HIGH);
		writememory(0x01FF, STACK_HEIGHT, 0, PROGRAM_COUNTER_LOW);
		STACK_HEIGHT += 1;
		PROGRAM_COUNTER_HIGH = ARG1;
		PROGRAM_COUNTER_LOW = ARG2;
		break;
	case RETURN_FROM_SUBROUTINE:
		STACK_HEIGHT -= 1;
		PROGRAM_COUNTER_HIGH = readmemory(0x01FE, STACK_HEIGHT, 0);
		PROGRAM_COUNTER_LOW = readmemory(0x01FF, STACK_HEIGHT, 0);
		increaseprogramcounter(4);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
