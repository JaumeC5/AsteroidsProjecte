#pragma once

#include "SpaceShip.hh"

SpaceShip::SpaceShip()
	//: pos({ WIDTH / 2, HEIGHT / 2 })
{

}


void SpaceShip::updatePos()
{
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym) {
			case SDLK_LEFT: b[0] = true; cout << "Rot: Left"; break;
			case SDLK_RIGHT: b[1] = true; cout << "Rot: Right"; break;
			}
		case SDL_KEYUP:
			switch (evnt.key.keysym.sym) {
			case SDLK_LEFT: b[0] = false; cout << "Stop Rot"; break;
			case SDLK_RIGHT: b[1] = false; cout << "Stop Rot"; break;
			}
		}
		if (b[0]) { angle -= 3; };
		if (b[1]) { angle += 3; };
	}

	if (angle >= 360) { angle -= 360; }
	if (angle <= -360) { angle += 360; }


	//cambiar posicion
	if (pos.x < 0) { pos.x = WIDTH; }
	if (pos.x > WIDTH) { pos.x = 0; }
	if (pos.y < 0) { pos.y = HEIGHT; }
	if (pos.y < HEIGHT) { pos.y = 0; }

}
