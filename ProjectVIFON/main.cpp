#include <SFML/Graphics.hpp>
#include <iostream>
#include "chrono"
#include "Config.h"
#include "dormTEX.h"
#include "WorldMap.h"
#include "constants.h"
#include "SaveData.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Texture generating testing!");
    window.setFramerateLimit(0u);
    window.setVerticalSyncEnabled(false);
    sf::Texture avatarTEX, dormTEX;
    sf::View gameplayView(sf::FloatRect(0, 0, windowWidth, windowHeight));

    //SaveData newSave;
    //SaveData newSave;

    SaveData newSave2("../Saves/save.json");
    WorldMap dormMAP(sf::Vector2u(defTileSize, defTileSize), newSave2.getDormConfig());

    if (!avatarTEX.loadFromFile("../Graphics/avatar.png"))
        std::cout << "Avatar didn't load" << std::endl;
    sf::Sprite avatar;
    avatar.setTexture(avatarTEX);
    avatar.setPosition( windowWidth/2.0f, windowHeight/2.0f);


    while (window.isOpen()) {
        // getting timestamp
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        // calculating  delta time to previous frame
        long long deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

        // move byt offset multiplied by delta time
        const float vel = 0.001f * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            gameplayView.move(sf::Vector2f(0, -vel));
            avatar.move(sf::Vector2f(0, -vel));
            while (dormMAP.is_colliding_top(&avatar)) {
                avatar.move(sf::Vector2f(0, vel));
                gameplayView.move(sf::Vector2f(0, vel));
            }
        }
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            gameplayView.move(sf::Vector2f(0, vel));
            avatar.move(sf::Vector2f(0, vel));
            while (dormMAP.is_colliding_bottom(&avatar)) {
                avatar.move(sf::Vector2f(0, -vel));
                gameplayView.move(sf::Vector2f(0, -vel));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            gameplayView.move(sf::Vector2f(-vel, 0));
            avatar.move(sf::Vector2f(-vel, 0));
            while (dormMAP.is_colliding_left(&avatar)) {
                avatar.move(sf::Vector2f(vel, 0));
                gameplayView.move(sf::Vector2f(vel, 0));
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            gameplayView.move(sf::Vector2f(vel, 0));
            avatar.move(sf::Vector2f(vel, 0));
            while (dormMAP.is_colliding_right(&avatar)) {
                avatar.move(sf::Vector2f(-vel, 0));
                gameplayView.move(sf::Vector2f(-vel, 0));
            }
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    //checking for the additional collisions
    while (dormMAP.is_colliding_top(&avatar)) {
        avatar.move(sf::Vector2f(0, vel));
        gameplayView.move(sf::Vector2f(0, vel));
    }
    while (dormMAP.is_colliding_bottom(&avatar)) {
        avatar.move(sf::Vector2f(0, -vel));
        gameplayView.move(sf::Vector2f(0, -vel));
    }
    while (dormMAP.is_colliding_right(&avatar)) {
        avatar.move(sf::Vector2f(-vel, 0));
        gameplayView.move(sf::Vector2f(-vel, 0));
    }
    while (dormMAP.is_colliding_left(&avatar)) {
        avatar.move(sf::Vector2f(vel, 0));
        gameplayView.move(sf::Vector2f(vel, 0));
    }

        window.clear();
        window.setView(gameplayView);
        window.draw(dormMAP);
        window.draw(avatar);
        window.display();
        
    }

    return 0;
}
