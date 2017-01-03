#pragma once
#include "Init.hh"
#include "GameEngine.hh"
#include "SpaceShip.hh"

#define IM InputManager::Instance()
bool pause = false; //llevar de variable global

class InputManager {

	

public:
	inline static InputManager &Instance() {
		static InputManager inputManager;
		return inputManager;
	}

	void Update() {
		
		while (SDL_PollEvent(&evnt)) { // While input events exist, unpack them and store them in the SDL_Event variable one by one
			switch (evnt.type) {
			case SDL_QUIT:	isRunning = false;  break;
			case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x; playerTarget.y = evnt.motion.y; break; //std::cout << playerTarget.x << std::endl;
			}

			if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
				bool once = false;
				if (!pause && !once) {
					cout << "Paused" << endl;
					pause = true;
					once = true;

				}
			if (pause && !once) {
				cout << "Unpaused" << endl;
				pause = false;
				once = true;

				}
			}

		}

	}
	




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

private:
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	bool isRunning = true;
	SDL_Rect playerTarget = { 0,0,5,5 };
	SDL_Rect r;
	SDL_Event evnt;
	
};


