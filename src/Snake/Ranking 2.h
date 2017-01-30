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
#define RK2 Ranking2::Instance()


// Hem intentat fer strings en binari, pero no ha estat possible.

class Ranking2 {
	struct Score {
		int score = 0;
		string name = "";
	};
	Score skE[10];
	Score skM[10];
	Score skH[10];
	bool initiated = false;
	bool loop = true;
public:

	inline static Ranking2 &Instance() {
		static Ranking2 ra;
		return ra;
	}
	void setRank();
	void updateRank(int, string);
	void check();
	void print(TTF_Font *f, SDL_Color color, int);
	void getPlayername();
};



void Ranking2::setRank() {
	ofstream savefile("rankingE.bin", std::ios::binary);
	ofstream savefile2("rankingM.bin", std::ios::binary);
	ofstream savefile3("rankingHbin", std::ios::binary);
	if (!initiated) {
		if (savefile.good()) {
			for (int i = 0; i < 10; i++) {
				savefile.write(skE[i].name.c_str(), skE[i].name.size()); // Write string to binary file
				savefile.write("\0", sizeof(char)); // Add null end string for easier reading
				savefile.write(reinterpret_cast<char*>(&skE[i].score), sizeof(skE[i].score)); // Write int to binary file

				savefile2.write(skM[i].name.c_str(), skM[i].name.size()); // Write string to binary file
				savefile2.write("\0", sizeof(char)); // Add null end string for easier reading
				savefile2.write(reinterpret_cast<char*>(&skM[i].score), sizeof(skM[i].score)); // Write int to binary file

				savefile3.write(skH[i].name.c_str(), skH[i].name.size()); // Write string to binary file
				savefile3.write("\0", sizeof(char)); // Add null end string for easier reading
				savefile3.write(reinterpret_cast<char*>(&skH[i].score), sizeof(skH[i].score)); // Write int to binary file
			}


		}
		initiated = true;
	}
	savefile.close();
	savefile2.close();
	savefile3.close();
}

void Ranking2::updateRank(int score, string name) {

	Score temp;
	temp.name = name;
	temp.score = score;
	for (int i = 0; i < 10; i++) {
		if (skE[i].score <= temp.score) {

			for (int j = 10 - 1; j >= i; j--) {
				skE[j] = skE[j - 1];
			}
		}
	}

}