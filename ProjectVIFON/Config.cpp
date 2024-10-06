#include "Config.h"

Config::Config() {
	std::cout << "New config created" << std::endl;
}

Config::Config(unsigned int width, unsigned int height, const std::string& backgroundTEX, const std::string& movableTEX, const int TEXscheme[], 
	const std::vector <WorldObject> MovableScheme, sf::Vector2f playerCoords) {
	this->width = width;
	this->height = height;
	this->backgroundTEX = backgroundTEX;
	this->movableTEX = movableTEX;
	this->TEXscheme = TEXscheme;
	this->playerCoord = playerCoords;
	for (int i = 0; i < MovableScheme.size(); i++) {
		movableObjectsScheme.push_back(MovableScheme[i]);
	}
}

unsigned int Config::getWidth() const {
	return width;
}

unsigned int Config::getHeight() const {
	return height;
}

std::string Config::getBackgroundTEX() const {
	return backgroundTEX;
}

std::string Config::getMovableTEX() const {
	return movableTEX;
}

const int* Config::getTEXscheme() const {
	return TEXscheme;
}

const std::vector <WorldObject> Config::getMovableObjScheme() const {
	return movableObjectsScheme;
}

sf::Vector2f Config::getPlayerCoord() const {
	return playerCoord;
}

Config Config::operator=(const Config& another) {
	this->width = another.getWidth();
	this->height = another.getHeight();
	this->backgroundTEX = another.getBackgroundTEX();
	this->movableTEX = another.getMovableTEX();
	this->movableObjectsScheme = another.getMovableObjScheme();
	this->TEXscheme = another.getTEXscheme();
	this->playerCoord = another.getPlayerCoord();
}