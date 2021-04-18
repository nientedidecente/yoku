#pragma once
#include "Types.hpp"

#include <SFML/Graphics.hpp>

class Entity
{
protected:
    Types m_type;
    int m_id;

public:
    int size = 0;
    Entity(const int id, Types type) : m_id(id), m_type(type) {}
    int getId() const { return m_id; }
    Types getType() const { return m_type; }
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Drawable &getDrawable() const = 0;
    virtual void update(float dt) = 0;
    virtual void setActive(bool value) = 0;
    virtual bool isActive() const = 0;

    virtual void checkCollision(Entity &other) = 0;
    virtual void setHighlight(bool value) = 0;
};
