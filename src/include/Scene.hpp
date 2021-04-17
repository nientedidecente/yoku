#pragma once

#include "Window.hpp"

#include <functional>
#include <string>

namespace yoku
{
    class Scene
    {
    protected:
        std::string m_Name;

    public:
        bool isActive;
        Scene(const std::string &name) : m_Name(name), isActive(false) {}
        std::string getName() const { return m_Name; }

        virtual void onCreate() = 0;
        virtual void onDestroy() = 0;

        virtual void onActivate() { isActive = true; };
        virtual void onDeactivate() { isActive = false; };

        virtual void processEvent(sf::Event &event){};
        virtual void processInput(float dt){};
        virtual void update(float dt){};
        virtual void draw(Window &window){};
    };
}