#include "Header.h"
#include "rapidxml.hpp"
#include <fstream>
#include <vector>

/*
using namespace rapidxml;
using namespace std;

int main(int, char*[]) {

	rapidxml::xml_document<> doc;
	std::ifstream config("config.xml");
		std::stringstream buffer; // da error aquí, no he encontrado el fallo
	buffer << config.rdbuf();
	config.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	
	for (xml_node<> * config_node = config_node->first_node("DConfig"); config_node; config_node = config_node->next_sibling())
	{
		
		printf(" %s  %s %d \n",
			config_node->first_attribute("name")->value(),
			config_node->first_attribute("description")->value(),
			config_node->first_attribute("valor")->value());
	}

		if (state == 1)
			mainMenu();

		if (state == 2)
			selection();

	

		if (state == 3 || state == 4 || state == 5)
			game();

		return 0;
	}
	*/