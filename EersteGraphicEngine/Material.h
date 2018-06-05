#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"
#include "RenderAPI.h"
#include "Texture.h"
#include "Shader.h"

namespace ege
{
    class Material: public IUpdatable
    {
    public:
        Material();
        Material(SPtr<Shader> shader);
        virtual ~Material() = 0 {};
        virtual void    Initialise();
        virtual void    Update() override;
        virtual void    Apply();

        const XMFLOAT4& GetSpecularColor() const;
        const float&    GetSpecularPower() const;
        void            SetSpecularColor(XMFLOAT4& specularColor);
        void            SetSpecularPower(float specularPower);

    protected:
        static const XMFLOAT4 DefaultSpecularColor;
        static const float    DefaultSpecularPower;

    protected:
        RenderAPI&               _renderAPI;

        Map<UINT, SPtr<Texture>> _textures;
        SPtr<Shader>             _shader;

        XMFLOAT4                 _specularColor;
        float                    _specularPower;
    };
}