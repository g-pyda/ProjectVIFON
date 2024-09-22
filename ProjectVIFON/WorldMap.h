#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "constants.h"

class WorldMap : public sf::Drawable, public sf::Transformable {
public: 
    // method to load the textures for the world map
    bool load(const std::string& tileset);
    // default constructor
    WorldMap(sf::Vector2u tileSize, const int* tiles, unsigned int Wwidth, unsigned int Wheight, const std::string& texture);

    bool is_colliding_left(sf::Sprite*);
    bool is_colliding_right(sf::Sprite*);
    bool is_colliding_top(sf::Sprite*);
    bool is_colliding_bottom(sf::Sprite*);
private:
    // array of vertice
    sf::VertexArray tileArray;
    // texture atribute
    sf::Texture texture;
    // tile size atribute
    sf::Vector2u tileSize;
    // array of texture numbers to render
    const int* tilesScheme;
    // world width
    unsigned int width;
    // world height
    unsigned int height;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

