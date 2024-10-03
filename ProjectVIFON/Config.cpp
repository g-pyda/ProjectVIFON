#include "Config.h"

Config::Config(unsigned int width, unsigned int height, const std::string& backgroundTEX, const std::string& movableTEX, const int TEXscheme[], const std::vector <WorldObject> MovableScheme) {
	this->width = width;
	this->height = height;
	this->backgroundTEX = backgroundTEX;
	this->movableTEX = movableTEX;
	this->TEXscheme = TEXscheme;
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
