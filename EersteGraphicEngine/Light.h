#pragma once

#include "PrerequisitesCore.h"
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

        virtual void     Move(XMVECTOR movement);
        virtual void     Move(XMFLOAT3 movement);
        virtual void     Move(float x, float y, float z);

        virtual void     Scale(XMVECTOR origin, XMVECTOR scale) override {};
        virtual void     Scale(XMVECTOR scale) override {};
        virtual void     Scale(XMFLOAT3 origin, XMFLOAT3 scale) override {};
        virtual void     Scale(XMFLOAT3 scale) override {};
        virtual void     Scale(XMFLOAT3 origin, float x, float y, float z) override {};
        virtual void     Scale(float x, float y, float z) override {};

        virtual void     Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override;
        virtual void     Rotate(XMVECTOR eulerAngles) override;
        virtual void     Rotate(XMFLOAT3 origin, XMFLOAT3 eulerAngles) override;
        virtual void     Rotate(XMFLOAT3 eulerAngles) override;
        virtual void     Rotate(XMFLOAT3 origin, float yaw, float pitch, float roll) override;
        virtual void     Rotate(float yaw, float pitch, float roll) override;

        const LightType& GetType() const;
        const XMFLOAT4&  GetColor() const;
        void             SetColor(const XMFLOAT4 color);
        void             SetColor(const Color color);

        void             SetDrawLightModel(bool drawLightModel);
        void             SetCastShadow(bool castShadow);
        void             SetEnabled(bool enabled);
        const bool       GetCastShadow() const;
        const bool       IsEnabled() const;
        
    public:
        static const XMFLOAT4 DefaultLightColor;
        static const bool     DefaultCastShadow;
        static const bool     DefaultDrawLightModel;
        static const bool     DefaultIsEnabled;

    protected:
        RenderAPI&        _renderAPI;

        LightType         _type;
        XMFLOAT4          _color;
        SPtr<LightModel> _lightModel;

        bool              _isEnabled;
        bool              _castShadow;
        bool              _drawLightModel;
    };
}