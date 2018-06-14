#pragma once

#include "PrerequisitesCore.h"
#include "LightSchema.h"
#include "RenderAPI.h"
#include "IEntity.h"


namespace ege
{
    enum class LightType
    {
        PointLight = 0,
        SpotLight = 1,
        DirectionalLight = 2,
        AmbientLight = 3
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

        virtual void    UpdateLocalPosition() override;
        virtual void    Move(XMVECTOR movement) override {};
        virtual void    Scale(XMVECTOR origin, XMVECTOR scale) override {};
        virtual void    Scale(XMVECTOR scale) override {};
        virtual void    Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override {};
        virtual void    Rotate(XMVECTOR eulerAngles) override {};

        void            SetDrawLightSchema(bool drawLightSchema);
        void            SetCastShadow(bool castShadow);
        void            SetEnabled(bool enabled);
        bool            GetCastShadow();
        bool            IsEnabled();
        
    public:
        static const XMFLOAT4 DefaultLightColor;

    protected:
        RenderAPI&        _renderAPI;

        LightType         _type;
        XMFLOAT4          _color;
        bool              _isEnabled;
        bool              _castShadow;
        bool              _drawLightSchema;
        SPtr<LightSchema> _lightSchema;
    };
}