#include "SpotLight.h"

namespace ege
{
    const XMFLOAT3 SpotLight::DefaultPosition   = XMFLOAT3(-2.0f, 2.0f, -2.0f);
    const XMFLOAT3 SpotLight::DefaultDirection  = XMFLOAT3(0.5f, -0.5f, 0.5f);
    const float    SpotLight::DefaultRadius     = 5.0f;
    const float    SpotLight::DefaultInnerAngle = 0.4f;
    const float    SpotLight::DefaultOuterAngle = 0.1f;

    SpotLight::SpotLight()
        : Light(LightType::SpotLight)
        , _direction(DefaultDirection)
        , _radius(DefaultRadius)
        , _innerAngle(DefaultInnerAngle)
        , _outerAngle(DefaultOuterAngle)
    {
        _position    = DefaultPosition;

        _lightModel = ege_shared_ptr_new<LightModel>("spot-light");
        _lightModel->Initialise();
        _lightModel->GoTo(_position);
        _lightModel->SetColor(Color(Colors::Yellow));
    }

    SpotLight::~SpotLight()
    {
    }

    void SpotLight::Initialise()
    {
    }

    void SpotLight::Update()
    {
        _lightModel->Update();
    }

    void SpotLight::Draw()
    {
        if (_drawLightModel)
        {
            _lightModel->Draw();
        }

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        constantBufferUpdate->LightColor      = _color;
        constantBufferUpdate->LightDirection  = _direction;
        constantBufferUpdate->LightPosition   = _position;
        constantBufferUpdate->LightRadius     = _radius;
        constantBufferUpdate->LightInnerAngle = _innerAngle;
        constantBufferUpdate->LightOuterAngle = _outerAngle;
        constantBufferUpdate->LightType       = static_cast<UINT>(_type);
    }

    const XMFLOAT3& SpotLight::GetDirection() const
    {
        return _direction;
    }

    void SpotLight::SetDirection(XMFLOAT3 direction)
    {
        _direction = direction;
    }

    void SpotLight::SetRadius(float radius)
    {
        _radius = radius;
    }

    const float& SpotLight::GetRadius() const
    {
        return _radius;
    }

    void SpotLight::SetInnerAngle(float innerAngle)
    {
        _innerAngle = innerAngle;
    }

    const float& SpotLight::GetInnerAngle() const
    {
        return _innerAngle;
    }

    void SpotLight::SetOuterAngle(float outerAngle)
    {
        _outerAngle = outerAngle;
    }

    const float& SpotLight::GetOuterAngle() const
    {
        return _outerAngle;
    }
}