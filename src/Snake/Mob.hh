#pragma once
#include "Sprite.hh"
#include "ID.hh"
#include "Renderer.hh"
#include "configXML.hh"
#include "GameEngine.hh"
int scene = 1;
class Mob {
	//
	Sprite sp;
	SDL_Rect rect;
	int lvlSpeed;
	int rDir = rand() % 8;
	
public:
	void generate(AsteroidID type) {
		switch (type) {
		case SMALL:
			sp.setRect(rand() % (rand() % -99 + (-100)) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100), 25, 25);
			sp.setTexture(R.getRender(), "../../res/a1.png");
			break;

		case MEDIUM:
			sp.setRect(rand() % (rand() % -99 + (-100)) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100), 50, 50);
			sp.setTexture(R.getRender(), "../../res/a2.png");
			break;

		case LARGE:
			sp.setRect(rand() % (rand() % -99 + (-100)) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100), 100, 100);
			sp.setTexture(R.getRender(), "../../res/a3.png");
			break;

		case UFO:
			sp.setRect(rand() % (rand() % -99 + (-100)) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100), 25, 25);
			sp.setTexture(R.getRender(), "../../res/ufo.png");

		}
	}

	void getCoords() {
		rect = sp.getRect();
	}

	Sprite getSprite() {
		return sp;
	}

	SDL_Rect a() {
		return rect;
	}

	void mobMovement() { // FER MOURE ELS METEORITS
		
		
		std::vector <int> v;
		v = getProps(); // works
		int speed;
		switch (scene) {
		case 3:
			speed = v[1];
			break;
		case 4:
			speed = v[5];
			break;
		case 5:
			speed = v[9];

		}

		if (rect.x >= WIDTH)
			rect.x = 1;
		else if (rect.x <= 0)
			rect.x = WIDTH - 1;
		else if (rect.y <= 0)
			rect.y = HEIGHT;
		else if (rect.y >= HEIGHT + 1)
			rect.y = 1;
				
		switch (rDir) {
		case 0: //up
			rect.y -= speed;

			break;
		case 1: //up-right
			rect.x += speed;
			rect.y -= speed;				
			break;
		case 2: //right
			rect.x += speed;
			break;
		case 3: //right-down
			rect.x += speed;
			rect.y += speed;
			break;
		case 4:// down
			rect.y += speed;
			break;
		case 5://down-left
			rect.y += speed;
			rect.x -= speed;
			break;
		case 6://left
			rect.x -= speed;
			break;
		case 7://left-up
			rect.x -= speed;
			rect.y -= speed;
		default:
			break;	
		}
		
		//cout << rect.x << " " << rect.y << endl;
	}

	void destroy() {
		
	}


};