#include "GameEngine.h"
#include <chrono>

void ThreadVisualisation(std::array<bool, 10>& states, std::array<bool, 30>& playerStates, sf::RenderWindow& window, SaveData& save, WorldMap& map, std::mutex& mtx) {
    
    window.setFramerateLimit(0u);
    window.setVerticalSyncEnabled(false);

    sf::Texture dormTEX;
    sf::View gameplayView(sf::FloatRect(0, 0, gameplayWidth, gameplayHeight));
    sf::View statsView(sf::FloatRect(0, 0, (windowWidth - gameplayWidth) / 2, windowHeight));
    statsView.setViewport(sf::FloatRect(0, 0, (1 - ((double)gameplayWidth / windowWidth)) / 2, 1));
    gameplayView.setViewport(sf::FloatRect(
        (1 - ((double)gameplayWidth / windowWidth)) / 2, (1 - ((double)gameplayHeight / windowHeight)) / 2,
        (double)gameplayWidth / windowWidth, (double)gameplayHeight / windowHeight));

    sf::RectangleShape needsBars[8];
    sf::Text needsText[8];
    sf::Text needsTitles[8];
    needsTitles[0].setString("Physical Health");
    needsTitles[1].setString("Mental Health");
    needsTitles[2].setString("Hunger");
    needsTitles[3].setString("Thirst");
    needsTitles[4].setString("Toilet");
    needsTitles[5].setString("Hygene");
    needsTitles[6].setString("Energy");
    needsTitles[7].setString("Entertainment");

    sf::Font mainFont;

    if (!mainFont.loadFromFile("../Fonts/AGENCYB.ttf"))
        std::cout << "Font didn't load!" << std::endl;

    for (int i = 0; i < 8; i++) {
        needsBars[i].setPosition(sf::Vector2f(50, 50 + 40 * i));
        needsBars[i].setSize(sf::Vector2f(300, 30));

        needsText[i].setFont(mainFont);
        needsText[i].setCharacterSize(20);
        needsText[i].setPosition(sf::Vector2f(300, 55 + 40 * i));
        needsText[i].setFillColor(sf::Color::Black);

        needsTitles[i].setFont(mainFont);
        needsTitles[i].setCharacterSize(20);
        needsTitles[i].setPosition(sf::Vector2f(80, 55 + 40 * i));
        needsTitles[i].setFillColor(sf::Color::Black);
    }

    
    
    Player* player = save.getPlayerPtr();
    

    while (states[enums::gameIsRunning] == true) {

        // moving the view so the player is in the center
        sf::Vector2f playerPos = player->getAvatarPtr()->getPosition();
        gameplayView.setCenter(playerPos);

        // creating the adequate players need bars
        std::array<int, 8> playerNeeds = player->getNeeds();
        for (int i = 0; i < 8; i++) {
            if (playerNeeds[i] >= 70)
                needsBars[i].setFillColor(sf::Color::Green);
            else if (playerNeeds[i] <= 30)
                needsBars[i].setFillColor(sf::Color::Red);
            else
                needsBars[i].setFillColor(sf::Color::Yellow);

            needsText[i].setString(std::to_string(playerNeeds[i]));
        }

        std::unique_lock<std::mutex> windowLock(mtx);
        window.clear();

        window.setView(gameplayView);

        window.draw(map);
        
        window.draw(*player->getAvatarPtr());

        window.setView(statsView);
        for (auto& bar : needsBars)
            window.draw(bar);
        for (auto& t : needsText)
            window.draw(t);
        for (auto& t : needsTitles)
            window.draw(t);

        window.display();
        windowLock.unlock();
    }
    window.setActive(false);
}

