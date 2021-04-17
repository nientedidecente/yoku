#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

namespace yoku
{

    struct KeyState
    {
        bool isPressed = false;
        bool wasPressed = false;
    };

    class Input
    {
    private:
        std::unordered_map<sf::Keyboard::Key, KeyState> m_trackedKeys;
        std::unordered_map<sf::Mouse::Button, KeyState> m_trackedMouseButton;

    public:
        Input(const std::vector<sf::Keyboard::Key> &keys);

        void update();

        bool wasKeyPressed(sf::Keyboard::Key key);
        bool wasMouseClicked(sf::Mouse::Button key = sf::Mouse::Button::Left);
    };

}
