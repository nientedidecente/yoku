#pragma once

#include "Entity.hpp"

class Paddle : public Entity
{
protected:
    sf::IntRect m_Field;
    sf::RectangleShape m_Shape;
    short m_Direction = 0;
    const int SPEED = 200;

public:
    Paddle(sf::Vector2f rectSize, sf::IntRect field) : m_Shape(rectSize), m_Field(field)
    {
        m_Shape.setOrigin(rectSize.x / 2, rectSize.y / 2);
    }
    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;
    bool intersect(const Entity &other) override;
    virtual void processInput() = 0;
    virtual void update(float dt) = 0;
    void draw(yoku::Window &window) override;
};
