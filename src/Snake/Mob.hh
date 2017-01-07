#pragma once
#include "Sprite.hh"
#include "ID.hh"
#include "Renderer.hh"
#include "configXML.hh"
#include "GameEngine.hh"
#include "Bullet.hh"
int scene = 1;
int score = 0;
class Mob {
	//
	Sprite m_Sp;
	SDL_Rect m_Rect;
	int m_Speed;
	int m_RDir = rand() % 8;
	AsteroidID m_Id;

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

	SDL_Rect a() {
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

		if (m_Rect.x >= WIDTH)
			m_Rect.x = -m_Rect.w;
		else if (m_Rect.x <= -m_Rect.w)
			m_Rect.x = WIDTH - 1;
		else if (m_Rect.y <= -m_Rect.h)
			m_Rect.y = HEIGHT;
		else if (m_Rect.y >= HEIGHT + m_Rect.h)
			m_Rect.y = -m_Rect.h + 1;

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
			break;

		case MEDIUM:
			score += 50;
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
		m_Sp.destroySprite();

	}
	void checkCollision() {
		Sprite b = S.getPlayer(); // canviar aixo per sa bala

		if (b.getRect().x >= m_Rect.x && b.getRect().x <= m_Rect.x + m_Rect.w && b.getRect().y >= m_Rect.y && b.getRect().y <= m_Rect.y + m_Rect.h) {
			destroy();
		}
/*
		if (m_Rect.x >= WIDTH)
			m_Rect.x = -m_Rect.w;
		else if (m_Rect.x <= -m_Rect.w)
			m_Rect.x = WIDTH - 1;
		else if (m_Rect.y <= -m_Rect.h)
			m_Rect.y = HEIGHT;
		else if (m_Rect.y >= HEIGHT + m_Rect.h)
			m_Rect.y = -m_Rect.h + 1;
			*/
	}
	AsteroidID getId() {
		return m_Id;
	}

};