#include "Cell.hpp"

#include "rand.h"

#include <iostream>

Cell::Cell(sf::Vector2i pos, sf::IntRect &field) : m_field(field)
{
    m_shape = std::make_unique<sf::CircleShape>(size);
    m_shape->setPosition(float(pos.x), float(pos.y));
    m_shape->setFillColor(sf::Color::White);
    auto bounds = m_shape->getLocalBounds();
    m_shape->setOrigin(bounds.width / 2, bounds.width / 2);
}

Cell::~Cell()
{
    auto position = m_shape->getPosition();
    std::cout << "Destroying cell at: " << position.x << "  ,  " << position.y << '\n';
}

void Cell::update(float dt)
{
    if (m_isDead)
        return;

    m_lastDecisionTimeout += dt;
    auto pos = m_shape->getPosition();
    auto isInside = m_field.contains(pos.x + size, pos.y + size);

    if (m_lastDecisionTimeout >= UPDATE_TIME)
    {
        m_satiety -= .1f;
        if (m_satiety <= 0)
        {
            std::cout << "Starving!!\n";
            m_satiety = 0.f;
        }

        if (isInside)
        {
            m_direction = rng::chance(0.5f) ? sf::Vector2i(1, 1) : sf::Vector2i(1, -1);
            m_direction = rng::chance(0.5f) ? sf::Vector2i(-1, -1) : sf::Vector2i(-1, 1);
        }
        m_lastDecisionTimeout = 0;
    }

    if (m_satiety <= 0 || !isInside)
    {
        std::cout << "Losing life\n";
        m_life -= 0.1f;
    }

    if (m_life <= 0)
    {
        std::cout << "I deeeeed!\n";
        m_isDead = true;
    }

    if (isInside)
    {
        m_shape->setPosition(pos.x + (m_speed * m_direction.x * dt), pos.y + (m_speed * m_direction.y * dt));
        return;
    }

    m_directionTimeout += dt;
    bool directionChangeTimedOut = m_directionTimeout >= DIRECTION_TIMEOUT;
    if (!isInside && directionChangeTimedOut)
    {
        std::cout << "Changing direction\n";
        m_directionTimeout = 0;
        if (rng::chance(0.5f))
            m_direction.x *= -1;
        if (rng::chance(0.5f))
            m_direction.y *= -1;

        m_shape->setPosition(pos.x + (m_speed * m_direction.x * dt), pos.y + (m_speed * m_direction.y * dt));
    }
}
