#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Config.h"
#include "WorldMap.h"
#include "constants.h"

class SaveData {
public:
	// default constructor
	SaveData();
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
};


