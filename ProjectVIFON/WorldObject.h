#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "constants.h"

class WorldObject {
private:
	// name of the object
	enums::movableObject name;
	// pointer to the triangles rendered on the world map
	sf::Vertex* objTriangles;
	// integer stating amout of 90 degree rotations (anticlockwise)
	int rotation;
	// vector to the position of the object
	sf::Vector2f position;
	// vector of the object's size
	sf::Vector2f size;
	// function to render the proper texture of the object
	sf::IntRect getTEXrect();
public:
	// default constructor
	WorldObject(enums::movableObject name, sf::Vector2f position, int rotation);
	//getter for the rotation
	int getRot() const;
	// getter for the position
	sf::Vector2f getPosition() const;
	// getter for the size
	sf::Vector2f getSize() const;
	//friend class
	friend class WorldMap;
};

