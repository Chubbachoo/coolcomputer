build:
	gcc main.c -o computer -lm `pkg-config sdl3 --cflags --libs`
filetest:
	gcc filemaker.c -o filemaker
