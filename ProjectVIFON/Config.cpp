#include "Config.h"

Config::Config(unsigned int width, unsigned int height, const std::string& backgroundTEX, const std::string& movableTEX, const int TEXscheme[]) {
	this->width = width;
	this->height = height;
	this->backgroundTEX = backgroundTEX;
	this->movableTEX = movableTEX;
	this->TEXscheme = TEXscheme;
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

