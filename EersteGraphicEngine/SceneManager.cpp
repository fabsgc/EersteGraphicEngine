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
#if defined(EGE_CONFIG_SCENE_FILE)
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_SCENE_FILE);

        tinyxml2::XMLElement* scenesElement = document.FirstChildElement("scenes");
        EGE_ASSERT_ERROR((scenesElement != nullptr), "Scene file malformed");

        for (tinyxml2::XMLElement* sceneElement = scenesElement->FirstChildElement("scene"); sceneElement != nullptr; sceneElement = sceneElement->NextSiblingElement())
        {
            SPtr<Scene> scene = ege_shared_ptr_new<Scene>();
            String name = sceneElement->Attribute("name");
            String filePath = sceneElement->Attribute("file");

            _sceneLoader.Load(filePath, scene);
            Insert(name, scene);
        }
#endif
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