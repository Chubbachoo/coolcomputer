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
	case SWAP_MEMORY_HEAD:
		writetoregister(ARG3, readmemory(HEAD_HIGH, HEAD_LOW, 0));
		writememory(HEAD_HIGH, HEAD_LOW, 0, readmemory(ARG1, ARG2, 0));
		increaseprogramcounter(4);
		break;
	case PLACE_HEAD:
		writetoregister(0x02, ARG1);
		writetoregister(0x03, ARG2);
		increaseprogramcounter(4);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
