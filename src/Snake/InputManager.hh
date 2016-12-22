#pragma once
#include "Init.hh"
#include "SpaceShip.h"

#define IM InputManager::Instance()

class InputManager {



public:
	inline static InputManager &Instance() {
		static InputManager inputManager;
		return inputManager;
	}


	void Update() {
		
		while (SDL_PollEvent(&evnt)) { // While input events exist, unpack them and store them in the SDL_Event variable one by one
			switch (evnt.type) {
			case SDL_QUIT: isRunning = false; break;
			case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x; playerTarget.y = evnt.motion.y; std::cout << playerTarget.x << std::endl;

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




private:
	bool isRunning = true;
	SDL_Rect playerTarget = { 0,0,5,5 };
	SDL_Event evnt;
};