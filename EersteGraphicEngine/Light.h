#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "Node.h"

namespace ege
{
    enum class LightType
    {
        PointLight       = 0,
        SpotLight        = 1,
        DirectionalLight = 2,
        AmbientLight     = 3
    };

    class Light: public Node
    {
    public:
        Light(LightType type);
        virtual ~Light() = 0;

        virtual void     Initialise() = 0;
        virtual void     Update() = 0;
        virtual void     Draw() = 0;

        using            IMoveable::Move;
        using            IMoveable::MoveStrafe;
        using            IMoveable::Scale;
        using            IMoveable::Rotate;
        virtual void     Move(XMVECTOR movement) override;
        virtual void     MoveStrafe(XMVECTOR movement) override;
        virtual void     Scale(XMVECTOR origin, XMVECTOR scale) override;
        virtual void     Scale(XMVECTOR scale) override;
        virtual void     Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override;
        virtual void     Rotate(XMVECTOR eulerAngles) override;

        const LightType& GetType() const;
        const XMFLOAT4&  GetColor() const;
        void             SetColor(const XMFLOAT4 color);
        void             SetColor(const Color color);

        void             SetDrawLightModel(bool drawLightModel);
        void             SetCastShadow(bool castShadow);
        void             SetEnabled(bool enabled);
        const bool       GetCastShadow() const;
        const bool       IsEnabled() const;
        
    protected:
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