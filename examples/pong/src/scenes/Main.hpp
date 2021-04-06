#pragma once
#include "../libs/Randomizer.hpp"
#include "../entities/Entity.hpp"
#include "../entities/Ball.hpp"
#include "../entities/PlayerPaddle.hpp"
#include "../entities/CpuPaddle.hpp"

#include <SFML/Graphics.hpp>
#include "yoku/Scene.hpp"
#include <memory>
#include <array>
#include <random>

class Main : public yoku::Scene
{
private:
    sf::IntRect m_Field;
    sf::Text m_PlayerScoreTxt;
    sf::Text m_CpuScoreTxt;
    std::array<std::shared_ptr<Entity>, 3> m_Entities;

    std::shared_ptr<Ball> m_Ball;
    std::shared_ptr<PlayerPaddle> m_PlayerPaddle;
    std::shared_ptr<CpuPaddle> m_CpuPaddle;

    int m_PlayerScore = 0;
    int m_CpuScore = 0;

public:
    Main(int width, int height)
        : Scene("main"), m_Field(0, 0, width, height) {}
    void onCreate() override;
    void onDestroy() override;
    void processInput(sf::Event &event) override;
    void update(float dt) override;
    void draw(yoku::Window &window) override;
};
