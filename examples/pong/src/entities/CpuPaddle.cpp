#include "CpuPaddle.hpp"

CpuPaddle::CpuPaddle(sf::Vector2f rectSize, sf::IntRect field, std::shared_ptr<Ball> ball)
    : Paddle(rectSize, field), m_Ball(ball)
{
    m_Shape.setPosition(m_Field.width - 50, m_Field.height / 2);
}

void CpuPaddle::processInput()
{
}

void CpuPaddle::update(float dt)
{
    m_Elapsed += dt;
    auto ballPosition = m_Ball->getPosition();
    auto cpuPos = getPosition();

    if (m_Elapsed >= ELAPSED_MAX)
    {
        auto diff = cpuPos.y - ballPosition.y;
        m_Direction = diff >= 50 ? -1 : 1;
        m_Elapsed = 0;
    }

    // only if ball it is in its field && ball going towards it
    if (ballPosition.x > (m_Field.width / 2) && m_Ball->getDirection().x > 0)
    {
        m_Shape.setPosition(cpuPos.x, cpuPos.y + (m_Direction * SPEED * dt));
    }
}