#pragma once

#include "PrerequisitesCore.h"
#include "IResourceManager.h"
#include "ModelLoader.h"
#include "IModule.h"

namespace ege
{
    class ModelManager : public IModule<ModelManager>, public IResourceManager<ModelDesc>
    {
    public:
        ModelManager() {};
        ~ModelManager() {};

        void OnStartUp() override;
        void OnShutDown() override;
        void Initialise() override;

    private:
        ModelLoader _modelLoader;
    };

    ModelManager& gModelManager();
    ModelManager* gModelManagerPtr();
}