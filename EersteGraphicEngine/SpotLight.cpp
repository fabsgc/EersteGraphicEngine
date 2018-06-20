#include "SpotLight.h"

namespace ege
{
    const XMFLOAT3 SpotLight::DefaultPosition  = XMFLOAT3(-2.0f, 2.0f, -2.0f);
    const float    SpotLight::DefaultRadius    = 5.0f;
    const XMFLOAT3 SpotLight::DefaultDirection = XMFLOAT3(0.5f, -0.5f, 0.5f);

    SpotLight::SpotLight()
        : Light(LightType::SpotLight)
        , _direction(DefaultDirection)
        , _radius(DefaultRadius)
    {
        _position    = DefaultPosition;
        _lightModel = ege_shared_ptr_new<LightModel>("spot-light");
        _lightModel->Initialise();
        _lightModel->GoTo(_position);
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

        constantBufferUpdate->LightColor     = _color;
        constantBufferUpdate->LightDirection = _direction;
        constantBufferUpdate->LightPosition  = _position;
        constantBufferUpdate->LightType      = static_cast<UINT>(_type);
    }

    const XMFLOAT3& SpotLight::GetDirection() const
    {
        return _direction;
    }

    void SpotLight::SetDirection(XMFLOAT3 direction)
    {
        _direction = direction;
    }
}