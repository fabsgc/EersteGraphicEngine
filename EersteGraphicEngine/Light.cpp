#include "Light.h"

namespace ege
{
    const XMFLOAT4 Light::DefaultLightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f);

    Light::Light(LightType type)
        : IEntity(EntityType::Light)
        , _renderAPI(gRenderAPI())
        , _type(type)
        , _color(DefaultLightColor)
        , _drawLightModel(false)
        , _isEnabled(true)
        , _castShadow(true)
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

    void Light::UpdateLocalPosition()
    {
        XMMATRIX worldInverse = XMMatrixInverse(nullptr, XMLoadFloat4x4(&_world));
        XMVECTOR position = XMVector3Transform(XMLoadFloat3(&_position), XMLoadFloat4x4(&_world));
        XMStoreFloat3(&_position, position);
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