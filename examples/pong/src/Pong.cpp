#include "Pong.hpp"

#include "scenes/Splash.hpp"
#include "scenes/Main.hpp"

#include <memory>

const int WIDTH = 800;
const int HEIGHT = 600;

Pong::Pong() : yoku::Game("Pong", WIDTH, HEIGHT)
{
    auto splash = std::make_shared<Splash>(m_SceneManager);
    m_SceneManager.add(splash);
    auto main = std::make_shared<Main>(WIDTH, HEIGHT);
    m_SceneManager.add(main);
}