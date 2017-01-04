#pragma once

#include "Sprite.hh"
#include "Renderer.hh"
using namespace std;

#define PI 3.14159265358979323846264338327950288

#define S SpaceShip::Instance()


class SpaceShip
{

private:
	double angle = 0.0;
	SDL_Point pos = { 0, 0 };
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

	bool b[5]{ 0,0,0,0,0 };

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	Sprite player;
	SDL_Rect playerRect = { WIDTH / 2, HEIGHT / 2 };

	float playerSpeed = 3;
	float angleSpeed = 4;

public:
	inline static SpaceShip &Instance() {
		static SpaceShip s;
		return s;
	}
	SpaceShip();

	void generatePlayer() {
		player.setRect(playerRect.x, playerRect.y, 25, 25);
		player.setTexture(R.getRender(), "../../res/ship.png");
	}

	Sprite getPlayer() { return player; }
	SDL_Point getPos() { return pos; }
	SDL_RendererFlip getFlip() { return flip; }
	double getAngle() { return angle; }
	SDL_Rect getPlayerRect() { return playerRect; }

	
	

	float moveBackward() {
		
	}

	void updatePos()
	{
		
		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
			b[0] = true;
			//cout << "Rot: Left" << endl;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			b[1] = true;
			//cout << "Rot: Right" << endl;
		}

		if (currentKeyStates[SDL_SCANCODE_UP]) {
			b[2] = true;
			//cout << "Mov: Forward" << endl;
		}

		if (currentKeyStates[SDL_SCANCODE_DOWN]) {
			b[3] = true;
			//cout << "Mov: Backward" << endl;
		}
		if (currentKeyStates[SDL_SCANCODE_V]) {
			b[4] = true;
		}

		//Moure tot aixo fora de l'update?
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
		if (b[4]) { //Hiperespacio
			playerRect.x = rand() % WIDTH;
			playerRect.y = rand() % HEIGHT;
		}


		if (angle >= 360) { angle -= 360; }
		if (angle <= -360) { angle += 360; }

		b[0] = false; b[1] = false; b[2] = false; b[3] = false; b[4] = false;

		cout << "X Pos: " << playerRect.x << endl;
		cout << "Y Pos: " << playerRect.y << endl;
		cout << "Angle: " << angle << endl;
		cout << "AngleCos: " << sin(angle * PI / 180.0) << endl;
		cout << "AngleSin: " << cos(angle * PI / 180.0) << endl << endl;
		
		
		if (playerRect.x < 0) { playerRect.x = WIDTH; }
		if (playerRect.x > WIDTH) { playerRect.x = 0; }
		if (playerRect.y < 0) { playerRect.y = HEIGHT; }
		if (playerRect.y > HEIGHT) { playerRect.y = 0; }
		

	};

};