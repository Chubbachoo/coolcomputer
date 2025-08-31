/*
	VRAM map
	0x01000000 - 0x010000FF		header
	0x01000100 - 0x01000FFF		pallette
	0x01001000 - 0x0100FFFF		unused
	0x01010000 - 0x0101FFFF		tile bank 1
	0x01020000 - 0x0102FFFF		tile bank 2
	0x01030000 - 0x0103FFFF		tile bank 3
	0x01041000 - 0x0104FFFF		tile bank 4
	0x01050000 - 0x0105FFFF		tile bank 5
	0x01060000 - 0x0106FFFF		tile bank 6
	0x01071000 - 0x0107FFFF		tile bank 7
	0x01080000 - 0x0108FFFF		sprite bank 0
	0x01090000 - 0x0109FFFF		sprite bank 1
	0x010A0000 - 0x010AFFFF		sprite bank 2
	0x010B1000 - 0x010BFFFF		sprite bank 3
	0x010C0000 - 0x010CFFFF		sprite bank 4
	0x010D0000 - 0x010DFFFF		sprite bank 5
	0x010E0000 - 0x010EFFFF		sprite bank 6
	0x010F0000 - 0x010FFFFF		sprite bank 7
	0x01100000 - 0x017FFFFF		image data
*/
/*
	graphics mode 00
		raw data, dichrome rg0
	graphics mode 01
		raw data, dichrome r0b
	graphics mode 02
		raw data, dichrome 0gb
*/
if(DRAW_SCREEN) {
	switch(memory[0x01000000]) {
		case 0x0000:
			for(uint8_t i_y = 0; i_y !=0xE0 ; i_y++){
				for(uint8_t ii_x = 0; ii_x !=0x80; ii_x++){
					SDL_SetRenderDrawColor(renderer, (uint8_t)((memory[0x01100000 + (i_y*128) + ii_x]) >> 8), (uint8_t)(memory[0x01100000 + (i_y*128) + ii_x]), 0x00, 0xFF);
					SDL_RenderPoint(renderer, (ii_x * 2), i_y);
					SDL_RenderPoint(renderer, (ii_x * 2) + 1, i_y);
				}
			}
			SDL_RenderPresent(renderer);
			break;
		case 0x0001:
			for(uint8_t i_y = 0; i_y !=0xE0 ; i_y++){
				for(uint8_t ii_x = 0; ii_x !=0x80; ii_x++){
					SDL_SetRenderDrawColor(renderer, (uint8_t)((memory[0x01100000 + (i_y*128) + ii_x]) >> 8), 0x00, (uint8_t)(memory[0x01100000 + (i_y*128) + ii_x]), 0xFF);
					SDL_RenderPoint(renderer, (ii_x * 2), i_y);
					SDL_RenderPoint(renderer, (ii_x * 2) + 1, i_y);
				}
			}
			SDL_RenderPresent(renderer);
			break;
		case 0x0002:
			for(uint8_t i_y = 0; i_y !=0xE0 ; i_y++){
				for(uint8_t ii_x = 0; ii_x !=0x80; ii_x++){
					SDL_SetRenderDrawColor(renderer, 0x00, (uint8_t)((memory[0x01100000 + (i_y*128) + ii_x]) >> 8), (uint8_t)(memory[0x01100000 + (i_y*128) + ii_x]), 0xFF);
					SDL_RenderPoint(renderer, (ii_x * 2), i_y);
					SDL_RenderPoint(renderer, (ii_x * 2) + 1, i_y);
				}
			}
			SDL_RenderPresent(renderer);
			break;
		default:
			printf("log: unknown graphics mode %X\n", memory[0x01000000]);
	};
	FLAGS &= 0x7FFF;
}
