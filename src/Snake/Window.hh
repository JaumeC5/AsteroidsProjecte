#pragma once

#include <SDL.h>
#include <string>

const int WIDTH = 640;
const int HEIGHT = 480;

class Window {
	SDL_Window *window;
public:
	Window(char* NAME) {
		
		window = SDL_CreateWindow(NAME,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH, HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == nullptr) throw SDL_GetError();
	}
	~Window() {
		window = nullptr;
	}

	SDL_Window *getWindow() {
		return window;
	}

};
