#pragma once
#include "Init.hh"
#include "GameEngine.hh"
#include "SpaceShip.hh"
#include "Bullet.hh"
#include "Bullet2.hh"

#define IM InputManager::Instance()
//llevar de variable global
bool pause = false;
class InputManager {
	bool renderText = false;
	bool once = false;
	bool once2 = false;
	bool shot = false;
	//string text = "Testest";
	Bullet2 bb;

public:
	inline static InputManager &Instance() {
		static InputManager inputManager;
		return inputManager;
	}

	void Update();


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
	int counter;
	bool isRunning = true;
	SDL_Rect playerTarget = { 0,0,5,5 };
	SDL_Rect r;
	SDL_Rect r2;
	SDL_Event evnt;


};


void InputManager::Update() {
	while (SDL_PollEvent(&evnt)) { // While input events exist, unpack them and store them in the SDL_Event variable one by one
								   //counter++;
								   //cout << counter << endl;
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

			if (!shot) {
				//	cout << "SI" << endl;

				shot = true;
			}
			shot = false;

		}

		break;
	}


}

bool InputManager::shoot() {
	cout << shot << endl;
	if (!shot) {


		shot = true;
	}
	if (shot) {
		//cout << true << endl;

		shot = false;
	}
	return shot;
}