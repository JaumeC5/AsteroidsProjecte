#pragma once

#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include <sstream> // faltava aixo paio
#include <stdlib.h>

using namespace rapidxml;
using namespace std;


vector<int> getProps() // funció que agafa informació de configuració de l'arxiu xml i l'agrupa a un vector
{

	int temp;
	vector <int> props; // 0-3 easy // 4-7 medium // 8-11 hard
						//ORDER: HPmultiplier, enemySpeed, numEnemies, enemyIncrement 

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
		//cout << attr->value() << endl;

		for (xml_node <> *n = node->first_node(); n; n = n->next_sibling()) {
			//cout << n->name() << ": " << n->value() << endl;
			temp = atoi(n->value());
			props.push_back(temp);


		}
		//cout << endl;


	}
	/*for (int i = 0; i < props.size(); i++) {
		cout << props[i] << " ";
	}*/
	return props;
}