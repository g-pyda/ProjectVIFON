#include <SFML/Graphics.hpp>
#include <iostream>
#include "dormTEX.h"
#include "WorldMap.h"
#include "constants.h"

bool is_colliding_left(sf::Sprite, sf::RectangleShape);
bool is_colliding_right(sf::Sprite, sf::RectangleShape);
bool is_colliding_top(sf::Sprite, sf::RectangleShape);
bool is_colliding_bottom(sf::Sprite, sf::RectangleShape);


int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Texture generating testing!");
    sf::Texture avatarTEX, dormTEX;
    sf::View gameplayView;


    if (!avatarTEX.loadFromFile("../Graphics/avatar.png"))
        std::cout << "Avatar didn't load" << std::endl;
    sf::Sprite avatar;
    avatar.setTexture(avatarTEX);
    avatar.setOrigin(-400, -150);

    WorldMap dormMAP(sf::Vector2u(defTileSize, defTileSize), dormTEXscheme, windowWidth/defTileSize, windowHeight/defTileSize, dormTEXadress);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::W:
                    avatar.move(sf::Vector2f(0, -2));
                    break;
                case sf::Keyboard::S:
                    avatar.move(sf::Vector2f(0, 2));
                    break;
                case sf::Keyboard::A:
                    avatar.move(sf::Vector2f(-2, 0));
                    break;
                case sf::Keyboard::D:
                    avatar.move(sf::Vector2f(2, 0));
                    break;
                default:
                    break;
                }

                //checking for the collisions
                while (dormMAP.is_colliding_top(&avatar)) {
                    std::cout << "top" << std::endl;
                    avatar.move(sf::Vector2f(0, 1));
                }
                while (dormMAP.is_colliding_bottom(&avatar)) {
                    std::cout << "bottom" << std::endl;
                    avatar.move(sf::Vector2f(0, -1));
                }
                while (dormMAP.is_colliding_right(&avatar)) {
                    std::cout << "right" << std::endl;
                    avatar.move(sf::Vector2f(-1, 0));
                }
                while (dormMAP.is_colliding_left(&avatar)) {
                    std::cout << "left" << std::endl;
                    avatar.move(sf::Vector2f(1, 0));
                }
            }
        }

        window.clear();
        window.draw(dormMAP);
        window.draw(avatar);
        window.display();
        
    }

    return 0;
}

bool is_colliding_left(sf::Sprite sprite, sf::RectangleShape shape) {
    sf::FloatRect sp_size = sprite.getGlobalBounds();
    sf::FloatRect sh_size = shape.getGlobalBounds();

    if (sh_size.left + sh_size.width > sp_size.left - 1 && sp_size.left - 1 > sh_size.left && //x axis
        (sh_size.top < sp_size.top && sp_size.top < sh_size.top + sh_size.height ||
         sp_size.top < sh_size.top && sh_size.top < sp_size.top + sp_size.height)) //y axis
        return true;
    else return false;
}

bool is_colliding_right(sf::Sprite sprite, sf::RectangleShape shape) {
    sf::FloatRect sp_size = sprite.getGlobalBounds();
    sf::FloatRect sh_size = shape.getGlobalBounds();

    if (sh_size.left + sh_size.width > sp_size.left + sp_size.width + 1 && sp_size.left + sp_size.width + 1 > sh_size.left && //x axis
        (sh_size.top < sp_size.top && sp_size.top < sh_size.top + sh_size.height ||
         sp_size.top < sh_size.top && sh_size.top < sp_size.top + sp_size.height)) //y axis
        return true;
    else return false;
}
bool is_colliding_top(sf::Sprite sprite, sf::RectangleShape shape) {
    sf::FloatRect sp_size = sprite.getGlobalBounds();
    sf::FloatRect sh_size = shape.getGlobalBounds();

    if (sh_size.top + sh_size.height > sp_size.top - 1 && sp_size.top - 1 > sh_size.top && //y axis
        (sh_size.left < sp_size.left && sp_size.left < sh_size.left + sh_size.width ||
         sp_size.left < sh_size.left && sh_size.left < sp_size.left + sp_size.width)) //x axis
        return true;
    else return false;
}

bool is_colliding_bottom(sf::Sprite sprite, sf::RectangleShape shape) {
    sf::FloatRect sp_size = sprite.getGlobalBounds();
    sf::FloatRect sh_size = shape.getGlobalBounds();

    if (sh_size.top + sh_size.height > sp_size.top + sp_size.height + 1 && sp_size.top + sp_size.height + 1 > sh_size.top && //y axis
        (sh_size.left < sp_size.left && sp_size.left < sh_size.left + sh_size.width ||
         sp_size.left < sh_size.left && sh_size.left < sp_size.left + sp_size.width)) //x axis
        return true;
    else return false;
}