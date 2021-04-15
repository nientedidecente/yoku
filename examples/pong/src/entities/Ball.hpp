#pragma once

#include "Entity.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

class Ball : public Entity
{
private:
    sf::CircleShape m_Shape;
    sf::IntRect m_Field;
    sf::Vector2f m_Direction = {-1, -1};
    int m_CurrentSpeed = 200;
    const int SPEED_INCREASE = 20;

public:
    Ball(int radius, sf::IntRect m_Field);

    sf::Vector2f getDirection() const;
    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;
    bool intersect(const Entity &other) override;
    void processInput() override {}
    void update(float dt) override;
    void draw(yoku::Window &window) override;

    void paddleHit(float hitY);
    void reset();
};
