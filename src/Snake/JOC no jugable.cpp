#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

const int WIDTH = 640, HEIGHT = 480;
/*
int main(int, char*[]) {
	try {
		// INIT
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();
		if (TTF_Init() != 0) printf("problema");
		const Uint8 imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) & imgFlags)) throw IMG_GetError();
		// WINDOW

		SDL_Window *window = SDL_CreateWindow("Cacasteroids",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH, HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == nullptr) throw SDL_GetError();

		// RENDERER
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr) throw SDL_GetError();

		//TITLE
		SDL_Color color = { 255, 255, 255 };
		TTF_Font *font = TTF_OpenFont("../../res/ka1.ttf", 35);
		if (font == NULL) printf("%s", TTF_GetError());

		
		// SPRITES
		SDL_Texture *bgTexture = IMG_LoadTexture(renderer, "../../res/bg.png");
		SDL_Rect bgRect = { 0,0,WIDTH, HEIGHT };
		SDL_Rect playerRect = { (WIDTH >> 1) - 50, (HEIGHT >> 1) - 50, 100, 75 };
		SDL_Rect playerTarget = { 0,0,100,100 };

		SDL_Texture *ship = IMG_LoadTexture(renderer, "../../res/ship.png");
		SDL_Rect shipRect = { WIDTH/2,HEIGHT/2, 25,25 };

		SDL_Texture *a1 = IMG_LoadTexture(renderer, "../../res/a1.png");
		SDL_Rect a1Rect = { 0,0, 50,50 };

		SDL_Texture *a2 = IMG_LoadTexture(renderer, "../../res/a2.png");
		SDL_Rect a2Rect = { 100,200, 100,100 };


		if (bgTexture == nullptr) throw SDL_GetError();
		//	GAME LOOP
		SDL_Event event;
		for (bool isRunning = true; isRunning;) {
			// INPUT HANDELER
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT: isRunning = false; break;
				case SDL_MOUSEMOTION: playerTarget.x = event.motion.x - 50; playerTarget.y = event.motion.y - 50; break;
				default:;
				}
			}
			// UPDATE
			playerRect.x += (playerTarget.x - playerRect.x);
			playerRect.y += (playerTarget.y - playerRect.y);

			printf("%d %d\n", playerRect.x, playerRect.y);

			if (playerRect.x >= 229 && playerRect.x <= 329 && playerRect.y >= 285 && playerRect.y <= 325 && event.type == SDL_MOUSEBUTTONDOWN);

			// Carregar seleccio de dificultat

			if (playerRect.x >= 229 && playerRect.x <= 329 && playerRect.y >= 335 && playerRect.y <= 385 && event.type == SDL_MOUSEBUTTONDOWN) {
				TTF_Quit();
				IMG_Quit();
				SDL_Quit();
			}



			// DRAW
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
			SDL_RenderCopy(renderer, ship, nullptr, &shipRect);
			SDL_RenderCopy(renderer, a1, nullptr, &a1Rect);
			SDL_RenderCopy(renderer, a2, nullptr, &a2Rect);
			SDL_RenderPresent(renderer);
		}
		// DESTROY
		SDL_DestroyWindow(window);
		SDL_DestroyTexture(bgTexture);
		SDL_DestroyRenderer(renderer);
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
		system("pause");
	}
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}*/