#include "Main.hpp"

#include "../entities/Cell.hpp"
#include "../libs/Timer.hpp"

#include <iostream>

void Main::processInput(float dt)
{
    auto pos = m_window.getMousePosition();
    m_highlight.setPosition(pos.x, pos.y);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_entities.size() > 0)
    {
        m_inputlag += dt;
        if (m_inputlag >= .1f)
        {
            m_entities.pop_back();
            m_inputlag = 0;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_inputlag += dt;
        if (m_inputlag >= .1f)
        {
            addEntity(pos);
            m_inputlag = 0;
        }
    }
}

void Main::update(float dt)
{
    Timer timer("update");
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
}

void Main::draw(yoku::Window &window)
{
    std::cout << "ents: " << m_entities.size() << '\n';
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
    auto ent = std::make_shared<Cell>(pos, m_field);
    m_entities.emplace_back(ent);
}