#pragma once
#include "Init.hh"
#include "GameEngine.hh"
#include "chrono"
#include "time.h"

#define IM InputManager::Instance()
bool pause = false;
class InputManager {
	bool hyper = false;
	bool once = false;
	bool once2 = false;
	bool shot = false;
	int counter = 0;
public:
	inline static InputManager &Instance() {
		static InputManager inputManager;
		return inputManager;
	}
	void Update();
	bool hyperspace() {
		return hyper;
	}
	SDL_Rect getCoords() {
		return playerTarget;
	}
	bool on() {
		return isRunning;
	}
	bool shoot() { return shot; }
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
private:
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	//int counter;
	bool isRunning = true;
	SDL_Rect playerTarget = { 0,0,5,5 };
	SDL_Rect r;
	SDL_Rect r2;
	SDL_Event evnt;
};

void InputManager::Update() { // S'encarregre els imputs per part de l'usuari
	double time_counter = 0;
	const int NUM_SECONDS = 1;
	clock_t this_time = clock();
	clock_t last_time = this_time;
	while (SDL_PollEvent(&evnt)) { 
		switch (evnt.type) {
		case SDL_QUIT:	isRunning = false;  break;
		case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x; playerTarget.y = evnt.motion.y; break; 
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


			if (currentKeyStates[SDL_SCANCODE_SPACE]) {
				shot = true;
			}


			if (currentKeyStates[SDL_SCANCODE_V]) {

				hyper = true;

			}
			break;

		case SDL_KEYUP:
			switch (evnt.key.keysym.sym) {
			case SDLK_SPACE:
				shot = false;
				break;
			case SDLK_v:
				hyper = false;
				break;
			default:;
			}
		default:;

		}
	} 
}

