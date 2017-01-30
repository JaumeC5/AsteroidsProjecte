#pragma once

#include "Sprite.hh"
#include "Renderer.hh"
#include "configXML.hh"

#define PI 3.14159265358979323846264338327950288
#define S SpaceShip::Instance()
using namespace std;

class SpaceShip
{
private:
	double angle = 0.0;
	SDL_Point pos = { 12, 12 };
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
	vector <int> v = getProps();
	bool b[5]{ 0,0,0,0,0 };
	int k = 1;
	int hp;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	SDL_Event evnt;
	SDL_Rect playerTarget = { 0,0,5,5 };
	bool toggleMouse = false;
	Sprite playerIcon;
	int timer = 0;
	Sprite player;
	SDL_Rect playerRect = { WIDTH / 2, HEIGHT / 2 };

	float playerSpeed = 3;
	float angleSpeed = 4;

public:
	inline static SpaceShip &Instance() { //Singleton de la nau
		static SpaceShip s;
		return s;
	}
	bool getBool() {
		return b[4];
	}
	void setHp() { //Seteja les vides depenent de la dificultat
		if (scene == 3)
			hp = k * v[0];
		else if (scene == 4)
			hp = k * v[4];
		else if (scene == 5)
			hp = k * v[8];
	}
	
	bool dispar() { // Permet activar el dispar de les bales
		if (IM.shoot()) {
			return true;
		}
		else return false;
	}

	int getHp() { //Retorna les vides actuals del jugador
		return hp;
	}

	void generatePlayer() {
		player.setRect(playerRect.x, playerRect.y, 24, 24);
		player.setTexture(R.getRender(), "../../res/ship.png");
	}
	Sprite getPlayer() { return player; }
	SDL_Point getPos() { return pos; }
	SDL_RendererFlip getFlip() { return flip; }
	double getAngle() { return angle; }
	SDL_Rect getPlayerRect() { return playerRect; }

	void updatePos(bool hyper)
	{
		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
			b[0] = true;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			b[1] = true;
		}
		if (currentKeyStates[SDL_SCANCODE_UP]) {
			b[2] = true;
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN]) {
			b[3] = true;
		}

		if (b[0]) { angle -= angleSpeed; };
		if (b[1]) { angle += angleSpeed; };

		if (b[2]) {
			playerRect.x += playerSpeed * sin(angle * PI / 180.0);
			playerRect.y -= playerSpeed * cos(angle * PI / 180.0);
		}

		if (b[3]) {
			playerRect.x = playerRect.x - playerSpeed * sin(angle * PI / 180.0);
			playerRect.y = playerRect.y + playerSpeed * cos(angle * PI / 180.0);
		}

		if (angle >= 360) { angle -= 360; }
		if (angle <= -360) { angle += 360; }

		b[0] = false; b[1] = false; b[2] = false; b[3] = false; b[4] = false;

		if (playerRect.x >= WIDTH)
			playerRect.x = -playerRect.w;
		else if (playerRect.x <= -playerRect.w)
			playerRect.x = WIDTH;
		else if (playerRect.y <= -playerRect.h)
			playerRect.y = HEIGHT;
		else if (playerRect.y >= HEIGHT + playerRect.h)
			playerRect.y = -playerRect.h;
	}
	void hyperSpace() {
		playerRect.x = rand() % WIDTH;
		playerRect.y = rand() % HEIGHT;
	}
	void playerHit() { // Resta una vida al jugador i el posa enmig de la pantalla
		playerRect.x = WIDTH / 2;
		playerRect.y = HEIGHT / 2;
		hp -= 1;
		cout << "hp: " << hp << endl;
	}

};