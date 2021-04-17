#pragma once

#include "../entities/Entity.hpp"
#include "Window.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <memory>

using vecOfEntities = std::vector<std::shared_ptr<Entity>>;
using vecOfEntitiesPtr = std::shared_ptr<vecOfEntities>;

class Quadtree
{
private:
    bool m_split = false;
    int m_maxElements = 2;
    sf::FloatRect m_boundaries;
    std::array<std::unique_ptr<Quadtree>, 4> m_subquads = {nullptr, nullptr, nullptr, nullptr};
    std::vector<std::shared_ptr<Entity>> m_entities;

    void split();

public:
    Quadtree(const int maxElements, const sf::FloatRect bounds) : m_maxElements(maxElements), m_boundaries(bounds) {}
    bool insert(const std::shared_ptr<Entity> &entity);
    vecOfEntitiesPtr entitiesIn(const sf::FloatRect &bounds, vecOfEntitiesPtr results = nullptr);

    void draw(yoku::Window &window);

    void clear();
};
