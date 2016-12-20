#include "Renderer.hh"
#include "Sprite.hh"
#include "GameEngine.hh"
#include "InputManager.hh"
#include "Window.hh"

int main(int argc, char* args[]) {

	

	init();
	TTF_Font * font = TTF_OpenFont("../../res/ka1.ttf", 35);
	SDL_Color color = { 255, 255, 255 };

	Window window("Asteroids");
	
	R.setWindow(window.getWindow());

	Sprite bg;
	bg.setTexture(R.getRender(), "../../res/bg.png");
	bg.setRect(0, 0, WIDTH, HEIGHT);

	
	Sprite title;
	title.setRect(WIDTH / 2 - 100, 50, 200,50);
	title.setSurface(font, "Asteroids", color);

	Sprite play;
	play.setRect(WIDTH / 2 - 40, HEIGHT - 150, 100, 50);
	play.setSurface(font, "Play", color);

	Sprite exit;
	exit.setRect(WIDTH / 2 - 40, HEIGHT - 90, 100, 50);
	exit.setSurface(font, "Exit", color);

	Sprite easy;
	easy.setRect(WIDTH / 2 - 40, HEIGHT - 250, 100, 50);
	easy.setSurface(font, "Easy", color);

	Sprite medium;
	medium.setRect(WIDTH / 2 - 40, HEIGHT - 180, 100, 50);
	medium.setSurface(font, "Medium", color);

	Sprite hard;
	hard.setRect(WIDTH / 2 - 40, HEIGHT - 110, 100, 50);
	hard.setSurface(font, "Hard", color);

	Sprite player;
	player.setRect(WIDTH / 2, HEIGHT / 2, 25, 25);
	player.setTexture(R.getRender(), "../../res/ship.png");

	SDL_Rect playerRect = { (WIDTH >> 1) - 50, (HEIGHT >> 1) - 50, 5, 5 };
	SDL_Rect playerTarget = { 0,0,5,5 };

	
	//LOOP
	while (IM.on()) {
		IM.Update();
		//std::cout << scene;
		switch (scene) {


		case 1:
			SDL_RenderCopy(R.getRender(), bg.getTexture(), nullptr, &bg.getRect());
			SDL_RenderCopy(R.getRender(), play.convertSurface(R.getRender()), nullptr, &play.getRect());
			SDL_RenderCopy(R.getRender(), exit.convertSurface(R.getRender()), nullptr, &exit.getRect());
			SDL_RenderCopy(R.getRender(), title.convertSurface(R.getRender()), nullptr, &title.getRect());

			if (IM.onButton(play.getRect()))
				scene = 2;
			break;
		case 2:
			SDL_RenderCopy(R.getRender(), bg.getTexture(), nullptr, &bg.getRect());
			SDL_RenderCopy(R.getRender(), easy.convertSurface(R.getRender()), nullptr, &easy.getRect());
			SDL_RenderCopy(R.getRender(), medium.convertSurface(R.getRender()), nullptr, &medium.getRect());
			SDL_RenderCopy(R.getRender(), hard.convertSurface(R.getRender()), nullptr, &hard.getRect());

			if (IM.onButton(easy.getRect()))
				scene = 3;
			if (IM.onButton(medium.getRect()))
				scene = 4;
			if (IM.onButton(hard.getRect()))
				scene = 5;
			break;

		case 3:
			SDL_RenderCopy(R.getRender(), bg.getTexture(), nullptr, &bg.getRect());
			SDL_RenderCopy(R.getRender(), player.getTexture(), nullptr, &player.getRect());
			break;
		case 4:
			break;
		case 5:
			break;
			
		}
	SDL_RenderPresent(R.getRender());




		//UPDATE
		//playerRect.x += (playerTarget.x - playerRect.x);
		//playerRect.y += (playerTarget.y - playerRect.y);


	}
		
		return 0;
	}




	