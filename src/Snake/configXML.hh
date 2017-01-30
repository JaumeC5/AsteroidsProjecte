#pragma once

#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace rapidxml;
using namespace std;


vector<int> getProps() // Retorna les dades de l'xml en forma de vector
{

	int temp;
	vector <int> props; // 0-3 easy // 4-7 medium // 8-11 hard					
	xml_document <>doc; //ORDRE: HPmultiplier, enemySpeed, numEnemies, enemyIncrement 
	ifstream file("config.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);
	xml_node<> *root = doc.first_node();

	for (xml_node <> *node = root->first_node("Level"); node; node = node->next_sibling()) {
		xml_attribute <> *attr = node->first_attribute();
		for (xml_node <> *n = node->first_node(); n; n = n->next_sibling()) {
			temp = atoi(n->value());
			props.push_back(temp);
		}
	}
	return props;
}