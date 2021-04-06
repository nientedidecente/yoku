#pragma once

#include "Entity.hpp"
#include "../libs/Randomizer.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

class Ball : public Entity
{
private:
    sf::CircleShape m_Shape;
    sf::IntRect m_Field;
    Randomizer rng;
    sf::Vector2f m_Direction = {1, -1};
    const int SPEED = 100;

public:
    Ball(int radius, sf::IntRect m_Field);

    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;
    bool intersect(const Entity &other) override;
    void processInput() override {}
    void update(float dt) override;
    void draw(yoku::Window &window) override;

    void paddleHit();
    void reset();
};