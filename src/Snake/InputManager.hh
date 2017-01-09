#pragma once
#include "Init.hh"


#define IM InputManager::Instance()
 //llevar de variable global

class InputManager {
private:
	bool ESCAPE, DOWN, LEFT, RIGHT, UP, SPACE, V, RIGHTMOUSE;
	bool isRunning = true;
	SDL_Event evnt;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	SDL_Rect playerTarget = { 0,0,5,5 };

public:
	inline static InputManager &Instance() {
		static InputManager inputManager;
		return inputManager;
	}

	void Update() {

		while (SDL_PollEvent(&evnt)) {
			switch (evnt.type) {

			case SDL_QUIT: isRunning = false; break;
			case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x; playerTarget.y = evnt.motion.y; break;

			case SDL_KEYDOWN:

				if (currentKeyStates[SDL_SCANCODE_ESCAPE]) { ESCAPE = true; }
				if (currentKeyStates[SDL_SCANCODE_V]) { V = true; }
				break;

			case SDL_KEYUP:

				if (currentKeyStates[SDL_SCANCODE_ESCAPE]) { ESCAPE = false; }
				if (currentKeyStates[SDL_SCANCODE_V]) { V = false; }
				break;

			}
			if (currentKeyStates[SDL_SCANCODE_UP]) { UP = true; }
			else { UP = false; }
			if (currentKeyStates[SDL_SCANCODE_LEFT]) { LEFT = true; }
			else { LEFT = false; }
			if (currentKeyStates[SDL_SCANCODE_RIGHT]) { RIGHT = true; }
			else { RIGHT = false; }
			if (currentKeyStates[SDL_SCANCODE_DOWN]) { DOWN = true; }
			else { DOWN = false; }
			if (currentKeyStates[SDL_SCANCODE_SPACE]) { SPACE = true; }
			else { SPACE = false; }
			if (currentKeyStates[SDL_BUTTON_RIGHT]) { RIGHTMOUSE = true; }
			else { RIGHTMOUSE = false; }

		}
	}

	bool onButton(SDL_Rect rect) {
		if (playerTarget.x >= rect.x && playerTarget.x <= rect.x + rect.w && playerTarget.y >= rect.y && playerTarget.y <= rect.y + rect.h && evnt.type == SDL_MOUSEBUTTONUP)
			return true;
		else
			return false;
	}

	bool isOn() {
		return isRunning;
	}

	bool getEscape() { return ESCAPE; }
	bool getUp() { return UP; }
	bool getLeft() { return LEFT; }
	bool getRight() { return RIGHT; }
	bool getDown() { return DOWN; }
	bool getSpace() { return SPACE; }
	bool getV() { return V; }
	bool getRightMouse() { return  RIGHTMOUSE; }
};



