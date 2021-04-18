#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "SceneManager.hpp"

class Splash : public yoku::Scene
{
private:
    yoku::SceneManager &m_SM;
    sf::Text m_Title;
    sf::Text m_Instruction;

public:
    Splash(yoku::SceneManager &sm) : Scene("splash"), m_SM(sm) {}

    void onCreate() override;
    void processEvent(sf::Event &event) override;
    void draw(yoku::Window &window) override;
};
