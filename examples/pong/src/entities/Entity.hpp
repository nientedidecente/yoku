#pragma once

#include "yoku/Window.hpp"

#include <SFML/Graphics.hpp>

class Entity
{
private:
public:
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual bool intersect(const Entity &other) = 0;
    virtual void processInput() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(yoku::Window &window) = 0;
};
