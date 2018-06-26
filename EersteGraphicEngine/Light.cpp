#include "Light.h"
#include "LightModel.h"

namespace ege
{
    const XMFLOAT4 Light::DefaultLightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f);
    const bool Light::DefaultCastShadow     = true;
    const bool Light::DefaultDrawLightModel = false;
    const bool Light::DefaultIsEnabled      = true;

    Light::Light(LightType type)
        : IEntity(EntityType::Light)
        , _renderAPI(gRenderAPI())
        , _type(type)
        , _color(DefaultLightColor)
        , _drawLightModel(DefaultDrawLightModel)
        , _isEnabled(DefaultIsEnabled)
        , _castShadow(DefaultCastShadow)
    {
    }

    Light::~Light()
    {
    }

    void Light::Initialise()
    {
    }

    void Light::Update()
    {
    }

    void Light::Draw()
    {
    }

    void Light::Move(XMVECTOR movement)
    {
        IMoveable::Move(movement);

        if (_lightModel != nullptr)
        {
            _lightModel->Move(movement);
        }
    }

    void Light::MoveStrafe(XMVECTOR movement)
    {
        IMoveable::MoveStrafe(movement);

        if (_lightModel != nullptr)
        {
            _lightModel->MoveStrafe(movement);
        }
    }

    void Light::Rotate(XMVECTOR point, XMVECTOR eulerAngles)
    {
        IMoveable::Rotate(point, eulerAngles);

        if (_lightModel != nullptr)
        {
            _lightModel->Rotate(point, eulerAngles);
        }
    }

    void Light::Rotate(XMVECTOR eulerAngles)
    {
        IMoveable::Rotate(eulerAngles);

        if (_lightModel != nullptr)
        {
            _lightModel->Rotate(eulerAngles);
        }
    }

    const LightType& Light::GetType() const
    {
        return _type;
    }

    const XMFLOAT4& Light::GetColor() const
    {
        return _color;
    }

    void Light::SetColor(XMFLOAT4 color)
    {
        _color = color;
    }

    void Light::SetColor(const Color color)
    {
        _color = color.ToXMFLOAT4();
    }

    void Light::SetDrawLightModel(bool drawLightModel)
    {
        _drawLightModel = drawLightModel;
    }

    void Light::SetCastShadow(bool castShadow)
    {
        _castShadow = castShadow;
    }

    void Light::SetEnabled(bool enabled)
    {
        _isEnabled = enabled;
    }

    const bool Light::GetCastShadow() const
    {
        return _castShadow;
    }

    const bool Light::IsEnabled() const
    {
        return _isEnabled;
    }
}