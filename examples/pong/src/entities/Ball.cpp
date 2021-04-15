#include "Ball.hpp"

Ball::Ball(int radius, sf::IntRect m_Field) : m_Shape(radius), m_Field(m_Field)
{
    auto a = rng.chance(0.5f) ? 1 : -1;
    auto b = (rng.chance(0.5f) ? -1 : 1) * a;
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

void Ball::paddleHit(float hitY)
{
    m_Direction.x = -1 * m_Direction.x;
    if (rng.chance(.2))
    {
        m_Shape.setFillColor(sf::Color::Red);
        m_Direction.y = 0;
        m_CurrentSpeed += (SPEED_INCREASE * 2.f);
        return;
    }

    m_Shape.setFillColor(sf::Color::White);
    auto pos = getPosition();
    m_Direction.y = (hitY >= pos.y ? -1 : 1);
    m_Shape.setPosition(pos.x + (m_Direction.x * 30), pos.y);
    m_CurrentSpeed += SPEED_INCREASE;
}

void Ball::reset()
{
    m_Shape.setFillColor(sf::Color::White);
    m_Shape.setPosition(m_Field.width / 2, m_Field.height / 2);
    m_Direction = rng.chance(0.5f) ? sf::Vector2f{1, -1} : sf::Vector2f{-1, 1};
    if (rng.chance(.5f))
        m_Direction = rng.chance(0.5f) ? sf::Vector2f{1, 1} : sf::Vector2f{-1, -1};
}

void Ball::update(float dt)
{
    auto initialPos = getPosition();
    m_Shape.setPosition(initialPos.x + (m_Direction.x * m_CurrentSpeed * dt), initialPos.y + (m_Direction.y * m_CurrentSpeed * dt));
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