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
    m_quadtree = std::make_unique<Quadtree>(4, sf::FloatRect(0, 0, m_field.width, m_field.height));

    auto it = m_entities.begin();
    while (it != m_entities.end())
    {
        auto &entity = *it;
        entity->update(dt);

        if (!entity->isActive())
        {
            it = m_entities.erase(it);
            continue;
        }

        m_quadtree->insert(entity);

        it++;
    }
}

void Main::draw(yoku::Window &window)
{

    for (auto &e : m_entities)
    {
        window.draw(e->getDrawable());
    }

    if (m_quadtree != nullptr)
        m_quadtree->draw(window);
}

void Main::addEntity(const sf::Vector2i &pos)
{
    auto ent = std::make_shared<Cell>(pos, m_field);
    m_entities.emplace_back(ent);
}