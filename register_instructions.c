switch (OPCODE){
	case MOVE_HEAD_TO_REGISTER:
		if(readmemory(HEAD_HIGH, HEAD_LOW, 0) == 0){
			PROGRAM_COUNTER_HIGH = ARG1;
			PROGRAM_COUNTER_LOW = ARG2;
			break;
		}
		increaseprogramcounter(4);
		break;
	case MOVE_REGISTER_TO_HEAD:
		if(readmemory(HEAD_HIGH, HEAD_LOW, 0) != 0){
			PROGRAM_COUNTER_HIGH = ARG1;
			PROGRAM_COUNTER_LOW = ARG2;
			break;
		}
		increaseprogramcounter(4);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
