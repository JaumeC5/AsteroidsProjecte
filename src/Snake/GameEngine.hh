#pragma once

#include "Init.hh"
#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include <sstream> // faltava aixo paio
#include <stdlib.h>
#include "InputManager.hh"
#include "Mob.hh"
#include "SpaceShip.hh"


void getConfig() {

using namespace rapidxml;
using namespace std;
int temp;
vector <int> props;

xml_document <>doc;
ifstream file("config.xml");
stringstream buffer;
buffer << file.rdbuf();
file.close();
string content(buffer.str());
doc.parse<0>(&content[0]);

xml_node<> *root = doc.first_node();

for (xml_node <> *node = root->first_node("Level"); node; node = node->next_sibling()) {
	xml_attribute <> *attr = node->first_attribute();
	cout << attr->value() << endl;

	for (xml_node <> *n = node->first_node(); n; n = n->next_sibling()) {
		cout << n->name() << ": " << n->value() << endl;
		temp = atoi(n->value());
		props.push_back(temp);


	}
	cout << endl;


}
for (int i = 0; i < props.size(); i++) {
	cout << props[i] << " ";
}

}

void Run() {
	init();
	int counter = 0;
	int maxMobs = 0;
	int mobsCreated = 0;
	int toGenerate = 0;
	TTF_Font * font = TTF_OpenFont("../../res/ka1.ttf", 35);
	SDL_Color color = { 255, 255, 255 };

	Window window("Asteroids");

	R.setWindow(window.getWindow());

	Sprite bg;
	bg.setTexture(R.getRender(), "../../res/bgmenu.jpg");
	bg.setRect(0, 0, WIDTH, HEIGHT);

	Sprite bgeasy;
	bgeasy.setTexture(R.getRender(), "../../res/bgeasy.jpg");
	bgeasy.setRect(0, 0, WIDTH, HEIGHT);

	Sprite bgmedium;
	bgmedium.setTexture(R.getRender(), "../../res/bgmedium.jpg");
	bgmedium.setRect(0, 0, WIDTH, HEIGHT);

	Sprite bghard;
	bghard.setTexture(R.getRender(), "../../res/bghard.jpg");
	bghard.setRect(0, 0, WIDTH, HEIGHT);


	Sprite title;
	title.setRect(WIDTH / 2 - 100, 50, 200, 50);
	title.setSurface(font, "Asteroids", color);

	Sprite play;
	play.setRect(WIDTH / 2 - 40, HEIGHT - 150, 100, 50);
	play.setSurface(font, "Play", color);

	Sprite exit;
	exit.setRect(WIDTH / 2 - 40, HEIGHT - 90, 100, 50);
	exit.setSurface(font, "Exit", color);

	Sprite easy;
	easy.setRect(40, HEIGHT / 2, 100, 50);
	easy.setSurface(font, "Easy", color);

	Sprite medium;
	medium.setRect(WIDTH / 2 - 40, HEIGHT / 2, 100, 50);
	medium.setSurface(font, "Medium", color);

	Sprite hard;
	hard.setRect(WIDTH - 40 - 80, HEIGHT / 2, 100, 50);
	hard.setSurface(font, "Hard", color);

	Sprite pauseMessage;
	pauseMessage.setRect(WIDTH / 2 - 100, HEIGHT / 2 - 50, 200, 100);
	pauseMessage.setSurface(font, "Pause", color);

	Sprite player;
	player.setRect(WIDTH / 2, HEIGHT / 2, 25, 25);
	player.setTexture(R.getRender(), "../../res/ship.png");

	Mob s;
	s.generate(SMALL);
	s.getCoords();

	Mob m;
	m.generate(MEDIUM);
	m.getCoords();

	Mob aux;
	aux.generate(LARGE);
	aux.getCoords();

	Mob u;
	u.generate(UFO);
	vector <Mob> mobs = { aux };

	//LOOP
	while (IM.on()) {
		IM.Update();
		S.updatePos();
		//std::cout << scene << std::endl;
		switch (scene) {
		case 1:
			SDL_RenderCopy(R.getRender(), bg.getTexture(), nullptr, &bg.getRect());
			SDL_RenderCopy(R.getRender(), play.convertSurface(R.getRender()), nullptr, &play.getRect());
			SDL_RenderCopy(R.getRender(), exit.convertSurface(R.getRender()), nullptr, &exit.getRect());
			SDL_RenderCopy(R.getRender(), title.convertSurface(R.getRender()), nullptr, &title.getRect());
		

			if (IM.onButton(play.getRect()))
				scene = 2;
			else if (IM.onButton(exit.getRect())) {
				IMG_Quit();
				SDL_Quit();
				TTF_Quit();
			}
			break;
		case 2:
			SDL_RenderCopy(R.getRender(), bg.getTexture(), nullptr, &bg.getRect());
			SDL_RenderCopy(R.getRender(), easy.convertSurface(R.getRender()), nullptr, &easy.getRect());
			SDL_RenderCopy(R.getRender(), medium.convertSurface(R.getRender()), nullptr, &medium.getRect());
			SDL_RenderCopy(R.getRender(), hard.convertSurface(R.getRender()), nullptr, &hard.getRect());

			if (IM.onButton(easy.getRect()))
				scene = 3;
			if (IM.onButton(medium.getRect()))
				scene = 4;
			if (IM.onButton(hard.getRect()))
				scene = 5;
			break;
			


		case 3:

			if (pause)
				SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
			else {
				SDL_RenderCopy(R.getRender(), bgeasy.getTexture(), nullptr, &bgeasy.getRect());
				SDL_RenderCopyEx(R.getRender(), player.getTexture(), nullptr, &player.getRect(), S.getAngle(), &S.getPos(), S.getFlip());
				if (pause)
					SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());

				else {
					counter++;
					maxMobs = 5;
					if (counter % 150 == 0 && mobsCreated < maxMobs) {
						Mob x;
						toGenerate = rand() % 3;
						switch (toGenerate) {
						case 0:
							x.generate(SMALL);
							x.getCoords();
							mobs.push_back(x);
							break;
						case 1:
							x.generate(MEDIUM);
							x.getCoords();
							mobs.push_back(x);
							break;
						case 2:
							x.generate(LARGE);
							x.getCoords();
							mobs.push_back(x);
							break;
						}

						mobsCreated++;
					}

					for (int i = 0; i < mobs.size(); i++) {
						SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
						mobs[i].mobMovement();
					}
			}

			
			}

			break;
		case 4:
			break;
		case 5:
			break;

		}
		SDL_RenderPresent(R.getRender());
	}
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}




