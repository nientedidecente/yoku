#pragma once
#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "SceneManager.hpp"

#include "../entities/Entity.hpp"
#include "../libs/Quadtree.hpp"

#include <memory>

class Main : public yoku::Scene
{
private:
    yoku::Window &m_window;
    sf::IntRect m_field;
    std::unique_ptr<Quadtree> m_quadtree = nullptr;
    std::vector<std::shared_ptr<Entity>> m_entities;

public:
    Main(yoku::Window &window)
        : Scene("main"), m_window(window),
          m_field(0, 0, window.getWidth(), window.getHeight()) {}
    void onCreate() override;
    void onDestroy() override;

    void processEvent(sf::Event &event) override;
    void processInput() override;

    void update(float dt) override;
    void draw(yoku::Window &window) override;

    void addEntity(const sf::Vector2i &pos);
};
