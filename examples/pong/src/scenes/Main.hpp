#pragma once
#include <SFML/Graphics.hpp>

#include "yoku/Scene.hpp"
#include <memory>

class Main : public yoku::Scene
{
private:
    sf::Text m_PlayerScoreTxt;
    sf::Text m_CpuScoreTxt;

    std::unique_ptr<sf::RectangleShape> m_PlayerPaddle;
    std::unique_ptr<sf::RectangleShape> m_CpuPaddle;

    int m_PlayerScore = 0;
    int m_CpuScore = 0;

    short m_Direction = 0;

public:
    Main() : Scene("main") {}
    void onCreate() override;
    void onDestroy() override;
    void processInput(sf::Event &event) override;
    void update(float dt) override;
    void draw(yoku::Window &window) override;
};
