#include "Pong.hpp"

#include "scenes/Splash.hpp"
#include "scenes/Main.hpp"

#include <memory>

Pong::Pong() : yoku::Game("Pong")
{
    auto splash = std::make_shared<Splash>(m_SceneManager);
    m_SceneManager.add(splash);
    auto main = std::make_shared<Main>();
    m_SceneManager.add(main);
}