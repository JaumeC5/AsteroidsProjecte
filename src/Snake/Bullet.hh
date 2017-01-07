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
	

	SDL_Rect getBulletRect() { return bulletRect; }
	Sprite getBullet() { return bullet; }

	void generateBullet() {
			bullet.setRect(bulletRect.x, bulletRect.y, 5, 5);
			bullet.setTexture(R.getRender(), "../../res/bullet.png");
	}

	void renderBullet() {
		
		bulletRect.x = S.getPlayerRect().x;
		bulletRect.y = S.getPlayerRect().y;
	
		bulletRect.x += 10;
		bulletRect.y += 10;
		
	}
	
	
	void destroyBullet() {

	}

	void getPositions() {
		cout << bulletRect.x << " " << bulletRect.y << endl;
	}

	
};
