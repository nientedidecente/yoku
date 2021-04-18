#include "SceneManager.hpp"

#include <memory>
#include <iostream>
namespace yoku
{

    SceneManager::SceneManager()
    {
    }

    void SceneManager::add(std::shared_ptr<Scene> scene)
    {
        scene->onCreate();
        if (m_Scenes.empty())
        {
            m_CurrentScene = scene;
            scene->onActivate();
            scene->activate();
        }

        m_Scenes.insert(std::make_pair(scene->getName(), scene));
    }

    void SceneManager::switchTo(const std::string &sceneName)
    {
        if (m_CurrentScene->getName() == sceneName)
        {
            return;
        }

        auto found = m_Scenes.find(sceneName);
        if (found == m_Scenes.end())
        {
            std::cout << "[SCENE_MANAGER] scene: " << sceneName << " not found.\n";
            return;
        }

        m_CurrentScene->onDeactivate();
        m_CurrentScene->deactivate();

        auto scene = found->second;
        m_CurrentScene = scene;
        scene->onActivate();
        scene->activate();
    }

    std::shared_ptr<Scene> SceneManager::getCurrent()
    {
        return m_CurrentScene;
    }
}
