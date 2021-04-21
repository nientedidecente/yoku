#pragma once

#include "Entity.hpp"

#include <memory>

class Cell : public Entity
{
private:
    sf::IntRect &m_field;
    std::unique_ptr<sf::CircleShape> m_shape;
    sf::Color m_baseColour = sf::Color::White;
    bool m_isDead = false;
    const float UPDATE_TIME = 4.f;
    const float DIRECTION_TIMEOUT = 1.5f;

    float m_lastDecisionTimeout = 5.f;
    float m_directionTimeout = 0.f;

    float m_satiety = 1.f;
    float m_life = 1.f;

    int m_speed = 20;

    sf::Vector2f m_direction = {0.f, 0.f};

public:
    Cell(const std::string &id, sf::Vector2i pos, sf::IntRect &field);

    sf::Vector2f getPosition() const override { return m_shape->getPosition(); }
    sf::FloatRect getBounds() const override { return m_shape->getGlobalBounds(); }

    void setActive(bool value) override { m_isDead = !value; }
    bool isActive() const override { return !m_isDead; }
    sf::Drawable &getDrawable() const override { return *m_shape; }

    void update(float dt) override;
    void checkCollision(Entity &other) override;
    void setHighlight(bool value) override;

    void grow();
};
