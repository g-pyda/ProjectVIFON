#pragma once
#include "constants.h"
#include <array>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "SaveData.h"

void ThreadVisualisation(std::array<bool, 10>& gameStates, std::array<bool, 30>& playersStates, sf::RenderWindow&, SaveData&, WorldMap&, std::mutex& mtx);

void ThreadEngine(std::array<bool, 10>& gameStates, std::array<bool, 30>& playersStates, sf::RenderWindow&, SaveData&, WorldMap&, std::mutex& mtx);

void ThreadKeyboardHandler(std::array<bool, 10>& gamestates, std::array<bool, 30>& playersStates, sf::RenderWindow&, SaveData&, WorldMap&, std::mutex& mtx);