#pragma once
#include "Types.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

#include "Entity.hpp"

class Food : public Entity
{
private:
    std::unique_ptr<sf::CircleShape> m_shape;
    bool m_isEaten = false;

public:
    int size = 5;
    Food(const std::string &id, sf::IntRect &field);

    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;
    sf::Drawable &getDrawable() const override;
    void update(float dt) override;
    void setActive(bool value) override;
    bool isActive() const override;

    void checkCollision(Entity &other) override;
    void setHighlight(bool value) override;
};
