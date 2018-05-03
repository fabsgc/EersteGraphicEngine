#pragma once

#include "PrerequisitesCore.h"
#include "IResourceManager.h"
#include "IModule.h"
#include "Shader.h"

namespace ege
{
    class ShaderManager : public IModule<ShaderManager>, public IResourceManager<Shader>
    {
    public:
        ShaderManager() {}
        ~ShaderManager() {}

        void OnStartUp() override;
        void OnShutDown() override;
        void Initialise() override;
    };

    ShaderManager& gShaderManager();
    ShaderManager* gShaderManagerPtr();
}