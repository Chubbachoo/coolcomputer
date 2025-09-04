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
	case PLACE_HEAD_REGISTER:
		writetoregister(0x02, readfromregister(ARG1));
		writetoregister(0x03, readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case SET_MEMORY_IMMEDIATE:
		writememory(ARG1, ARG2, 0, ARG3);
		increaseprogramcounter(4);
		break;
	case SET_MEMORY_ZEROPAGE:
		writememory(ARG1, ARG2, 0, readmemory(0x0000, ARG3, 0));
		increaseprogramcounter(4);
		break;
	case SET_ZEROPAGE_MEMORY:
		writememory(0x0000, ARG1, 0, readmemory(ARG2, ARG3, 0));
		increaseprogramcounter(4);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
