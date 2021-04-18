#pragma once
#include <SFML/Graphics.hpp>

#include "Assets.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Input.hpp"

#include "../entities/Entity.hpp"
#include "../libs/Quadtree.hpp"

#include <memory>

class Main : public yoku::Scene
{
private:
    yoku::Window &m_window;
    sf::IntRect m_field;
    sf::Text m_info;
    std::unique_ptr<Quadtree> m_quadtree = nullptr;
    std::vector<std::shared_ptr<Entity>> m_entities;

    sf::RectangleShape m_highlight;
    yoku::Input m_input;

    float m_inputlag = 0;

public:
    Main(yoku::Window &window)
        : Scene("main"), m_window(window),
          m_field(0, 0, window.getWidth(), window.getHeight()),
          m_highlight(sf::Vector2f(100, 100)),
          m_input({sf::Keyboard::D})
    {
        m_highlight.setOutlineColor(sf::Color::Green);
        m_highlight.setOutlineThickness(1.f);
        m_highlight.setFillColor(sf::Color::Transparent);
        auto bounds = m_highlight.getLocalBounds();
        m_highlight.setOrigin(bounds.width / 2, bounds.height / 2);
    }
    void onCreate() override {}
    void onDestroy() override {}
    void onActivate() override;
    void processInput(float dt) override;

    void update(float dt) override;
    void draw(yoku::Window &window) override;

    void addEntity(const sf::Vector2i &pos);
};
