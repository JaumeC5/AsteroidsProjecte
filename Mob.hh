
#pragma once
#include "Sprite.hh"
#include "ID.hh"
#include "Renderer.hh"
#include "configXML.hh"
#include "GameEngine.hh"
#include "Bullet.hh"

int score = 0;
class Mob {
	Sprite m_Sp;
	Sprite m_Sub1;
	Sprite m_Sub2;
	SDL_Rect m_Rect;
	int m_Speed;
	int m_RDir = rand() % 8;
	AsteroidID m_Id;
	bool kaput = false;
	int count = 150;
	

public:
	void generate(AsteroidID type, int x, int y) {
		m_Id = type;
		switch (m_Id) {
		case SMALL:
			m_Sp.setRect(x, y, 25, 25);
			m_Sp.setTexture(R.getRender(), "../../res/a1.png");
			break;

		case MEDIUM:
			m_Sp.setRect(x, y, 50, 50);
			m_Sp.setTexture(R.getRender(), "../../res/a2.png");
			break;

		case LARGE:
			m_Sp.setRect(x, y, 100, 100);
			m_Sp.setTexture(R.getRender(), "../../res/a3.png");
			break;

		case UFOl:
			m_Sp.setRect(x, y, 50, 50);
			m_Sp.setTexture(R.getRender(), "../../res/ufo.png");
			break;
		case UFOs:
			m_Sp.setRect(x, y, 25, 25);
			m_Sp.setTexture(R.getRender(), "../../res/ufo.png");
			break;

		}
	}

	void getCoords() {
		m_Rect = m_Sp.getRect();
	}

	Sprite getSprite() {
		return m_Sp;
	}

	SDL_Rect a() { // the most useful and powerful function
		return m_Rect;
	}

	void mobMovement() { // FER MOURE ELS METEORITS



		std::vector <int> v;
		v = getProps(); // works. Go to configXML.hh
		int m_Speed;
		switch (scene) {
		case 3:
			m_Speed = v[1];
			break;
		case 4:
			m_Speed = v[5];
			break;
		case 5:
			m_Speed = v[9];

		}

		if (m_Rect.x >= WIDTH - 10)
			m_Rect.x = -m_Rect.w + 10;
		else if (m_Rect.x <= -m_Rect.w +9)
			m_Rect.x = WIDTH -11;
		else if (m_Rect.y <= -m_Rect.h + 9)
			m_Rect.y = HEIGHT - 9;
		else if (m_Rect.y >= HEIGHT + m_Rect.h - 10)
			m_Rect.y = -m_Rect.h + 10;

		if (m_Id == UFOl || m_Id == UFOs) {
			count++;
			if (count >= 150) {
				m_RDir = rand() % 8;
				count = 0;
			}
		}


		
		switch (m_RDir) {
		case 0: //up
			m_Rect.y -= m_Speed;

			break;
		case 1: //up-right
			m_Rect.x += m_Speed;
			m_Rect.y -= m_Speed;
			break;
		case 2: //right
			m_Rect.x += m_Speed;
			break;
		case 3: //right-down
			m_Rect.x += m_Speed;
			m_Rect.y += m_Speed;
			break;
		case 4:// down
			m_Rect.y += m_Speed;
			break;
		case 5://down-left
			m_Rect.y += m_Speed;
			m_Rect.x -= m_Speed;
			break;
		case 6://left
			m_Rect.x -= m_Speed;
			break;
		case 7://left-up
			m_Rect.x -= m_Speed;
			m_Rect.y -= m_Speed;
		default:
			break;
		}
		
		

		//cout << rect.x << " " << rect.y << endl;
	}

	void destroy() {

		switch (getId()) {

		case SMALL:
			score += 100;
			cout << "ouch" << endl;
			break;

		case MEDIUM:
			score += 50;
			cout << "Medium ouch" << endl;
			break;

		case LARGE:
			score += 20;

			break;
		case UFOs:
			score += 1000;
			break;
		case UFOl:

			score += 200;
			break;
		}
	}
	bool boom() {
		return kaput;
	}
	void checkCollision(vector <Mob> m) {
		Sprite b = S.getPlayer(); // canviar aixo per sa bala // deixar això també per restar vides

		if (b.getRect().x >= m_Rect.x && b.getRect().x <= m_Rect.x + m_Rect.w && b.getRect().y >= m_Rect.y && b.getRect().y <= m_Rect.y + m_Rect.h) {
			kaput = true;
			//destroy(m);
		}

	}
	AsteroidID getId() {
		return m_Id;
	}

};