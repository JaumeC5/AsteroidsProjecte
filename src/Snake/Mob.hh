
#pragma once
#include "Sprite.hh"
#include "ID.hh"
#include "Renderer.hh"
#include "configXML.hh"
#include "Bullet2.hh"

int score = 0;
class Mob {
	Sprite m_Sp; // Mob pare
	Sprite m_Sub1; //Mob fill 1
	Sprite m_Sub2; // Mob fill 2
	SDL_Rect m_Rect;
	int m_RDir = rand() % 8; // Direcció de moviment
	AsteroidID m_Id; // Id del mob
	int count = 150; // Permet als ovnis variar la seva direcció
	int i = 0;
	int m_Speed; // Velocitat dels mobs, augmenta segons la dificultat i el tamany del mob
	int j = 1;

public:
	bool kaput = false;

	void generate(AsteroidID type, int x, int y) { //Genera l'enemic amb les seves propies característiques
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

	void getCoords() { //Rep les coordenades del mob
		m_Rect = m_Sp.getRect();
	}

	Sprite getSprite() {
		return m_Sp;
	}

	SDL_Rect a() { // Retorna el rectangle del mob
		return m_Rect;
	}

	void mobMovement() { // FER MOURE ELS METEORITS

		std::vector <int> v;
		v = getProps(); // Go to configXML.hh
		switch (scene) {
		case 3:		//Segons la dificultat, augment de la velocitat
			m_Speed = v[1] + i;
			break;
		case 4:
			m_Speed = v[5] + i;
			break;
		case 5:
			m_Speed = v[9] + i;

		}

		switch (m_Id) { //Segons el tamany, augment de la velocitat
		case MEDIUM:
			m_Speed += 1;
			break;
		case SMALL:
			m_Speed += 2;
			break;
		}
		//Controla la posició del mob, per tal que apareixi per l'altra banda de la pantalla si travessa la banda contrària
		if (m_Rect.x >= WIDTH - 10)
			m_Rect.x = -m_Rect.w + 10;
		else if (m_Rect.x <= -m_Rect.w + 9)
			m_Rect.x = WIDTH - 11;
		else if (m_Rect.y <= -m_Rect.h + 9)
			m_Rect.y = HEIGHT - 9;
		else if (m_Rect.y >= HEIGHT + m_Rect.h - 10)
			m_Rect.y = -m_Rect.h + 10;

		if (m_Id == UFOl || m_Id == UFOs) { // Camvi de direcció dels ovnis
			count++;
			if (count >= 150) {
				m_RDir = rand() % 8;
				count = 0;
			}
		}
		switch (m_RDir) { // Seteja la direcció dels mobs
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

		if (score >= 10000 * j) { //Augmenta la velocitat depenent de la score
			i++;
			j++;
		}

	}

	void destroy() {

		switch (getId()) { //Otorga punts en relñació al mob destruit

		case SMALL:
			score += 100;
			cout << "Small Destroyed!! Got 100 Points" << endl;
			break;

		case MEDIUM:
			score += 50;
			cout << "Medium Destroyed!! Got 50 Points" << endl;
			break;

		case LARGE:
			score += 20;
			cout << "Medium Destroyed!! Got 20 Points" << endl;
			break;

		case UFOs:
			score += 1000;
			cout << "Small UFO Destroyed!! Got 1000 Points." << endl;
			break;

		case UFOl:
			score += 200;
			cout << "Large UFO Destroyed!! Got 200 Points" << endl;
			break;

		}
	}
	bool boom() { 
		return kaput;// Destruit
	}
	void checkCollision(vector <Bullet2> bullets) { // Controla si la nau o una bala col·lisionen amb un mob
		Sprite b = S.getPlayer(); 

		if (b.getRect().x-2 >= m_Rect.x && b.getRect().x-2 <= m_Rect.x + m_Rect.w && b.getRect().y-2 >= m_Rect.y && b.getRect().y-2 <= m_Rect.y + m_Rect.h) {
			S.playerHit();
			cout << "spaceship hit" << endl;
			kaput = true;
			//destroy(m);
		}
		else if (b.getRect().x + 25 >= m_Rect.x && b.getRect().x + 25 <= m_Rect.x + m_Rect.w && b.getRect().y + 25 >= m_Rect.y && b.getRect().y + 25 <= m_Rect.y + m_Rect.h) {
			S.playerHit();
			cout << "HIT" << endl;
			kaput = true;
		}
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i].getPos().x >= m_Rect.x && bullets[i].getPos().x <= m_Rect.x + m_Rect.w && bullets[i].getPos().y >= m_Rect.y && bullets[i].getPos().y <= m_Rect.y + m_Rect.w) {
				kaput = true;
				//cout << "bullet hit" << endl;
				bullets[i].meteorHit = true;
			}

			if (bullets[i].getPos().x + 1 >= m_Rect.x && bullets[i].getPos().x + 1 <= m_Rect.x + m_Rect.w && bullets[i].getPos().y + 1 >= m_Rect.y && bullets[i].getPos().y + 1 <= m_Rect.y + m_Rect.w) {
				kaput = true;
				//cout << "bullet hit" << endl;
				bullets[i].meteorHit = true;
			}

		}
	}
	AsteroidID getId() {
		return m_Id; //Retorna l'id del mob
	}

};