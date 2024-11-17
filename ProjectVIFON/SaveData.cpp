#include "SaveData.h"


SaveData::SaveData(std::string fileName) {
	// opening the file with the save 
	std::ifstream f(fileName);
	json js;
	f >> js;
	//
	// 
	// reading the player data
	//
	//
	json plNeeds = js["PLAYERCONFIG"]["needs"];
	int needs[8] = {
		plNeeds["physical health"], plNeeds["mental health"], plNeeds["hunger"], plNeeds["thirst"],
		plNeeds["toilet"], plNeeds["hygene"], plNeeds["energy"], plNeeds["entertainment"]
	};

	std::vector <Food> FoodArray;
	const json& foods = js["PLAYERCONFIG"]["owned food"];
	for (const auto& foodie : foods) {
		std::string name_str = enums::str_food[foodie["name"]];
		int name = foodie["name"];
		int amount = foodie["amount"];
		int exp_date = foodie["expiration days"];
		FoodArray.push_back(Food(name_str, (enums::food)name,
			amount, exp_date));
	}

	int x = js["PLAYERCONFIG"]["coordinates"]["x"];
	int y = js["PLAYERCONFIG"]["coordinates"]["y"];

	this->currentPlayer = Player(js["PLAYERCONFIG"]["nick"], enums::fieldOfStudy(js["PLAYERCONFIG"]["field of study"]), js["PLAYERCONFIG"]["money"], needs, js["PLAYERCONFIG"]["accomodation"]["days untill fee"], 
		enums::accomodation(js["PLAYERCONFIG"]["accomodation"]["type"]), FoodArray, js["PLAYERCONFIG"]["TEXadress"], sf::Vector2f(x, y));
	//
	//
	// 
	// reading the dorm data
	//
	//
	const int width = js["DORMCONFIG"]["mapsize"]["x"], height = js["DORMCONFIG"]["mapsize"]["y"];
	
	std::vector <int> tempTileScheme_vector;
	json jsTiles = js["DORMCONFIG"]["tilescheme"];
	for (const auto& tile : jsTiles) {
		tempTileScheme_vector.push_back(tile);
	}

	int tempTileScheme[MAXwidth * MAXheight];
	for (int i = 0; i < tempTileScheme_vector.size(); ++i) {
		tempTileScheme[i] = tempTileScheme_vector[i];
	}
	
	std::vector <WorldObject> tempObjects;
	for (const auto& object : js["DORMCONFIG"]["objects"]) {
		tempObjects.push_back(WorldObject(object["name"], sf::Vector2f(object["coordinates"]["x"] * defTileSize, object["coordinates"]["y"] * defTileSize), object["rotation"]));
	}

	this->dormConfig = Config(width, height, js["DORMCONFIG"]["backgroundTEXadress"], js["DORMCONFIG"]["movableTEXadress"], tempTileScheme,
		tempObjects,  sf::Vector2f(js["DORMCONFIG"]["spawnCoords"]["x"], js["DORMCONFIG"]["spawnCoords"]["y"]));
	
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


Player* SaveData::getPlayerPtr() {
	return &(this->currentPlayer);
}

