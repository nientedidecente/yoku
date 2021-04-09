#include "Window.hpp"

namespace yoku
{
    Window::Window(const std::string &title, int width = 800, int height = 600, sf::Uint32 style = sf::Style::Titlebar)
        : m_Renderer(sf::VideoMode(width, height), title, style), m_Width(width), m_Height(height)
    {
        m_Renderer.setVerticalSyncEnabled(true);
    }

    sf::RenderWindow &Window::getRenderer()
    {
        return m_Renderer;
    }

    bool Window::isOpen()
    {
        return m_Renderer.isOpen();
    }

    sf::Event Window::getEvent()
    {
        sf::Event event;
        while (m_Renderer.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                m_Renderer.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                m_Renderer.close();

            return event;
        }

        return event;
    }

    sf::Vector2i Window::getMousePosition()
    {
        return sf::Mouse::getPosition(m_Renderer);
    }

    void Window::startDraw()
    {
        m_Renderer.clear(m_BgColor);
    }

    void Window::draw(sf::Drawable &drawable)
    {
        m_Renderer.draw(drawable);
    }

    void Window::endDraw()
    {
        m_Renderer.display();
    }
}