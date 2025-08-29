static uint16_t program_words[0x01000000];
FILE *flie = fopen("cartridge.cart", "r");

if (flie != NULL){
	fread(&program_words, sizeof(uint16_t), 0x01000000, flie);
	/*printf("0x%X\n", program_words[0]);
	printf("0x%X\n", program_words[1]);
	printf("0x%X\n", program_words[2]);
	printf("0x%X\n", program_words[3]);*/
	
	for (uint32_t i = 0; i < 0x01000000; i++) {
		memory[(0x03000000 + i)] = program_words[(i)];
	}
	//memcpy((void*)((uintptr_t)&memory + 0x0300000), &program_words, sizeof(uint16_t));
	
	/*printf("0x%X\n", memory[0x03000000]);
	printf("0x%X\n", memory[0x03000001]);
	printf("0x%X\n", memory[0x03000002]);
	printf("0x%X\n", memory[0x03000003]);*/
} else {
	perror("Could not find a file named cartridge.cart, please rename or provide one.");
}
