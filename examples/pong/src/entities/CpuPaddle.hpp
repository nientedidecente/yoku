#pragma once

#include "Paddle.hpp"
#include "Ball.hpp"

#include <memory>

class CpuPaddle : public Paddle
{
private:
    std::shared_ptr<Ball> m_Ball;

    const float ELAPSED_MAX = 0.200f;
    float m_Elapsed = 0;

    short m_Direction = 0;

public:
    CpuPaddle(sf::Vector2f rectSize, sf::IntRect field, std::shared_ptr<Ball> ball);
    void processInput() override;
    void update(float dt) override;
};
