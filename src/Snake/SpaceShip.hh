#pragma once

#include "Sprite.hh"
#include "Renderer.hh"

using namespace std;

#define S SpaceShip::Instance()


class SpaceShip
{

private:
	SDL_Event evnt;
	
	float cosA = 0.0;
	float sinA = 0.0;
	
	double angle = 0.0;
	SDL_Point pos = { 0, 0 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	bool b[4]{ 0,0,0,0 };

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	Sprite player;
	SDL_Rect playerRect;

public:
	inline static SpaceShip &Instance() {
		static SpaceShip s;
		return s;
	}
	SpaceShip();

	void generatePlayer() {
		player.setRect(WIDTH / 2, HEIGHT / 2, 25, 25);
		player.setTexture(R.getRender(), "../../res/ship.png");
	}

	Sprite getPlayer() { return player; }
	SDL_Point getPos() { return pos; }
	SDL_RendererFlip getFlip() { return flip; }
	double getAngle() { return angle; }
	void getCoords() { playerRect = player.getRect();}

	void updatePos()
	{

		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
			b[0] = true;
			cout << "Rot: Left" << endl;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			b[1] = true;
			cout << "Rot: Right" << endl;
		}

		if (b[0]) { angle -= 5; };
		if (b[1]) { angle += 5; };


		if (angle >= 360) { angle -= 360; }
		if (angle <= -360) { angle += 360; }

		b[0] = false;
		b[1] = false;

		if (playerRect.x < 0) { playerRect.x = WIDTH; }
		if (playerRect.x > WIDTH) { playerRect.x = 0; }
		if (playerRect.y < 0) { playerRect.y = HEIGHT; }
		if (playerRect.y < HEIGHT) { playerRect.y = 0; }

	};

	

};