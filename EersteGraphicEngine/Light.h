#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "IEntity.h"

namespace ege
{
    enum class LightType
    {
        PointLight,
        SportLight,
        DirectionalLight,
        AmbientLight
    };

    class Light: public IEntity
    {
    public:
        Light(LightType type);
        virtual ~Light() = 0;

        virtual void    Initialise() = 0;
        virtual void    Update() = 0;
        virtual void    Draw() = 0;

        LightType       GetType();
        const XMFLOAT4& GetColor() const;
        void            SetColor(XMFLOAT4 color);

        virtual void    UpdateLocalPosition() = 0;
        virtual void    Move(XMVECTOR movement) override {};
        virtual void    Scale(XMVECTOR origin, XMVECTOR scale) override {};
        virtual void    Scale(XMVECTOR scale) override {};
        virtual void    Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override {};
        virtual void    Rotate(XMVECTOR eulerAngles) override {};
        
    public:
        static const XMFLOAT4 DefaultLightColor;

    protected:
        RenderAPI& _renderAPI;

        LightType  _type;
        XMFLOAT4   _color;
    };
}