#include "Quadtree.hpp"
#include <iostream>

// TODO: move this to an helpers header on yoku maybe
std::ostream &operator<<(std::ostream &o, const sf::FloatRect &r)
{
    o << "x: " << r.top << " y: " << r.left << " | w: " << r.width << " h: " << r.height << '\n';

    return o;
}

bool Quadtree::insert(const std::shared_ptr<Entity> &entity)
{
    if (!m_boundaries.contains(entity->getPosition()))
    {
        // if is not within its bounds
        return false;
    }

    if (m_entities.size() < m_maxElements)
    {
        m_entities.emplace_back(entity);
        return true;
    }

    // otherwise split if not already split
    if (!m_split)
    {
        split();
    }

    for (auto &subquad : m_subquads)
    {
        if (subquad->insert(entity))
        {
            return true;
        }
    }

    // not able to insert anywhere,
    //this should never happen
    return false;
}

void Quadtree::split()
{
    auto x = m_boundaries.left;
    auto y = m_boundaries.top;
    auto width = m_boundaries.width / 2;
    auto height = m_boundaries.height / 2;

    auto topLeft = sf::FloatRect(x, y, width, height);
    m_subquads[0] = std::make_unique<Quadtree>(m_maxElements, topLeft);

    auto topRight = sf::FloatRect(x + width, y, width, height);
    m_subquads[1] = std::make_unique<Quadtree>(m_maxElements, topRight);

    auto bottomLeft = sf::FloatRect(x, y + height, width, height);
    m_subquads[2] = std::make_unique<Quadtree>(m_maxElements, bottomLeft);

    auto bottomRight = sf::FloatRect(x + width, y + height, width, height);
    m_subquads[3] = std::make_unique<Quadtree>(m_maxElements, bottomRight);

    m_split = true;
}

void Quadtree::draw(yoku::Window &window)
{
    auto me = sf::RectangleShape(sf::Vector2f(m_boundaries.width, m_boundaries.height));
    me.setPosition(m_boundaries.left, m_boundaries.top);
    me.setFillColor(sf::Color::Transparent);
    me.setOutlineColor(sf::Color::White);
    me.setOutlineThickness(-1.f);
    window.draw(me);

    if (!m_split)
        return;

    for (auto &subquad : m_subquads)
    {
        subquad->draw(window);
    }
}

void Quadtree::clear()
{
    m_entities.clear();
    if (!m_split)
        return;

    for (auto &subquad : m_subquads)
    {
        subquad->clear();
    }

    std::fill(m_subquads.begin(), m_subquads.end(), nullptr);
    m_split = false;
}

vecOfEntitiesPtr Quadtree::entitiesIn(const sf::FloatRect &bounds, vecOfEntitiesPtr results)
{
    if (results == nullptr)
    {
        results = std::make_shared<vecOfEntities>();
    }

    std::vector<std::shared_ptr<Entity>> result;
    if (!m_boundaries.intersects(bounds))
    {
        return results;
    }

    for (auto &entity : m_entities)
    {
        if (bounds.intersects(entity->getBounds()))
        {
            results->emplace_back(entity);
        }
    }

    if (!m_split)
    {
        return results;
    }

    for (auto &subquad : m_subquads)
    {
        subquad->entitiesIn(bounds, results);
    }

    return results;
}