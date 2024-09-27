#pragma once
#include <string>
// size of the map in tiles
const unsigned int dormWIDTH = 32;
const unsigned int dormHEIGHT = 50;

// adress to the texture file
const std::string dormBackgroundTEXadress = "../Graphics/Background/dormBackgroundTEX.png";
const std::string dormMovableTEXadress = "../Graphics/Movable/dormFurnitureTEX.png";

/*--------------DESCRIPTION OF THE BACKGROUND TEXTURES-----------------
* o - shortage for open
* c - shortage for closed
* construction -> name/sides from left
0 - 3   -> door
4 - 9   -> window
10      -> floor
11      -> kitchen tiles
12      -> bathroom tiles
13      -> stairs
14 - 15 -> 2-end straight wall
16 - 19 -> 2-end curved wall
20      -> 4-end wall
21 - 24 -> 3-end wall
------------------------------------------------------------*/

