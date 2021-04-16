#pragma once

#include "../entities/Entity.hpp"
#include "Window.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <memory>

class Quadtree
{
private:
    bool m_split = false;
    bool m_maxElements = false;
    sf::FloatRect m_boundaries;
    std::array<std::unique_ptr<Quadtree>, 4> m_subquads = {nullptr, nullptr, nullptr, nullptr};
    std::vector<std::shared_ptr<Entity>> m_entities;

    void split();

public:
    Quadtree(const int maxElements, const sf::FloatRect bounds) : m_maxElements(maxElements), m_boundaries(bounds) {}
    bool insert(const std::shared_ptr<Entity> &entity);
    std::vector<std::shared_ptr<Entity>> &entitiesIn(const sf::FloatRect &bounds);

    void draw(yoku::Window &window);
};
