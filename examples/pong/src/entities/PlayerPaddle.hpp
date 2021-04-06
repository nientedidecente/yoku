#pragma once

#include "Paddle.hpp"

class PlayerPaddle : public Paddle
{
public:
    PlayerPaddle(sf::Vector2f rectSize, sf::IntRect field);
    void processInput() override;
    void update(float dt) override;
};
