#pragma once

#include "PrerequisitesCore.h"
#include "IResourceManager.h"
#include "Texture.h"
#include "IModule.h"

namespace ege
{
    class TextureManager : public IModule<TextureManager>, public IResourceManager<Texture>
    {
    public:
        TextureManager() {}
        ~TextureManager() {}

        void OnStartUp() override;
        void OnShutDown() override;
        void Initialise() override;
    };

    TextureManager& gTextureManager();
    TextureManager* gTextureManagerPtr();
}