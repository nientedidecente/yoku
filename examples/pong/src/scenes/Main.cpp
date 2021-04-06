#include "Main.hpp"

#include "yoku/Assets.hpp"
#include <iostream>

const int BALL_SPEED = 300;
const int BALL_SIZE = 10;
const int PADDLE_SPEED = 300;
const sf::IntRect PADDLE_SIZE = {0, 0, 10, 80};

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
    m_CpuScoreTxt.setPosition(m_Field.width - 40, 0);

    auto paddleShape = sf::Vector2f(PADDLE_SIZE.width, PADDLE_SIZE.height);
    m_PlayerPaddle = std::make_unique<sf::RectangleShape>(paddleShape);
    m_PlayerPaddle->setOrigin(PADDLE_SIZE.width / 2, PADDLE_SIZE.height / 2);
    m_PlayerPaddle->setPosition(30, m_Field.height / 2);

    m_CpuPaddle = std::make_unique<sf::RectangleShape>(paddleShape);
    m_CpuPaddle->setOrigin(PADDLE_SIZE.width / 2, PADDLE_SIZE.height / 2);
    m_CpuPaddle->setPosition(m_Field.width - 50, m_Field.height / 2);

    m_Ball = std::make_unique<sf::CircleShape>(BALL_SIZE);
    m_Ball->setOrigin(BALL_SIZE, BALL_SIZE);
    m_Ball->setPosition(m_Field.width / 2, m_Field.height / 2);
}

void Main::onDestroy()
{
}

void Main::processInput(sf::Event &event)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_PlayerDirection = -1;
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_PlayerDirection = 1;
        return;
    }
}

void Main::update(float dt)
{
    if (m_PlayerDirection != 0)
    {
        auto pos = m_PlayerPaddle->getPosition();
        m_PlayerPaddle->setPosition(pos.x, pos.y + (m_PlayerDirection * PADDLE_SPEED * dt));
    }

    auto initialPos = m_Ball->getPosition();
    m_Ball->setPosition(initialPos.x + (m_BallDirection.x * 100 * dt), initialPos.y + (m_BallDirection.y * BALL_SPEED * dt));

    if (m_Ball->getGlobalBounds().intersects(m_PlayerPaddle->getGlobalBounds()))
    {
        m_BallDirection.x = -1 * m_BallDirection.x;
        m_BallDirection.y = (rng.chance(70) ? -1 : 1) * m_BallDirection.y;
    }

    auto updatedPos = m_Ball->getPosition();
    if (updatedPos.x >= m_Field.width || updatedPos.x <= 0)
    {
        m_BallDirection.x = -1 * m_BallDirection.x;
    }
    if (updatedPos.y >= m_Field.height || updatedPos.y <= 0)
    {
        m_BallDirection.y = -1 * m_BallDirection.y;
    }

    m_PlayerDirection = 0;
}
void Main::draw(yoku::Window &window)
{
    window.draw(*m_Ball);
    window.draw(*m_CpuPaddle);
    window.draw(*m_PlayerPaddle);
    window.draw(m_CpuScoreTxt);
    window.draw(m_PlayerScoreTxt);
}