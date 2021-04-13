#include "Simulation.hpp"

#include "scenes/Splash.hpp"

#include <memory>

const int WIDTH = 800;
const int HEIGHT = 600;

Simulation::Simulation() : yoku::Game("Simulation", WIDTH, HEIGHT)
{
    auto splash = std::make_shared<Splash>(m_SceneManager);
    m_SceneManager.add(splash);
}