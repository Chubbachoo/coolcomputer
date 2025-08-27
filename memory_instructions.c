switch (OPCODE){
	case MOVE_HEAD_RIGHT:
		increasehead(ARG1);
		increaseprogramcounter(4);
		break;
	case MOVE_HEAD_LEFT:
		increasehead(-ARG1);
		increaseprogramcounter(4);
		break;
	case PUSH_STACK:
		writememory(0x01FE, STACK_HEIGHT, 0, ARG1);
		writememory(0x01FF, STACK_HEIGHT, 0, ARG2);
		STACK_HEIGHT += 1;
		increaseprogramcounter(4);
		break;
	case POP_STACK:
		STACK_HEIGHT -= 1;
		writetoregister(ARG1, readmemory(0x01FE, STACK_HEIGHT, 0));
		writetoregister(ARG2, readmemory(0x01FF, STACK_HEIGHT, 0));
		increaseprogramcounter(4);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
