#include "Main.hpp"

#include "../entities/Cell.hpp"
#include "../libs/Timer.hpp"

#include <iostream>

void Main::processInput(float dt)
{
    auto pos = m_window.getMousePosition();
    m_highlight.setPosition(pos.x, pos.y);
    m_input.update();

    if (m_input.wasKeyPressed(sf::Keyboard::D) && m_entities.size() > 0)
    {
        m_entities.pop_back();
    }

    if (m_input.wasMouseClicked())
    {
        addEntity(pos);
    }
}

void Main::update(float dt)
{
    //Timer timer("update");
    if (m_quadtree == nullptr)
    {
        m_quadtree = std::make_unique<Quadtree>(4, sf::FloatRect(0, 0, m_field.width, m_field.height));
    }

    auto it = m_entities.begin();
    while (it != m_entities.end())
    {
        auto &entity = *it;
        entity->setHighlight(false);
        entity->update(dt);

        if (!entity->isActive())
        {
            it = m_entities.erase(it);
            continue;
        }

        m_quadtree->insert(entity);

        it++;
    }

    auto res = m_quadtree->entitiesIn(m_highlight.getGlobalBounds());
    for (auto &e : *res)
    {
        e->setHighlight(true);
    }

    for (auto &e : m_entities)
    {
        auto possibleCollisions = m_quadtree->entitiesIn(e->getBounds());
        for (auto &colliding : *possibleCollisions)
        {
            if (e->getId() == colliding->getId() || (!e->isActive() || !colliding->isActive()))
            {
                continue;
            }

            e->checkCollision(*colliding);
        }
    }
}

void Main::draw(yoku::Window &window)
{
    //std::cout << "ents: " << m_entities.size() << '\n';
    for (auto &e : m_entities)
    {
        window.draw(e->getDrawable());
    }

    if (m_quadtree != nullptr)
    {
        m_quadtree->draw(window);
        m_quadtree->clear();
    }

    window.draw(m_highlight);
}

void Main::addEntity(const sf::Vector2i &pos)
{
    auto id = m_entities.size() + 1;
    auto ent = std::make_shared<Cell>(id, pos, m_field);

    m_entities.emplace_back(ent);
}