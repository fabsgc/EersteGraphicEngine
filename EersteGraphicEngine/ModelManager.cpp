#include "ModelManager.h"

namespace ege
{
    void ModelManager::OnStartUp()
    {
    }

    void ModelManager::OnShutDown()
    {
    }

    void ModelManager::Initialise()
    {
    }

    ModelManager& gModelManager()
    {
        return static_cast<ModelManager&>(ModelManager::Instance());
    }

    ModelManager* gModelManagerPtr()
    {
        return static_cast<ModelManager*>(ModelManager::InstancePtr());
    }
}