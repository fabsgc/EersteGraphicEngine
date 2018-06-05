#include "PointLight.h"

namespace ege
{
    const XMFLOAT3 PointLight::DefaultPosition = XMFLOAT3(-2.0f, 2.0f, -2.0f);
    const float    PointLight::DefaultRadius   = 5.0f;

    PointLight::PointLight()
        : DirectionalLight()
        , _radius(DefaultRadius)
    {
        _position = DefaultPosition;
    }

    PointLight::~PointLight()
    {
    }

    void PointLight::Initialise()
    {
    }

    void PointLight::Update()
    {
    }

    void PointLight::Draw()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer();
        ConstantBuffer* constantBufferUpdate = _renderAPI.GetConstantBufferUpdate();

        constantBufferUpdate->LightColor = _color;
        constantBufferUpdate->LightDirection = XMFLOAT4(_direction.x, _direction.y, _direction.z, 0.0f);
        constantBufferUpdate->LightPosition = XMFLOAT4(_position.x, _position.y, _position.z, 0.0f);
        constantBufferUpdate->LightRadius = XMFLOAT4(_radius, 0.0f, 0.0f, 0.0f);
    }
}