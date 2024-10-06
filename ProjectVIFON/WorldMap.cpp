#include "WorldMap.h"

// method to load the textures for the world map
bool WorldMap::load(const std::string& backTexture, const std::string& movTexture) {
    // load the background tileset texture
    sf::Texture worldTEX;
    if (!worldTEX.loadFromFile(backTexture))
        std::cout << "Background" << std::endl;
        return false;
    this->texture = worldTEX;
    // load the movable tileset texture
    if (!worldTEX.loadFromFile(movTexture))
        std::cout << "Movable" << std::endl;
        return false;
    this->objtexture = worldTEX;
    return true;
}

// default constructor
WorldMap::WorldMap(sf::Vector2u tileSize, Config config) {
    this->height = config.getHeight();
    this->width = config.getWidth();
    this->tilesScheme = config.getTEXscheme();
    this->backgroundTileSize = tileSize;
    this->movableObjects = config.getMovableObjScheme();
    if (!this->load(config.getBackgroundTEX(),config.getMovableTEX()))
        std::cout << "Textures didn't load!" << std::endl;

    // resize the background vertex array to fit the level size
    this->tileArray.setPrimitiveType(sf::Triangles);
    this->tileArray.resize(width * height * 6);
    
    // populate the vertex array of background, with two triangles per tile
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

    // resize the objects vertex array to fit the level size
    this->movableObjArray.setPrimitiveType(sf::Triangles);
    this->movableObjArray.resize(movableObjects.size() * 6);

    // populate the vertex array of objects, with two triangles per object
    for (unsigned int i = 0; i < movableObjects.size(); i++)
    {
        // get the rectangle of the object rexture
        sf::IntRect TEXrect = movableObjects[i].getTEXrect();
        sf::Vector2f objPos = movableObjects[i].getPosition();

        // get a pointer to the triangles' vertices of the current tile
        sf::Vertex* triangles = &this->movableObjArray[i * 6];

        // define the 6 corners of the two triangles regarding to the rotation
        switch (movableObjects[i].getRot()) {
        case 1:
            triangles[0].position = sf::Vector2f(objPos.x, objPos.y + TEXrect.width);
            triangles[1].position = sf::Vector2f(objPos.x, objPos.y);
            triangles[2].position = sf::Vector2f(objPos.x + TEXrect.height, objPos.y + TEXrect.width);
            triangles[3].position = sf::Vector2f(objPos.x + TEXrect.height, objPos.y + TEXrect.width);
            triangles[4].position = sf::Vector2f(objPos.x, objPos.y);
            triangles[5].position = sf::Vector2f(objPos.x + TEXrect.height, objPos.y);
            break;
        case 2:
            triangles[0].position = sf::Vector2f(objPos.x + TEXrect.width, objPos.y + TEXrect.height);
            triangles[1].position = sf::Vector2f(objPos.x, objPos.y + TEXrect.height);
            triangles[2].position = sf::Vector2f(objPos.x + TEXrect.width, objPos.y);
            triangles[3].position = sf::Vector2f(objPos.x + TEXrect.width, objPos.y);
            triangles[4].position = sf::Vector2f(objPos.x, objPos.y + TEXrect.height);
            triangles[5].position = sf::Vector2f(objPos.x, objPos.y);
            break;
        case 3:
            triangles[0].position = sf::Vector2f(objPos.x + TEXrect.height, objPos.y);
            triangles[1].position = sf::Vector2f(objPos.x + TEXrect.height, objPos.y + TEXrect.width);
            triangles[2].position = sf::Vector2f(objPos.x, objPos.y);
            triangles[3].position = sf::Vector2f(objPos.x, objPos.y);
            triangles[4].position = sf::Vector2f(objPos.x + TEXrect.height, objPos.y + TEXrect.width);
            triangles[5].position = sf::Vector2f(objPos.x, objPos.y + TEXrect.width);
            break;
        default:
            triangles[0].position = sf::Vector2f(objPos.x, objPos.y);
            triangles[1].position = sf::Vector2f(objPos.x + TEXrect.width, objPos.y);
            triangles[2].position = sf::Vector2f(objPos.x, objPos.y + TEXrect.height);
            triangles[3].position = sf::Vector2f(objPos.x, objPos.y + TEXrect.height);
            triangles[4].position = sf::Vector2f(objPos.x + TEXrect.width, objPos.y);
            triangles[5].position = sf::Vector2f(objPos.x + TEXrect.width, objPos.y + TEXrect.height);
            break;
        }

        // define the 6 matching texture coordinates
        triangles[0].texCoords = sf::Vector2f(TEXrect.left, TEXrect.top);
        triangles[1].texCoords = sf::Vector2f(TEXrect.left + TEXrect.width, TEXrect.top);
        triangles[2].texCoords = sf::Vector2f(TEXrect.left, TEXrect.top + TEXrect.height);
        triangles[3].texCoords = sf::Vector2f(TEXrect.left, TEXrect.top + TEXrect.height);
        triangles[4].texCoords = sf::Vector2f(TEXrect.left + TEXrect.width, TEXrect.top);
        triangles[5].texCoords = sf::Vector2f(TEXrect.left + TEXrect.width, TEXrect.top + TEXrect.height);
    }
    
}

void WorldMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // printing the background
    // apply the tileset texture
    states.texture = &this->texture;

    // draw the vertex array
    target.draw(this->tileArray, states);

    // printing the objects
    // apply the tileset texture
    states.texture = &this->objtexture;

    // draw the vertex array
    target.draw(this->movableObjArray, states);
}

bool WorldMap::is_colliding_left(sf::Sprite* sprite) {
    sf::FloatRect sp_size = (*sprite).getGlobalBounds();

    // check through every background tile on the map
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
    // check through every object on the map
    for (int i = 0; i < this->movableObjects.size(); i++) {
        //define the corners of the tile by rect
        sf::FloatRect sh_size(movableObjects[i].getPosition(), movableObjects[i].getSize());
        if (sp_size.left > sh_size.left) {
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
    // check through every object on the map
    for (int i = 0; i < this->movableObjects.size(); i++) {
        //define the corners of the tile by rect
        sf::FloatRect sh_size(movableObjects[i].getPosition(), movableObjects[i].getSize());
        if (sp_size.left + sp_size.width < sh_size.left + sh_size.width) {
            //checking the texture
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
    // check through every object on the map
    for (int i = 0; i < this->movableObjects.size(); i++) {
        //define the corners of the tile by rect
        sf::FloatRect sh_size(movableObjects[i].getPosition(), movableObjects[i].getSize());
        if (sp_size.top > sh_size.top) {
            //checking the texture
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
    // check through every object on the map
    for (int i = 0; i < this->movableObjects.size(); i++) {
        //define the corners of the tile by rect
        sf::FloatRect sh_size(movableObjects[i].getPosition(), movableObjects[i].getSize());
        if (sp_size.top + sp_size.height < sh_size.top + sh_size.height) {
            //checking the texture
            if (sh_size.intersects(sp_size)) {
                return true;
            }
        }
    }
    return false;
}