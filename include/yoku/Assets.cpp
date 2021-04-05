#include "Assets.hpp"

#include <iostream>
namespace yoku
{

    Assets *Assets::instance = nullptr;

    std::shared_ptr<sf::Font> Assets::loadFont(std::string name)
    {
        auto found = m_Fonts.find(name);
        if (found != m_Fonts.end())
        {
            return found->second;
        }

        auto font = std::make_shared<sf::Font>();
        if (!font->loadFromFile("assets/fonts/" + name + ".ttf"))
        {
            std::cout << "Cannot load font " << name << std::endl;
        }
        m_Fonts.insert(std::make_pair(name, font));

        return font;
    }
}