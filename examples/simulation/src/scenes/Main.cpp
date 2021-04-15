#include "Main.hpp"

#include "../entities/Cell.hpp"

#include <iostream>

void Main::onCreate()
{
}

void Main::onDestroy()
{
}

void Main::processEvent(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto pos = m_window.getMousePosition();
        addEntity(pos);
        return;
    }

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
    {
        if (m_entities.size() > 0)
        {
            m_entities.pop_back();
        }
    }
}
void Main::processInput()
{
}

void Main::update(float dt)
{
    for (auto &e : m_entities)
    {
        e->update(dt);
    }
}

void Main::draw(yoku::Window &window)
{

    for (auto &e : m_entities)
    {
        window.draw(e->getDrawable());
    }
}

void Main::addEntity(const sf::Vector2i &pos)
{
    auto ent = std::make_shared<Cell>(pos, m_field);
    m_entities.emplace_back(ent);
}