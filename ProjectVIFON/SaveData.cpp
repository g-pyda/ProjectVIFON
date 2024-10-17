#include "SaveData.h"

// default constructor
SaveData::SaveData() {
	// getting the data from the save file
	std::ifstream records;
	records.open("../Saves/save_0.txt");
	std::vector <std::string> record_lines;
	std::string temp;
	if (records.is_open()) {
		while (std::getline(records, temp)) {
			record_lines.push_back(temp);  // Add each line to the vector
		}
		records.close();
	}
	else {
		std::cerr << "Unable to open file." << std::endl;
	}

	enums::map section = enums::map(-1);
	bool rendD = false, mapD = false, mapSize = false, objectsD = false, sect_end = true;

	// variables to store temporarily the components of the configuration
	unsigned int TEMPwidth = 0; 
	unsigned int TEMPheight = 0; 
	std::vector <int> TEMPTEXscheme;
	std::vector <WorldObject> TEMPMovableScheme;
	sf::Vector2f TEMPplayerCoords;

	for (int i = 0; i < record_lines.size(); i++) {
		// starting the rendering the section of the file 
		// (specifies which map is rendered)
		if (record_lines[i][0] == '/' && record_lines[i][2] == '/' && sect_end) {
			sect_end = !sect_end;
			section = enums::map(int(record_lines[i][1] - '0'));
			std::cout << "Rendering the map " << int(section) << std::endl;
			continue;
		}
		// ending the rendering the section of the file 
		else if (record_lines[i][0] == '/' && record_lines[i][2] == '/' && !sect_end) {
			sect_end = !sect_end;
			int texSize = TEMPTEXscheme.size();
			int TEMPTEXscheme2[MAXwidth * MAXheight];
			for (int j = 0; j < TEMPTEXscheme.size(); j++) {
				std::cout << TEMPTEXscheme[j] << ", ";
				if ((j+1)%TEMPwidth==0)
					std::cout << std::endl;
				TEMPTEXscheme2[j] = TEMPTEXscheme[j];
			}
			switch (section) {
				case enums::dorm:
					Config TEMPconfig(TEMPwidth, TEMPheight, "../Graphics/Background/dormBackgroundTEX.png", "../Graphics/Movable/dormFurnitureTEX.png", TEMPTEXscheme2, TEMPMovableScheme, TEMPplayerCoords);
					dormConfig = TEMPconfig;
					break;
				//case int(outdoor):
					//Config outdoorConfig;
				//case int(uni):
					//Config uniConfig;
				//case int(hipermarket):
					//Config hipermarketConfig;
			}
			continue;
		}
		// specifying which component of configuration is rendered -> rendering coordinates
		else if (record_lines[i] == "rend") {
			rendD = true;
			continue;
		}
		// obtaining the data -> rendering coordinates
		else if (rendD) {
			int sep = record_lines[i].find("x");
			std::string temp = "";
			for (int j = 1; j < sep; j++)
				temp += record_lines[i][j];
			std::cout << "Coords: " << temp;
			TEMPplayerCoords.x = stoi(temp);
			temp.erase();
			for (int j = sep + 1; j < record_lines[i].size() - 1; j++)
				temp += record_lines[i][j]; 
			std::cout << " " << temp << std::endl;
			TEMPplayerCoords.y = stoi(temp);
			rendD = false;
			continue;
		}
		// specifying which component of configuration is rendered -> map scheme / map size
		else if (record_lines[i] == "map") {
			mapD = mapSize = true;
			continue;
		}
		// obtaining the data -> map size
		else if (mapSize) {
			int sep = record_lines[i].find("x");
			std::string temp = "";
			for (int j = 1; j < sep; j++)
				temp += record_lines[i][j];
			std::cout << "Map size: " << temp;
			TEMPwidth = stoi(temp);
			temp.erase();
			for (int j = sep + 1; j < record_lines[i].size() - 2; j++)
				temp += record_lines[i][j];
			std::cout << " " << temp << std::endl;
			TEMPheight = stoi(temp);
			mapSize = false;
			continue;
		}
		// obtaining the data -> map scheme
		else if (mapD) {
			if (record_lines[i] == "}") { // end of map scheme
				if (TEMPTEXscheme.size() == TEMPheight * TEMPwidth)
					std::cout << "Map rendered correctly!" << std::endl;
				mapD = false;
				continue;
			}
			int sep1 = -1, sep2;
			for (int t = 0; t < TEMPwidth; t++) {
				sep2 = record_lines[i].find(",",sep1 + 1);
				std::cout << "/" << sep1 << "/" << sep2 << "/";
				std::string temp = "";
				for (int j = sep1 + 1; j < sep2; j++)
					temp += record_lines[i][j];
				std::cout << temp << ", ";
				TEMPTEXscheme.push_back(stoi(temp));
				temp.erase();
				sep1 = sep2;
			}
			std::cout << std::endl;
			continue;
		}
		// specifying which component of configuration is rendered -> objects
		else if (record_lines[i] == "objects{") {
			objectsD = true;
			continue;
		}
		// obtaining the data -> objects
		else if (objectsD) {
			if (record_lines[i] == "}") { // end of objects list
				objectsD = false;
				continue;
			}
			int sep1 = 0, sep2;
			int name, corX, corY, rot;

			// getting the name
			sep2 = record_lines[i].find(",", sep1 + 1);
			std::string temp = "";
			for (int j = sep1 + 1; j < sep2; j++)
				temp += record_lines[i][j];
			std::cout << temp << ", ";
			name = stoi(temp);
			temp.erase();
			sep1 = sep2;

			// getting the corX
			sep2 = record_lines[i].find(",", sep1 + 1);
			temp = "";
			for (int j = sep1 + 1; j < sep2; j++)
				temp += record_lines[i][j];
			std::cout << temp << ", ";
			corX = stoi(temp);
			temp.erase();
			sep1 = sep2;

			// getting the corY
			sep2 = record_lines[i].find(",", sep1 + 1);
			temp = "";
			for (int j = sep1 + 1; j < sep2; j++)
				temp += record_lines[i][j];
			std::cout << temp << ", ";
			corY = stoi(temp);
			temp.erase();
			sep1 = sep2;

			// getting the rot
			sep2 = record_lines[i].find("}", sep1 + 1);
			temp = "";
			for (int j = sep1 + 1; j < sep2; j++)
				temp += record_lines[i][j];
			std::cout << temp << std::endl;
			rot = stoi(temp);
			temp.erase();
			
			//adding the new object to the vector
			TEMPMovableScheme.push_back(WorldObject(enums::movableObject(name), sf::Vector2f(corX*defTileSize, corY*defTileSize), rot));
			std::cout << "Object rendered correctly" << std::endl;
			continue;
		}

	}

}

