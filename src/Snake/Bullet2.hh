#pragma once
#include "SpaceShip.hh"
#include "SDL.h"

class Bullet2 {
	int x;
	int y;
	int bulletSpeed = 8;
	Sprite sp;
	float bulletAngle;
public:
	bool alive;
	bool meteorHit;
	Bullet2(Sprite sp2) {
		sp = sp2;
	}
	SDL_Rect getPos();
	void setLimits();
	void setBullet();
	void draw();
	void update();
	void shoot(int, int);
};

SDL_Rect Bullet2::getPos() {
	return sp.getRect();
}

void Bullet2::setBullet() {
	sp.setRect( x, y, 2, 2 ); 
}

void Bullet2::update() { //moure objectes
	//cout << x << ' ' << y << endl;
	if (alive) {
		x += bulletSpeed * sin(bulletAngle * PI / 180.0);
		y -= bulletSpeed * cos(bulletAngle * PI / 180.0);
	}

	if(!alive) {
		x = S.getPlayerRect().x+12;
		y = S.getPlayerRect().y+12;
		bulletAngle = S.getAngle();
	}
		

	
}

void Bullet2::draw() {
	if(alive)
		SDL_RenderCopy(R.getRender(), sp.getTexture(), nullptr, &sp.getRect());
}

void Bullet2::shoot(int s, int c) { // son ses poscions de sa nave. que no fan falta al final

	alive = true;
	
}

void Bullet2::setLimits() {
	if (x >= WIDTH || x <= 0 || y >= HEIGHT || y <= 0)
		alive = false;
}
