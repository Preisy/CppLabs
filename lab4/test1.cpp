#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML");
    int keyCounter = 0;

    window.setKeyRepeatEnabled(false);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                    keyCounter++;
                }
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                    keyCounter--;
                }
            } else if (event.type == sf::Event::MouseMoved) {
                /* move cursor inside the window to observe how the counter
                   behaves while pressing the keys */
                std::cout << keyCounter << std::endl;
            }
        }

        window.clear();
        window.display();

    }

    return 0;
}