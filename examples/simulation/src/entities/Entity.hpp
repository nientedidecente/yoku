#pragma once

#include <SFML/Graphics.hpp>

class Entity
{

public:
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Drawable &getDrawable() const = 0;
    virtual void update(float dt) = 0;
    virtual bool isActive() const = 0;
};
