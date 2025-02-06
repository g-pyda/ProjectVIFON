#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <chrono>
#include "Config.h"
#include "dormTEX.h"
#include "WorldMap.h"
#include "constants.h"
#include "SaveData.h"
#include "GameEngine.h"

int main() {
    // Creating the bool state array for threading handling
    std::array<bool, 10> gameStates = { false };
    gameStates[enums::gameIsRunning] = true;
    std::array<bool, 30> playerStates = { false };

    std::mutex mtx;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Project VIFON");
    window.setActive(false);

    SaveData save("../Saves/save.json");
    WorldMap map(sf::Vector2u(defTileSize, defTileSize), save.getDormConfig());

    // Create threads and pass objects by reference
    std::thread visualisation(ThreadVisualisation, std::ref(gameStates), std::ref(playerStates), std::ref(window), std::ref(save), std::ref(map), std::ref(mtx));
    std::thread engine(ThreadEngine, std::ref(gameStates), std::ref(playerStates), std::ref(window), std::ref(save), std::ref(map), std::ref(mtx));
    std::thread keyboardHandler(ThreadKeyboardHandler, std::ref(gameStates), std::ref(playerStates), std::ref(window), std::ref(save), std::ref(map), std::ref(mtx));
    
    while (true) {
        // closing the window
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameStates[enums::gameIsRunning] = false;

                visualisation.join();
                engine.join();
                keyboardHandler.join();

                std::cout << "About to close the window" << std::endl;
                window.setActive(true);
                window.close();

                break;
            }
        }
    }

    


    return 0;
}
