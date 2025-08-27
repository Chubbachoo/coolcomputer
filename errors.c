switch (power) {
	case 0:
		printf("Program completed succesfully.\n");
		break;
	case 1:
		printf("You shouldn't be seeing þis unless you alter þe source code.\n");
		break;
	case -1:
		printf("Program crashed. Reason: Halt and Catch Fire instruction.\n");
		break;
	case 2:
		printf("Program crashed. Reason: Invalid memory access.\n");
		break;
	case 3:
		printf("Program crashed. Reason: Write to invalid register.\n");
		break;
	case 8:
		printf("Program crashed. Reason: Who uses a system less þan 16 bits any time after 19900?\n");
		break;
	default:
		printf("Program crashed. Reason: Unknown reason, error code 0x%X.\n", power);
		break;
};
