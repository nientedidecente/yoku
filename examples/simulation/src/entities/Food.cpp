#include "Food.hpp"

#include "rng.hpp"

Food::Food(const std::string &id, sf::IntRect &field) : Entity(id, Types::Food), size(5)
{
    auto x = yoku::rng::integer(0, field.width);
    auto y = yoku::rng::integer(0, field.height);
    m_shape = std::make_unique<sf::CircleShape>(size);
    m_shape->setPosition(x, y);
    m_shape->setFillColor(sf::Color(33, 33, 33));
    auto bounds = m_shape->getLocalBounds();
    m_shape->setOrigin(bounds.width / 2, bounds.width / 2);
}

sf::Vector2f Food::getPosition() const
{
    return m_shape->getPosition();
}
sf::FloatRect Food::getBounds() const
{
    return m_shape->getGlobalBounds();
}
sf::Drawable &Food::getDrawable() const
{
    return *m_shape;
}
void Food::update(float dt)
{
    return;
}
void Food::setActive(bool value)
{
    m_isEaten = !value;
}
bool Food::isActive() const
{
    return !m_isEaten;
}

void Food::checkCollision(Entity &other)
{
    // noop
}
void Food::setHighlight(bool value)
{
    m_shape->setFillColor(value ? sf::Color::Blue : sf::Color(33, 33, 33));
}