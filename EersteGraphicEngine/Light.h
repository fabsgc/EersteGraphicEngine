#pragma once

#include "PrerequisitesCore.h"
#include "IMoveable.h"
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

    class Light: public IEntity, public IMoveable
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
        
    public:
        static const XMFLOAT4 DefaultLightColor;

    protected:
        RenderAPI& _renderAPI;

        LightType  _type;
        XMFLOAT4   _color;
    };
}