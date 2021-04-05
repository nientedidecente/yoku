#include "Main.hpp"

#include "yoku/Assets.hpp"
#include <iostream>

void Main::onCreate()
{
    auto font = yoku::Assets::getInstance()->loadFont("callingcode");

    m_PlayerScoreTxt.setFont(*font);
    m_PlayerScoreTxt.setString(std::to_string(m_PlayerScore));
    m_PlayerScoreTxt.setCharacterSize(40);
    m_PlayerScoreTxt.setPosition(20, 0);

    m_CpuScoreTxt.setFont(*font);
    m_CpuScoreTxt.setString(std::to_string(m_CpuScore));
    m_CpuScoreTxt.setCharacterSize(40);
    m_CpuScoreTxt.setPosition(800 - 40, 0);

    auto paddleShape = sf::Vector2f(10, 80);
    m_PlayerPaddle = std::make_unique<sf::RectangleShape>(paddleShape);
    m_PlayerPaddle->setOrigin(5, 40);
    m_PlayerPaddle->setPosition(30, 300);

    m_CpuPaddle = std::make_unique<sf::RectangleShape>(paddleShape);
    m_CpuPaddle->setOrigin(5, 40);
    m_CpuPaddle->setPosition(800 - 50, 300);
}

void Main::onDestroy()
{
}

void Main::processInput(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    {
        m_Direction = -1;
        return;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
    {
        m_Direction = 1;
        return;
    }
}

void Main::update(float dt)
{
    if (m_Direction != 0)
    {
        std::cout << "dir: " << m_Direction << std::endl;
        auto pos = m_PlayerPaddle->getPosition();
        m_PlayerPaddle->setPosition(pos.x, pos.y + (m_Direction * 500 * dt));
    }
    m_Direction = 0;
}
void Main::draw(yoku::Window &window)
{
    window.draw(m_CpuScoreTxt);
    window.draw(m_PlayerScoreTxt);
    window.draw(*m_CpuPaddle);
    window.draw(*m_PlayerPaddle);
}