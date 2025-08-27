switch (OPCODE){
	case INCREMENT_AT_HEAD:
		ACCUMULATOR = (readmemory(HEAD_HIGH, HEAD_LOW, 0) + ARG1);
		writememory(HEAD_HIGH, HEAD_LOW, 0, ACCUMULATOR);
		increaseprogramcounter(4);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
