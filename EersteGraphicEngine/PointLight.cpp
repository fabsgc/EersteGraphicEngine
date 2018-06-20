#include "PointLight.h"

namespace ege
{
    const XMFLOAT3 PointLight::DefaultPosition = XMFLOAT3(-2.0f, 2.0f, -2.0f);
    const float    PointLight::DefaultRadius   = 5.0f;

    PointLight::PointLight()
        : Light(LightType::PointLight)
        , _radius(DefaultRadius)
    {
        _position = DefaultPosition;
        _lightModel = ege_shared_ptr_new<LightModel>("point-light");
        _lightModel->Initialise();
        _lightModel->GoTo(_position);
    }

    PointLight::~PointLight()
    {
    }

    void PointLight::Initialise()
    {
    }

    void PointLight::Update()
    {
        _lightModel->Update();
    }

    void PointLight::Draw()
    {
        if (_drawLightModel)
        {
            _lightModel->Draw();
        }

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);
        LightConstantBuffer* constantBufferUpdate = (LightConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::LIGHT);

        constantBufferUpdate->LightColor     = _color;
        constantBufferUpdate->LightPosition  = _position;
        constantBufferUpdate->LightType      = static_cast<UINT>(_type);
    }
}