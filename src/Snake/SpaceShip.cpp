#pragma once

#include "SpaceShip.h"

SpaceShip::SpaceShip()
: pos({WIDTH / 2, HEIGHT / 2})
{

}

SpaceShip::~SpaceShip()
{
}


void SpaceShip::updatePos()
{
	switch (rot)
	{
	case Left: {angle -= 0.175; break; }
	case Right: {angle += 0.175; break; }
	}

	//cambiar posicion
	if (pos.x < 0) { pos.x = WIDTH; }
	if (pos.x > WIDTH) { pos.x = 0; }
	if (pos.y < 0) { pos.y = HEIGHT; }
	if (pos.y < HEIGHT) { pos.y = 0; }
	

}