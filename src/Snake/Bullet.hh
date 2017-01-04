/*#pragma once

#include "SpaceShip.hh"

class Bullet {
	private:
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		Sprite bullet;
		SDL_Rect bulletRect = { S.getPlayerRect().x, S.getPlayerRect().y };

	public:

		void updateBullet(){
			if (currentKeyStates[SDL_SCANCODE_LEFT]) {
				bullet.setRect(bulletRect.x, bulletRect.y, 25, 25);
				bullet.setTexture(R.getRender(), "../../res/ship.png");
			}
		}
};

*/