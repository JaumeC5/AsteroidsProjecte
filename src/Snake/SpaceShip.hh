#pragma once

#include <iostream>
#include "Window.hh"

using namespace std;
//

#define S SpaceShip::Instance()

class SpaceShip
{

private:
	float cosA = 0.0;
	float sinA = 0.0;
	double angle = 0.0;
	SDL_Event evnt;
	bool b[4]{ 0,0,0,0 };

	SDL_Point pos = { 0, 0 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

public:
	inline static SpaceShip &Instance() {
		static SpaceShip s;
		return s;
	}


	SpaceShip();

	int rot;

	SDL_Point getPos() { return pos; }
	SDL_RendererFlip getFlip() { return flip; }
	double getAngle() { return angle; }

	void rotate(const int& val) { rot = val; }

	void updatePos();

};