#pragma once

#include "Init.hh"
#include "Window.hh"
#include <map>

class SpaceShip
{

private:
	float cosA = 0.0;
	float sinA = 0.0;
	double angle = 0.0;

	SDL_Point pos;

public:
	int rot;

	enum direction {Left = 1, Right = 2 };

	SpaceShip();
	~SpaceShip();


	inline SDL_Point getPos() { return pos; }

	void updatePos();

};
