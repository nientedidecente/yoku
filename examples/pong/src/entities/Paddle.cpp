#include "Paddle.hpp"

sf::Vector2f Paddle::getPosition() const
{
    return m_Shape.getPosition();
}
sf::FloatRect Paddle::getBounds() const
{
    return m_Shape.getGlobalBounds();
}
bool Paddle::intersect(const Entity &other)
{
    return getBounds().intersects(other.getBounds());
}
void Paddle::draw(yoku::Window &window)
{
    window.draw(m_Shape);
}