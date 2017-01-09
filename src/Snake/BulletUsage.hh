#pragma once

#include "Bullet.hh"
#include <vector>

#define BU BulletUsage::Instance()

class BulletUsage{

private:
	vector<Bullet> bulletV;
	Bullet newBullet;

public:

	inline static BulletUsage &Instance() {
		static BulletUsage bu;
		return bu;
	}

void ifInput() {

	if (IM.getSpace()) {

		bulletV.push_back(newBullet);
		bulletRect.x = S.getPlayerRect().x;
		bulletRect.y = S.getPlayerRect().y;

	}
}



void drawBullet() {
	for (int i = 0; i > bulletV.size(); i++) {
		SDL_RenderCopyEx(R.getRender(), bulletV[i].getBullet().getTexture(), nullptr, &bulletV[i].getBulletRect(), S.getAngle(), &S.getPos(), S.getFlip());
		bulletV[i].updateBullet();
	}
}

void generateBullet() {
	B.getBullet().setRect(B.getBulletRect().x, B.getBulletRect().y, 25, 25);
	B.getBullet().setTexture(R.getRender(), "../../res/bullet.png");
}



};