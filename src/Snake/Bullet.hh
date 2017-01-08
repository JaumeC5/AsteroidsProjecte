#pragma once

#include "SpaceShip.hh"

#define B Bullet::Instance()

class Bullet {
private:
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	Sprite bullet;
	SDL_Rect bulletRect;

	float bulletVel = 10;

public:

	inline static Bullet &Instance() {
		static Bullet b;
		return b;
	}
	

	

	void updateBullet() {

		bulletRect.x = S.getPlayerRect().x;
		bulletRect.y = S.getPlayerRect().y;
	
		bulletRect.x += 1000;
		bulletRect.y += 1000;

	}
	SDL_Rect getBulletRect() { return bulletRect; }
	Sprite getBullet() { return bullet; }

	void generateBullet() {
		bullet.setRect(bulletRect.x, bulletRect.y, 25, 25);
		bullet.setTexture(R.getRender(), "../../res/bullet.png");
	}
	
	
};
