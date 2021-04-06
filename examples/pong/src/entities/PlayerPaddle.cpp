#include "PlayerPaddle.hpp"

PlayerPaddle::PlayerPaddle(sf::Vector2f rectSize, sf::IntRect field) : Paddle(rectSize, field)
{
    m_Shape.setPosition(30, m_Field.height / 2);
}

void PlayerPaddle::processInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_Direction = -1;
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_Direction = 1;
        return;
    }
}
void PlayerPaddle::update(float dt)
{
    if (m_Direction != 0)
    {
        auto pos = getPosition();
        m_Shape.setPosition(pos.x, pos.y + (m_Direction * SPEED * dt));
    }

    m_Direction = 0;
}