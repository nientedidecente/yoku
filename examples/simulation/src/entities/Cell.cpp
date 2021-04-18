#include "Cell.hpp"
#include "Types.hpp"

#include "rng.hpp"

#include <iostream>

Cell::Cell(const int id, sf::Vector2i pos, sf::IntRect &field) : Entity(id, Types::Cell), m_field(field)
{
    size = 10;
    m_shape = std::make_unique<sf::CircleShape>(size);
    m_shape->setPosition(float(pos.x), float(pos.y));
    m_shape->setFillColor(sf::Color::White);
    auto bounds = m_shape->getLocalBounds();
    m_shape->setOrigin(bounds.width / 2, bounds.width / 2);
}

void Cell::checkCollision(Entity &other)
{
    if (getBounds().intersects(other.getBounds()))
    {
        if (other.getType() == Types::Cell)
        {
            m_shape->setFillColor(sf::Color::Red);
            if (yoku::rng::chance(.5f + (.1f * (size - other.size))))
                other.setActive(false);
            else
                setActive(false);
        }
    }
}

void Cell::setHighlight(bool value)
{
    m_shape->setFillColor(value ? sf::Color::Green : sf::Color::White);
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
            m_direction = yoku::rng::chance(0.5f) ? sf::Vector2i(1, 1) : sf::Vector2i(1, -1);
            m_direction = yoku::rng::chance(0.5f) ? sf::Vector2i(-1, -1) : sf::Vector2i(-1, 1);
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
        if (yoku::rng::chance(0.5f))
            m_direction.x *= -1;
        else
            m_direction.y *= -1;

        m_shape->setPosition(pos.x + (m_speed * m_direction.x * dt), pos.y + (m_speed * m_direction.y * dt));
    }
}
