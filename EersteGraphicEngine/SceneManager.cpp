#include "SceneManager.h"

namespace ege
{
    void SceneManager::OnStartUp()
    {
        Initialise();
    }

    void SceneManager::OnShutDown()
    {
    }

    void SceneManager::Initialise()
    {
    }

    SceneManager& gSceneManager()
    {
        return static_cast<SceneManager&>(SceneManager::Instance());
    }

    SceneManager* gSceneManagerPtr()
    {
        return static_cast<SceneManager*>(SceneManager::InstancePtr());
    }
}