#pragma once
#include "Init.hh"

class Sprite {
	SDL_Rect rect;
	SDL_Texture* texture;
	SDL_Surface * surface; // In case we're rendering text

public:
	void setRect(int x, int y, int w, int h) {
		rect = { x, y, w, h };
	}

	void setTexture(SDL_Renderer* renderer,char* dir) {
		texture = IMG_LoadTexture(renderer, dir);
		if (texture == nullptr) std::cout << "?" << std::endl;

	}

	void setSurface(TTF_Font *f, char* t, SDL_Color c){
		surface = TTF_RenderText_Solid(f, t, c);
	}

	SDL_Surface *getSurface() {
		return surface;
	}

	SDL_Texture *convertSurface(SDL_Renderer * r) {
		SDL_Surface *s = getSurface();
		SDL_Texture* text = SDL_CreateTextureFromSurface(r, s);
		return text;
	}

	SDL_Texture *getTexture() {
		return texture;
	}
	SDL_Rect getRect() {
		return rect;
	}

	void move(int x, int y) { // x i y han de ser obtingudes desde xml
		rect.x += x;
		rect.y += y;
	}

};
