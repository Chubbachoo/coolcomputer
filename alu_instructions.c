switch (OPCODE){
	case INCREMENT_AT_HEAD:
		ACCUMULATOR = (readmemory(HEAD_HIGH, HEAD_LOW, 0) + ARG1);
		writememory(HEAD_HIGH, HEAD_LOW, 0, ACCUMULATOR);
		increaseprogramcounter(4);
		break;
	case DECREMENT_AT_HEAD:
		ACCUMULATOR = (readmemory(HEAD_HIGH, HEAD_LOW, 0) - ARG1);
		writememory(HEAD_HIGH, HEAD_LOW, 0, ACCUMULATOR);
		increaseprogramcounter(4);
		break;
	case ADD_IMMEDIATE_REGISTER:
		if (((int32_t)ARG1 + (int32_t)readfromregister(ARG2)) >= 65536) {
			FLAGS |= 1;
		}
		ACCUMULATOR = (ARG1 + readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case SUB_IMMEDIATE_REGISTER:
		if (((int32_t)ARG1 - (int32_t)readfromregister(ARG2)) <= 0) {
			FLAGS |= 3;
		}
		ACCUMULATOR = (ARG1 - readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case SUB_REGISTER_IMMEDIATE:
		if (((int32_t)readfromregister(ARG1) - (int32_t)ARG2) <= 0) {
			FLAGS |= 3;
		}
		ACCUMULATOR = (readfromregister(ARG1) - ARG2);
		increaseprogramcounter(4);
		break;
	case ADDC_IMMEDIATE_REGISTER:
		if(((int32_t)ARG1 + (int32_t)readfromregister(ARG2) + CARRY) >= 65536){
			FLAGS |= 1;
		}
		ACCUMULATOR = (ARG1 + readfromregister(ARG2) + CARRY);
		increaseprogramcounter(4);
		break;
	case SUBC_IMMEDIATE_REGISTER:
		if ((((int32_t)ARG1 - (int32_t)readfromregister(ARG2))- CARRY) <= 0) {
			FLAGS |= 3;
		}
		ACCUMULATOR = ((ARG1 - readfromregister(ARG2)) - CARRY);
		increaseprogramcounter(4);
		break;
	case SUBC_REGISTER_IMMEDIATE:
		if ((((int32_t)readfromregister(ARG1) - (int32_t)ARG2) - CARRY) <= 0) {
			FLAGS |= 3;
		}
		ACCUMULATOR = ((readfromregister(ARG1) - ARG2) - CARRY);
		increaseprogramcounter(4);
		break;
	case SET_CARRY_FLAG:
		FLAGS &= 0xFFFE;
		increaseprogramcounter(4);
		break;
	case SET_NEGATIVE_FLAG:
		FLAGS &= 0xFFFD;
		increaseprogramcounter(4);
		break;
	case AND_IMMEDIATE_REGISTER:
		ACCUMULATOR = ARG1 & readfromregister(ARG2);
		increaseprogramcounter(4);
		break;
	case OR_IMMEDIATE_REGISTER:
		ACCUMULATOR = ARG1 | readfromregister(ARG2);
		increaseprogramcounter(4);
		break;
	case XOR_IMMEDIATE_REGISTER:
		ACCUMULATOR = ARG1 ^ readfromregister(ARG2);
		increaseprogramcounter(4);
		break;
	case NAND_IMMEDIATE_REGISTER:
		ACCUMULATOR = ~(ARG1 & readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case NOR_IMMEDIATE_REGISTER:
		ACCUMULATOR = ~(ARG1 | readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case NXOR_IMMEDIATE_REGISTER:
		ACCUMULATOR = ~(ARG1 ^ readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case NOT_REGISTER:
		ACCUMULATOR = readfromregister(ARG1);
		increaseprogramcounter(4);
		break;
	
	
	
	
	case ADD_REGISTER_REGISTER:
		if (((int32_t)readfromregister(ARG1) + (int32_t)readfromregister(ARG2)) >= 65536) {
			FLAGS |= 1;
		}
		ACCUMULATOR = (readfromregister(ARG1) + readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case SUB_REGISTER_REGISTER:
		if (((int32_t)readfromregister(ARG1) - (int32_t)readfromregister(ARG2)) <= 0) {
			FLAGS |= 3;
		}
		ACCUMULATOR = (readfromregister(ARG1) - readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	
	
	
	
	case ADDC_REGISTER_REGISTER:
		if(((int32_t)readfromregister(ARG1) + (int32_t)readfromregister(ARG2) + CARRY) >= 65536){
			FLAGS |= 1;
		}
		ACCUMULATOR = (readfromregister(ARG1) + readfromregister(ARG2) + CARRY);
		increaseprogramcounter(4);
		break;
	case SUBC_REGISTER_REGISTER:
		if ((((int32_t)readfromregister(ARG1) - (int32_t)readfromregister(ARG2))- CARRY) <= 0) {
			FLAGS |= 3;
		}
		ACCUMULATOR = ((readfromregister(ARG1) - readfromregister(ARG2)) - CARRY);
		increaseprogramcounter(4);
		break;
	
	
	
	
	
	
	case MULTIPLY_REGISTER_IMMEDIATE:
		ACCUMULATOR = (readfromregister(ARG1) * ARG2);
		increaseprogramcounter(4);
		break;
	case MULTIPLY_REGISTER_REGISTER:
		ACCUMULATOR = (readfromregister(ARG1) * readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case AND_REGISTER_REGISTER:
		ACCUMULATOR = readfromregister(ARG1) & readfromregister(ARG2);
		increaseprogramcounter(4);
		break;
	case OR_REGISTER_REGISTER:
		ACCUMULATOR = readfromregister(ARG1) | readfromregister(ARG2);
		increaseprogramcounter(4);
		break;
	case XOR_REGISTER_REGISTER:
		ACCUMULATOR = readfromregister(ARG1) ^ readfromregister(ARG2);
		increaseprogramcounter(4);
		break;
	case NAND_REGISTER_REGISTER:
		ACCUMULATOR = ~(readfromregister(ARG1) & readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case NOR_REGISTER_REGISTER:
		ACCUMULATOR = ~(readfromregister(ARG1) | readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	case NXOR_REGISTER_REGISTER:
		ACCUMULATOR = ~(readfromregister(ARG1) ^ readfromregister(ARG2));
		increaseprogramcounter(4);
		break;
	default:
		increaseprogramcounter(4);
		break;
};
