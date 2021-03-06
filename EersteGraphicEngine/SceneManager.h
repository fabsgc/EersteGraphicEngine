#pragma once

#include "PrerequisitesCore.h"
#include "IResourceManager.h"
#include "SceneLoader.h"
#include "Scene.h"
#include "IModule.h"

namespace ege
{
    class SceneManager : public IModule<SceneManager>, public IResourceManager<Scene>
    {
    public:
        SceneManager() {};
        ~SceneManager() {};

        void OnStartUp() override;
        void OnShutDown() override;
        void Initialise() override;

    protected:
        SceneLoader _sceneLoader;
    };

    SceneManager& gSceneManager();
    SceneManager* gSceneManagerPtr();
}