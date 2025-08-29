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
	case DRAW_GRAPHICS:
		FLAGS |= 0x8000;
		memory[0x01000000] = ARG1;
		increaseprogramcounter(4);
		break;
	case WAIT:
		usleep(ARG1);
		increaseprogramcounter(4);
		break;
	case WAIT_COARSE:
		usleep((uint32_t)(ARG1) * 1000);
		increaseprogramcounter(4);
		break;
	case WAIT_REGISTER:
		usleep(readfromregister(ARG1));
		increaseprogramcounter(4);
		break;
	case WAIT_REGISTER_COARSE:
		usleep((uint32_t)(readfromregister(ARG1)) * 1000);
		increaseprogramcounter(4);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
