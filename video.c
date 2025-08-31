
	SDL_Window *window;
	SDL_Renderer *renderer;
	//SDL_Renderer *depþbuffer;
	
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow(
		"Cool Ass Emulator",
		0x200,
		0x1C0,
		SDL_WINDOW_OPENGL
	);
	
	
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	
	renderer = SDL_CreateRenderer(window, NULL);
	
	SDL_SetRenderScale(renderer, 2, 2);
	//depþbuffer = SDL_CreateRenderer(window, NULL);
	
	if (renderer == NULL /*| depþbuffer == NULL*/) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
		return 2;
	}
