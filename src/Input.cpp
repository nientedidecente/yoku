#include "Input.hpp"

#include <iostream>

namespace yoku
{

    Input::Input(const std::vector<sf::Keyboard::Key> &keys)
    {
        for (auto &key : keys)
        {
            m_trackedKeys[key] = {.isPressed = false, .wasPressed = false};
        }

        m_trackedMouseButton[sf::Mouse::Button::Left] = {.isPressed = false,
                                                         .wasPressed = false};
        m_trackedMouseButton[sf::Mouse::Button::Right] = {.isPressed = false,
                                                          .wasPressed = false};
    }

    void Input::update()
    {
        for (auto &[key, state] : m_trackedKeys)
        {
            state.wasPressed = state.isPressed;
            state.isPressed = sf::Keyboard::isKeyPressed(key);
        }

        for (auto &[key, state] : m_trackedMouseButton)
        {
            state.wasPressed = state.isPressed;
            state.isPressed = sf::Mouse::isButtonPressed(key);
        }
    }

    bool Input::wasKeyPressed(sf::Keyboard::Key key)
    {
        auto found = m_trackedKeys.find(key);
        if (found != m_trackedKeys.end())
        {
            return found->second.wasPressed && !found->second.isPressed;
        }

        return false;
    }

    bool Input::wasMouseClicked(sf::Mouse::Button key)
    {
        auto found = m_trackedMouseButton.find(key);
        if (found != m_trackedMouseButton.end())
        {
            return found->second.wasPressed && !found->second.isPressed;
        }

        return false;
    }
}
