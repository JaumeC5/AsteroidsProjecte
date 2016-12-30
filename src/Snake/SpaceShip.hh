#pragma once

#include <iostream>
#include "Window.hh"

using namespace std;


#define S SpaceShip::Instance()

class SpaceShip
{

private:
	float cosA = 0.0;
	float sinA = 0.0;
	double angle = 0.0;
	SDL_Event evnt;
	bool b[4]{ 0,0,0,0 };

	SDL_Point pos;

public:
	inline static SpaceShip &Instance() {
		static SpaceShip s;
		return s;
	}

	SpaceShip();

	int rot;


	//inline SDL_Point getPos() { return pos; }

	double getAngle() { return angle; }

	void rotate(const int& val) { rot = val; }

	void updatePos();

};

