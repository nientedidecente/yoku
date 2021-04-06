#include "CpuPaddle.hpp"

CpuPaddle::CpuPaddle(sf::Vector2f rectSize, sf::IntRect field, std::shared_ptr<Ball> ball) : Paddle(rectSize, field), m_Ball(ball)
{
    m_Shape.setPosition(m_Field.width - 50, m_Field.height / 2);
}

void CpuPaddle::processInput()
{
}

void CpuPaddle::update(float dt)
{
    auto ballPosition = m_Ball->getPosition();
    auto cpuPos = getPosition();

    // only if ball it is in his own field
    if ((cpuPos.y - ballPosition.y) <= 20 && ballPosition.x > (m_Field.width / 2))
    {
        auto cpuDir = cpuPos.y < ballPosition.y ? 1 : -1;
        m_Shape.setPosition(cpuPos.x, cpuPos.y + (cpuDir * SPEED * dt));
    }
}