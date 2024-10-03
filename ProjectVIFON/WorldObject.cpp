#include "WorldObject.h"
#include "TextureFinder.h"

// default constructor
WorldObject::WorldObject(movableObject name, sf::Vector2f position, int rotation) {
	this->name = name;
	this->position = position;
	this->rotation = rotation;
	switch (rotation) {
	case 1:
	case 3:
		this->size = sf::Vector2f(defTileSize * 2, defTileSize * 2 * defNrOfTiles(name));
		break;
	default:
		this->size = sf::Vector2f(defTileSize * 2 * defNrOfTiles(name), defTileSize * 2);
		break;
	}
	
	
}

sf::IntRect WorldObject::getTEXrect() {
	// obtaining the number of tiles the object takes
	int tilesNR = defNrOfTiles(name);

	// getting to know the position of the texture in the texture file
	int TEXpos = 0;
	for (int i = 0; i < name; i++) {
		TEXpos += (defTileSize * 2) * defNrOfTiles(movableObject(i));
	}

	return sf::IntRect(TEXpos, 0, defTileSize * 2 * tilesNR, defTileSize * 2);


}

//getter for the rotation
int WorldObject::getRot() const {
	return rotation;
}

// getter for the position
sf::Vector2f WorldObject::getPosition() const {
	return position;
}

// getter for the size
sf::Vector2f WorldObject::getSize() const {
	return size;
}