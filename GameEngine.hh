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
#include "Ranking.hh"


std::mutex mut;
using namespace rapidxml;
using namespace std;



class GameEngine {
	vector <Mob> mobs;
	Mix_Music *music = NULL;
	Mix_Chunk *bullet = NULL;
	Mix_Chunk *meteor = NULL;
	Mix_Chunk *death = NULL;
	TTF_Font * font = TTF_OpenFont("../../res/ka1.ttf", 35);
	SDL_Color color = { 255, 255, 255 };
	bool ranking = false;
	int counter = 0; // permet generar asteroides cada cert temps
	int maxMobs = 0; // maxim num d'asteroides creats depenent del nivell
	int mobsCreated = 0; // contador dels asteroides creats
	int toGenerate = 0; // crea asteroides depenent d'un numero
	int level = 1; // current level of the game. Increases everytime all asteroids are destroyed
	vector <int> v = getProps();
	Scene s_Menu;
	Scene Game;
	Scene Ranking;
public:

	void Run();
	void lvlup();
	void generateMobs();
	//void loop();
	//void pause(SDL_Rect, SDL_Rect, SDL_Rect);
	//void showRank();
};

void GameEngine::Run() {
	init();
	char buffer[150];
	TTF_Font * font = TTF_OpenFont("../../res/ka1.ttf", 35);
	SDL_Color color = { 255, 255, 255 };


	music = Mix_LoadMUS("../../res/music.wav");
	bullet = Mix_LoadWAV("../../res/blaster.wav");
	meteor = Mix_LoadWAV("../../res/boom.wav");
	death = Mix_LoadWAV("../../res/muerte.wav");

	Mix_PlayMusic(music, 0); // MUSICA

	Window window("Asteroids");

	R.setWindow(window.getWindow());
	RK.setRank();
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

	Sprite bgRank;
	bgRank.setTexture(R.getRender(), "../../res/bgmenu.jpg");
	bgRank.setRect(0, 0, WIDTH, HEIGHT);

	Sprite title;
	title.setRect(WIDTH / 2 - 100, 50, 200, 50);
	title.setSurface(font, "Asteroids", color);

	Sprite play;
	play.setRect(WIDTH / 2 - 40, HEIGHT - 225, 100, 50);
	play.setSurface(font, "Play", color);

	Sprite rank;
	rank.setRect(WIDTH / 2 - 40, HEIGHT - 150, 100, 50);
	rank.setSurface(font, "Rank", color);

	Sprite back;
	back.setRect(WIDTH - 100, HEIGHT - 50, 75, 45);
	back.setSurface(font, "Back", color);

	Sprite exit;
	exit.setRect(WIDTH / 2 - 40, HEIGHT - 75, 100, 50);
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

	Sprite sc;
	sc.setRect(WIDTH - 150, HEIGHT - 100, 100, 75);

	Sprite gameOver;
	gameOver.setRect(WIDTH / 2 - 115, HEIGHT / 2 - 50, 230, 100);
	gameOver.setSurface(font, "Game Over", color);

	Sprite bullet;
	bullet.setTexture(R.getRender(), "../../res/bullet.png");
	//thread th;

	
	
	
	mut.unlock();


	//LOOP
	while (IM.on()) {
		
		Bullet2 b(bullet);
		vector <Bullet2> bullets(10, b);


		
		//cout << bullets.size() << endl;
		switch (scene) {
		case 1:
			s_Menu.onEntry("../../res/bgmenu.jpg");
			s_Menu.Draw();
			SDL_RenderCopy(R.getRender(), play.convertSurface(R.getRender()), nullptr, &play.getRect());
			SDL_RenderCopy(R.getRender(), exit.convertSurface(R.getRender()), nullptr, &exit.getRect());
			SDL_RenderCopy(R.getRender(), rank.convertSurface(R.getRender()), nullptr, &rank.getRect());
			SDL_RenderCopy(R.getRender(), title.convertSurface(R.getRender()), nullptr, &title.getRect());
			//bullets[0].renderBullet(R.getRender());

			if (IM.onButton(play.getRect()))
				scene = 2;
			else if (IM.onButton(exit.getRect())) {
				IMG_Quit();
				SDL_Quit();
				TTF_Quit();
			}
			else if (IM.onButton(rank.getRect())) {
				scene = 6;


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
					//cout << score << endl;
					RK.check();
					RK.updateRank(score);
					
					scene = 1;
					pause = false;
					mobsCreated = 0;
					
					score = 0;
					mobs.clear();
				}
				mut.unlock();
			}

			else {
				S.updatePos();
				S.generatePlayer();
				S.setHp();
				
				//cout << S.getHp() << endl;
				
				_itoa_s(score, buffer, 10);
				sc.setSurface(font, buffer, color);

				
				mut.lock();
				
				SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip());
				SDL_RenderCopy(R.getRender(), sc.convertSurface(R.getRender()), nullptr, &sc.getRect());
				counter++;
				if (counter % 350 == 0) {
					Mob z;
					z.generate(UFOl, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
					z.getCoords();
					mobs.push_back(z);
				}
				maxMobs = v[2];
				if (mobsCreated < maxMobs) {
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
					default:
						break;
					}

					mobsCreated++;
					//std::cout << "wow" << endl;

				}
				lvlup();
				//cout << mobs.size() << endl;
				//b.renderBullet();
				for (int i = 0; i < mobs.size(); i++) {
					SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
					
					mobs[i].mobMovement();
					mobs[i].checkCollision(mobs);
					if (mobs[i].boom()) {
						Mix_PlayChannel(-1, meteor, 0);
						mobs[i].destroy();
						Mob m1, m2;
						if (mobs[i].getId() == MEDIUM) {
							m1.generate(SMALL, mobs[i].a().x, mobs[i].a().y);
							m2.generate(SMALL, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						else if (mobs[i].getId() == LARGE) {
							m1.generate(MEDIUM, mobs[i].a().x, mobs[i].a().y);
							m2.generate(MEDIUM, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						else if (mobs[i].getId() == UFOl) {
							Mix_PlayChannel(-1, death, 0);

							m1.generate(UFOs, mobs[i].a().x + 25, mobs[i].a().y + 25);
							m2.generate(UFOs, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						mobs.erase(mobs.begin() + i);// borra asteroides del vector


					}
				}


				mut.unlock();
			}

			break;
			//
		case 4:
			Game.Draw();
			B.generateBullet();
			B.getPositions();
			if (pause) {
				mut.lock();
				SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
				SDL_RenderCopy(R.getRender(), continueButton.convertSurface(R.getRender()), nullptr, &continueButton.getRect());
				SDL_RenderCopy(R.getRender(), exitButton.convertSurface(R.getRender()), nullptr, &exitButton.getRect());

				if (IM.onButton(continueButton.getRect()))
					pause = false;
				if (IM.onButton(exitButton.getRect())) {
					//cout << score << endl;
					RK.check();
					RK.updateRank(score);

					scene = 1;
					pause = false;
					mobsCreated = 0;

					score = 0;
					mobs.clear();
				}
				mut.unlock();
			}

			else {
				S.updatePos();
				S.generatePlayer();
				S.setHp();
				B.renderBullet();
				_itoa_s(score, buffer, 10);
				sc.setSurface(font, buffer, color);


				mut.lock();
				SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip());
				SDL_RenderCopy(R.getRender(), sc.convertSurface(R.getRender()), nullptr, &sc.getRect());

				counter++;
				maxMobs = v[2];
				if (mobsCreated < maxMobs) {
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
					default:
						break;
					}

					mobsCreated++;
					//std::cout << "wow" << endl;

				}
				lvlup();
				//cout << mobs.size() << endl;

				for (int i = 0; i < mobs.size(); i++) {
					SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
					mobs[i].mobMovement();
					mobs[i].checkCollision(mobs);
					if (mobs[i].boom()) {
						Mix_PlayChannel(-1, meteor, 0);
						mobs[i].destroy();
						Mob m1, m2;
						if (mobs[i].getId() == MEDIUM) {
							m1.generate(SMALL, mobs[i].a().x, mobs[i].a().y);
							m2.generate(SMALL, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						else if (mobs[i].getId() == LARGE) {
							m1.generate(MEDIUM, mobs[i].a().x, mobs[i].a().y);
							m2.generate(MEDIUM, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						else if (mobs[i].getId() == UFOl) {
							Mix_PlayChannel(-1, death, 0);

							m1.generate(UFOs, mobs[i].a().x + 25, mobs[i].a().y + 25);
							m2.generate(UFOs, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						mobs.erase(mobs.begin() + i);// borra asteroides del vector


					}
				}


				mut.unlock();
			}

			break;
			//
		case 5:
			Game.Draw();
			B.generateBullet();
			B.getPositions();
			if (pause) {
				mut.lock();
				SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
				SDL_RenderCopy(R.getRender(), continueButton.convertSurface(R.getRender()), nullptr, &continueButton.getRect());
				SDL_RenderCopy(R.getRender(), exitButton.convertSurface(R.getRender()), nullptr, &exitButton.getRect());

				if (IM.onButton(continueButton.getRect()))
					pause = false;
				if (IM.onButton(exitButton.getRect())) {
					//cout << score << endl;
					RK.check();
					RK.updateRank(score);

					scene = 1;
					pause = false;
					mobsCreated = 0;

					score = 0;
					mobs.clear();
				}
				mut.unlock();
			}

			else {
				S.updatePos();
				S.generatePlayer();
				S.setHp();
				B.renderBullet();
				_itoa_s(score, buffer, 10);
				sc.setSurface(font, buffer, color);


				mut.lock();
				SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip());
				SDL_RenderCopy(R.getRender(), sc.convertSurface(R.getRender()), nullptr, &sc.getRect());

				counter++;
				maxMobs = v[2];
				if (mobsCreated < maxMobs) {
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
					default:
						break;
					}

					mobsCreated++;
					//std::cout << "wow" << endl;

				}
				lvlup();
				//cout << mobs.size() << endl;

				for (int i = 0; i < mobs.size(); i++) {
					SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
					mobs[i].mobMovement();
					mobs[i].checkCollision(mobs);
					if (mobs[i].boom()) {
						Mix_PlayChannel(-1, meteor, 0);
						mobs[i].destroy();
						Mob m1, m2;
						if (mobs[i].getId() == MEDIUM) {
							m1.generate(SMALL, mobs[i].a().x, mobs[i].a().y);
							m2.generate(SMALL, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						else if (mobs[i].getId() == LARGE) {
							m1.generate(MEDIUM, mobs[i].a().x, mobs[i].a().y);
							m2.generate(MEDIUM, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						else if (mobs[i].getId() == UFOl) {
							Mix_PlayChannel(-1, death, 0);

							m1.generate(UFOs, mobs[i].a().x + 25, mobs[i].a().y + 25);
							m2.generate(UFOs, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						mobs.erase(mobs.begin() + i);// borra asteroides del vector


					}
				}


				mut.unlock();
			}

			break;
			//
				
			

			break;
		case 6:
			SDL_RenderCopy(R.getRender(), bgRank.getTexture(), nullptr, &bgRank.getRect());
			SDL_RenderCopy(R.getRender(), back.convertSurface(R.getRender()), nullptr, &back.getRect());
			if (IM.onButton(back.getRect()))
				scene = 1;

			
			RK.print(font, color);
			RK.check();

			break;

		case 7:
			s_Menu.Draw();
			SDL_RenderCopy(R.getRender(), gameOver.getTexture(), nullptr, &gameOver.getRect());


		}
		IM.Update(bullets);
		SDL_RenderPresent(R.getRender());
	}
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void GameEngine::lvlup() {


	if (mobs.size() == 0) {
		++level;

		switch (scene) {
		case 3:
			maxMobs = v[2] + (v[3] * level);
			break;
		case 4:
			maxMobs = v[6] + (v[7] * level);
			break;
		case 5:
			maxMobs = v[10] + (v[11] * level);
			break;

		}
		mobs.clear();
		mobsCreated = 0;
		counter = 0;
	}
	generateMobs();


}

void GameEngine::generateMobs() {
	if (mobsCreated < maxMobs) {
		Mob x;
		/*toGenerate = rand() % 3;
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
		case 2:*/
		x.generate(LARGE, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
		x.getCoords();
		mobs.push_back(x);
		/*	break;
		default:
		break;
		}*/

		mobsCreated++;
		//std::cout << "wow" << endl;

	}
}




