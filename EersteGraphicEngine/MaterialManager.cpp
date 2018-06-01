#include "MaterialManager.h"

namespace ege
{
    void MaterialManager::OnStartUp()
    {
        Initialise();
    }

    void MaterialManager::OnShutDown()
    {
    }

    void MaterialManager::Initialise()
    {
    }

    MaterialManager& gMaterialManager()
    {
        return static_cast<MaterialManager&>(MaterialManager::Instance());
    }

    MaterialManager* gMaterialManagerPtr()
    {
        return static_cast<MaterialManager*>(MaterialManager::InstancePtr());
    }
}