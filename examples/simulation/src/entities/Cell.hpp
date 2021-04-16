#pragma once

#include "Entity.hpp"

#include <memory>

class Cell : public Entity
{
private:
    sf::IntRect &m_field;
    std::unique_ptr<sf::CircleShape> m_shape;
    bool m_isDead = false;
    const float UPDATE_TIME = 4.f;
    const float DIRECTION_TIMEOUT = 1.5f;

    float m_lastDecisionTimeout = 5.f;
    float m_directionTimeout = 0.f;

    float m_satiety = 1.f;
    float m_life = 1.f;

    int m_speed = 20;

    sf::Vector2i m_direction = {0, 0};

public:
    int size = 10;
    Cell(sf::Vector2i pos, sf::IntRect &field);
    ~Cell();

    sf::Vector2f getPosition() const override { return m_shape->getPosition(); }
    sf::FloatRect getBounds() const override { return m_shape->getGlobalBounds(); }

    bool isActive() const override { return !m_isDead; }
    sf::Drawable &getDrawable() const override { return *m_shape; }

    void update(float dt) override;
};
