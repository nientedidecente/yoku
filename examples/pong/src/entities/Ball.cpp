#include "Ball.hpp"

Ball::Ball(int radius, sf::IntRect m_Field) : m_Shape(radius), m_Field(m_Field)
{
    m_Shape.setOrigin(radius, radius);
    m_Shape.setPosition(m_Field.width / 2, m_Field.height / 2);
}
sf::Vector2f Ball::getDirection() const
{
    return m_Direction;
}

sf::Vector2f Ball::getPosition() const
{
    return m_Shape.getPosition();
}

sf::FloatRect Ball::getBounds() const
{
    return m_Shape.getGlobalBounds();
}

bool Ball::intersect(const Entity &other)
{
    return getBounds().intersects(other.getBounds());
}

void Ball::paddleHit()
{
    auto pos = getPosition();
    m_Direction.y = (rng.chance(50) ? -1 : 1) * m_Direction.y;
    m_Direction.x = -1 * m_Direction.x;
    m_Shape.setPosition(pos.x + (m_Direction.x * 30), pos.y);
}

void Ball::reset()
{
    m_Shape.setPosition(m_Field.width / 2, m_Field.height / 2);
}

void Ball::update(float dt)
{
    auto initialPos = getPosition();
    m_Shape.setPosition(initialPos.x + (m_Direction.x * SPEED * dt), initialPos.y + (m_Direction.y * SPEED * dt));
    auto updatedPos = getPosition();
    if (updatedPos.y >= m_Field.height || updatedPos.y <= 0)
    {
        m_Direction.y = -1 * m_Direction.y;
    }
}

void Ball::draw(yoku::Window &window)
{
    window.draw(m_Shape);
}