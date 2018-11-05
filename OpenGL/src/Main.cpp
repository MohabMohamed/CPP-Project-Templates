#include <iostream>
#include <SFML/Graphics.hpp>
#include "Glad/glad.h"

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    if (!gladLoadGL()) {
        std::cout << "Unable to load OpenGL function, exiting\n";
        return -1;
    }

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        glClearColor(0.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.display();
    }
}