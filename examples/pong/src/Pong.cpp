#include "Pong.hpp"

#include "scenes/Splash.hpp"
#include "scenes/Main.hpp"

#include <memory>

const int WIDTH = 1024;
const int HEIGHT = 576;

Pong::Pong() : yoku::Game("Pong", WIDTH, HEIGHT)
{
    auto splash = std::make_shared<Splash>(m_SceneManager, WIDTH, HEIGHT);
    m_SceneManager.add(splash);
    auto main = std::make_shared<Main>(WIDTH, HEIGHT);
    m_SceneManager.add(main);
}