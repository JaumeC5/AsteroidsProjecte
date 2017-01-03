#pragma once

#include "SpaceShip.hh"

SpaceShip::SpaceShip()
	//: pos({ WIDTH / 2, HEIGHT / 2 })
{

}


void SpaceShip::updatePos()
{

	while (SDL_PollEvent(&evnt)) {
		cout << "updateposworkin" << endl;
		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
			b[0] = true;
			cout << "Rot: Left" << endl;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			b[1] = true;
			cout << "Rot: Right" << endl;
		}

		if (currentKeyStates[SDL_SCANCODE_W]) {
			//player.setRect.x += 10;
			cout << "Pos: UP" << endl;
		}
		if (currentKeyStates[SDL_SCANCODE_S]) {
			pos.y -= 10;
			cout << "Pos: DOWN" << endl;
		}
		if (currentKeyStates[SDL_SCANCODE_D]) {
			pos.x += 10;
			cout << "Pos: RIGHT" << endl;
		}
		if (currentKeyStates[SDL_SCANCODE_A]) {
			pos.x -= 10;
			cout << "Pos: LEFT" << endl;
		}

		if (b[0]) { angle -= 5; };
		if (b[1]) { angle += 5; };
	}

	if (angle >= 360) { angle -= 360; }
	if (angle <= -360) { angle += 360; }

	b[0] = false;
	b[1] = false;

	//cambiar posicion
	if (pos.x < 0) { pos.x = WIDTH; }
	if (pos.x > WIDTH) { pos.x = 0; }
	if (pos.y < 0) { pos.y = HEIGHT; }
	if (pos.y < HEIGHT) { pos.y = 0; }

};


