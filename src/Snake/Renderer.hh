#pragma once
#include "Window.hh"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

int scene = 1;
#define R Renderer::Instance()

class Renderer {
	SDL_Renderer *renderer;

public:
	inline static Renderer &Instance() {
		static Renderer r;
		return r;
	}

	~Renderer() {
		renderer = nullptr;
	}

	void setWindow(SDL_Window *w) {
		renderer = SDL_CreateRenderer(w, -1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr) throw SDL_GetError();
	}

	SDL_Renderer* getRender() {
		return renderer;
	}
};

