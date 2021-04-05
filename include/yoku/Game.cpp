#include "Game.hpp"

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
namespace yoku
{
    void Game::run()
    {
        while (m_Window.isOpen())
        {
            auto scene = m_SceneManager.getCurrent();
            auto dt = m_Clock.restart().asSeconds();
#if FPS == 1
            m_Window.getRenderer().setTitle(
                m_Name + " -  FPS: " + std::to_string((1 / dt)));
#endif

            auto event = m_Window.getEvent();

            if (scene != nullptr)
            {
                scene->processInput(event);
                scene->update(dt);
                m_Window.startDraw();
                scene->draw(m_Window);
                m_Window.endDraw();
            }
        }
    }
}