void ThreadEngine(std::array<bool, 10>& states, std::array<bool, 30>& playerStates, sf::RenderWindow& window, SaveData& save, WorldMap & map, std::mutex& mtx) {
    window.setActive(false);

    Player* player = save.getPlayerPtr();
    
    std::chrono::steady_clock::time_point gameBegin = std::chrono::steady_clock::now();

    while (states[enums::gameIsRunning] == true) {
        // getting timestamp
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        // calculating  delta time to previous frame
        long long deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

        // move byt offset multiplied by delta time
        float* velPtr = player->getVelocityPtr();
        const float vel = 0.001f * deltaTime;
        std::unique_lock<std::mutex> velLock(mtx);
        *velPtr = vel;
        velLock.unlock();

        if (playerStates[enums::movingTop]) {
            (player)->move(sf::Vector2f(0, -vel));
            while (map.is_colliding_top((player)->getAvatarPtr())) {
                playerStates[enums::collisionTop] = true;
                if (states[enums::viewMoving])
                    continue;
                (player)->move(sf::Vector2f(0, vel));
            }
        }
        if (playerStates[enums::movingBottom]) {
            (player)->move(sf::Vector2f(0, vel));
            while (map.is_colliding_bottom((player)->getAvatarPtr())) {
                playerStates[enums::collisionBottom] = true;
                if (states[enums::viewMoving])
                    continue;
                (player)->move(sf::Vector2f(0, -vel));
            }
        }
        if (playerStates[enums::movingLeft]) {
            (player)->move(sf::Vector2f(-vel, 0));
            while (map.is_colliding_left((player)->getAvatarPtr())) {
                playerStates[enums::collisionLeft] = true;
                if (states[enums::viewMoving])
                    continue;
                (player)->move(sf::Vector2f(vel, 0));
            }
        }
        if (playerStates[enums::movingRight]) {
            (player)->move(sf::Vector2f(vel, 0));
            while (map.is_colliding_right((player)->getAvatarPtr())) {
                playerStates[enums::collisionRight] = true;
                if (states[enums::viewMoving])
                    continue;
                (player)->move(sf::Vector2f(-vel, 0));
            }            
        }
        playerStates[enums::collisionBottom] = false;
        playerStates[enums::collisionTop] = false;
        playerStates[enums::collisionRight] = false;
        playerStates[enums::collisionLeft] = false;

        // looking for the closest objects and using them
        sf::IntRect playerRect = sf::IntRect(sf::Vector2i(player->getAvatarPtr()->getPosition().x, player->getAvatarPtr()->getPosition().y),
            sf::Vector2i(player->getAvatarPtr()->getTexture()->getSize().x, player->getAvatarPtr()->getTexture()->getSize().y));
        enums::movableObject closestObject = map.getClosestObject(playerRect);
        player->use(closestObject);

        // evaluation of player needs during the gametime
        std::chrono::steady_clock::time_point gameEnd = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::minutes>(gameEnd - gameBegin).count() >= 2) {
            player->evaluateEvery2min();
            gameBegin = std::chrono::steady_clock::now();
        }
    }
}

void ThreadKeyboardHandler(std::array<bool, 10>& states, std::array<bool, 30>& playerStates, sf::RenderWindow& window, SaveData&, WorldMap&, std::mutex& mtx) {
    window.setActive(false);
    
    while (states[enums::gameIsRunning] == true) {

        // -------------------------- MOVEMENT SECTION ---------------------------- //

        // moving to the top
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            std::unique_lock<std::mutex> moveLock(mtx);
            playerStates[enums::movingTop] = true;
            moveLock.unlock();
        }
        else if (playerStates[enums::movingTop]) {
            std::unique_lock<std::mutex> moveLock(mtx);
            playerStates[enums::movingTop] = false;
            moveLock.unlock();
        }

        // moving tho the bottom

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            std::unique_lock<std::mutex> moveLock(mtx);
            playerStates[enums::movingBottom] = true;
            moveLock.unlock();
        }
        else if (playerStates[enums::movingBottom]) {
            std::unique_lock<std::mutex> moveLock(mtx);
            playerStates[enums::movingBottom] = false;
            moveLock.unlock();
        }

        // moving to the left

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            std::unique_lock<std::mutex> moveLock(mtx);
            playerStates[enums::movingLeft] = true;
            moveLock.unlock();
        }
        else if (playerStates[enums::movingLeft]) {
            std::unique_lock<std::mutex> moveLock(mtx);
            playerStates[enums::movingLeft] = false;
            moveLock.unlock();
        }

        // moving to the right

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            std::unique_lock<std::mutex> moveLock(mtx);
            playerStates[enums::movingRight] = true;
            moveLock.unlock();
        }
        else if (playerStates[enums::movingRight]) {
            std::unique_lock<std::mutex> moveLock(mtx);
            playerStates[enums::movingRight] = false;
            moveLock.unlock();
        }

        
    }
}
