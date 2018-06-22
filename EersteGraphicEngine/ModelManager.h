#pragma once

#include "PrerequisitesCore.h"
#include "IResourceManager.h"
#include "ModelLoader.h"
#include "IModule.h"
#include "Model.h"

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
        void Load(String filePath, String name);
        void Get(String name, Model& model);

    protected:
        ModelLoader _modelLoader;
    };

    ModelManager& gModelManager();
    ModelManager* gModelManagerPtr();
}