#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
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
        RenderAPI&   _renderAPI;
        SPtr<Shader> _shader;
    };
}