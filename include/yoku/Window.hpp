#pragma once

#include <SFML/Graphics.hpp>

namespace yoku
{
    class Window
    {
    private:
        sf::RenderWindow m_Renderer;
        sf::Color m_BgColor = sf::Color::Black;
        int m_Width;
        int m_Height;

    public:
        Window(const std::string &title, int width, int height, sf::Uint32 style);
        bool isOpen();
        void setBgColour(sf::Color color) { m_BgColor = color; }
        int getWidth() { return m_Width; }
        int getHeight() { return m_Height; }
        sf::RenderWindow &getRenderer();
        sf::Vector2i getMousePosition();
        sf::Event getEvent();

        void startDraw();
        void draw(sf::Drawable &drawable);
        void endDraw();
    };
}
