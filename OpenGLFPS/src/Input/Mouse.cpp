#include "Mouse.h"

#include <SFML/Window/Window.hpp>

Mouse::Mouse()
{}

Mouse::Mouse(const sf::Window& window, bool centerMouse)
:   m_pWindow           (&window)
,   m_windowCentre      (window.getSize().x / 2, window.getSize().y / 2)
,   m_shouldCentreMouse (centerMouse) {}

void Mouse::update(sf::Event e) {
    switch(e.type) {
        case sf::Event::MouseButtonPressed:
            m_buttons[e.mouseButton.button] = true;
            break;
            
        case sf::Event::MouseButtonReleased:
            m_buttons[e.mouseButton.button] = false;
            break;

        case sf::Event::MouseMoved:
            m_lastMove = {e.mouseMove.x, e.mouseMove.y};
            if (m_shouldCentreMouse) {
                sf::Mouse::setPosition(m_windowCentre, *m_pWindow);
            }
            break;

        default:
            break;
    }
}

bool Mouse::isReleased(sf::Mouse::Button button) const {
    return m_recentlyReleased == button;
}