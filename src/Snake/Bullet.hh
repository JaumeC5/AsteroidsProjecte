#pragma once

#include "SpaceShip.hh"
#include "InputManager.hh"

#define B Bullet::Instance()

SDL_Rect bulletRect; //variable global ¯\_(?)_/¯

class Bullet {
private:

	Sprite bullet;
	

	float bulletVel = 100;

public:

	inline static Bullet &Instance() {
		static Bullet b;
		return b;
	}

	void updateBullet() { //no sabem q fa primer, si sumar bulletVel o getPlayerRect. Threads?
		bulletRect.x += bulletVel;
		bulletRect.y += bulletVel;

	}
	
	SDL_Rect getBulletRect() { return bulletRect; }
	Sprite getBullet() { return bullet; }
	int getBulletVel() { return bulletVel;  }

	
	
	
};
