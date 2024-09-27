#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "constants.h"

class WorldObject : public sf::Drawable {
private:
	// name of the object
	std::string name;
	// sprite to render 
	sf::Sprite sprite;
	// default constructor
	WorldObject(std::string name);

};

