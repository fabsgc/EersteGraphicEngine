#include "ShaderManager.h"

namespace ege
{
    void ShaderManager::OnStartUp()
    {

    }

    void ShaderManager::OnShutDown()
    {

    }

    void ShaderManager::Initialise()
    {

    }

    ShaderManager& gShaderManager()
    {
        return static_cast<ShaderManager&>(ShaderManager::Instance());
    }

    ShaderManager* gShaderManagerPtr()
    {
        return static_cast<ShaderManager*>(ShaderManager::InstancePtr());
    }
}