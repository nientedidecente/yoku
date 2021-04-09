#include "Main.hpp"
#include "../entities/Ball.hpp"
#include "../entities/PlayerPaddle.hpp"

#include "Assets.hpp"
#include <iostream>

const int BALL_SIZE = 10;
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

    m_Ball = std::make_shared<Ball>(BALL_SIZE, m_Field);
    m_PlayerPaddle = std::make_shared<PlayerPaddle>(paddleShape, m_Field);
    m_CpuPaddle = std::make_unique<CpuPaddle>(paddleShape, m_Field, m_Ball);

    m_Entities[0] = m_Ball;
    m_Entities[1] = m_PlayerPaddle;
    m_Entities[2] = m_CpuPaddle;
}

void Main::onDestroy()
{
}

void Main::processInput(sf::Event &event)
{
    for (auto &e : m_Entities)
    {
        if (e == nullptr)
            continue;
        e->processInput();
    }
}

void Main::update(float dt)
{
    for (auto &e : m_Entities)
    {
        if (e == nullptr)
            continue;
        e->update(dt);
    }

    if (m_Ball->intersect(*m_PlayerPaddle) || m_Ball->intersect(*m_CpuPaddle))
    {
        m_Ball->paddleHit();
    }

    auto updatedPos = m_Ball->getPosition();
    if (updatedPos.x >= m_Field.width)
    {
        m_PlayerScore += 1;
        m_PlayerScoreTxt.setString(std::to_string(m_PlayerScore));
        m_Ball->reset();
    }
    if (updatedPos.x <= 0)
    {
        m_CpuScore += 1;
        m_CpuScoreTxt.setString(std::to_string(m_CpuScore));
        m_Ball->reset();
    }
}

void Main::draw(yoku::Window &window)
{
    for (auto &e : m_Entities)
    {
        if (e == nullptr)
            continue;
        e->draw(window);
    }
    window.draw(m_CpuScoreTxt);
    window.draw(m_PlayerScoreTxt);
}