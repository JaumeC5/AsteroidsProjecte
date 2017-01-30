#pragma once


#include <stdio.h>
#include <stdlib.h>
#include "InputManager.hh"
#include "Scene.hh"
#include <thread>
#include <mutex>
#include "SDL_mixer.h"
#include "Ranking.hh"
#include "Bullet2.hh"
#include "UFOBullet.h"


std::mutex mut;
using namespace rapidxml;
using namespace std;



class GameEngine {
	vector <Mob> mobs;
	int ufoBulletCounter = 0;
	Mix_Music *music = NULL;
	Mix_Chunk *blaster = NULL;
	Mix_Chunk *meteor = NULL;
	Mix_Chunk *death = NULL;
	TTF_Font * font = TTF_OpenFont("../../res/ka1.ttf", 35);
	SDL_Color color = { 255, 255, 255 };
	bool ranking = false; // S'activa o desactiva depenent de com s'entri en l'escena de ranking
	int rankScene = 0;
	int counter = 0; // Permet generar asteroides cada cert temps
	int maxMobs = 0; // Máxim num d'asteroides creats depenent del nivell
	int mobsCreated = 0; // Contador dels asteroides creats
	int toGenerate = 0; // Crea asteroides depenent d'un numero
	int level = 1; // Nivell en que es troba el jugador
	
	bool hpSet = false;
	int bulletCounter = 0;
	vector <int> v = getProps(); // Vector emprat per configurar el joc. S'umple per mitjà del fitxer xml de configuració.
	Scene s_Menu; // Escena del menú
	Scene Game; // Escena del joc
	int time = 0;
	int temp = 0;
	int temp2 = 0; // Comptadors de frames;
	int timeZ = 0; // Seteja un cooldown per l'hyperspace

public:

	void Run(); // Funció principal
	void lvlup(); // Funció que augmenta la dificultat del joc cada vegada que tots els enemics són destruits
	void generateMobs();// Genera a tots els enemics depenent del nivell en que es trobi el jugador
	void loop(Sprite p, Sprite c, Sprite e, char*b, Sprite sc, Sprite pI, vector <Bullet2> bullts); //funció que permet acurçar el codi a la meitat o més, el problema es que no permet que ni l'sstream ni el _itoa_s funcionin
;
};

