#pragma once

#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <stdlib.h>
#include "InputManager.hh"
#include "Mob.hh"
#include "SpaceShip.hh"
#include "Scene.hh"
#include <thread>
#include <mutex>
#include "SDL_mixer.h"
#include "Bullet.hh"


std::mutex mut;
using namespace rapidxml;
using namespace std;

class GameEngine {
vector <Mob> mobs;
Mix_Music *music = NULL;
Mix_Chunk *bullet = NULL;
Mix_Chunk *meteor = NULL;

const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

public:

	void Run() {
		init();
		int counter = 0;
		int maxMobs = 0;
		int mobsCreated = 0;
		int toGenerate = 0;

		TTF_Font * font = TTF_OpenFont("../../res/ka1.ttf", 35);
		SDL_Color color = { 255, 255, 255 };
		music = Mix_LoadMUS("../../res/music.wav");
		bullet = Mix_LoadWAV("../../res/laser.wav");

		Mix_PlayMusic(music, 0);

		Window window("Asteroids");

		R.setWindow(window.getWindow());
		mut.lock();
		Scene s_Menu;
		Scene Game;
		vector <int> props = getProps();

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
		pauseMessage.setRect(WIDTH / 2 - 50, 100, 100, 50);
		pauseMessage.setSurface(font, "Pause", color);

		Sprite continueButton;
		continueButton.setRect(WIDTH / 2 - 115, HEIGHT / 2 - 50, 230, 100);
		continueButton.setSurface(font, "Continue", color);

		Sprite exitButton;
		exitButton.setRect(WIDTH / 2 - 115, HEIGHT / 2 + 50, 150, 100);
		exitButton.setSurface(font, "Exit", color);
		mut.unlock();


		//LOOP
		while (IM.on()) {
			IM.Update();


			switch (scene) {
			case 1:
				s_Menu.onEntry("../../res/bgmenu.jpg");
				s_Menu.Draw();
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
				s_Menu.Draw();
				SDL_RenderCopy(R.getRender(), easy.convertSurface(R.getRender()), nullptr, &easy.getRect());
				SDL_RenderCopy(R.getRender(), medium.convertSurface(R.getRender()), nullptr, &medium.getRect());
				SDL_RenderCopy(R.getRender(), hard.convertSurface(R.getRender()), nullptr, &hard.getRect());

				if (IM.onButton(easy.getRect())) {
					Game.onEntry("../../res/bgeasy.jpg");
					scene = 3;
				}
				if (IM.onButton(medium.getRect())) {
					Game.onEntry("../../res/bgmedium.jpg");
					scene = 4;
				}

				if (IM.onButton(hard.getRect())) {
					Game.onEntry("../../res/bghard.jpg");
					scene = 5;
				}
				break;

			case 3:

				Game.Draw();
				

				if (pause) {
					mut.lock();
					SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
					SDL_RenderCopy(R.getRender(), continueButton.convertSurface(R.getRender()), nullptr, &continueButton.getRect());
					SDL_RenderCopy(R.getRender(), exitButton.convertSurface(R.getRender()), nullptr, &exitButton.getRect());

					if (IM.onButton(continueButton.getRect()))
						pause = false;
					if (IM.onButton(exitButton.getRect())) {
						scene = 1;
						pause = false;
						mobsCreated = 0;
						mobs.clear();
					}
					mut.unlock();
				}

				else {
					S.updatePos();
					S.generatePlayer();
					
					mut.lock();
					SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip());
				
				
				
					counter++;
					maxMobs = 5;
					if (counter % 150 == 0 && mobsCreated < maxMobs) {
						Mob x;
						toGenerate = rand() % 3;
						switch (toGenerate) {
						case 0:
							x.generate(SMALL, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						case 1:
							x.generate(MEDIUM, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						case 2:
							x.generate(LARGE, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						}

						mobsCreated++;
						std::cout << "wow" << endl;
					}

					for (int i = 0; i < mobs.size(); i++) {
						SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
						mobs[i].mobMovement();
						mobs[i].checkCollision();
					}

					mut.unlock();

					

				}

				break;

			case 4:
				Game.Draw();

				if (pause) {
					mut.lock();
					SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
					SDL_RenderCopy(R.getRender(), continueButton.convertSurface(R.getRender()), nullptr, &continueButton.getRect());
					SDL_RenderCopy(R.getRender(), exitButton.convertSurface(R.getRender()), nullptr, &exitButton.getRect());

					if (IM.onButton(continueButton.getRect()))
						pause = false;
					if (IM.onButton(exitButton.getRect())) {
						scene = 1;
						pause = false;
						mobsCreated = 0;
						mobs.clear();
					}
					mut.unlock();
				}
				else {
					S.updatePos();
					S.generatePlayer();

					mut.lock();
					SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip());

					counter++;
					maxMobs = 7;
					if (counter % 120 == 0 && mobsCreated < maxMobs) {
						Mob x;
						toGenerate = rand() % 3;
						switch (toGenerate) {
						case 0:
							x.generate(SMALL, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						case 1:
							x.generate(MEDIUM, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						case 2:
							x.generate(LARGE, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						}

						mobsCreated++;
						std::cout << "wow" << endl;
					}

					for (int i = 0; i < mobs.size(); i++) {
						SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
						mobs[i].mobMovement();
						mobs[i].checkCollision();
					}

					mut.unlock();

				}

				break;
			case 5:
				Game.Draw();

				S.updatePos();
				S.generatePlayer();

				if (pause) {
					mut.lock();
					SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
					SDL_RenderCopy(R.getRender(), continueButton.convertSurface(R.getRender()), nullptr, &continueButton.getRect());
					SDL_RenderCopy(R.getRender(), exitButton.convertSurface(R.getRender()), nullptr, &exitButton.getRect());

					if (IM.onButton(continueButton.getRect()))
						pause = false;
					if (IM.onButton(exitButton.getRect())) {
						scene = 1;
						pause = false;
						mobsCreated = 0;
						mobs.clear();
					}
					mut.unlock();
				}
				else {
					mut.lock();
					SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip());

					counter++;
					maxMobs = 5;
					if (counter % 90 == 0 && mobsCreated < maxMobs) {
						Mob x;
						toGenerate = rand() % 3;
						switch (toGenerate) {
						case 0:
							x.generate(SMALL, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						case 1:
							x.generate(MEDIUM, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						case 2:
							x.generate(LARGE, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
							x.getCoords();
							mobs.push_back(x);
							break;
						}

						mobsCreated++;
						std::cout << "wow" << endl;
					}

					for (int i = 0; i < mobs.size(); i++) {
						SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
						mobs[i].mobMovement();
						mobs[i].checkCollision();
					}

					mut.unlock();
					

				}

				break;

			}
			SDL_RenderPresent(R.getRender());
		}
		IMG_Quit();
		SDL_Quit();
		TTF_Quit();
	}

};


	





