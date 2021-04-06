#pragma once
#include "../libs/Randomizer.hpp"

#include <SFML/Graphics.hpp>
#include "yoku/Scene.hpp"
#include <memory>
#include <random>

class Main : public yoku::Scene
{
private:
    sf::IntRect m_Field;
    Randomizer rng;
    sf::Text m_PlayerScoreTxt;
    sf::Text m_CpuScoreTxt;

    std::unique_ptr<sf::RectangleShape> m_PlayerPaddle;
    std::unique_ptr<sf::RectangleShape> m_CpuPaddle;
    std::unique_ptr<sf::CircleShape> m_Ball;

    int m_PlayerScore = 0;
    int m_CpuScore = 0;

    short m_PlayerDirection = 0;
    sf::Vector2f m_BallDirection = {-1, 1};

public:
    Main(int width, int height) : Scene("main"), m_Field(0, 0, width, height)
    {
    }
    void onCreate() override;
    void onDestroy() override;
    void processInput(sf::Event &event) override;
    void update(float dt) override;
    void draw(yoku::Window &window) override;
};
