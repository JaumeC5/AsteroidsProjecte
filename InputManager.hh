#pragma once
#include "Init.hh"
#include "GameEngine.hh"
#include "SpaceShip.hh"
#include "Bullet.hh"
#include "Bullet2.hh"
#include "chrono"
#include "time.h"

#define IM InputManager::Instance()
 //llevar de variable global
bool pause = false;
class InputManager {
	bool renderText = false;
	bool once = false;
	bool once2 = false;
	//bool shot = false;
	//string text = "Testest";
	//Bullet2 bb;
	int time = 0;
	int counter = 0;
	vector <Bullet2> b2;
public:
	inline static InputManager &Instance() {
		static InputManager inputManager;
		return inputManager;
	}

	void Update(vector <Bullet2> b2);


	SDL_Rect getCoords() {
		return playerTarget;
	}

	bool on() {
		return isRunning;
	}


	bool onButton(SDL_Rect rect) {
		if (playerTarget.x >= rect.x && playerTarget.x <= rect.x + rect.w && playerTarget.y >= rect.y && playerTarget.y <= rect.y + rect.h && evnt.type == SDL_MOUSEBUTTONUP)
			return true;
		else
			return false;
	}

	void randCoords(Sprite s) {
		r = s.getRect();
		r.x = rand() % WIDTH;
		r.y = rand() % HEIGHT;
	}

	bool shoot();

private:
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	//int counter;
	bool isRunning = true;
	SDL_Rect playerTarget = { 0,0,5,5 };
	SDL_Rect r;
	SDL_Rect r2;
	SDL_Event evnt;


};


void InputManager::Update(vector <Bullet2> b) {
	b2 = b;
	double time_counter = 0;
	const int NUM_SECONDS = 1;
	clock_t this_time = clock();
	clock_t last_time = this_time;
	 // contador de bales

	while (SDL_PollEvent(&evnt)) { // While input events exist, unpack them and store them in the SDL_Event variable one by one
		//counter++;
		//cout << "Time " << time << endl;

		switch (evnt.type) {
		case SDL_QUIT:	isRunning = false;  break;
		case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x; playerTarget.y = evnt.motion.y; break; //std::cout << playerTarget.x << std::endl;
		case SDL_KEYDOWN:

			if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {

				if (!pause && !once) {
					cout << "Paused" << endl;
					pause = true;
					once = true;

				}
				else if (pause && !once) {
					cout << "Unpaused" << endl;
					pause = false;
					once = true;
				}
				once = false;


			}



		}
		if (currentKeyStates[SDL_SCANCODE_SPACE]) {

			time++;

			if (time == 5) { // funciona
				b2[counter].active = true;
				cout << "bala " << counter << " " <<b2[counter].active << endl;
				counter++;
				if (counter >= 10)
					counter = 0;
				time = 0;
			}
		}

		break;
	}

	for (int i = 0; i < 10; i++) {
		b2[i].getCoords();
		b2[i].setRect();
		b2[i].shot();
		SDL_RenderCopy(R.getRender(), b2[i].getSprite().getTexture(), nullptr, &b2[i].getR());
	}
}

bool InputManager::shoot() {
	return true;
}