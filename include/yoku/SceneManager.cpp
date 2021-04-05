#include "SceneManager.hpp"

#include <memory>
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
            return;
        }

        m_CurrentScene->onDeactivate();
        auto scene = found->second;
        m_CurrentScene = scene;
        scene->onActivate();
    }

    std::shared_ptr<Scene> SceneManager::getCurrent()
    {
        return m_CurrentScene;
    }
}
