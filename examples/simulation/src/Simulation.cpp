#include "Simulation.hpp"

#include "scenes/Splash.hpp"
#include "scenes/Main.hpp"

#include <memory>

const int WIDTH = 800;
const int HEIGHT = 600;

Simulation::Simulation()
    : yoku::Game("Simulation", WIDTH, HEIGHT, sf::Style::Titlebar | sf::Style::Close)
{
    auto splash = std::make_shared<Splash>(m_SceneManager);
    auto main = std::make_shared<Main>(m_Window);
    m_SceneManager.add(splash);
    m_SceneManager.add(main);
}