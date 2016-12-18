#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

const int WIDTH = 640, HEIGHT = 480;
int dificultat = 0;


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
		//SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Asteroids", color);
		//SDL_Rect fontRect = { WIDTH / 2 - 100, 50, 200,50 };
		//SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);


		// SPRITES
		SDL_Texture *bgTexture = IMG_LoadTexture(renderer, "../../res/bg.png");
		SDL_Texture *playerTexture = IMG_LoadTexture(renderer, "../../res/red.png");
		SDL_Rect bgRect = { 0,0,WIDTH, HEIGHT };
		SDL_Rect playerRect = { (WIDTH >> 1) - 50, (HEIGHT >> 1) - 50, 100, 75 };
		SDL_Rect playerTarget = { 0,0,100,100 };


		//EASY MEDIUM HARD BUTTONS
		SDL_Surface *easySurface = TTF_RenderText_Solid(font, "EASY", color);
		SDL_Rect easyRect = { WIDTH / 2 - 40, HEIGHT / 3 - 100, 100,50 };
		SDL_Texture *easyText = SDL_CreateTextureFromSurface(renderer, easySurface);

		SDL_Surface *mediumSurface = TTF_RenderText_Solid(font, "MEDIUM", color);
		SDL_Rect mediumRect = { WIDTH / 2 - 40, (HEIGHT / 3), 100,50 };
		SDL_Texture *mediumText = SDL_CreateTextureFromSurface(renderer, mediumSurface);

		SDL_Surface *hardSurface = TTF_RenderText_Solid(font, "HARD", color);
		SDL_Rect hardRect = { WIDTH / 2 - 40, HEIGHT/3 + 100, 100,50 };
		SDL_Texture *hardText = SDL_CreateTextureFromSurface(renderer, hardSurface);

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

			if (playerRect.x >= 229 && playerRect.x <= 329 && playerRect.y >= 15 && playerRect.y <= 58 && event.type == SDL_MOUSEBUTTONDOWN) {

				// Carregar dificultat 1
				printf("1\n");
			}

			

			if (playerRect.x >= 229 && playerRect.x <= 329 && playerRect.y >= 114 && playerRect.y <= 158 && event.type == SDL_MOUSEBUTTONDOWN){
			
				// Carregar dificultat 2
				printf("2\n");
			}

			

			if (playerRect.x >= 229 && playerRect.x <= 329 && playerRect.y >= 214 && playerRect.y <= 258 && event.type == SDL_MOUSEBUTTONDOWN) {

				// Carregar dificultat 3
				printf("3\n");
			}



			// DRAW
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
			SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
			//SDL_RenderCopy(renderer, text, nullptr, &fontRect);
			SDL_RenderCopy(renderer, easyText, nullptr, &easyRect);
			SDL_RenderCopy(renderer, mediumText, nullptr, &mediumRect);
			SDL_RenderCopy(renderer, hardText, nullptr, &hardRect);

			SDL_RenderPresent(renderer);
		}
		// DESTROY
		SDL_DestroyWindow(window);
		SDL_DestroyTexture(bgTexture);
		SDL_DestroyTexture(playerTexture);
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



