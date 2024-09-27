#include "WorldMap.h"

// method to load the textures for the world map
bool WorldMap::load(const std::string& texture) {
    // load the tileset texture
    sf::Texture worldTEX;
    if (!worldTEX.loadFromFile(texture))
        return false;
    this->texture = worldTEX;
    return true;
}

// default constructor
WorldMap::WorldMap(sf::Vector2u tileSize, Config config) {
    this->height = config.getHeight();
    this->width = config.getWidth();
    this->tilesScheme = config.getTEXscheme();
    this->tileSize = tileSize;
    if (!this->load(config.getBackgroundTEX()))
        std::cout << "Texture didn't load!" << std::endl;

    // resize the vertex array to fit the level size
    this->tileArray.setPrimitiveType(sf::Triangles);
    this->tileArray.resize(width * height * 6);
    
    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tilesScheme[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (this->texture.getSize().x / tileSize.x);
            int tv = tileNumber / (this->texture.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &this->tileArray[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    
}

void WorldMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &this->texture;

    // draw the vertex array
    target.draw(this->tileArray, states);
}

bool WorldMap::is_colliding_left(sf::Sprite* sprite) {
    sf::FloatRect sp_size = (*sprite).getGlobalBounds();

    // check through every tile on the map
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j) {
            //define the corners of the tile by rect
            sf::FloatRect sh_size(sf::Vector2f(i * defTileSize, j * defTileSize), sf::Vector2f(defTileSize, defTileSize));
            // get the current tile number
            int tileNumber = this->tilesScheme[i + j * this->width];
            if (sp_size.left > sh_size.left && 
                (tileNumber >= 14 || (tileNumber <= 9 && tileNumber >= 4))) {
                //checking the texture
                if (sh_size.intersects(sp_size)) {
                    return true;
                }
            }
        }
    return false;
}

bool WorldMap::is_colliding_right(sf::Sprite* sprite) {
    sf::FloatRect sp_size = (*sprite).getGlobalBounds();
    // check through every tile on the map
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j) {
            //define the corners of the tile by rect
            sf::FloatRect sh_size(sf::Vector2f(i * defTileSize, j * defTileSize), sf::Vector2f(defTileSize, defTileSize));
            // get the current tile number
            int tileNumber = this->tilesScheme[i + j * width];
            if (sp_size.left + sp_size.width < sh_size.left + sh_size.width && 
                (tileNumber >= 14 || (tileNumber <= 9 && tileNumber >= 4))) {
                if (sh_size.intersects(sp_size)) {
                    return true;
                }
            }
        }
    return false;
}
bool WorldMap::is_colliding_top(sf::Sprite* sprite) {
    sf::FloatRect sp_size = (*sprite).getGlobalBounds();
    // check through every tile on the map
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j) {
            //define the corners of the tile by rect
            sf::FloatRect sh_size(sf::Vector2f(i * defTileSize, j * defTileSize), sf::Vector2f(defTileSize, defTileSize));
            // get the current tile number
            int tileNumber = this->tilesScheme[i + j * width];
            if (sp_size.top > sh_size.top && 
                (tileNumber >= 14 || (tileNumber <= 9 && tileNumber >= 4))) {
                if (sh_size.intersects(sp_size)) {
                    return true;
                }
            }
        }
    return false;
}

bool WorldMap::is_colliding_bottom(sf::Sprite* sprite) {
    sf::FloatRect sp_size = (*sprite).getGlobalBounds();
    // check through every tile on the map
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j) {
            //define the corners of the tile by rect
            sf::FloatRect sh_size(sf::Vector2f(i * defTileSize, j * defTileSize), sf::Vector2f(defTileSize, defTileSize));
            // get the current tile number
            int tileNumber = this->tilesScheme[i + j * width];
            if (sp_size.top + sp_size.height < sh_size.top + sh_size.height && 
                (tileNumber >= 14 || (tileNumber <= 9 && tileNumber >= 4))) {
                if (sh_size.intersects(sp_size)) {
                    return true;
                }
            }
        }
    return false;
}