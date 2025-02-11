#pragma once
#include "WorldObject.h"
#include "ShopObject.h"
#include "constants.h"
#include "TextureFinder.h"

class StorageObject : public WorldObject {
private:
	std::vector<ShopObject> storage;
public:
	// default constructor
	StorageObject(enums::movableObject name, sf::Vector2f position, int rotation, std::vector<ShopObject> storage);
};

