#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "SceneManager.hpp"

class Splash : public yoku::Scene
{
private:
    int m_width, m_height;
    yoku::SceneManager &m_SM;
    sf::Text m_Title;
    sf::Text m_Instruction;

public:
    Splash(yoku::SceneManager &sm, int width, int height) : Scene("splash"), m_width(width), m_height(height), m_SM(sm) {}

    void onCreate() override;
    void onDestroy() override;
    void processEvent(sf::Event &event) override;
    void draw(yoku::Window &window) override;
};
