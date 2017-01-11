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
		//string name;


	};
	Score sk[4];
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
	void print(TTF_Font *f, SDL_Color color);
};
void Ranking::setRank() {
	ifstream fsalida("ranking.dat", ios::out | ios::binary);
	if (!initiated) {
		for (int i = 0; i < 4; i++) {
			//sk[i].score = 0;
			cout << "done" << endl;
			fsalida.read(reinterpret_cast<char *>(&sk[i].score), sizeof(sk[i].score));
		}
		initiated = true;
	}

	fsalida.close();

}

void Ranking::check() {
	//char* temp;
	ifstream fentrada("ranking.dat", ios::out | ios::binary);
	for (int i = 0; i < 4; i++) {
		fentrada.read(reinterpret_cast<char *>(&sk[i].score), sizeof(sk[i].score));
		//cout << sk[i].score << endl;

	}
	//getchar();
}

void Ranking::updateRank(int score) {
	int swap;
	ofstream fsalida("ranking.dat", ios::out | ios::binary);

	cout << "detectat score :" << score << endl;

	if (sk[0].score < score)
		sk[0].score = score;
	else if (sk[0].score > score && sk[1].score < score)
		sk[1].score = score;
	else if (sk[1].score > score && sk[2].score < score)
		sk[2].score = score;
	else if (sk[2].score > score && sk[3].score < score)
		sk[3].score = score;

	for (int c = 0; c < 4; c++)
	{
		for (int d = 0; d < 4 - 1; d++)
		{
			if (sk[d].score > sk[d + 1].score) // este bucle ordena el score
			{
				swap = sk[d].score;
				sk[d].score = sk[d + 1].score;
				sk[d + 1].score = swap;
			}
		}
	}

	for (int i = 0; i< 4; i++)
		fsalida.write(reinterpret_cast<char *>(&sk[i].score), sizeof(sk[i].score));

}



void Ranking::print(TTF_Font *f, SDL_Color color) {
	Sprite sp;
	char buffer[150];

	for (int i = 0; i < 4; i++) {
		_itoa_s(sk[i].score, buffer, 10);
		sp.setRect(WIDTH / 2 - 40, 300 - (75 * i), 50, 40);
		sp.setSurface(f, buffer, color);
		SDL_RenderCopy(R.getRender(), sp.convertSurface(R.getRender()), nullptr, &sp.getRect());
	}
}