#pragma once

#include <SFML/Graphics.hpp>

class Entity
{

public:
    virtual sf::Drawable &getDrawable() const = 0;
    virtual void update(float dt) = 0;
};
