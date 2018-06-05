#include "Light.h"

namespace ege
{
    const XMFLOAT4 Light::DefaultLightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f);

    Light::Light(LightType type)
        : IEntity(EntityType::Light)
        , _renderAPI(gRenderAPI())
        , _type(type)
        , _color(DefaultLightColor)
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

    LightType Light::GetType()
    {
        return _type;
    }

    void Light::SetColor(XMFLOAT4 color)
    {
        _color = color;
    }

    const XMFLOAT4& Light::GetColor() const
    {
        return _color;
    }
}