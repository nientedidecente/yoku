#include "Cell.hpp"
#include "Types.hpp"

#include "rng.hpp"

#include <iostream>

Cell::Cell(const std::string &id, sf::Vector2i pos, sf::IntRect &field) : Entity(id, Types::Cell), m_field(field)
{
    size = 10;
    m_shape = std::make_unique<sf::CircleShape>(size);
    m_shape->setPosition(float(pos.x), float(pos.y));
    m_shape->setFillColor(m_baseColour);
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

        if (other.getType() == Types::Food)
        {
            other.setActive(false);
            m_satiety = 1;
            m_baseColour = sf::Color::White;
            grow();
        }
    }
}

void Cell::setHighlight(bool value)
{
    m_shape->setFillColor(value ? sf::Color::Green : m_baseColour);
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
            m_baseColour = sf::Color::Yellow;
            m_satiety = 0.f;
        }

        if (isInside)
        {
            m_direction.x = (yoku::rng::chance(.5f) ? -1 : 1) * yoku::rng::integer(1, 10) / 10.f;
            m_direction.y = (yoku::rng::chance(.5f) ? -1 : 1) * yoku::rng::integer(1, 10) / 10.f;
        }

        if (m_satiety <= 0 || !isInside)
        {
            m_life -= 0.1f;
        }

        m_lastDecisionTimeout = 0;
    }

    if (m_life <= 0)
    {
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
        m_directionTimeout = 0;
        m_direction.x *= -1;
        m_direction.y *= -1;
        auto bounceSpeed = m_speed + 5;
        m_shape->setPosition(pos.x + (bounceSpeed * m_direction.x * dt), pos.y + (bounceSpeed * m_direction.y * dt));
    }
}

void Cell::grow()
{
    size += 5;
    auto currentPosition = getPosition();
    m_shape = std::make_unique<sf::CircleShape>(size);
    auto bounds = m_shape->getLocalBounds();
    m_shape->setOrigin(bounds.width / 2, bounds.width / 2);
    m_shape->setPosition(currentPosition);
    m_shape->setFillColor(m_baseColour);
}
