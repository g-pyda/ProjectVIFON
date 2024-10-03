#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "constants.h"
#include "WorldObject.h"
#include "Config.h"
#include <vector>

class WorldMap : public sf::Drawable, public sf::Transformable {
public: 
    // method to load the textures for the world map
    bool load(const std::string& backTexture, const std::string& movTexture);
    // default constructor
    WorldMap(sf::Vector2u tileSize, const Config config);

    // methods to check the collision with the side of the sprite
    bool is_colliding_left(sf::Sprite*);
    bool is_colliding_right(sf::Sprite*);
    bool is_colliding_top(sf::Sprite*);
    bool is_colliding_bottom(sf::Sprite*);

private:
    // array of vertice - background/walls
    sf::VertexArray tileArray;
    // texture atribute - background/walls
    sf::Texture texture;

    // tile size atribute
    sf::Vector2u backgroundTileSize;
    // array of texture numbers to render
    const int* tilesScheme;

    // world width
    unsigned int width;
    // world height
    unsigned int height;

    // vector of movable objects
    std::vector <WorldObject> movableObjects;
    // array of vertice - movable objects
    sf::VertexArray movableObjArray;
    // texture atribute - movable objects
    sf::Texture objtexture;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