SaveData::SaveData(std::string fileName) {
	// opening the file with the save 
	std::ifstream f(fileName);
	json js;
	f >> js;

	// reading the player data
	
	json plNeeds = js["PLAYERCONFIG"]["needs"];
	int needs[8] = {
		plNeeds["physical health"], plNeeds["mental health"], plNeeds["hunger"], plNeeds["thirst"],
		plNeeds["toilet"], plNeeds["hygene"], plNeeds["energy"], plNeeds["entertainment"]
	};

	std::vector <Food> FoodArray;
	auto plFood = js["PLAYERCONFIG"]["owned food"];
	for (auto& foodie : plFood) {
		FoodArray.push_back(Food(enums::str_food[plFood["name"]],plFood["name"], plFood["amount"]));
	}
	

	Player tempPlayer(js["PLAYERCONFIG"]["nick"], enums::fieldOfStudy(js["PLAYERCONFIG"]["field of study"]), js["PLAYERCONFIG"]["money"], needs,
		js["PLAYERCONFIG"]["accomodation"]["days untill fee"], enums::accomodation(js["PLAYERCONFIG"]["accomodation"]["type"]), FoodArray);
	
	// reading the dorm data
}

// getter for the dorm map configuration
Config SaveData::getDormConfig() const {
	return dormConfig;
}

//// getter for the uni map configuration
//Config SaveData::getUniConfig() const {
//	return uniConfig;
//}
//
//// getter for the hipermarket map configuration
//Config SaveData::getHipermarketConfig() const {
//	return hipermarketConfig;
//}
//
//// getter for the outdoor map configuration
//Config SaveData::getOutdoorConfig() const {
//	return outdoorConfig;
//}


