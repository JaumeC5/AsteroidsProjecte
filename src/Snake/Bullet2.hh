#pragma once
#include "SpaceShip.hh"
#include "Sprite.hh"

SDL_Rect bulletRect;

class Bullet2 {
	Sprite m_sp;
	SDL_Rect r;
	int speed = 6;
	

public:
	bool active;
	int x;
	int y;
	//int xShot;
	//int yShot;
	Bullet2(Sprite z) {
		m_sp = z;
	}
	void getCoords() {
		if (!active)
			x = S.getPlayerRect().x + 12; y = S.getPlayerRect().y + 12;
	}
	void shot() {
		if (active) {
			/*bool bulletShot = true;
			if (bulletShot = true) {
				xShot = S.getPlayerRect().x + 12;
				yShot = S.getPlayerRect().y + 12;
				bulletShot = false;
			}*/
			x += 20;
		}
		

		
	}
	Sprite getSprite() {
		return m_sp;
	}
	void setRect() {
		r = { x, y, 3, 3 };
		if (x >= WIDTH || x <= 0 || y >= HEIGHT || y <= 0)
			active = false;
	}
	SDL_Rect getR() {
		return r;
	}

	
};

