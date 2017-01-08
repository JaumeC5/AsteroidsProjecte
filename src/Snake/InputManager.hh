#pragma once
#include "Init.hh"
#include "GameEngine.hh"
#include "SpaceShip.hh"
#include "Bullet.hh"

#define IM InputManager::Instance()
bool pause = false; //llevar de variable global

class InputManager {

	bool once = false;
	bool once2 = false;
	bool shot = false;

	vector<Bullet> bulletV;

public:
	inline static InputManager &Instance() {
		static InputManager inputManager;
		return inputManager;
	}

	void Update() {

		while (SDL_PollEvent(&evnt)) { // While input events exist, unpack them and store them in the SDL_Event variable one by one
			switch (evnt.type) {
			case SDL_QUIT:	isRunning = false;  break;
			case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x; playerTarget.y = evnt.motion.y; break; //std::cout << playerTarget.x << std::endl;
			case SDL_KEYDOWN:
				if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {

					if (!pause && !once) {
						cout << "Paused" << endl;
						pause = true;
						once = true;

					}
					else if (pause && !once) {
						cout << "Unpaused" << endl;
						pause = false;
						once = true;
					}
					once = false;

					break;
			/*
}
			if (currentKeyStates[SDL_SCANCODE_SPACE]) {
				if (!shot) {
					cout << "PEW" << endl; // generar bales aquí
					//B.renderBullet();
					shot = true;
				}
				shot = false;*/
				}
			
			}

		}
		Bullet newBullet;
		B.generateBullet();
		B.updateBullet();
		
		if (currentKeyStates[SDL_SCANCODE_SPACE]) {
			cout << "new Bullet" << endl;
			bulletV.push_back(newBullet);
			cout << "Bullet counter: " << bulletV.size() << endl;
			
		
		}
		SDL_RenderCopyEx(R.getRender(), B.getBullet().getTexture(), nullptr, &B.getBulletRect(), S.getAngle(), &S.getPos(), S.getFlip());
		B.updateBullet();
		//int bulletNum = bulletV.size();
		//SDL_RenderCopyEx(R.getRender(), bulletV[bulletNum].getBullet().getTexture(), nullptr, &bulletV[bulletNum].getBulletRect(), S.getAngle(), &S.getPos(), S.getFlip());
		for (int i = 0; i > bulletV.size(); i++) {
			SDL_RenderCopyEx(R.getRender(), bulletV[i].getBullet().getTexture(), nullptr, &bulletV[i].getBulletRect(), S.getAngle(), &S.getPos(), S.getFlip());
			bulletV[i].updateBullet();
			cout << "getBulletRect()" << B.getBulletRect().x << endl;
			cout << "Bullet nº" << i << "Pos x" << bulletV[i].getBulletRect().x << endl;
			cout << "Bullet nº" << i << "Pos y" << bulletV[i].getBulletRect().y << endl;
		}

		if (bulletV.size() > 2) {
			//cout << "Bala 1 Xpos: " << bulletV[1].getBulletRect().x << endl;
			//cout << "Bala 1 Ypos: " << bulletV[1].getBulletRect().y << endl;
		}

		if (bulletV.size() > 30) { //si n'hi ha mes de 30, elimina el primer i mou els elements del vector -1
			bulletV.erase(bulletV.begin());
			for (int i = 1; i < bulletV.size(); i++) {
					bulletV[i] = bulletV[i - 1];
			}
		}

		/*
		for (int i = 1; i < bulletV.size(); i++) {

			if (bulletV[i].getBulletRect().x > WIDTH || bulletV[i].getBulletRect().x < 0 ||
			bulletV[i].getBulletRect().y > HEIGHT || bulletV[i].getBulletRect().y < 0 ||
			bulletV.size() < 40) {

			bulletV.erase(bulletV.begin() + i - 1);
			cout << "rip bullet" << endl;

		}
		}*/

	}


	


	SDL_Rect getCoords() {
		return playerTarget;
	}

	bool on() {
		return isRunning;
	}


	bool onButton(SDL_Rect rect) {
		if (playerTarget.x >= rect.x && playerTarget.x <= rect.x + rect.w && playerTarget.y >= rect.y && playerTarget.y <= rect.y + rect.h && evnt.type == SDL_MOUSEBUTTONUP)
			return true;
		else
			return false;
	}

	void randCoords(Sprite s) {
		r = s.getRect();
		r.x = rand() % WIDTH;
		r.y = rand() % HEIGHT;
	}

private:
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	bool isRunning = true;
	SDL_Rect playerTarget = { 0,0,5,5 };
	SDL_Rect r;
	SDL_Event evnt;

};



