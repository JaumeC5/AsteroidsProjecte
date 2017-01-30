#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include "string"
#include <sstream>
#include <vector>
#include "SDL_ttf.h"
#include "Renderer.hh"
using namespace std;


#define RK Ranking::Instance()


class Ranking {
	struct Score {
		int score;
		char* name;
	};
	Score skE[10];
	Score skM[10];
	Score skH[10];

	bool initiated = false;
	bool loop = true;
public:

	inline static Ranking &Instance() {
		static Ranking ra;
		return ra;
	}
	void setRank();
	void updateRank(int);
	void check();
	void print(TTF_Font *f, SDL_Color color, int);
	void getPlayername();
};
void Ranking::setRank() {
	ifstream fsalida("rankingE.dat", ios::out | ios::binary);
	ifstream fsalida2("rankingM.dat", ios::out | ios::binary);
	ifstream fsalida3("rankingH.dat", ios::out | ios::binary);


	if (!initiated) {
		for (int i = 0; i < 10; i++) {
			fsalida.read(reinterpret_cast<char *>(&skE[i].score), sizeof(skE[i].score));
			fsalida2.read(reinterpret_cast<char *>(&skM[i].score), sizeof(skM[i].score));
			fsalida3.read(reinterpret_cast<char *>(&skH[i].score), sizeof(skH[i].score));
		}
		initiated = true;
	}

	fsalida.close();
}

void Ranking::check() {
	ifstream fentrada("rankingE.dat", ios::out | ios::binary);
	ifstream fentrada2("rankingM.dat", ios::out | ios::binary);
	ifstream fentrada3("rankingH.dat", ios::out | ios::binary);

	for (int i = 0; i < 10; i++) {
		
		fentrada.read(reinterpret_cast<char *>(&skE[i].score), sizeof(skE[i].score));
		fentrada2.read(reinterpret_cast<char *>(&skM[i].score), sizeof(skM[i].score));
		fentrada3.read(reinterpret_cast<char *>(&skH[i].score), sizeof(skH[i].score));

	}
}

void Ranking::updateRank(int score) {
	int swap;
	ofstream fsalida("rankingE.dat", ios::out | ios::binary);
	ofstream fsalida2("rankingM.dat", ios::out | ios::binary);
	ofstream fsalida3("rankingH.dat", ios::out | ios::binary);
	cout << "detectat score :" << score << endl;
	switch (scene) {
	case 3: // Hem de disculpar-nos per aquest fragment de codi, degut a un error de github, va perdre's l'algoritme d'ordenament del ranking, i hem hagut d'improvisar un nou algoritme una mica caòtic per a la vista.
		if (skE[0].score < score) //Depenent de la dificultat, s'actualitza un document binari o un altre
			skE[0].score = score;
		else if (skE[0].score > score && skE[1].score < score)
			skE[1].score = score;
		else if (skE[1].score > score && skE[2].score < score)
			skE[2].score = score;
		else if (skE[2].score > score && skE[3].score < score)
			skE[3].score = score;
		else if (skE[3].score > score && skE[4].score < score)
			skE[4].score = score;
		else if (skE[4].score > score && skE[5].score < score)
			skE[5].score = score;
		else if (skE[5].score > score && skE[6].score < score)
			skE[6].score = score;
		else if (skE[6].score > score && skE[7].score < score)
			skE[7].score = score;
		else if (skE[7].score > score && skE[8].score < score)
			skE[8].score = score;
		else if (skE[8].score > score && skE[9].score < score)
			skE[9].score = score;

		for (int c = 0; c < 10; c++) // S'ordenen les puntuacions
		{
			for (int d = 0; d < 10 - 1; d++)
			{
				if (skE[d].score > skE[d + 1].score) 
				{
					swap = skE[d].score;
					skE[d].score = skE[d + 1].score;
					skE[d + 1].score = swap;
				}
			}
		}
		for (int i = 0; i < 10; i++)
			fsalida.write(reinterpret_cast<char *>(&skE[i].score), sizeof(skE[i].score));
		break;

	case 4:
		if (skM[0].score < score)
			skM[0].score = score;
		else if (skM[0].score > score && skM[1].score < score)
			skM[1].score = score;
		else if (skM[1].score > score && skM[2].score < score)
			skM[2].score = score;
		else if (skM[2].score > score && skM[3].score < score)
			skM[3].score = score;
		else if (skM[3].score > score && skM[4].score < score)
			skM[4].score = score;
		else if (skM[4].score > score && skM[5].score < score)
			skM[5].score = score;
		else if (skM[5].score > score && skM[6].score < score)
			skM[6].score = score;
		else if (skM[6].score > score && skM[7].score < score)
			skM[7].score = score;
		else if (skM[7].score > score && skM[8].score < score)
			skM[8].score = score;
		else if (skM[8].score > score && skM[9].score < score)
			skM[9].score = score;


		for (int c = 0; c < 10; c++)
		{
			for (int d = 0; d < 10 - 1; d++)
			{
				if (skM[d].score > skM[d + 1].score)
				{
					swap = skM[d].score;
					skM[d].score = skM[d + 1].score;
					skM[d + 1].score = swap;
				}
			}
		}

		for (int i = 0; i < 10; i++)
			fsalida2.write(reinterpret_cast<char *>(&skM[i].score), sizeof(skM[i].score));
		break;

	case 5:
		if (skH[0].score < score)
			skH[0].score = score;
		else if (skH[0].score > score && skH[1].score < score)
			skH[1].score = score;
		else if (skH[1].score > score && skH[2].score < score)
			skH[2].score = score;
		else if (skH[2].score > score && skH[3].score < score)
			skH[3].score = score;
		else if (skH[3].score > score && skH[4].score < score)
			skH[4].score = score;
		else if (skH[4].score > score && skH[5].score < score)
			skH[5].score = score;
		else if (skH[5].score > score && skH[6].score < score)
			skH[6].score = score;
		else if (skH[6].score > score && skH[7].score < score)
			skH[7].score = score;
		else if (skH[7].score > score && skH[8].score < score)
			skH[8].score = score;
		else if (skH[8].score > score && skH[9].score < score)
			skH[9].score = score;


		for (int c = 0; c < 10; c++)
		{
			for (int d = 0; d < 10 - 1; d++)
			{
				if (skH[d].score > skH[d + 1].score)
				{
					swap = skH[d].score;
					skH[d].score = skH[d + 1].score;
					skH[d + 1].score = swap;
				}
			}
		}
		for (int i = 0; i < 10; i++)
			fsalida3.write(reinterpret_cast<char *>(&skH[i].score), sizeof(skH[i].score));

		break;
	}


}



