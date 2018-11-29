#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>

class Mouse {
    public:
        Mouse();
        Mouse(const sf::Window& window, bool centreMouse = false);

        void update(sf::Event e);

        bool isDown(sf::Mouse::Button button) const;
        bool isReleased(sf::Mouse::Button button) const;

        const sf::Vector2i& getLastMove() const;

    private:
        std::array<bool, sf::Mouse::ButtonCount> m_buttons;
        sf::Mouse::Button m_recentlyReleased;

        sf::Vector2i        m_lastMove;
        
        const sf::Window*   m_pWindow = nullptr;
        const sf::Vector2i  m_windowCentre;
        const bool m_shouldCentreMouse = false;
};