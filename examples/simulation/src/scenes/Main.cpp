#include "rng.hpp"

#include "Main.hpp"

#include "../entities/Cell.hpp"
#include "../entities/Food.hpp"
#include "../libs/Timer.hpp"

#include <iostream>

Main::Main(yoku::Window &window)
    : Scene("main"), m_window(window),
      m_field(0, 0, window.getWidth(), window.getHeight()),
      m_highlight(sf::Vector2f(100, 100)),
      m_input({sf::Keyboard::D, sf::Keyboard::F})
{
    m_highlight.setOutlineColor(sf::Color::Green);
    m_highlight.setOutlineThickness(1.f);
    m_highlight.setFillColor(sf::Color::Transparent);
    auto bounds = m_highlight.getLocalBounds();
    m_highlight.setOrigin(bounds.width / 2, bounds.height / 2);
}

void Main::onActivate()
{
    auto font = yoku::Assets::getInstance()->loadFont("callingcode");
    m_info.setFont(*font);
    m_info.setPosition(10, 10);
    m_info.setCharacterSize(15);
}

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

    if (m_input.wasKeyPressed(sf::Keyboard::F))
    {
        auto id = yoku::rng::str(5) + "_Food";
        auto food = std::make_shared<Food>(id, m_field);
        m_entities.emplace_back(food);
    }
}

void Main::update(float dt)
{
    m_info.setString("Entities: " + std::to_string(m_entities.size()));
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
    window.draw(m_info);
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
    auto index = m_entities.size() + 1;
    auto id = yoku::rng::str(5) + "_" + std::to_string(index);
    auto ent = std::make_shared<Cell>(id, pos, m_field);

    m_entities.emplace_back(ent);
}