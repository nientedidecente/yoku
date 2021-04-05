#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <unordered_map>
#include <string>
namespace yoku
{
    class Assets
    {
    private:
        static Assets *instance;
        Assets() {}
        std::unordered_map<std::string, std::shared_ptr<sf::Font>> m_Fonts;

    public:
        static Assets *getInstance()
        {
            if (instance == nullptr)
                instance = new Assets();
            return instance;
        }

        std::shared_ptr<sf::Font> loadFont(std::string name);
    };
}