void GameEngine::Run() {
	init();
	char buffer[50];
	TTF_Font * font = TTF_OpenFont("../../res/ka1.ttf", 35); 
	SDL_Color color = { 255, 255, 255 };


	music = Mix_LoadMUS("../../res/music.wav");
	blaster = Mix_LoadWAV("../../res/blaster.wav");
	meteor = Mix_LoadWAV("../../res/boom.wav");
	death = Mix_LoadWAV("../../res/muerte.wav"); // els efectes de so i la musica

	Mix_FadeInMusic(music, -1, 0); // MUSICA
	

	Window window("Asteroids. By Toni Ferrari and Jaume Company"); // obri la finestra amb el nom del joc

	R.setWindow(window.getWindow());
	RK.setRank();
	Scene s_Menu;
	Scene Game;
	vector <int> props = getProps(); // el vector de configuració d'umple amb les dades que conté l'xml

	Sprite playerIcon;												// Tots els sprites necessaris per navegar entre els menús del joc
	playerIcon.setTexture(R.getRender(), "../../res/ship.png");


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
	play.setRect(WIDTH / 2 - 40, 130, 100, 50);
	play.setSurface(font, "Play", color);

	Sprite rank;
	rank.setRect(WIDTH / 2 - 40, 190, 100, 50);
	rank.setSurface(font, "Rank", color);

	Sprite back;
	back.setRect(WIDTH - 100, HEIGHT - 50, 75, 45);
	back.setSurface(font, "Back", color);

	Sprite exit;
	exit.setRect(WIDTH / 2 - 40, 250, 100, 50);
	exit.setSurface(font, "Exit", color);

	Sprite easy;
	easy.setRect(40, HEIGHT / 2, 100, 50);
	easy.setSurface(font, "Easy", color);

	Sprite medium;
	medium.setRect(WIDTH / 2 - 40, HEIGHT / 2 + 100, 100, 50);
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

	Sprite game;
	game.setRect(30, HEIGHT / 2 - 140, 160, 100);
	game.setSurface(font, "Game", color);
	Sprite over;
	over.setRect(30, HEIGHT / 2, 160, 100);
	over.setSurface(font, "Over", color);

	Sprite bullet;
	bullet.setTexture(R.getRender(), "../../res/bullet.png");

	Sprite enemyBullet;
	enemyBullet.setTexture(R.getRender(), "../../res/ufobullet.png");

	Bullet2 b(bullet);
	vector <Bullet2> bullets(10, b); // Vector de bales del jugador

	UFOBullet uB(enemyBullet);
	vector <UFOBullet> ufoB(10, uB); //Vector de bales dels enemics que poden disparar

	//Bucle del joc
	while (IM.on()) {
		switch (scene) {
		case 1:
			temp2 = 0;
			temp = 0;
			score = 0;
			mobsCreated = 0;
			maxMobs = 0; // S'inicien les variables que permeten el trascurs normal d'una partida
			mobs.clear();
			s_Menu.onEntry("../../res/bgmenu.jpg");
			s_Menu.Draw();
			SDL_RenderCopy(R.getRender(), play.convertSurface(R.getRender()), nullptr, &play.getRect());
			SDL_RenderCopy(R.getRender(), exit.convertSurface(R.getRender()), nullptr, &exit.getRect());
			SDL_RenderCopy(R.getRender(), rank.convertSurface(R.getRender()), nullptr, &rank.getRect());
			SDL_RenderCopy(R.getRender(), title.convertSurface(R.getRender()), nullptr, &title.getRect()); // Es pinta el menú principal

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
			SDL_RenderCopy(R.getRender(), back.convertSurface(R.getRender()), nullptr, &back.getRect()); // Es pinta el menú de selecció de dificultat
			if (!ranking) {
				if (IM.onButton(easy.getRect())) {
					Game.onEntry("../../res/bgeasy.jpg");
					scene = 3;
				}
				if (IM.onButton(medium.getRect())) {
					Game.onEntry("../../res/bgmedium.jpg");
					scene = 4;
				}

				if (IM.onButton(hard.getRect())) {
					Game.onEntry("../../res/bghard.jpg");			//Depenent de com s'accedeixi a aquest menú, mitjançant el rànking o la selecció de dificultat,
					scene = 5;										//el joc es permetrà jugar al jugador el mode de dificultat seleccionat o mirar les millors puntuacions de cada mode de dificultat
					
				}
			}
			else {
				if (IM.onButton(easy.getRect())) {
					rankScene = 1;
					scene = 6;
				}
				if (IM.onButton(medium.getRect())) {
					rankScene = 2;
					scene = 6;
				}

				if (IM.onButton(hard.getRect())) {
					rankScene = 3;
					scene = 6;
				}
			}

			if (IM.onButton(back.getRect())) {
				scene = 1;
				ranking = false;
			}

			break;

		case 3:  //Nivell de dificultat 1
			Game.Draw();

			if (pause) { // Si la pausa està activa, s'obre un menú i el joc s'atura fins que el jugador decideixi
				mut.lock();
				SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
				SDL_RenderCopy(R.getRender(), continueButton.convertSurface(R.getRender()), nullptr, &continueButton.getRect());
				SDL_RenderCopy(R.getRender(), exitButton.convertSurface(R.getRender()), nullptr, &exitButton.getRect());

				if (IM.onButton(continueButton.getRect())) // Botó de continuar
					pause = false;
				if (IM.onButton(exitButton.getRect())) { //Botó de sortida. Permet gravar la puntuació al ranking. També, per seguritat, se resetejen aquí ses variables com el nº d'enemics, la score, ect
					//cout << score << endl;
					RK.check();
					RK.updateRank(score);

					scene = 1;
					pause = false;
					mobsCreated = 0;
					hpSet = false;
					score = 0;
					mobs.clear();
				}
				mut.unlock();
			}

			else {
				S.updatePos(IM.hyperspace()); // Controla la posició del jugador
				S.generatePlayer(); // Genera el jugador, a partir de l'SDL_Rect
				if (!hpSet) {
					S.setHp();
					hpSet = true;

				}
				if (S.getHp() <= 0) { //Control de vides del jugador
					RK.check();
					RK.updateRank(score);
					rankScene = 1;
					scene = 7;
				}

				_itoa_s(score, buffer, 10); // Se converteix la puntuació a char* per tal de ser pintada per pantalla quan el jugador jugui
				sc.setSurface(font, buffer, color); // Així obtenim una superfície printable per la puntuació


				mut.lock();

				SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip()); // Se printa al jugador, a la nau, tenint en compte la seva rotació
				SDL_RenderCopy(R.getRender(), sc.convertSurface(R.getRender()), nullptr, &sc.getRect()); // S'imprimeix per pantalla la puntuació

				for (int i = 0; i < S.getHp(); i++) {
					playerIcon.setRect(30 * i, 20, 25, 25);
					SDL_RenderCopy(R.getRender(), playerIcon.getTexture(), nullptr, &playerIcon.getRect()); // S'imprimeixen les vides actuals del jugador

				}
				counter++; // Contador que genera enemics Ovni

				if (counter % 750 - 50 * level == 0) { // **Cada nivell que augmenta, els ovnis es generen més sovint**
					Mob z;
					z.generate(UFOl, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
					z.getCoords();
					mobs.push_back(z);
				}
				maxMobs = v[2]; // Depenent de la dificultat, el nombre d'enemics variarà
				if (mobsCreated < maxMobs) { // Se generen enemics
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
				}

				lvlup(); // Es té en compte l'augment de nivell


				for (int i = 0; i < mobs.size(); i++) { // Per cada mob, actualitza la seva posició i revisa si és actiu o no
					SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
					mobs[i].mobMovement();
					/*for (int j = 0; j < 10; j++) {
						if (!ufoB[j].alive) {
							ufoB[j].alive = true;
						}
						ufoB[j].setLimits();
						ufoB[j].update(mobs[i], level);				Sistema de bales dels ovnis, quasi acabat.
						ufoB[j].setBullet();
						ufoB[j].draw();
					}*/


					mobs[i].checkCollision(bullets); // Revisa les colisions amb la nau i les bales
					if (mobs[i].boom()) { // Subdivisió dels meteorits
						Mix_PlayChannel(-1, meteor, 0); // En cas d'explotar, emet un soroll d'explosió
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
							Mix_PlayChannel(-1, death, 0); //L'ovni gros emet un soroll diferent

							m1.generate(UFOs, mobs[i].a().x + 25, mobs[i].a().y + 25);
							m2.generate(UFOs, mobs[i].a().x, mobs[i].a().y);
							m1.getCoords();
							m2.getCoords();
							mobs.push_back(m1);
							mobs.push_back(m2);
						}
						mobs.erase(mobs.begin() + i);// Borra asteroides del vector


					}
				}
				if (S.dispar()) { // Dispar de la nau
					time++;
					if (time >= 15) {
						Mix_PlayChannel(-1, blaster, 0);//Soroll de dispar

						if (!bullets[bulletCounter].alive) {
							bullets[bulletCounter].shoot(S.getPlayerRect().x, S.getPlayerRect().y);
							bulletCounter++;
							if (bulletCounter > 9)
								bulletCounter = 0;
						}
						time = 0;
					}
				}
				else {
					time = 14;
				}

				if (IM.hyperspace()) { // Hiperespai
					timeZ++;
					if (timeZ >= 800000) {
						S.hyperSpace();
						timeZ = 0;
					}
				}
				else {
					timeZ = 800000 - 1;
				}

				for (int i = 0; i < 10; i++) { // Actualització de les bales del jugador
					bullets[i].setLimits();
					bullets[i].update();
					bullets[i].setBullet();
					bullets[i].draw();
				}

				mut.unlock();
			}

			break;

		case 4:
			Game.Draw();

			if (pause) { // Si la pausa està activa, s'obre un menú i el joc s'atura fins que el jugador decideixi
				mut.lock();
				SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
				SDL_RenderCopy(R.getRender(), continueButton.convertSurface(R.getRender()), nullptr, &continueButton.getRect());
				SDL_RenderCopy(R.getRender(), exitButton.convertSurface(R.getRender()), nullptr, &exitButton.getRect());

				if (IM.onButton(continueButton.getRect())) // Botó de continuar
					pause = false;
				if (IM.onButton(exitButton.getRect())) { //Botó de sortida. Permet gravar la puntuació al ranking. També, per seguritat, se resetejen aquí ses variables com el nº d'enemics, la score, ect
														 //cout << score << endl;
					RK.check();
					RK.updateRank(score);

					scene = 1;
					pause = false;
					mobsCreated = 0;
					hpSet = false;
					score = 0;
					mobs.clear();
				}
				mut.unlock();
			}

			else {
				S.updatePos(IM.hyperspace()); // Controla la posició del jugador
				S.generatePlayer(); // Genera el jugador, a partir de l'SDL_Rect
				if (!hpSet) {
					S.setHp();
					hpSet = true;

				}
				if (S.getHp() <= 0) { //Control de vides del jugador
					RK.check();
					RK.updateRank(score);
					rankScene = 2;
					scene = 7;
				}

				_itoa_s(score, buffer, 10); // Se converteix la puntuació a char* per tal de ser pintada per pantalla quan el jugador jugui
				sc.setSurface(font, buffer, color); // Així obtenim una superfície printable per la puntuació


				mut.lock();

				SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip()); // Se printa al jugador, a la nau, tenint en compte la seva rotació
				SDL_RenderCopy(R.getRender(), sc.convertSurface(R.getRender()), nullptr, &sc.getRect()); // S'imprimeix per pantalla la puntuació

				for (int i = 0; i < S.getHp(); i++) {
					playerIcon.setRect(30 * i, 20, 25, 25);
					SDL_RenderCopy(R.getRender(), playerIcon.getTexture(), nullptr, &playerIcon.getRect()); // S'imprimeixen les vides actuals del jugador

				}
				counter++; // Contador que genera enemics Ovni

				if (counter % 750 - 50 * level == 0) { // **Cada nivell que augmenta, els ovnis es generen més sovint**
					Mob z;
					z.generate(UFOl, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
					z.getCoords();
					mobs.push_back(z);
				}
				maxMobs = v[6]; // Depenent de la dificultat, el nombre d'enemics variarà
				if (mobsCreated < maxMobs) { // Se generen enemics
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
				}

				lvlup(); // Es té en compte l'augment de nivell


				for (int i = 0; i < mobs.size(); i++) { // Per cada mob, actualitza la seva posició i revisa si és actiu o no
					SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
					mobs[i].mobMovement();
					/*for (int j = 0; j < 10; j++) {
					if (!ufoB[j].alive) {
					ufoB[j].alive = true;
					}
					ufoB[j].setLimits();
					ufoB[j].update(mobs[i], level);				Sistema de bales dels ovnis, quasi acabat.
					ufoB[j].setBullet();
					ufoB[j].draw();
					}*/


					mobs[i].checkCollision(bullets); // Revisa les colisions amb la nau i les bales
					if (mobs[i].boom()) { // Subdivisió dels meteorits
						Mix_PlayChannel(-1, meteor, 0); // En cas d'explotar, emet un soroll d'explosió
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
							Mix_PlayChannel(-1, death, 0);//L'ovni gros emet un soroll diferent

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
				if (S.dispar()) { // Dispar de la nau
					time++;
					if (time >= 15) {
						Mix_PlayChannel(-1, blaster, 0); //Soroll de dispar

						if (!bullets[bulletCounter].alive) {
							bullets[bulletCounter].shoot(S.getPlayerRect().x, S.getPlayerRect().y);
							bulletCounter++;
							if (bulletCounter > 9)
								bulletCounter = 0;
						}
						time = 0;
					}
				}
				else {
					time = 14;
				}

				if (IM.hyperspace()) { // Hiperespai
					timeZ++;
					if (timeZ >= 800000) {
						S.hyperSpace();
						timeZ = 0;
					}
				}
				else {
					timeZ = 800000 - 1;
				}

				for (int i = 0; i < 10; i++) { // Actualització de les bales del jugador
					bullets[i].setLimits();
					bullets[i].update();
					bullets[i].setBullet();
					bullets[i].draw();
				}

				mut.unlock();
			}
			break;
		case 5:
			Game.Draw();

			if (pause) { // Si la pausa està activa, s'obre un menú i el joc s'atura fins que el jugador decideixi
				mut.lock();
				SDL_RenderCopy(R.getRender(), pauseMessage.convertSurface(R.getRender()), nullptr, &pauseMessage.getRect());
				SDL_RenderCopy(R.getRender(), continueButton.convertSurface(R.getRender()), nullptr, &continueButton.getRect());
				SDL_RenderCopy(R.getRender(), exitButton.convertSurface(R.getRender()), nullptr, &exitButton.getRect());

				if (IM.onButton(continueButton.getRect())) // Botó de continuar
					pause = false;
				if (IM.onButton(exitButton.getRect())) { //Botó de sortida. Permet gravar la puntuació al ranking. També, per seguritat, se resetejen aquí ses variables com el nº d'enemics, la score, ect
														 //cout << score << endl;
					RK.check();
					RK.updateRank(score);

					scene = 1;
					pause = false;
					mobsCreated = 0;
					hpSet = false;
					score = 0;
					mobs.clear();
				}
				mut.unlock();
			}

			else {
				S.updatePos(IM.hyperspace()); // Controla la posició del jugador
				S.generatePlayer(); // Genera el jugador, a partir de l'SDL_Rect
				if (!hpSet) {
					S.setHp();
					hpSet = true;

				}
				if (S.getHp() <= 0) { //Control de vides del jugador
					RK.check();
					RK.updateRank(score);
					rankScene = 3;
					scene = 7;
				}

				_itoa_s(score, buffer, 10); // Se converteix la puntuació a char* per tal de ser pintada per pantalla quan el jugador jugui
				sc.setSurface(font, buffer, color); // Així obtenim una superfície printable per la puntuació


				mut.lock();

				SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip()); // Se printa al jugador, a la nau, tenint en compte la seva rotació
				SDL_RenderCopy(R.getRender(), sc.convertSurface(R.getRender()), nullptr, &sc.getRect()); // S'imprimeix per pantalla la puntuació

				for (int i = 0; i < S.getHp(); i++) {
					playerIcon.setRect(30 * i, 20, 25, 25);
					SDL_RenderCopy(R.getRender(), playerIcon.getTexture(), nullptr, &playerIcon.getRect()); // S'imprimeixen les vides actuals del jugador

				}
				counter++; // Contador que genera enemics Ovni

				if (counter % 750 - 50 * level == 0) { // **Cada nivell que augmenta, els ovnis es generen més sovint**
					Mob z;
					z.generate(UFOl, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
					z.getCoords();
					mobs.push_back(z);
				}
				maxMobs = v[10]; // Depenent de la dificultat, el nombre d'enemics variarà
				if (mobsCreated < maxMobs) { // Se generen enemics
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
				}

				lvlup(); // Es té en compte l'augment de nivell


				for (int i = 0; i < mobs.size(); i++) { // Per cada mob, actualitza la seva posició i revisa si és actiu o no
					SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());
					mobs[i].mobMovement();
					/*for (int j = 0; j < 10; j++) {
					if (!ufoB[j].alive) {
					ufoB[j].alive = true;
					}
					ufoB[j].setLimits();
					ufoB[j].update(mobs[i], level);				Sistema de bales dels ovnis, quasi acabat.
					ufoB[j].setBullet();
					ufoB[j].draw();
					}*/


					mobs[i].checkCollision(bullets); // Revisa les colisions amb la nau i les bales
					if (mobs[i].boom()) { // Subdivisió dels meteorits
						Mix_PlayChannel(-1, meteor, 0); // En cas d'explotar, emet un soroll d'explosió
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
							Mix_PlayChannel(-1, death, 0);//L'ovni gros emet un soroll diferent

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
				if (S.dispar()) { // Dispar de la nau
					time++;
					if (time >= 15) {
						Mix_PlayChannel(-1, blaster, 0); // Soroll de dispar

						if (!bullets[bulletCounter].alive) {
							bullets[bulletCounter].shoot(S.getPlayerRect().x, S.getPlayerRect().y);
							bulletCounter++;
							if (bulletCounter > 9)
								bulletCounter = 0;
						}
						time = 0;
					}
				}
				else {
					time = 14;
				}

				if (IM.hyperspace()) { // Hiperespai
					timeZ++;
					if (timeZ >= 800000) {
						S.hyperSpace();
						timeZ = 0;
					}
				}
				else {
					timeZ = 800000 - 1;
				}

				for (int i = 0; i < 10; i++) { // Actualització de les bales del jugador
					bullets[i].setLimits();
					bullets[i].update();
					bullets[i].setBullet();
					bullets[i].draw();
				}

				mut.unlock();
			}
			break;

		case 6: //Escena de ranking
			s_Menu.onEntry("../../res/bgmenu.jpg");
			s_Menu.Draw();
			SDL_RenderCopy(R.getRender(), back.convertSurface(R.getRender()), nullptr, &back.getRect());
			if (IM.onButton(back.getRect())) {
				scene = 1;
				ranking = false;
			}
			if (!ranking) {
				ranking = true;
				scene = 2;
			}

			else
				switch (rankScene) {
				case 1:
					RK.print(font, color, rankScene);
					break;
				case 2:
					RK.print(font, color, rankScene);
					break;
				case 3:
					RK.print(font, color, rankScene);
					break;
				}

			SDL_RenderCopy(R.getRender(), back.convertSurface(R.getRender()), nullptr, &back.getRect());
			break;

		case 7: //Escena de Game Over
			hpSet = false;
			s_Menu.onEntry("../../res/bgmenu.jpg");
			s_Menu.Draw();

			temp++;

			if (temp <= 218) { // Es mostra el ranking al jugador i després d'un interval de temps, el du al menú principal
				temp2++;
				SDL_RenderCopy(R.getRender(), game.convertSurface(R.getRender()), nullptr, &game.getRect());
				SDL_RenderCopy(R.getRender(), over.convertSurface(R.getRender()), nullptr, &over.getRect());

				switch (rankScene) {
				case 1:
					RK.print(font, color, rankScene);
					break;
				case 2:
					RK.print(font, color, rankScene);
					break;
				case 3:
					RK.print(font, color, rankScene);
					break;
				}
				if (temp2 == 218) {
					scene = 1;

				}
			}
			break;
		}
		IM.Update();
		SDL_RenderPresent(R.getRender());
	}
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void GameEngine::lvlup() { // Funció que augmenta la dificultat del joc a partir de les dades dins l'xml
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

void GameEngine::generateMobs() { // Generació d'enemics
	if (mobsCreated < maxMobs) {
		Mob x;
		x.generate(LARGE, rand() % -99 + (-100) + (rand() % WIDTH + 100 + 99), rand() % -99 + (-100));
		x.getCoords();
		mobs.push_back(x);
		mobsCreated++;

	}
}
void GameEngine::loop(Sprite p, Sprite c, Sprite e, char* b, Sprite sk, Sprite pI, vector <Bullet2> bullts) { // Funció que anava a acurçar
	if (pause) {
		mut.lock();
		SDL_RenderCopy(R.getRender(), p.convertSurface(R.getRender()), nullptr, &p.getRect());
		SDL_RenderCopy(R.getRender(), c.convertSurface(R.getRender()), nullptr, &c.getRect());
		SDL_RenderCopy(R.getRender(), e.convertSurface(R.getRender()), nullptr, &e.getRect());

		if (IM.onButton(c.getRect()))
			pause = false;
		if (IM.onButton(e.getRect())) {
			//cout << score << endl;
			RK.check();
			RK.updateRank(score);

			scene = 1;
			pause = false;
			mobsCreated = 0;
			hpSet = false;
			score = 0;
			mobs.clear();
		}
		mut.unlock();
	}

	else {

		S.updatePos(IM.hyperspace());
		S.generatePlayer();
		if (!hpSet) {
			S.setHp();
			hpSet = true;

		}
		if (S.getHp() <= 0) {
			RK.check();
			RK.updateRank(score);
			rankScene = 1;
			scene = 7;
		}

		//cout << bulletCounter << endl;

	//	_itoa_s(score, b, 10);									debido a esta línia, el código no ha podido optimizarse. Se ha tenido que repetir el mismo código 3 veces
		sk.setSurface(font, b, color);						 // tambien se ha usado stringstream y la función copy, que permite rellenar un char * a partir de un string, pero daba un error que necessitaba modificar el precompilador, haciendo el programa inestable.


		mut.lock();

		SDL_RenderCopyEx(R.getRender(), S.getPlayer().getTexture(), nullptr, &S.getPlayer().getRect(), S.getAngle(), &S.getPos(), S.getFlip());
		SDL_RenderCopy(R.getRender(), sk.convertSurface(R.getRender()), nullptr, &sk.getRect());

		for (int i = 0; i < S.getHp(); i++) {
			pI.setRect(30 * i, 20, 25, 25);
			SDL_RenderCopy(R.getRender(), pI.getTexture(), nullptr, &pI.getRect());

		}
		counter++;

		if (counter % 750 - 50 * level == 0) { // everytime a level increases, ufos are spawned more often
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
		}

		lvlup();


		for (int i = 0; i < mobs.size(); i++) {
			SDL_RenderCopy(R.getRender(), mobs[i].getSprite().getTexture(), nullptr, &mobs[i].a());

			mobs[i].mobMovement();
			mobs[i].checkCollision(bullts);
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
		if (S.dispar()) {
			time++;
			if (time >= 15) {
				if (!bullts[bulletCounter].alive) {
					bullts[bulletCounter].shoot(S.getPlayerRect().x, S.getPlayerRect().y);
					bulletCounter++;
					if (bulletCounter > 9)
						bulletCounter = 0;
				}
				time = 0;
			}


		}
		else {
			time = 14;
		}

		if (IM.hyperspace()) {
			timeZ++;
			if (timeZ >= 800000) {
				S.hyperSpace();
				timeZ = 0;
			}
		}
		else {
			timeZ = 799;
		}

		for (int i = 0; i < 10; i++) {
			bullts[i].setLimits();
			bullts[i].update();
			bullts[i].setBullet();
			bullts[i].draw();

		}
		//if (S.getHp <= 0) {
		//anar a ranking amb un icono de game over. despres de uns segons? || surt un icono de game over i un q si li clickes vas a ranking
		//}

		mut.unlock();
	}


}



