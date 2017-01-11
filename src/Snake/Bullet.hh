#pragma once

#include "SpaceShip.hh"

#define B Bullet::Instance()



class Bullet {
private:
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	Sprite bullet;
	SDL_Rect bulletRect;
	vector <Bullet> bullets;
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
		//bullets[0] = bullet;
	}

	void renderBullet() {
		Bullet b;
		for (int i = 0; i < bullets.size(); i++) {

			bullets[i].bulletRect.x = S.getPlayerRect().x;
			bullets[i].bulletRect.y = S.getPlayerRect().y;

			bullets[i].bulletRect.x += 5;
			bullets[i].bulletRect.y += 5;

			bullets.push_back(b);
			cout << bullets.size();
			SDL_RenderCopy(R.getRender(), bullets[i].getBullet().getTexture(), nullptr, &bullets[i].getBulletRect());

		}





	}


	void destroyBullet() {

	}

	void getPositions() {
		//cout << bulletRect.x << " " << bulletRect.y << endl;
	}


};
