#pragma once

#include "SpaceShip.hh"

#define B Bullet::Instance()

class Bullet {
private:
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	Sprite bullet;
	SDL_Rect bulletRect = { S.getPlayerRect().x, S.getPlayerRect().y };

	float bulletVel = 10;

public:

	inline static Bullet &Instance() {
		static Bullet b;
		return b;
	}

	SDL_Rect getBulletRect() { return bulletRect; }

	void generateBullet() {
			bullet.setRect(bulletRect.x, bulletRect.y, 10, 10);
			bullet.setTexture(R.getRender(), "../../res/bullet.png");
	}

	void renderBullet() {
		if (currentKeyStates[SDL_SCANCODE_SPACE]) {
			cout << "im gay";
			//SDL_RenderCopy(R.getRender(), bullet.getTexture() , nullptr, &getBulletRect());
		}
	}



	
};
