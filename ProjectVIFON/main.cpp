#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "SFML works!");
    sf::Texture avatar_tex;

    if (!avatar_tex.loadFromFile("../Graphics/avatar.png"))
        std::cout << "Avatar didn't load" << std::endl;

    sf::Sprite avatar;
    avatar.setTexture(avatar_tex);
    avatar.setOrigin(sf::Vector2f(-500, -400));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::W:
                    avatar.move(sf::Vector2f(0, -5));
                    continue;
                case sf::Keyboard::S:
                    avatar.move(sf::Vector2f(0, 5));
                    continue;
                case sf::Keyboard::A:
                    avatar.move(sf::Vector2f(-5, 0));
                    continue;
                case sf::Keyboard::D:
                    avatar.move(sf::Vector2f(5, 0));
                    continue;
                default:
                    break;
                }
            }
        }

        window.clear();
        window.draw(avatar);
        window.display();
    }

    return 0;
}