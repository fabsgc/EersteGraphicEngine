#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "Texture.h"
#include "Shader.h"

namespace ege
{
    class Material
    {
    public:
        Material(SPtr<Shader> shader);
        virtual ~Material() = 0 {};
        virtual void Apply();

    protected:
        RenderAPI&               _renderAPI;

        Map<UINT, SPtr<Texture>> _textures;
        SPtr<Shader>             _shader;
    };
}