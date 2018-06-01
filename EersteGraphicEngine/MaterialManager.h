#pragma once

#include "PrerequisitesCore.h"
#include "IResourceManager.h"
#include "Material.h"
#include "IModule.h"

namespace ege
{
    class MaterialManager : public IModule<MaterialManager>, public IResourceManager<Material>
    {
    public:
        MaterialManager() {}
        ~MaterialManager() {}

        void OnStartUp() override;
        void OnShutDown() override;
        void Initialise() override;
    };

    MaterialManager& gMaterialManager();
    MaterialManager* gMaterialManagerPtr();
}