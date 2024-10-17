#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include "Player.h"
#include "Config.h"
#include "WorldMap.h"
#include "constants.h"
using json = nlohmann::json;

class SaveData {
public:
	// default constructor
	SaveData();
	SaveData(std::string);
	// getter for the dorm map configuration
	Config getDormConfig() const;
	// getter for the uni map configuration
	//Config getUniConfig() const;
	//// getter for the hipermarket map configuration
	//Config getHipermarketConfig() const;
	//// getter for the outdoor map configuration
	//Config getOutdoorConfig() const;
private:
	Config dormConfig;
	//Config outdoorConfig;
	//Config uniConfig;
	//Config hipermarketConfig;
	Player currentPlayer;
};


