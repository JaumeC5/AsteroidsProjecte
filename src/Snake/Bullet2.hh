#pragma once
#include "SpaceShip.hh"

SDL_Rect bulletRect;

class Bullet2 {
	Sprite m_sp;
	SDL_Rect r;
	int speed = 6;
	bool shot = false;

public:
	void setBullet();
	void getPos();
	SDL_Rect getRect();
	void renderBullet(SDL_Renderer *r);

};

void Bullet2::setBullet() {
	m_sp.setRect(S.getPlayerRect().x + 11, S.getPlayerRect().y + 11, 3, 3);
	m_sp.setTexture(R.getRender(), "../../res/bullet.png");

}
void Bullet2::getPos() {
	cout << m_sp.getRect().x << " " << m_sp.getRect().y << endl;
}

void Bullet2::renderBullet(SDL_Renderer *r) {
	SDL_RenderCopy(r, m_sp.getTexture(), nullptr, &m_sp.getRect());
}

SDL_Rect Bullet2::getRect() {
	return m_sp.getRect();
}