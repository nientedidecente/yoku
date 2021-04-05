#pragma once

#include "Scene.hpp"

#include <unordered_map>
#include <memory>
namespace yoku
{
    class SceneManager
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
        std::shared_ptr<Scene> m_CurrentScene = nullptr;

    public:
        SceneManager();

        void add(std::shared_ptr<Scene> scene);
        void switchTo(const std::string &sceneName);
        std::shared_ptr<Scene> getCurrent();
    };
}
