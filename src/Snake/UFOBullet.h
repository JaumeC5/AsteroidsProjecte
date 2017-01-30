#pragma once
#include "Mob.hh"

// S'ha intentat amb 80% d'éxit aconseguir que els ovnis disparin 

class UFOBullet {
	int x;
	int y;
	int bulletSpeed = 8;
	Sprite sp;
	float bulletAngle;
	int counter = 0;
	int counter2 = 0;
	SDL_Rect r;
	float aux;
public:
	bool alive;
	bool meteorHit;
	UFOBullet(Sprite sp2) {
		sp = sp2;
	}
	SDL_Rect getPos();
	void setLimits();
	void setBullet();
	void draw();
	void update(Mob, int);
	void shoot();
	bool shootSim();
	float getAngle();

};

SDL_Rect UFOBullet::getPos() {
	return sp.getRect();
}

void UFOBullet::setBullet() {
	sp.setRect(x, y, 2, 2);
}
float  UFOBullet::getAngle() {
	return bulletAngle;
}
void UFOBullet::update(Mob m, int lvl) { //moure objectes
	if (!m.kaput) {
		if (m.getId() == UFOl || m.getId() == UFOs) {
			if (alive) {
				x += bulletSpeed * sin(bulletAngle * PI / 180.0);
				y -= bulletSpeed * cos(bulletAngle * PI / 180.0);

			}

			if (!alive) {
				cout << bulletAngle << endl;
				x = m.getSprite().getRect().x + m.getSprite().getRect().w / 2;
				y = m.getSprite().getRect().y + m.getSprite().getRect().h / 2;
				if (m.getId() == UFOl)
					bulletAngle = rand() % 360;
				if (m.getId() == UFOs) {
					r = { x - S.getPlayerRect().x, y - S.getPlayerRect().y, 0, 0 };
					if (r.x >= 0 && r.y <= 0) {
						bulletAngle = tan(r.y / r.x);
						aux = -90 + bulletAngle;
						bulletAngle = bulletAngle + (aux * 2);
					}
					else if (r.x > 0 && r.y > 0) {
						bulletAngle = tan(r.y / r.x);
						aux = 90 - bulletAngle;
						bulletAngle = bulletAngle + (aux * 2);
					}

					else if (r.x < 0 && r.y > 0) {
						bulletAngle = tan(r.y / r.x);
						bulletAngle = -(bulletAngle * 2);
					}
					else if (r.x < 0 && r.y < 0) {
						bulletAngle = tan(r.y / r.x);
						bulletAngle = -(bulletAngle * 2);
					}

				}
			}
		}
	}



}

void UFOBullet::draw() {
	if (alive)

		SDL_RenderCopy(R.getRender(), sp.getTexture(), nullptr, &sp.getRect());

}

void UFOBullet::shoot() {
	alive = true;
}

void UFOBullet::setLimits() {
	if (x >= WIDTH || x <= 0 || y >= HEIGHT || y <= 0)
		alive = false;
}

bool UFOBullet::shootSim() {
	shoot();

	return true;
}