void Ranking::print(TTF_Font *f, SDL_Color color, int sc) { // Permet imprimir per pantalla les puntuacions
	Sprite sp;
	char buffer[150];
	switch (sc) {

	case 1:
		for (int i = 0; i < 10; i++) {
			_itoa_s(skE[i].score, buffer, 10);
			sp.setRect(WIDTH / 2 - 40, HEIGHT - 50 - (45 * i), 50, 40);
			sp.setSurface(f, buffer, color);
			SDL_RenderCopy(R.getRender(), sp.convertSurface(R.getRender()), nullptr, &sp.getRect());
		}
		break;
	case 2:

		for (int i = 0; i < 10; i++) {
			_itoa_s(skM[i].score, buffer, 10);
			sp.setRect(WIDTH / 2 - 40, HEIGHT - 50 - (45 * i), 50, 40);
			sp.setSurface(f, buffer, color);
			SDL_RenderCopy(R.getRender(), sp.convertSurface(R.getRender()), nullptr, &sp.getRect());
		}
		break;
	case 3:

		for (int i = 0; i < 10; i++) {
			_itoa_s(skH[i].score, buffer, 10);
			sp.setRect(WIDTH / 2 - 40, HEIGHT - 50 - (45 * i), 50, 40);
			sp.setSurface(f, buffer, color);
			SDL_RenderCopy(R.getRender(), sp.convertSurface(R.getRender()), nullptr, &sp.getRect());
		}

		break;
	}

}

void Ranking::getPlayername() { // Un altre intent per poder fer strings en binari
	/*	cout << "//////////////////////////" << endl;
		cout << "//INSERT YOUR NAME BELOW//" << endl;
		cout << "//////////////////////////" << endl;

		cin >> playerName;
		playerName += ": ";

		ofstream fsalida("rankingE.dat", ios::out | ios::binary);
		ofstream fsalida2("rankingM.dat", ios::out | ios::binary);
		ofstream fsalida3("rankingH.dat", ios::out | ios::binary);

		switch (scene) {
		case 3:
			fsalida.write();
			break;
		case 4:
			fsalida2.write(reinterpret_cast<char *>(&playerName), sizeof(playerName));
			break;
		case 5:
			fsalida3.write(reinterpret_cast<char *>(&playerName), sizeof(playerName));
			break;

		}*/


}