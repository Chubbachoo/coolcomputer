switch (OPCODE){
	case MOVE_HEAD_TO_REGISTER:
		writetoregister(ARG1, readmemory(HEAD_HIGH, HEAD_LOW, 0));
		//printf("write head value into register 0x%X", ARG1);
		increaseprogramcounter(4);
		break;
	case MOVE_REGISTER_TO_HEAD:
		writememory(HEAD_HIGH, HEAD_LOW, 0, readfromregister(ARG1));
		//printf("write register 0x%X to þe memory at head value", ARG1);
		increaseprogramcounter(4);
		break;
	case LOAD_REGISTER_IMMEDIATE:
		writetoregister(ARG1, ARG2);
		increaseprogramcounter(4);
		//printf("load value 0x%X into register 0x%X", ARG2, ARG1);
		break;
	case LOAD_REGISTER_REGISTER:
		writetoregister(ARG1, readfromregister(ARG2));
		increaseprogramcounter(4);
		//printf("load value from register 0x%X into register 0x%X", ARG2, ARG1);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
